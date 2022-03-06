/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#include "EffectExporter.h"

namespace TD_COLLADA_EXPORT
{
  EffectExporter::EffectExporter(COLLADASW::StreamWriter * streamWriter):COLLADASW::LibraryEffects ( streamWriter ) 
  {
    openLibrary();
  }

  EffectExporter::~EffectExporter()
  { 
    closeLibrary();
  }

  void EffectExporter::exportEffects(OdDbBaseDatabase* pDb, MaterialData* pMaterialData, COLLADASW::NativeString idStr)
  {
    //note: in acad channel flags can be false even if effects are present

    COLLADASW::NativeString strID("ID");
    COLLADASW::NativeString strEffect("-effect");

    openEffect((strID + idStr + strEffect).toString());
    COLLADASW::EffectProfile effectProfile(LibraryEffects::mSW);

    effectProfile.setShaderType(COLLADASW::EffectProfile::PHONG);

    if (pMaterialData->bAmbientChannelEnabled)
      effectProfile.setAmbient(pMaterialData->ambientColor);

    //diffuse
    //is always present in acad
    //if (pMaterialData->bDiffuseChannelEnabled)
    {
      if (pMaterialData->bDiffuseHasTexture)
      {
        COLLADASW::String imageId("ImageID" + idStr + "-diffuse");
        COLLADASW::Texture texture(imageId);
        texture.setTexcoord("UVSET0");

        // Create the sampler
        COLLADASW::String samplerSid = imageId + COLLADASW::Sampler::SAMPLER_SID_SUFFIX;
        COLLADASW::String surfaceSid = imageId + COLLADASW::Sampler::SURFACE_SID_SUFFIX;
        COLLADASW::Sampler sampler(COLLADASW::Sampler::SAMPLER_TYPE_2D, samplerSid, surfaceSid);
        sampler.setImageId(imageId);
        texture.setSampler(sampler);
        effectProfile.setDiffuse(COLLADASW::ColorOrTexture(texture));
      }
      else
      {
        effectProfile.setDiffuse(pMaterialData->diffuseColor);
      }
    }

    //specular
    if (pMaterialData->bSpecularChannelEnabled ||
      pMaterialData->bSpecularHasTexture || pMaterialData->dGlossFactor != 0.0)
    {
      if (pMaterialData->bSpecularHasTexture)
      {
        COLLADASW::String imageId("ImageID" + idStr + "-specular");
        COLLADASW::Texture texture(imageId);
        texture.setTexcoord("UVSET0");

        // Create the sampler
        COLLADASW::String samplerSid = imageId + COLLADASW::Sampler::SAMPLER_SID_SUFFIX;
        COLLADASW::String surfaceSid = imageId + COLLADASW::Sampler::SURFACE_SID_SUFFIX;
        COLLADASW::Sampler sampler(COLLADASW::Sampler::SAMPLER_TYPE_2D, samplerSid, surfaceSid);
        sampler.setImageId(imageId);
        texture.setSampler(sampler);
        effectProfile.setSpecular(COLLADASW::ColorOrTexture(texture));
      }
      else
      {
        effectProfile.setSpecular(pMaterialData->specularColor);
      }
      effectProfile.setShininess(pMaterialData->dGlossFactor);
    }

    //emission
    if (pMaterialData->bEmissionChannelEnabled ||
      pMaterialData->bEmissionHasTexture || pMaterialData->dEmissionPercentage != 0.0)
    {
      if (pMaterialData->bEmissionHasTexture)
      {
        COLLADASW::String imageId("ImageID" + idStr + "-emission");
        COLLADASW::Texture texture(imageId);
        texture.setTexcoord("UVSET0");

        // Create the sampler
        COLLADASW::String samplerSid = imageId + COLLADASW::Sampler::SAMPLER_SID_SUFFIX;
        COLLADASW::String surfaceSid = imageId + COLLADASW::Sampler::SURFACE_SID_SUFFIX;
        COLLADASW::Sampler sampler(COLLADASW::Sampler::SAMPLER_TYPE_2D, samplerSid, surfaceSid);
        sampler.setImageId(imageId);
        texture.setSampler(sampler);
        effectProfile.setEmission(COLLADASW::ColorOrTexture(texture));
      }
      else
      {
        effectProfile.setEmission(COLLADASW::Color(pMaterialData->diffuseColor.getRed() * pMaterialData->dEmissionPercentage,
                                                   pMaterialData->diffuseColor.getGreen() * pMaterialData->dEmissionPercentage,
                                                   pMaterialData->diffuseColor.getBlue() * pMaterialData->dEmissionPercentage,
                                                   pMaterialData->dEmissionPercentage));
      }
    }

    //transparency
    if (pMaterialData->bOpacityChannelEnabled ||
      pMaterialData->bOpacityHasTexture || pMaterialData->dOpacityPercentage != 1.0)
    {
      if (pMaterialData->bOpacityHasTexture)
      {
        COLLADASW::String imageId("ImageID" + idStr + "-opacity");
        COLLADASW::Texture texture(imageId);
        texture.setTexcoord("UVSET0");

        // Create the sampler
        COLLADASW::String samplerSid = imageId + COLLADASW::Sampler::SAMPLER_SID_SUFFIX;
        COLLADASW::String surfaceSid = imageId + COLLADASW::Sampler::SURFACE_SID_SUFFIX;
        COLLADASW::Sampler sampler(COLLADASW::Sampler::SAMPLER_TYPE_2D, samplerSid, surfaceSid);
        sampler.setImageId(imageId);
        texture.setSampler(sampler);
        effectProfile.setTransparent(COLLADASW::ColorOrTexture(texture));
      }
      effectProfile.setOpaque(COLLADASW::EffectProfile::A_ONE);
      effectProfile.setTransparency(pMaterialData->dOpacityPercentage);
    }

    //reflection
    if (pMaterialData->bReflectionChannelEnabled ||
      pMaterialData->bReflectionHasTexture || pMaterialData->dReflectionPercentage != 0.0)
    {
      if (pMaterialData->bReflectionHasTexture)
      {
        COLLADASW::String imageId("ImageID" + idStr + "-reflection");
        COLLADASW::Texture texture(imageId);
        texture.setTexcoord("UVSET0");

        // Create the sampler
        COLLADASW::String samplerSid = imageId + COLLADASW::Sampler::SAMPLER_SID_SUFFIX;
        COLLADASW::String surfaceSid = imageId + COLLADASW::Sampler::SURFACE_SID_SUFFIX;
        COLLADASW::Sampler sampler(COLLADASW::Sampler::SAMPLER_TYPE_2D, samplerSid, surfaceSid);
        sampler.setImageId(imageId);
        texture.setSampler(sampler);
        effectProfile.setReflective(COLLADASW::ColorOrTexture(texture));
      }
      effectProfile.setReflectivity(pMaterialData->dReflectionPercentage);
    }

    if (pMaterialData->bRefractionChannelEnabled ||
      pMaterialData->bReflectionHasTexture || pMaterialData->dRefractionIndex != 1.0)
    {
      //bRefractionHasTexture not supported in Collada
      effectProfile.setIndexOfRefraction(pMaterialData->dRefractionIndex);
    }

    /*
    //collada doesn't have bump??
    // Bump
    bool             bBumpChannelEnabled;
    double           dBumpPercentage;
    bool             bBumpHasTexture;
    OdString         sBumpFileSource;*/

    addEffectProfile(effectProfile);
    //addExtraTechniques(ElementWriter::mSW);
    closeEffect();
  }
}
