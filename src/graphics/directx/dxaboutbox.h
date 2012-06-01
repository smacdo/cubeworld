/*
 * Copyright 2011 Scott MacDonald
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
#ifndef SCOTT_ABOUT_BOX_H
#define SCOTT_ABOUT_BOX_H

#include <boost/utility.hpp>
#include <Windows.h>

class Window;

/**
 * Its an about box! What more could you possibly want?
 */
class AboutBox : boost::noncopyable
{
public:
    AboutBox( HINSTANCE hInstance, HWND hWnd );
    ~AboutBox();

    void show();

private:
    HINSTANCE mAppInstance;
    HWND mParentWindow;
};

#endif