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
import android.graphics.PixelFormat;
import android.graphics.PointF;
import android.graphics.Rect;
import android.opengl.GLES10;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

import android.util.DisplayMetrics;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

import java.util.Queue;
import java.util.concurrent.LinkedBlockingQueue;

public class TeighaDwgView extends GLSurfaceView {

	private static String TAG = "DwgView";
	// Use this constant to control of OpenGL version which is used by native library:
	// GLESVER == 1 - for OpenGL 1.1 renderer
	// GLESVER == 2 - for GLES2 renderer
	private static int GLESVER = 2;
	private Context dwgViewCtx;
	private TeighaDwgActivity activity;



	// we can be in one of these 3 states
	public static final int NONE = 0;
	public static final int DRAG = 1;
	public static final int ZOOM = 2;
	public static final int ORBIT = 3;
	public static final int ZOOM_WINDOW = 4;

	public static final int PROJECTION_PARALLEL = 0;
	public static final int PROJECTION_PERSPECTIVE = 1;

	private int mTouchMode = NONE;
	private int mSelectedTouchMode = NONE;
	// remember some things for zooming
	private PointF mTouchStart = new PointF();
	private PointF mTouchEnd = new PointF();
	private PointF mTouchMid = new PointF();
	private float mTouchOldDist = 1f;
	private float mTouchOldRot = 0f;
	private float[] mTouchLastEvent = null;
	private long mTouchLastTime = -1;

    boolean translucent;
    int depth;
    int stencil;

	
	public Renderer mRenderer;
	
	public void onLoad() {
		mRenderer.onLoad(dwgViewCtx);
	}


    public TeighaDwgView(Context context) {
        super(context);
//        init(false, 24, 2);
        dwgViewCtx = context;
    }

    public TeighaDwgView(Context context, boolean translucent, int depth, int stencil) {
        super(context);
        this.translucent = translucent;
        this.depth = depth;
        this.stencil = stencil;
        dwgViewCtx = context;
    }

    public void init(boolean translucent, int depth, int stencil) {
        if (translucent) {
            this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        }

        setEGLContextFactory(new ContextFactory());

        setEGLConfigChooser( translucent ?
                             new ConfigChooser(8, 8, 8, 8, depth, stencil) :
                             new ConfigChooser(5, 6, 5, 0, depth, stencil) );
		Rect rectf = new Rect();
		this.getGlobalVisibleRect(rectf);
        mRenderer = new Renderer(this);
        setRenderer(mRenderer);
        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }


    @Override
    public void onPause() {
    	if(mRenderer.isContextCreated())
    	{
    		queueEvent(new Runnable() {
    	        @Override
    	        public void run() {
//    	        	if (GLESVER == 2)
    	        	//   TeighaDWGJni.saveContext(1);
    	        }
    	    });
    	}
    	super.onPause();
    }

	/**
	 * Determine the space between the first two fingers
	 */
	private float spacing(MotionEvent event) {
		float x = event.getX(0) - event.getX(1);
		float y = event.getY(0) - event.getY(1);
		return (float)Math.sqrt(x * x + y * y);
	}

	/**
	 * Calculate the mid point of the first two fingers
	 */
	private void midPoint(PointF point, MotionEvent event) {
		float x = event.getX(0) + event.getX(1);
		float y = event.getY(0) + event.getY(1);
		point.set(x / 2, y / 2);
	}

	/**
	 * Calculate the degree to be rotated by.
	 *
	 * @param event
	 * @return Degrees
	 */
	private float rotation(MotionEvent event) {
		double delta_x = (event.getX(0) - event.getX(1));
		double delta_y = (event.getY(0) - event.getY(1));
		double radians = Math.atan2(delta_y, delta_x);
		return (float)Math.toDegrees(radians);
	}

	@Override public boolean onTouchEvent (MotionEvent event) {
		switch (event.getAction() & MotionEvent.ACTION_MASK) {
			case MotionEvent.ACTION_DOWN:
				mTouchMode = mSelectedTouchMode;
				mTouchStart.set(event.getX(), event.getY());
				if(mTouchMode == ZOOM_WINDOW) {
					TeighaDWGJni.startSelectionFrame((int)event.getX(), (int)event.getY());
					this.requestRender();
				}
				mTouchLastEvent = null;
				break;
			case MotionEvent.ACTION_POINTER_DOWN:
				mTouchOldDist = spacing(event);
				if (mTouchOldDist > 10f) {
					midPoint(mTouchMid, event);
					mTouchMode = ZOOM;
				}
				mTouchLastEvent = new float[4];
				mTouchLastEvent[0] = event.getX(0);
				mTouchLastEvent[1] = event.getX(1);
				mTouchLastEvent[2] = event.getY(0);
				mTouchLastEvent[3] = event.getY(1);
				mTouchOldRot = rotation(event);
				break;
			case MotionEvent.ACTION_UP:
				float x = mTouchStart.x - mTouchEnd.x;
				float y = mTouchStart.y - mTouchEnd.y;
				if(mTouchMode == ZOOM_WINDOW && (float)Math.sqrt(x * x + y * y) > 10f) {
					double xMin, xMax, yMin, yMax;
					if(mTouchStart.x < mTouchEnd.x) {
						xMin = mTouchStart.x;
						xMax = mTouchEnd.x;
					} else {
						xMax = mTouchStart.x;
						xMin = mTouchEnd.x;
					}

					if(mTouchStart.y < mTouchEnd.y) {
						yMin = mTouchStart.y;
						yMax = mTouchEnd.y;
					} else {
						yMax = mTouchStart.y;
						yMin = mTouchEnd.y;
					}
					TeighaDWGJni.zoomWindow(xMin, yMin, xMax, yMax);
					this.requestRender();
				}
			case MotionEvent.ACTION_POINTER_UP:
				mTouchMode = NONE;
				mTouchLastEvent = null;
				break;
			case MotionEvent.ACTION_MOVE:
				if (mTouchLastEvent != null && event.getPointerCount() == 3) {
					float newRot = rotation(event);
					float r = newRot - mTouchOldRot;
					TeighaDWGJni.viewRotate((float)Math.toRadians(r));
					this.requestRender();
					mTouchOldRot = newRot;
				} else if (mTouchMode == DRAG) {
					float dx = event.getX() - mTouchStart.x;
					float dy = event.getY() - mTouchStart.y;
					TeighaDWGJni.viewTranslate(dx, dy);
					this.requestRender();
					mTouchStart.x += dx; mTouchStart.y += dy;
				} else if (mTouchMode == ORBIT) {
					float dx = event.getX() - mTouchStart.x;
					float dy = event.getY() - mTouchStart.y;
					final DisplayMetrics displayMetrics = new DisplayMetrics();
					this.getDisplay().getMetrics(displayMetrics);
					float density = displayMetrics.density;
					TeighaDWGJni.viewOrbit(-(float)Math.toRadians(dy / density / 2), -(float)Math.toRadians(dx / density / 2));
					this.requestRender();
					mTouchStart.x += dx; mTouchStart.y += dy;
				} else if (mTouchMode == ZOOM_WINDOW) {
					mTouchEnd.set(event.getX(), event.getY());
					TeighaDWGJni.resizeSelectionFrame((int)event.getX(), (int)event.getY());
					this.requestRender();
				} else if (mTouchMode == ZOOM) {
					float newDist = spacing(event);
					if (newDist > 10f) {
						float scale = (newDist / mTouchOldDist);
						TeighaDWGJni.viewScale(scale);
						this.requestRender();
						mTouchOldDist = newDist;
					}
				}
				break;
		}
		return true;
	}

	private static class ConfigChooser implements GLSurfaceView.EGLConfigChooser {

        public ConfigChooser(int r, int g, int b, int a, int depth, int stencil) {
            mRedSize = r;
            mGreenSize = g;
            mBlueSize = b;
            mAlphaSize = a;
            mDepthSize = depth;
            mStencilSize = stencil;
        }

        private static int EGL_OPENGL_ES2_BIT = 4;
        private static int[] s_configAttribs1 =
        {
            EGL10.EGL_RED_SIZE, 4,
            EGL10.EGL_GREEN_SIZE, 4,
            EGL10.EGL_BLUE_SIZE, 4,
            // EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL10.EGL_NONE
        };
        private static int[] s_configAttribs2 =
        {
            EGL10.EGL_RED_SIZE, 4,
            EGL10.EGL_GREEN_SIZE, 4,
            EGL10.EGL_BLUE_SIZE, 4,
            EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL10.EGL_NONE

        };

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display) {

            int[] num_config = new int[1];
            if (GLESVER != 2)
            	egl.eglChooseConfig(display, s_configAttribs1, null, 0, num_config);
            else
            	egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

            int numConfigs = num_config[0];

            if (numConfigs <= 0) {
                throw new IllegalArgumentException("No configs match configSpec");
            }

            EGLConfig[] configs = new EGLConfig[numConfigs];
            if (GLESVER != 2)
            	egl.eglChooseConfig(display, s_configAttribs1, configs, numConfigs, num_config);
            else
            	egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

            return chooseConfig(egl, display, configs);
        }

        public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display,
                EGLConfig[] configs) {
        	int checkStencil = 2;
        	while ((checkStencil--) != 0) {
        		for(EGLConfig config : configs) {
        			int d = findConfigAttrib(egl, display, config,
        					EGL10.EGL_DEPTH_SIZE, 0);
        			int s = findConfigAttrib(egl, display, config,
        					EGL10.EGL_STENCIL_SIZE, 0);
        			if (d < mDepthSize || ((checkStencil != 0) && (s < mStencilSize)))
        				continue;
        			int r = findConfigAttrib(egl, display, config,
        					EGL10.EGL_RED_SIZE, 0);
        			int g = findConfigAttrib(egl, display, config,
        					EGL10.EGL_GREEN_SIZE, 0);
        			int b = findConfigAttrib(egl, display, config,
                            EGL10.EGL_BLUE_SIZE, 0);
        			int a = findConfigAttrib(egl, display, config,
                        EGL10.EGL_ALPHA_SIZE, 0);

        			if (r == mRedSize && g == mGreenSize && b == mBlueSize && a == mAlphaSize)
        				return config;
        		}
        	}
            return null;
        }

        private int findConfigAttrib(EGL10 egl, EGLDisplay display,
                EGLConfig config, int attribute, int defaultValue) {

            if (egl.eglGetConfigAttrib(display, config, attribute, mValue)) {
                return mValue[0];
            }
            return defaultValue;
        } 
        protected int mRedSize;
        protected int mGreenSize;
        protected int mBlueSize;
        protected int mAlphaSize;
        protected int mDepthSize;
        protected int mStencilSize;
        private int[] mValue = new int[1];
    }
    
    private static class ContextFactory implements GLSurfaceView.EGLContextFactory {
        private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
        	if (GLESVER != 2)
        		Log.w(TAG, "creating OpenGL ES 1.1 context");
        	else
        		Log.w(TAG, "creating OpenGL ES 2.0 context");
            checkEglError("Before eglCreateContext", egl);
            int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, GLESVER, EGL10.EGL_NONE };
            EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
            checkEglError("After eglCreateContext", egl);
            return context;
        }

        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
            egl.eglDestroyContext(display, context);
        }
    }
    
    private static void checkEglError(String prompt, EGL10 egl) {
        int error;
        while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS) {
            Log.e(TAG, String.format("%s: EGL error: 0x%x", prompt, error));
        }
    }
    
    private static class Renderer implements GLSurfaceView.Renderer {
		private int xMin;
		private int xMax;
		private int yMin;
		private int yMax;
		private int mWidth = 0;
    	private int mHeight = 0;
    	private boolean mLoaded = false;
    	private boolean mContextCreated = false;
    	private Context dwgViewCtx;
    	private View parentView;

    	public Renderer(View parentView) {
    		super();
    		this.parentView = parentView;
    		this.xMin = xMin;
			this.xMax = xMax;
			this.yMin = yMin;
			this.yMax = yMax;
		}
    	
    	public void onDrawFrame(GL10 gl) {
    		if ( mContextCreated == true )
    		{
    			long beginTime = System.currentTimeMillis();
    			if (!TeighaDWGJni.renderFrame())
    			{ // draw 'red' background for error
    				if (GLESVER != 2)
    				{
    					GLES10.glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    					GLES10.glClear(GLES10.GL_COLOR_BUFFER_BIT);
    				}
    				else
    				{
    					GLES20.glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    					GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
    				}
    			}
    		}
    		else
    		{
    			if (mLoaded == true && mWidth != 0 && mHeight != 0)
    			{
    				mContextCreated = true;
                    Rect rectf = new Rect();
                    parentView.getGlobalVisibleRect(rectf);
    				TeighaDWGJni.createRenderer(rectf.left, rectf.right, -30, rectf.bottom, dwgViewCtx);
        			{ // draw 'yellow' background while creation
        				if (GLESVER != 2)
        				{
        					GLES10.glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
        					GLES10.glClear(GLES10.GL_COLOR_BUFFER_BIT);
        				}
        				else
        				{
        					GLES20.glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
        					GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        				}
        			}
					TeighaDWGJni.renderFrame();
    			}
    			else
    			{ // draw 'green' background while loading
    				if (GLESVER != 2)
    				{
    					GLES10.glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    					GLES10.glClear(GLES10.GL_COLOR_BUFFER_BIT);
    				}
    				else
    				{
    					GLES20.glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
    					GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
    				}
    			}
    		}
        }

        public void onSurfaceChanged(GL10 gl, int width, int height) {
           mWidth = width;
           mHeight = height;
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        { // check extensions
        	if (GLESVER != 2)
        	{
         	   String checkStr = gl.glGetString(GLES10.GL_EXTENSIONS);
         	   Log.i("GL10", checkStr);
            }
        	else
        	{
          	   String checkStr = GLES20.glGetString(GLES20.GL_EXTENSIONS);
          	   Log.i("GL20", checkStr);
            }
        }
        }
        public void onLoad(Context ctx) {
        	mLoaded = true;
        	dwgViewCtx = ctx;
        }
        public boolean isContextCreated() {
        	return mContextCreated;
        }

        public void onDestroyContext() {
          if (mContextCreated == true)
          {
        	  mContextCreated = false;
        	//   TeighaDWGJni.destroyRenderer();
          }
        }
    }

    public void onDestroy() {
    	mRenderer.onDestroyContext();
    }

    public void setTouchMode(String touchMode) {
		switch (touchMode) {
			case "pan":
				this.mSelectedTouchMode = TeighaDwgView.DRAG;
				break;
			case "orbit":
				this.mSelectedTouchMode = TeighaDwgView.ORBIT;
				break;
			case "zoom_window":
				this.mSelectedTouchMode = TeighaDwgView.ZOOM_WINDOW;
		}
//		mTouchMode = mSelectedTouchMode;
	}

	public void setVisualStyle(String visualStyleName) {
		TeighaDWGJni.setRenderMode(visualStyleName);
		this.requestRender();
	}

	public void setViewPosition(int viewPosition) {
		TeighaDWGJni.setViewPosition(viewPosition);
		this.requestRender();
	}

    public void zoomExtents() {
	    TeighaDWGJni.zoomExtents();
		this.requestRender();
    }

    public void zoomWindow() {
    }

	public void regen(String regenMode) {
		switch (regenMode) {
			case "regen_all":
				TeighaDWGJni.regenAll();
				break;
			case "regen_visible":
				TeighaDWGJni.regenVisible();
				break;
			case "regen_active_view":
				TeighaDWGJni.regenActiveView();
				break;
		}
		this.requestRender();
	}

	public void setProjection(int projection) {
		TeighaDWGJni.setProjectionForActiveView(projection);
		this.requestRender();
	}


}

