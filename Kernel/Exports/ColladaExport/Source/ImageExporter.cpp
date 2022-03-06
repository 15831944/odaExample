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

#include "ImageExporter.h"
#include "DbBaseHostAppServices.h"

namespace TD_COLLADA_EXPORT
{
  ImageExporter::ImageExporter(COLLADASW::StreamWriter * streamWriter):COLLADASW::LibraryImages ( streamWriter ) 
  {
  }

  ImageExporter::~ImageExporter()
  { 
  }

  void ImageExporter::exportImage(const OdString& pSourceFileName, const OdString& pFileName, const COLLADASW::NativeString& pImageId,
    OdDbBaseHostAppServices* pHostApp, OdDbBaseDatabase* pDb)
  {
    /*3DMax way
    COLLADASW::NativeString sFileName(diffuseMap.sourceFileName().c_str());
    COLLADABU::String imageStr = COLLADASW::URI::nativePathToUri(sFileName);
    COLLADABU::String str3DMaxPrefix("file:/");
    addImage ( COLLADASW::Image ( str3DMaxPrefix + imageStr, "ImageID" + idStr, "ImageID" + idStr ) );*/

    OdString sFileSource(pSourceFileName);
    sFileSource.replace(L'/', L'\\');
    int iLatestSimbol = sFileSource.reverseFind('\\') + 1;
    OdString sFileName(sFileSource.right(sFileSource.getLength() - iLatestSimbol));
    {
      OdString sTmpFileName(pFileName);
      sTmpFileName.replace(L'/', L'\\');
      OdString sFilePath(sTmpFileName.left(sTmpFileName.reverseFind('\\') + 1));

      if (sFileSource != sFilePath + sFileName)
      {
        OdString sFoundFileName;
        if (pHostApp)
          sFoundFileName = pHostApp->findFile(sFileSource, pDb);
        else if (odrxSystemServices()->accessFile(sFileSource, Oda::kFileRead))
          sFoundFileName = sFileSource;
        else if (sFileSource.getLength() > sFileName.getLength() && odrxSystemServices()->accessFile(sFileName, Oda::kFileRead))
          sFoundFileName = sFileName;
        if (!sFoundFileName.isEmpty())
        {
          OdStreamBufPtr fIn = odrxSystemServices()->createFile(sFoundFileName);
          OdStreamBufPtr fOut = odrxSystemServices()->createFile(sFilePath + sFileName, Oda::kFileWrite, Oda::kShareDenyNo, Oda::kCreateAlways);
          fIn->copyDataTo(fOut);
        }
      }
    }
    COLLADASW::NativeString snFileName(sFileName.c_str());
    addImage(COLLADASW::Image(COLLADASW::URI::nativePathToUri(snFileName.toString()), "ImageID" + pImageId, "ImageID" + pImageId));
  }

  void ImageExporter::exportImages(OdArray<MaterialData>& pMatTraitsDataArr, const OdString& pFileName, OdDbBaseHostAppServices* pHostApp, OdDbBaseDatabase* pDb)
  {
    //effect numbers 1,2...
    OdString buffer;
    OdUInt32 intDataSize = pMatTraitsDataArr.size();
    {
      for (OdUInt32 i = 0; i < intDataSize; ++i)
      {
        buffer.format(OD_T("%i"), i + 1); 
        COLLADASW::NativeString idStr(buffer.c_str());
        if (pMatTraitsDataArr[i].bDiffuseHasTexture)
        {
          COLLADASW::NativeString idStrDiffuse(idStr + "-diffuse");
          exportImage(pMatTraitsDataArr[i].sDiffuseFileSource, pFileName, idStrDiffuse, pHostApp, pDb);
        }
        if (pMatTraitsDataArr[i].bSpecularHasTexture)
        {
          COLLADASW::NativeString idStrSpecular(idStr + "-specular");
          exportImage(pMatTraitsDataArr[i].sSpecularFileSource, pFileName, idStrSpecular, pHostApp, pDb);
        }
        if (pMatTraitsDataArr[i].bEmissionHasTexture)
        {
          COLLADASW::NativeString idStrEmission(idStr + "-emission");
          exportImage(pMatTraitsDataArr[i].sEmissionFileSource, pFileName, idStrEmission, pHostApp, pDb);
        }
        if (pMatTraitsDataArr[i].bOpacityHasTexture)
        {
          COLLADASW::NativeString idStrOpacity(idStr + "-opacity");
          exportImage(pMatTraitsDataArr[i].sOpacityFileSource, pFileName, idStrOpacity, pHostApp, pDb);
        }
        if (pMatTraitsDataArr[i].bReflectionHasTexture)
        {
          COLLADASW::NativeString idStrReflection(idStr + "-reflection");
          exportImage(pMatTraitsDataArr[i].sReflectionFileSource, pFileName, idStrReflection, pHostApp, pDb);
        }
        if (pMatTraitsDataArr[i].bRefractionHasTexture)
        {
          COLLADASW::NativeString idStrRefraction(idStr + "-refraction");
          exportImage(pMatTraitsDataArr[i].sRefractionFileSource, pFileName, idStrRefraction, pHostApp, pDb);
        }
        //not supported in Collada
        /*if (pMatTraitsDataArr[i].bBumpHasTexture)
        {
          COLLADASW::NativeString idStrBump(idStr + "-bump");
          exportImage(pMatTraitsDataArr[i].sBumpFileSource, pFileName, idStrBump);
        }*/
      }
    }
    closeLibrary();
  }
}
