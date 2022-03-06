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
package com.opendesign.odaviewer;

import android.content.Context;
import android.util.Log;

import com.opendesign.odaviewer.ImportParams.DgnImportParams;
import com.opendesign.odaviewer.ImportParams.DwgImportParams;
import com.opendesign.odaviewer.ImportParams.ObjImportParams;
import com.opendesign.odaviewer.ImportParams.PrcImportParams;
import com.opendesign.odaviewer.ImportParams.StlImportParams;

public class VisualizeSdkJni {

    static {
        try {
            System.loadLibrary("visualize_sdk_jni");
        } catch (UnsatisfiedLinkError e) {
            Log.e("JNI", e.getMessage());
            Log.e("JNI", "ERROR: Could not load visualize_sdk_jni.so");
        }
    }

    public static native void activate();

    public static native void deactivate();

    public static native void release();

    public static native String openFile(String filePath);

    public static native  String lowMemoryOpenFile(String filePath, RenderActivity progressMeterController);

    public static native String setupDevice(Context context, int w, int h);

    public static native void update();

    public static native void resizeDevice(int xMin, int xMax, int yMin, int yMax);

    public static native int onTouchDown(int x, int y);

    public static native void onTouchMove(int x, int y);

    public static native int onTouchUp(int x, int y);

    public static native int onProcessEnter();

    public static native void onProcessBackspace();

    public static native void onProcessText(String text);

    public static native void zoom(double delta, int x, int y);

    public static native void runNavigationAction(int navAction);

    public static native void set3DView(int viewInd);

    public static native void regenVisible();

    public static native boolean isPerspective();

    public static native void setProjection(int projType);

    public static native void runRenderMode(int renderMode);

    public static native int getRenderMode();

    public static native void runMarkupAction(int markupCmd);

    public static native String isSaveMarkupAvaliable();

    public static native String saveMarkup(String markupName);

    public static native String isLoadMarkupAvaliable();

    public static native String loadMarkup(String markupName);

    public static native void getGlobalParams(GlobalSettings jParams);

    public static native void setGlobalParams(GlobalSettings jParams);

    public static native void applyGlobalParams();

    public static native void onAppearSectioningPanel(boolean bAppear);

    public static native boolean isCuttingPlanesVisible();

    public static native boolean isCuttingPlanesFilled();

    public static native void onShowCuttingPlanes();

    public static native void onAddCuttingPlanes(int x, int y, int z);

    public static native void onFillCuttingPlanes();

    public static native void onRemoveCuttingPlanes();

    public static native String runCollide();

    public static native void finishDragger();

    public static native long getTotalTime();

    public static native void getDwgImportParams(DwgImportParams dwgParams);

    public static native void setDwgImportParams(DwgImportParams dwgParams);

    public static native void getStlImportParams(StlImportParams stlParams);

    public static native void setStlImportParams(StlImportParams stlParams);

    public static native void getPrcImportParams(PrcImportParams prcParams);

    public static native void setPrcImportParams(PrcImportParams prcParams);

    public static native void getDgnImportParams(DgnImportParams dgnParams);

    public static native void setDgnImportParams(DgnImportParams dgnParams);

    public static native void getObjImportParams(ObjImportParams objParams);

    public static native void setObjImportParams(ObjImportParams objParams);

    public static native void saveFile(String fileName, boolean bPartialIndexing);

    public static native boolean addGroundShadow();

    public static native boolean isViewAllowGroundShadow();

    public static native boolean isPdfExportEnabled();

    public static native boolean exportToPdf(boolean b3D);
}
