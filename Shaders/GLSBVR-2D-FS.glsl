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
  \file    GLSBVR-2D-FS.glsl
  \author    Jens Krueger
        SCI Institute
        University of Utah
  \version  1.0
  \date    October 2008
*/

vec4 sampleVolume(vec3 coords);
vec3 ComputeGradient(vec3 vCenter, vec3 StepSize);

uniform sampler2D texTrans2D; ///< the 2D Transfer function
uniform float fTransScale;    ///< value scale for 2D Transfer function lookup
uniform float fGradientScale; ///< gradient scale for 2D Transfer function lookup
uniform float fStepScale;   ///< opacity correction quotient
uniform vec3 vVoxelStepsize;  ///< Stepsize (in texcoord) to get to the next voxel

void main(void)
{
  // get volume value
  float fVolumVal = sampleVolume( gl_TexCoord[0].xyz).x;	

  // compute the gradient
  vec3  vGradient = ComputeGradient(gl_TexCoord[0].xyz, vVoxelStepsize);
  float fGradientMag = length(vGradient);

  // apply 2D transfer function
  vec4  vTransVal = texture2D(texTrans2D, vec2(fVolumVal*fTransScale, 1.0-fGradientMag*fGradientScale));

  // apply opacity correction
  vTransVal.a = 1.0 - pow(1.0 - vTransVal.a, fStepScale);

  // pre-multiply color with alpha (for front to back)
  vTransVal.xyz *= vTransVal.a;

  // write result to fragment color
  gl_FragColor    = vTransVal;
}