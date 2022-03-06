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
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.View;
import android.view.inputmethod.InputMethodManager;
import android.widget.EditText;

public class TouchListener extends ScaleGestureDetector.SimpleOnScaleGestureListener implements GestureDetector.OnGestureListener {

    public boolean IsRequestKeyboard = false;
    public boolean IsLongClickEnabled = false;
    private RenderActivity mRenderActivity;

    public TouchListener(RenderActivity renderActivity) {
        mRenderActivity = renderActivity;
    }

    private void enableKeyboard() {
        if(IsRequestKeyboard) {
            EditText editText = mRenderActivity.findViewById(R.id.hiddenTextEdit);
            editText.setVisibility(View.VISIBLE);
            editText.requestFocus();
            InputMethodManager imm = (InputMethodManager) mRenderActivity.getSystemService(Context.INPUT_METHOD_SERVICE);
            if(imm != null) {
                imm.showSoftInput(editText, InputMethodManager.SHOW_IMPLICIT);
            }
            IsRequestKeyboard = false;
        } else {
            InputMethodManager imm = (InputMethodManager) mRenderActivity.getSystemService(Context.INPUT_METHOD_SERVICE);
            if(imm != null && imm.isActive()) {
                EditText editText = mRenderActivity.findViewById(R.id.hiddenTextEdit);
                editText.setVisibility(View.INVISIBLE);
                editText.clearFocus();
                imm.hideSoftInputFromWindow(editText.getWindowToken(), 0);
            }
        }
    }

    @Override
    public void onShowPress(MotionEvent e) {
    }

    @Override
    public boolean onDown(MotionEvent e) {
        if(e.getPointerCount() == 1) {
            int code = VisualizeSdkJni.onTouchDown((int)e.getX(), (int)e.getY());
            mRenderActivity.processDraggerResult(code);
            // show keyboard if needed
            enableKeyboard();
        }
        return false;
    }
    @Override
    public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
        if(e2.getAction() == MotionEvent.ACTION_MOVE) {
            if (e2.getPointerCount() == 1) {
                VisualizeSdkJni.onTouchMove((int) e2.getX(), (int) e2.getY());
            } else if (e2.getPointerCount() > 1) {
                int code = VisualizeSdkJni.onTouchUp((int) e2.getX(), (int) e2.getY());
                mRenderActivity.processDraggerResult(code);
            }
        }
        return false;
    }

    public void onTouchUp(MotionEvent e) {
        if(e.getPointerCount() == 1) {
            int code = VisualizeSdkJni.onTouchUp((int) e.getX(), (int) e.getY());
            mRenderActivity.processDraggerResult(code);
        }
    }

    @Override
    public boolean onSingleTapUp(MotionEvent e) {
        if(e.getPointerCount() == 1) {
            //VisualizeSdkJni.onTouchUp((int)e.getX(), (int)e.getY());
        }
        return false;
    }

    @Override
    public void onLongPress(MotionEvent e) {
        if(IsLongClickEnabled && e.getPointerCount() == 1) {
            int code = VisualizeSdkJni.onProcessEnter();
            mRenderActivity.processDraggerResult(code);
            IsLongClickEnabled = false;
        }
    }

    public void onCustomDoubleClick(MotionEvent e) {
        if(IsLongClickEnabled && e.getPointerCount() == 1) {
            int code = VisualizeSdkJni.onProcessEnter();
            mRenderActivity.processDraggerResult(code);
            IsLongClickEnabled = false;
        }
    }

    @Override
    public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
        return false;
    }

    @Override
    public boolean onScale(ScaleGestureDetector detector) {
        VisualizeSdkJni.zoom(detector.getScaleFactor(), (int)detector.getFocusX(), (int)detector.getFocusY());
        return true;
    }

}
