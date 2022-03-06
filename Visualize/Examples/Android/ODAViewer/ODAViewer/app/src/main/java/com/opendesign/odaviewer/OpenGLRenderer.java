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

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class OpenGLRenderer implements GLSurfaceView.Renderer {

    public RenderActivity renderActivity = null;
    private boolean _bFirstPaint = true;

    @Override
    public void onDrawFrame(GL10 arg0) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        VisualizeSdkJni.update();

        if(_bFirstPaint)
        {
            _bFirstPaint = false;
            renderActivity.setupTotalTime();
        }
    }

    @Override
    public void onSurfaceChanged(GL10 arg0, int width, int height) {
        VisualizeSdkJni.resizeDevice(0, width, height, 0);
    }

    @Override
    public void onSurfaceCreated(GL10 arg0, EGLConfig arg1) {
        GLES20.glClearColor(0,0,0,1);
    }
}
