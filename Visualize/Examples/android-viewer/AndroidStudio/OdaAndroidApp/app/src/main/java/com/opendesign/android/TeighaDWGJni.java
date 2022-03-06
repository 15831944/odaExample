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
package com.opendesign.android;

import android.content.Context;
import android.opengl.EGLContext;
import android.util.Log;
import android.view.Surface;

public class TeighaDWGJni {

    public enum LIBRARY {
        NONE, TEIGHA, ARCHITECTURE, CIVIL
    }
    public static LIBRARY loadedLibrary = LIBRARY.NONE;
    static {
        try {
            System.loadLibrary("teigha_civil_jni");
            loadedLibrary = LIBRARY.CIVIL;
        } catch (UnsatisfiedLinkError err1) {
          try {
            System.loadLibrary("teigha_architecture_jni");
            loadedLibrary = LIBRARY.ARCHITECTURE;
          } catch (UnsatisfiedLinkError err2) {
            try {
                System.loadLibrary("od_jni_for_vis");
                loadedLibrary = LIBRARY.TEIGHA;
            } catch (UnsatisfiedLinkError err3) {
                Log.e("JNI", err3.getMessage());
                Log.e("JNI", "WARNING: Could not load libod_jni_for_vis.so");
            }
          }
        }
    }
	public static native boolean init ();
	
	public static native boolean finit ();
	
	public static native boolean open ( String file );
	
	public static native boolean createRenderer (int xMin, int xMax, int yMin, int yMax, Context glContext);
	
	public static native boolean renderFrame ();
	
	// public static native boolean destroyRenderer ();
	
	// public static native boolean close ();

	 public static native boolean viewTranslate ( float xAxis, float yAxis );
	
	 public static native boolean viewScale ( float sCoef );
	
	// public static native boolean viewCanRotate ();
	
	public static native boolean viewRotate ( float rAngle );
	
	public static native boolean viewOrbit ( float xAxis, float yAxis );
	
	// public static native int viewGetRenderMode ();
	
	// public static native boolean saveContext ( int saveContextValue );

    public static native boolean setVisualStyle ( String selectedStyle);

    public static native boolean setRenderMode ( String selectedStyle);

    public static native boolean setViewPosition ( int pos );

    public static native boolean zoomExtents ();

    public static native boolean zoomWindow ( double xMin, double yMin, double xMax, double yMax);

    public static native boolean startSelectionFrame ( int x, int y);

    public static native boolean resizeSelectionFrame ( int x, int y);

    public static native boolean regenAll();

    public static native boolean regenActiveView();

    public static native boolean regenVisible();

    public static native boolean setProjectionForActiveView(int projection);

    public static native boolean createObjectExplorer();

    public static native int getChildrenCount(int index);

    public static native String[] getCurrentObjects();

    public static native int toParent();

    public static native boolean toChild(int index);
}
