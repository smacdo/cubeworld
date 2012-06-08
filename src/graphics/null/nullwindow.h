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
#ifndef SCOTT_CUBEWORLD_NULL_WINDOW_H
#define SCOTT_CUBEWORLD_NULL_WINDOW_H

#include "graphics/iwindow.h"

class NullWindow : public IWindow
{
public:
    NullWindow();
    ~NullWindow();

    virtual void create();
    virtual void show();
    virtual void exit();
    
    virtual bool processMessages();

};

#endif
