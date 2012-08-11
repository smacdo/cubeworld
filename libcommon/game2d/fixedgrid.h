/*
 * Copyright (C) 2011 Scott MacDonald. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SCOTT_COMMON_GAME2D_FIXEDGRID_H
#define SCOTT_COMMON_GAME2D_FIXEDGRID_H

#include <game2d/point.h>
#include <game2d/rect.h>
#include <common/assert.h>
#include <common/delete.h>
#include <algorithm>

template<typename T>
class FixedGrid
{
public:
    /**
     * Create a fixed grid of dimensions width and height and fill it in
     * with copies of base.
     */
    FixedGrid( unsigned int width, unsigned int height, T base )
        : mWidth( width ),
          mHeight( height ),
          mTiles( new T[ mWidth * mHeight ] )
    {
        std::fill( &mTiles[0],
                   &mTiles[mWidth * mHeight],
                   base );
    }

    /**
     * Copy constructor
     */
    FixedGrid( const FixedGrid& grid )
        : mWidth( grid.mWidth ),
          mHeight( grid.mHeight ),
          mTiles( new T[ mWidth * mHeight ] )
    {
        std::copy( &grid.mTiles[0],
                   &grid.mTiles[mWidth*mHeight],
                   &mTiles[0] );
    }

    /**
     * Move constructor
     */
    FixedGrid( FixedGrid&& other )
        : mWidth( other.mWidth ),
          mHeight( other.mHeight ),
          mTiles( other.mTiles )
    {
        // reset other.mTiles to NULL so it the destructor will safely
        // not delete the tile array
        other.mTiles = NULL;
    }

    /**
     * Destructor
     */
    virtual ~FixedGrid()
    {
        DeleteArray( mTiles );
    }

    /**
     * Assignment operator
     */
    FixedGrid<T>& operator = ( const FixedGrid<T>& rhs )
    {
        ASSERT( this != &rhs );

        if ( rhs.mTiles != NULL )
        {
            // Destroy our current tile array, since we're getting rid of it
            // in the assignment
            DeleteArray( mTiles );

            // Initialize our fixed grid
            mWidth  = rhs.mWidth;
            mHeight = rhs.mHeight;
            mTiles  = new T[ mWidth * mHeight ];

            // Now copy all of the elements over
            std::copy( &rhs.mTiles[0],
                       &rhs.mTiles[mWidth * mHeight],
                       &mTiles[0] );
        }
        else
        {
            mWidth  = 0;
            mHeight = 0;
            mTiles  = NULL;
        }

        return *this;
    }

    /**
     * Move assignment operator
     *
     * \param  other  The source fixed grid that we are copying
     * \return Reference to this class after it has copied the other grid
     */
    FixedGrid& operator = ( FixedGrid&& other )
    {
        // Make sure we're not trying to assign to ourself
        if ( this != &other )
        {
            // Make sure we destroy our current tile grid before
            // assuming ownership of the new grid
            DeleteArray( mTiles );

            // Transfer the values to us
            mWidth  = other.mWidth;
            mHeight = other.mHeight;
            mTiles  = other.mTiles;

            // Now set the other fixed grid's tile pointer to null, so it
            // doesn't destroy the grid when it goes away
            other.mTiles = NULL;
        }

        return *this;
    }

    /**
     * Equality operator. Checks if the dimensions and contents of this fixed
     * grid are identical to another fixed grid
     */
    bool operator == ( const FixedGrid& rhs ) const
    {
        return std::equal( &mTiles[0],
                           &mTiles[mWidth * mHeight],
                           &(rhs.mTiles[0]) );
    }

    bool operator != ( const FixedGrid& rhs ) const
    {
        return !( *this == rhs );
    }

    /**
     * "Inserts" a fixed grid into this grid. What this means is that the
     * source grid will be copied into us at the requested position
     *
     * The source grid must fit within the bounds of the destination grid
     */
    void insert( const Point& upperLeft, FixedGrid& source ) const
    {
        Rect destBounds( 0, 0, mWidth, mHeight );
        Rect sourceBounds( upperLeft, source.mWidth, source.mHeight );

        // Verify that the source grid will fit in us
        CORE_ASSERT( destBounds.contains( sourceBounds ), "Source too large" );

        // Now copy the tiles over
        for ( unsigned int sy = 0; sy < source.mHeight; ++sy )
        {
            for ( unsigned int sx = 0; sx < source.mWidth; ++sx )
            {
                size_t si = source.offset( sx, sy );
                size_t di = this->offset( sx + upperLeft.x(),
                    sy + upperLeft.y() );

                mTiles[di] = source.mTiles[si];
            }
        }
    }

    /**
     * Clears the fixed grid by setting every tile to the requested 'base'
     *
     * \param  base  The value to assign to each tile
     */
    void clear( T base )
    {
        CORE_ASSERT( mTiles != NULL, "FixedGrid is not initialized" );

        std::fill( &mTiles[0],
                   &mTiles[mWidth * mHeight],
                   base );
    }

    /**
     * Returns a reference to the value stored at the requested position.
     *
     */
    T& get( const Point& pt  )
    {
        CORE_ASSERT( mTiles != NULL, "FixedGrid is not initialized" );
        return mTiles[ offset( pt ) ];
    }

    /**
     * Returns a reference to the value stored at the requested position.
     *
     */
    const T& get( const Point& pt ) const
    {
        CORE_ASSERT( mTiles != NULL, "FixedGrid is not initialized" );
        return mTiles[ offset( pt ) ];
    }

    void set( const Point& pt, const T& value )
    {
        CORE_ASSERT( mTiles != NULL, "FixedGrid is not initialized" );
        mTiles[ offset( pt ) ] = value;
    }

    unsigned int width() const
    {
        return mWidth;
    }

    unsigned int height() const
    {
        return mHeight;
    }

    unsigned int size() const
    {
        return mWidth * mHeight;
    }

protected:
    unsigned int offset( const Point& pt ) const
    {
        CORE_ASSERT( pt.x() < mWidth,  "X coordinate out of bounds" );
        CORE_ASSERT( pt.y() < mHeight, "Y coordinate out of bounds" );

        return pt.y() * mWidth + pt.x();
    }

    unsigned int offset( unsigned int x, unsigned int y ) const
    {
        CORE_ASSERT( x < mWidth,  "X coordinate out of bounds" );
        CORE_ASSERT( y < mHeight, "Y coordinate out of bounds" );

        return y * mWidth + x;
    }

private:
    unsigned int mWidth;
    unsigned int mHeight;
    T * mTiles;
};

#endif
