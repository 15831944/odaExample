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
using System.IO;
using Teigha.Core;
using ODA.Ifc.IfcCore;
using ODA.Sdai.sdai;

namespace ExIfcDumpSwigMgd
{

  public class OdExIfcDumper
  {
    #region Internal
    public enum ExIfcBaseType
    {
      kGeom,
      kBIM
    };

    public class ExIfcEntInfo
    {
      public String m_typeName;   // Type name literal by OdIfcEntityType
      public UInt32 m_ents;       // Total amount of entities of specified type
      public UInt32 m_entsFiles;  // Total amount of files where specified entity appears
      public ExIfcBaseType m_branch;     // Branch of file (BIM/Geometry)
    };

    public class OdFileCollectionStatistics
    {
      StreamWriter m_dumpStream;

      //
      // Total amount of files
      //
      public uint m_numFiles;

      //
      // Amount of files where dumping wasn't finished by different reasons
      //
      public uint m_errorFiles;

      //
      // Entities statistics
      //

      public Dictionary<OdIfc_OdIfcEntityType, ExIfcEntInfo> m_ents;

      public OdFileCollectionStatistics(StreamWriter dumpStream)
      {
        m_numFiles = 0;
        m_errorFiles = 0;
        m_ents = new Dictionary<OdIfc_OdIfcEntityType, ExIfcEntInfo>();
        m_dumpStream = dumpStream;
      }

      //
      // Write results to the txt file
      //
      public void writeToFile()
      {
        m_dumpStream.Write("=========================================\n");
        m_dumpStream.Write("Total files: {0}\n", m_numFiles);
        m_dumpStream.Write("Opened succesfully: {0}\n", m_numFiles - m_errorFiles);
        m_dumpStream.Write("Unsuccessful: {0}\n", m_errorFiles);
        m_dumpStream.Write("=========================================\n");


        //
        // Sort by amount of entities in total
        //
        Dictionary<UInt32, List<ExIfcEntInfo>> stats_res = new Dictionary<uint, List<ExIfcEntInfo>>();

        foreach (var item in m_ents)
        {
          if (!stats_res.ContainsKey(item.Value.m_ents))
            stats_res.Add(item.Value.m_ents, new List<ExIfcEntInfo>() { item.Value });
          else
            stats_res[item.Value.m_ents].Add(item.Value);
        }


        m_dumpStream.Write("Entity type, Branch, # entities, # files\n");
        foreach (var item in stats_res)
        {
          foreach (var _value in item.Value)
          {
            String ifcBranchName = _value.m_branch == ExIfcBaseType.kGeom ? "GEOM" : "BIM";

            m_dumpStream.Write("%s, %s, %i, %i\n",
              _value.m_typeName,
              ifcBranchName,
              _value.m_ents,
              _value.m_entsFiles);
          }
        }
      }

    }
    #endregion

    public OdExIfcDumper(StreamWriter dumpStream)
    {
      m_DumpStream = dumpStream;
      m_stats = new OdFileCollectionStatistics(dumpStream);
    }

    StreamWriter m_DumpStream;

    public OdFileCollectionStatistics m_stats;

    public static bool isDir(String path)
    {
      FileAttributes attr = File.GetAttributes(path);
      if (attr.HasFlag(FileAttributes.Directory))
        return true;
      else
        return false;
    }

    public void DumpFile(OdIfcHostAppServices pHostApp, String fileName, String version)
    {
      //
      // Dump single file
      //
      MemoryTransaction mTr = MemoryManager.GetMemoryManager().StartTransaction();
      try
      {
        m_DumpStream.Write(String.Format("Dump file: {0}\n", fileName));
        Console.WriteLine(String.Format("Dump file: {0}\n", fileName));

        if (version == "ANY")
        {
          OdDAI_OdHeaderSection headerSection = pHostApp.getHeaderSection(fileName);
          if (headerSection != null)
          {
            OdDAI_FileSchema pSchema = OdDAI_FileSchema.cast(headerSection.getEntityByType(OdDAI_OdHeaderEntityType.kFileSchema));

            if (pSchema == null)
            {
              m_DumpStream.Write(String.Format("File is invalid ... skip\n"));
              return;
            }

            OdAnsiStringArray schemasCollection = new OdAnsiStringArray();
            pSchema.getSchemaIdentifiers(schemasCollection);

            if (version == (schemasCollection[0]))
            {
              m_DumpStream.Write(String.Format("File schema: {0} ... skip\n", schemasCollection[0]));
              return;
            }
          }
          else
          {
            m_DumpStream.Write(String.Format("Error getting header section: {0}\n", fileName));
            Console.WriteLine(String.Format("Error getting header section: {0}\n", fileName));
            return;
          }
        }

        ++m_stats.m_numFiles;

        OdIfc_OdIfcEntity pEnt;
        //OdDAI_Entity pDef;
        OdIfcFile pIfcFile = pHostApp.readFile(fileName);
        if (pIfcFile == null)
        {
          ++m_stats.m_errorFiles;
          m_DumpStream.Write(String.Format("File open error: OdIfcFile wasn't created\n"));
          Console.WriteLine(String.Format("File open error: OdIfcFile wasn't created)\n"));
          return;
        }

        OdDAI_Model pModel = pIfcFile.getModel();

        if (pModel != null)
        {
          OdDAI_InstanceIterator it = pModel.newIterator();
          if (it != null)
          {
            //
            // Collect file entities information
            //
            HashSet<OdIfc_OdIfcEntityType> entities_in_file = new HashSet<OdIfc_OdIfcEntityType>();

            OdIfc_OdIfcEntityType type_id;

            for (; !it.done(); it.step())
            {
              pEnt = OdIfc_OdIfcEntity.cast(it.id().openObject());
              if (pEnt == null)
              {
                UInt64 _handleVal = it.id().getHandle().ToUInt64();
                m_DumpStream.Write("File error: Empty cell for handle #{0}\n", _handleVal);
                Console.Write("File error: Empty cell for handle #{0}\n", _handleVal);
                continue;
              }

              type_id = pEnt.type();

              if (!m_stats.m_ents.ContainsKey(type_id))
              {
                ExIfcEntInfo ent = new ExIfcEntInfo();
                ent.m_typeName = pEnt.typeName();
                ent.m_ents = 1;
                ent.m_entsFiles = 0;

                if (pEnt.isKindOf(OdIfc_OdIfcEntityType.kIfcRepresentationItem) ||
                    pEnt.isKindOf(OdIfc_OdIfcEntityType.kIfcProfileDef))
                  ent.m_branch = ExIfcBaseType.kGeom;
                else
                  ent.m_branch = ExIfcBaseType.kBIM;

                //
                // Uncomment the line to get entity definition of the entity
                //
                //pDef = pModel->getEntityDefinition(pEnt->typeName());

                m_stats.m_ents[type_id] = ent;
              }
              else
              {
                ++m_stats.m_ents[type_id].m_ents;
              }
              entities_in_file.Add(type_id);
            }

            {
              foreach (var item in entities_in_file)
              {
                ExIfcEntInfo value = null;
                if (m_stats.m_ents.TryGetValue(item, out value))
                {
                  ++value.m_entsFiles;
                }
              }
            }
          }
          else
          {
            ++m_stats.m_errorFiles;
            m_DumpStream.Write("File open error: empty model)\n");
            Console.Write("File open error: empty model)\n");
          }
        }
        else
        {
          ++m_stats.m_errorFiles;

          String schemaName = String.Empty;
          OdDAI_OdHeaderSection pHeaderSection = pIfcFile != null ? pIfcFile.getHeaderSection() : null;

          if (pHeaderSection != null)
          {
            OdDAI_FileSchema pSchema = OdDAI_FileSchema.cast(pHeaderSection.getEntityByType(OdDAI_OdHeaderEntityType.kFileSchema));

            if (pSchema != null)
            {
              OdAnsiStringArray schemasCollection = new OdAnsiStringArray();
              pSchema.getSchemaIdentifiers(schemasCollection);
              schemaName = schemasCollection.Count != 0 ? schemasCollection[0] : "";
            }
          }

          m_DumpStream.Write("Can not open the file (Unsupported schema: {0})\n", schemaName);
          Console.Write("Can not open the file (Unsupported schema: {0})\n", schemaName);
        }
      }
      catch (Exception)
      {
        m_DumpStream.Write("Exception in file '{0}'\n", fileName);
        Console.Write("Exception in file '{0}'\n", fileName);
        ++m_stats.m_errorFiles;
      }
      finally
      {
        MemoryManager.GetMemoryManager().StopTransaction(mTr);
      }
    }

    public void WalkAlongDirectories(OdIfcHostAppServices pHostApp, String dirName, String version)
    {
      var files = Directory.EnumerateFiles(dirName, "*.ifc", SearchOption.AllDirectories);
      foreach (var file in files)
      {
        DumpFile(pHostApp, file, version);
      }
    }
  }
}