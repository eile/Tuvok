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
  \brief   
*/


#ifndef EXTERNAL_UNIT_TESTING

#include "Controller/Controller.h"
#include "3rdParty/LUA/lua.hpp"

#else

#include <assert.h>
#include "utestCommon.h"

#endif

#include <vector>

#include "LUAScripting.h"
#include "LUAClassInstance.h"

using namespace std;

namespace tuvok
{

const char* LuaClassInstance::MD_GLOBAL_INSTANCE_ID = "globalID";
const char* LuaClassInstance::MD_FACTORY_NAME       = "factoryName";
const char* LuaClassInstance::MD_INSTANCE           = "instance";
const char* LuaClassInstance::MD_DEL_FUN            = "delFun";

const char* LuaClassInstance::SYSTEM_TABLE          = "_sys_";
const char* LuaClassInstance::CLASS_INSTANCE_TABLE  = "_sys_.inst";
const char* LuaClassInstance::CLASS_INSTANCE_PREFIX = "m";

LuaClassInstance::LuaClassInstance(int instanceID)
: mInstanceID(instanceID)
{

}

//{return mFullyQualifiedName;}
std::string LuaClassInstance::fqName() const
{
  std::ostringstream os;
  os << LuaClassInstance::CLASS_INSTANCE_TABLE << "."
     << LuaClassInstance::CLASS_INSTANCE_PREFIX << mInstanceID;
  return os.str();
}

lua_State* LuaClassInstance::internalGetLuaState(
    tr1::shared_ptr<LuaScripting> ss)
{
  return ss->getLUAState();
}

bool LuaClassInstance::isDefaultInstance() const
{
  return (mInstanceID == DEFAULT_INSTANCE_ID);
}

}

