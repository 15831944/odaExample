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

import java.io.File;
import java.io.FileFilter;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Application;
import android.app.LauncherActivity;
import android.app.ListActivity;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.preference.PreferenceManager;
import android.support.annotation.NonNull;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Filter;
import android.widget.Filterable;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class Main extends ListActivity {

    private TeighaDwgView GLView;
    private String currentFile;

    private class DWGFile {
        private String mPath;
        private String mFile;
        private ProgressDialog mPd;
        private long mSize;


        private class DWGFileOpen implements View.OnClickListener {

            private String mPath;


            public DWGFileOpen(String path) {
                mPath = path;
            }

            private Handler mPdHandler = new Handler() {
                @Override
                public void handleMessage(Message msg) {
//					mPd.dismiss();
                    GLView.onLoad();
                    GLView.requestRender();
                }
            };

            // @Override
            public void onClick(View v) {
//				Intent myIntent = new Intent(getApplicationContext(), TeighaDwgActivity.class);
//				myIntent.putExtra("file", mPath);
//	            startActivityForResult(myIntent, 0);

                GLView = new TeighaDwgView(getApplication());

//	            setContentView(GLView);
                setGLView();
                GLView.init(false, 24, 2);
                GLView.setTouchMode("pan");
//                currentSubMenuItemId = R.id.navigation_pan;

                TeighaDWGJni.init();

                mFile = mPath;
                currentFile = mFile;
//				mPd = ProgressDialog.show(getApplicationContext(), "Please wait", "Loading " + mFile + " file...", true, false);
                new Thread(new Runnable() {
                    public void run() {
                        TeighaDWGJni.open(mFile);
                        mPdHandler.sendEmptyMessage(0);
                    }
                }).start();
            }

        }

        public DWGFile(String path,
                       String file,
                       long size) {
            mPath = path;
            mFile = file;
            mSize = size;
        }

        public View getView(int position, View convertView, ViewGroup parent) {
            LayoutInflater inflater = (LayoutInflater) mApp.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            View view;
            view = inflater.inflate(R.layout.listrow, parent, false);

            TextView filename_txt = (TextView) view.findViewById(R.id.filename);
            filename_txt.setText(mFile);

            TextView size_txt = (TextView) view.findViewById(R.id.size);
            long size = mSize;
            String metric;
            if (size > (1024 * 1024 * 1024)) {
                metric = "Gb";
                size = size / (1024 * 1024 * 1024);
            } else if (size > (1024 * 1024)) {
                metric = "Mb";
                size = size / (1024 * 1024);
            } else {
                metric = "kb";
                size = size / 1024;
            }
            size_txt.setText(size + metric);

            view.setOnClickListener(new DWGFileOpen(mPath));
            return view;
        }

        @Override
        public String toString() {
            return mFile;
        }
    }

    public class DWGFileAdapter extends ArrayAdapter<DWGFile> implements Filterable {

        ProgressDialog mPd;
        boolean mReadRecurcevly;
        ArrayList<String> mExtEntries;

        private Handler mPdHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                mPd.dismiss();
                notifyDataSetChanged();
            }
        };
        private Handler mDataHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                DWGFile new_file = (DWGFile) msg.obj;
                add(new_file);
            }
        };

        public DWGFileAdapter(Context context) {
            super(context, R.layout.listrow);
            mReadRecurcevly = false;
            mExtEntries = new ArrayList<String>();
        }

        public void setReadRecursive(boolean rec) {
            mReadRecurcevly = rec;
        }

        public void setEnabledExtensions(ArrayList<String> arr) {
            mExtEntries = arr;
        }

        private void _readDir(File dir) {
            File[] files = dir.listFiles(new FileFilter() {

                // @Override
                public boolean accept(File pathname) {
                    boolean bShowFile = false;
                    for (String it : mExtEntries) {
                        bShowFile |= pathname.getName().toLowerCase().endsWith(it);
                    }
                    if (bShowFile ||
                            (pathname.isDirectory() == true && mReadRecurcevly)) {
                        return true;
                    }
                    return false;
                }
            });
            if (files != null) {
                for (int index = 0; index < files.length; index++) {
                    if (files[index].isDirectory() == true) {
                        _readDir(files[index]);
                    } else {
                        mDataHandler.sendMessage(mDataHandler.obtainMessage(0, new DWGFile(files[index].getAbsolutePath(), files[index].getName(), files[index].length())));
                    }
                }
            }
        }

        private void _rebuildSync() {
            File sdcard = Environment.getExternalStorageDirectory();
            if (sdcard.isDirectory()) {
                _readDir(sdcard);
            }
        }

        public void rebuild(Context ctx) {
            this.clear();
            mPd = ProgressDialog.show(ctx, "Please wait", "Finding files...", true, false);
            new Thread(new Runnable() {
                public void run() {
                    _rebuildSync();
                    mPdHandler.sendEmptyMessage(0);
                }
            }).start();
        }


        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            try {
                DWGFile item = (DWGFile) getItem(position);
                return item.getView(position, convertView, parent);
            } catch (Exception e) {
                return null;
            }
        }
    }

    private void copyFile(String filename) {
        final String rawExternalStorage = getFilesDir().getAbsolutePath();
        File file = new File(rawExternalStorage + "/" + filename);
        if (file.exists())
            return;
        AssetManager assetManager = this.getAssets();
        InputStream in = null;
        OutputStream out = null;
        try {
            in = assetManager.open(filename);
            out = new FileOutputStream(file);

            byte[] buffer = new byte[1024];
            int read;
            while ((read = in.read(buffer)) != -1) {
                out.write(buffer, 0, read);
            }
            in.close();
            in = null;
            out.flush();
            out.close();
            out = null;
        } catch (Exception e) {
            Log.e("MainActivity", e.getMessage());
        }
    }

    private ArrayAdapter mListAdapter;
    private Application mApp;
    private RelativeLayout mainView = null;
    private ListView list;
    private int currentMenuItemId = 0;
    private int currentSubMenuItemId = 0;
    private int currentViewType;
    private LinearLayout bottomMenu;
    private boolean listViewLoaded = true;
    private RelativeLayout subMenuView;
    private LinearLayout topRightMenu;
    private View searchBar;
    private TextView titleView;
    private EditText searchField;
    private LinearLayout topLeftMenu;


    @SuppressLint("ClickableViewAccessibility")
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.new_main);

        bottomMenu = (LinearLayout) findViewById(R.id.bottomPanel);
        subMenuView = (RelativeLayout) findViewById(R.id.submenu_view);
        titleView = (TextView) findViewById(R.id.title_view);
        topRightMenu = (LinearLayout) findViewById(R.id.top_right_menu);
        searchBar = findViewById(R.id.search_bar);
        searchField = (EditText) findViewById(R.id.search_src_text);

        topLeftMenu = (LinearLayout) findViewById(R.id.top_left_menu);

        mApp = (Application) getApplicationContext();

        searchField.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                if(s.length() > 0) {
                    list.setTextFilterEnabled(true);
                    list.setFilterText(searchField.getText().toString());
                } else {
                    list.clearTextFilter();
                }
            }

            @Override
            public void afterTextChanged(Editable s) {}
        });

        searchField.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                if (actionId == EditorInfo.IME_ACTION_DONE) {
                    InputMethodManager imm = (InputMethodManager)v.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                    imm.hideSoftInputFromWindow(v.getWindowToken(), 0);
                    searchBar.setVisibility(View.GONE);
                    mainView.requestFocus();
                    return true;
                }
                return false;
            }
        });

        topLeftMenu.setOnClickListener(v -> {
            if(GLView != null && !mainView.getChildAt(0).equals(list)) {
                setObjectExplorerView();
            } else if(TeighaDWGJni.toParent() == 0) {
                ArrayAdapter adapter = (ArrayAdapter) list.getAdapter();
                adapter.clear();
                adapter.addAll(TeighaDWGJni.getCurrentObjects());
            } else {

                GLView = new TeighaDwgView(getApplication());

                setGLView();
                GLView.init(false, 24, 2);
                GLView.setTouchMode("pan");

                TeighaDWGJni.init();

                new Thread(new Runnable() {
                    public void run() {
                        TeighaDWGJni.open(currentFile);
                        GLView.onLoad();
                        GLView.requestRender();
                    }
                }).start();
            }
        });


        topRightMenu.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                int x = Math.round(motionEvent.getX());
                int y = Math.round(motionEvent.getY());

                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    if(mainView.getChildAt(0).equals(GLView)) {

                        ImageView projectionImage = new ImageView(mApp);

                        if (currentViewType == TeighaDwgView.PROJECTION_PARALLEL) {
                            projectionImage.setImageDrawable(getDrawable(R.drawable.projection_isometric));
                            currentViewType = TeighaDwgView.PROJECTION_PERSPECTIVE;
                            GLView.setProjection(TeighaDwgView.PROJECTION_PERSPECTIVE);
                        } else {
                            projectionImage.setImageDrawable(getDrawable(R.drawable.projection_perspective));
                            currentViewType = TeighaDwgView.PROJECTION_PARALLEL;
                            GLView.setProjection(TeighaDwgView.PROJECTION_PARALLEL);
                        }

                        topRightMenu.removeAllViews();
                        topRightMenu.addView(projectionImage);
                    } else {
                        searchBar.setVisibility(searchBar.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);
                        searchField.requestFocus();
                    }

                }

                return true;
            }
        });


        bottomMenu.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                int x = Math.round(motionEvent.getX());
                int y = Math.round(motionEvent.getY());

                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {

                        View child = findViewById(getMenuItemIdByCoordinates(x, y, bottomMenu));

                        if (child != null && currentMenuItemId != child.getId() && mainView.getChildAt(0).equals(GLView)) {
                            int selectedSubmenuId = 0;
                            switch (child.getId()) {
                                case R.id.file:
                                    setList();
                                    titleView.setText(R.string.files_title);
                                    break;
                                case R.id.view:
                                    selectedSubmenuId = R.layout.view_menu;
                                    titleView.setText(R.string.view_title);
                                    break;
                                case R.id.navigation:
                                    selectedSubmenuId = R.layout.navigation_menu;
                                    titleView.setText(R.string.navigation_title);
                                    break;
                                case R.id.visual_style:
                                    selectedSubmenuId = R.layout.visual_style_menu;
                                    titleView.setText(R.string.visual_style_title);
                                    break;
                                case R.id.regen:
                                    selectedSubmenuId = R.layout.regen_menu;
                                    titleView.setText(R.string.regen_title);
                                    break;
                            }
                            subMenuView.removeAllViews();
                            if (selectedSubmenuId != 0) {
                                View selectedSubMenuView = getLayoutInflater().inflate(selectedSubmenuId, null);
                                subMenuView.addView(selectedSubMenuView);
                                subMenuView.setVisibility(View.VISIBLE);
                            }
                            currentMenuItemId = child.getId();
                        } else {
                            subMenuView.setVisibility(View.GONE);
                            currentMenuItemId = 0;
                            return true;
                        }

                }
                return true;
            }
        });

        subMenuView.setOnTouchListener(new View.OnTouchListener() {

            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                int x = Math.round(motionEvent.getX());
                int y = Math.round(motionEvent.getY());

                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {

                    LinearLayout menu = (LinearLayout) subMenuView.getChildAt(0);

                    View menuItem = findViewById(getMenuItemIdByCoordinates(x, y, menu));

                    if (currentSubMenuItemId != menuItem.getId() && mainView.getChildAt(0).equals(GLView)) {

                        switch (currentMenuItemId) {
                            case R.id.view:
                                GLView.setViewPosition(Integer.parseInt((String)menuItem.getTag()));
                                break;
                            case R.id.navigation:
                                proceedNavigationMenu((String)menuItem.getTag());
                                break;
                            case R.id.visual_style:
                                GLView.setVisualStyle((String)menuItem.getTag());
                                break;
                            case R.id.regen:
                                GLView.regen((String) menuItem.getTag());
                                break;
                        }
                    }
                    subMenuView.setVisibility(View.GONE);
                    currentMenuItemId = 0;
                    currentSubMenuItemId = 0;
                }
                return true;
            }

        });
        mainView = (RelativeLayout) findViewById(R.id.mainView);

        list = (ListView) getLayoutInflater().inflate(R.layout.list, null);
        mListAdapter = new DWGFileAdapter(this);

        list.setTextFilterEnabled(true);

        setList();

        //copy adinit.dat file from assets to external storage
        CopyFileTask copyTask = new CopyFileTask();
        copyTask.execute();
    }

    private void proceedNavigationMenu(String navigationActionTag) {
        switch (navigationActionTag) {
            case "zoom_extents":
                GLView.zoomExtents();
                break;
            default:
                GLView.setTouchMode(navigationActionTag);
        }
    }

    private int getMenuItemIdByCoordinates(int x, int y, @NonNull ViewGroup parent) {
        int itemId = 0;
        for (int i = 0; i < parent.getChildCount(); i++) {
            View child = parent.getChildAt(i);
            if (x > child.getLeft() && x < child.getRight() && y > child.getTop() && y < child.getBottom()) {
                itemId = child.getId();
                break;
            }
        }
        return itemId;
    }

    private void setList() {
        ListView listView = (ListView) list.findViewById(R.id.list);

        mainView.removeAllViews();
        if (listViewLoaded) {
            mListAdapter = new DWGFileAdapter(this);
            onResumeListView();
        }
        mainView.addView(list);

        topRightMenu.removeAllViews();
        ImageView searchImage = new ImageView(mApp);
        searchImage.setImageDrawable(getDrawable(R.drawable.ic_search));
        topRightMenu.addView(searchImage);

        topLeftMenu.setVisibility(View.GONE);


        listView.setAdapter(mListAdapter);
    }

    private void setObjectExplorerView() {
        ListView listView = (ListView) list.findViewById(R.id.list);
        TeighaDWGJni.createObjectExplorer();
        GLView.onDestroy();
        mainView.removeAllViews();
        if (listViewLoaded) {
            mListAdapter = new ObjectExplorerAdapter(mApp, new LinkedList<String>(Arrays.asList(TeighaDWGJni.getCurrentObjects())));
        }
        mainView.addView(list);

        subMenuView.setVisibility(View.GONE);

        topRightMenu.removeAllViews();
        listView.setAdapter(mListAdapter);

        ImageView backArrow = (ImageView) findViewById(R.id.back_arrow);
        backArrow.setVisibility(View.VISIBLE);

        TextView objectExplorerBtn = (TextView) findViewById(R.id.object_explorer_btn);
        objectExplorerBtn.setText(R.string.object_explorer_back_btn);
    }

    private void setGLView() {
        topRightMenu.removeAllViews();
        ImageView projectionImage = new ImageView(mApp);

        currentViewType = TeighaDwgView.PROJECTION_PARALLEL;
        projectionImage.setImageDrawable(getDrawable(R.drawable.projection_perspective));
        titleView.setText(R.string.navigation_title);
        currentMenuItemId = R.id.navigation;
        currentSubMenuItemId = R.layout.navigation_menu;
        subMenuView.removeAllViews();
        View selectedSubMenuView = getLayoutInflater().inflate(currentSubMenuItemId, null);
        subMenuView.addView(selectedSubMenuView);
        subMenuView.setVisibility(View.VISIBLE);

        ImageView backArrow = (ImageView) findViewById(R.id.back_arrow);
        backArrow.setVisibility(View.GONE);

        TextView objectExplorerBtn = (TextView) findViewById(R.id.object_explorer_btn);
        objectExplorerBtn.setText(R.string.object_explorer_btn);

        topLeftMenu.setVisibility(View.VISIBLE);

        topRightMenu.addView(projectionImage);
        mainView.removeAllViews();
        mainView.addView(GLView);
    }

    @Override
    protected void onResume() {
        super.onResume();
        listViewLoaded = true;
        // Read preferences
        // onResumeListView();

    }

    private void onResumeListView() {
        Resources res = getBaseContext().getResources();
        SharedPreferences SP = PreferenceManager.getDefaultSharedPreferences(getBaseContext());

        boolean readRecursefly = false;
        String fileExt;
        if (TeighaDWGJni.loadedLibrary == TeighaDWGJni.LIBRARY.TEIGHA) {
            fileExt = Arrays.toString(res.getStringArray(R.array.file_extension_default));
        } else {
            fileExt = Arrays.toString(res.getStringArray(R.array.file_extension_defaultA));
        }

        Map<String, ?> allEntries = SP.getAll();
        for (Map.Entry<String, ?> entry : allEntries.entrySet()) {
            if (MainSettings.KEY_FOLDER_DEPTH.equals(entry.getKey())) {
                readRecursefly = Boolean.valueOf(entry.getValue().toString());
            } else if (MainSettings.KEY_SELECTED_EXT.equals(entry.getKey())) {
                fileExt = entry.getValue().toString();
            }
        }

        ArrayList<String> fileExtArrayValues = new ArrayList<String>();
        fileExt = fileExt.replace(" ", "").replace("[", "").replace("]", "");
        String[] extEntries;
        String[] extValues;
        if (TeighaDWGJni.loadedLibrary == TeighaDWGJni.LIBRARY.TEIGHA) {
            extEntries = res.getStringArray(R.array.file_extension_entries);
            extValues = res.getStringArray(R.array.file_extension_values);
        } else {
            extEntries = res.getStringArray(R.array.file_extension_entriesA);
            extValues = res.getStringArray(R.array.file_extension_valuesA);
        }
        for (String it : Arrays.asList(fileExt.split(","))) {
            fileExtArrayValues.add(extEntries[Integer.valueOf(extValues[Integer.valueOf(it)])]);
        }
        ((DWGFileAdapter)mListAdapter).setReadRecursive(readRecursefly);
        ((DWGFileAdapter)mListAdapter).setEnabledExtensions(fileExtArrayValues);
        ((DWGFileAdapter)mListAdapter).rebuild(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main_menu, menu);//Menu Resource, Menu
        return true;
    }


    public class CopyFileTask extends AsyncTask<Void, Void, Void> {
        @Override
        protected Void doInBackground(Void... params) {
            copyFile("adinit.dat");
            copyFile("TD.tsbf");
            return null;
        }
    }
}