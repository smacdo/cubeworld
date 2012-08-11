/*
 * Copyright 2010-2012 Scott MacDonald
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef SCOTT_GAME2D_RECT_H
#define SCOTT_GAME2D_RECT_H

#include <game2d/point.h>

/**
 * 2D axis align rectangle that uses non-negative integer coordinates
 * to define it's position.
 */
class Rect
{
public:
    Rect( const Point& topLeft, const Point& rectSize )
        : mTopLeft( topLeft ),
          mSize( rectSize )
    {
    }

    Rect( const Point& topLeft, unsigned int width, unsigned int height )
        : mTopLeft( topLeft ),
          mSize( width, height )
    {
    }

    Rect( unsigned int topX,
          unsigned int topY,
          unsigned int width,
          unsigned int height )
        : mTopLeft( topX, topY ),
          mSize( width, height )
    {
    }

    Rect( const Rect& rect )
        : mTopLeft( rect.mTopLeft ),
          mSize( rect.mSize )
    {
    }

    Rect& operator = ( const Rect& rect )
    {
        mTopLeft = rect.mTopLeft;
        mSize    = rect.mSize;

        return *this;
    }

    bool operator == ( const Rect& rect ) const
    {
        return ( mTopLeft == rect.mTopLeft && mSize == rect.mSize );
    }

    bool operator != ( const Rect& rect ) const
    {
        return !( mTopLeft == rect.mTopLeft && mSize == rect.mSize ); 
    }

    Point position() const
    {
        return mTopLeft;
    }

    Point topLeft() const
    {
        return mTopLeft;
    }

    Point topRight() const
    {
        return Point( mTopLeft.x() + mSize.x(), mTopLeft.y() );
    }

    Point bottomLeft() const
    {
        return Point( mTopLeft.x(), mTopLeft.y() + mSize.y() );
    }
    
    Point bottomRight() const
    {
        return mTopLeft + mSize;
    }

    Point center() const
    {
        return Point( ( mTopLeft.x() + mSize.x() ) / 2,
                      ( mTopLeft.y() + mSize.y() ) / 2 );
    }

    Point size() const
    {
        return mSize;
    }

    unsigned int top() const
    {
        return mTopLeft.y();
    }

    unsigned int left() const
    {
        return mTopLeft.x();
    }

    unsigned int right() const
    {
        return mTopLeft.x() + mSize.x();
    }

    unsigned int bottom() const
    {
        return mTopLeft.y() + mSize.y();
    }

    unsigned int width() const
    {
        return mSize.x();
    }

    unsigned int height() const
    {
        return mSize.y();
    }

    void move( const Point& delta )
    {
        mTopLeft += delta;
    }

    void moveTo( const Point& position )
    {
        mTopLeft = position;
    }

    void adjustSize( const Point& newSize )
    {
        mSize += newSize;
    }

    void resize( const Point& newSize )
    {
        mSize = newSize;
    }

    bool contains( const Point& point ) const
    {
        Point pt = point - mTopLeft;

        return ( pt.x() >= 0.0f && pt.x() <= mSize.x() &&
                 pt.y() >= 0.0f && pt.y() <= mSize.y() );
    }

    bool contains( const Rect& /*rect*/ ) const
    {
        return false;
    }

    bool intersects( const Rect& /*rect*/ ) const
    {
        return false;
    }

private:
    Point mTopLeft;
    Point mSize;
};

#endif

