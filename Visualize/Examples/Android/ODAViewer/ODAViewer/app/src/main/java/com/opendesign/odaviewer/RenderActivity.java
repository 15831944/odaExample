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

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.view.GestureDetectorCompat;

import android.annotation.SuppressLint;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Looper;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.ScaleGestureDetector;
import android.view.View;
import android.view.WindowManager;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import com.opendesign.odaviewer.ImportParams.DwgImportParams;

import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Objects;

import java.nio.file.Paths;

public class RenderActivity extends AppCompatActivity implements CustomDialogFragment.DialogListener {

    // sub menus
    private View _viewsMenu;
    private View _navigationMenu;
    private View _markupsMenu;
    private View _toolsMenu;
    private View _stylesMenu;
    private View _activeMenu;
    private View _groundShadowBtn;

    private EditText _hiddenTextEdit;

    private GLSurfaceView _glView;
    private OpenGLRenderer _renderer;

    private View _loadingIndicator;

    public String FilePath;

    private TouchListener _touchListener;
    private GestureDetectorCompat _gestureDetector;
    private ScaleGestureDetector _scaleDetector;

    private CircularProgressBar _lowMemoryProgressBar = null;

    private long _startOpenTime = 0;

    enum Markups {
        Rectangle,
        Circle,
        Handle,
        Cloud,
        Text,
        Save,
        Load
    }

    enum ToolsActions {
        ShowCuttingPlanes,
        AddCuttingPlaneByX,
        AddCuttingPlaneByY,
        AddCuttingPlaneByZ,
        FillCuttingPlane,
        RemoveCuttingPlane,
        Collide,
        GroundShadow
    }

    enum DraggerResult {
        NothingToDo(0), NeedUpdateView(2), NeedFinishDragger(4);

        private final int id;

        DraggerResult(int i) {
            id = i;
        }

        public int getValue() { return id; }
    }

    private ArrayList<String> mMarkupsList = new ArrayList<>();

    private View _activeBtnView = null;

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTheme(R.style.AppTheme);
        super.onCreate(savedInstanceState);

        getWindow().setFlags(WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE, WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE);

        // hide bar with application title
        Objects.requireNonNull(getSupportActionBar()).hide();

        setContentView(R.layout.activity_render);

        _viewsMenu = findViewById(R.id.views_menu);
        _navigationMenu = findViewById(R.id.navigation_menu);
        _markupsMenu = findViewById(R.id.markups_menu);
        _toolsMenu = findViewById(R.id.tools_menu);
        _stylesMenu = findViewById(R.id.style_menu);
        _loadingIndicator = findViewById(R.id.loadingIndicator);
        _loadingIndicator.setVisibility(View.VISIBLE);
        _groundShadowBtn = findViewById(R.id.tools_groundShadows);
        initialize();

        _touchListener = new TouchListener(this);
        _gestureDetector = new GestureDetectorCompat(this, _touchListener);
        _scaleDetector = new ScaleGestureDetector(this, _touchListener);

        ImageView pdfBtn = findViewById(R.id.pdfButton);
        if(pdfBtn != null)
            pdfBtn.setVisibility(VisualizeSdkJni.isPdfExportEnabled() ? View.VISIBLE : View.INVISIBLE);

        Bundle args = getIntent().getExtras();

        _glView =  findViewById(R.id.glSurface);
        if(_glView == null) {
            Toast toast = Toast.makeText(this, "GL Surface is null.",Toast.LENGTH_LONG);
            toast.show();
        }
        else {
            FilePath = Objects.requireNonNull(args.get("filePath")).toString();

            // setup bar for low memory import
            _lowMemoryProgressBar = (CircularProgressBar)findViewById(R.id.lowMemory_progressBar);
            _lowMemoryProgressBar.setProgressColor(getColor(R.color.colorPrimary));
            _lowMemoryProgressBar.setProgressWidth(20);
            _lowMemoryProgressBar.setTextColor(getColor(R.color.colorPrimary));

            // setup gl view
            _glView.setEGLContextClientVersion(2);
            _renderer = new OpenGLRenderer();
            _renderer.renderActivity = this;
            _glView.setRenderer(_renderer);
            _glView.setVisibility(View.INVISIBLE);

            TextView fileNameLabel = (TextView) findViewById(R.id.filename_label);
            Path pathFile = Paths.get(FilePath);
            fileNameLabel.setText(pathFile.getFileName().toString());

            // open file
            _startOpenTime = System.currentTimeMillis();
            new Thread(new Runnable() {
                public void run() {

                    String res = "";
                    if(MainActivity.getFileExtension(FilePath).toUpperCase().equals("DWG")) {
                        DwgImportParams dwgParams = new DwgImportParams();
                        VisualizeSdkJni.getDwgImportParams(dwgParams);
                        if(dwgParams.LowMemoryImport) {
                            res = VisualizeSdkJni.lowMemoryOpenFile(FilePath, RenderActivity.this);
                        }
                        else
                            res = VisualizeSdkJni.openFile(FilePath);
                    }
                    else
                        res = VisualizeSdkJni.openFile(FilePath);

                    if(!res.isEmpty()) {
                        Looper.prepare();
                        (Toast.makeText(MainActivity.App, res, Toast.LENGTH_LONG)).show();
                    }
                    else {
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                String res = VisualizeSdkJni.setupDevice(_glView.getContext(), _glView.getWidth(), _glView.getHeight());
                                if(!res.isEmpty())
                                    (Toast.makeText(MainActivity.App, res, Toast.LENGTH_LONG)).show();
                                else {
                                    enableRender(true);
                                    getWindow().clearFlags(WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE);
                                }
                            }
                        });
                    }
                }
            }).start();


            _glView.setOnTouchListener(new View.OnTouchListener() {
                @Override
                public boolean onTouch(View v, MotionEvent event) {
                    if(event.getAction() == MotionEvent.ACTION_UP) {
                        _touchListener.onTouchUp(event);
                    } else {
                        _scaleDetector.onTouchEvent(event);
                        _gestureDetector.onTouchEvent(event);
                    }
                    return true;
                }
            });


        }

        _hiddenTextEdit = findViewById(R.id.hiddenTextEdit);
        _hiddenTextEdit.setOnKeyListener(new View.OnKeyListener() {
            @Override
            public boolean onKey(View v, int keyCode, KeyEvent event) {
                //This is the filter
                if (event.getAction() != KeyEvent.ACTION_DOWN)
                    return true;

                if(keyCode == KeyEvent.KEYCODE_DEL) {
                    VisualizeSdkJni.onProcessBackspace();
                } else if (keyCode == KeyEvent.KEYCODE_ENTER) {
                    VisualizeSdkJni.onProcessEnter();
                }
                return true;
            }
        });
        _hiddenTextEdit.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {
            }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {
                if(!charSequence.toString().isEmpty()) {
                    VisualizeSdkJni.onProcessText(_hiddenTextEdit.getText().toString());
                    _hiddenTextEdit.setText("");
                }
            }

            @Override
            public void afterTextChanged(Editable editable) {
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    @Override
    protected void onPause() {
        super.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    private void enableRender(boolean bEnable) {
        _loadingIndicator.setVisibility(bEnable ? View.GONE : View.VISIBLE);
        _glView.setVisibility(bEnable ? View.VISIBLE : View.INVISIBLE);

        // set projection button
        ImageView projBtn = findViewById(R.id.projection_button);
        if(VisualizeSdkJni.isPerspective())
            projBtn.setImageDrawable(getDrawable(R.drawable.projection_perspective));
        else
            projBtn.setImageDrawable(getDrawable(R.drawable.projection_isometric));

        // set render mode btn
        int ind = VisualizeSdkJni.getRenderMode();
        if(ind == 0)
            setBackgroundBtnColor(R.id.wire2d, false);
        else if(ind == 1)
            setBackgroundBtnColor(R.id.wire3d, false);
        else if(ind == 2)
            setBackgroundBtnColor(R.id.hiddenLine, false);
        else if(ind == 3)
            setBackgroundBtnColor(R.id.shaded, false);
        else if(ind == 4)
            setBackgroundBtnColor(R.id.gouShaded, false);
        else if(ind == 5)
            setBackgroundBtnColor(R.id.shadeWithEdges, false);
        else if(ind == 6)
            setBackgroundBtnColor(R.id.gouShadedWithEdges, false);
    }

    public void startProgressMeter() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                _lowMemoryProgressBar.setVisibility(View.VISIBLE);
                _loadingIndicator.setVisibility(View.INVISIBLE);
            }
        });
    }

    public void stopProgressMeter() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                _lowMemoryProgressBar.setVisibility(View.INVISIBLE);
                _loadingIndicator.setVisibility(View.VISIBLE);
            }
        });
    }

    public void setProgressMeterValue(int value) {
        final int val = value;
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                _lowMemoryProgressBar.setProgress(val);
            }
        });
    }

    public void setupTotalTime() {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                // update open time label
                TextView openFileTimeLabel = findViewById(R.id.fileOpenTime_label);
                if(openFileTimeLabel != null)
                {
                    double time = (System.currentTimeMillis() - _startOpenTime) / 1000d;
                    openFileTimeLabel.setText( String.format("%.2f s", time) );
                    groundShadowCheck();
                }
            }
        });
    }

    private void initialize() {
        // activate navigation panel
        _navigationMenu.setVisibility(View.VISIBLE);
        _activeMenu = findViewById(R.id.navigationMenu);
        ((ImageView)_activeMenu).setColorFilter(getColor(R.color.activeMenuButton));
        View panBnt = findViewById(R.id.navigation_pan);
        panBnt.setBackgroundColor(getColor(R.color.activeButtonColor));
    }

    public void onMenuClick(View view) {
        String tag = view.getTag().toString();
        // clear selection
        if(_activeMenu != view)
            disableMenus();
        _activeMenu = view;
        // set active color
        ((ImageView)view).setColorFilter(getColor(R.color.activeMenuButton));

        TextView title = findViewById(R.id.titleTextView);

        if(tag.equals(getString(R.string.menu_files))) { // menu click
            enableRender(false);
            VisualizeSdkJni.release();
            Intent intent = new Intent(this, MainActivity.class);
            intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP | Intent.FLAG_ACTIVITY_SINGLE_TOP);
            startActivity(intent);
        }
        else if(tag.equals(getString(R.string.menu_views))) { // views click
            _viewsMenu.setVisibility(_viewsMenu.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);
            title.setText(R.string.menu_views);
        }
        else if(tag.equals(getString(R.string.menu_navigation))) { // navigation click
            _navigationMenu.setVisibility(_navigationMenu.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);
            title.setText(R.string.menu_navigation);
        }
        else if(tag.equals(getString(R.string.menu_markups))) { // navigation click
            _markupsMenu.setVisibility(_markupsMenu.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);
            title.setText(R.string.menu_markups);
        }
        else if(tag.equals(getString(R.string.menu_tools))) { // tools click
            _toolsMenu.setVisibility(_toolsMenu.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);
            title.setText(R.string.menu_tools);
            VisualizeSdkJni.onAppearSectioningPanel(true);
        }
        else if(tag.equals(getString(R.string.menu_styles))) { // styles click
            _stylesMenu.setVisibility(_stylesMenu.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);
            title.setText(R.string.menu_styles);
        }
    }

    private void disableMenus() {
        VisualizeSdkJni.onAppearSectioningPanel(false);
        if(_viewsMenu != null)
            _viewsMenu.setVisibility(View.GONE);
        if(_navigationMenu != null)
            _navigationMenu.setVisibility(View.GONE);
        if(_markupsMenu != null)
            _markupsMenu.setVisibility(View.GONE);
        if(_toolsMenu != null)
            _toolsMenu.setVisibility(View.GONE);
        if(_stylesMenu != null)
            _stylesMenu.setVisibility(View.GONE);

        resetImageViewTint((ImageView)findViewById(R.id.viewsMenu));
        resetImageViewTint((ImageView)findViewById(R.id.navigationMenu));
        resetImageViewTint((ImageView)findViewById(R.id.markupsMenu));
        resetImageViewTint((ImageView)findViewById(R.id.toolsMenu));
        resetImageViewTint((ImageView)findViewById(R.id.stylesMenu));
    }

    private void resetImageViewTint(ImageView view) {
        view.setColorFilter(getColor(R.color.itemListDefault));
    }

    public void onOptionsMenuClick(View view) {
        CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.RenderActivityOptions);
        dlg.show(getSupportFragmentManager(), "custom");
    }

    public void onSaveButtonClick(View view) {
        CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.Save);
        dlg.show(getSupportFragmentManager(), "custom");
    }

    public void onPdfExportClick(View view)
    {
        if(VisualizeSdkJni.isPdfExportEnabled())
        {
            if(VisualizeSdkJni.exportToPdf(false))
                (Toast.makeText(this, "Export to PDF successful!", Toast.LENGTH_LONG)).show();
            else
                (Toast.makeText(this, "Export to PDF failed!", Toast.LENGTH_LONG)).show();
        }
    }

    public void processDraggerResult(int code) {
        if((code & DraggerResult.NeedFinishDragger.getValue()) > 0) {
            if(_activeBtnView != null) {
                setBackgroundBtnColor(_activeBtnView, true);
                _activeBtnView = null;
            }
        }
    }

    private void setBackgroundBtnColor(int viewId, boolean bReset) {
        setBackgroundBtnColor(findViewById(viewId), bReset);
    }

    private void setBackgroundBtnColor(View view, boolean bReset) {
        if(view == null)
            return;
        if(bReset)
            view.setBackgroundColor(getColor(R.color.simpleButtonColor));
        else
            view.setBackgroundColor(getColor(R.color.activeButtonColor));
    }

    private void setDisabledBtnColor(View view) {
        if(view == null)
            return;
        view.setBackgroundColor(getColor(R.color.disabledTextColor));
    }

    public void onNavigationClick(View view) {
        try {
            int navInd = Integer.parseInt(view.getTag().toString());
            VisualizeSdkJni.runNavigationAction(navInd);
            // set color
            if(navInd < 2) {
                // reset prev colors
                setBackgroundBtnColor(R.id.navigation_pan, true);
                setBackgroundBtnColor(R.id.navigation_orbit, true);
                view.setBackgroundColor(getColor(R.color.activeButtonColor));
            } else if(navInd == 2) {
                _activeBtnView = view;
                setBackgroundBtnColor(view, false);
            }
        }
        catch (Exception e) {
            (Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG)).show();
        }
    }

    public void onViewsClick(View view) {
        try {
            int viewInd = Integer.parseInt(view.getTag().toString());
            VisualizeSdkJni.set3DView(viewInd);
        }
        catch (Exception e) {
            (Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG)).show();
        }
    }

    public void onRegenVisible(View view) {
        VisualizeSdkJni.regenVisible();
    }

    public void onProjectionChange(View view) {
        ImageView projBtn = findViewById(R.id.projection_button);
        if(VisualizeSdkJni.isPerspective()) {
            VisualizeSdkJni.setProjection(0);
            projBtn.setImageDrawable(getDrawable(R.drawable.projection_isometric));
        }
        else {
            VisualizeSdkJni.setProjection(1);
            projBtn.setImageDrawable(getDrawable(R.drawable.projection_perspective));
        }
    }

    private void groundShadowCheck() {
        boolean bAllow = VisualizeSdkJni.isViewAllowGroundShadow();
        _groundShadowBtn.setEnabled(bAllow);
        _groundShadowBtn.setAlpha( bAllow ? 1.f : .5f );
        if(!bAllow)
            setBackgroundBtnColor(_groundShadowBtn, true);
    }

    public void onRenderModeChange(View view) {
        try {
            int ind = Integer.parseInt(view.getTag().toString());
            VisualizeSdkJni.runRenderMode(ind);
            groundShadowCheck();
            // reset prev colors
            setBackgroundBtnColor(R.id.wire2d, true);
            setBackgroundBtnColor(R.id.wire3d, true);
            setBackgroundBtnColor(R.id.hiddenLine, true);
            setBackgroundBtnColor(R.id.shaded, true);
            setBackgroundBtnColor(R.id.gouShaded, true);
            setBackgroundBtnColor(R.id.shadeWithEdges, true);
            setBackgroundBtnColor(R.id.gouShadedWithEdges, true);
            view.setBackgroundColor(getColor(R.color.activeButtonColor));
        }
        catch (Exception e) {
            (Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG)).show();
        }
    }

    public void onMarkupsClick(View view) {
        try {
            int ind = Integer.parseInt(view.getTag().toString());
            VisualizeSdkJni.runMarkupAction(ind);
            Markups markup = (Markups.values()[ind]);
            switch (markup) {
                case Rectangle:
                case Circle:
                case Handle:
                    _activeBtnView = view;
                    setBackgroundBtnColor(view, false);
                    break;
                case Cloud:
                    _touchListener.IsLongClickEnabled = true;
                    _activeBtnView = view;
                    setBackgroundBtnColor(view, false);
                    break;
                case Text:
                    _touchListener.IsRequestKeyboard = true;
                    _activeBtnView = view;
                    setBackgroundBtnColor(view, false);
                    break;
                case Save:
                    showSaveMarkupDlg();
                    break;
                case Load:
                    showLoadMarkupDlg();
                    break;
            }

        }
        catch (Exception e) {
            (Toast.makeText(this, e.getMessage(), Toast.LENGTH_LONG)).show();
        }
    }

    private void showSaveMarkupDlg() {
        String res = VisualizeSdkJni.isSaveMarkupAvaliable();
        if(!res.isEmpty()) {
            (Toast.makeText(this, res, Toast.LENGTH_LONG)).show();
            return;
        }
        CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.MarkupSave);
        dlg.show(getSupportFragmentManager(), "custom");
    }

    private void showLoadMarkupDlg() {
        String res = VisualizeSdkJni.isLoadMarkupAvaliable();
        if(!res.isEmpty()) {
            (Toast.makeText(this, res, Toast.LENGTH_LONG)).show();
            return;
        }
        CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.MarkupLoad);
        dlg.show(getSupportFragmentManager(), "custom");
    }


    @Override
    public void saveMarkup(String markupName) {
        String res = VisualizeSdkJni.saveMarkup(markupName);
        if(res.isEmpty()) {
            mMarkupsList.add(markupName);
            res = "Markup saved";
        }
        (Toast.makeText(MainActivity.App, res, Toast.LENGTH_LONG)).show();
    }

    @Override
    public void loadMarkup(String markupName) {
        String res = VisualizeSdkJni.loadMarkup(markupName);
        if(res.isEmpty()) {
            res = "Markup loaded";
        }
        (Toast.makeText(MainActivity.App, res, Toast.LENGTH_LONG)).show();
    }

    @Override
    public void setupList(ListView listView) {
        // setup list
        String[] arr = mMarkupsList.toArray(new String[mMarkupsList.size()]);
        ArrayAdapter<String> adapter = new ArrayAdapter<>(this, android.R.layout.simple_list_item_single_choice, arr);
        listView.setAdapter(adapter);
    }

    @Override
    public void onImportDialogAccepted() {

    }

    public void onToolsClick(View view) {
        try {
            int ind = Integer.parseInt(view.getTag().toString());
            ToolsActions act = (ToolsActions.values()[ind]);
            switch (act) {
                case ShowCuttingPlanes:
                    VisualizeSdkJni.onShowCuttingPlanes();
                    ImageView onShow = findViewById(R.id.tools_showCuttingPlanes);
                    onShow.setImageDrawable( getDrawable(VisualizeSdkJni.isCuttingPlanesVisible() ? R.drawable.cutting_plane : R.drawable.cuttingplane_off) );
                    break;
                case AddCuttingPlaneByX:
                    VisualizeSdkJni.onAddCuttingPlanes(1, 0, 0);
                    break;
                case AddCuttingPlaneByY:
                    VisualizeSdkJni.onAddCuttingPlanes(0, 1, 0);
                    break;
                case AddCuttingPlaneByZ:
                    VisualizeSdkJni.onAddCuttingPlanes(0, 0, 1);
                    break;
                case FillCuttingPlane:
                    VisualizeSdkJni.onFillCuttingPlanes();
                    ImageView onFill = findViewById(R.id.tools_fillCuttingPlanes);
                    onFill.setImageDrawable( getDrawable(VisualizeSdkJni.isCuttingPlanesFilled() ? R.drawable.fill_cutting_plane : R.drawable.fill_cutting_plane_off) );
                    break;
                case RemoveCuttingPlane:
                    VisualizeSdkJni.onRemoveCuttingPlanes();
                    break;
                case Collide:
                    if(_activeBtnView != view) {
                        String res = VisualizeSdkJni.runCollide();
                        if (!res.isEmpty())
                            (Toast.makeText(MainActivity.App, res, Toast.LENGTH_LONG)).show();
                        else {
                            if (_activeBtnView != view) {
                                _activeBtnView = view;
                                setBackgroundBtnColor(view, false);
                            }
                        }
                    } else {
                        processDraggerResult(DraggerResult.NeedFinishDragger.getValue());
                        VisualizeSdkJni.finishDragger();
                    }
                    break;
                case GroundShadow:
                    boolean bShadowAdded = VisualizeSdkJni.addGroundShadow();
                    setBackgroundBtnColor(view, !bShadowAdded);
                    break;
            }
        } catch (Exception ignored) {

        }
    }

}
