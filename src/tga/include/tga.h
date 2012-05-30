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
#ifndef SCOTT_OPENGL_TGA_H
#define SCOTT_OPENGL_TGA_H

#include <stdint.h>

namespace TGA
{

struct TgaImage
{
    TgaImage()
        : width(0),
          height(0),
          depth(0),
          pixels(0)
    {
    }

    TgaImage( int w, int h, int d, uint8_t *p )
        : width(w),
          height(h),
          depth(d),
          pixels(p)
    {
    }

    ~TgaImage()
    {
        delete pixels;

        // set everything to zero, sanity to ensure no double delete
        // goes undetected
        width = height = depth = 0;
        pixels = 0;
    }

    bool isValid() const
    {
        return ( pixels != 0 );
    }

    int width;
    int height;
    int depth;
    uint8_t* pixels;
};

TgaImage loadTGA( const char * filename );
bool     saveTGA( const char * filename, const TgaImage& img );
bool     savePixelBufferAsTGA( const char * filename,
                               uint8_t * pixelbuffer,
                               int width,
                               int height,
                               int depth
);
}

#endif
