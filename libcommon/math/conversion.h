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
#ifndef SCOTT_MATH_CONVERSION_H
#define SCOTT_MATH_CONVERSION_H

#include <math/constants.h>

namespace Math
{
    /**
     * Convert degrees to radians
     *
     * \param  deg  Degrees input
     * \return      Radians output
     */
    template<typename T>
    inline T deg2rad( T deg )
    {
        return static_cast<T>(Pi) / static_cast<T>(180.0) * deg;
    }

    /**
     * Convert radians to degrees
     *
     * \param  rad  Radians input
     * \return      Degrees output
     */
    template<typename T>
    inline T rad2deg( T rad )
    {
        return static_cast<T>(180.0) / static_cast<T>(Pi) * rad;
    }
}

#endif
