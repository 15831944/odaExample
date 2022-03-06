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
#include "ColladaMaterialCreator.h"
#include "DbDictionary.h"
#include "DbMaterial.h"
#include "DbEntity.h"
#include "DbSubDMesh.h"


namespace TD_COLLADA_IMPORT
{
  MaterialCreator::MaterialCreator(DocumentImporter* documentImporter)
    : ImporterBase(documentImporter)
  {
  }

  MaterialCreator::~MaterialCreator()
  {
  }

  bool MaterialCreator::create()
  {
    const DocumentImporter::EntityMaterialBindingsArray& materialBindings = getEntityMaterialBindings();
    bool bRes = true;

    for (unsigned int i = 0; i < materialBindings.size(); i++)
    {
      OdDbObjectId objId = materialBindings[i].objId;
      createMaterialResults res = createAndAssingMaterial(objId, materialBindings[i].materialBinding);
      if (res != errOk && res != errNoTexture)
      {
        bRes = false;
      }
    }
    return bRes;
  }

  MaterialCreator::createMaterialResults MaterialCreator::createAndAssingMaterial(OdDbObjectId objId, const COLLADAFW::MaterialBinding& materialBinding)
  {
    createMaterialResults crMatRes = errOk;
    OdDbDictionaryPtr pMatDic = this->getDocumentImporter()->getDatabase()->getMaterialDictionaryId().safeOpenObject(OdDb::kForWrite);

    const COLLADAFW::UniqueId& materialUniqueId = materialBinding.getReferencedMaterial();
    if (materialUniqueId.isValid())
    {
      const COLLADAFW::Material* pMaterial = getFWMaterialByUniqueId(materialUniqueId);
      if (pMaterial)
      {
        OdDbObjectId objIdMat = pMatDic->getAt(pMaterial->getName().c_str());
        const COLLADAFW::Effect* effect = getEffect(pMaterial);
        if (objIdMat.isNull())
        {
          if (!effect)
            return crMatRes;
          crMatRes = createTeighaMaterial(*effect, pMaterial->getName(), pMatDic, objIdMat);
        }
        if (!objId.isNull())
        {
          OdDbEntityPtr ent = objId.safeOpenObject(OdDb::kForWrite);
          if (eOk != ent->setMaterial(objIdMat))
          {
            crMatRes = errSetMatState;
          }
          else if (ent->isA() != OdDbSubDMesh::desc())
          {
            OdDbMaterialPtr dbMaterial = objIdMat.safeOpenObject(OdDb::kForWrite);
            OdGiMaterialColor color;
            OdGiMaterialMap map;
            dbMaterial->diffuse(color, map);
            OdCmColor cmColor;
            cmColor.setColor(color.color().color());
            if (eOk != ent->setColor(cmColor))
            {
              crMatRes = errSetMatState;
            }
          }
        }
      }
    }
    else
    {
      crMatRes = errUnknown;
    }
    return crMatRes;
  }

  const COLLADAFW::Effect* MaterialCreator::getEffect(const COLLADAFW::Material* pMaterial)
  {
    const COLLADAFW::UniqueId& effectUniqueId = pMaterial->getInstantiatedEffect();
    if (!effectUniqueId.isValid())
      return 0;

    return getFWEffectByUniqueId(effectUniqueId);
  }
  

  MaterialCreator::createMaterialResults MaterialCreator::setTexture(const COLLADAFW::EffectCommon& effectCommon, const COLLADAFW::Texture& texture, OdGiMaterialMap& materialMap)
  {
    createMaterialResults res = errOk;
    COLLADAFW::SamplerID samplerId = texture.getSamplerId();
    const COLLADAFW::Sampler* sampler = effectCommon.getSamplerPointerArray()[ samplerId ];

    const COLLADAFW::UniqueId& imageUniqueId = sampler->getSourceImage();
    const COLLADAFW::Image* image = getFWImageByUniqueId( imageUniqueId );
    if (image)
    {
      COLLADABU::URI imageUri(getFileInfo().absoluteFileUri, image->getImageURI().getURIString());
      OdString strImageFileName;
      try
      {
        COLLADABU::NativeString imageFileNameUTF8(imageUri.toNativePath().c_str(), COLLADABU::NativeString::ENCODING_UTF8);
        strImageFileName = imageFileNameUTF8.c_str();
      }
      catch (const COLLADABU::Exception& e)
      {
        if (e.getType() == COLLADABU::Exception::ERROR_UTF8_2_WIDE)
        {
          COLLADABU::NativeString imageFileNameNative(imageUri.toNativePath().c_str());
          strImageFileName = imageFileNameNative.c_str();
        }
        else
        {
          throw;
        }
      }
      //check if texture file exists; if not - use file name without path
      if (!odrxSystemServices()->accessFile(strImageFileName, Oda::kFileRead))
      {
        res = errNoTexture;
        strImageFileName.replace(L'/', L'\\');
        int iLatestSimbol = strImageFileName.reverseFind('\\') + 1;
        strImageFileName = strImageFileName.right(strImageFileName.getLength() - iLatestSimbol);
      }
      materialMap.setSourceFileName(strImageFileName);
      OdGiMapper mapper;
      mapper.setUTiling(OdGiMapper::kInheritTiling);
      mapper.setVTiling(OdGiMapper::kInheritTiling);
      materialMap.setMapper(mapper);
    }
    return res;
  }

  MaterialCreator::createMaterialResults MaterialCreator::createTeighaMaterial(const COLLADAFW::Effect& effect, const COLLADAFW::String& name,
    OdDbDictionaryPtr pMatDic, OdDbObjectId& objectId)
  {
    objectId = OdDbObjectId();
    createMaterialResults res = errOk;
    const COLLADAFW::CommonEffectPointerArray& commonEffects = effect.getCommonEffects();
    if (commonEffects.getCount() > 0)
    {
      const COLLADAFW::EffectCommon& effectCommon = *commonEffects[0];

      OdDbMaterialPtr pMaterial = OdDbMaterial::createObject();

      pMaterial->setName(name.c_str());    

      unsigned int channelFlags = OdGiMaterialTraits::kNone;

      OdGiMaterialMap materialMap;
      materialMap.setSource(OdGiMaterialMap::kFile);

      const COLLADAFW::ColorOrTexture& diffuse = effectCommon.getDiffuse();
      if (diffuse.isValid())
      {
        SETBIT_1(channelFlags, OdGiMaterialTraits::kUseDiffuse);
        OdGiMaterialColor diffuseColor;
        diffuseColor.setMethod(OdGiMaterialColor::kOverride);
        if (diffuse.isColor())
        {
          const COLLADAFW::Color& diffColor = diffuse.getColor();
          diffuseColor.color() = OdCmEntityColor((OdUInt8)(diffColor.getRed()*255.), (OdUInt8)(diffColor.getGreen()*255.), (OdUInt8)(diffColor.getBlue()*255.));
          pMaterial->setDiffuse(diffuseColor, materialMap);
        }
        else
        {
          OdGiMaterialMap diffuseMap(materialMap);
          if (setTexture(effectCommon, diffuse.getTexture(), diffuseMap) != errOk)
          {
            res = errNoTexture;
          }
          OdString sTextureFName = diffuseMap.sourceFileName();
          pMaterial->setDiffuse(diffuseColor, diffuseMap);
        }
      }

      const COLLADAFW::ColorOrTexture& ambient = effectCommon.getAmbient();
      if (ambient.isValid())
      {
        if (ambient.isColor())
        {
          const COLLADAFW::Color& ambColor = ambient.getColor();
          OdGiMaterialColor ambientColor;
          ambientColor.setMethod(OdGiMaterialColor::kOverride);
          ambientColor.color() = OdCmEntityColor((OdUInt8)(ambColor.getRed()*255.), (OdUInt8)(ambColor.getGreen()*255.), (OdUInt8)(ambColor.getBlue()*255.));
          pMaterial->setAmbient(ambientColor);
          if (!diffuse.isValid())
          {
            //Diffuse color is used even if kUseDiffuse is not set (e.g., ColladaImportTest_11458_IS, run = 1)
            pMaterial->setDiffuse(ambientColor, materialMap);
          }
        }
        else
        {
          //Ambient map is not supported in DbMaterial
        }
      }

      const COLLADAFW::ColorOrTexture& specular = effectCommon.getSpecular();
      if (specular.isValid())
      {
        SETBIT_1(channelFlags, OdGiMaterialTraits::kUseSpecular);
        const COLLADAFW::FloatOrParam& shininessFloatOrParam = effectCommon.getShininess();
        double dGlossFactor = 1.0;
        if (shininessFloatOrParam.getType() == COLLADAFW::FloatOrParam::FLOAT)
        {
          dGlossFactor = shininessFloatOrParam.getFloatValue();
          if (dGlossFactor == -1.0)
          {
            dGlossFactor = 0.5;
          }
        }
        OdGiMaterialColor specularColor;
        specularColor.setMethod(OdGiMaterialColor::kOverride);
        if (specular.isColor())
        {
          const COLLADAFW::Color& specColor = specular.getColor();
          specularColor.color() = OdCmEntityColor((OdUInt8)(specColor.getRed()*255.), (OdUInt8)(specColor.getGreen()*255.), (OdUInt8)(specColor.getBlue()*255.));
          pMaterial->setSpecular(specularColor, materialMap, dGlossFactor);
        }
        else
        {
          OdGiMaterialMap specularMap(materialMap);
          if (setTexture(effectCommon, specular.getTexture(), specularMap) != errOk)
          {
            res = errNoTexture;
          }
          OdString sTextureFName = specularMap.sourceFileName();
          pMaterial->setSpecular(specularColor, specularMap, dGlossFactor);
        }
      }

      const COLLADAFW::ColorOrTexture& emission = effectCommon.getEmission();
      if (emission.isValid())
      {
        SETBIT_1(channelFlags, OdGiMaterialTraits::kUseEmission);
        if (emission.isColor())
        {
          const COLLADAFW::Color& emColor = emission.getColor();
          pMaterial->setSelfIllumination(emColor.getAlpha());
        }
        else
        {
          //emission map is not supported in DbMaterial
        }
      }

      //transparency
      const COLLADAFW::ColorOrTexture& opacity = effectCommon.getOpacity();
      if (opacity.isValid())
      {
        double dAverageOpacity = 1.0;
        if (opacity.isColor())
        {
          const COLLADAFW::Color& opacityColor = opacity.getColor();
          dAverageOpacity = (opacityColor.getRed() + opacityColor.getGreen() + opacityColor.getBlue()) / 3;
          if (dAverageOpacity != 1.0)
          {
            SETBIT_1(channelFlags, OdGiMaterialTraits::kUseOpacity);
            pMaterial->setOpacity(dAverageOpacity, materialMap);
          }
        }
        else
        {
          SETBIT_1(channelFlags, OdGiMaterialTraits::kUseOpacity);
          OdGiMaterialMap opacityMap(materialMap);
          if (setTexture(effectCommon, opacity.getTexture(), opacityMap) != errOk)
          {
            res = errNoTexture;
          }
          OdString sTextureFName = opacityMap.sourceFileName();
          pMaterial->setOpacity(dAverageOpacity, opacityMap);
        }
      }

      const COLLADAFW::FloatOrParam& reflectivity = effectCommon.getReflectivity();
      const COLLADAFW::ColorOrTexture& reflection = effectCommon.getReflective();
      double dReflectivity = -1.0;
      reflectivity.getFloatValue();
      if (reflectivity.getType() == COLLADAFW::FloatOrParam::FLOAT)
      {
        dReflectivity = reflectivity.getFloatValue();
      }
      if (dReflectivity != -1.0 || reflection.isValid())
      {
        SETBIT_1(channelFlags, OdGiMaterialTraits::kUseReflection);
        if (dReflectivity == -1.0)
        {
          dReflectivity = 1.0;
        }
        if (reflection.isColor())
        {
          const COLLADAFW::Color& reflectionColor = reflection.getColor();
          dReflectivity *= (reflectionColor.getRed() + reflectionColor.getGreen() + reflectionColor.getBlue()) / 3;
        }
        else if (reflection.isTexture())
        {
          OdGiMaterialMap reflectionMap(materialMap);
          if (setTexture(effectCommon, reflection.getTexture(), reflectionMap) != errOk)
          {
            res = errNoTexture;
          }
          OdString sTextureFName = reflectionMap.sourceFileName();
          pMaterial->setReflection(reflectionMap);
        }
        pMaterial->setReflectivity(dReflectivity);
      }

      const COLLADAFW::FloatOrParam& indexOfRefraction = effectCommon.getIndexOfRefraction();
      double dIndexOfRefraction = -1.0;
      if (indexOfRefraction.getType() == COLLADAFW::FloatOrParam::FLOAT)
      {
        dIndexOfRefraction = indexOfRefraction.getFloatValue();
      }
      if (dIndexOfRefraction != -1.0)
      {
        SETBIT_1(channelFlags, OdGiMaterialTraits::kUseRefraction);
        //refraction map is not supported in Collada
        pMaterial->setRefraction(dIndexOfRefraction, materialMap);
      }

      //bump is not supported in Collada

      pMaterial->setChannelFlags(OdGiMaterialTraits::ChannelFlags(channelFlags));
      objectId = pMatDic->setAt(name.c_str(), pMaterial);
    }
    return res;
	}
}
