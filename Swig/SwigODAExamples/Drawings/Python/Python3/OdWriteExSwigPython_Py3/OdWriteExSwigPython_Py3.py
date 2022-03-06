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
from OdActivationInfo import *
from DatabaseFiller_Py3 import *
import sys
import os

class SystemServices(RxSystemServicesImpl):
    def __init__(self):
        RxSystemServicesImpl.__init__(self)
        ODA_Kernel_Py3.odActivate(ActivationData.userInfo,ActivationData.userSignature)

class UserApplicationServices(ExHostAppServices):
    def __init__(self):
      ExHostAppServices.__init__(self)
    def product(self):
      return "ODA Drawings Python"

def main(argv):

    #Check input application arguments
    if(len(sys.argv) < 2):
        print("Incorrect input args:")
        print("Usage: OdWriteExSwigPython_Py3.py <dwg_path>")
        sys.exit(2)
    
    #Get path to dwg file
    dwgFilePath = sys.argv[1]

    #Start Memory Transaction
    tr1 = ODA_PyMemoryManager_Get_MemoryManager().StartTransaction()
    
    #Create ODA System Services
    systemServices = SystemServices()
    
    #Initialize ODA SDK
    odInitialize(systemServices)
    
    #Create Host Application Services
    hostApp = UserApplicationServices()

    #Show ODA SDK Summary Info
    libInfo = oddbGetLibraryInfo()
    print("OdWriteExSwigPython_Py3 developed using {0} ver {1}\n".format(hostApp.product(), hostApp.versionString()))
    print("OdWriteExSwigPython_Py3 developed using minor major ver {0}\n".format(hostApp.releaseMajorMinorString()))
    print("OdDbLibraryInfo  libVer {0} buildComments {1}\n".format(libInfo.getLibVersion(), libInfo.getBuildComments()))
    
    # Create a default OdDbDatabase object
    database = hostApp.createDatabase(True, ODA_Kernel_Py3.kEnglish)
    pSumInfo = oddbGetSummaryInfo(database)
    pSumInfo.setComments("File was created by OdWriteExSwigPython_Py3")
    oddbPutSummaryInfo(pSumInfo)

    #Create Dwg Database Filler
    databaseFiller = DatabaseFiller_Py3()

    #Fill Dwg Database
    databaseFiller.fill(database)
    
    #######################################################################
    # Audit the database                                                  #
    #######################################################################
    aiAppAudit = OdDbAuditInfo()
    aiAppAudit.setFixErrors(True);
    aiAppAudit.setPrintDest(OdDbAuditInfo.kBoth)
    database.auditDatabase(aiAppAudit)

    fileType = OdDb_SaveType_kDwg
    outVer = vAC24
    #Write Dwg Database to filesystem
    database.writeFile(dwgFilePath, fileType, outVer, True)

    #Stop Memory Transaction
    ODA_PyMemoryManager_Get_MemoryManager().StopTransaction(tr1)
    
    #Unintialize ODA SDK
    odUninitialize()
    
    print("OdWriteExSwigPython_Py3 finished")

if __name__ == "__main__":
   main(sys.argv[1:])