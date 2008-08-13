######################################################################
# Generated by Jens Krueger
######################################################################

TEMPLATE          = app
unix:TARGET       = Build/Linux/Bin/ImageVis3D
win32:TARGET      = Build/Win32/Bin/ImageVis3D
mac:TARGET        = Build/OSX/Bin/ImageVis3D
unix:RCC_DIR      = Build/Linux
win32:RCC_DIR     = Build/Win32
mac:RCC_DIR       = Build/OSX
unix:OBJECTS_DIR  = Build/Linux
win32:OBJECTS_DIR = Build/Win32
mac:OBJECTS_DIR   = Build/OSX
UI_DIR            = UI/AutoGen
MOC_DIR           = UI/AutoGen
DEPENDPATH       += .
INCLUDEPATH      += .
QT               += opengl

# Input
HEADERS += Basics/Grids.h \
           Basics/SysTools.h \
           Basics/Vectors.h \
           UI/BrowseData.h \
           UI/ImageVis3D.h \
           UI/PleaseWait.h \
           UI/Q1DTransferFunction.h \
           UI/Q2DTransferFunction.h \
           UI/QDataRadioButton.h \
           UI/RenderWindow.h \
           IO/Transferfunction1D.h \
           IO/Transferfunction2D.h \
           IO/VolumeDataset.h \
           IO/Images/BMPLoader.h \
           Controller/MasterController.h \
           DebugOut/AbstrDebugOut.h \
           DebugOut/QTOut.h \
           DebugOut/ConsoleOut.h \
           Renderer/GLInclude.h \
           Renderer/GLTexture.h \
           Renderer/GLTexture1D.h \
           Renderer/GLTexture2D.h \
           Renderer/AbstrRenderer.h \
           Renderer/GPUSBVR.h \
           Renderer/GPUMemMan/GPUMemMan.h


FORMS += UI/UI/BrowseData.ui UI/UI/ImageVis3D.ui UI/UI/PleaseWait.ui

SOURCES += Basics/SysTools.cpp \
           UI/BrowseData.cpp \
           UI/ImageVis3D.cpp \
           UI/PleaseWait.cpp \
           UI/Q1DTransferFunction.cpp \
           UI/Q2DTransferFunction.cpp \
           UI/QDataRadioButton.cpp \
           UI/RenderWindow.cpp \
           IO/Transferfunction1D.cpp \
           IO/Transferfunction2D.cpp \
           IO/VolumeDataset.cpp \
           IO/DICOM/DICOMParser.cpp \
           Controller/MasterController.cpp \
           DebugOut/QTOut.cpp \
           DebugOut/ConsoleOut.cpp \
           Renderer/GLTexture.cpp \
           Renderer/GLTexture1D.cpp \
           Renderer/GLTexture2D.cpp \
           Renderer/AbstrRenderer.cpp \
           Renderer/GPUSBVR.cpp \
           Renderer/GPUMemMan/GPUMemMan.cpp \
           main.cpp
