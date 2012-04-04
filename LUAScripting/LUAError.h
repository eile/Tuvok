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
  \file    LUAError.h
  \author  James Hughes
           SCI Institute
           University of Utah
  \date    Mar 21, 2012
  \brief   Defines exceptions thrown in the LUA scripting system.
*/

#ifndef TUVOK_LUAERROR_H_
#define TUVOK_LUAERROR_H_

#include "TuvokException.h"

namespace tuvok
{

/// Generic LUA error.
class LuaError : virtual public tuvok::Exception
{
public:

  explicit LuaError(const char* e, const char* where = NULL, size_t ln = 0)
    : tuvok::Exception(e, where, ln)
  {}
  virtual ~LuaError() throw() { }

};

/// Errors dealing with the LUA-Based function registration system.
class LuaFunBindError : virtual public LuaError
{
public:
  explicit LuaFunBindError(const char* e, const char* where = NULL,
                           size_t ln = 0)
    : LuaError(e, where, ln)
  {}
  virtual ~LuaFunBindError() throw() { }
};

class LuaNonExistantFunction : virtual public LuaError
{
public:
  explicit LuaNonExistantFunction(const char* e, const char* where = NULL,
                                  size_t ln = 0)
    : LuaError(e, where, ln)
  {}
  virtual ~LuaNonExistantFunction() throw() { }
};

class LuaInvalidFunSignature : virtual public LuaError
{
public:
  explicit LuaInvalidFunSignature(const char* e, const char* where = NULL,
                                  size_t ln = 0)
    : LuaError(e, where, ln)
  {}
  virtual ~LuaInvalidFunSignature() throw() { }
};

class LuaProvenanceReenter : virtual public LuaError
{
public:
  explicit LuaProvenanceReenter(const char* e, const char* where = NULL,
                                  size_t ln = 0)
    : LuaError(e, where, ln)
  {}
  virtual ~LuaProvenanceReenter() throw() { }
};

class LuaProvenanceInvalidRedo : virtual public LuaError
{
public:
  explicit LuaProvenanceInvalidRedo(const char* e, const char* where = NULL,
                                  size_t ln = 0)
    : LuaError(e, where, ln)
  {}
  virtual ~LuaProvenanceInvalidRedo() throw() { }
};

class LuaProvenanceInvalidUndo : virtual public LuaError
{
public:
  explicit LuaProvenanceInvalidUndo(const char* e, const char* where = NULL,
                                  size_t ln = 0)
    : LuaError(e, where, ln)
  {}
  virtual ~LuaProvenanceInvalidUndo() throw() { }
};

} /* namespace tuvok */

#endif /* LUAERROR_H_ */
