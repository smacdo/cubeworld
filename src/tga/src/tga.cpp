/**
 * Copyright 2010 Scott MacDonald. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *   1. Redistributions of source code must retain the above copyright notice,
 *  this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *  this list of conditions and the following disclaimer in the documentation
 *  and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY Scott MacDonald ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL Scott MacDonald OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of Scott MacDonald.
 */
#include "tga.h"

#include <stdint.h>
#include <stdio.h>
#include <memory>
#include <cassert>
#include <cstring>

#define TGA_NULL           0
#define TGA_COLORMAP       1
#define TGA_RGB            2
#define TGA_BW             3
#define TGA_RLE_COLORMAP   9
#define TGA_RLE_RGB       10
#define TGA_RLE_BW        11
#define TGA_COMPRESSED_COLORMAP_1
#define TGA_COMPRESSED_COLORMAP_2
#define INVALID_COLOR     0xFF00FF

using namespace TGA;

struct __attribute__((packed, aligned(1))) TGAHeader 
{
    uint8_t  id_length;
    uint8_t  maptype;
    uint8_t  imagetype;     // imge type
    uint16_t mapStart;     // starting index of colormap
    uint16_t mapLength;     // length of colormap;
    uint8_t  mapDepth;      // width of colormap
    uint16_t xOrigin;       // x-origin of the image
    uint16_t yOrigin;       // y-origin of the image
    uint16_t imageWidth;    // width of the image
    uint16_t imageHeight;   // height of the image
    uint8_t  pixelDepth;    // number of bits per pixel
    uint8_t  imageDesc;
};

void raiseTgaError( const char * message );
void reportTgaHeader( TGAHeader& header );
bool verifyTgaHeader( TGAHeader& header );
bool decompressRleStream( FILE * file, uint8_t * pixels, int length, int size );

///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////
TgaImage TGA::loadTGA( const char * filename )
{
    TGAHeader header;
    uint8_t * colormap = NULL;
    int       result   = 0;

    //
    // Open the file, and slurp the header in
    //
    FILE * f = fopen( filename, "rb" );

    if ( false == f )
    {
        raiseTgaError( "Failed to open TGA file for reading" );
        return TgaImage();
    }

    result = fread( &header, sizeof(header), 1, f );

    if ( result != 1 )
    {
        raiseTgaError( "Failed to read TGA image header" );
        return TgaImage();
    }

    // Report TGA data
    reportTgaHeader( header );

    // Make sure we support this tga image
    if ( !verifyTgaHeader( header ) )
    {
        // nope, we don't support it :(
        return TgaImage();
    }

	//
	// Do we need to read a colormap in?
	//
	if ( header.maptype == 1 )
	{
		printf( "Reading colormap (len=%d,start=%d,depth=%d)\n",
		          header.mapLength,
		          header.mapStart,
		          header.mapDepth );

		// Sanity checks
		assert( header.mapLength > 0 );
		assert( header.mapDepth == 8  || header.mapDepth == 16 ||
		        header.mapDepth == 24 || header.mapDepth == 32 );
		assert( header.mapStart <= header.mapLength );

		// If the colormap origin isn't zero, get rid of the leading empty 
		// colormap entries
		if ( header.mapStart > 0 )
		{
			printf("*** Map start is not at zero\n");
			fseek( f, header.mapStart, SEEK_CUR );
		}

		// Allocate a colormap buffer
		int size = header.mapLength - header.mapStart;
		colormap = new uint8_t[ size ];

		// Read it in
		fread( colormap, size, 1, f );
	}

    //
    // Allocate a pixel buffer, and then read the TGA pixel data into
    // memory. If the TGA image is RLE-encoded or color mapped, we'll
    // need to do some extra processing to decompress it into a RGB pixel
    // buffer.
    //
    int length       = header.imageHeight * header.imageWidth;
	int size         = header.pixelDepth / 8;
    int bytesize     = size * length; 
    uint8_t * pixels = new uint8_t[ bytesize ];

    memset( pixels, 0, bytesize );

    fprintf( stdout, "Allocating %d(%d) bytes\n", bytesize, size );

    if ( header.imagetype == TGA_RGB )
    {
        // Its a simple RGB pixel dump - slurp it into memory
        // and we're almost there
        int items = fread( pixels, size, length, f );

        if ( items != length )
        {
            raiseTgaError( "Failed reading RGB data from TGA" );
        }
    }
    else if ( header.imagetype == TGA_RLE_RGB )
    {
		decompressRleStream( f, pixels, length, size );
    }
	else if ( header.imagetype == TGA_COLORMAP )
	{
		// Read the indexed array in
		fread( pixels, size, 1, f );

		// Allocate a new buffer to store the texture in
        int       depth  = header.pixelDepth;
		uint8_t * buffer = new uint8_t[ (depth / 8) * length ];

		// Go through the indexed array, and write the pointed-to values into the
		// texture
		for ( int i = 0; i < length; ++i )
		{
			// Finish me
		}

		// Delete it and swap (refactor all this junk)
		delete buffer;
        delete colormap;
	}

    //
    // Cleanup
    //
    fclose(f);

    return TgaImage( header.imageWidth,
                     header.imageHeight,
                     header.pixelDepth,
                     pixels );
}

///////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////
bool TGA::saveTGA( const char * filename, const TgaImage& img )
{
    //
    // Verify that the passed tga image is valid and can be written to
    // disk
    //
    assert( img.pixels != 0 );
    assert( img.width > 0 && img.height > 0 && img.depth > 0 );
    assert( img.depth == 8  ||
            img.depth == 16 ||
            img.depth == 24 ||
            img.depth == 32 );

    //
    // Create a TGA header
    //
    TGAHeader header;
    memset( &header, 0, sizeof(header) );

    header.imagetype   = TGA_RGB;     // TODO add RLE support
    header.imageWidth  = img.width;
    header.imageHeight = img.height;
    header.pixelDepth  = img.depth;

    //
    // Write the TGA file out
    //
    FILE * file = fopen( filename, "wb" );
    int bytes   = img.width * img.height * ( img.depth / 8 );
    int result  = 0;
    
    // Open the file
    if ( !file )
    {
        raiseTgaError( "Could not open TGA file for writing" );
        return false;
    }

    // Write the tga image header
    result = fwrite( &header, sizeof(header), 1, file );

    if ( result != 1 )
    {
        raiseTgaError( "Could not write TGA header" );
        fclose( file );

        return false;
    }

    // Write the tga pixel data
    result = fwrite( (const void*) img.pixels, bytes, 1, file );

    if ( result != bytes )
    {
        raiseTgaError( "Could not write TGA pixel data" );
        fclose( file );

        return false;
    }

    // All done
    fclose( file );
}

bool decompressRleStream( FILE * file, uint8_t * pixels, int length, int size )
{
	// TODO convert this into pointer only
	uint8_t  packet = 0;
	uint32_t pixel  = 0;
	uint8_t* ptr    = pixels;
	int      pos    = 0;

	printf("Decompresing RLE stream; len=%d, size=%d\n", length, size);

	//
	// Process the RLE stream, one packet at a time
	//
	while ( pos < length )
	{
		// Pull the packet header in
		fread( &packet, sizeof(packet), 1, file );

		//
		// Check if this header describes a RLE pixel series, or is simply
		// a set of raw pixels
		//
		if ( (packet >> 7) == 1 )		// encoded packet header
		{
			// THIS BREAKS ON BIG ENDIAN SYSTEMS!!!
			uint8_t runlen = (packet & 0x7F) + 1;
//			printf("encoded len: %d\n", runlen);

			// Read pixel in
			if ( fread( &pixel, size, 1, file ) != 1 )
			{
				assert( false && "Failed to read encoded packet header" );
				return false;
			}

			// Pointer to the source pixel
			uint8_t * pp = reinterpret_cast<uint8_t*>(&pixel);

			// Since we have to support writing an arbitrary pixel size (8/16/24/32) 
			// that doesn't map cleanly to word types, the cleanest solution is to
			// have a double for loop like so:
			//
			//  loop( number_of_runs )
			//    loop( each byte of pixel )
			//      write to pixel
			//
			// An easier option is to treat the pixel buffer as an array of bytes,
			// AND treat the source pixel as a array of 1-4 bytes. We simply take
			// the base of the pixel address, and add the byte offset to it.
			//
			for ( int i = 0; i < runlen * size; ++i )
			{
				*ptr++ = *(pp + (i % size) );
			}

			// Update pos
			pos += runlen;
		}
		else							// raw packet header
		{
			uint8_t runlen = (packet & 0x7F) + 1;
//			printf("raw count: %d\n", runlen);

			// Read pixels in
			if ( runlen != fread( ptr, size, runlen, file ) )
			{
				assert( false && "Failed to read raw pixel run" );
				return false;
			}

			// Update pos
			pos += runlen;
			ptr += (runlen * size);
		}
	}

	return true;
}

void reportTgaHeader( TGAHeader& header )
{
    fprintf( stdout, "maptype:   %u\n", (int) header.maptype );
    fprintf( stdout, "imgtype:   %u\n", (int) header.imagetype );
    fprintf( stdout, "origin:    %u,%u\n", (int) header.xOrigin, 
                                           (int) header.yOrigin );
    fprintf( stdout, "dimemsion: %u,%u\n", (int) header.imageWidth,
                                           (int) header.imageHeight );
    fprintf( stdout, "depth:     %d\n",    (int) header.pixelDepth );
    fprintf( stdout, "descr:     %x\n",    header.imageDesc );
}

bool verifyTgaHeader( TGAHeader& header )
{
    bool bStatus = true;

    //=====================================================================
    // Validate header
    //=====================================================================
    // Reject image types
    if ( header.imagetype !=  0 && header.imagetype !=  1 &&
         header.imagetype !=  2 && header.imagetype !=  3 &&
         header.imagetype !=  9 && header.imagetype != 10    )
    {
       raiseTgaError( "TGA image type is not supported" );
       bStatus = false;
    }

    if ( header.imagetype == 11 || header.imagetype == 32 || 
         header.imagetype == 33                              )
    {
        raiseTgaError( "TGA image compression not supported" );
        bStatus = true;
    }

	if ( header.mapDepth == 15 )
	{
        raiseTgaError( "Map depth not supported" );
        bStatus = true;
	}

    if ( header.pixelDepth != 8  && header.pixelDepth != 16 &&
         header.pixelDepth != 24 && header.pixelDepth != 32 )
    {
        raiseTgaError( "Tga pixel depth not supported (must be "
                       "8, 16, 24 or 32)." );
        bStatus = true;
    }

    // Verify origin is in lower left hand corner
    if ( header.xOrigin != 0 && header.yOrigin != 0 )
    {
        raiseTgaError( "TGA image origin must be in lower left hand "
                       "corner" );
        bStatus = true;
    }

    return bStatus;
}

void raiseTgaError( const char * message )
{
    fprintf( stderr, "ERROR: %s\n", message );
}

