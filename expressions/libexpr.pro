TEMPLATE          = lib
win32:TEMPLATE    = vclib
CONFIG            = exceptions largefile rtti static staticlib stl
CONFIG           += warn_on
DEFINES          += YY_NO_UNPUT _FILE_OFFSET_BITS=64
TARGET            = tuvokexpr
DEPENDPATH       += . ../../Basics ../
INCLUDEPATH      += ../../ ../../Basics ../ ../3rdParty/boost
unix:QMAKE_CXXFLAGS += -fno-strict-aliasing
unix:QMAKE_CFLAGS += -fno-strict-aliasing

include(flex.pri)
include(bison.pri)

FLEXSOURCES = tvk-scan.lpp
BISONSOURCES = tvk-parse.ypp

SOURCES += \
  binary-expression.cpp \
  conditional-expression.cpp \
  constant.cpp          \
  treenode.cpp          \
  volume.cpp
