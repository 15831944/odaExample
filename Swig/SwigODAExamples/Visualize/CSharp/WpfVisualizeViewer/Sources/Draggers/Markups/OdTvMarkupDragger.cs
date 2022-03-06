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

using Teigha.Core;
using Teigha.Visualize;

namespace WpfVisualizeViewer
{
    public abstract class OdTvMarkupDragger : OdTvDragger
    {
        public OdTvLineWeightDef LineWeight { get; set; }

        public const string NameOfMarkupModel = "$ODA_TVVIEWER_MARKUPS";
        public const string NameOfMarkupTempEntity = "$MarkupTempEntity";
        public const string NameOfMarkupRectFold = "Rectangles";
        public const string NameOfMarkupCircFold = "Circles";
        public const string NameOfMarkupHandleFold = "Free handles";
        public const string NameOfMarkupCloudFold = "Clouds";
        public const string NameOfMarkupTextFold = "Texts";
        public const string NameOfMarkupTextStyle = "TextStyle";
        public const double MarkupTextSize = 0.02;
        public const double MarkupCaretTranslation = 0.001;
        public const double MarkupLineSpacing = 0.035;

        protected OdTvColorDef MarkupColor { get; set; }

        protected new MemoryManager MM = MemoryManager.GetMemoryManager();

        public OdTvMarkupDragger(OdTvGsDeviceId tvDeviceId, OdTvModelId tvDraggersModelId)
            : base(tvDeviceId, tvDraggersModelId)
        {
            LineWeight = new OdTvLineWeightDef(3);
            MarkupColor = new OdTvColorDef(255, 0, 0);
        }

        public override bool CanFinish()
        {
            return true;
        }

        /// <summary>
        /// Method for remove geometry data from parent
        /// </summary>
        protected void RemoveGeometryData(ref OdTvGeometryDataId parentId, ref OdTvGeometryDataId removed)
        {
            if (parentId == null || removed == null)
                return;
            MemoryTransaction mtr = MM.StartTransaction();
            parentId.openAsSubEntity(OpenMode.kForWrite).removeGeometryData(removed);
            removed = null;
            MM.StopTransaction(mtr);
        }

        /// <summary>
        /// Method for find entity by name or find first visible entity
        /// </summary>
        protected OdTvEntityId FindMarkupEntity(string name, bool findVisible = false)
        {
            MemoryTransaction mtr = MM.StartTransaction();
            OdTvEntityId id = null;
            OdTvEntitiesIterator it = TvDraggerModelId.openObject().getEntitiesIterator();

            while (!it.done())
            {
                id = it.getEntity();
                OdTvEntity curEntity = id.openObject();
                // find first visible entity or just by name
                if (findVisible && curEntity.getName() != name
                    && curEntity.getVisibility().getType() != OdTvVisibilityDef.VisibilityType.kInvisible)
                {
                    MM.StopTransaction(mtr);
                    return id;
                }
                else if (curEntity.getName() == name)
                {
                    MM.StopTransaction(mtr);
                    return id;
                }
                it.step();
            }
            MM.StopTransaction(mtr);
            return null;
        }

        /// <summary>
        /// Method for find subentity by name or first visible subentity
        /// </summary>
        protected OdTvGeometryDataId FindSubEntity(OdTvGeometryDataIterator it, string name, bool findVisible = false)
        {
            OdTvGeometryDataId id = null;

            while (!it.done())
            {
                id = it.getGeometryData();
                if (findVisible && id.getType() == OdTvGeometryDataType.kSubEntity
                  && id.openAsSubEntity().getName() != name
                  && id.openAsSubEntity().getVisibility().getType() != OdTvVisibilityDef.VisibilityType.kInvisible)
                    return id;
                else if (id.getType() == OdTvGeometryDataType.kSubEntity &&
                  id.openAsSubEntity().getName() == name)
                    return id;

                it.step();
            }

            return null;
        }

    }
}
