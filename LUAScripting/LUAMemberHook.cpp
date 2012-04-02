/*
 For more information, please see: http://software.sci.utah.edu

 The MIT License

 Copyright (c) 2012 Scientific Computing and Imaging Institute,
 University of Utah.


 Permission is hereby granted, free of charge, to any person obtaining a
 copy of this software and associated documentation files (the "Software"),
 to deal in the Software without restriction, including without limitation
 the rights to use, copy, modify, merge, publish, distribute, sublicense,
 and/or sell copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included
 in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 DEALINGS IN THE SOFTWARE.
 */

/**
 \file    LUAMemberHook.cpp
 \author  James Hughes
          SCI Institute
          University of Utah
 \date    Mar 26, 2012
 \brief   A mechanism to hook into the Scripting System using member functions.
          Used for updating the UI when actions, such as undo/redo, are
          executed.
          Instantiate this class alongside your encapsulating class.
 */

#ifndef EXTERNAL_UNIT_TESTING

#include "Controller/Controller.h"
#include "3rdParty/LUA/lua.hpp"

#else

#include "assert.h"
#include "utestCommon.h"

#endif

#include <vector>

#include "LUAError.h"
#include "LUAFunBinding.h"
#include "LUAScripting.h"
#include "LUAMemberHook.h"

using namespace std;

namespace tuvok
{


LUAMemberHook::LUAMemberHook(tr1::shared_ptr<LUAScripting> scriptSys)
: mScriptSystem(scriptSys)
{

}

LUAMemberHook::~LUAMemberHook()
{

}

}
