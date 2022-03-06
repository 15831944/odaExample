QT += quick
QT += widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


INCLUDEPATH += $$PWD/../../../../ThirdParty/activation
INCLUDEPATH += $$PWD/../../../../Visualize/Include
INCLUDEPATH += $$PWD/../../../../Components/OBJToolkit/Include
INCLUDEPATH += $$PWD/../../../../Kernel/Include
INCLUDEPATH += $$PWD/../../../..//Kernel/Extensions/ExServices
INCLUDEPATH += $$PWD/../../../../Drawing/Include
INCLUDEPATH += $$PWD/../../../../Drawing/Extensions/ExServices
INCLUDEPATH += $$PWD/../../../../Kernel/Extensions/BrepBuilderFiller/Include
INCLUDEPATH += $$PWD/../../../../Kernel/DevInclude/DbRoot
INCLUDEPATH += $$PWD/../../../../ThirdParty/tinyxml
INCLUDEPATH += $$PWD/../../../../Kernel/DevInclude/IBr
INCLUDEPATH += $$PWD/../../../../Prc/Include

HEADERS += \
    ../../../../Drawing/Extensions/ExServices/ExHostAppServices.h \
    ../../../../Drawing/Examples/iOS/iCommon/iOdaAppServices.h \
    ../../../../Drawing/Examples/iOS/iCommon/ExHostAppServices.h \
    tvidatabaseinfo.h \
    tvicontroller.h \
    tviview.h \
    Draggers/tvipandragger.h \
    Draggers/tviorbitdragger.h \
    Draggers/tvizoomwindowdragger.h \
    tvithreadcontroller.h \
    tvifileopenthreadtask.h \
    tviutils.h \
    TviImportParamsController.h \
    TviAppearanceParams.h \
    TviMemoryStatus.h \
    TviLimitManager.h

SOURCES += \
    ../../../../Drawing/Extensions/ExServices/ExHostAppServices.cpp \
    ../../../../Drawing/Examples/iOS/iCommon/iOdaAppServices.cpp \
    Draggers/tvipandragger.cpp \
    Draggers/tviorbitdragger.cpp \
    Draggers/tvizoomwindowdragger.cpp \
    tvithreadcontroller.cpp \
    tvifileopenthreadtask.cpp \
    tviutils.cpp \
    tviview.cpp \
    tvicontroller.cpp \
    main.cpp \
    TviImportParamsController.cpp \
    TviAppearanceParams.cpp \
    TviLimitManager.cpp

ios {

CONFIG(debug, release|debug){
#LIBSPATH = /../../../../lib/iphone_12.0simdbg/
LIBSPATH = /../../../../lib/iphone_12.0dbg/
} else {
LIBSPATH = /../../../../lib/iphone_12.0/
}

LIBS += -framework OpenGLES

QMAKE_TARGET_BUNDLE_PREFIX = com.OpenDesignAlliance
QMAKE_BUNDLE = IOSVisualizeViewer
QMAKE_INFO_PLIST = $$PWD/iOSSettingsFiles/Info.plist
QMAKE_ASSET_CATALOGS += $$PWD/iOSSettingsFiles/Images.xcassets
QMAKE_ASSET_CATALOGS += $$PWD/iOSSettingsFiles/ODALaunch.xib
# copy scheme file to assets(need for open vsf files)
CONFIG(debug, release|debug){
QMAKE_ASSET_CATALOGS += $$PWD/../../../../bin/iphone_12.0dbg/TD.tsbf
} else {
QMAKE_ASSET_CATALOGS += $$PWD/../../../../bin/iphone_12.0/TD.tsbf
}

OBJECTIVE_SOURCES += \
    TviMemoryStatus.mm
}

INCLUDEPATH += $$PWD$${LIBSPATH}
DEPENDPATH += $$PWD$${LIBSPATH}

LIBS += -L$$PWD$${LIBSPATH} -lTV_Visualize
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTV_Visualize.a
LIBS += -L$$PWD$${LIBSPATH} -lTV_VisualizeTools
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTV_VisualizeTools.a
LIBS += -L$$PWD$${LIBSPATH} -lExVisualizeDevice
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libExVisualizeDevice.a
LIBS += -L$$PWD$${LIBSPATH} -lVisualizeModelsGenerator
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libVisualizeModelsGenerator.a
LIBS += -L$$PWD$${LIBSPATH} -lObj2Visualize
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libObj2Visualize.a
LIBS += -L$$PWD$${LIBSPATH} -lOBJToolkit
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libOBJToolkit.a
LIBS += -L$$PWD$${LIBSPATH} -lStl2Visualize
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libStl2Visualize.a
LIBS += -L$$PWD$${LIBSPATH} -lSTLImport
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libSTLImport.a
LIBS += -L$$PWD$${LIBSPATH} -lDwg2Visualize
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libDwg2Visualize.a
LIBS += -L$$PWD$${LIBSPATH} -lRcs2Visualize
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libRcs2Visualize.a
LIBS += -L$$PWD$${LIBSPATH} -lExFieldEvaluator
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libExFieldEvaluator.a
LIBS += -L$$PWD$${LIBSPATH} -lAcDbPointCloudObj
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libAcDbPointCloudObj.a
LIBS += -L$$PWD$${LIBSPATH} -lPointCloudHost
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libPointCloudHost.a
LIBS += -L$$PWD$${LIBSPATH} -lRcsFileServices
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libRcsFileServices.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Ge
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Ge.a
LIBS += -L$$PWD$${LIBSPATH} -lRecomputeDimBlock
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libRecomputeDimBlock.a
LIBS += -L$$PWD$${LIBSPATH} -lRasterProcessor
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libRasterProcessor.a
LIBS += -L$$PWD$${LIBSPATH} -lDbCryptModule
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libDbCryptModule.a
# render
LIBS += -L$$PWD$${LIBSPATH} -lTrVec
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTrVec.a
LIBS += -L$$PWD$${LIBSPATH} -lTrGL2
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTrGL2.a
LIBS += -L$$PWD$${LIBSPATH} -lTrBase
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTrBase.a
LIBS += -L$$PWD$${LIBSPATH} -lTrRenderBase
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTrRenderBase.a
LIBS += -L$$PWD$${LIBSPATH} -lWinGLES2
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libWinGLES2.a

LIBS += -L$$PWD$${LIBSPATH} -lVsf2Visualize
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libVsf2Visualize.a

LIBS += -L$$PWD$${LIBSPATH} -lTD_Db
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Db.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_DbIO
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_DbIO.a
LIBS += -L$$PWD$${LIBSPATH} -lISM
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libISM.a
LIBS += -L$$PWD$${LIBSPATH} -lSCENEOE
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libSCENEOE.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_DbRoot
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_DbRoot.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_DynBlocks
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_DynBlocks.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Gs
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Gs.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Gi
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Gi.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_SpatialIndex
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_SpatialIndex.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_BrepRenderer
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_BrepRenderer.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Ge
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Ge.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Root
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Root.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Alloc
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Alloc.a
LIBS += -L$$PWD$${LIBSPATH} -lFreeType
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libFreeType.a
LIBS += -L$$PWD$${LIBSPATH} -lRxRasterServices
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libRxRasterServices.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Zlib
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Zlib.a
LIBS += -L$$PWD$${LIBSPATH} -llibcrypto
PRE_TARGETDEPS += $$PWD$${LIBSPATH}liblibcrypto.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Br
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Br.a
LIBS += -L$$PWD$${LIBSPATH} -lUTF
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libUTF.a
LIBS += -L$$PWD$${LIBSPATH} -lACCAMERA
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libACCAMERA.a
LIBS += -L$$PWD$${LIBSPATH} -lAcMPolygonObj15
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libAcMPolygonObj15.a
LIBS += -L$$PWD$${LIBSPATH} -lWipeOut
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libWipeOut.a
LIBS += -L$$PWD$${LIBSPATH} -lATEXT
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libATEXT.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_DbCore
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_DbCore.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_DbEntities
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_DbCore.a
LIBS += -L$$PWD$${LIBSPATH} -lRText
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libRText.a
LIBS += -L$$PWD$${LIBSPATH} -lFreeImage
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libFreeImage.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Tf
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Tf.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_TfCore
PRE_TARGETDEPS += $$PWD$${LIBSPATH}liblibTD_TfCore.a
LIBS += -L$$PWD$${LIBSPATH} -ltinyxml
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libtinyxml.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_BrepBuilderFiller
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_BrepBuilderFiller.a
LIBS += -L$$PWD$${LIBSPATH} -lOdBrepModeler
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libOdBrepModeler.a
LIBS += -L$$PWD$${LIBSPATH} -lModelerGeometry
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libModelerGeometry.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_AcisBuilder
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_AcisBuilder.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_BrepBuilder
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_BrepBuilder.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_STLExport
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_STLExport.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_PdfExport
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_PdfExport.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_PDFToolkit
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_PDFToolkit.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_SvgExport
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_SvgExport.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_RasterExport
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_RasterExport.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_2dExport
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_2dExport.a
LIBS += -L$$PWD$${LIBSPATH} -lstsflib
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libstsflib.a
LIBS += -L$$PWD$${LIBSPATH} -lqpdf
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libqpdf.a
LIBS += -L$$PWD$${LIBSPATH} -lpcre
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libpcre.a
LIBS += -L$$PWD$${LIBSPATH} -lWinOpenGL
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libWinOpenGL.a
LIBS += -L$$PWD$${LIBSPATH} -lWinBitmap
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libWinBitmap.a
LIBS += -L$$PWD$${LIBSPATH} -lPlotStyleServices
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libPlotStyleServices.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_OpenGL
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_OpenGL.a
# Rcs2Visualize
LIBS += -L$$PWD$${LIBSPATH} -llibXML
PRE_TARGETDEPS += $$PWD$${LIBSPATH}liblibXML.a
LIBS += -L$$PWD$${LIBSPATH} -lDbConstraints
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libDbConstraints.a
LIBS += -L$$PWD$${LIBSPATH} -lDwfToolkit
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libDwfToolkit.a
LIBS += -L$$PWD$${LIBSPATH} -lDwfCore
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libDwfCore.a
LIBS += -L$$PWD$${LIBSPATH} -lDwfxSignatureHandler
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libDwfxSignatureHandler.a
LIBS += -L$$PWD$${LIBSPATH} -lTDwfDb
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTDwfDb.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_DwfUnderlay
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_DwfUnderlay.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_Dwf7Import
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_Dwf7Import.a
LIBS += -L$$PWD$${LIBSPATH} -lExCustObjs
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libExCustObjs.a
LIBS += -L$$PWD$${LIBSPATH} -lWhipTk
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libWhipTk.a
LIBS += -L$$PWD$${LIBSPATH} -lW3dTk
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libW3dTk.a
LIBS += -L$$PWD$${LIBSPATH} -lminizip_mem
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libminizip_mem.a
# Dgn2Visualize
LIBS += -L$$PWD$${LIBSPATH} -lDgn2Visualize
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libDgn2Visualize.a
LIBS += -L$$PWD$${LIBSPATH} -lTG_Db
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTG_Db.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_DgnDb
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_DgnDb.a
LIBS += -L$$PWD$${LIBSPATH} -lTG_Dgn7IO
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTG_Dgn7IO.a
LIBS += -L$$PWD$${LIBSPATH} -loless
PRE_TARGETDEPS += $$PWD$${LIBSPATH}liboless.a
# Prc2Visualize
LIBS += -L$$PWD$${LIBSPATH} -lPrc2Visualize
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libPrc2Visualize.a
LIBS += -L$$PWD$${LIBSPATH} -lTD_PrcDb
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_PrcDb.a
LIBS += -L$$PWD$${LIBSPATH} -lOdPrcModule
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libOdPrcModule.a
# Dwg2Visualize
LIBS += -L$$PWD$${LIBSPATH} -lTD_DrawingsExamplesCommon
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libTD_DrawingsExamplesCommon.a
LIBS += -L$$PWD$${LIBSPATH} -lThreadPool
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libThreadPool.a
# Partial viewing
LIBS += -L$$PWD$${LIBSPATH} -lOdDbPartialViewing
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libOdDbPartialViewing.a

LIBS += -L$$PWD$${LIBSPATH} -lRxCommonDataAccess
PRE_TARGETDEPS += $$PWD$${LIBSPATH}libRxCommonDataAccess.a
