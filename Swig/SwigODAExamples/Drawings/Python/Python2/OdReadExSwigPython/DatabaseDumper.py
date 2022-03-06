#######################################################################################
# Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
# All rights reserved. 
# 
# This software and its documentation and related materials are owned by 
# the Alliance. The software may only be incorporated into application 
# programs owned by members of the Alliance, subject to a signed 
# Membership Agreement and Supplemental Software License Agreement with the
# Alliance. The structure and organization of this software are the valuable  
# trade secrets of the Alliance and its suppliers. The software is also 
# protected by copyright law and international treaty provisions. Application  
# programs incorporating this software must include the following statement 
# with their copyright notices:
#   
#   This application incorporates Open Design Alliance software pursuant to a license 
#   agreement with Open Design Alliance.
#   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
#   All rights reserved.
#
# By use of this software, its documentation or related materials, you 
# acknowledge and accept the above terms.
#######################################################################################

from ODA_PyMemManager import *
from ODA_Kernel import *
from ODA_Drawings import *
import os

class DatabaseDumper():
     def toString(self,val):
     # type: (ODA_Drawings.OdDbObjectId) -> str
        if(val.isNull() == None):
          return "Null"
        if (val.isErased()):
          return "Erased"

        #/**********************************************************************/
        #/* Open the object */
        #/**********************************************************************/
        pObject = val.safeOpenObject()

        #/**********************************************************************/
        #/* Return the name of an OdDbSymbolTableRecord */
        #/**********************************************************************/
        if (pObject is OdDbSymbolTableRecord):
          pSTR = pObject
          return pSTR.getName()


        #/**********************************************************************/
        #/* Return the name of an OdDbMlineStyle */
        #/**********************************************************************/
        if (pObject is OdDbMlineStyle):
          pStyle = pObject
          return pStyle.name()

        #/**********************************************************************/
        #/* Return the name of a PlotStyle */
        #/**********************************************************************/
        if (pObject is OdDbPlaceHolder):
          pDictionary = val.database().getPlotStyleNameDictionaryId().safeOpenObject()
          plotStyleName = pDictionary.nameAt(val)
          return plotStyleName

        #/**********************************************************************/
        #/* Return the name of an OdDbMaterial */
        #/**********************************************************************/
        if (pObject is OdDbMaterial):
          pMaterial = pObject
          return pMaterial.name()

        #/**********************************************************************/
        #/* We don't know what it is, so return the description of the object
        #*/
        #/* object specified by the ObjectId */
        #/**********************************************************************/
        return pObject.isA().name()

     def dump(self, database):
      # type: (ODA_Drawings.OdDatabase) -> None
        self.dumpSummaryInfo(database)
        self.dumpHeader(database)
        self.dumpLayouts(database)
        self.dumpBlocks(database)

     def dumpSummaryInfo(self,database):
      # type: (ODA_Drawings.OdDatabase) -> None
      sumInfo = oddbGetSummaryInfo(database)
      title = sumInfo.getTitle()
      subject = sumInfo.getSubject()
      Author = sumInfo.getAuthor()
      Comments = sumInfo.getComments()
      Keywords = sumInfo.getKeywords()
      LastSavedBy = sumInfo.getLastSavedBy()
      RevisionNumber = sumInfo.getRevisionNumber()

      print("\nSummaryInfo:")
      print("Title: = {0}\n".format(title))
      print("Subject: = {0}\n".format(subject))
      print("Author: = {0}\n".format(Author))
      print("Comments: = {0}\n".format(Comments))
      print("Keywords: = {0}\n".format(Keywords))
      print("LastSavedBy: = {0}\n".format(LastSavedBy))
      print("RevisionNumber: = {0}\n".format(RevisionNumber))

      numSummaryInfo = sumInfo.numCustomInfo()
      if(numSummaryInfo != 0):
        print("Number of custom info: = {0}\n".format(numSummaryInfo))
        for idx in range(numSummaryInfo):
          key,value = sumInfo.getCustomSummaryInfo(idx)
          print("Key: = {0}\n".format(key))
          print("Value: = {0}\n".format(value))

     def dumpHeader(self,database):
     # type: (ODA_Drawings.OdDatabase) -> None
      print("\n")
      print("Filename: = {0}\n".format(os.path.basename(database.getFilename())))

      print("File DWG Version: = {0}\n".format((database.originalFileVersion())))

      print("\n")
      print("Header Variables:\n")

      print("\n")
      Date = database.getTDCREATE()

      print("TDCREATE: = {0}/{1}/{2} {3}:{4}:{5}\n".format(Date.year(), Date.month(), Date.day(), Date.hour(), Date.minute(), Date.second()))
      Date = database.getTDUPDATE()
      print("TDUPDATE: = {0}/{1}/{2} {3}:{4}:{5}\n".format(Date.year(), Date.month(), Date.day(), Date.hour(), Date.minute(), Date.second()))

      print("\n")
      print("ANGBASE = {0}\n".format((database.getANGBASE())))
      print("ANGDIR = {0}\n".format((database.getANGDIR())))
      print("ATTMODE = {0}\n".format((database.getATTMODE())))
      print("AUNITS = {0}\n".format((database.getAUNITS())))
      print("AUPREC = {0}\n".format((database.getAUPREC())))
      print("CECOLOR = {0}\n".format((database.getCECOLOR().color())))
      print("CELTSCALE = {0}\n".format((database.getCELTSCALE())))
      print("CHAMFERA = {0}\n".format((database.getCHAMFERA())))
      print("CHAMFERB = {0}\n".format((database.getCHAMFERB())))
      print("CHAMFERC = {0}\n".format((database.getCHAMFERC())))
      print("CHAMFERD = {0}\n".format((database.getCHAMFERD())))
      print("CMLJUST = {0}\n".format((database.getCMLJUST())))
      print("CMLSCALE = {0}\n".format((database.getCMLSCALE())))
      print("DIMADEC = {0}\n".format((database.dimadec())))
      print("DIMALT = {0}\n".format((database.dimalt())))
      print("DIMALTD = {0}\n".format((database.dimaltd())))
      print("DIMALTF = {0}\n".format((database.dimaltf())))
      print("DIMALTRND = {0}\n".format((database.dimaltrnd())))
      print("DIMALTTD = {0}\n".format((database.dimalttd())))
      print("DIMALTTZ = {0}\n".format((database.dimalttz())))
      print("DIMALTU = {0}\n".format((database.dimaltu())))
      print("DIMALTZ = {0}\n".format((database.dimaltz())))
      print("DIMAPOST = {0}\n".format((database.dimapost())))
      print("DIMASZ = {0}\n".format((database.dimasz())))
      print("DIMATFIT = {0}\n".format((database.dimatfit())))
      print("DIMAUNIT = {0}\n".format((database.dimaunit())))
      print("DIMAZIN = {0}\n".format((database.dimazin())))
      print("DIMBLK = {0}\n".format(self.toString(database.dimblk())))
      print("DIMBLK1 = {0}\n".format(self.toString(database.dimblk1())))
      print("DIMBLK2 = {0}\n".format(self.toString(database.dimblk2())))
      print("DIMCEN = {0}\n".format((database.dimcen())))
      print("DIMCLRD = {0}\n".format((database.dimclrd().color())))
      print("DIMCLRE = {0}\n".format((database.dimclre().color())))
      print("DIMCLRT = {0}\n".format((database.dimclrt().color())))
      print("DIMDEC = {0}\n".format((database.dimdec())))
      print("DIMDLE = {0}\n".format((database.dimdle())))
      print("DIMDLI = {0}\n".format((database.dimdli())))
      print("DIMDSEP = {0}\n".format((database.dimdsep())))
      print("DIMEXE = {0}\n".format((database.dimexe())))
      print("DIMEXO = {0}\n".format((database.dimexo())))
      print("DIMFRAC = {0}\n".format((database.dimfrac())))
      print("DIMGAP = {0}\n".format((database.dimgap())))
      print("DIMJUST = {0}\n".format((database.dimjust())))
      print("DIMLDRBLK = {0}\n".format(self.toString(database.dimldrblk())))
      print("DIMLFAC = {0}\n".format((database.dimlfac())))
      print("DIMLIM = {0}\n".format((database.dimlim())))
      print("DIMLUNIT = {0}\n".format((database.dimlunit())))
      print("DIMLWD = {0}\n".format((database.dimlwd())))
      print("DIMLWE = {0}\n".format((database.dimlwe())))
      print("DIMPOST = {0}\n".format((database.dimpost())))
      print("DIMRND = {0}\n".format((database.dimrnd())))
      print("DIMSAH = {0}\n".format((database.dimsah())))
      print("DIMSCALE = {0}\n".format((database.dimscale())))
      print("DIMSD1 = {0}\n".format((database.dimsd1())))
      print("DIMSD2 = {0}\n".format((database.dimsd2())))
      print("DIMSE1 = {0}\n".format((database.dimse1())))
      print("DIMSE2 = {0}\n".format((database.dimse2())))
      print("DIMSOXD = {0}\n".format((database.dimsoxd())))
      print("DIMTAD = {0}\n".format((database.dimtad())))
      print("DIMTDEC = {0}\n".format((database.dimtdec())))
      print("DIMTFAC = {0}\n".format((database.dimtfac())))
      print("DIMTIH = {0}\n".format((database.dimtih())))
      print("DIMTIX = {0}\n".format((database.dimtix())))
      print("DIMTM = {0}\n".format((database.dimtm())))
      print("DIMTOFL = {0}\n".format((database.dimtofl())))
      print("DIMTOH = {0}\n".format((database.dimtoh())))
      print("DIMTOL = {0}\n".format((database.dimtol())))
      print("DIMTOLJ = {0}\n".format((database.dimtolj())))
      print("DIMTP = {0}\n".format((database.dimtp())))
      print("DIMTSZ = {0}\n".format((database.dimtsz())))
      print("DIMTVP = {0}\n".format((database.dimtvp())))
      print("DIMTXSTY = {0}\n".format(self.toString(database.dimtxsty())))
      print("DIMTXT = {0}\n".format((database.dimtxt())))
      print("DIMTZIN = {0}\n".format((database.dimtzin())))
      print("DIMUPT = {0}\n".format((database.dimupt())))
      print("DIMZIN = {0}\n".format((database.dimzin())))
      print("DISPSILH = {0}\n".format((database.getDISPSILH())))
      print("DRAWORDERCTL = {0}\n".format((database.getDRAWORDERCTL())))
      print("ELEVATION = {0}\n".format((database.getELEVATION())))
      print("EXTMAX = ({0},{1},{2})\n".format(database.getEXTMAX().x,database.getEXTMAX().y,database.getEXTMAX().z))
      print("EXTMIN = ({0},{1},{2})\n".format(database.getEXTMIN().x,database.getEXTMIN().y,database.getEXTMIN().z))
      print("FACETRES = {0}\n".format((database.getFACETRES())))
      print("FILLETRAD = {0}\n".format((database.getFILLETRAD())))
      print("FILLMODE = {0}\n".format((database.getFILLMODE())))
      print("INSBASE = ({0},{1},{2})\n".format(database.getINSBASE().x,database.getINSBASE().y,database.getINSBASE().z))
      print("ISOLINES = {0}\n".format((database.getISOLINES())))
      print("LIMCHECK = {0}\n".format((database.getLIMCHECK())))
      print("LIMMAX = ({0},{1})\n".format(database.getLIMMAX().x,database.getLIMMAX().y))
      print("LIMMIN = ({0},{1})\n".format(database.getLIMMIN().x,database.getLIMMIN().y))
      print("LTSCALE = {0}\n".format((database.getLTSCALE())))
      print("LUNITS = {0}\n".format((database.getLUNITS())))
      print("LUPREC = {0}\n".format((database.getLUPREC())))
      print("MAXACTVP = {0}\n".format((database.getMAXACTVP())))
      print("MIRRTEXT = {0}\n".format((database.getMIRRTEXT())))
      print("ORTHOMODE = {0}\n".format((database.getORTHOMODE())))
      print("PDMODE = {0}\n".format((database.getPDMODE())))
      print("PDSIZE = {0}\n".format((database.getPDSIZE())))
      print("PELEVATION = {0}\n".format((database.getPELEVATION())))
      print("PELLIPSE = {0}\n".format((database.getPELLIPSE())))
      print("PEXTMAX = ({0},{1},{2})\n".format(database.getPEXTMAX().x,database.getPEXTMAX().y,database.getPEXTMAX().z))
      print("PEXTMIN = ({0},{1},{2})\n".format(database.getPEXTMIN().x,database.getPEXTMIN().y,database.getPEXTMIN().z))
      print("PINSBASE = ({0},{1},{2})\n".format(database.getPINSBASE().x,database.getPINSBASE().y,database.getPINSBASE().z))
      print("PLIMCHECK = {0}\n".format((database.getPLIMCHECK())))
      print("PLIMMAX = ({0},{1})\n".format(database.getPLIMMAX().x,database.getPLIMMAX().y))
      print("PLIMMIN = ({0},{1})\n".format(database.getPLIMMIN().x,database.getPLIMMIN().y))
      print("PLINEGEN = {0}\n".format((database.getPLINEGEN())))
      print("PLINEWID = {0}\n".format((database.getPLINEWID())))
      print("PROXYGRAPHICS = {0}\n".format((database.getPROXYGRAPHICS())))
      print("PSLTSCALE = {0}\n".format((database.getPSLTSCALE())))
      print("PUCSNAME = {0}\n".format(self.toString(database.getPUCSNAME())))
      print("PUCSORG = ({0},{1},{2})\n".format(database.getPUCSORG().x,database.getPUCSORG().y,database.getPUCSORG().z))
      print("PUCSXDIR = ({0},{1},{2})\n".format(database.getPUCSXDIR().x,database.getPUCSXDIR().y,database.getPUCSXDIR().z))
      print("PUCSYDIR = ({0},{1},{2})\n".format(database.getPUCSYDIR().x,database.getPUCSYDIR().y,database.getPUCSYDIR().z))
      print("QTEXTMODE = {0}\n".format((database.getQTEXTMODE())))
      print("REGENMODE = {0}\n".format((database.getREGENMODE())))
      print("SHADEDGE = {0}\n".format((database.getSHADEDGE())))
      print("SHADEDIF = {0}\n".format((database.getSHADEDIF())))
      print("SKETCHINC = {0}\n".format((database.getSKETCHINC())))
      print("SKPOLY = {0}\n".format((database.getSKPOLY())))
      print("SPLFRAME = {0}\n".format((database.getSPLFRAME())))
      print("SPLINESEGS = {0}\n".format((database.getSPLINESEGS())))
      print("SPLINETYPE = {0}\n".format((database.getSPLINETYPE())))
      print("SURFTAB1 = {0}\n".format((database.getSURFTAB1())))
      print("SURFTAB2 = {0}\n".format((database.getSURFTAB2())))
      print("SURFTYPE = {0}\n".format((database.getSURFTYPE())))
      print("SURFU = {0}\n".format((database.getSURFU())))
      print("SURFV = {0}\n".format((database.getSURFV())))
      print("TEXTQLTY = {0}\n".format((database.getTEXTQLTY())))
      print("TEXTSIZE = {0}\n".format((database.getTEXTSIZE())))
      print("THICKNESS = {0}\n".format((database.getTHICKNESS())))
      print("TILEMODE = {0}\n".format((database.getTILEMODE())))
      print("TRACEWID = {0}\n".format((database.getTRACEWID())))
      print("TREEDEPTH = {0}\n".format((database.getTREEDEPTH())))
      print("UCSNAME = {0}\n".format(self.toString(database.getUCSNAME())))
      print("UCSORG = ({0},{1},{2})\n".format(database.getUCSORG().x,database.getUCSORG().y,database.getUCSORG().z))
      print("UCSXDIR = ({0},{1},{2})\n".format(database.getUCSXDIR().x,database.getUCSXDIR().y,database.getUCSXDIR().z))
      print("UCSYDIR = ({0},{1},{2})\n".format(database.getUCSYDIR().x,database.getUCSYDIR().y,database.getUCSYDIR().z))
      print("UNITMODE = {0}\n".format((database.getUNITMODE())))
      print("USERI1 = {0}\n".format((database.getUSERI1())))
      print("USERI2 = {0}\n".format((database.getUSERI2())))
      print("USERI3 = {0}\n".format((database.getUSERI3())))
      print("USERI4 = {0}\n".format((database.getUSERI4())))
      print("USERI5 = {0}\n".format((database.getUSERI5())))
      print("USERR1 = {0}\n".format((database.getUSERR1())))
      print("USERR2 = {0}\n".format((database.getUSERR2())))
      print("USERR3 = {0}\n".format((database.getUSERR3())))
      print("USERR4 = {0}\n".format((database.getUSERR4())))
      print("USERR5 = {0}\n".format((database.getUSERR5())))
      print("USRTIMER = {0}\n".format((database.getUSRTIMER())))
      print("VISRETAIN = {0}\n".format((database.getVISRETAIN())))
      print("WORLDVIEW = {0}\n".format((database.getWORLDVIEW())))

     def dumpLayouts(self,database):
     # type: (ODA_Drawings.OdDatabase) -> None
        pLayoutDict = database.getLayoutDictionaryId().safeOpenObject()
        pIter = pLayoutDict.newIterator()
        while(not pIter.done()):
            id = pIter.objectId()
            pEntry = OdDbLayout_cast(id.safeOpenObject())
            if (pEntry == None):
                continue
            
            print("\n")
            print((pEntry.isA().name()))
            print("Name = {0}", (pEntry.getLayoutName()))
            pBlock = pEntry.getBlockTableRecordId().safeOpenObject()
            if (pBlock != None):
                print((pBlock.isA().name()))
                print("Name = {0}", (pBlock.getName()))
                extents = OdGeExtents3d()
                res = pBlock.getGeomExtents(extents)
                if (int(eOk) == res):
                    print("Min Extents = ({0},{1},{2})".format(extents.minPoint().x,extents.minPoint().y,extents.minPoint().z))
                    print("Max Extents = ({0},{1},{2})".format(extents.maxPoint().x,extents.maxPoint().y,extents.maxPoint().z))
                else:
                    print("   Incorrect extents")
            pIter.next()

     def dumpBlocks(self,database):
     # type: (ODA_Drawings.OdDatabase) -> None
      tr = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
      #/**********************************************************************/
      #/* Get a SmartPointer to the BlockTable                               */
      #/**********************************************************************/

      pTable = database.getBlockTableId().safeOpenObject()

      #/**********************************************************************/
      #/* Dump the Description                                               */
      #/**********************************************************************/
      print(pTable.isA().name())

      #/**********************************************************************/
      #/* Step through the BlockTable                                        */
      #/**********************************************************************/
      pBlkIter = pTable.newIterator()
      pBlkIter.start()
      while(not pBlkIter.done()):
        tr1 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        #/********************************************************************/
        #/* Open the BlockTableRecord for Reading                            */
        #/********************************************************************/
        pBlock = pBlkIter.getRecordId().safeOpenObject();

        #/********************************************************************/
        #/* Dump the BlockTableRecord                                        */
        #/********************************************************************/
        print(" ");
        print((pBlock.isA().name()))
        print("Name = {0}".format(pBlock.getName()))
        print("Anonymous = {0}".format(pBlock.isAnonymous()))
        print("Comments = {0}".format(pBlock.comments()))
        print("Origin = ({0},{1},{2})".format(pBlock.origin().x,pBlock.origin().y,pBlock.origin().z))
        print("Block Insert Units = {0}".format(pBlock.blockInsertUnits())) #debug C++
        print("Block Scaling = {0}".format(pBlock.blockScaling())) #debug C++
        print("Explodable = {0}".format(pBlock.explodable()))

        extents = OdGeExtents3d();
        if (eOk == pBlock.getGeomExtents(extents)):
          print("Min Extents = ({0},{1},{2})".format(extents.minPoint().x,extents.minPoint().y,extents.minPoint().z))
          print("Max Extents = ({0},{1},{2})".format(extents.maxPoint().x,extents.maxPoint().y,extents.maxPoint().z))

        print("Layout = {0}".format(pBlock.isLayout()))
        print("Has Attribute Definitions = {0}".format(pBlock.hasAttributeDefinitions()));
        print("Xref Status = {0}".format(pBlock.xrefStatus()));
        if (pBlock.xrefStatus() != kXrfNotAnXref):
          print("Xref Path = {0}".format(pBlock.pathName()));
          print("From Xref Attach = {0}".format(pBlock.isFromExternalReference()));
          print("From Xref Overlay = {0}".format(pBlock.isFromOverlayReference()));
          print("Xref Unloaded = {0}".format(pBlock.isUnloaded()));

        pEntIter = pBlock.newIterator();
        pEntIter.start()

        while(not pEntIter.done()):
            self.dumpEntity(pEntIter.objectId());
            pEntIter.step()

        pBlkIter.step()
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr1)

      ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr)
      return

     def dumpEntity(self,id):
     # type: (ODA_Drawings.OdDbObjectId) -> None
        #/**********************************************************************/
        #/* Get a SmartPointer to the Entity                                   */
        #/**********************************************************************/
        tr = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
        res, pEnt = id.openObject()
        if(res == eOk):
            pEnt = OdDbEntity_cast(pEnt);
        #    if (pEnt != None):
        #        #/**********************************************************************/
        #        #/* Dump Entity Class Name                                             */
        #        #/**********************************************************************/
        #        print("Entity class: {0}".format(pEnt.isA().name()))
        ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr)

