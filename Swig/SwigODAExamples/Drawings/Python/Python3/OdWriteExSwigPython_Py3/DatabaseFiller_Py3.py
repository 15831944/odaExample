#######################################################################################
# Copyright (C) 2002-2022, Open Design Alliance (the "Alliance").
# All rights reserved.
#
# This software and its documentation and related materials are owned by
# the Alliance.  The software may only be incorporated into application
# programs owned by members of the Alliance, subject to a signed
# Membership Agreement and Supplemental Software License Agreement with the
# Alliance.  The structure and organization of this software are the valuable
# trade secrets of the Alliance and its suppliers.  The software is also
# protected by copyright law and international treaty provisions.  Application
# programs incorporating this software must include the following statement
# with their copyright notices:
#
#   This application incorporates Open Design Alliance software pursuant to a
#   license
#   agreement with Open Design Alliance.
#   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance.
#   All rights reserved.
#
# By use of this software, its documentation or related materials, you
# acknowledge and accept the above terms.
#######################################################################################
from ODA_PyMemManager_Py3 import *
from ODA_Kernel_Py3 import *
from ODA_Drawings_Py3 import *
from DbNurbData_Py3 import *
from DbSubDMeshData_Py3 import *
import os
import math

class EntityBoxes():
     WIDTH_BOX = 2.25
     HEIGHT_BOX = 3.25
     
     HOR_SPACE = 0.625
     VER_SPACE = 0.375
     
     HOR_BOXES = 11
     VER_BOXES = 8

     #***********************************************************************/
     # Define the entity box widths */
     #***********************************************************************/
     BoxSizes = [[1,1,1,1,2,1,1,1,1,1,0],
       [1,3,2,1,1,1,2,0,0,0,0],
       [2,3,3,1,2,0,0,0,0,0,0],
       [1,1,1,2,1,1,1,1,1,1,0],
       [2,2,2,1,1,2,1,0,0,0,0],
       [3,2,1,1,1,1,1,1,0,0,0],
       [1,1,1,1,1,1,1,1,1,1,1],
       [1,1,1,1,1,1,1,1,1,1,1]]

     #*********************************************************************/
     # Return the width of the specified box */
     #*********************************************************************/
     @staticmethod
     def getWidth(row, col):
       return EntityBoxes.BoxSizes[row][col] * EntityBoxes.WIDTH_BOX + (EntityBoxes.BoxSizes[row][col] - 1) * EntityBoxes.HOR_SPACE

     #*********************************************************************/
     # Return the height of specified box */
     #*********************************************************************/
     @staticmethod
     def getHeight():
       return EntityBoxes.HEIGHT_BOX

     #*********************************************************************/
     # Return True if and only if the specified box is a box */
     #*********************************************************************/
     @staticmethod
     def isBox(row, col):
       return True if EntityBoxes.BoxSizes[row][col] > 0 else False
    
     #*********************************************************************/
     # Return the upper-left corner of the specified box */
     #*********************************************************************/
     @staticmethod
     def getBox(row, col):
       point = OdGePoint3d.kOrigin
       if (col > EntityBoxes.HOR_BOXES - 1):
         return point
     
       point = OdGePoint3d(0, EntityBoxes.HEIGHT_BOX * EntityBoxes.VER_BOXES + EntityBoxes.VER_SPACE * (EntityBoxes.VER_BOXES - 1), 0)
     
       for i in range(0, col):
         point.x += EntityBoxes.BoxSizes[row][i] * EntityBoxes.WIDTH_BOX
         point.x += EntityBoxes.BoxSizes[row][i] * EntityBoxes.HOR_SPACE
  
       point.y -= row * EntityBoxes.HEIGHT_BOX
       point.y -= row * EntityBoxes.VER_SPACE
       return point
     
     #*********************************************************************/
     # Return the center of the specified box */
     #*********************************************************************/
     @staticmethod
     def getBoxCenter(row, col):
       point = EntityBoxes.getBox(row, col)
       w = EntityBoxes.getWidth(row, col)
       point.x += w / 2.0
       point.y -= EntityBoxes.HEIGHT_BOX / 2.0
       return point
     
     #*********************************************************************/
     # Return the size of the box array */
     #*********************************************************************/
     @staticmethod
     def getArraySize():
       return OdGeVector3d(EntityBoxes.WIDTH_BOX * EntityBoxes.HOR_BOXES + EntityBoxes.HOR_SPACE * (EntityBoxes.HOR_BOXES - 1),
                          -(EntityBoxes.HEIGHT_BOX * EntityBoxes.VER_BOXES + EntityBoxes.VER_SPACE * (EntityBoxes.VER_BOXES - 1)), 
                          0)
     
     #*********************************************************************/
     # Return the center of the box array */
     #*********************************************************************/
     @staticmethod
     def getArrayCenter():
       return OdGePoint3d(0.5 * (EntityBoxes.WIDTH_BOX * EntityBoxes.HOR_BOXES + EntityBoxes.HOR_SPACE * (EntityBoxes.HOR_BOXES - 1)),
                          0.5 * (EntityBoxes.HEIGHT_BOX * EntityBoxes.VER_BOXES + EntityBoxes.VER_SPACE * (EntityBoxes.VER_BOXES - 1)),
                          0)


class DatabaseFiller_Py3():
     m_layoutEntities = OdDbObjectIdArray()
     m_textSize = 0.2
     m_textOffset = OdGeVector3d(0.5 * m_textSize, -0.5 * m_textSize, 0)
     m_textLine = OdGeVector3d(0, -1.6 * m_textSize, 0)

     @staticmethod
     def OdaToRadian(deg): return (deg) * math.pi / 180.0

     def addRegApp(self,database,name):
        return database.newRegApp(name)

     def addStyle(self, 
                 pDb, styleName, textSize, xScale, priorSize,
                 obliquing, fileName, isShapeFile, ttFaceName,
                 bold, italic, charset, pitchAndFamily):
      pStyles = pDb.getTextStyleTableId().safeOpenObject(kForWrite)
      pStyle = OdDbTextStyleTableRecord.createObject()

      # Name must be set before a table object is added to a table.  The
      # isShapeFile flag must also be set (if True) before adding the object
      # to the database.
      pStyle.setName(styleName)
      pStyle.setIsShapeFile(isShapeFile)

      # Add the object to the table.
      styleId = pStyles.add(pStyle)

      # Set the remaining properties.
      pStyle.setTextSize(textSize)
      pStyle.setXScale(xScale)
      pStyle.setPriorSize(priorSize)
      pStyle.setObliquingAngle(obliquing)
      pStyle.setFileName(fileName)

      if (isShapeFile):
        pStyle.setPriorSize(22.45)
      if (ttFaceName != ""):
        pStyle.setFont(ttFaceName, bold, italic, charset, pitchAndFamily)
      return styleId
     
     def addLinetype(self,pDb,name,comments):
      ##*********************************************************************/
      ## Open the Linetype table */
      ##*********************************************************************/
      pLinetypes = pDb.getLinetypeTableId().safeOpenObject(kForWrite)
      pLinetype = OdDbLinetypeTableRecord.createObject()
      
      ##*********************************************************************/
      ## Linetype must have a name before adding it to the table.  */
      ##*********************************************************************/
      pLinetype.setName(name)
      
      ##*********************************************************************/
      ## Add the record to the table.  */
      ##*********************************************************************/
      linetypeId = pLinetypes.add(pLinetype)
      
      ##*********************************************************************/
      ## Add the Comments.  */
      ##*********************************************************************/
      pLinetype.setComments(comments)   
      return linetypeId

     def addLinetypes(self, pDb, shapeStyleId, txtStyleId):        
      # Continuous linetype
      self.addLinetype(pDb, "Continuous2", "Solid Line")
     
      #Hidden linetype
      #This is not the standard Hidden linetype, but is used by examples
      ltId = self.addLinetype(pDb, "Hidden", "- - - - - - - - - - - - - - - - - - - - -")
      pLt = ltId.safeOpenObject(kForWrite)
      pLt.setNumDashes(2)
      pLt.setPatternLength(0.1875)
      pLt.setDashLengthAt(0, 0.125)
      pLt.setDashLengthAt(1, -0.0625)
   
      # Linetype with text
      ltId = self.addLinetype(pDb, "HW_ODA", "__ HW __ OD __ HW __ OD __")
      pLt = ltId.safeOpenObject(kForWrite)
      pLt.setNumDashes(6)
      pLt.setPatternLength(1.8)
      pLt.setDashLengthAt(0, 0.5)
      pLt.setDashLengthAt(1, -0.2)
      pLt.setDashLengthAt(2, -0.2)
      pLt.setDashLengthAt(3, 0.5)
      pLt.setDashLengthAt(4, -0.2)
      pLt.setDashLengthAt(5, -0.2)

      pLt.setShapeStyleAt(1, txtStyleId)
      pLt.setShapeOffsetAt(1, OdGeVector2d(-0.1, -0.05))
      pLt.setTextAt(1, "HW")
      pLt.setShapeScaleAt(1, 0.5)

      pLt.setShapeStyleAt(4, txtStyleId)
      pLt.setShapeOffsetAt(4, OdGeVector2d(-0.1, -0.05))
      pLt.setTextAt(4, "OD")
      pLt.setShapeScaleAt(4, 0.5)
      
      # ZIGZAG linetype
      ltId = self.addLinetype(pDb, "ZigZag", "/\\/\\/\\/\\/\\/\\/\\/\\")
      pLt = ltId.safeOpenObject(kForWrite)
      pLt.setNumDashes(4)
      pLt.setPatternLength(0.8001)
      pLt.setDashLengthAt(0, 0.0001)
      pLt.setDashLengthAt(1, -0.2)
      pLt.setDashLengthAt(2, -0.4)
      pLt.setDashLengthAt(3, -0.2)

      pLt.setShapeStyleAt(1, shapeStyleId)
      pLt.setShapeOffsetAt(1, OdGeVector2d(-0.2, 0.0))
      pLt.setShapeNumberAt(1, 131) #ZIG shape
      pLt.setShapeScaleAt(1, 0.2)

      pLt.setShapeStyleAt(2, shapeStyleId)
      pLt.setShapeOffsetAt(2, OdGeVector2d(0.2, 0.0))
      pLt.setShapeNumberAt(2, 131) #ZIG shape
      pLt.setShapeScaleAt(2, 0.2)
      pLt.setShapeRotationAt(2, 3.1415926)
      return

     def addLayer(self, pDb, name, color, linetype):
       ##*********************************************************************/
       ## Open the layer table */
       ##*********************************************************************/
       pLayers = pDb.getLayerTableId().safeOpenObject(kForWrite)
       
       #*********************************************************************/
       # Create a layer table record */
       #*********************************************************************/
       pLayer = OdDbLayerTableRecord.createObject()
       
       #*********************************************************************/
       # Layer must have a name before adding it to the table.  */
       #*********************************************************************/
       pLayer.setName(name)
       
       #*********************************************************************/
       # Set the Color.  */
       #*********************************************************************/
       pLayer.setColorIndex(color)
       
       #*********************************************************************/
       # Set the Linetype.  */
       #*********************************************************************/
       pLinetypes = pDb.getLinetypeTableId().safeOpenObject()
       linetypeId = pLinetypes.getAt(linetype)
       pLayer.setLinetypeObjectId(linetypeId)
       
       #*********************************************************************/
       # Add the record to the table.  */
       #*********************************************************************/
       return pLayers.add(pLayer)

     def addBlockDef(self, pDb, name, boxRow, boxCol):
       #*********************************************************************/
       # Open the block table */
       #*********************************************************************/
       pBlocks = pDb.getBlockTableId().safeOpenObject(kForWrite)
       
       #*********************************************************************/
       # Create a BlockTableRecord */
       #*********************************************************************/
       bBTR = OdDbBlockTableRecord.createObject()
       
       #*********************************************************************/
       # Block must have a name before adding it to the table.  */
       #*********************************************************************/
       bBTR.setName(name)
       
       #*********************************************************************/
       # Add the record to the table.  */
       #*********************************************************************/
       btrId = pBlocks.add(bBTR)
       w = EntityBoxes.getWidth(boxRow, boxCol)
       
       #*********************************************************************/
       # Add a Circle */
       #*********************************************************************/
       pCircle = OdDbCircle.createObject()
       pCircle.setDatabaseDefaults(pDb)
       bBTR.appendOdDbEntity(pCircle)
       
       center = OdGePoint3d(0, 0, 0)
       center.x -= w * 2.5 / 8.0
       
       pCircle.setCenter(center)
       pCircle.setRadius(w * 1.0 / 8.0)
       
       #*********************************************************************/
       # Add an Arc */
       #*********************************************************************/
       pArc = OdDbArc.createObject()
       pArc.setDatabaseDefaults(pDb)
       bBTR.appendOdDbEntity(pArc)
       
       pArc.setRadius(w * 1.0 / 8.0)
       
       center = OdGePoint3d(0, 0, 0)
       center.y -= pArc.radius() / 2.0
       
       pArc.setCenter(center)
       pArc.setStartAngle(self.OdaToRadian(0.0))
       pArc.setEndAngle(self.OdaToRadian(180.0))
       
       #*********************************************************************/
       # Add an Ellipse */
       #*********************************************************************/
       pEllipse = OdDbEllipse.createObject()
       pEllipse.setDatabaseDefaults(pDb)
       bBTR.appendOdDbEntity(pEllipse)
       
       center = OdGePoint3d(0, 0, 0)
       center.x += w * 2.5 / 8.0
       
       majorRadius = w * 1.0 / 8.0
       majorAxis = OdGeVector3d(majorRadius, 0.0, 0.0)
       majorAxis.rotateBy(self.OdaToRadian(30.0), OdGeVector3d.kZAxis)
       
       radiusRatio = 0.25
       
       pEllipse.set(center, OdGeVector3d.kZAxis, majorAxis, radiusRatio)
       
       #*********************************************************************/
       # Add an Attdef */
       #*********************************************************************/
       pAttDef = OdDbAttributeDefinition.createObject()
       pAttDef.setDatabaseDefaults(pDb)
       bBTR.appendOdDbEntity(pAttDef)
       
       pAttDef.setPrompt("Enter ODT_ATT: ")
       pAttDef.setTag("Oda_ATT")
       pAttDef.setHorizontalMode(kTextCenter)
       pAttDef.setHeight(0.1)
       pAttDef.setTextString("Default")
       
       #*********************************************************************/
       # Return the ObjectId of the BlockTableRecord */
       #*********************************************************************/
       return btrId

     def addDimStyle(self,pDb,dimStyleName):
       #*********************************************************************/
       # Create the DimStyle */
       #*********************************************************************/
       pDimStyle = OdDbDimStyleTableRecord.createObject()
       #*********************************************************************/
       # Set the name */
       #*********************************************************************/
       pDimStyle.setName(dimStyleName)
       #*********************************************************************/
       # Open the DimStyleTable */
       #*********************************************************************/
       pTable = pDb.getDimStyleTableId().safeOpenObject(kForWrite)
       #*********************************************************************/
       # Add the DimStyle */
       #*********************************************************************/
       dimStyleId = pTable.add(pDimStyle)
       #*********************************************************************/
       # Set some properties */
       #*********************************************************************/

       pDimStyle.setDimtxsty(OdDbHardPointerId(pDb.getTextStyleStandardId()))
       pDimStyle.setDimsah(True)
       pDimStyle.setDimblk1("_OBLIQUE")
       pDimStyle.setDimblk2("_DOT")

       return dimStyleId

     def addMLineStyle(self, pDb, name, desc):
       #*********************************************************************/
       # Open the MLineStyle dictionary */
       #*********************************************************************/
       pMLDic = pDb.getMLStyleDictionaryId().safeOpenObject(kForWrite)
       
       #*********************************************************************/
       # Create an Mline Style */
       #*********************************************************************/
       pStyle = OdDbMlineStyle.createObject()
       #*********************************************************************/
       # Set some parameters */
       #*********************************************************************/
       pStyle.setName(name)
       pStyle.setDescription(desc)
       pStyle.setStartAngle(self.OdaToRadian(105.0))
       pStyle.setEndAngle(self.OdaToRadian(75.0))
       pStyle.setShowMiters(True)
       pStyle.setStartSquareCap(True)
       pStyle.setEndSquareCap(True)
       
       #*********************************************************************/
       # Get the object ID of the desired linetype */
       #*********************************************************************/
       pLtTable = pDb.getLinetypeTableId().safeOpenObject()
       linetypeId = pLtTable.getAt("Hidden")
       
       color = OdCmColor()
       
       #*********************************************************************/
       # Add some elements */
       #*********************************************************************/
       color.setRGB(255, 0, 0)
       pStyle.addElement(0.1, color, linetypeId)
       color.setRGB(0, 255, 0)
       pStyle.addElement(0.0, color, linetypeId)
       
       #*********************************************************************/
       # Update the MLine dictionary */
       #*********************************************************************/
       return pMLDic.setAt(name, pStyle)

     def addMaterial(self, pDb, name, desc):
       #*********************************************************************/
       # Open the Material dictionary */
       #*********************************************************************/
       pMatDic = pDb.getMaterialDictionaryId().safeOpenObject(kForWrite)
       
       #*********************************************************************/
       # Create a Material */
       #*********************************************************************/
       pMaterial = OdDbMaterial.createObject()
       #*********************************************************************/
       # Set some parameters */
       #*********************************************************************/
       pMaterial.setName(name)
       pMaterial.setDescription(desc)
       
       materialColor = OdGiMaterialColor()
       materialColor.setMethod(OdGiMaterialColor.kOverride)
       materialColor.setFactor(0.75)
       materialColor.setColor(OdCmEntityColor(192, 32, 255))
       
       materialMap = OdGiMaterialMap()
       materialMap.setBlendFactor(0.0)
       materialMap.setSource(OdGiMaterialMap.kFile)
       
       pMaterial.setAmbient(materialColor)
       pMaterial.setBump(materialMap)
       pMaterial.setDiffuse(materialColor, materialMap)
       pMaterial.setOpacity(1.0, materialMap)
       pMaterial.setReflection(materialMap)
       pMaterial.setRefraction(1.0, materialMap)
       pMaterial.setTranslucence(0.0)
       pMaterial.setSelfIllumination(0.0)
       pMaterial.setReflectivity(0.0)
       pMaterial.setMode(OdGiMaterialTraits.kRealistic)
       pMaterial.setChannelFlags(OdGiMaterialTraits.kNone)
       pMaterial.setIlluminationModel(OdGiMaterialTraits.kBlinnShader)
       
       materialColor.setFactor(1.0)
       materialColor.setColor(OdCmEntityColor(255, 255, 255))
       pMaterial.setSpecular(materialColor, materialMap, 0.67)
       #*********************************************************************/
       # Update the Material dictionary */
       #*********************************************************************/
       return pMatDic.setAt(name, pMaterial)

     def addPsViewport(self,pDb,layerId):
       #*********************************************************************/
       # Enable PaperSpace */
       #                                                                    */
       # NOTE: This is required to cause Teigha to automatically create */
       # the overall viewport.  If not called before opening PaperSpace */
       # BlockTableRecord, the first viewport created IS the the overall */
       # viewport.  */
       #*********************************************************************/
       pDb.setTILEMODE(False)
       
       #*********************************************************************/
       # Open PaperSpace */
       #*********************************************************************/
       pPs = pDb.getPaperSpaceId().safeOpenObject(kForWrite)
       
       #*********************************************************************/
       # Disable PaperSpace */
       #*********************************************************************/
       # pDb.setTILEMODE(1)
       
       #*********************************************************************/
       # Create the viewport */
       #*********************************************************************/
       pVp = OdDbViewport.createObject()
       pVp.setDatabaseDefaults(pDb)
       #*********************************************************************/
       # Add it to PaperSpace */
       #*********************************************************************/
       pPs.appendOdDbEntity(pVp)
       
       #*********************************************************************/
       # Set some parameters */
       #*********************************************************************/
       pVp.setCenterPoint(OdGePoint3d(5.25, 4.0, 0))
       pVp.setWidth(10.0)
       pVp.setHeight(7.5)
       pVp.setViewTarget(OdGePoint3d(0, 0, 0))
       pVp.setViewDirection(OdGeVector3d(0, 0, 1))
       pVp.setViewHeight(8.0)
       pVp.setLensLength(50.0)
       pVp.setViewCenter(OdGePoint2d(5.25, 4.0))
       pVp.setSnapIncrement(OdGeVector2d(0.25, 0.25))
       pVp.setGridIncrement(OdGeVector2d(0.25, 0.25))
       pVp.setCircleSides(20000)
       
       #*********************************************************************/
       # Freeze a layer in this viewport */
       #*********************************************************************/
       frozenLayers = OdDbObjectIdArray()
       frozenLayers.push_back(layerId)
       pVp.freezeLayersInViewport(frozenLayers)    
       
       #*********************************************************************/
       # Disable PaperSpace */
       #*********************************************************************/
       pDb.setTILEMODE(True)
       return

     def createEntityBoxes(self,btrId,layerId):
        pDb = btrId.database()

        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)

        #*********************************************************************/
        # Create a 2D polyline for each box */
        #*********************************************************************/
        for j in range(0, EntityBoxes.VER_BOXES):
          for i in range(0, EntityBoxes.HOR_BOXES):
            if not EntityBoxes.isBox(j, i):
              break

            wCurBox = EntityBoxes.getWidth(j, i)
            currentPoint = EntityBoxes.getBox(j, i)

            pPline = OdDb2dPolyline.createObject()
            pPline.setDatabaseDefaults(pDb)

            pVertex1 = OdDb2dVertex.createObject()
            pVertex1.setDatabaseDefaults(pDb)
            pPline.appendVertex(pVertex1)
            pos = currentPoint
            pVertex1.setPosition(pos)
            pVertex1.thisown = False

            pVertex2 = OdDb2dVertex.createObject()
            pPline.appendVertex(pVertex2)
            pos.x += wCurBox
            pVertex2.setPosition(pos)
            pVertex2.thisown = False

            pVertex3 = OdDb2dVertex.createObject()
            pPline.appendVertex(pVertex3)
            pos.y -= EntityBoxes.getHeight()
            pVertex3.setPosition(pos)
            pVertex3.thisown = False

            pVertex4 = OdDb2dVertex.createObject()
            pPline.appendVertex(pVertex4)
            pos.x -= wCurBox
            pVertex4.setPosition(pos)
            pVertex4.thisown = False
            
            pPline.makeClosed()

            pPline.setColorIndex(OdCmEntityColor.kACIBlue, True)
            pPline.setLayer(layerId, True)
            pPline.thisown = False

            bBTR.appendOdDbEntity(pPline)
          
        
        #*********************************************************************/
        # 'Zoom' the box array by resizing the active tiled MS viewport */
        #*********************************************************************/
        pVpTable = pDb.getViewportTableId().safeOpenObject(kForWrite)
        vpID = pVpTable.getActiveViewportId()
        vPortRec = vpID.safeOpenObject(kForWrite)

        center = EntityBoxes.getArrayCenter()
        vPortRec.setCenterPoint(center.convert2d())

        size = EntityBoxes.getArraySize()
        vPortRec.setHeight(1.05 * abs(size.y))
        vPortRec.setWidth(1.05 * abs(size.x))
        vPortRec.setCircleSides(20000)
        return
     
     def addPointEnt(self,bBTR,point,layerId,pGroup):
        #*********************************************************************/
        # Create the point object */
        #*********************************************************************/
        pPoint = OdDbPoint.createObject()
        pPoint.setDatabaseDefaults(bBTR.database())
        pointId = bBTR.appendOdDbEntity(pPoint)
        
        #*********************************************************************/
        # Set some properties */
        #*********************************************************************/
        pPoint.setPosition(point)
        
        #*********************************************************************/
        # Add the point to the specified group */
        #*********************************************************************/
        if (pGroup != None):
          pGroup.append(pointId)
        #*********************************************************************/
        # Set the point to the specified layer */
        #*********************************************************************/
        if (not layerId.isNull()):
          pPoint.setLayer(layerId, False)
        return pointId 

     def addTextEnt(self, bBTR, position, ap,
                    str, height, hMode, vMode, layerId, styleId):
        return self.addTextEnt2(bBTR, position, ap, str, height, hMode, vMode, layerId, styleId, None)
   
     def addTextEnt2(self, bBTR, position, ap,
                        str, height, hMode, vMode,
                        layerId, styleId, pGroup):
        #*********************************************************************/
        # Create the text object */
        #*********************************************************************/
        pText = OdDbText.createObject()
        pText.setDatabaseDefaults(bBTR.database())
        textId = bBTR.appendOdDbEntity(pText)
        
        #*********************************************************************/
        # Add the text to the specified group */
        #*********************************************************************/
        if (pGroup != None):
          pGroup.append(textId)
        
        #*********************************************************************/
        # Set some properties */
        #*********************************************************************/
        pText.setPosition(position)
        pText.setAlignmentPoint(ap)
        pText.setHeight(height)
        pText.setWidthFactor(1.0)
        pText.setTextString(str)
        pText.setHorizontalMode(hMode)
        pText.setVerticalMode(vMode)
        
        #*********************************************************************/
        # Set the text to the specified style */
        #*********************************************************************/
        if (not styleId.isNull()):
          pText.setTextStyle(styleId)
        
        #*********************************************************************/
        # Set the text to the specified layer */
        #*********************************************************************/
        if (not layerId.isNull()):
          pText.setLayer(layerId, False)    
        return textId
   

     def addLines(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "LINEs", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the center of the box */
        #*********************************************************************/
        point = EntityBoxes.getBoxCenter(0, 0)
        
        #*********************************************************************/
        # Add the lines that describe a 12 pointed star */
        #*********************************************************************/
        toStart = OdGeVector3d(1.0, 0.0, 0.0)
        
        for i in range(0,12):        
          pLine = OdDbLine.createObject()
          pLine.setDatabaseDefaults(bBTR.database())
          bBTR.appendOdDbEntity(pLine)
          pLine.setStartPoint(point + toStart)
          pLine.setEndPoint(point + toStart.rotateBy(self.OdaToRadian(160.0), OdGeVector3d.kZAxis))      
        return
     
     def add2dPolyline(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "2D POLYLINE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Add a 2dPolyline to the database */
        #*********************************************************************/
        pPline = OdDb2dPolyline.createObject()
        pPline.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pPline)
        
        #*********************************************************************/
        # Add the vertices */
        #*********************************************************************/
        pos = point
        pos.y -= h
        pos.x += w / 8
        pos.y += h / 8
        
        width = [[0.0, w / 12, w / 4, 0.0],  [w / 4, w / 12, 0.0, 0.0]]
        
        for i in range(0,4):
          pVertex = OdDb2dVertex.createObject()
          pVertex.setDatabaseDefaults(bBTR.database())
          pPline.appendVertex(pVertex)
          pVertex.setPosition(pos)
          pos.x += w / 4.0
          pos.y += h / 4.0
          pVertex.setStartWidth(width[0][i])
          pVertex.setEndWidth(width[1][i])
        return

     def addPolyFaceMesh(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)

        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "PolyFaceMesh", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Add a PolyFaceMesh to the database */
        #*********************************************************************/
        pMesh = OdDbPolyFaceMesh.createObject()
        pMesh.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pMesh)
        
        
        #*********************************************************************/
        # Add the faces and vertices that define a pup tent */
        #*********************************************************************/
        
        dx = w * 3.0 / 8.0
        dy = h * 3.0 / 8.0
        dz = dy
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        
        self.appendPfMeshVertex(pMesh, center.x + dx, center.y + dy, 0)
        self.appendPfMeshVertex(pMesh, center.x + 0, center.y + dy, center.z + dz)
        self.appendPfMeshVertex(pMesh, center.x - dx, center.y + dy, 0)
        self.appendPfMeshVertex(pMesh, center.x - dx, center.y - dy, 0)
        self.appendPfMeshVertex(pMesh, center.x + 0, center.y - dy, center.z + dz)
        self.appendPfMeshVertex(pMesh, center.x + dx, center.y - dy, 0)
        
        self.appendFaceRecord(pMesh, 1, 2, 5, 6)
        self.appendFaceRecord(pMesh, 2, 3, 4, 5)
        self.appendFaceRecord(pMesh, 6, 5, 4, 0)
        self.appendFaceRecord(pMesh, 3, 2, 1, 0)
        return

     def appendFaceRecord(self,pMesh, i1, i2, i3, i4):
        #*********************************************************************/
        # Append a FaceRecord to the PolyFaceMesh */
        #*********************************************************************/
        pFr = OdDbFaceRecord.createObject()
        pMesh.appendFaceRecord(pFr)
        
        #*********************************************************************/
        # Set the properties */
        #*********************************************************************/
        pFr.setVertexAt(0, i1)
        pFr.setVertexAt(1, i2)
        pFr.setVertexAt(2, i3)
        pFr.setVertexAt(3, i4)
        return

     def appendPfMeshVertex(self, pMesh, x, y, z):
        #*********************************************************************/
        # Append a MeshVertex to the PolyFaceMesh */
        #*********************************************************************/
        pVertex = OdDbPolyFaceMeshVertex.createObject()
        pMesh.appendVertex(pVertex)
        
        #*********************************************************************/
        # Set the properties */
        #*********************************************************************/
        pVertex.setPosition(OdGePoint3d(x, y, z))
        return

     def addPolygonMesh(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "PolygonMesh", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Add a PolygonMesh to the database */
        #*********************************************************************/
        pMesh = OdDbPolygonMesh.createObject()
        pMesh.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pMesh)
        
        #*********************************************************************/
        # Define the size of the mesh */
        #*********************************************************************/
        mSize = 16
        nSize = 4
        pMesh.setMSize(mSize)
        pMesh.setNSize(nSize)
        
        
        #*********************************************************************/
        # Define a profile */
        #*********************************************************************/
        dx = w * 3.0 / 8.0
        dy = h * 3.0 / 8.0
        
        vectors = OdGeVector3dArray()
        vectors.push_back(OdGeVector3d(0, -dy, 0))
        vectors.push_back(OdGeVector3d(dx, -dy, 0))
        vectors.push_back(OdGeVector3d(dx, dy, 0))
        vectors.push_back(OdGeVector3d(0, dy, 0))
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        
        #*********************************************************************/
        # Append the vertices to the mesh */
        #*********************************************************************/
        for i in range(0,mSize):
          for j in range(0,nSize):
            self.appendPgMeshVertex(pMesh, center + vectors.At(j))
            vectors.At(j).rotateBy(self.OdaToRadian(360.0 / mSize), OdGeVector3d.kYAxis)

        pMesh.makeMClosed()
        return
     
     def appendPgMeshVertex(self,pPgMesh,pos):
        #*********************************************************************/
        # Append a Vertex to the PolyFaceMesh */
        #*********************************************************************/
        pVertex = OdDbPolygonMeshVertex.createObject()
        pPgMesh.appendVertex(pVertex)
        
        #*********************************************************************/
        # Set the properties */
        #*********************************************************************/
        pVertex.setPosition(pos)
        return
     
     def addCurves(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Create a Circle */
        #*********************************************************************/
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pCircle)
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        center.x -= w * 2.5 / 8.0
        pCircle.setCenter(center)
        pCircle.setRadius(w * 1.0 / 8.0)
        
        #*********************************************************************/
        # Add a Hyperlink to the Circle */
        #*********************************************************************/
        hpe = OdDbEntityHyperlinkPE.cast(pCircle)
        urls = hpe.getHyperlinkCollection(pCircle)
        
        urls.addTail("http://forum.opendesign.com/forumdisplay.php?s=&forumid=17", "Open Design Alliance Forum > Teigha, C++ version")
        
        hpe.setHyperlinkCollection(pCircle, urls)
        
        if (not hpe.hasHyperlink(pCircle)):
          raise OdError("Hyperlinks are broken")
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        textY = point.y - self.m_textSize / 2.0
        
        self.addTextEnt(bBTR,
          OdGePoint3d(center.x, textY, 0), OdGePoint3d(center.x, textY, 0),
          "CIRCLE", self.m_textSize, kTextCenter, kTextTop, layerId, styleId)
        self.addTextEnt(bBTR,
          OdGePoint3d(center.x, textY - 1.6 * self.m_textSize, 0), OdGePoint3d(center.x, textY - 1.6 * self.m_textSize, 0),
          "w/Hyperlink", self.m_textSize, kTextCenter, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Create an Arc */
        #*********************************************************************/
        pArc = OdDbArc.createObject()
        pArc.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pArc)
        
        pArc.setRadius(w * 1.0 / 8.0)
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        
        center.y += pArc.radius() / 2.0
        
        pArc.setCenter(center)
        pArc.setStartAngle(self.OdaToRadian(0.0))
        pArc.setEndAngle(self.OdaToRadian(180.0))
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          OdGePoint3d(center.x, textY, 0), OdGePoint3d(center.x, textY, 0),
          "ARC", self.m_textSize, kTextCenter, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Add an Ellipse */
        #*********************************************************************/
        pEllipse = OdDbEllipse.createObject()
        pEllipse.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pEllipse)
        
        majorRadius = w * 1.0 / 8.0
        radiusRatio = 0.25
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        center.x += w * 2.5 / 8.0
        center.y += majorRadius
        
        majorAxis = OdGeVector3d(majorRadius, 0.0, 0.0)
        majorAxis.rotateBy(self.OdaToRadian(30.0), OdGeVector3d.kZAxis)
        
        pEllipse.set(center, OdGeVector3d.kZAxis, majorAxis, radiusRatio)
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          OdGePoint3d(center.x, textY, 0), OdGePoint3d(center.x, textY, 0),
          "ELLIPSE", self.m_textSize, kTextCenter, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Add a Point */
        #*********************************************************************/
        pPoint = OdDbPoint.createObject()
        pPoint.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pPoint)
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        center.y -= h * 1.0 / 8.0
        
        pPoint.setPosition(center)
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        center.y += h * 1.0 / 8.0
        self.addTextEnt(bBTR, center, center,
          "POINT", self.m_textSize, kTextCenter, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Set the point display mode so we can see it */
        #*********************************************************************/
        pDb.database().setPDMODE(3)
        pDb.database().setPDSIZE(0.1)
        return

     def addTolerance(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "TOLERANCE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        
        #*********************************************************************/
        # Add a Frame Control Feature (Tolerance) to the database */
        #*********************************************************************/
        pTol = OdDbFcf.createObject()
        pTol.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pTol)
        
        #*********************************************************************/
        # Set the properties */
        #*********************************************************************/
        pTol.setDatabaseDefaults(pDb)
        point.x += w / 6.0
        point.y -= h / 4.0
        pTol.setLocation(point)
        pTol.setText("{\\Fgdt;r}%%v{\\Fgdt;n}3.2{\\Fgdt;m}%%v%%v%%v%%v")
        return

     def addLeaders(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "LEADERs", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Define an annotation block -- A circle with radius 0.5 */
        #*********************************************************************/
        pBlocks = pDb.getBlockTableId().safeOpenObject(kForWrite)
        pAnnoBlock = OdDbBlockTableRecord.createObject()
        pAnnoBlock.setName("AnnoBlock")
        annoBlockId = pBlocks.add(pAnnoBlock)
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(bBTR.database())
        pAnnoBlock.appendOdDbEntity(pCircle)
        center = OdGePoint3d(0.5, 0, 0)
        pCircle.setCenter(center)
        pCircle.setRadius(0.5)
        
        #*********************************************************************/
        # Add a leader with database defaults to the database */
        #*********************************************************************/
        pLeader = OdDbLeader.createObject()
        pLeader.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pLeader)
        #*********************************************************************/
        # Add the vertices */
        #*********************************************************************/
        point.x += w * 1.0 / 8.0
        point.y -= h * 3.0 / 8.0
        pLeader.appendVertex(point)
        point.x += w * 2.0 / 8.0
        point.y += h * 1.0 / 8.0
        pLeader.appendVertex(point)
        
        #*********************************************************************/
        # Insert the annotation */
        #*********************************************************************/
        pBlkRef = OdDbBlockReference.createObject()
        blkRefId = bBTR.appendOdDbEntity(pBlkRef)
        pBlkRef.setBlockTableRecord(annoBlockId)
        pBlkRef.setPosition(point)
        pBlkRef.setScaleFactors(OdGeScale3d(0.375, 0.375, 0.375))
        
        #*********************************************************************/
        # Attach the Block Reference as annotation to the Leader */
        #*********************************************************************/
        pLeader.attachAnnotation(blkRefId)
        
        #*********************************************************************/
        # Add a leader with database defaults to the database */
        #*********************************************************************/
        pLeader = OdDbLeader.createObject()
        pLeader.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pLeader)
        
        #*********************************************************************/
        # Add the vertices */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        point.x += w * 1.0 / 8.0
        point.y -= h * 5.0 / 8.0
        pLeader.appendVertex(point)
        point.x += w * 1.0 / 8.0
        point.y += h * 1.0 / 8.0
        pLeader.appendVertex(point)
        point.x += w * 1.0 / 8
        
        #*********************************************************************/
        # Set the arrowhead */
        #*********************************************************************/
        pLeader.setDimldrblk("DOT")
        
        #*********************************************************************/
        # Create MText at a 30 degree angle */
        #*********************************************************************/
        pMText = OdDbMText.createObject()
        pMText.setDatabaseDefaults(pDb)
        mTextId = bBTR.appendOdDbEntity(pMText)
        textHeight = 0.15
        textWidth = 1.0
        pMText.setLocation(point)
        pMText.setRotation(self.OdaToRadian(10.0))
        pMText.setTextHeight(textHeight)
        pMText.setWidth(textWidth)
        pMText.setAttachment(OdDbMText.kMiddleLeft)
        pMText.setContents("MText")
        pMText.setTextStyle(styleId)
        
        #*********************************************************************/
        # Set a background color */
        #*********************************************************************/
        cBackground = OdCmColor()
        cBackground.setRGB(255, 255, 0) #// Yellow
        pMText.setBackgroundFillColor(cBackground)
        pMText.setBackgroundFill(True)
        pMText.setBackgroundScaleFactor(2.0)
        
        #*********************************************************************/
        # Attach the MText as annotation to the Leader */
        #*********************************************************************/
        pLeader.attachAnnotation(mTextId)
        
        #*********************************************************************/
        # Add a leader with database defaults to the database */
        #*********************************************************************/
        pLeader = OdDbLeader.createObject()
        bBTR.appendOdDbEntity(pLeader)
        pLeader.setDatabaseDefaults(pDb)
        
        
        #*********************************************************************/
        # Add the vertices */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        point.x += w * 1.0 / 8.0
        point.y -= h * 7.0 / 8.0
        pLeader.appendVertex(point)
        point.x += w * 1.0 / 8.0
        point.y += h * 1.0 / 8.0
        pLeader.appendVertex(point)
        
        #*********************************************************************/
        # Create a Frame Control Feature (Tolerance) */
        #*********************************************************************/
        pTol = OdDbFcf.createObject()
        pTol.setDatabaseDefaults(pDb)
        pTol.setLocation(point)
        pTol.setText("{\\Fgdt;r}%%v{\\Fgdt;n}3.2{\\Fgdt;m}%%v%%v%%v%%v")
        
        #*********************************************************************/
        # Attach the FCF as annotation to the Leader */
        #*********************************************************************/
        pLeader.attachAnnotation(bBTR.appendOdDbEntity(pTol))
        return
     
     def addAlignedDimension(self, btrId, boxRow, boxCol, layerId, styleId, dimStyleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the labels */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Aligned", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dimension", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the lower-left corner of the box */
        #*********************************************************************/
        point.y -= h
        
        #*********************************************************************/
        # Create a line to be dimensioned */
        #*********************************************************************/
        line1Pt = OdGePoint3d()
        line2Pt = OdGePoint3d()
        line1Pt.x = point.x + w * 0.5 / 8.0
        line1Pt.y = point.y + h * 1.5 / 8.0
        line2Pt = line1Pt + OdGeVector3d(1.5, 2.0, 0.0)
        
        pLine = OdDbLine.createObject()
        pLine.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pLine)
        pLine.setStartPoint(line1Pt)
        pLine.setEndPoint(line2Pt)
        
        #*********************************************************************/
        # Create an aligned dimension and dimension the ends of the line */
        #*********************************************************************/
        pDimension = OdDbAlignedDimension.createObject()
        pDimension.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pDimension)
        
        dimLinePt = OdGePoint3d()
        dimLinePt.x = point.x + w * 3.5 / 8.0
        dimLinePt.y = point.y + h * 2.0 / 8.0
        
        pDimension.setDimensionStyle(dimStyleId)
        pDimension.setXLine1Point(pLine.startPoint())
        pDimension.setXLine2Point(pLine.endPoint())
        pDimension.setDimLinePoint(dimLinePt)
        pDimension.useDefaultTextPosition()
        pDimension.setJogSymbolHeight(1.5)
        return

     def addMLine(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the labels */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "MLINE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the lower-left corner of MLine */
        #*********************************************************************/
        point.x += w / 10.0
        point.y -= h / 2
        
        #*********************************************************************/
        # Create an MLine and add it to the database */
        #*********************************************************************/
        pMLine = OdDbMline.createObject()
        pMLine.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pMLine)
        
        #*********************************************************************/
        # Open the MLineStyle dictionary, and set the style */
        #*********************************************************************/
        pMLDic = pDb.getMLStyleDictionaryId().safeOpenObject()
        pMLine.setStyle(pMLDic.getAt("OdaStandard"))
        
        #*********************************************************************/
        # Add some segments */
        #*********************************************************************/
        point.y -= h / 2.2
        pMLine.appendSeg(point)
        
        point.y += h / 3.0
        pMLine.appendSeg(point)
        
        point.y += h / 5.0
        point.x += w / 4.0
        pMLine.appendSeg(point)
        
        point.x += w / 4.0
        pMLine.appendSeg(point)
        
        point.y += h / 3.0
        pMLine.appendSeg(point)
        
        point.x += w / 3
        pMLine.appendSeg(point)
        
        point.y -= h / 2
        pMLine.appendSeg(point)
        
        point.x -= w / 4
        point.y -= h / 3
        pMLine.appendSeg(point)
        return

     def addArcDimension(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the labels */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Arc", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dimension", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the lower-left corner of the box */
        #*********************************************************************/
        point.y -= h
        
        #*********************************************************************/
        # Create an arc to be dimensioned */
        #*********************************************************************/
        pArc = OdDbArc.createObject()
        pArc.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pArc)
        center = point + OdGeVector3d(w * 1.0 / 8.0, h * 1.0 / 8.0, 0.0)
        pArc.setCenter(center)
        pArc.setStartAngle(self.OdaToRadian(0.0))
        pArc.setEndAngle(self.OdaToRadian(90.0))
        pArc.setRadius(4.0 / math.pi)
        
        
        #*********************************************************************/
        # Create an ArcDimension */
        #*********************************************************************/
        pDimension = OdDbArcDimension.createObject()
        pDimension.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pDimension)
        
        #*********************************************************************/
        # Use the default dim variables */
        #*********************************************************************/
        pDimension.setDatabaseDefaults(pDb)
        
        #*********************************************************************/
        # Set some parameters */
        #*********************************************************************/
        pDimension.setCenterPoint(pArc.center())
        pDimension.setArcPoint(pArc.center() + OdGeVector3d(pArc.radius() + 0.45, 0.0, 0.0))
        
        startPoint = OdGePoint3d()
        pArc.getStartPoint(startPoint)
        pDimension.setXLine1Point(startPoint)
        
        endPoint = OdGePoint3d()
        pArc.getEndPoint(endPoint)
        pDimension.setXLine2Point(endPoint)
        
        pDimension.setArcSymbolType(1)
        return

     def add3dPolyline(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "3D POLYLINE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Add a 3dPolyline to the database */
        #*********************************************************************/
        pPline = OdDb3dPolyline.createObject()
        pPline.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pPline)
        
        #*********************************************************************/
        # Add the vertices */
        #*********************************************************************/
        pos = point
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        
        radius = w * 3.0 / 8.0
        height = 0.0
        theta = 0.0
        
        turns = 4
        segs = 16
        points = segs * turns
        
        deltaR = radius / points
        deltaTheta = math.pi * 2 / segs
        deltaH = 2 * radius / points
        
        vec = OdGeVector3d(radius, 0, 0)
        
        for i in range(0, points):
          pVertex = OdDb3dPolylineVertex.createObject()
          pVertex.setDatabaseDefaults(bBTR.database())
          pPline.appendVertex(pVertex)
          pVertex.setPosition(center + vec)
        
          radius -= deltaR
          height += deltaH
          theta += deltaTheta
          vec = OdGeVector3d(radius, 0, height)
          vec.rotateBy(theta, OdGeVector3d.kZAxis)

        return

     def addMText(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the Block Table Record #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the origin and size of the box #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
     
        #********************************************************************#
        # Add a label #
        #********************************************************************#
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "MTEXT", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Add MText to the database #
        #********************************************************************#
        pMText = OdDbMText.createObject()
        pMText.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pMText)
     
        #********************************************************************#
        # Set some properties #
        #********************************************************************#
        pMText.setLocation(point + OdGeVector3d(w / 8.0, -h * 2.0 / 8.0, 0))
        pMText.setTextHeight(0.4)
        pMText.setAttachment(OdDbMText.kTopLeft)
        pMText.setContents("Sample {\\C1;MTEXT} created by {\\C5;OdWriteEx}")
        pMText.setWidth(w * 6.0 / 8.0)
        pMText.setTextStyle(styleId)
     
     
        #********************************************************************#
        # Add annotation scales #
        #********************************************************************#
        OdDbAnnotativeObjectPE.cast(pMText).setAnnotative(pMText, True)
        contextCollection = bBTR.database().objectContextManager().contextCollection("ACDB_ANNOTATIONSCALES")
        # OdString cast is necessary to avoid incorrect char pointer
        # interpretation as an OdDbObjectContextId (that is essentially void*)
        scale = contextCollection.getContext("1:2")
        if (scale != None):
          OdDbObjectContextInterface.cast(pMText).addContext(pMText, scale)
        return
                
     def addBlockRef(self, btrId, boxRow, boxCol, layerId, styleId, insertId):
        #********************************************************************#
        # Open the Block Table Record #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the origin and size of the box #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        #       w = EntityBoxes.getWidth(boxRow, boxCol)
        #       h = EntityBoxes.getHeight()
     
        #********************************************************************#
        # Add a label #
        #********************************************************************#
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "INSERT", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Insert the Block #
        #********************************************************************#
        bklRefId = self.addInsert(bBTR, insertId, 1.0, 1.0)
     
        #********************************************************************#
        # Open the insert #
        #********************************************************************#
        pBlkRef = bklRefId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Create a transformation matrix for the block and attributes #
        #********************************************************************#
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        blkXfm = OdGeMatrix3d()
        blkXfm.setTranslation(insPoint.asVector())
        pBlkRef.transformBy(blkXfm)
     
        #********************************************************************#
        # Scan the block definition for non-constant attribute definitions #
        # and use them as templates for attributes #
        #********************************************************************#
        pBlockDef = insertId.safeOpenObject()
        pIter = pBlockDef.newIterator()
        pIter.start()
        while(not pIter.done()):
          pEntity = pIter.entity()
          pAttDef = OdDbAttributeDefinition.cast(pEntity)
          if (pAttDef != None and (not pAttDef.isConstant())):
            pAtt = OdDbAttribute.createObject()
            pAtt.setDatabaseDefaults(bBTR.database())
            pBlkRef.appendAttribute(pAtt)
            pAtt.setPropertiesFrom(pAttDef, False)
            pAtt.setAlignmentPoint(pAttDef.alignmentPoint())
            pAtt.setHeight(pAttDef.height())
            pAtt.setHorizontalMode(pAttDef.horizontalMode())
            pAtt.setNormal(pAttDef.normal())
            pAtt.setOblique(pAttDef.oblique())
            pAtt.setPosition(pAttDef.position())
            pAtt.setRotation(pAttDef.rotation())
            pAtt.setTextString(pAttDef.textString())
            pAtt.setTextStyle(pAttDef.textStyle())
            pAtt.setWidthFactor(pAttDef.widthFactor())
     
            #****************************************************************#
            # Specify a new value for the attribute #
            #****************************************************************#
            pAtt.setTextString("The Value")
     
            #****************************************************************#
            # Transform it as the block was transformed #
            #****************************************************************#
            pAtt.transformBy(blkXfm)
          pIter.step()
        return
     
     def addInsert(self, bBTR, btrId, xscale, yscale):
        #********************************************************************#
        # Add the block reference to the BlockTableRecord #
        #********************************************************************#
        pBlkRef = OdDbBlockReference.createObject()
        pBlkRef.setDatabaseDefaults(bBTR.database())
        brefId = bBTR.appendOdDbEntity(pBlkRef)
     
        #********************************************************************#
        # Set some properties #
        #********************************************************************#
        pBlkRef.setBlockTableRecord(btrId)
        pBlkRef.setScaleFactors(OdGeScale3d(xscale, yscale, 1.0))
        return brefId
        
     def addRadialDimension(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        #  w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the labels #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Radial", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dimension", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create a circle to be dimensioned #
        #********************************************************************#
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pCircle)
        pCircle.setCenter(point + OdGeVector3d(0.625, h * 3.0 / 8.0, 0))
        pCircle.setRadius(0.5)
     
        #********************************************************************#
        # Create a Radial Dimension #
        #********************************************************************#
        pDimension = OdDbRadialDimension.createObject()
        pDimension.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pDimension)
        pDimension.setCenter(pCircle.center())
        chordVector = OdGeVector3d(pCircle.radius(), 0.0, 0.0)
        chordVector.rotateBy(self.OdaToRadian(75.0), OdGeVector3d.kZAxis)
        pDimension.setChordPoint(pDimension.center() + chordVector)
        pDimension.setLeaderLength(0.125)
        pDimension.useDefaultTextPosition()
        return
        
     def add3dFace(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "3DFACE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create a 3D Face #
        #********************************************************************#
        pFace = OdDbFace.createObject()
        pFace.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pFace)
     
        pFace.setVertexAt(0, point + OdGeVector3d(w * 1.0 / 8.0, h * 1.0 / 8.0, 0.0))
        pFace.setVertexAt(1, point + OdGeVector3d(w * 7.0 / 8.0, h * 1.0 / 8.0, 0.0))
        pFace.setVertexAt(2, point + OdGeVector3d(w * 7.0 / 8.0, h * 6.0 / 8.0, 0.0))
        pFace.setVertexAt(3, point + OdGeVector3d(w * 1.0 / 8.0, h * 6.0 / 8.0, 0.0))
        return
        
     def addRText(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        #  h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        point += self.m_textOffset
        self.addTextEnt(bBTR, point, point,
          "RTEXT", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Create RText DIESEL expression with no MText sequences #
        #********************************************************************#
     
        pRText = RText.createObject()
        pRText.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pRText)
     
        point += self.m_textLine + self.m_textLine
        point.x += w / 16.0
        pRText.setHeight(self.m_textSize)
        pRText.setPoint(point)
        pRText.setRotAngle(0.0)
        pRText.setToExpression(True)
        pRText.enableMTextSequences(False)
        pRText.setStringContents("Expression: 123{\\C5;456}")
        pRText.setTextStyle(styleId)
     
        #********************************************************************#
        # Create RText DIESEL expression with MText sequences #
        #********************************************************************#
        pRText = RText.createObject()
        pRText.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pRText)
     
        point += self.m_textLine
        pRText.setHeight(self.m_textSize)
        pRText.setPoint(point)
        pRText.setRotAngle(0.0)
        pRText.setToExpression(True)
        pRText.enableMTextSequences(True)
        pRText.setStringContents("Expression: 123{\\C5;456}")
        pRText.setTextStyle(styleId)
     
        #********************************************************************#
        # Create RText External with no MText sequences #
        #********************************************************************#
        pRText = RText.createObject()
        pRText.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pRText)
     
        point += self.m_textLine
        pRText.setHeight(self.m_textSize)
        pRText.setPoint(point)
        pRText.setRotAngle(0.0)
        pRText.setToExpression(False)
        pRText.enableMTextSequences(False)
        pRText.setStringContents("OdWriteEx.txt")
        pRText.setTextStyle(styleId)
     
        #********************************************************************#
        # Create RText External with MText sequences #
        #********************************************************************#
        pRText = RText.createObject()
        pRText.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pRText)
     
        point += self.m_textLine
        pRText.setHeight(self.m_textSize)
        pRText.setPoint(point)
        pRText.setRotAngle(0.0)
        pRText.setToExpression(False)
        pRText.enableMTextSequences(True)
        pRText.setStringContents("OdWriteEx.txt")
        pRText.setTextStyle(styleId)
        return
        
     def addHatches(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        #  h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        delta = w / 12.0
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "HATCHs", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Create a rectangular Hatch with a circular hole #
        #********************************************************************#
        pHatch = OdDbHatch.createObject()
        pHatch.setDatabaseDefaults(pDb)
        whiteHatchId = bBTR.appendOdDbEntity(pHatch)
     
        #********************************************************************#
        # Set some properties #
        #********************************************************************#
        pHatch.setAssociative(False)
        pHatch.setPattern(OdDbHatch.kPreDefined, "SOLID")
        pHatch.setHatchStyle(OdDbHatch.kNormal)
     
        #********************************************************************#
        # Define the outer loop with an OdGePolyline2d #
        #********************************************************************#
        vertexPts = OdGePoint2dArray()
        vertexPts.resize(4,OdGePoint2d.kOrigin)
        vertexBulges = OdGeDoubleArray()
        vertexPts.At(0).set(point.x + delta, point.y - delta)
        vertexPts.At(1).set(point.x + delta * 5, point.y - delta)
        vertexPts.At(2).set(point.x + delta * 5, point.y - delta * 5)
        vertexPts.At(3).set(point.x + delta, point.y - delta * 5)
        pHatch.appendLoop((OdDbHatch.kExternal | OdDbHatch.kPolyline),
          vertexPts, vertexBulges)
     
     
        #********************************************************************#
        # Define an inner loop with an array of edges #
        #********************************************************************#
        cenPt = OdGePoint2d(point.x + delta * 3, point.y - delta * 3)
        cirArc = OdGeCircArc2d()
        cirArc.setCenter(cenPt)
        cirArc.setRadius(delta)
        cirArc.setAngles(0.0, math.pi * 2)
        edgePtrs = EdgeArray()
        cirArc.thisown = False #Before push pbject to C++ container need change owner
        edgePtrs.push_back(cirArc)
        pHatch.appendLoop(OdDbHatch.kDefault, edgePtrs)
     
        #********************************************************************#
        # Create a circular Hatch #
        #********************************************************************#
        pHatch = OdDbHatch.createObject()
        pHatch.setDatabaseDefaults(pDb)
        redHatchId = bBTR.appendOdDbEntity(pHatch)
     
        #********************************************************************#
        # Set some properties #
        #********************************************************************#
        pHatch.setAssociative(False)
        pHatch.setPattern(OdDbHatch.kPreDefined, "SOLID")
        pHatch.setHatchStyle(OdDbHatch.kNormal)
        col = OdCmColor()
        col.setRGB(255, 0, 0)
        pHatch.setColor(col)
     
        #********************************************************************#
        # Define an outer loop with an array of edges #
        #********************************************************************#
        cirArc = OdGeCircArc2d()
        cirArc.setCenter(cenPt - OdGeVector2d(delta, 0.0))
        cirArc.setRadius(delta)
        cirArc.setAngles(0.0, math.pi * 2)
        edgePtrs.clear()
        cirArc.thisown = False #Before push pbject to C++ container need change owner
        edgePtrs.push_back(cirArc)
        pHatch.appendLoop(OdDbHatch.kDefault, edgePtrs)
     
        #********************************************************************#
        # Create a circular Hatch #
        #********************************************************************#
        pHatch = OdDbHatch.createObject()
        pHatch.setDatabaseDefaults(pDb)
        greenHatchId = bBTR.appendOdDbEntity(pHatch)
     
        pHatch.setAssociative(False)
        pHatch.setPattern(OdDbHatch.kPreDefined, "SOLID")
        pHatch.setHatchStyle(OdDbHatch.kNormal)
        col.setRGB(0, 255, 0)
        pHatch.setColor(col)
     
        #********************************************************************#
        # Define an outer loop with an array of edges #
        #********************************************************************#
        cirArc = OdGeCircArc2d()
        cirArc.setCenter(cenPt - OdGeVector2d(0.0, delta))
        cirArc.setRadius(delta)
        cirArc.setAngles(0.0, math.pi * 2)
        edgePtrs.clear()
        cirArc.thisown = False #Before push pbject to C++ container need change owner
        edgePtrs.push_back(cirArc)
        pHatch.appendLoop(OdDbHatch.kDefault, edgePtrs)

        #********************************************************************#
        # Use the SortentsTable to manipulate draw order #
        #                                                                    #
        # The draw order now is white, red, green #
        #********************************************************************#
        pSET = bBTR.getSortentsTable()
     
        #********************************************************************#
        # Move the green hatch below the red hatch #
        # The draw order now is white, green, red #
        #********************************************************************#
        id = OdDbObjectIdArray()
        id.push_back(greenHatchId)
        pSET.moveBelow(id, redHatchId)
     
        #********************************************************************#
        # Create an associative user-defined hatch #
        #********************************************************************#
        pHatch = OdDbHatch.createObject()
        pHatch.setDatabaseDefaults(pDb)
        hatchId = bBTR.appendOdDbEntity(pHatch)
     
        #********************************************************************#
        # Set some properties #
        #********************************************************************#
        pHatch.setAssociative(True)
        pHatch.setDatabaseDefaults(pDb) # make hatch aware of DB for the next call
        pHatch.setPattern(OdDbHatch.kUserDefined, "_USER")
        pHatch.setPatternSpace(0.125)
        pHatch.setPatternAngle(self.OdaToRadian(30.0))
        pHatch.setPatternDouble(True)
        pHatch.setHatchStyle(OdDbHatch.kNormal)
     
        #********************************************************************#
        # Define the loops #
        #********************************************************************#
        loopIds = OdDbObjectIdArray()
        pEllipse = OdDbEllipse.createObject()
        pEllipse.setDatabaseDefaults(pDb)
        loopIds.push_back(bBTR.appendOdDbEntity(pEllipse))
     
        centerPt = EntityBoxes.getBoxCenter(boxRow, boxCol)
        centerPt.x += delta
        centerPt.y += delta * 1.5
        pEllipse.set(centerPt, OdGeVector3d.kZAxis, OdGeVector3d(delta, 0.0, 0.0), 0.5)
     
        #********************************************************************#
        # Append the loops to the hatch #
        #********************************************************************#
        pHatch.appendLoop(OdDbHatch.kDefault, loopIds)
     
        #********************************************************************#
        # Define a custom hatch pattern "MY_STARS" #
        #********************************************************************#
        stars = OdHatchPattern()
        line = OdHatchPatternLine()
     
        line.m_dLineAngle = 0.0
        line.m_patternOffset = OdGeVector2d(0, 0.866)
        line.m_dashes.push_back(0.5)
        line.m_dashes.push_back(-0.5)
        stars.push_back(line)
        line.m_dLineAngle = 1.0472
        line.m_patternOffset = OdGeVector2d(0, 0.866)
        stars.push_back(line)
        line.m_dLineAngle = 2.0944
        line.m_basePoint = OdGePoint2d(0.25, 0.433)
        line.m_patternOffset = OdGeVector2d(0, 0.866)
        stars.push_back(line)
     
        #********************************************************************#
        # Register the pattern #
        #********************************************************************#
        pDb.appServices().patternManager().appendPattern(OdDbHatch.kCustomDefined,
          "MY_STARS", stars)
     
        #********************************************************************#
        # Create an associative custom defined hatch #
        #********************************************************************#
        pHatch = OdDbHatch.createObject()
        pHatch.setDatabaseDefaults(pDb)
        hatchId = bBTR.appendOdDbEntity(pHatch)
     
        #********************************************************************#
        # Set some properties #
        #********************************************************************#
        pHatch.setAssociative(True)
        pHatch.setDatabaseDefaults(pDb) # make hatch aware of DB for the next call
        pHatch.setPattern(OdDbHatch.kCustomDefined, "MY_STARS")
        pHatch.setPatternScale(0.125)
        pHatch.setPatternAngle(self.OdaToRadian(30.0))
        pHatch.setHatchStyle(OdDbHatch.kNormal)
     
        #********************************************************************#
        # Define the loops #
        #********************************************************************#
        loopIds.clear()
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(pDb)
        loopIds.push_back(bBTR.appendOdDbEntity(pCircle))
     
        centerPt = EntityBoxes.getBoxCenter(boxRow, boxCol)
        centerPt.x += delta * 4.0
        centerPt.y += delta
        pCircle.setCenter(centerPt)
        pCircle.setRadius(delta * 1.5)
     
        #********************************************************************#
        # Append the loops to the hatch #
        #********************************************************************#
        pHatch.appendLoop(OdDbHatch.kDefault, loopIds)
     
        try:
          #******************************************************************#
          # Create an associative predefined hatch #
          #******************************************************************#
          pHatch = OdDbHatch.createObject()
          pHatch.setDatabaseDefaults(pDb)
          hatchId = bBTR.appendOdDbEntity(pHatch)
     
          #******************************************************************#
          # Set some properties #
          #******************************************************************#
          point = EntityBoxes.getBoxCenter(boxRow, boxCol)
          # Set the hatch properties.
          pHatch.setAssociative(True)
          pHatch.setDatabaseDefaults(pDb)# make hatch aware of DB for the next call
          pHatch.setPattern(OdDbHatch.kPreDefined, "ANGLE")
          pHatch.setPatternScale(0.5)
          pHatch.setPatternAngle(0.5) # near 30 degrees
          pHatch.setHatchStyle(OdDbHatch.kNormal)
     
     
          #******************************************************************#
          # Define the loops #
          #******************************************************************#
          loopIds.clear()
          pCircle = OdDbCircle.createObject()
          pCircle.setDatabaseDefaults(pDb)
          loopIds.push_back(bBTR.appendOdDbEntity(pCircle))
          centerPt.x -= delta * 2.0# delta*3 #;
          centerPt.y -= delta * 2.5
          pCircle.setCenter(centerPt)
          pCircle.setRadius(delta * 1.5)
     
          #******************************************************************#
          # Append the loops to the hatch #
          #******************************************************************#
          pHatch.appendLoop(OdDbHatch.kDefault, loopIds)
        except OdError as e:
          print("\n\nException occurred: {0}", e.description())
          print("\nHatch with predefined pattern \"ANGLE\" was not added.")
          print("\nMake sure PAT file with pattern definition is available to Teigha.")
          print("\nPress ENTER to continue...")
        return
        
     def addTextEnts(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
        
        # We want to place all text items into a newly created group, so
        # open the group dictionary here.
        
        #********************************************************************#
        # Open the Group Dictionary #
        #********************************************************************#
        pGroupDic = btrId.database().getGroupDictionaryId().safeOpenObject(kForWrite)
        
        #********************************************************************#
        # Create a new Group #
        #********************************************************************#
        pGroup = OdDbGroup.createObject()
        
        #********************************************************************#
        # Add it to the Group Dictionary #
        #********************************************************************#
        pGroupDic.setAt("OdaGroup", pGroup)
        
        #********************************************************************#
        # Set some properties #
        #********************************************************************#
        pGroup.setName("OdaGroup")
        pGroup.setSelectable(True)
        
        #********************************************************************#
        # Get the Lower-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        dx = w / 16.0
        dy = h / 12.0
        
        textHeight = EntityBoxes.getHeight() / 12.0
        
        #********************************************************************#
        # Add a label #
        #********************************************************************#
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "TEXT", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
        
        #********************************************************************#
        # Add the text entities, and add them to the group #
        #                                                                    #
        # Show the relevant positions and alignment points #
        #********************************************************************#
        position = point + OdGeVector3d(dx, dy * 9.0, 0.0)
        self.addPointEnt(bBTR, position, layerId, pGroup)
        self.addTextEnt2(bBTR, position, position,
          "Left Text", textHeight, kTextLeft, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w / 2.0, dy * 9.0, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Center Text", textHeight, kTextCenter, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w - dx, dy * 9.0, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Right Text", textHeight, kTextRight, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w / 2.0, dy * 8.0, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Middle Text", textHeight, kTextMid, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        position = point + OdGeVector3d(dx, dy * 1, 0.0)
        alignmentPoint = point + OdGeVector3d(w - dx, dy, 0.0)
        self.addPointEnt(bBTR, position, layerId, pGroup)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, position, alignmentPoint,
          "Aligned Text", textHeight, kTextAlign, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        position = point + OdGeVector3d(dx, dy * 5.5, 0.0)
        alignmentPoint = point + OdGeVector3d(w - dx, dy * 5.5, 0.0)
        self.addPointEnt(bBTR, position, layerId, pGroup)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, position, alignmentPoint,
          "Fit Text", textHeight, kTextFit, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        
        #********************************************************************#
        # Start a new box #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol + 1)
        
        #********************************************************************#
        # Add a label #
        #********************************************************************#
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "TEXT", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
        textHeight = h / 16.0
        
        #********************************************************************#
        # Create a new anonymous Group #
        #********************************************************************#
        pGroup = OdDbGroup.createObject()
        
        #********************************************************************#
        # Add it to the Group Dictionary #
        #********************************************************************#
        pGroupDic.setAt("*", pGroup)
        
        #********************************************************************#
        # Set some properties #
        #********************************************************************#
        pGroup.setName("*")
        pGroup.setAnonymous()
        pGroup.setSelectable(True)
        
        #********************************************************************#
        # Add the text entities, and add them to the group #
        #                                                                    #
        # Show the relevant positions and alignment points #
        #********************************************************************#
        alignmentPoint = point + OdGeVector3d(dx, dy * 9.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Top Left", textHeight, kTextLeft, kTextTop, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w / 2.0, dy * 9.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Top Center", textHeight, kTextCenter, kTextTop, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w - dx, dy * 9.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Top Right", textHeight, kTextRight, kTextTop, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(dx, dy * 7.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Middle Left", textHeight, kTextLeft, kTextVertMid, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w / 2.0, dy * 7.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Middle Center", textHeight, kTextCenter, kTextVertMid, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w - dx, dy * 7.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Middle Right", textHeight, kTextRight, kTextVertMid, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(dx, dy * 5.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Baseline Left", textHeight, kTextLeft, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w / 2.0, dy * 5.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Baseline Center", textHeight, kTextCenter, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w - dx, dy * 5.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Baseline Right", textHeight, kTextRight, kTextBase, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(dx, dy * 3.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Bottom Left", textHeight, kTextLeft, kTextBottom, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w / 2.0, dy * 3.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
          "Bottom Center", textHeight, kTextCenter, kTextBottom, OdDbObjectId.kNull, styleId, pGroup)
        
        alignmentPoint = point + OdGeVector3d(w - dx, dy * 3.5, 0.0)
        self.addPointEnt(bBTR, alignmentPoint, layerId, pGroup)
        self.addTextEnt2(bBTR, alignmentPoint, alignmentPoint,
             "Bottom Right", textHeight, kTextRight, kTextBottom, OdDbObjectId.kNull, styleId, pGroup)
        return
        
     def addSolid(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "SOLID", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create a Solid #
        #********************************************************************#
        pSolid = OdDbSolid.createObject()
        pSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pSolid)
     
        pSolid.setPointAt(0, point + OdGeVector3d(w * 1.0 / 8.0, h * 1.0 / 8.0, 0.0))
        pSolid.setPointAt(1, point + OdGeVector3d(w * 7.0 / 8.0, h * 1.0 / 8.0, 0.0))
        pSolid.setPointAt(2, point + OdGeVector3d(w * 1.0 / 8.0, h * 6.0 / 8.0, 0.0))
        pSolid.setPointAt(3, point + OdGeVector3d(w * 7.0 / 8.0, h * 6.0 / 8.0, 0.0))
        return
        
     def addDimAssoc(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the labels #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Associative", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dimension", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create a line to be dimensioned #
        #********************************************************************#
        line1Pt = OdGePoint3d()
        line1Pt.x = point.x + w * 1.0 / 8.0
        line1Pt.y = point.y + h * 2.0 / 8.0
        line2Pt = OdGePoint3d()
        line2Pt.x = line1Pt.x + 3.75
        line2Pt.y = point.y + h * 7.0 / 8.0
     
        pLine = OdDbLine.createObject()
        pLine.setDatabaseDefaults(pDb)
        lineId = bBTR.appendOdDbEntity(pLine)
        pLine.setStartPoint(line1Pt)
        pLine.setEndPoint(line2Pt)
     
        #********************************************************************#
        # Create a rotated dimension and dimension the ends of the line #
        #********************************************************************#
        pDimension = OdDbRotatedDimension.createObject()
        pDimension.setDatabaseDefaults(pDb)
        dimensionId = bBTR.appendOdDbEntity(pDimension)
     
        dimLinePt = OdGePoint3d()
        dimLinePt.x = point.x + w / 2.0
        dimLinePt.y = point.y + h * 1.0 / 8.0
        pDimension.setDatabaseDefaults(pDb)
        pDimension.setXLine1Point(pLine.startPoint())
        pDimension.setXLine2Point(pLine.endPoint())
        pDimension.setDimLinePoint(dimLinePt)
        pDimension.useDefaultTextPosition()
        pDimension.createExtensionDictionary()
     
        #********************************************************************#
        # Create an associative dimension #
        #********************************************************************#
        pDimAssoc = OdDbDimAssoc.createObject()
     
        #********************************************************************#
        # Associate the associative dimension with the rotated dimension by #
        # adding it to the extension dictionary of the rotated dimension #
        #********************************************************************#
        pDict = pDimension.extensionDictionary().safeOpenObject(kForWrite)
        dimAssId = pDict.setAt("ACAD_DIMASSOC", pDimAssoc)
     
        #********************************************************************#
        # Associate the rotated dimension with the associative dimension #
        #********************************************************************#
        pDimAssoc.setDimObjId(dimensionId)
        pDimAssoc.setRotatedDimType(OdDbDimAssoc.kUnknown)
     
        #********************************************************************#
        # Attach the line to the associative dimension #
        #********************************************************************#
        pointRef = OdDbOsnapPointRef.createObject()
        pointRef.setPoint(pLine.startPoint())
        pointRef.setOsnapType(kOsModeStart)
        pointRef.setNearPointParam(0.0)
     
        pointRef.mainEntity().objectIds().push_back(lineId)
        pointRef.mainEntity().subentId().setType(kVertexSubentType)
        pDimAssoc.setPointRef(OdDbDimAssoc.kXline1Point, pointRef)
     
        pointRef = OdDbOsnapPointRef.createObject()
        pointRef.setPoint(pLine.endPoint())
        pointRef.setOsnapType(kOsModeEnd)
        pointRef.setNearPointParam(1.0)
     
        pointRef.mainEntity().objectIds().push_back(lineId)
        pointRef.mainEntity().subentId().setType(kEdgeSubentType)
     
        pDimAssoc.setPointRef(OdDbDimAssoc.kXline2Point, pointRef)
     
        #********************************************************************#
        # Add Persistent reactors from the rotated dimension and the line #
        # to the associative dimension #
        #********************************************************************#
        pDimension.addPersistentReactor(dimAssId)
        pLine.addPersistentReactor(dimAssId)
        return
        
     def addRay(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        #  w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "RAY", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create a Ray from the center of the box and passing through #
        # the lower-left corner of the box #
        #********************************************************************#
        pRay = OdDbRay.createObject()
        pRay.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pRay)
     
        basePoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        unitDir = (point - basePoint).normalize()
     
        pRay.setBasePoint(basePoint)
        pRay.setUnitDir(unitDir)
        return
        
     def add3PointAngularDimension(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the labels #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "3 Point Angular", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dimension", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create an arc to be dimensioned #
        #********************************************************************#
        pArc = OdDbArc.createObject()
        pArc.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pArc)
        center = point + OdGeVector3d(w * 1.0 / 8.0, h * 1.0 / 8.0, 0.0)
        pArc.setCenter(center)
        pArc.setStartAngle(self.OdaToRadian(0.0))
        pArc.setEndAngle(self.OdaToRadian(90.0))
        pArc.setRadius(w * 3.0 / 8.0)
     
        #********************************************************************#
        # Create 3 point angular dimension #
        #********************************************************************#
        pDimension = OdDb3PointAngularDimension.createObject()
        pDimension.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pDimension)
     
        #********************************************************************#
        # Use the default dim variables #
        #********************************************************************#
        pDimension.setDatabaseDefaults(pDb)
     
        #********************************************************************#
        # Set some parameters #
        #********************************************************************#
        pDimension.setCenterPoint(pArc.center())
        pDimension.setArcPoint(pArc.center() + OdGeVector3d(pArc.radius() + 0.45, 0.0, 0.0))
     
        startPoint = OdGePoint3d()
        pArc.getStartPoint(startPoint)
        pDimension.setXLine1Point(startPoint)
     
        endPoint = OdGePoint3d()
        pArc.getEndPoint(endPoint)
        pDimension.setXLine2Point(endPoint)
        return
        
     def addOrdinateDimensions(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the labels #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Ordinate", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dimension", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        dx = w / 8.0
        dy = h / 8.0
        #********************************************************************#
        # Create a line to be dimensioned #
        #********************************************************************#
        pLine = OdDbLine.createObject()
        pLine.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pLine)
     
        point1 = point + OdGeVector3d(dx, dy, 0.0)
        point2 = point1 + OdGeVector3d(0.0, 1.5, 0)
        pLine.setStartPoint(point1)
        pLine.setEndPoint(point2)
     
        #********************************************************************#
        # Create the base ordinate dimension #
        #********************************************************************#
        pDimension = OdDbOrdinateDimension.createObject()
        bBTR.appendOdDbEntity(pDimension)
     
        #********************************************************************#
        # Use the default dim variables #
        #********************************************************************#
        pDimension.setDatabaseDefaults(pDb)
     
        #********************************************************************#
        # Set some parameters #
        #********************************************************************#
     
        startPoint = OdGePoint3d()
        endPoint = OdGePoint3d()
        pLine.getStartPoint(startPoint)
        pLine.getEndPoint(endPoint)
     
        leaderEndPoint = startPoint + OdGeVector3d(3.0 * dx, 0, 0.0)
        pDimension.setOrigin(startPoint)
        pDimension.setDefiningPoint(startPoint)
        pDimension.setLeaderEndPoint(leaderEndPoint)
        pDimension.useYAxis()
     
        #********************************************************************#
        # Create an ordinate dimension #
        #********************************************************************#
        pDimension = OdDbOrdinateDimension.createObject()
        bBTR.appendOdDbEntity(pDimension)
     
        #********************************************************************#
        # Use the default dim variables #
        #********************************************************************#
        pDimension.setDatabaseDefaults(pDb)
     
        #********************************************************************#
        # Set some parameters #
        #********************************************************************#
        leaderEndPoint = endPoint + OdGeVector3d(3.0 * dx, -dy, 0.0)
     
        pDimension.setOrigin(startPoint)
        pDimension.setDefiningPoint(endPoint)
        pDimension.setLeaderEndPoint(leaderEndPoint)
        pDimension.useYAxis()
        return
        
     def addSpline(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "SPLINE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create Spline #
        #********************************************************************#
        pSpline = OdDbSpline.createObject()
        pSpline.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pSpline)
     
        #********************************************************************#
        # Create the fit points #
        #********************************************************************#
     
        dx = w / 8.0
        dy = h / 8.0
     
        fitPoints = OdGePoint3dArray()
        fitPoints.push_back(point + OdGeVector3d(1.0 * dx, 1.0 * dy, 0.0))
        fitPoints.push_back(point + OdGeVector3d(3.0 * dx, 6.0 * dy, 0.0))
        fitPoints.push_back(point + OdGeVector3d(4.0 * dx, 2.0 * dy, 0.0))
        fitPoints.push_back(point + OdGeVector3d(7.0 * dx, 7.0 * dy, 0.0))
     
        pSpline.setFitData(fitPoints,                    # Fit Points
          3,                            # Degree
          0.0,                          # Fit tolerance
          OdGeVector3d(0.0, 0.0, 0.0),  # startTangent
          OdGeVector3d(1.0, 0.0, 0.0)) # endTangent
        return
        
     def addTraces(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "TRACEs", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create a Trace #
        #********************************************************************#
        pTrace = OdDbTrace.createObject()
        pTrace.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pTrace)
     
        dx = w / 8.0
        dy = h / 8.0
        pTrace.setPointAt(0, point + OdGeVector3d(1.0 * dx, 2.0 * dx, 0.0))
        pTrace.setPointAt(1, point + OdGeVector3d(1.0 * dx, 1.0 * dx, 0.0))
        pTrace.setPointAt(2, point + OdGeVector3d(6.0 * dx, 2.0 * dx, 0.0))
        pTrace.setPointAt(3, point + OdGeVector3d(7.0 * dx, 1.0 * dx, 0.0))
     
        #********************************************************************#
        # Create a Trace #
        #********************************************************************#
        pTrace = OdDbTrace.createObject()
        pTrace.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pTrace)
     
        pTrace.setPointAt(0, point + OdGeVector3d(6.0 * dx, 2.0 * dx, 0.0))
        pTrace.setPointAt(1, point + OdGeVector3d(7.0 * dx, 1.0 * dx, 0.0))
        pTrace.setPointAt(2, point + OdGeVector3d(6.0 * dx, 7.0 * dy, 0.0))
        pTrace.setPointAt(3, point + OdGeVector3d(7.0 * dx, 7.0 * dy, 0.0))
        return
        
     def addPolyline(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "LWPOLYLINE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create a polyline #
        #********************************************************************#
        pPolyline = OdDbPolyline.createObject()
        pPolyline.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pPolyline)
     
        #********************************************************************#
        # Create the vertices #
        #********************************************************************#
     
        dx = w / 8.0
        dy = h / 8.0
     
        point2d = OdGePoint2d(point.x + 1.5 * dx, point.y + 3.0 * dy)
     
        pPolyline.addVertexAt(0, point2d)
     
        point2d.y -= 0.5 * dy
        pPolyline.addVertexAt(1, point2d)
        pPolyline.setBulgeAt(1, 1.0)
     
        point2d.x += 5.0 * dx
        pPolyline.addVertexAt(2, point2d)
     
        point2d.y += 4.0 * dy
        pPolyline.addVertexAt(3, point2d)
     
        point2d.x -= 1.0 * dx
        pPolyline.addVertexAt(4, point2d)
     
        point2d.y -= 4.0 * dy
        pPolyline.addVertexAt(5, point2d)
        pPolyline.setBulgeAt(5, -1.0)
     
        point2d.x -= 3.0 * dx
        pPolyline.addVertexAt(6, point2d)
     
        point2d.y += 0.5 * dy
        pPolyline.addVertexAt(7, point2d)
     
        pPolyline.setClosed(True)
        return
        
     def addArcText(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        #  w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "ARCALIGNED-", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "TEXT", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
     
        #********************************************************************#
        # Create an arc #
        #********************************************************************#
        pArc = OdDbArc.createObject()
        pArc.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pArc)
     
        #  dx = w / 8.0;
        dy = h / 8.0
     
        center = EntityBoxes.getBoxCenter(boxRow, boxCol) + OdGeVector3d(0.0, -2.0 * dy, 0)
        pArc.setCenter(center)
        pArc.setRadius(3.0 * dy)
        pArc.setStartAngle(self.OdaToRadian(45.0))
        pArc.setEndAngle(self.OdaToRadian(135.0))
     
        #********************************************************************#
        # Create the ArcAlignedText #
        #********************************************************************#
        pArcText = OdDbArcAlignedText.createObject()
        pArcText.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pArcText)
     
        pArcText.setTextString("ArcAligned")
        pArcText.setArcId(pArc.objectId())
        pArcText.setTextStyle(styleId)
        return
        
     def addWipeout(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
     
        #********************************************************************#
        # Get the lower-left corner and center of the box #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the label #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "WIPEOUT", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create a hatch object to be wiped out #
        #********************************************************************#
        pHatch = OdDbHatch.createObject()
        pHatch.setDatabaseDefaults(bBTR.database())
        hatchId = bBTR.appendOdDbEntity(pHatch)
     
        #********************************************************************#
        # Create a hatch object to be wiped out #
        #********************************************************************#
        pHatch.setAssociative(True)
        pHatch.setPattern(OdDbHatch.kUserDefined, "_USER")
        pHatch.setPatternSpace(0.125)
        pHatch.setPatternAngle(0.5) # near 30 degrees
        pHatch.setPatternDouble(True) # Cross hatch
        pHatch.setHatchStyle(OdDbHatch.kNormal)
     
        #********************************************************************#
        # Create an outer loop for the hatch #
        #********************************************************************#
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(bBTR.database())
        loopIds = OdDbObjectIdArray()
        loopIds.push_back(bBTR.appendOdDbEntity(pCircle))
        pCircle.setCenter(center)
        pCircle.setRadius(min(w, h) * 0.4)
        pHatch.appendLoop(OdDbHatch.kDefault, loopIds)
     
        #********************************************************************#
        # Create the wipeout #
        #********************************************************************#
        pWipeout = OdDbWipeout.createObject()
        pWipeout.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pWipeout)
     
        boundary = OdGePoint3dArray()
        boundary.push_back(center + OdGeVector3d(-w * 0.4, -h * 0.4, 0.0))
        boundary.push_back(center + OdGeVector3d(w * 0.4, -h * 0.4, 0.0))
        boundary.push_back(center + OdGeVector3d(0.0, h * 0.4, 0.0))
        boundary.push_back(center + OdGeVector3d(-w * 0.4, -h * 0.4, 0.0))
     
        pWipeout.setBoundary(boundary)
     
        pWipeout.setDisplayOpt(OdDbRasterImage.kShow, True)
        pWipeout.setDisplayOpt(OdDbRasterImage.kClip, True)
        pWipeout.setDisplayOpt(OdDbRasterImage.kShowUnAligned, True)
        pWipeout.setDisplayOpt(OdDbRasterImage.kTransparent, False)
        return
     
     def addRadialDimensionLarge(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the labels #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Radial", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dim Large", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create an arc to be dimensioned #
        #********************************************************************#
        pArc = OdDbArc.createObject()
        pArc.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pArc)
     
        center = point + OdGeVector3d(w * 1.0 / 8.0, h * 1.0 / 8.0, 0.0)
        pArc.setRadius(2.0)
     
        pArc.setCenter(center)
        pArc.setStartAngle(self.OdaToRadian(30.0))
        pArc.setEndAngle(self.OdaToRadian(90.0))
     
        #********************************************************************#
        # Create RadialDimensionLarge #
        #********************************************************************#
        pDimension = OdDbRadialDimensionLarge.createObject()
        bBTR.appendOdDbEntity(pDimension)
     
        #********************************************************************#
        # Use the default dim variables #
        #********************************************************************#
        pDimension.setDatabaseDefaults(pDb)
     
        #********************************************************************#
        # Set some parameters #
        #********************************************************************#

        # The centerPoint of the dimension is the center of the arc
        centerPoint = pArc.center()
     
        # The chordPoint of the dimension is the midpoint of the arc
        v1 = OdGeVector3d(pArc.radius(), 0.0, 0.0)
        v1.rotateBy(0.5 * (pArc.startAngle() + pArc.endAngle()), OdGeVector3d.kZAxis)
        chordPoint = centerPoint + v1
     
        # The overrideCenter is just to the right of the actual center
        overrideCenter = centerPoint + OdGeVector3d(w * 3.0 / 8.0, 0.0, 0.0)
     
        # The jogPoint is halfway between the overrideCenter and the chordCoint
        jogPoint = overrideCenter + (chordPoint - overrideCenter) * 0.5
     
        # The textPosition is along the vector between the centerPoint and the
        # chordPoint.
        textPosition = centerPoint + (chordPoint - centerPoint) * 0.7
     
        jogAngle = self.OdaToRadian(45.0)
     
        pDimension.setCenter(centerPoint)
        pDimension.setChordPoint(chordPoint)
        pDimension.setOverrideCenter(overrideCenter)
        pDimension.setJogPoint(jogPoint)
        pDimension.setTextPosition(textPosition)
        pDimension.setJogAngle(jogAngle)
        return
        
     def add2LineAngularDimension(self, btrId, boxRow, boxCol, layerId, styleId):
        #********************************************************************#
        # Open the BlockTableRecord #
        #********************************************************************#
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
     
        #********************************************************************#
        # Get the Upper-left corner of the box and its size #
        #********************************************************************#
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
     
        #********************************************************************#
        # Add the labels #
        #********************************************************************#
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "2 Line Angular", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dimension", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
     
        #********************************************************************#
        # Get the lower-left corner of the box #
        #********************************************************************#
        point.y -= h
     
        #********************************************************************#
        # Create the lines to be dimensioned #
        #********************************************************************#
        center = point + OdGeVector3d(w * 1.0 / 8.0, h * 1.0 / 8.0, 0.0)
        v1 = OdGeVector3d(w * 1.0 / 8.0, 0.0, 0.0)
        v2 = OdGeVector3d(w * 4.0 / 8.0, 0.0, 0.0)
        v3 = v2 + OdGeVector3d(0.45, 0.0, 0.0)
     
        pLine1 = OdDbLine.createObject()
        pLine1.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pLine1)
        pLine1.setStartPoint(center + v1)
        pLine1.setEndPoint(center + v2)
     
        rot = self.OdaToRadian(75.0)
        v1.rotateBy(rot, OdGeVector3d.kZAxis)
        v2.rotateBy(rot, OdGeVector3d.kZAxis)
     
        pLine2 = OdDbLine.createObject()
        pLine2.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pLine2)
        pLine2.setStartPoint(center + v1)
        pLine2.setEndPoint(center + v2)
     
        #********************************************************************#
        # Create 2 Line Angular Dimensionn #
        #********************************************************************#
        pDimension = OdDb2LineAngularDimension.createObject()
        bBTR.appendOdDbEntity(pDimension)
     
        #********************************************************************#
        # Use the default dim variables #
        #********************************************************************#
        pDimension.setDatabaseDefaults(pDb)
     
        #********************************************************************#
        # Set some parameters #
        #********************************************************************#
     
        v3.rotateBy(rot / 2.0, OdGeVector3d.kZAxis)
        pDimension.setArcPoint(center + v3)
     
        startPoint = OdGePoint3d()
        pLine1.getStartPoint(startPoint)
        pDimension.setXLine1Start(startPoint)
     
        endPoint = OdGePoint3d()
        pLine1.getEndPoint(endPoint)
        pDimension.setXLine1End(endPoint)
     
        #  pDimension.setArcPoint(endPoint + 0.45*(endPoint -
        #  startPoint).normalize())
     
        pLine2.getStartPoint(startPoint)
        pDimension.setXLine2Start(startPoint)
     
        pLine2.getEndPoint(endPoint)
        pDimension.setXLine2End(endPoint)
        return
     
     def addACIS(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)

        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "3DSOLID", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        entities = OdDbEntityPtrArray()
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())
        vv = xfm.getCsOrigin()
        #*********************************************************************/
        # Read the solids in the .sat file */
        #*********************************************************************/
        if (OdDbBody.acisIn("OdWriteEx.sat", entities) == eOk):
          #*******************************************************************/
          # Read the solids in the .sat file */
          #*******************************************************************/
          self.addTextEnt(bBTR,
            point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
            "from SAT file", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)

          for i in range(0,entities.size()):
            p3dSolid = entities.At(i)
            #*****************************************************************/
            # Move the solid into the center of the box */
            #*****************************************************************/
            id_ent = bBTR.appendOdDbEntity(p3dSolid)
            p3dSolid.transformBy(xfm)            
            extents = OdGeExtents3d()
            p3dSolid.getGeomExtents(extents)
            max = extents.maxPoint()


            #*****************************************************************/
            # Each of these entities will later get its own viewport */
            #*****************************************************************/
            self.m_layoutEntities.push_back(id_ent)
        else:
          #*******************************************************************/
          # Create a simple solid */
          #*******************************************************************/
          p3dSolid = OdDb3dSolid.createObject()
          p3dSolid.setDatabaseDefaults(bBTR.database())
          id = bBTR.appendOdDbEntity(p3dSolid)
        
          p3dSolid.createSphere(1.0)
          p3dSolid.transformBy(xfm)
        
          #*******************************************************************/
          # This entity will later get its own viewport */
          #*******************************************************************/
          self.m_layoutEntities.push_back(id)
        return

     def addImage(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Get the lower-left corner of the box */
        #*********************************************************************/
        point.y -= h
        
        #*********************************************************************/
        # Open the Image Dictionary */
        #*********************************************************************/
        imageDictId = OdDbRasterImageDef.createImageDictionary(pDb)
        pImageDict = imageDictId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Create an ImageDef object */
        #*********************************************************************/
        pImageDef = OdDbRasterImageDef.createObject()
        imageDefId = pImageDict.setAt("OdWriteEx", pImageDef)
        
        #*********************************************************************/
        # Set some parameters */
        #*********************************************************************/
        pImageDef.setSourceFileName("OdWriteEx.jpg")
        # Use next line to set image size manually without loading actual
        # raster file.
        # This method sets "dummy" image instead.  It's OK for saving drawing
        # to DXF/DWG.
        # But image will not be rendered/exported to other formats without file
        # saving and opening again
        pImageDef.setImage(OdGiRasterImageDesc.createObject(1024, 650, OdGiRasterImage.kInch))
        
        # Use next line to set size from the actual raster file.
        # This is also required if you are going to render/export the drawing
        # immediately
        # without saving to DWG and loading again
        #pImageDef.image() // Force image loading from file (findFile() should
        #be able to locate the image).
        
        
        #*********************************************************************/
        # Create an Image object */
        #*********************************************************************/
        pImage = OdDbRasterImage.createObject()
        pImage.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pImage)
        
        #*********************************************************************/
        # Set some parameters */
        #*********************************************************************/
        pImage.setImageDefId(imageDefId)
        pImage.setOrientation(point, OdGeVector3d(w, 0, 0),  OdGeVector3d(0.0, h, 0))
        pImage.setDisplayOpt(OdDbRasterImage.kShow, True)
        pImage.setDisplayOpt(OdDbRasterImage.kShowUnAligned, True)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "IMAGE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        return

     def addXRef(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "XREF INSERT", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the lower-left corner of the box */
        #*********************************************************************/
        point.y -= h
        
        #*********************************************************************/
        # Open the block table */
        #*********************************************************************/
        pBlocks = pDb.getBlockTableId().safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Create a BlockTableRecord */
        #*********************************************************************/
        pXRef = OdDbXRefManExt.addNewXRefDefBlock(pDb, "OdWriteEx XRef.dwg", "XRefBlock", False)
        
        #*********************************************************************/
        # Insert the Xref */
        #*********************************************************************/
        xRefId = self.addInsert(bBTR, pXRef.objectId(), 1.0, 1.0)
        
        #*********************************************************************/
        # Open the insert */
        #*********************************************************************/
        pXRefIns = xRefId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Set the insertion point */
        #*********************************************************************/
        pXRefIns.setPosition(point)
        
        #*********************************************************************/
        # Move\Scale XREF to presentation rectangle */
        #*********************************************************************/
        
        extents = OdGeExtents3d()
        if (pXRefIns.getGeomExtents(extents) == eOk & extents.isValidExtents()):
          dScale = min(w / (extents.maxPoint().x - extents.minPoint().x), h * (7.0 / 8.0) / (extents.maxPoint().y - extents.minPoint().y))
          pXRefIns.setScaleFactors(OdGeScale3d(dScale, dScale, 1))
          pt = (extents.minPoint() - point.asVector())
          vvv = pt.asVector() * dScale
          pXRefIns.setPosition(point - vvv)
        return

     def addTable(self, btrId, addedBlockId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        pRecord = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the lower-left corner and center of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Create the Table */
        #*********************************************************************/
        pAcadTable = OdDbTable.createObject()
        tableId = pRecord.appendOdDbEntity(pAcadTable)
        #*********************************************************************/
        # This entity will later get its own viewport */
        #*********************************************************************/
        self.m_layoutEntities.push_back(tableId)
        
        #*********************************************************************/
        # Set the parameters */
        #*********************************************************************/
        pAcadTable.setDatabaseDefaults(pRecord.database())
        pAcadTable.setNumColumns(3)
        pAcadTable.setNumRows(4)
        
        pAcadTable.generateLayout()
        pAcadTable.setColumnWidth(w / pAcadTable.numColumns())
        pAcadTable.setRowHeight(h / pAcadTable.numRows())
        
        pAcadTable.setPosition(point)
        pAcadTable.setTextStyle(styleId)
        
        pAcadTable.setTextHeight(0.500 * pAcadTable.rowHeight(0), kTitleRow)
        pAcadTable.setTextHeight(0.300 * pAcadTable.rowHeight(1), kHeaderRow)
        pAcadTable.setTextHeight(0.250 * pAcadTable.rowHeight(2), kDataRow)
        
        #*********************************************************************/
        # Set the alignments */
        #*********************************************************************/
        for row in range(1,pAcadTable.numRows()):
          for col in range(0,pAcadTable.numColumns()):
            pAcadTable.setAlignment(row, col, kMiddleCenter)
        
        #*********************************************************************/
        # Define the title row */
        #*********************************************************************/
        pAcadTable.mergeCells(0, 0, 0, pAcadTable.numColumns() - 1)
        pAcadTable.setTextString(0, 0, "Title of TABLE")
        
        #*********************************************************************/
        # Define the header row */
        #*********************************************************************/
        pAcadTable.setTextString(1, 0, "Header0")
        pAcadTable.setTextString(1, 1, "Header1")
        pAcadTable.setTextString(1, 2, "Header2")
        
        #*********************************************************************/
        # Define the first data row */
        #*********************************************************************/
        pAcadTable.setTextString(2, 0, "Data0")
        pAcadTable.setTextString(2, 1, "Data1")
        pAcadTable.setTextString(2, 2, "Data2")
        
        #*********************************************************************/
        # Define the second data row */
        #*********************************************************************/
        pAcadTable.setCellType(3, 0, kBlockCell)
        pAcadTable.setBlockTableRecordId(3, 0, addedBlockId)
        pAcadTable.setBlockScale(3, 0, 1.0)
        pAcadTable.setAutoScale(3, 0, True)
        pAcadTable.setBlockRotation(3, 0, 0.0)
        
        pAcadTable.setTextString(3, 1, "<-Block Cell.")
        
        pAcadTable.setCellType(3, 2, kBlockCell)
        pAcadTable.setBlockTableRecordId(3, 2, addedBlockId)
        pAcadTable.setAutoScale(3, 2, True)
        pAcadTable.setBlockRotation(3, 2, self.OdaToRadian(30.0))
        
        pAcadTable.recomputeTableBlock()
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(pRecord,
          point + self.m_textOffset, point + self.m_textOffset,
          "ACAD_TABLE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        return

     def addDiametricDimension(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        #  w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the labels */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Diametric", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Dimension", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the lower-left corner of the box */
        #*********************************************************************/
        point.y -= h
        
        #*********************************************************************/
        # Create a circle to be dimensioned */
        #*********************************************************************/
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pCircle)
        pCircle.setCenter(point + OdGeVector3d(0.625, h * 3.0 / 8.0, 0))
        pCircle.setRadius(0.5)
        
        #*********************************************************************/
        # Create a Diametric Dimension */
        #*********************************************************************/
        pDimension = OdDbDiametricDimension.createObject()
        pDimension.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pDimension)
        
        chordVector = OdGeVector3d(pCircle.radius(), 0.0, 0.0)
        chordVector.rotateBy(self.OdaToRadian(75.0), OdGeVector3d.kZAxis)
        
        pDimension.setChordPoint(pCircle.center() + chordVector)
        pDimension.setFarChordPoint(pCircle.center() - chordVector)
        pDimension.setLeaderLength(0.125)
        pDimension.useDefaultTextPosition()
        return

     def addShape(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the labels */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Shape", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the center of the box */
        #*********************************************************************/
        pCenter = EntityBoxes.getBoxCenter(boxRow, boxCol)
        
        #*********************************************************************/
        # Create a Shape */
        #*********************************************************************/
        pShape = OdDbShape.createObject()
        pShape.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pShape)
        size = w * 3.0 / 8.0
        pCenter.y -= size
        pShape.setSize(size)
        pShape.setPosition(pCenter)
        pShape.setRotation(self.OdaToRadian(90.0))
        pShape.setName("CIRC1")
        return

     def addMInsert(self, btrId, boxRow, boxCol, layerId, styleId,insertId):
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR, point + self.m_textOffset, point + self.m_textOffset,
            "MInsert", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the lower-left corner of the box */
        #*********************************************************************/
        point.y -= h
        
        #*********************************************************************/
        # Add MInsert to the database */
        #*********************************************************************/
        pMInsert = OdDbMInsertBlock.createObject()
        pMInsert.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pMInsert)
        
        #*********************************************************************/
        # Set some Parameters */
        #*********************************************************************/
        pMInsert.setBlockTableRecord(insertId)
        insPnt = point + OdGeVector3d(w * 2.0 / 8.0, h * 2.0 / 8.0, 0.0)
        pMInsert.setPosition(insPnt)
        pMInsert.setScaleFactors(OdGeScale3d(2.0 / 8.0))
        pMInsert.setRows(2)
        pMInsert.setColumns(3)
        pMInsert.setRowSpacing(h * 4.0 / 8.0)
        pMInsert.setColumnSpacing(w * 2.0 / 8.0)
        return

     def addXline(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        #  w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "XLINE", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Get the lower-left corner of the box */
        #*********************************************************************/
        point.y -= h
        
        #*********************************************************************/
        # Create a Ray from the center of the box and passing through */
        # the lower-left corner of the box */
        #*********************************************************************/
        pXline = OdDbXline.createObject()
        pXline.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pXline)
        
        basePoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        unitDir = (point - basePoint).normalize()
        
        pXline.setBasePoint(basePoint)
        pXline.setUnitDir(unitDir)
        return

     def addCustomObjects(self, pDb):
        #Open the main dictionary
        pMain = pDb.getNamedObjectsDictionaryId().safeOpenObject(kForWrite)
        
        # Create the new dictionary.
        pOdtDic = OdDbDictionary.createObject()
        
        # Add new dictionary to the main dictionary.
        dicId = pMain.setAt("ODA_OBJECTS", pOdtDic)
        
        # Create a new xrecord object.
        pXRec = OdDbXrecord.createObject()
        
        # Add the xrecord the owning dictionary.
        xrId = pOdtDic.setAt("PROPERTIES_1", pXRec)
        
        temp = pRb = OdResBuf.newRb(1000)
        temp.setString("Sample XRecord Data")
        
        temp = self.appendXDataPair(temp, 40)
        temp.setDouble(3.14159)
        
        temp = self.appendXDataPair(temp, 70)
        temp.setInt16(312)
        
        pXRec.setFromRbChain(pRb)
        return
     
     def appendXDataPair(self,pCurr, code):
        pCurr.setNext(OdResBuf.newRb(code))
        return pCurr.next()

     def addTextWithField(self, btrId, boxRow, boxCol, layerId, styleId, noteStyleId):
        pRecord = btrId.safeOpenObject(kForWrite)
        
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #  dx = w/16.0;
        #  dy = h/12.0;
        
        textPos1 = OdGePoint3d(point.x,point.y,point.z)
        textPos1.x += w / 15.0
        textPos1.y -= h / 3.0
        
        textPos2 = OdGePoint3d(point.x,point.y,point.z)
        textPos2.x += w / 15.0
        textPos2.y -= 2.0 * h / 3.0
        
        textHeight = EntityBoxes.getHeight() / 12.0
        
        #*********************************************************************/
        # Prepare the text entities */
        #*********************************************************************/
        pText1 = OdDbText.createObject()
        textId = pRecord.appendOdDbEntity(pText1)
        pText2 = OdDbText.createObject()
        textId2 = pRecord.appendOdDbEntity(pText2)
        
        pText1.setPosition(textPos1)
        pText1.setHeight(textHeight)
        pText2.setPosition(textPos2)
        pText2.setHeight(textHeight)
        if (not styleId.isNull()):
          pText1.setTextStyle(styleId)
          pText2.setTextStyle(styleId)
        
        #*********************************************************************/
        # Create field objects */
        #*********************************************************************/
        pTextField1 = OdDbField.createObject()
        pField1_1 = OdDbField.createObject()
        
        pTextField2 = OdDbField.createObject()
        pField2_1 = OdDbField.createObject()
        pField2_2 = OdDbField.createObject()
        
        #*********************************************************************/
        # Set field objects */
        #*********************************************************************/
        textFldId1 = pText1.setField("TEXT", pTextField1)
        fldId1_1 = pTextField1.setField("", pField1_1)
        
        textFldId2 = pText2.setField("TEXT", pTextField2)
        
        #*********************************************************************/
        # Set field property */
        #*********************************************************************/
        
        pField1_1.setEvaluationOption(OdDbField.kAutomatic)
        fc1 = "\\AcVar Comments"
        pField1_1.setFieldCode(fc1)
        
        pTextField1.setEvaluationOption(OdDbField.kAutomatic)
        fc2 = "%<\\_FldIdx 0>%"
        pTextField1.setFieldCode(fc2, OdDbField.kTextField | OdDbField.kPreserveFields)
        
        #*********************************************************************/
        # Evaluate field */
        #*********************************************************************/
        pField1_1.evaluate(OdDbField.kDemand)
        
        fldArray = OdDbFieldArray()
        fldArray.push_back(pField2_1)
        fldArray.push_back(pField2_2)
        
        pTextField2.setEvaluationOption(OdDbField.kAutomatic)
        fc3 = "Date %<\\_FldIdx 0>% Time %<\\_FldIdx 1>%"
        pTextField2.setFieldCode(fc3, OdDbField.kTextField, fldArray)
        
        pField2_1.setEvaluationOption(OdDbField.kAutomatic)
        fc4 = "\\AcVar Date \\f M/dd/yyyy"
        pField2_1.setFieldCode(fc4)
        
        pField2_2.setEvaluationOption(OdDbField.kAutomatic)
        fc5 = "\\AcVar Date \\f h:mm tt"
        pField2_2.setFieldCode(fc5)
        
        #*********************************************************************/
        # Evaluate fields */
        #*********************************************************************/
        pField2_1.evaluate(OdDbField.kDemand)
        pField2_2.evaluate(OdDbField.kDemand)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(pRecord,
          point + self.m_textOffset, point + self.m_textOffset,
          "FIELDS", self.m_textSize, kTextLeft, kTextTop, layerId, noteStyleId)
        return

     def addOLE2FrameFromFile(self, btrId, boxRow, boxCol, fileName, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        pBlock = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the lower-left corner and center of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        pOle2Frame = None
        #*********************************************************************/
        # Create an ole2frame entity from arbitrary file using Windows OLE RT*/
        #*********************************************************************/
        # pOle2Frame = OleWrappers.CreateFromFile(inCurrentFolder(fileName))
        
        #*********************************************************************/
        # Create an ole2frame entity in a platform-neutral manner */
        # Important: open file that is a compound document.  */
        # OLE2 frame can't be created from arbitrary file such way.  */
        #*********************************************************************/
        
        try:
          pFile = odSystemServices().createFile(fileName + ".ole", kFileRead, kShareDenyReadWrite, kOpenExisting)
        
          pOle2Frame = OdDbOle2Frame.createObject()
        
          pHandler = pOle2Frame.getItemHandler()
        
          pHandler.setCompoundDocument(pFile.length(), pFile)
        
          pHandler.setDrawAspect(OdOleItemHandler.kContent)
        
          pOle2Frame.unhandled_setHimetricSize(6879, 3704)
        except OdError:
          print("Ole file: {0} not found, no OdDbOle2Frame entity created.\n", fileName)
 
        if (pOle2Frame != None):
          pOle2Frame.setDatabaseDefaults(pBlock.database())
          pBlock.appendOdDbEntity(pOle2Frame)
        
          #*********************************************************************/
          # Add the label */
          #*********************************************************************/
          self.addTextEnt(pBlock, point + self.m_textOffset, point + self.m_textOffset,
            "OLE2: " + pOle2Frame.getUserType(), self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        
          #*********************************************************************/
          # Inscribe OLE frame in entity box */
          #*********************************************************************/
          h += self.m_textOffset.y
          h -= (self.m_textSize * 1.5)
          center.y += (self.m_textOffset.y / 2.0)
          center.y -= (self.m_textSize * 1.5 / 2.0)
        
          h *= 0.95
          w *= 0.95
        
          h /= 2.0
          w /= 2.0
        
          oh = pOle2Frame.unhandled_himetricHeight()
          ow = pOle2Frame.unhandled_himetricWidth()
          if (oh / ow < h / w):
            h = w * oh / ow
          else:
            w = h * ow / oh
        
          rect = OdRectangle3d()
          rect.upLeft.x = rect.lowLeft.x = center.x - w
          rect.upLeft.y = rect.upRight.y = center.y + h
          rect.upRight.x = rect.lowRight.x = center.x + w
          rect.lowLeft.y = rect.lowRight.y = center.y - h
          pOle2Frame.setPosition(rect)
        return
 
     def addBox(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Box", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        p3dSolid = OdDb3dSolid.createObject()
        p3dSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(p3dSolid)
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())

        p3dSolid.createBox(w * 6.0 / 8.0, h * 6.0 / 8.0, w * 6.0 / 8.0)
        p3dSolid.transformBy(xfm)
        return
 
     def addFrustum(self, btrId, boxRow, boxCol, layerId, styleId):
        #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Frustum", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        p3dSolid = OdDb3dSolid.createObject()
        p3dSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(p3dSolid)
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())

        p3dSolid.createFrustum(w * 6.0 / 8.0, w * 3.0 / 8.0, h * 3.0 / 8.0, w * 1.0 / 8.0)
        p3dSolid.transformBy(xfm)
        return
 
     def addSphere(self, btrId, boxRow, boxCol, layerId, styleId):
                #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Sphere", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        p3dSolid = OdDb3dSolid.createObject()
        p3dSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(p3dSolid)
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())
        
        p3dSolid.createSphere(w * 3.0 / 8.0)
        p3dSolid.transformBy(xfm)
        return
 
     def addTorus(self, btrId, boxRow, boxCol, layerId, styleId):
           #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Torus", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        p3dSolid = OdDb3dSolid.createObject()
        p3dSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(p3dSolid)
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())

        p3dSolid.createTorus(w * 2.0 / 8.0, w * 1.0 / 8.0)
        p3dSolid.transformBy(xfm)
        return
 
     def addWedge(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Wedge", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        p3dSolid = OdDb3dSolid.createObject()
        p3dSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(p3dSolid)
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())

        p3dSolid.createWedge(w * 6.0 / 8.0, h * 6.0 / 8.0, w * 6.0 / 8.0)
        p3dSolid.transformBy(xfm)
        return
 
     def addRegion(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Region", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Create a Circle */
        #*********************************************************************/
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(bBTR.database())
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        pCircle.setCenter(center)
        pCircle.setRadius(w * 3.0 / 8.0)
        
        
        #*********************************************************************/
        # Add it to the array of curves */
        #*********************************************************************/
        curveSegments = OdRxObjectPtrArray()
        curveSegments.push_back(pCircle)
        
        #*********************************************************************/
        # Create the region */
        #*********************************************************************/
        regions = OdRxObjectPtrArray()
        res = OdDbRegion.createFromCurves(curveSegments, regions)
        
        #*********************************************************************/
        # Append it to the block table record */
        #*********************************************************************/
        if (res == eOk):
          bBTR.appendOdDbEntity(OdDbEntity.cast(regions.At(0)))
        return
 
     def addExtrusion(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
 
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Extrusion", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        p3dSolid = OdDb3dSolid.createObject()
        p3dSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(p3dSolid)
        
        #*********************************************************************/
        # Create a Circle */
        #*********************************************************************/
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(bBTR.database())
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        pCircle.setCenter(center)
        pCircle.setRadius(w * 3.0 / 8.0)
        
        #*********************************************************************/
        # Add it to the array of curves */
        #*********************************************************************/
        curveSegments = OdRxObjectPtrArray()
        curveSegments.push_back(pCircle)
        
        #*********************************************************************/
        # Create a region */
        #*********************************************************************/
        regions = OdRxObjectPtrArray()
        OdDbRegion.createFromCurves(curveSegments, regions)
        
        #*********************************************************************/
        # Extrude the region */
        #*********************************************************************/
        p3dSolid.extrude(OdDbRegion.cast(regions.At(0)), w * 6.0 / 8.0)
        return
 
     def addSolRev(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
 
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Solid of", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        self.addTextEnt(bBTR,
          point + self.m_textOffset + self.m_textLine, point + self.m_textOffset + self.m_textLine,
          "Revolution", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        p3dSolid = OdDb3dSolid.createObject()
        p3dSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(p3dSolid)
        
        #*********************************************************************/
        # Create a Circle */
        #*********************************************************************/
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(bBTR.database())
        
        center = EntityBoxes.getBoxCenter(boxRow, boxCol)
        pCircle.setCenter(center + OdGeVector3d(w * 2.5 / 8.0, 0.0, 0.0))
        pCircle.setRadius(w * 1.0 / 8.0)
        
        #*********************************************************************/
        # Add it to the array of curves */
        #*********************************************************************/
        curveSegments = OdRxObjectPtrArray()
        curveSegments.push_back(pCircle)
        
        #*********************************************************************/
        # Create a region */
        #*********************************************************************/
        regions = OdRxObjectPtrArray()
        OdDbRegion.createFromCurves(curveSegments, regions)
        
        #*********************************************************************/
        # revolve the region */
        #*********************************************************************/
        p3dSolid.revolve(OdDbRegion.cast(regions.At(0)), center, OdGeVector3d(0.0, 1.0, 0.0), math.pi * 2)
        return
 
     def addHelix(self, blockId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = blockId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Helix", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Create the Helix */
        #*********************************************************************/
        pHelix = OdDbHelix.createObject()
        pHelix.setDatabaseDefaults(bBTR.database())
        
        #*********************************************************************/
        # Add the Helix to the database */
        #*********************************************************************/
        bBTR.appendOdDbEntity(pHelix)
        
        #*********************************************************************/
        # Set the Helix's parameters */
        #*********************************************************************/
        pHelix.setConstrain(OdDbHelix.kHeight)
        pHelix.setHeight(h)
        pHelix.setAxisPoint(point + OdGeVector3d(w / 2.0, -h / 2.0, 0.0))
        pHelix.setStartPoint(pHelix.axisPoint() + OdGeVector3d(w / 6.0, 0.0, 0.0))
        pHelix.setTwist(False)
        pHelix.setTopRadius(w * 3.0 / 8.0)
        pHelix.setTurns(6)
        
        #*********************************************************************/
        # Create the Helix geometry (confirm parameters are set) */
        #*********************************************************************/
        pHelix.createHelix()
        return
 
     def addDwfUnderlay(self, blockId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = blockId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Dwf reference", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Create the Dwf definition */
        #*********************************************************************/
        pDwfDef = OdDbDwfDefinition.createObject()
        itemName = "Unsaved Drawing-Model"
        pDwfDef.setSourceFileName("OdWriteEx.dwf")
        pDwfDef.setItemName(itemName)
        
        # Post to database
        idDef = pDwfDef.postDefinitionToDb(blockId.database(), "OdWriteEx - " + itemName)
        
        #*********************************************************************/
        # Create the Dwf reference */
        #*********************************************************************/
        pDwfRef = OdDbDwfReference.createObject()
        pDwfRef.setDatabaseDefaults(bBTR.database())
        
        #*********************************************************************/
        # Add the Dwf reference to the database */
        #*********************************************************************/
        bBTR.appendOdDbEntity(pDwfRef)
        
        #*********************************************************************/
        # Set the Dwf reference's parameters */
        #*********************************************************************/
        pDwfRef.setDefinitionId(idDef)
        pDwfRef.setPosition(point + OdGeVector3d(-w / 4, -h / 2, 0.0))
        pDwfRef.setScaleFactors(OdGeScale3d(0.001))
        return
 
     def addDgnUnderlay(self, blockId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = blockId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Dgn reference", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Create the Dwf definition */
        #*********************************************************************/
        pDgnDef = OdDbDgnDefinition.createObject()
        itemName = "Model"
        pDgnDef.setSourceFileName("OdWriteEx.dgn")
        pDgnDef.setItemName(itemName)
        
        # Post to database
        idDef = pDgnDef.postDefinitionToDb(blockId.database(), "OdWriteEx - " + itemName)
        
        #*********************************************************************/
        # Create the Dgn reference */
        #*********************************************************************/
        pDgnRef = OdDbDgnReference.createObject()
        pDgnRef.setDatabaseDefaults(bBTR.database())
        
        #*********************************************************************/
        # Add the Dgn reference to the database */
        #*********************************************************************/
        bBTR.appendOdDbEntity(pDgnRef)
        
        #*********************************************************************/
        # Set the Dgn reference's parameters */
        #*********************************************************************/
        pDgnRef.setDefinitionId(idDef)
        pDgnRef.setPosition(point + OdGeVector3d(0.0, -h, 0.0))
        pDgnRef.setScaleFactors(OdGeScale3d(0.0004))
        return
 
     def addPdfUnderlay(self, blockId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = blockId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Pdf reference", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        #*********************************************************************/
        # Create the Pdf definition */
        #*********************************************************************/
        pPdfDef = OdDbPdfDefinition.createObject()
        itemName = "1"
        pPdfDef.setSourceFileName("OdWriteEx.pdf")
        pPdfDef.setItemName(itemName)
        
        # Post to database
        idDef = pPdfDef.postDefinitionToDb(blockId.database(), "OdWriteEx - " + itemName)
        
        #*********************************************************************/
        # Create the Pdf reference */
        #*********************************************************************/
        pPdfRef = OdDbPdfReference.createObject()
        pPdfRef.setDatabaseDefaults(bBTR.database())
        
        #*********************************************************************/
        # Add the Pdf reference to the database */
        #*********************************************************************/
        bBTR.appendOdDbEntity(pPdfRef)
        
        #*********************************************************************/
        # Set the Pdf reference's parameters */
        #*********************************************************************/
        pPdfRef.setDefinitionId(idDef)
        pPdfRef.setPosition(point + OdGeVector3d(0.0, -h, 0.0))
        pPdfRef.setScaleFactors(OdGeScale3d(0.2))
        return
 
     def addLights(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        
        #*********************************************************************/
        # Create a Light */
        #*********************************************************************/
        pLight = OdDbLight.createObject()
        pLight.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pLight)
        
        ptLight = EntityBoxes.getBoxCenter(boxRow, boxCol)
        pLight.setPosition(ptLight)
        pLight.setLightType(OdGiDrawable.kPointLight)
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Light", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        return
 
     def addSubDMeshes(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Create a SubDMesh */
        #*********************************************************************/
        pSubDMesh = OdDbSubDMesh.createObject()
        pSubDMesh.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pSubDMesh)
        

        vertexArray, faceArray, ext = DbSubDMeshData.createData()
        pSubDMesh.setSubDMesh(vertexArray, faceArray, 0)
        
        scaleX = w * 0.7 / (ext.maxPoint().x - ext.minPoint().x)
        scaleY = h * 0.7 / (ext.maxPoint().y - ext.minPoint().y)
        xfm = OdGeMatrix3d.scaling(min(scaleX, scaleY), ext.center())
        pSubDMesh.transformBy(xfm)
        pt1 = EntityBoxes.getBoxCenter(boxRow, boxCol)
        pt2 = ext.center()

        insPoint = pt1.asVector() - pt2.asVector()
        xfm.setToTranslation(insPoint)
        pSubDMesh.transformBy(xfm)
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "SubDMesh", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        return
 
     def addExtrudedSurfaces(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        ellipse = OdDbEllipse.createObject()
        ellipse.set(OdGePoint3d(0.0, 0.0, 0.0), OdGeVector3d(0.0, 0.0, 1.0), OdGeVector3d(2.0, 0.0, 0.0), 0.5)
        
        #*********************************************************************/
        # Create extruded surface */
        #*********************************************************************/
        try:
          pFile = odSystemServices().createFile("extrudedsurf.sat")
          pExtruded = OdDbExtrudedSurface.createObject()
          options = OdDbSweepOptions()
          pExtruded.createExtrudedSurface(ellipse, OdGeVector3d(0.0, 1.0, 3.0), options, pFile)
          pExtruded.setDatabaseDefaults(bBTR.database())
          bBTR.appendOdDbEntity(pExtruded)
          ext = OdGeExtents3d()
          pExtruded.getGeomExtents(ext)
          xfm = OdGeMatrix3d()
          insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
          center = ext.center()
          xfm.setToTranslation(insPoint.asVector() - center.asVector())
          pExtruded.transformBy(xfm)
          scaleX = w * 0.7 / (ext.maxPoint().x - ext.minPoint().x)
          scaleY = h * 0.7 / (ext.maxPoint().y - ext.minPoint().y)
          xfm.setToScaling(min(scaleX, scaleY), EntityBoxes.getBoxCenter(boxRow, boxCol))
          pExtruded.transformBy(xfm)
        
          #*********************************************************************/
          # Add a label */
          #*********************************************************************/
          self.addTextEnt(bBTR,
            point + self.m_textOffset, point + self.m_textOffset,
            "Extruded surf", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        except: OdError
          # just skip entity creation
 
        return
 
     def addRevolvedSurfaces(self, btrId, boxRow, boxCol, layerId, styleId):
                #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        # base curve
        ellipse = OdDbEllipse.createObject()
        ellipse.set(OdGePoint3d(0.0, 0.0, 0.0), OdGeVector3d(0.0, 0.0, 1.0), OdGeVector3d(2.0, 0.0, 0.0), 0.5)
        
        #*********************************************************************/
        # Create revolved surface */
        #*********************************************************************/
        try:
          pFile = odSystemServices().createFile("revolvedsurf.sat")
          pRevolved = OdDbRevolvedSurface.createObject()
          options = OdDbRevolveOptions()
          pRevolved.createRevolvedSurface(ellipse, OdGePoint3d(5, 0, 0), OdGeVector3d(0, 1, 0), 3.14, 0, options, pFile)
          pRevolved.setDatabaseDefaults(bBTR.database())
          bBTR.appendOdDbEntity(pRevolved)
          ext = OdGeExtents3d()
          pRevolved.getGeomExtents(ext)
          xfm = OdGeMatrix3d()
          insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
          center = ext.center()
          xfm.setToTranslation(insPoint.asVector() - center.asVector())
          pRevolved.transformBy(xfm)
          scaleX = w * 0.7 / (ext.maxPoint().x - ext.minPoint().x)
          scaleY = h * 0.7 / (ext.maxPoint().y - ext.minPoint().y)
          xfm.setToScaling(min(scaleX, scaleY), EntityBoxes.getBoxCenter(boxRow, boxCol))
          pRevolved.transformBy(xfm)
        
          #*********************************************************************/
          # Add a label */
          #*********************************************************************/
          self.addTextEnt(bBTR,
            point + self.m_textOffset, point + self.m_textOffset,
            "Revolved surf", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        except: OdError
          # just skip entity creation
        return
 
     def addPlaneSurfaces(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        # base curve
        ellipse = OdDbEllipse.createObject()
        ellipse.set(OdGePoint3d(0.0, 0.0, 0.0), OdGeVector3d(0.0, 0.0, 1.0), OdGeVector3d(2.0, 0.0, 0.0), 0.5)
        
        #*********************************************************************/
        # Create plane surface */
        #*********************************************************************/
        pPlane = OdDbPlaneSurface.createObject()
        curveSegments = OdRxObjectPtrArray()
        curveSegments.push_back(ellipse)
        regions = OdRxObjectPtrArray()
        OdDbRegion.createFromCurves(curveSegments, regions)
        pPlane.createFromRegion(OdDbRegion.cast(regions.At(0)))
        pPlane.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pPlane)
        ext = OdGeExtents3d()
        pPlane.getGeomExtents(ext)
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        center = ext.center()
        xfm.setToTranslation(insPoint.asVector() - center.asVector())
        pPlane.transformBy(xfm)
        scaleX = w * 0.7 / (ext.maxPoint().x - ext.minPoint().x)
        scaleY = h * 0.7 / (ext.maxPoint().y - ext.minPoint().y)
        xfm.setToScaling(min(scaleX, scaleY), EntityBoxes.getBoxCenter(boxRow, boxCol))
        pPlane.transformBy(xfm)
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          point + self.m_textOffset, point + self.m_textOffset,
          "Plane surf", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        return
 
     def addLoftedSurfaces(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        # base curve
        ellipse = OdDbEllipse.createObject()
        ellipse.set(OdGePoint3d(0.0, 0.0, 0.0), OdGeVector3d(0.0, 0.0, 1.0), OdGeVector3d(2.0, 0.0, 0.0), 0.5)
        
        #*********************************************************************/
        # Create lofted surface */
        #*********************************************************************/
        try:
          pFile = odSystemServices().createFile("loftedsurf.sat")
          pLofted = OdDbLoftedSurface.createObject()
          crossSectionCurves = OdDbEntityPtrArray()
          crossSectionCurves.push_back(ellipse)
          mat = OdGeMatrix3d()
          mat.setToScaling(0.5)
          res, e = ellipse.getTransformedCopy(mat)
          crossSectionCurves.push_back(e)
          mat.setToTranslation(OdGeVector3d(0.0, 0.0, 3.0))
          crossSectionCurves.At(1).transformBy(mat)
          guideCurves = OdDbEntityPtrArray()
          options = OdDbLoftOptions()
          pLofted.createLoftedSurface(crossSectionCurves, guideCurves, None, options, pFile)
          pLofted.setDatabaseDefaults(bBTR.database())
          bBTR.appendOdDbEntity(pLofted)
          ext = OdGeExtents3d()
          pLofted.getGeomExtents(ext)
          xfm = OdGeMatrix3d()
          insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
          center = ext.center()
          xfm.setToTranslation(insPoint.asVector() - center.asVector())
          pLofted.transformBy(xfm)
          scaleX = w * 0.7 / (ext.maxPoint().x - ext.minPoint().x)
          scaleY = h * 0.7 / (ext.maxPoint().y - ext.minPoint().y)
          xfm.setToScaling(min(scaleX, scaleY), EntityBoxes.getBoxCenter(boxRow, boxCol))
          pLofted.transformBy(xfm)
        
          #*********************************************************************/
          # Add a label */
          #*********************************************************************/
          self.addTextEnt(bBTR,
            point + self.m_textOffset, point + self.m_textOffset,
            "Lofted surf", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        except: OdError
          # just skip entity creation

        return
 
     def addSweptSurfaces(self, btrId, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        # base curve
        ellipse = OdDbEllipse.createObject()
        ellipse.set(OdGePoint3d(0.0, 0.0, 0.0), OdGeVector3d(0.0, 0.0, 1.0), OdGeVector3d(2.0, 0.0, 0.0), 0.5)
        
        #*********************************************************************/
        # Create swept surface */
        #*********************************************************************/
        try:
          pFile = odSystemServices().createFile("sweptsurf.sat")
          pSwept = OdDbSweptSurface.createObject()
          options = OdDbSweepOptions()
          aVx = [OdDb3dPolylineVertex.createObject(), OdDb3dPolylineVertex.createObject(), OdDb3dPolylineVertex.createObject()]
          aVx[0].setPosition(OdGePoint3d(0.0, 0.0, 0.0))
          aVx[1].setPosition(OdGePoint3d(0.5, 0.0, 2.0))
          aVx[2].setPosition(OdGePoint3d(-0.5, 0.0, 4.0))
          poly = OdDb3dPolyline.createObject()
          poly.appendVertex(aVx[0])
          poly.appendVertex(aVx[1])
          poly.appendVertex(aVx[2])
          pSwept.createSweptSurface(ellipse, poly, options, pFile)
          pSwept.setDatabaseDefaults(bBTR.database())
          bBTR.appendOdDbEntity(pSwept)
          ext = OdGeExtents3d()
          pSwept.getGeomExtents(ext)
          xfm = OdGeMatrix3d()
          insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
          center = ext.center()
          xfm.setToTranslation(insPoint.asVector() - center.asVector())
          pSwept.transformBy(xfm)
          scaleX = w * 0.7 / (ext.maxPoint().x - ext.minPoint().x)
          scaleY = h * 0.7 / (ext.maxPoint().y - ext.minPoint().y)
          xfm.setToScaling(min(scaleX, scaleY), EntityBoxes.getBoxCenter(boxRow, boxCol))
          pSwept.transformBy(xfm)
        
          #*********************************************************************/
          # Add a label */
          #*********************************************************************/
          self.addTextEnt(bBTR,
            point + self.m_textOffset, point + self.m_textOffset,
            "Swept surf", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        except: OdError
          # just skip entity creation
        return
 
     def addNURBSurface(self, pDb, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = pDb.getModelSpaceId().safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        ptUpperLeft = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset, ptUpperLeft + self.m_textOffset,
          "NURBS surface", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset + self.m_textLine, ptUpperLeft + self.m_textOffset + self.m_textLine,
          "by brep builder", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        #*******************************************************************/
        # Create NURBS surface, trimming-loop and holes */
        #*******************************************************************/
        nurbSurf = OdGeNurbSurface()
        arrLoops = OdGeNurbCurve3dArray2d()
        arrLoopsPar = OdGeNurbCurve2dArray2d()
        
        DbNurbData.fillNurbData(nurbSurf,arrLoops,arrLoopsPar)

        pSurface = OdDbNurbSurface.createObject()
        
        #*******************************************************************/
        # BrepBuilder initialization */
        #*******************************************************************/
        brep = OdBrepBuilder()
        pService = pDb.appServices()
        bbType = BrepType_kOpenShell
        pService.brepBuilder(brep, bbType)
        #*******************************************************************/
        # Create NURBS Surface by BrepBuilder */
        #*******************************************************************/
        try:
          complexId = brep.addComplex()
          shellId = brep.addShell(complexId)
          faceId = brep.addFace(nurbSurf, OdBrepBuilder.kForward, shellId)
        
          if (arrLoops.size() != arrLoopsPar.size()):
            raise OdError("arrLoops.size() != arrLoopsPar.size()")
        
          for i in range(0,arrLoops.size()):
            currentLoop = arrLoops.At(i)
            currentParLoop = arrLoopsPar.At(i)
            if (currentLoop.size() != currentParLoop.size()):
              raise OdError("currentLoop.size() != currentParLoop.size()")
        
            LoopId = brep.addLoop(faceId)
            for j in range(0, currentLoop.size()):
              edgeId = brep.addEdge(currentLoop.At(j))
              brep.addCoedge(LoopId, edgeId, OdBrepBuilder.kForward, currentParLoop.At(j))
            brep.finishLoop(LoopId)

          brep.finishFace(faceId)
          brep.finishShell(shellId)
          brep.finishComplex(complexId)
          pModelGeometry = brep.finish()
          pSurface.setBody(pModelGeometry)
        except OdError as e:
          print("\n\nException occurred: %ls\n", e.description())
        #*******************************************************************/
        # Free created trimming-loop curves */
        #*******************************************************************/
        for i in range(arrLoops.size()):
          for j in range(0,arrLoops.At(i).size()):
            tmp1 = arrLoops.At(i).At(j)
            tmp2 = arrLoopsPar.At(i).At(j)
            del tmp1
            del tmp2
        #*********************************************************************/
        # Add NURB surface to database */
        #*********************************************************************/
        ext = OdGeExtents3d()
        pSurface.getGeomExtents(ext)
        xfm = OdGeMatrix3d()
        scaleX = w * 0.7 / (ext.maxPoint().x - ext.minPoint().x)
        scaleY = h * 0.7 / (ext.maxPoint().y - ext.minPoint().y)
        
        xfm.setToScaling(min(scaleX, scaleY), ext.center())
        pSurface.transformBy(xfm)
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        center = ext.center()
        xfm.setToTranslation(insPoint.asVector() - center.asVector())
        pSurface.transformBy(xfm)
        
        pSurface.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(pSurface)
        #*********************************************************************/
        # Add the NURB surface */
        #*********************************************************************/
        arObjId = OdDbObjectIdArray()
        arObjId.push_back(pSurface.objectId())
        
        #*********************************************************************/
        # Add NURB surface to Sortents table */
        #*********************************************************************/
        pSortentsTable = bBTR.getSortentsTable(True)
        pSortentsTable.moveToBottom(arObjId)
        return
 
     def addMLeaders(self, btrId, boxRow, boxCol, layerId, styleId):       
        llIndex = 0
        #*********************************************************************/
        # Open the Block Table Record */
        #*********************************************************************/
        bBTR = btrId.safeOpenObject(kForWrite)
        pDb = btrId.database()
        
        #*********************************************************************/
        # Get the origin and size of the box */
        #*********************************************************************/
        point = EntityBoxes.getBox(boxRow, boxCol)
        w = EntityBoxes.getWidth(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        
        #*********************************************************************/
        # Add a label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
            point + self.m_textOffset, point + self.m_textOffset,
            "MLeaders",
            self.m_textSize,
            kTextLeft, kTextTop,
            layerId, styleId)
        
        #*********************************************************************/
        # Add a MLeader with database defaults to the database */
        #*********************************************************************/
        pMLeader = OdDbMLeader.createObject()
        pMLeader.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pMLeader)
        
        
        #*********************************************************************/
        # Add the vertices */
        #*********************************************************************/
        pMText = OdDbMText.createObject()
        pMText.setDatabaseDefaults(pDb)
        pMLeader.setEnableFrameText(True)
        pMText.setContents("MText")
        
        textHeight = 0.15
        textWidth = 1.0
        
        point.x += w * 3.0 / 8.0
        point.y -= h * 1.0 / 6.0
        pMText.setLocation(point)
        pMText.setTextHeight(textHeight)
        pMText.setWidth(textWidth)
        pMText.setAttachment(OdDbMText.kMiddleLeft)
        pMText.setTextStyle(styleId)
        pMLeader.setMText(pMText)
        pMLeader.setDoglegLength(0.18)
        
        point.x -= w * 2.0 / 8.0
        point.y -= h * 1.0 / 8.0
        odResult,llIndex = pMLeader.addLeaderLine(point)
        point.x += w * 1.0 / 8.0
        odResult,llIndex = pMLeader.addLeaderLine(point)
        point.x += w * 1.0 / 6.0
        point.y -= h * 1.0 / 8.0
        pMLeader.addFirstVertex(llIndex, point)
        
        point.x += w * 3.0 / 8.0
        point.y -= h * 1.0 / 8.0
        odResult,llIndex = pMLeader.addLeaderLine(point)
        
        #*********************************************************************/
        # Add block with attribute for second MLeader contents */
        #*********************************************************************/
        contentBlockId = None
        odRes, bt = pDb.getBlockTableId().openObject(kForWrite)
        pBlocks = OdDbBlockTable.cast(bt)
        pBlock = OdDbBlockTableRecord.createObject()
        pBlock.setName("AnnoBlock2")
        contentBlockId = pBlocks.add(pBlock)
        pCircle = OdDbCircle.createObject()
        pCircle.setDatabaseDefaults(pDb)
        pBlock.appendOdDbEntity(pCircle)
        pCircle.setCenter(OdGePoint3d.kOrigin)
        pCircle.setRadius(0.5)
        pAttr = OdDbAttributeDefinition.createObject()
        pAttr.setDatabaseDefaults(pDb)
        pBlock.appendOdDbEntity(pAttr)
        pAttr.setPrompt("Enter Attr: ")
        pAttr.setTag("Attr")
        pAttr.setHorizontalMode(kTextCenter)
        pAttr.setHeight(0.2)
        pAttr.setTextString("Block")
        
        #*********************************************************************/
        # Add block for second MLeader arrow heads */
        #*********************************************************************/
        arrowBlockId = None
        odRes, bt = pDb.getBlockTableId().openObject(kForWrite)
        pBlocks = OdDbBlockTable.cast(bt)
        pBlock = OdDbBlockTableRecord.createObject()
        pBlock.setName("ArrowBlock2")
        pBlock.setComments("Block for MLeader arrow heads.")
        arrowBlockId = pBlocks.add(pBlock)
        pPl = OdDbPolyline.createObject()
        pPl.setDatabaseDefaults(pDb)
        pBlock.appendOdDbEntity(pPl)
        pPl.addVertexAt(0, OdGePoint2d(0.0, -0.5))
        pPl.addVertexAt(1, OdGePoint2d(0.5, 0.0))
        pPl.addVertexAt(2, OdGePoint2d(0.0, 0.5))
        pPl.addVertexAt(3, OdGePoint2d(-0.5, 0.0))
        pPl.addVertexAt(4, OdGePoint2d(0.0, -0.5))
        pPl.transformBy(OdGeMatrix3d.scaling(2.0))
        
        #*********************************************************************/
        # Create style for second MLeader */
        #*********************************************************************/
        pMLeader = OdDbMLeader.createObject()
        styleId2 = None
        
        pMLeaderStyleDic = pDb.getMLeaderStyleDictionaryId().safeOpenObject(kForWrite)
        pMLeaderStyle = OdDbMLeaderStyle.createObject()
        pMLeaderStyle.setDatabaseDefaults(pDb)
        pMLeaderStyle.setContentType(OdDbMLeaderStyle.kBlockContent)
        styleId2 = pMLeaderStyleDic.setAt("BlockMLeaderStyle2", pMLeaderStyle)
        
        pMLeaderStyle.setBlockId(contentBlockId)
        pMLeaderStyle.setBlockScale(OdGeScale3d(0.5, 0.5, 1.0))
        pMLeaderStyle.setArrowSymbolId(arrowBlockId)
        pMLeaderStyle.setDoglegLength(0.1)
        pMLeaderStyle.setLandingGap(0.0)
        #pMLeaderStyle.setArrowSize(0.5)
        
        
        #*********************************************************************/
        # Set second MLeader vertices */
        #*********************************************************************/
        pMLeader.setDatabaseDefaults(pDb)
        bBTR.appendOdDbEntity(pMLeader)
        pMLeader.setMLeaderStyle(styleId2)
        pMLeader.setBlockPosition(OdGePoint3d(12.2, 1.0, 0.0))
        
        odResult,llIndex = pMLeader.addLeaderLine(OdGePoint3d(12.0, 1.5, 0.0))
        pMLeader.addFirstVertex(llIndex, OdGePoint3d(12.7, 1.9, 0.0))
        pMLeader.addFirstVertex(llIndex, OdGePoint3d(12.3, 2.3, 0.0))
        
        odResult,llIndex = pMLeader.addLeaderLine(OdGePoint3d(13.0, 1.65, 0.0))
        pMLeader.addFirstVertex(llIndex, OdGePoint3d(13.0, 2.3, 0.0))
        
        pMLeader.setArrowSize(pMLeader.arrowSize() * 0.5)
        return
 
     def add3dSolidBox(self, pDb, boxRow, boxCol, layerId, styleId):
        bBTR = pDb.getModelSpaceId().safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        ptUpperLeft = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset, ptUpperLeft + self.m_textOffset,
          "3DSolidBox", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset + self.m_textLine, ptUpperLeft + self.m_textOffset + self.m_textLine,
          "by brep builder", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        #*********************************************************************/
        # Create input 3D Solid Box */
        #*********************************************************************/
        input3dSolid = OdDb3dSolid.createObject()
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())

        input3dSolid.createBox(w * 6.0 / 8.0, h * 6.0 / 8.0, w * 6.0 / 8.0)
        input3dSolid.transformBy(xfm)
        
        brep = OdBrBrep()
        input3dSolid.brep(brep)
        
        #*********************************************************************/
        # Fill BrepBuilder by means of OdBrepBuilderFillerModule */
        #*********************************************************************/
        
        brepData = None
        bbuilder = OdBrepBuilder()
        pService = pDb.appServices()
        bbType = BrepType_kOpenShell
        pService.brepBuilder(bbuilder, bbType)
        
        
        BBFiller = OdBrepBuilderFiller()
        res = BBFiller.initFrom(bbuilder, brep)
        if (res != eOk):
          raise OdError(res)
        
        brepData = bbuilder.finish()
        
        #*********************************************************************/
        # Get OdDb3dSolid from brep geometry data */
        #*********************************************************************/
        output3dSolid = OdDb3dSolid.createObject()
        output3dSolid.setBody(brepData)
        
        #*********************************************************************/
        # Add to database */
        #*********************************************************************/
        ext = OdGeExtents3d()
        output3dSolid.getGeomExtents(ext)
        scaleX = w * 0.8 / (ext.maxPoint().x - ext.minPoint().x)
        scaleY = h * 0.5 / (ext.maxPoint().y - ext.minPoint().y)
        
        xfm.setToScaling(min(scaleX, scaleY), ext.center())
        output3dSolid.transformBy(xfm)
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        center = ext.center()
        xfm.setToTranslation(insPoint.asVector() - center.asVector())
        output3dSolid.transformBy(xfm)
        
        output3dSolid.setDatabaseDefaults(bBTR.database())
        bBTR.appendOdDbEntity(output3dSolid)
        #*********************************************************************/
        # Add the 3D Solid */
        #*********************************************************************/
        arObjId = OdDbObjectIdArray()
        arObjId.push_back(output3dSolid.objectId())
        
        #*********************************************************************/
        # Add 3D Solid to Sortents table */
        #*********************************************************************/
        pSortentsTable = bBTR.getSortentsTable(True)
        pSortentsTable.moveToBottom(arObjId)
        return
 
     def addBRepCylinder(self, pDb, boxRow, boxCol, layerId, styleId):
        bBTR = pDb.getModelSpaceId().safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        ptUpperLeft = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset, ptUpperLeft + self.m_textOffset,
          "Cylinder", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset + self.m_textLine, ptUpperLeft + self.m_textOffset + self.m_textLine,
          "by brep builder", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())

        brepData = None
        try:

          bbuilder = OdBrepBuilder()
          
          pService = pDb.appServices()
          bbType = BrepType_kOpenShell
          pService.brepBuilder(bbuilder, bbType)
          
          # Create complex
          complexId = bbuilder.addComplex()
          
          # Create shell
          shellId = bbuilder.addShell(complexId)
          
          intrvlV = OdGeInterval(-50.0, 50.0)
          cylSurf = OdGeCylinder(50, OdGePoint3d(50, -100, 250), OdGeVector3d(0, 0, 1), OdGeVector3d(0, 1, 0), intrvlV, 0, Oda2PI)
          
          top = OdGePlane(OdGePoint3d(0, 0, 300), OdGeVector3d(1, 0, 0), OdGeVector3d(0, 1, 0))
          bottom = OdGePlane(OdGePoint3d(0, 0, 200), OdGeVector3d(1, 0, 0), OdGeVector3d(0, 1, 0))
          
          # Add Faces
          cylFaceId = bbuilder.addFace(cylSurf, OdBrepBuilder.kForward, shellId)
          topFaceId = bbuilder.addFace(top, OdBrepBuilder.kForward, shellId)
          bottomFaceId = bbuilder.addFace(bottom, OdBrepBuilder.kReversed, shellId)
          
          edgeBottom = OdGeEllipArc3d(OdGePoint3d(50, -100, 200), OdGeVector3d.kXAxis, -OdGeVector3d.kYAxis, 50, 50, 0, Oda2PI)
          edgeTop = OdGeEllipArc3d(OdGePoint3d(50, -100, 300), OdGeVector3d.kXAxis, OdGeVector3d.kYAxis, 50, 50, 0, Oda2PI)
          
          edgeBottomId = bbuilder.addEdge(edgeBottom)
          edgeTopId = bbuilder.addEdge(edgeTop)
          
          loopId_cylTop = bbuilder.addLoop(cylFaceId)
          loopId_cylBottom = bbuilder.addLoop(cylFaceId)
          loopId_Top = bbuilder.addLoop(topFaceId)
          loopId_Bottom = bbuilder.addLoop(bottomFaceId)
          bbuilder.finishFace(cylFaceId)
          bbuilder.finishFace(topFaceId)
          bbuilder.finishFace(bottomFaceId)
          
          bbuilder.addCoedge(loopId_cylTop, edgeTopId, OdBrepBuilder.kReversed)
          bbuilder.addCoedge(loopId_cylBottom, edgeBottomId, OdBrepBuilder.kReversed)
          bbuilder.addCoedge(loopId_Top, edgeTopId, OdBrepBuilder.kForward)
          bbuilder.addCoedge(loopId_Bottom, edgeBottomId, OdBrepBuilder.kForward)
          bbuilder.finishLoop(loopId_cylTop)
          bbuilder.finishLoop(loopId_cylBottom)
          bbuilder.finishLoop(loopId_Top)
          bbuilder.finishLoop(loopId_Bottom)
          
          bbuilder.finishShell(shellId)
          bbuilder.finishComplex(complexId)
          
          brepData = bbuilder.finish()
          
          
          #*********************************************************************/
          # Get Cylinder from brep geometry data */
          #*********************************************************************/
          pRetSurface = OdDb3dSolid.createObject()
          pRetSurface.setBody(brepData)
          
          #*********************************************************************/
          # Add to database */
          #*********************************************************************/
          ext = OdGeExtents3d()
          pRetSurface.getGeomExtents(ext)
          scaleX = w * 0.8 / (ext.maxPoint().x - ext.minPoint().x)
          scaleY = h * 0.5 / (ext.maxPoint().y - ext.minPoint().y)
          
          xfm.setToScaling(min(scaleX, scaleY), ext.center())
          pRetSurface.transformBy(xfm)
          insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
          center = ext.center()
          xfm.setToTranslation(insPoint.asVector() - center.asVector())
          pRetSurface.transformBy(xfm)
          
          pRetSurface.setDatabaseDefaults(bBTR.database())
          bBTR.appendOdDbEntity(pRetSurface)
          #*********************************************************************/
          # Add the Cylinder */
          #*********************************************************************/
          arObjId = OdDbObjectIdArray()
          arObjId.push_back(pRetSurface.objectId())
          
          #*********************************************************************/
          # Add Cylinder to Sortents table */
          #*********************************************************************/
          pSortentsTable = bBTR.getSortentsTable(True)
          pSortentsTable.moveToBottom(arObjId)
        except OdError as e:
          print("\n\nException occurred: %ls\n", e.description())

        return
 
     def addSeamedCylinder(self, pDb, boxRow, boxCol, layerId, styleId):
        bBTR = pDb.getModelSpaceId().safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        ptUpperLeft = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset, ptUpperLeft + self.m_textOffset,
          "Seamed Cylinder", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset + self.m_textLine, ptUpperLeft + self.m_textOffset + self.m_textLine,
          "by brep builder", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())
        
        brepData = None
        try:

          bbuilder = OdBrepBuilder()
          
          pService = pDb.appServices()
          bbType = BrepType_kOpenShell
          pService.brepBuilder(bbuilder, bbType)
          
          # Create complex
          complexId = bbuilder.addComplex()
          
          # Create shell
          shellId = bbuilder.addShell(complexId)
          
          radius = 3.15
          intrvlV = OdGeInterval(-5.0, 5.0)
          cylSurf = OdGeCylinder(OdGeCylinder(radius, OdGePoint3d(0, 0, 5), OdGeVector3d(0, 0, 1), OdGeVector3d(0, 1, 0), intrvlV, 0, Oda2PI))
          
          top = OdGePlane(OdGePoint3d(0, 0, 10), OdGeVector3d(1, 0, 0), OdGeVector3d(0, 1, 0))
          bottom = OdGePlane(OdGePoint3d(0, 0, 0), OdGeVector3d(1, 0, 0), OdGeVector3d(0, 1, 0))
          
          # Add Faces
          cylFaceId = bbuilder.addFace(cylSurf, OdBrepBuilder.kForward, shellId)
          topFaceId = bbuilder.addFace(top, OdBrepBuilder.kForward, shellId)
          bottomFaceId = bbuilder.addFace(bottom, OdBrepBuilder.kReversed, shellId)
          
          edgeBottom = OdGeEllipArc3d(OdGePoint3d(0, 0, 0), OdGeVector3d.kXAxis, -OdGeVector3d.kYAxis, radius, radius, 0, Oda2PI)
          edgeTop = OdGeEllipArc3d(OdGePoint3d(0, 0, 10), OdGeVector3d.kXAxis, OdGeVector3d.kYAxis, radius, radius, 0, Oda2PI)
          edgeSeam = OdGeLineSeg3d(edgeBottom.evalPoint(0.0), edgeTop.evalPoint(0.0))
          
          edgeBottomId = bbuilder.addEdge(edgeBottom)
          edgeTopId = bbuilder.addEdge(edgeTop)
          edgeSeamId = bbuilder.addEdge(edgeSeam)
          
          loopId_cylinder = bbuilder.addLoop(cylFaceId)
          loopId_Top = bbuilder.addLoop(topFaceId)
          loopId_Bottom = bbuilder.addLoop(bottomFaceId)
          
          bbuilder.finishFace(cylFaceId)
          bbuilder.finishFace(topFaceId)
          bbuilder.finishFace(bottomFaceId)
          
          bbuilder.addCoedge(loopId_cylinder, edgeTopId, OdBrepBuilder.kReversed)
          bbuilder.addCoedge(loopId_cylinder, edgeSeamId, OdBrepBuilder.kReversed)
          bbuilder.addCoedge(loopId_cylinder, edgeBottomId, OdBrepBuilder.kReversed)
          bbuilder.addCoedge(loopId_cylinder, edgeSeamId, OdBrepBuilder.kForward)
          bbuilder.addCoedge(loopId_Top, edgeTopId, OdBrepBuilder.kForward)
          bbuilder.addCoedge(loopId_Bottom, edgeBottomId, OdBrepBuilder.kForward)
          bbuilder.finishLoop(loopId_cylinder)
          bbuilder.finishLoop(loopId_Top)
          bbuilder.finishLoop(loopId_Bottom)
          
          bbuilder.finishShell(shellId)
          bbuilder.finishComplex(complexId)
          
          brepData = bbuilder.finish()
          
          
          #*********************************************************************/
          # Get Seamed Cylinder from brep geometry data */
          #*********************************************************************/
          pSolid = OdDb3dSolid.createObject()
          pSolid.setBody(brepData)
          
          #*********************************************************************/
          # Add to database */
          #*********************************************************************/
          ext = OdGeExtents3d()
          pSolid.getGeomExtents(ext)
          scaleX = w * 0.8 / (ext.maxPoint().x - ext.minPoint().x)
          scaleY = h * 0.5 / (ext.maxPoint().y - ext.minPoint().y)
          
          xfm.setToScaling(min(scaleX, scaleY), ext.center())
          pSolid.transformBy(xfm)
          insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
          center = ext.center()
          xfm.setToTranslation(insPoint.asVector() - center.asVector())
          pSolid.transformBy(xfm)
          
          pSolid.setDatabaseDefaults(bBTR.database())
          bBTR.appendOdDbEntity(pSolid)
          
          #*********************************************************************/
          # Add the Seamed Cylinder */
          #*********************************************************************/
          arObjId = OdDbObjectIdArray()
          arObjId.push_back(pSolid.objectId())
          
          #*********************************************************************/
          # Add Seamed Cylinder to Sortents table */
          #*********************************************************************/
          pSortentsTable = bBTR.getSortentsTable(True)
          pSortentsTable.moveToBottom(arObjId)
        except OdError as e:
          print("\n\nException occurred: %ls\n", e.description())

        return
 
     def addPointCloud(self, pDb, boxRow, boxCol, layerId, styleId):
          #*********************************************************************/
        # Open the BlockTableRecord */
        #*********************************************************************/
        bBTR = pDb.getModelSpaceId().safeOpenObject(kForWrite)
        
        #*********************************************************************/
        # Get the Upper-left corner of the box and its size */
        #*********************************************************************/
        ptUpperLeft = EntityBoxes.getBox(boxRow, boxCol)
        h = EntityBoxes.getHeight()
        w = EntityBoxes.getWidth(boxRow, boxCol)
        
        #*********************************************************************/
        # Add the label */
        #*********************************************************************/
        self.addTextEnt(bBTR,
          ptUpperLeft + self.m_textOffset, ptUpperLeft + self.m_textOffset,
          "Point Cloud", self.m_textSize, kTextLeft, kTextTop, layerId, styleId)
        
        xfm = OdGeMatrix3d()
        insPoint = EntityBoxes.getBoxCenter(boxRow, boxCol)
        xfm.setTranslation(insPoint.asVector())
        
        #*********************************************************************/
        # File name for PCG file */
        #*********************************************************************/
        pcgFileName = "bunny.pcg"
        
        p1 = OdGePoint3d()
        p2 = OdGePoint3d()
        extents = OdGeExtents3d(p1, p2)
        translation = OdGeVector3d()
        
        #*********************************************************************/
        # Start parsing PCG file */
        #*********************************************************************/
        
        bFileAvailable = odSystemServices().accessFile(pcgFileName, kFileRead)
        
        if (bFileAvailable):
          pcgFile = OdRdFileBuf.createObject(pcgFileName)
        
          canRead = True
          # read pcg file version
          pcgFile.seek(3, kSeekFromStart)
          pcgFileVer = OdPlatformStreamer.rdInt16(pcgFile)
          #seek to extents info
          if (pcgFileVer == 0x0003):
            pcgFile.seek(7, kSeekFromStart)
          elif (pcgFileVer == 0x0004):
            pcgFile.seek(19, kSeekFromStart)
          else:
            canRead = False
          
          if (canRead):
            # extents reading
            x = OdPlatformStreamer.rdDouble(pcgFile)
            y = OdPlatformStreamer.rdDouble(pcgFile)
            z = OdPlatformStreamer.rdDouble(pcgFile)
            p1.set(x, y, z)
          
            x = OdPlatformStreamer.rdDouble(pcgFile)
            y = OdPlatformStreamer.rdDouble(pcgFile)
            z = OdPlatformStreamer.rdDouble(pcgFile)
            p2.set(x, y, z)
            extents.set(p1, p2)
          
            # translation reading
            x = OdPlatformStreamer.rdDouble(pcgFile)
            y = OdPlatformStreamer.rdDouble(pcgFile)
            z = OdPlatformStreamer.rdDouble(pcgFile)
            translation.set(x, y, z)       

        #*********************************************************************/
        # Calculate point cloud scale and center position */
        #*********************************************************************/
        scale = 1
        if (extents.maxPoint().x - extents.minPoint().x != 0):
          scale = EntityBoxes.getWidth(boxRow, boxCol) / (extents.maxPoint().x - extents.minPoint().x)
        
        location = EntityBoxes.getBoxCenter(boxRow, boxCol)
        translation = location.asVector() - translation * scale
        location.set(translation.x, translation.y, translation.z)
        
        #*********************************************************************/
        # Load point cloud module */
        #*********************************************************************/
        pPointCloudModule = odrxDynamicLinker().loadApp("AcDbPointCloudObj")
        
        if (pPointCloudModule != None):
          #*********************************************************************/
          # Create point cloud entity */
          #*********************************************************************/
          odres, pPointCloud = oddbCreatePointCloudEntity(bBTR, pcgFileName, "", location, scale)
        
          #*********************************************************************/
          # Append extents info to point cloud */
          #*********************************************************************/
          pPointCloud.setExtents(extents)
        return
 
     def addLayout(self, pDb):
          #*******************************************************************/
        # Create a new Layout */
        #*******************************************************************/
        layoutId = pDb.createLayout("ODA Layout")
        pLayout = layoutId.safeOpenObject()
        
        #*******************************************************************/
        # Make it current, creating the overall PaperSpace viewport */
        #*******************************************************************/
        pDb.setCurrentLayout(layoutId)
        
        #*******************************************************************/
        # Open the overall viewport for this layout */
        #*******************************************************************/
        pOverallViewport = pLayout.overallVportId().safeOpenObject()
        
        #*******************************************************************/
        # Get some useful parameters */
        #*******************************************************************/
        overallCenter = pOverallViewport.centerPoint()
        
        #*******************************************************************/
        # Note: */
        # If a viewport is an overall viewport, */
        # the values returned by width() and height() must be divided by a */
        # factor of 1.058, and the parameters of setWidth and setHeight() */
        # must be multiplied a like factor.  */
        #*******************************************************************/
        margin = 0.25
        overallWidth = pOverallViewport.width() / 1.058 - 2 * margin
        overallHeight = pOverallViewport.height() / 1.058 - 2 * margin
        overallLLCorner = overallCenter - OdGeVector3d(0.5 * overallWidth, 0.5 * overallHeight, 0.0)
        
        #*******************************************************************/
        # Open the PaperSpace BlockTableRecord for this layout */
        #*******************************************************************/
        pPS = pLayout.getBlockTableRecordId().safeOpenObject(kForWrite)
        
        #*******************************************************************/
        # Create a new viewport, and append it to PaperSpace */
        #*******************************************************************/
        pViewport = OdDbViewport.createObject()
        pViewport.setDatabaseDefaults(pDb)
        pPS.appendOdDbEntity(pViewport)
        
        #*******************************************************************/
        # Set some parameters */
        #                                                                  */
        # This viewport occupies the upper half of the overall viewport, */
        # and displays all objects in model space */
        #*******************************************************************/
        
        pViewport.setWidth(overallWidth)
        pViewport.setHeight(overallHeight * 0.5)
        pViewport.setCenterPoint(overallCenter + OdGeVector3d(0.0, 0.5 * pViewport.height(), 0.0))
        pViewport.setViewCenter(pOverallViewport.viewCenter())
        pViewport.zoomExtents()
        
        #*******************************************************************/
        # Create viewports for each of the entities that have been */
        # pushBacked onto m_layoutEntities */
        #*******************************************************************/
        if (self.m_layoutEntities.size() != 0):
          widthFactor = 1.0 / self.m_layoutEntities.size()
          for i in range(0, self.m_layoutEntities.size()):
            pEnt = self.m_layoutEntities.At(i).safeOpenObject()
            entityExtents = OdGeExtents3d()
            if (pEnt.getGeomExtents(entityExtents) == eOk):
              #*************************************************************/
              # Create a new viewport, and append it to PaperSpace */
              #*************************************************************/
              pViewport = OdDbViewport.createObject()
              pViewport.setDatabaseDefaults(pDb)
              pPS.appendOdDbEntity(pViewport)
        
              #*************************************************************/
              # The viewports are tiled along the bottom of the overall */
              # viewport */
              #*************************************************************/
              pViewport.setWidth(overallWidth * widthFactor)
              pViewport.setHeight(overallHeight * 0.5)
              pViewport.setCenterPoint(overallLLCorner + OdGeVector3d((i + 0.5) * pViewport.width(), 0.5 * pViewport.height(), 0.0))
        
              #*************************************************************/
              # The target of the viewport is the midpoint of the entity */
              # extents */
              #*************************************************************/
              minPt = entityExtents.minPoint()
              maxPt = entityExtents.maxPoint()
              viewTarget = OdGePoint3d()
              viewTarget.x = (minPt.x + maxPt.x) / 2.0
              viewTarget.y = (minPt.y + maxPt.y) / 2.0
              viewTarget.z = (minPt.z + maxPt.z) / 2.0
              pViewport.setViewTarget(viewTarget)
        
              #*************************************************************/
              # The viewHeight is the larger of the height as defined by */
              # the entityExtents, and the height required to display the */
              # width of the entityExtents */
              #*************************************************************/
              viewHeight = abs(maxPt.y - minPt.y)
              viewWidth = abs(maxPt.x - minPt.x)
              viewHeight = max(viewHeight, viewWidth * pViewport.height() / pViewport.width())
              pViewport.setViewHeight(viewHeight * 1.05)


        pDb.setTILEMODE(True) # Disable PaperSpace
        return

     def fill(self, database): # type: (ODA_Drawings.OdDatabase) -> None
     
        tr1 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()

        ######################################################################
        # Set Creation and Last Update times #
        ######################################################################
        date = OdDbDate()     
        date.setDate(1, 1, 2006)
        date.setTime(12, 0, 0, 0)
        date.localToUniversal()
        odDbSetTDUCREATE(database, date)     
        date.getUniversalTime()
        odDbSetTDUUPDATE(database, date)
        
        ######################################################################
        # Add some Registered Applications #
        ######################################################################
        self.addRegApp(database, "ODA")
        self.addRegApp(database, "AVE_FINISH") # for materials
        ######################################################################
        # Add an SHX text style #
        ######################################################################
        shxTextStyleId = self.addStyle(database, "OdaShxStyle", 0.0, 1.0, 0.2, 0.0, "txt",
          False, "", False, False, 0, 0)
        
        ######################################################################
        # Add a TTF text style #
        ######################################################################
        ttfStyleId = self.addStyle(database, "OdaTtfStyle", 0.0, 1.0, 0.2, 0.0,
            "VERDANA.TTF", False, "Verdana", False, False, 0, 34)
        
        ######################################################################
        # Add a Shape file style for complex linetypes #
        ######################################################################
        shapeStyleId = self.addStyle(database, "", 0.0, 1.0, 0.2, 0.0, "ltypeshp.shx",
          True, "", False, False, 0, 0)
        
        ######################################################################
        # Add some linetypes #
        ######################################################################
        self.addLinetypes(database, shapeStyleId, shxTextStyleId)
        
        ######################################################################
        # Add a Layer #
        ######################################################################
        odaLayer1Id = self.addLayer(database, "Oda Layer 1", OdCmEntityColor.kACIRed, "CONTINUOUS")
        
        ######################################################################
        # Add a block definition #
        ######################################################################
        odaBlock1Id = self.addBlockDef(database, "OdaBlock1", 1, 2)
        
        ######################################################################
        # Add a DimensionStyle #
        ######################################################################
        odaDimStyleId = self.addDimStyle(database, "OdaDimStyle")
        
        ######################################################################
        # Add an MLine style #
        ######################################################################
        odaMLineStyleId = self.addMLineStyle(database, "OdaStandard", "ODA Standard Style")
        
        ######################################################################
        # Add a Material #
        ######################################################################
        odaMaterialId = self.addMaterial(database, "OdaMaterial", "ODA Defined Material")
        
        ######################################################################
        # Add a PaperSpace Viewport #
        ######################################################################
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addPsViewport(database, odaLayer1Id)
        
        ######################################################################
        # Add ModelSpace Entity Boxes #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.createEntityBoxes(database.getModelSpaceId(), odaLayer1Id)
        
        ######################################################################
        # Add some lines #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addLines(database.getModelSpaceId(), 0, 0, odaLayer1Id, ttfStyleId)

        ######################################################################
        # Add a 2D (heavy) polyline #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.add2dPolyline(database.getModelSpaceId(), 0, 1, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a PolyFace Mesh #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addPolyFaceMesh(database.getModelSpaceId(), 0, 2, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a PolygonMesh #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addPolygonMesh(database.getModelSpaceId(), 0, 3, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add some curves #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addCurves(database.getModelSpaceId(), 0, 4, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add Tolerance #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addTolerance(database.getModelSpaceId(), 0, 5, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add some Leaders #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addLeaders(database.getModelSpaceId(), 0, 6, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add an Aligned Dimension #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addAlignedDimension(database.getModelSpaceId(), 0, 7, odaLayer1Id, ttfStyleId, odaDimStyleId)
        
        ######################################################################
        # Add a MultiLine #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addMLine(database.getModelSpaceId(), 0, 8, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add an Arc Dimension #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addArcDimension(database.getModelSpaceId(), 0, 9, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a 3D Polyline #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.add3dPolyline(database.getModelSpaceId(), 1, 0, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add MText #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addMText(database.getModelSpaceId(), 1, 1, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add Block Reference #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addBlockRef(database.getModelSpaceId(), 1, 2, odaLayer1Id, ttfStyleId, odaBlock1Id)
        
        ######################################################################
        # Add Radial Dimension #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addRadialDimension(database.getModelSpaceId(), 1, 3, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add 3D Face #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.add3dFace(database.getModelSpaceId(), 1, 4, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add RText #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addRText(database.getModelSpaceId(), 1, 6, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add Hatches #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addHatches(database.getModelSpaceId(), 2, 0, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add some text entities to ModelSpace #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addTextEnts(database.getModelSpaceId(), 2, 1, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add Solid #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addSolid(database.getModelSpaceId(), 2, 3, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add an Associative Dimension #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addDimAssoc(database.getModelSpaceId(), 2, 4, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add an Ray #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addRay(database.getModelSpaceId(), 3, 0, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a 3d Point Angular Dimension #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.add3PointAngularDimension(database.getModelSpaceId(), 3, 1, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add Ordinate Dimensions #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addOrdinateDimensions(database.getModelSpaceId(), 3, 2, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a Spline #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addSpline(database.getModelSpaceId(), 3, 3, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add some Traces #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addTraces(database.getModelSpaceId(), 3, 4, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a Polyline #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addPolyline(database.getModelSpaceId(), 3, 5, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add an ArcAlignedText #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addArcText(database.getModelSpaceId(), 3, 6, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a Wipeout #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addWipeout(database.getModelSpaceId(), 3, 7, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a RadialDimensionLarge #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addRadialDimensionLarge(database.getModelSpaceId(), 3, 8, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a 2 Line Angular Dimension #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.add2LineAngularDimension(database.getModelSpaceId(), 3, 9, odaLayer1Id, ttfStyleId)
        

        ######################################################################
        # Add an ACIS Solid #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addACIS(database.getModelSpaceId(), 1, 5, odaLayer1Id, ttfStyleId)
        
        #######################################################################
        ## Add an Image #
        #######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addImage(database.getModelSpaceId(), 4, 0, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add an Xref #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addXRef(database.getModelSpaceId(), 4, 1, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add a Table #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addTable(database.getModelSpaceId(), odaBlock1Id, 4, 2,
        odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a Diametric Dimension #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addDiametricDimension(database.getModelSpaceId(), 4, 3,
        odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a Shape #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addShape(database.getModelSpaceId(), 4, 4, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add a MInsert #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addMInsert(database.getModelSpaceId(), 4, 5, odaLayer1Id,
        ttfStyleId, odaBlock1Id)
        
        ######################################################################
        # Add an Xline #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addXline(database.getModelSpaceId(), 4, 6, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add custom objects #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addCustomObjects(database)
        
        ######################################################################
        # Add Text with Field #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addTextWithField(database.getModelSpaceId(), 5, 0, odaLayer1Id,
        shxTextStyleId, ttfStyleId)
        
        ######################################################################
        # Add OLE object #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addOLE2FrameFromFile(database.getModelSpaceId(), 5, 1,
        "OdWriteEx.xls", odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add Box #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addBox(database.getModelSpaceId(), 5, 2, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add Frustum #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addFrustum(database.getModelSpaceId(), 5, 3, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add Sphere #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addSphere(database.getModelSpaceId(), 5, 4, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add Torus #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addTorus(database.getModelSpaceId(), 5, 5, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add Wedge #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addWedge(database.getModelSpaceId(), 5, 6, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add Region #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addRegion(database.getModelSpaceId(), 5, 7, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add Extrusion #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addExtrusion(database.getModelSpaceId(), 6, 0, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add Revolution #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addSolRev(database.getModelSpaceId(), 6, 1, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add Helix #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addHelix(database.getModelSpaceId(), 6, 2, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add Underlays #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addDwfUnderlay(database.getModelSpaceId(), 6, 3, odaLayer1Id,
        ttfStyleId)
        self.addDgnUnderlay(database.getModelSpaceId(), 6, 4, odaLayer1Id,
        ttfStyleId)
        self.addPdfUnderlay(database.getModelSpaceId(), 6, 5, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add some Lights #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addLights(database.getModelSpaceId(), 6, 6, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add some SubDMeshes #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addSubDMeshes(database.getModelSpaceId(), 6, 7, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add some Surfaces #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addExtrudedSurfaces(database.getModelSpaceId(), 6, 8,
        odaLayer1Id, ttfStyleId)
        self.addRevolvedSurfaces(database.getModelSpaceId(), 6, 9,
        odaLayer1Id, ttfStyleId)
        self.addPlaneSurfaces(database.getModelSpaceId(), 6, 10, odaLayer1Id,
        ttfStyleId)
        self.addLoftedSurfaces(database.getModelSpaceId(), 7, 0, odaLayer1Id,
        ttfStyleId)
        self.addSweptSurfaces(database.getModelSpaceId(), 7, 1, odaLayer1Id,
        ttfStyleId)
        self.addNURBSurface(database, 7, 2, odaLayer1Id, ttfStyleId)
        ######################################################################
        # Add some MLeaders #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addMLeaders(database.getModelSpaceId(), 7, 3, odaLayer1Id,
        ttfStyleId)
        
        ######################################################################
        # Add a 3D Solid Box by BrepBuilder #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.add3dSolidBox(database, 7, 5, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a Cylinder by BrepBuilder #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addBRepCylinder(database, 7, 6, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a Cylinder by BrepBuilder #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addSeamedCylinder(database, 7, 7, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add PointCloud #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addPointCloud(database, 7, 8, odaLayer1Id, ttfStyleId)
        
        ######################################################################
        # Add a Layout #
        ######################################################################
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr2)
        tr2 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        self.addLayout(database)
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr1)
        return
    

