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
using Teigha.Core;
using Teigha.PRC;
using Teigha.TD;

namespace OdPrcCreateSwigMgd.Samples.OdAttributeSamples
{
  public class OdAttributeExample_AttributeToProductOccurrence : OdAttributeExample
  {
    public override string Description
    {
      get
      {
        return "Create sphere and write attributes in it";
      }
    }
  }

  public class OdAttributeExample_AttributeToPartDefinition : OdAttributeExample
  {
    public override string Description
    {
      get
      {
        return "Create sphere and write attributes in it";
      }
    }
  }

  public class OdAttributeExample_AttributeToRepresentationItem : OdAttributeExample
  {
    public override string Description
    {
      get
      {
        return "Create sphere and write attributes in it";
      }
    }
  }

  public abstract class OdAttributeExample : OdPrcCreateExample
  {
    protected override void Execute(OdStreamBuf pPrcStream, OdPrcCreateSwigMgd_ExampleModes mode, OdDbHostAppServices pH, OdPrcHostAppServices pPrcHost)
    {
      // create an object
      OdStreamBuf pMemStream = OdMemoryStream.createNew();
      createTestGeometryForAttributeTest(pMemStream, pH);

      // add attribute to the object
      pMemStream.rewind();
      OdPrcFile pFile = pPrcHost.readFile(pMemStream);
      OdPrcFileStructurePtrArray fileStructures = pFile.fileStructures();
      OdPrcFileStructureTree tree = fileStructures[fileStructures.Count - 1].fileStructureTree();
      for (int i = 0; i < tree.productOccurrence().Count; ++i)
      {
        OdPrcProductOccurrence pPO = tree.productOccurrence()[i];
        pPO.name().setName("sphere");
      }

      if (mode == OdPrcCreateSwigMgd_ExampleModes.AttributeToProductOccurrence)
      {
        //  write to product occurrence
        OdPrcProductOccurrencePtrArray productOccurrence = tree.productOccurrence();
        OdPrcProductOccurrence productOc = productOccurrence[productOccurrence.Count - 1];
        // - write several attributes
        AddAttribute(productOc.attributeData(), "attribute in PrOcc #1");
        AddAttribute(productOc.attributeData(), "attribute in PrOcc #2");
        AddAttribute(productOc.attributeData(), "attribute in PrOcc #3");
      }
      if (mode == OdPrcCreateSwigMgd_ExampleModes.AttributeToPartDefinition)
      {
        // write to part definition
        OdPrcObjectIdArray partDefinition = tree.partDefinition();
        OdPrcPartDefinition part = partDefinition[partDefinition.Count -1].safeOpenObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcPartDefinition;
        // - write several attributes
        AddAttribute(part.attributeData(), "attribute in PtDef #1");
        AddAttribute(part.attributeData(), "attribute in PtDef #2");
        AddAttribute(part.attributeData(), "attribute in PtDef #3");
      }
      if (mode == OdPrcCreateSwigMgd_ExampleModes.AttributeToRepresentationItem)
      {
        // write to representation item
        OdPrcObjectIdArray partDefinition = tree.partDefinition();
        OdPrcPartDefinition part = partDefinition[partDefinition.Count -1].safeOpenObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcPartDefinition;

        OdPrcObjectIdArray representationItem = part.representationItem();
        OdPrcRepresentationItem item = representationItem[representationItem.Count -1].safeOpenObject(Teigha.PRC.OpenMode.kForWrite) as OdPrcRepresentationItem;
        // - write several attributes
        AddAttribute(item.attributeData(), "attribute in RpIt #1");
        AddAttribute(item.attributeData(), "attribute in RpIt #2");
        AddAttribute(item.attributeData(), "attribute in RpIt #3");
      }

      // write file
      pFile.writeFile(pPrcStream);
    }

    void createTestGeometryForAttributeTest(OdStreamBuf pMemStream, OdDbHostAppServices pH)
    {
      // create a solid object
      OdDb3dSolid p3dSolid = OdDb3dSolid.createObject();
      p3dSolid.createSphere(10);

      OdDbDatabase pDb = pH.createDatabase();
      OdDbBlockTableRecord pRec = pDb.getModelSpaceId().safeOpenObject(Teigha.TD.OpenMode.kForWrite) as OdDbBlockTableRecord;
      pRec.appendOdDbEntity(p3dSolid);

      // load module
      Globals.odrxDynamicLinker().loadModule("OdDwg2PrcExport", false);
      PdfExportServiceInterface pExportIFace = Globals.getPdfExportService();

      // write file to stream
      using (PDF2PRCExportParams _params = new PDF2PRCExportParams())
      {
        OdRxObject pContext = pExportIFace.createPrcExportContext(pDb);
        OdResult res = pExportIFace.ExportPrc(pContext, p3dSolid, _params);
        if (res != OdResult.eOk)
        {
          throw new OdError(res);
        }
        res = pExportIFace.serialize(pMemStream, pContext, _params);
        if (res != OdResult.eOk)
        {
          throw new OdError(res);
        }
      }
    }

    // sample timestamp sub attribute created here!
    void AddAttributeTimeStamp(OdPrcAttribute newAttribute)
    {
      // create pair
      OdPrcContentSingleAttribute attributeDataPair = new OdPrcContentSingleAttribute();
      OdTimeStamp testtime = new OdTimeStamp(OdTimeStamp.InitialValue.kInitLocalTime);
      testtime.setDate(1, 1, 1970); // month, day, year
      testtime.setTime(1, 2, 3, 0); // hour, minute, second, millisecond
      attributeDataPair.setData(testtime);

      // pair title
      OdPrcAttributeEntry subtitle = new OdPrcAttributeEntry();
      subtitle.setData(EPRCAttributeEntry.EPRCAttributeEntryCreateTimeDate); // can be one of pre-defined names from enum or any string
      attributeDataPair.setattributeEntry(subtitle);

      // add pair to attribute
      newAttribute.AddDataPair(attributeDataPair);
    }

    // sample integer sub attribute created here!
    void AddAttributeInt(OdPrcAttribute newAttribute)
    {
      // create pair
      OdPrcContentSingleAttribute attributeDataPair = new OdPrcContentSingleAttribute();
      attributeDataPair.setData((int)112233); // can be negative as well!

      // pair title
      OdPrcAttributeEntry subtitle = new OdPrcAttributeEntry();
      subtitle.setData(EPRCAttributeEntry.EPRCAttributeEntryRevisionNumber); // can be one of pre-defined names from enum or any string
      attributeDataPair.setattributeEntry(subtitle);

      // add pair to attribute
      newAttribute.AddDataPair(attributeDataPair);
    }

    // sample double sub attribute created here!
    void AddAttributeDouble(OdPrcAttribute newAttribute)
    {
      // create pair
      OdPrcContentSingleAttribute attributeDataPair = new OdPrcContentSingleAttribute();
      attributeDataPair.setData(0.123);

      // pair title
      OdPrcAttributeEntry subtitle = new OdPrcAttributeEntry();
      subtitle.setData("example double title"); // can be one of pre-defined names from enum or any string
      attributeDataPair.setattributeEntry(subtitle);

      // add pair to attribute
      newAttribute.AddDataPair(attributeDataPair);
    }

    // sample string sub attribute created here!
    void AddAttributeString(OdPrcAttribute newAttribute)
    {
      // create pair
      OdPrcContentSingleAttribute attributeDataPair = new OdPrcContentSingleAttribute();
      attributeDataPair.setData("ODA PRC SDK Create Example App");

      // pair title
      OdPrcAttributeEntry subtitle = new OdPrcAttributeEntry();
      subtitle.setData(EPRCAttributeEntry.EPRCAttributeEntryAuthor); // can be one of pre-defined names from enum or any string
      attributeDataPair.setattributeEntry(subtitle);

      // add pair to attribute
      newAttribute.AddDataPair(attributeDataPair);
    }

    // creates an attribute and fills it with several sub attributes of different type
    void AddAttribute(OdPrcAttributeData attrdata, String strTitle)
    {
      OdPrcAttributeArray  attrArr = attrdata.attributes();
      OdPrcAttribute newAttribute = new OdPrcAttribute();
      attrArr.Add(newAttribute);

      // add data
      AddAttributeTimeStamp(newAttribute);
      AddAttributeInt(newAttribute);
      AddAttributeDouble(newAttribute);
      AddAttributeString(newAttribute);

      // add title to attribute
      OdPrcAttributeEntry title = new OdPrcAttributeEntry();
      title.setData(strTitle);
      newAttribute.SetTitle(title);
    }
  }
}
