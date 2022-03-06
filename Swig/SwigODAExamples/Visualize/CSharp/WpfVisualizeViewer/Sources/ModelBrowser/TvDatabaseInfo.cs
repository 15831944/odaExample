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
using Teigha.Visualize;

namespace WpfVisualizeViewer.ModelBrowser.ObjectProperties
{
    public class TvDatabaseInfo : OdTvFilerTimeProfiling
    {
        [Flags]
        public enum ProfilingType
        {
            New = 0,
            BuiltIn = 1,
            FromFile = 2,
            Import = 4
        }

        public long ImportTime { get; set; }
        public long VectorizingTime { get; set; }
        public long TvCreationTime { get; set; }
        public long FirstUpdateTime { get; set; }
        public long CDACreationTime { get; set; }
        public ProfilingType Type { get; set; }

        public long TotalTime { get { return ImportTime + VectorizingTime + FirstUpdateTime + CDACreationTime; } }

        public string FilePath { get; set; }

        public TvDatabaseInfo()
        {
            Type = ProfilingType.New;
        }

        public override void setVectorizingTime(long time)
        {
            VectorizingTime = time;
        }

        public override long getVectorizingTime()
        {
            return VectorizingTime;
        }

        public override void setTvTime(long time)
        {
            TvCreationTime = time;
        }

        public override long getTvTime()
        {
            return TvCreationTime;
        }

        public override void setImportTime(long time)
        {
            ImportTime = time;
        }

        public override long getImportTime()
        {
            return ImportTime;
        }

        public override void setCDATreeCreationTime(long time)
        {
          CDACreationTime = time;
        }

        public override long getCDATreeCreationTime()
        {
          return CDACreationTime;
        }

  }
}
