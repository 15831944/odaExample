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
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Teigha.Core;
using Teigha.TD;
using Teigha.PRC;
using Teigha.Publish;

namespace OdPrcAnimationCreateExSwigMgd
{
  class Program
  {
    static Program()
    {
      OdCreationNetSwigExampleLib.Helpers.OdNetSmokeTest.Use();
    }

    class SystemServices : RxSystemServicesImpl
    {
      public SystemServices()
      {
        Teigha.Core.Globals.odActivate(ActivationData.userInfo, ActivationData.userSignature);
      }
    }

    static OdRxObject odCreatePrcAllInSingleViewContextForTD()
    {
      OdRxObject pObj = null;
      OdRxClass pClass = OdRxClass.cast(Globals.odrxClassDictionary().getAt("OdPrcContextForPdfExport_AllInSingleView"));
      if (pClass != null)
      {
        pObj = pClass.create();
      }
      return OdRxObject.cast(pObj);
    }

    static void Main(string[] args)
    {
      if (args.Count() < 2)
      {
        Console.WriteLine("Invalid input args!");
        Console.WriteLine("Example usage: OdPrcAnimationCreateExSwigMgd.exe \"Input_PRC_FilePath\" \"Out_PDF_FilePath\" ");
        Console.ReadLine();
        return;
      }

      String in_prcPath = args[0];
      String out_pdfPath = args[1];

      if (!System.IO.File.Exists(in_prcPath))
      {
        Console.WriteLine("Invalid input args!");
        Console.WriteLine("PRC Path not exist: {0}", in_prcPath);
        Console.ReadLine();
        return;
      }

      MemoryManager mMan = MemoryManager.GetMemoryManager();
      MemoryTransaction mStartTrans = mMan.StartTransaction();

      SystemServices Serv = new SystemServices();
      ExHostAppServices hostApp = new ExHostAppServices();
      OdPrcHostAppServices prcHostApp = new OdPrcHostAppServices();
      Console.WriteLine("OdPrcAnimationCreateExSwigMgd developed using {0} ver {1}",
          hostApp.product(), hostApp.versionString());
      TD_Db.odInitialize(Serv);

      Console.WriteLine("Load OdPrcModule");
      Globals.odrxDynamicLinker().loadApp("OdPrcModule", false);
      Globals.odrxDynamicLinker().loadApp("PdfPublish", false);
      try
      {

        OdRxModule pRasSvcs = Globals.odrxDynamicLinker().loadApp("RxRasterServices");
        if (pRasSvcs == null)
          throw new OdError(OdResult.eNullObjectPointer);

        OdStreamBuf pStreamPrc = Globals.odrxSystemServices().createFile(in_prcPath, FileAccessMode.kFileRead);
        OdPrcFile prcDb = prcHostApp.readFile(in_prcPath);

        OdGeExtents3d extPrc = PRC_Globals.calculateExtents(prcDb);
        OdResult res = CreateAnimationEx(pStreamPrc, extPrc, out_pdfPath);

        if (res == OdResult.eOk)
          Console.WriteLine("PDF created: {0}", out_pdfPath);
      }
      catch (OdError e)
      {
        Console.WriteLine("Example OdError: " + e.description());
      }
      catch (Exception ex)
      {
        Console.WriteLine("Other example error: " + ex.Message);
      }

      mMan.StopTransaction(mStartTrans);

      try
      {
        TD_Db.odUninitialize();
      }
      catch (OdError e)
      {
        Console.WriteLine("Cleanup OdError: " + e.description());
      }
      catch (Exception ex)
      {
        Console.WriteLine("Other cleanup error: " + ex.Message);
      }
      Teigha.Core.Helpers.odUninit();

      mMan.StopAll();
    }

    private const String CreatorStr = "ODA Publish .NET SWIG";

    private static OdResult CreateAnimationEx(OdStreamBuf pStreamPrc, OdGeExtents3d extPrc, String sOutPdf)
    {
      if (pStreamPrc == null || !extPrc.isValidExtents() || String.IsNullOrEmpty(sOutPdf))
        return OdResult.eInvalidInput;

      OdFile pPublisher = OdFile.createObject();
      if (pPublisher == null)
        return OdResult.eNullObjectPointer;

      OdDocument pDoc = OdDocument.createObject();
      String creatorStr = CreatorStr;
      pDoc.setInformation(creatorStr + " Template Document", creatorStr, " Template Document", creatorStr);

      OdPage pPage1 = OdPage.createObject();
      pPage1.setOrientation(OdPdfPublish_Page_Orientation.kLandscape);
      pDoc.addPage(pPage1);

      addPageHeader(pPage1, sOutPdf, 0);

      OdCADModel pModel = OdCADModel.createObject();
      pModel.setSource(pStreamPrc);
      OdAnnotation pAnnot = OdAnnotation.createObject();
      pAnnot.setSource(pModel);

      pAnnot.setTransparentBackground(false);
      pAnnot.setBorderWidth(2);
      pAnnot.setName("Test 3D Annotation");

      OdGsDCRect rect = new OdGsDCRect(9, 832, 30, 530);


      pPage1.addAnnotation(pAnnot, rect);

      double field_w = 100;
      double field_h = 100;

      OdArtwork pArtwork = OdArtwork.createObject();

      //Default View
      OdGePoint3d defCamPos = new OdGePoint3d(-0.90612681748501411, -0.37532908821626582, 0.19509553088993711);
      OdGeVector3d defUpVec = new OdGeVector3d(0.18024483319542611, 0.074659669699104828, 0.98078424427943056);
      double camera_roll_angle = 0;
      addView(pArtwork, defCamPos, OdGePoint3d.kOrigin, defUpVec, "Default", "Default",
        OdPdfPublish_Camera_Projection.kPerspective, field_w, field_h, extPrc, OdPdfPublish_Rendering_Mode.kDefault, OdPdfPublish_Lighting_Mode.kDefault, true, camera_roll_angle);

      String animationStr = String.Empty;
      animationStr += "var Timer=0;                                                                               \n";
      animationStr += "var time=0;                                                                                \n";
      animationStr += "function RoatateZAnimation (event)                                                         \n";
      animationStr += "{                                                                                          \n";
      animationStr += "  time += event.deltaTime;                                                                 \n";
      animationStr += "  if (time>=0.02)                                                                          \n";
      animationStr += "  {                                                                                        \n";
      animationStr += "    time = 0;                                                                              \n";
      animationStr += "    var camera = scene.cameras.getByIndex(0);                                              \n";
      animationStr += "    var camdir = camera.transform.rotateAboutVectorInPlace(0.0123599, new Vector3(0,0,1)); \n";
      animationStr += "  }                                                                                        \n";
      animationStr += "}                                                                                          \n";
      animationStr += "                                                                                           \n";
      animationStr += "function PlayAnimation()                                                                   \n";
      animationStr += "{                                                                                          \n";
      animationStr += "  if (Timer == 0)                                                                          \n";
      animationStr += "  {                                                                                        \n";
      animationStr += "    runtime.setView('Default');                                                            \n";
      animationStr += "    Timer=new TimeEventHandler();                                                          \n";
      animationStr += "    Timer.onEvent=RoatateZAnimation;                                                       \n";
      animationStr += "    runtime.addEventHandler(Timer);                                                        \n";
      animationStr += "  }                                                                                        \n";
      animationStr += "  runtime.play();                                                                          \n";
      animationStr += "}                                                                                          \n";
      animationStr += "PlayAnimation()                                                                            \n";
      pArtwork.setJavaScript(animationStr);

      pAnnot.setArtwork(pArtwork);

      addPageFooter(pPage1, rect);

      OdResult result = (OdResult)pPublisher.exportPdf(pDoc, sOutPdf);
      return OdResult.eOk;
    }

    public static readonly string AppRoot = System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetEntryAssembly().Location);

    private static String correctPath(String filePath)
    {
      OdRxSystemServices pSs = Globals.odrxSystemServices();
      if (pSs != null)
      {

        String validPath = filePath;
        if (System.IO.File.Exists(System.IO.Path.Combine(AppRoot, validPath)))
          return validPath; // Found path as is.

        validPath = validPath.Insert(0, "Prc\\Examples\\OdPrcPublish3dCmds\\");

        if (System.IO.File.Exists(System.IO.Path.Combine(AppRoot, validPath)))
          return validPath;
        for (UInt32 i = 0; i < 6; i++)
        {
          validPath = validPath.Insert(0, "..\\");
          if (System.IO.File.Exists(System.IO.Path.Combine(AppRoot, validPath)))
            return validPath;
        }
      }
      return String.Empty; // not found
    }

    private static void addPageHeader(OdPage pPage, String sOutPdf, UInt16 page_index)
    {
      OdImage topLogo = OdImage.createObject();
      String pathBrandLogo = "brand-logo.jpg";
      String validPath = correctPath(pathBrandLogo);
      if (String.IsNullOrEmpty(validPath))
      {
        validPath = "brand-logo.jpg";
        throw new OdError("File 'brand-logo.jpg' not found! Please copy this file from 'Prc/Examples/OdPrcPublish3dCmds' to the folder in the support path.");
      }
      topLogo.setFile(validPath);
      OdGsDCRect topLogoRect = new OdGsDCRect(9, 256, 540, 584);
      pPage.addImage(topLogo, topLogoRect);

      OdGsDCRect fieldRect = new OdGsDCRect(332, 492, 564, 584);

      OdGsDCRect topTextRect = new OdGsDCRect(332, 492, 564, 584);
      topTextRect.m_max.y = fieldRect.m_min.y - 3;
      topTextRect.m_min.y = topTextRect.m_max.y - 10;

      addTextFields((uint)page_index * 3, sOutPdf, topTextRect, fieldRect, pPage);
    }

    private static void addTextFields(UInt32 iStartIndex, String sOutPdf, OdGsDCRect topTextRect, OdGsDCRect fieldRect, OdPage pPage)
    {
      for (UInt32 i = iStartIndex; i < iStartIndex + 3; ++i)
      {
        OdTextField field = OdTextField.createObject();
        String fieldName = "Field" + i;
        field.setName(fieldName);
        field.setBorder(false);
        field.setFont(OdPdfPublish_Text_StandardFontsType.kTimesBold);
        field.setTextJustification(OdPdfPublish_Text_Justification.kLeft);
        field.setReadOnly(true);

        OdText text = OdText.createObject();
        text.setSize(8);

        if (i == iStartIndex)
        {
          String outFileName = System.IO.Path.GetFileNameWithoutExtension(sOutPdf);
          field.setDefaultValue(outFileName);
          text.setText("FILE NAME");
        }
        else if (i == iStartIndex + 1)
        {
          OdTimeStamp date = new OdTimeStamp();
          date.getLocalTime();
          String dateStr = String.Empty;
          date.strftime("%x", ref dateStr);
          field.setDefaultValue(dateStr);
          text.setText("DATE CREATED");
        }
        else if (i == iStartIndex + 2)
        {
          field.setDefaultValue(CreatorStr);
          text.setText("AUTHOR");
        }

        pPage.addTextField(field, fieldRect);

        fieldRect.m_min.x = fieldRect.m_max.x + 10;
        fieldRect.m_max.x = fieldRect.m_min.x + 160;

        topTextRect.m_min.x += 2;
        pPage.addText(text, topTextRect);

        topTextRect.m_min.x = fieldRect.m_min.x;
        topTextRect.m_max.x = fieldRect.m_max.x;
      }
    }

    private static void addView(OdArtwork pArtwork, OdGePoint3d camPos, OdGePoint3d targPos, OdGeVector3d upVec, String extName, String intName,
      OdPdfPublish_Camera_Projection proj, double f_w, double f_h, OdGeExtents3d extPrc, OdPdfPublish_Rendering_Mode rMode,
      OdPdfPublish_Lighting_Mode lMode, bool bDefault, double camera_roll_angle /*= 0 */)
    {
      OdGePoint3d tmpCamPos = camPos;
      OdGePoint3d tmpTargPos = targPos;
      OdGeVector3d tmpUpVec = upVec;

      OdGeBoundBlock3d bbox = new OdGeBoundBlock3d(extPrc.minPoint(), extPrc.maxPoint());
      calculateCameraHelper(bbox, ref tmpCamPos, ref tmpTargPos, ref tmpUpVec, proj, ref f_w, ref f_h);
      //////////////////////////////////////////////////////////////////////////

      OdCamera pCamera = OdCamera.createObject();
      pCamera.setPosition(tmpCamPos);
      pCamera.setTarget(tmpTargPos);
      pCamera.setUpVector(tmpUpVec);
      pCamera.setField(f_w, f_h);
      pCamera.setProjection(proj);
      pCamera.zoom(0.8);

      if (camera_roll_angle > 0)
        pCamera.roll(camera_roll_angle);

      OdView pView = OdView.createObject();

      pView.setCamera(pCamera);
      pView.setExternalName(extName);
      pView.setInternalName(intName);
      pView.setDefault(bDefault);
      uint color = 0x00DC1000;
      pView.setBackgroundColor(color);
      pView.setLighting(lMode);
      pView.setRendering(rMode);
      pArtwork.addView(pView);
    }

    private static void calculateCameraHelper(OdGeBoundBlock3d extents,
      ref OdGePoint3d camPos,
      ref OdGePoint3d targPos,
      ref OdGeVector3d upVec,
      OdPdfPublish_Camera_Projection proj,
      ref double f_w,
      ref double f_h)
    {
      OdGeBoundBlock3d tmp_ext = extents;

      if ((proj != OdPdfPublish_Camera_Projection.kPerspective) && !extents.isBox())
      {
        tmp_ext.setToBox(true);
      }

      //set target to center of the scene
      OdGePoint3d newTarg = tmp_ext.center();
      OdGeVector3d viewDir = camPos - targPos;
      OdGeMatrix3d xEyeToWorld = new OdGeMatrix3d();
      {
        OdGeVector3d yVector = upVec;
        yVector.normalize();
        OdGeVector3d zVector = (camPos - targPos).normalize();
        OdGeVector3d xVector = yVector.crossProduct(zVector);
        xEyeToWorld.setCoordSystem(newTarg, xVector, yVector, zVector);
      }

      //rotate extents
      tmp_ext.transformBy(xEyeToWorld);

      OdGePoint3d min_pt = tmp_ext.minPoint(), max_pt = tmp_ext.maxPoint();

      double distance = 0.0;

      if (proj == OdPdfPublish_Camera_Projection.kPerspective)
      {
        OdGePoint3d cameraPos = newTarg;
        OdGeVector3d cameraY = upVec.normal();
        OdGeVector3d cameraZ = (camPos - targPos).normalize();
        OdGeVector3d cameraX = cameraY.crossProduct(cameraZ);

        OdGeVector3d boxVecX = new OdGeVector3d(max_pt.x - min_pt.x, 0.0, 0.0),
        boxVecY = new OdGeVector3d(0.0, max_pt.y - min_pt.y, 0.0),
        boxVecZ = new OdGeVector3d(0.0, 0.0, max_pt.z - min_pt.z);
        OdGePoint3d[] boxPt = new OdGePoint3d[8]{ min_pt, min_pt + boxVecX, min_pt + boxVecY, min_pt + boxVecZ,
                                      max_pt, max_pt - boxVecX, max_pt - boxVecY, max_pt - boxVecZ };

        // Project extents onto view plane
        OdGeExtents2d projectedExt = new OdGeExtents2d();
        {
          for (int nPt = 0; nPt < 8; nPt++)
            projectedExt.addPoint(new OdGePoint2d((boxPt[nPt] - cameraPos).dotProduct(cameraX), (boxPt[nPt] - cameraPos).dotProduct(cameraY)));
        }
        // Compute center of extents
        OdGePoint2d extCenter = projectedExt.minPoint() + projectedExt.maxPoint().Sub(projectedExt.minPoint()).Mul(0.5);

        f_w = 2.0 * (projectedExt.maxPoint().x - projectedExt.minPoint().x);
        f_h = 2.0 * (projectedExt.maxPoint().y - projectedExt.minPoint().y);

        distance = Math.Max(f_w / 2.0, f_h / 2.0) / Math.Tan(Globals.OdaPI / 6.0);
      }
      else
      {
        f_w = Math.Abs(max_pt.x - min_pt.x);//use fabs(...) for the case if min and max points are swapped
        f_h = Math.Abs(max_pt.y - min_pt.y);

        //move the camera outside the object extents
        distance = newTarg.distanceTo(extents.maxPoint());
      }

      viewDir = viewDir * distance;

      camPos = newTarg + viewDir;
      targPos = newTarg;
    }

    private static void addPageFooter(OdPage pPage, OdGsDCRect rect)
    {
      Int32 secondLineTop = 18;
      OdGsDCRect leftBottomTextRect1 = new OdGsDCRect(rect.m_min.x, rect.m_max.x, rect.m_min.y, rect.m_min.y);
      leftBottomTextRect1.m_max.y = rect.m_min.y - 5;
      leftBottomTextRect1.m_min.y = secondLineTop;
      leftBottomTextRect1.m_max.x = rect.m_min.x + 10;
      OdText copText = OdText.createObject();
      copText.setSize(8);
      copText.setFont(OdPdfPublish_Text_StandardFontsType.kSymbol);
      String copStr = new string((char)0xD3, 1);
      copText.setText(copStr);
      pPage.addText(copText, leftBottomTextRect1);

      leftBottomTextRect1.m_min.x = leftBottomTextRect1.m_max.x;
      leftBottomTextRect1.m_max.x = rect.m_max.x / 2;
      OdText leftBottomText1 = OdText.createObject();
      leftBottomText1.setSize(8);
      String copyrightStr = "2020, Open Design Alliance";
      leftBottomText1.setText(copyrightStr);
      pPage.addText(leftBottomText1, leftBottomTextRect1);

      leftBottomTextRect1.m_min.x = rect.m_min.x;
      leftBottomTextRect1.m_max.x = 220;
      leftBottomTextRect1.m_min.y = 9;
      leftBottomTextRect1.m_max.y = secondLineTop;
      OdText leftBottomText2 = OdText.createObject();
      leftBottomText2.setSize(8);
      leftBottomText2.setText("10115 E Bell Road, Suite 107 #447 Scottsdale, AZ 85260, USA. ");
      pPage.addText(leftBottomText2, leftBottomTextRect1);

      leftBottomTextRect1.m_min.x = 220;
      leftBottomTextRect1.m_max.x = rect.m_max.x / 2;
      leftBottomTextRect1.m_min.y = 9;
      leftBottomTextRect1.m_max.y = secondLineTop;
      OdText leftBottomText3 = OdText.createObject();
      leftBottomText3.setSize(8);
      leftBottomText3.setFont(OdPdfPublish_Text_StandardFontsType.kTimesBold);
      leftBottomText3.setText("www.opendesign.com");
      pPage.addText(leftBottomText3, leftBottomTextRect1);

      OdImage bottomLogo = OdImage.createObject();
      String validPath = correctPath("brand-logo-small.jpg");
      if (String.IsNullOrEmpty(validPath))
      {
        validPath = "brand-logo-small.jpg";
        throw new OdError("File 'brand-logo.jpg' not found! Please copy this file from 'Prc/Examples/OdPrcPublish3dCmds' to the folder in the support path.");
      }
      bottomLogo.setFile(validPath);
      OdGsDCRect bottomLogoRect = new OdGsDCRect();
      bottomLogoRect.m_min.x = 722;
      bottomLogoRect.m_max.y = rect.m_min.y - 5;
      bottomLogoRect.m_min.y = 3;
      bottomLogoRect.m_max.x = bottomLogoRect.m_min.x + (bottomLogoRect.m_max.y - bottomLogoRect.m_min.y);
      pPage.addImage(bottomLogo, bottomLogoRect);

      OdGsDCRect rightBottomTextRect1 = new OdGsDCRect(bottomLogoRect.m_max.x + 3, 832, secondLineTop, rect.m_min.y - 5);
      OdText rightBottomText1 = OdText.createObject();
      rightBottomText1.setSize(8);
      rightBottomText1.setText("Created with");
      pPage.addText(rightBottomText1, rightBottomTextRect1);

      rightBottomTextRect1.m_max.y = secondLineTop;
      rightBottomTextRect1.m_min.y = 9;
      OdText rightBottomText2 = OdText.createObject();
      rightBottomText2.setSize(8);
      rightBottomText2.setFont(OdPdfPublish_Text_StandardFontsType.kTimesBold);
      rightBottomText2.setText(CreatorStr);
      pPage.addText(rightBottomText2, rightBottomTextRect1);
    }
  }
}