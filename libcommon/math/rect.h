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
#ifndef SCOTT_MATH_RECT_H
#define SCOTT_MATH_RECT_H

#include <math/vector.h>

/**
 * 2d axis aligned rectangle.
 */
class RectF
{
public:
    RectF( const Vec2& topLeft, const Vec2& rectSize )
        : mTopLeft( topLeft ),
          mSize( rectSize )
    {
        math_assert( mSize.x() > 0.0f && mSize.y() > 0.0f );
    }

    RectF( float topX, float topY, float width, float height )
        : mTopLeft( topX, topY ),
          mSize( width, height )
    {
        math_assert( width > 0.0f && height > 0.0f );
    }

    RectF( const RectF& rect )
        : mTopLeft( rect.mTopLeft ),
          mSize( rect.mSize )
    {
    }

    RectF& operator = ( const RectF& rect )
    {
        mTopLeft = rect.mTopLeft;
        mSize    = rect.mSize;

        return *this;
    }

    bool operator == ( const RectF& rect ) const
    {
        return ( mTopLeft == rect.mTopLeft && mSize == rect.mSize );
    }

    bool operator != ( const RectF& rect ) const
    {
        return !( mTopLeft == rect.mTopLeft && mSize == rect.mSize ); 
    }

    Vec2 position() const
    {
        return mTopLeft;
    }

    Vec2 topLeft() const
    {
        return mTopLeft;
    }

    Vec2 topRight() const
    {
        return Vec2( mTopLeft.x() + mSize.x(), mTopLeft.y() );
    }

    Vec2 bottomLeft() const
    {
        return Vec2( mTopLeft.x(), mTopLeft.y() + mSize.y() );
    }
    
    Vec2 bottomRight() const
    {
        return mTopLeft + mSize;
    }

    Vec2 center() const
    {
        return ( mTopLeft + mSize ) / 2.0f;
    }

    Vec2 size() const
    {
        return mSize;
    }

    float top() const
    {
        return mTopLeft.y();
    }

    float left() const
    {
        return mTopLeft.x();
    }

    float right() const
    {
        return mTopLeft.x() + mSize.x();
    }

    float bottom() const
    {
        return mTopLeft.y() + mSize.y();
    }

    float width() const
    {
        return mSize.x();
    }

    float height() const
    {
        return mSize.y();
    }

    void move( const Vec2& delta )
    {
        mTopLeft += delta;
    }

    void moveTo( const Vec2& position )
    {
        mTopLeft = position;
    }

    void adjustSize( const Vec2& newSize )
    {
        mSize += newSize;
        math_assert( mSize.x() > 0.0f && mSize.y() > 0.0f );
    }

    void resize( const Vec2& newSize )
    {
        math_assert( newSize.x() > 0.0f && newSize.y() > 0.0f );
        mSize = newSize;
    }

    void resize( float width, float height )
    {
        resize( Vec2( width, height ) );
    }

    bool contains( const Vec2& point ) const
    {
        Vec2 pt = point - mTopLeft;

        return ( pt.x() >= 0.0f && pt.x() <= mSize.x() &&
                 pt.y() >= 0.0f && pt.y() <= mSize.y() );
    }

    bool contains( const RectF& /*rect*/ ) const
    {
        return false;
    }

    bool intersects( const RectF& /*rect*/ ) const
    {
        return false;
    }

private:
    Vec2 mTopLeft;
    Vec2 mSize;
};

#endif

