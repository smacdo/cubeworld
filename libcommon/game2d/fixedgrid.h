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
#include <math/rect.h>
#include <common/assert.h>
#include <boost/checked_delete.hpp>
#include <algorithm>

template<typename T>
class FixedGrid
{
public:
    /**
     * Create a fixed grid of dimensions width and height and fill it in
     * with copies of base.
     */
    FixedGrid( int width, int height, const T& base )
        : mWidth( width ), mHeight( height ),
          mTiles( new T[ mWidth * mHeight ] )
    {
        assert( width > 0 );
        assert( height > 0 );
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
        boost::checked_array_delete( mTiles );
    }

    /**
     * Assignment operator
     */
    FixedGrid<T>& operator = ( const FixedGrid<T>& rhs )
    {
        assert( this != &rhs );
        assert( rhs.mTiles != NULL );

        // Destroy our current tile array, since we're getting rid of it
        // in the assignment
        boost::checked_array_delete( mTiles );

        // Initialize our fixed grid
        mWidth  = rhs.mWidth;
        mHeight = rhs.mHeight;
        mTiles  = new T[ mWidth * mHeight ];

        // Now copy all of the elements over
        std::copy( &rhs.mTiles[0],
                   &rhs.mTiles[mWidth * mHeight],
                   &mTiles[0] );
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
            boost::checked_array_delete( mTiles );

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
        assert( destBounds.contains( sourceBounds ) );

        // Now copy the tiles over
        for ( int sy = 0; sy < source.mHeight; ++sy )
        {
            for ( int sx = 0; sx < source.mWidth; ++sx )
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
    void clear( const T& base )
    {
        assert( mTiles != NULL );
        std::fill( &mTiles[0], &mTiles[mWidth*mHeight], base );
    }

    /**
     * Returns a reference to the value stored at the requested position
     *
     * \param  point  The fixed grid position to retrieve
     * \return A reference to the value stored at that position
     */
    T& get( const Point& point )
    {
        return get( point.x(), point.y() );
    }

    /**
     * Returns a reference to the value stored at the requested position.
     *
     * \param  x  The x offset to look up
     * \param  y  The y offset to look up
     * \return A const reference to the value at that position
     */
    T& get( int x, int y )
    {
        assert( x >= 0 && x < mWidth );
        assert( y >= 0 && y < mHeight );
        return mTiles[ offset( x, y ) ];
    }

    /**
     * Returns a const reference to the value stored at the requested
     * position.
     *
     * \param  point  The fixed grid position to retrieve
     * \return A const reference to the value at that position
     */
    const T& get( const Point& point ) const
    {
        return get( point.x(), point.y() );
    }

    const T& get( int x, int y ) const
    {
        assert( x >= 0 && x < mWidth  );
        assert( y >= 0 && y < mHeight );
        return mTiles[ offset( x, y ) ];
    }

    void set( const Point& point, const T& value )
    {
        set( point.x(), point.y(), value );
    }

    void set( int x, int y, const T& value )
    {
        assert( x >= 0 && x < mWidth );
        assert( y >= 0 && y < mHeight );
        mTiles[ offset( x, y ) ] = value;
    }

    int width() const
    {
        return mWidth;
    }

    int height() const
    {
        return mHeight;
    }

    size_t size() const
    {
        return mWidth * mHeight;
    }

protected:
    size_t offset( int x, int y ) const
    {
        assert( x >= 0 && x < mWidth );
        assert( y >= 0 && y < mHeight );
        return y * mWidth + x;
    }

    int mWidth;
    int mHeight;
    T * mTiles;
};

#endif
