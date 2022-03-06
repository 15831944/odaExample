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

#include "stdafx.h"

#include "ManagedCommandsCPP.h"

void ManagedCommands::ManagedCommandsCPP1::AddDbText()
{
  Database^ db = HostApplicationServices::WorkingDatabase;
  Transaction^ tr = db->TransactionManager->StartTransaction();
  try
  {
    DBText text;
    text.TextString = "Created with the ODA Drawings.NET SDK";
    text.Height = 0.2;
    text.Position = Point3d(0, 0, 0);
    BlockTable^ bt = (BlockTable^)db->BlockTableId.GetObject(OpenMode::ForRead);
    BlockTableRecord^ ms = (BlockTableRecord^)bt[BlockTableRecord::ModelSpace].GetObject(OpenMode::ForWrite);
    ms->AppendEntity(%text);
    tr->Commit();
  }
  finally
  {
    delete tr;
  }
}

void ManagedCommands::ManagedCommandsCPP1::TestInputCommand()
{
  Database^ db = HostApplicationServices::WorkingDatabase;
  Transaction^ tr = db->TransactionManager->StartTransaction();
  try
  {
    int intValue = Editor::Current->GetInteger("enter integer value")->Value;
    Editor::Current->WriteMessage("entered integer value: " + intValue.ToString());
    double doubleValue = Editor::Current->GetDouble("enter double value")->Value;
    Editor::Current->WriteMessage("entered double value: " + doubleValue.ToString());
    String^ stringValue = Editor::Current->GetString("enter string value")->StringResult;
    Editor::Current->WriteMessage("entered string value: " + stringValue);
    String^ fileForOpen = Editor::Current->GetFileNameForOpen("filename")->StringResult;
    Editor::Current->WriteMessage("chosen file for open: " + fileForOpen);
    tr->Commit();
  }
  finally
  {
    delete tr;
  }
}

void ManagedCommands::ManagedCommandsCPP2::run()
{
  Database^ db = HostApplicationServices::WorkingDatabase;
  db->StartUndoRecord();
  Transaction^ tr = db->TransactionManager->StartTransaction();
  try
  {
    BlockTableRecord^ paperSpace = static_cast<BlockTableRecord^>(db->CurrentSpaceId.GetObject(OpenMode::ForWrite));
    Layout^ layout = static_cast<Layout^>(paperSpace->LayoutId.GetObject(OpenMode::ForWrite));

    // Convert Viewports geometry to simple entities
    ObjectIdCollection^ arrViewports = layout->GetViewports();
    if (arrViewports->Count == 0)
    {
      Editor::Current->WriteMessage("Layout is not initialized");
    }
    else
    {
      // First viewport in the list is overall - skip it
      for (int i = 1; i < arrViewports->Count; i++)
      {
        Viewport^ viewport = static_cast<Viewport^>(arrViewports[i].GetObject(OpenMode::ForWrite));
        viewport->ExplodeGeometryToBlock(paperSpace);
        viewport->NonRectClipEntityId = ObjectId::Null; // To prevent its erasing
        viewport->Erase();
      }
      // Erase overall viewport
      (static_cast<Viewport^>(arrViewports[0].GetObject(OpenMode::ForWrite)))->Erase();

      ObjectId extDictId = paperSpace->ExtensionDictionary;
      if (!extDictId.IsNull)
      {
        extDictId.GetObject(OpenMode::ForWrite)->Erase();
      }

      tr->Commit();

      // Paper block is cloned to Paper Space
      // pNewDb = pDb->wblock(idBlk);

      // insert() creates new BTR - can't be used

      Database^ newDb = gcnew Database(true, true);
      ObjectIdCollection^ identifiers = gcnew ObjectIdCollection();
      BlockTableRecordEnumerator^ blTRecEnum = paperSpace->GetEnumerator();
      while (blTRecEnum->MoveNext())
      {
        identifiers->Add(blTRecEnum->Current);
      }
      IdMapping^ idMap = gcnew IdMapping();
      delete paperSpace;

      BlockTable^ bt = static_cast<BlockTable^>(tr->GetObject(newDb->BlockTableId, OpenMode::ForWrite));
      ObjectId modelSpaceId = bt[BlockTableRecord::ModelSpace];
      delete bt;

      db->WblockCloneObjects(identifiers, modelSpaceId, idMap, DuplicateRecordCloning::Replace, false);

      // Zoom extents
      ViewportTableRecord^ viewportOfNewDb = (ViewportTableRecord^)newDb->CurrentViewportTableRecordId.GetObject(OpenMode::ForWrite);
      AbstractViewPE^ abstractViewportPE = gcnew AbstractViewPE(viewportOfNewDb);
      abstractViewportPE->ZoomExtents();

      String^ exportedLayoutName = db->Filename->Substring(0, db->Filename->LastIndexOf(".")) + "_" + layout->LayoutName;

      PromptSaveFileOptions^ saveFileOptions = gcnew PromptSaveFileOptions("Enter file name to save:");
      saveFileOptions->InitialFileName = exportedLayoutName + ".dwg";
      PromptFileNameResult^ fileNameForSave = Editor::Current->GetFileNameForSave(saveFileOptions);

      newDb->SaveAs(fileNameForSave->StringResult, DwgVersion::Current);
    }

  }
  catch (Object^ err)
  {
    Editor::Current->WriteMessage(err->ToString());
    tr->Abort();
  }
  finally
  {
    delete tr;
  }
  db->Undo();
}
