/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2008 Scientific Computing and Imaging Institute,
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
  \file    GLSBVR.cpp
  \author    Jens Krueger
        SCI Institute
        University of Utah
  \date    August 2008
*/


#include "GLSBVR.h"

#include <cmath>
#include <Basics/SysTools.h>
#include <Controller/MasterController.h>

using namespace std;

GLSBVR::GLSBVR(MasterController* pMasterController) :
  GLRenderer(pMasterController)
{
}

GLSBVR::~GLSBVR() {
}


bool GLSBVR::Initialize() {
  if (!GLRenderer::Initialize()) {
    m_pMasterController->DebugOut()->Error("GLSBVR::Initialize","Error in parent call -> aborting");
    return false;
  }

  glShadeModel(GL_SMOOTH);
  glDisable(GL_CULL_FACE);
  
  if (!LoadAndVerifyShader("Shaders/GPUSBVR-VS.glsl", "Shaders/GPUSBVR-1D-FS.glsl",       &(m_pProgram1DTrans[0])) ||
      !LoadAndVerifyShader("Shaders/GPUSBVR-VS.glsl", "Shaders/GPUSBVR-1D-light-FS.glsl", &(m_pProgram1DTrans[1])) ||
      !LoadAndVerifyShader("Shaders/GPUSBVR-VS.glsl", "Shaders/GPUSBVR-2D-FS.glsl",       &(m_pProgram2DTrans[0])) ||
      !LoadAndVerifyShader("Shaders/GPUSBVR-VS.glsl", "Shaders/GPUSBVR-2D-light-FS.glsl", &(m_pProgram2DTrans[1])) ||
      !LoadAndVerifyShader("Shaders/GPUSBVR-VS.glsl", "Shaders/GPUSBVR-ISO-FS.glsl",      &(m_pProgramIso))) {

      Cleanup();

      m_pMasterController->DebugOut()->Error("GLSBVR::Initialize","Error loading a shader.");
      return false;
  } else {
    m_pProgram1DTrans[0]->Enable();
    m_pProgram1DTrans[0]->SetUniformVector("texVolume",0);
    m_pProgram1DTrans[0]->SetUniformVector("texTrans1D",1);
    m_pProgram1DTrans[0]->Disable();

    m_pProgram1DTrans[1]->Enable();
    m_pProgram1DTrans[1]->SetUniformVector("texVolume",0);
    m_pProgram1DTrans[1]->SetUniformVector("texTrans1D",1);
    m_pProgram1DTrans[1]->SetUniformVector("vLightAmbient",0.2f,0.2f,0.2f);
    m_pProgram1DTrans[1]->SetUniformVector("vLightDiffuse",1.0f,1.0f,1.0f);
    m_pProgram1DTrans[1]->SetUniformVector("vLightSpecular",1.0f,1.0f,1.0f);
    m_pProgram1DTrans[1]->SetUniformVector("vLightDir",0.0f,0.0f,-1.0f);
    m_pProgram1DTrans[1]->Disable();

    m_pProgram2DTrans[0]->Enable();
    m_pProgram2DTrans[0]->SetUniformVector("texVolume",0);
    m_pProgram2DTrans[0]->SetUniformVector("texTrans2D",1);
    m_pProgram2DTrans[0]->Disable();

    m_pProgram2DTrans[1]->Enable();
    m_pProgram2DTrans[1]->SetUniformVector("texVolume",0);
    m_pProgram2DTrans[1]->SetUniformVector("texTrans2D",1);
    m_pProgram2DTrans[1]->SetUniformVector("vLightAmbient",0.2f,0.2f,0.2f);
    m_pProgram2DTrans[1]->SetUniformVector("vLightDiffuse",1.0f,1.0f,1.0f);
    m_pProgram2DTrans[1]->SetUniformVector("vLightSpecular",1.0f,1.0f,1.0f);
    m_pProgram2DTrans[1]->SetUniformVector("vLightDir",0.0f,0.0f,-1.0f);
    m_pProgram2DTrans[1]->Disable();

    m_pProgramIso->Enable();
    m_pProgramIso->SetUniformVector("texVolume",0);
    m_pProgramIso->SetUniformVector("vLightAmbient",0.2f,0.2f,0.2f);
    m_pProgramIso->SetUniformVector("vLightDiffuse",m_vIsoColor.x,m_vIsoColor.y,m_vIsoColor.z);
    m_pProgramIso->SetUniformVector("vLightSpecular",1.0f,1.0f,1.0f);
    m_pProgramIso->SetUniformVector("vLightDir",0.0f,0.0f,-1.0f);
    m_pProgramIso->Disable();
  }

  return true;
}

void GLSBVR::SetSampleRateModifier(float fSampleRateModifier) {
  GLRenderer::SetSampleRateModifier(fSampleRateModifier);
  m_SBVRGeogen.SetSamplingModifier(fSampleRateModifier);
}

void GLSBVR::SetBrickDepShaderVars(size_t iCurrentBrick) {
  const Brick& currentBrick = m_vCurrentBrickList[iCurrentBrick];
  FLOATVECTOR3 vStep(1.0f/currentBrick.vVoxelCount.x, 1.0f/currentBrick.vVoxelCount.y, 1.0f/currentBrick.vVoxelCount.z);

  float fStepScale = m_SBVRGeogen.GetOpacityCorrection();

  switch (m_eRenderMode) {
    case RM_1DTRANS    :  {                    
                            m_pProgram1DTrans[m_bUseLigthing ? 1 : 0]->SetUniformVector("fStepScale", fStepScale);
                            if (m_bUseLigthing)
                                m_pProgram1DTrans[1]->SetUniformVector("vVoxelStepsize", vStep.x, vStep.y, vStep.z);
                            break;
                          }
    case RM_2DTRANS    :  {
                            m_pProgram2DTrans[m_bUseLigthing ? 1 : 0]->SetUniformVector("fStepScale", fStepScale);
                            m_pProgram2DTrans[m_bUseLigthing ? 1 : 0]->SetUniformVector("vVoxelStepsize", vStep.x, vStep.y, vStep.z);
                            break;
                          }
    case RM_ISOSURFACE : {
                            m_pProgramIso->SetUniformVector("vVoxelStepsize", vStep.x, vStep.y, vStep.z);
                            break;
                          }
    case RM_INVALID    :  m_pMasterController->DebugOut()->Error("GLSBVR::SetBrickDepShaderVars","Invalid rendermode set"); break;
  }

}

const FLOATVECTOR2 GLSBVR::SetDataDepShaderVars() {
  const FLOATVECTOR2 vSizes = GLRenderer::SetDataDepShaderVars();

  switch (m_eRenderMode) {
    case RM_1DTRANS    :  {
                            m_pProgram1DTrans[m_bUseLigthing ? 1 : 0]->Enable();
                            m_pProgram1DTrans[m_bUseLigthing ? 1 : 0]->SetUniformVector("fTransScale",vSizes.x);
                            m_pProgram1DTrans[m_bUseLigthing ? 1 : 0]->Disable();
                            break;
                          }
    case RM_2DTRANS    :  {
                            m_pProgram2DTrans[m_bUseLigthing ? 1 : 0]->Enable();
                            m_pProgram2DTrans[m_bUseLigthing ? 1 : 0]->SetUniformVector("fTransScale",vSizes.x);
                            m_pProgram2DTrans[m_bUseLigthing ? 1 : 0]->SetUniformVector("fGradientScale",vSizes.y);
                            m_pProgram2DTrans[m_bUseLigthing ? 1 : 0]->Disable();
                            break;
                          }
    case RM_ISOSURFACE : {
                            m_pProgramIso->Enable();
                            m_pProgramIso->SetUniformVector("fIsoval",m_fIsovalue/vSizes.x);
                            m_pProgramIso->Disable();
                            break;
                          }
    case RM_INVALID    :  m_pMasterController->DebugOut()->Error("GLSBVR::SetDataDepShaderVars","Invalid rendermode set"); break;
  }


  return vSizes;
}


void GLSBVR::Render3DPreLoop() {
  switch (m_eRenderMode) {
    case RM_1DTRANS    :  m_p1DTransTex->Bind(1); 
                          m_pProgram1DTrans[m_bUseLigthing ? 1 : 0]->Enable();
                          glEnable(GL_BLEND);
                          glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE);
                          break;
    case RM_2DTRANS    :  m_p2DTransTex->Bind(1);
                          m_pProgram2DTrans[m_bUseLigthing ? 1 : 0]->Enable(); 
                          glEnable(GL_BLEND);
                          glBlendFunc(GL_ONE_MINUS_DST_ALPHA, GL_ONE);
                          break;
    case RM_ISOSURFACE :  m_pProgramIso->Enable(); 
                          m_pProgramIso->SetUniformVector("vLightDiffuse",m_vIsoColor.x,m_vIsoColor.y,m_vIsoColor.z);
                          break;
    default    :  m_pMasterController->DebugOut()->Error("GLSBVR::Render3DView","Invalid rendermode set"); 
                          break;
  }

  if (m_eRenderMode != RM_ISOSURFACE) glDepthMask(GL_FALSE);

  m_SBVRGeogen.SetLODData( UINTVECTOR3(m_pDataset->GetInfo()->GetDomainSize(m_iCurrentLOD))  );
}

void GLSBVR::Render3DInLoop(size_t iCurrentBrick) {
  // setup the slice generator
  m_SBVRGeogen.SetBrickData(m_vCurrentBrickList[iCurrentBrick].vExtension, m_vCurrentBrickList[iCurrentBrick].vVoxelCount, 
                            m_vCurrentBrickList[iCurrentBrick].vTexcoordsMin, m_vCurrentBrickList[iCurrentBrick].vTexcoordsMax);
  FLOATMATRIX4 maBricktTrans; 
  maBricktTrans.Translation(m_vCurrentBrickList[iCurrentBrick].vCenter.x, m_vCurrentBrickList[iCurrentBrick].vCenter.y, m_vCurrentBrickList[iCurrentBrick].vCenter.z);
  FLOATMATRIX4 maBricktModelView = maBricktTrans * m_matModelView;
  maBricktModelView.setModelview();
  m_SBVRGeogen.SetTransformation(maBricktModelView, true);

  // update the shader parameter
  SetBrickDepShaderVars(iCurrentBrick);

  // render the slices
  glBegin(GL_TRIANGLES);
    for (int i = int(m_SBVRGeogen.m_vSliceTriangles.size())-1;i>=0;i--) {
      glTexCoord3fv(m_SBVRGeogen.m_vSliceTriangles[i].m_vTex);
      glVertex3fv(m_SBVRGeogen.m_vSliceTriangles[i].m_vPos);
    }
  glEnd();
}


void GLSBVR::Render3DPostLoop() {
  // disable the shader
  switch (m_eRenderMode) {
    case RM_1DTRANS    :  m_pProgram1DTrans[m_bUseLigthing ? 1 : 0]->Disable(); break;
    case RM_2DTRANS    :  m_pProgram2DTrans[m_bUseLigthing ? 1 : 0]->Disable(); break;
    case RM_ISOSURFACE :  m_pProgramIso->Disable(); break;
    case RM_INVALID    :  m_pMasterController->DebugOut()->Error("GLSBVR::Render3DView","Invalid rendermode set"); break;
  }

  glDepthMask(GL_TRUE);
}


bool GLSBVR::LoadDataset(const string& strFilename) {
  if (GLRenderer::LoadDataset(strFilename)) {
    UINTVECTOR3    vSize = UINTVECTOR3(m_pDataset->GetInfo()->GetDomainSize());
    FLOATVECTOR3 vAspect = FLOATVECTOR3(m_pDataset->GetInfo()->GetScale());
    vAspect /= vAspect.maxVal();
    
    m_SBVRGeogen.SetVolumeData(vAspect, vSize);
    return true;
  } else return false;
}