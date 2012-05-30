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
#ifndef SCOTT_MATH_CONSTANTS_H
#define SCOTT_MATH_CONSTANTS_H

#include <math/config.h>

///////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////
namespace Math
{
    // Zero delta
    const float  ZeroEpsilonF = 1e-5f;
    const double ZeroEpsilonD = 1e-9;

    // Pi
    const Scalar Pi     = 3.141592653589793238462f;
    const Scalar TwoPi  = 6.283185307179586476925286766559f;
    const Scalar HalfPi = 1.570796326794896619231321691639f;

    // e constant
    const Scalar E      = 2.71828182845904523536f;
    const Scalar Log10E = 0.4342944819032518f;
    const Scalar Log2E  = 1.4426950408889633f;

    // sqrt
    const Scalar SqrtTwo      = 1.41421356237309504880f;
    const Scalar SqrtThree    = 1.73205080756887729352f;
    const Scalar SqrtOneHalf  = 0.70710678118654752440f;
    const Scalar SqrtOneThird = 0.57735026918962576450f;

    // deg and radian conversions
    const Scalar Deg2Rad = Pi / 180.0f;
    const Scalar Rad2Deg = 180.0f / Pi;

    // Time conversions
    const Scalar SecToMillisec = 1000.0f;
    const Scalar MillisecToSec = 0.001f;
}

#endif
