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

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.Manifest;
import android.app.Activity;
import android.app.ActivityOptions;
import android.app.AlertDialog;
import android.app.Application;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.SystemClock;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.ContextMenu;
import android.view.KeyEvent;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.inputmethod.EditorInfo;
import android.view.inputmethod.InputMethodManager;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;

import com.opendesign.odaviewer.FileList.FileAdapter;
import com.opendesign.odaviewer.FileList.FileInfo;
import com.opendesign.odaviewer.ImportParams.DwgImportParams;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Objects;

import yuku.ambilwarna.AmbilWarnaDialog;

public class MainActivity extends AppCompatActivity implements CustomDialogFragment.DialogListener {

    public static Application App;
    private Activity _curActivity;
    private View _mainView;
    private ArrayAdapter _listAdapter;
    private ListView _fileList;
    // search bar fields
    private View _searchBar;
    private EditText _searchField;
    private String _selectedFilePath = null;

    private int _longPressItmPos = -1;

    public static GlobalSettings Settings = new GlobalSettings();

    @Override
    protected void onDestroy() {
        VisualizeSdkJni.deactivate();
        super.onDestroy();
    }

    @Override
    protected void onStart() {
        super.onStart();
        fillList();
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);
        if(v.getId() == R.id.fileListView) {
            MenuInflater inflater = getMenuInflater();
            inflater.inflate(R.menu.menu_list, menu);
        }
    }

    @Override
    public boolean onContextItemSelected(@NonNull MenuItem item) {
        AdapterView.AdapterContextMenuInfo info = (AdapterView.AdapterContextMenuInfo) item.getMenuInfo();

        switch (item.getItemId()) {
            case R.id.menu_remove:
                if(_longPressItmPos >= 0) {
                    FileInfo f = (FileInfo) _listAdapter.getItem(_longPressItmPos);
                    if(f != null) {
                        File file = new File(f.FilePath);
                        if(file.exists() && file.delete()) {
                            _listAdapter.remove(_listAdapter.getItem(_longPressItmPos));
                            _listAdapter.notifyDataSetChanged();
                            _longPressItmPos = -1;
                        }
                    }
                }
                return true;
            default:
                return super.onContextItemSelected(item);
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        setTheme(R.style.AppTheme);

        SystemClock.sleep(1500);

        super.onCreate(savedInstanceState);

        _curActivity = this;
        App = getApplication();
        // hide bar with application title
        Objects.requireNonNull(getSupportActionBar()).hide();

        // check files permission
        if (Build.VERSION.SDK_INT >= 23) {
            while (checkSelfPermission(android.Manifest.permission.WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED)
                ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
        }

        // set activity
        setContentView(R.layout.activity_main);

        // initialize fields
        _mainView = findViewById(R.id.mainView);
        _searchBar = findViewById(R.id.search_bar);
        _searchField = findViewById(R.id.search_text);
        _searchField.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {
                if(s.length() > 0) {
                    _fileList.setTextFilterEnabled(true);
                    _fileList.setFilterText(_searchField.getText().toString());
                } else {
                    _fileList.clearTextFilter();
                }
            }

            @Override
            public void afterTextChanged(Editable s) {}
        });

        _searchField.setOnEditorActionListener(new TextView.OnEditorActionListener() {
            @Override
            public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
                if (actionId == EditorInfo.IME_ACTION_DONE) {
                    InputMethodManager imm = (InputMethodManager)v.getContext().getSystemService(Context.INPUT_METHOD_SERVICE);
                    if (imm != null) {
                        imm.hideSoftInputFromWindow(v.getWindowToken(), 0);
                    }
                    _searchBar.setVisibility(View.GONE);
                    _mainView.requestFocus();
                    return true;
                }
                return false;
            }
        });

        _fileList = findViewById(R.id.fileListView);
        registerForContextMenu(_fileList);
        _listAdapter = new FileAdapter(this);
        _fileList.setTextFilterEnabled(true);
        _fileList.setAdapter(_listAdapter);
        _fileList.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {

                // clear selection
                if(_fileList.getSelectedItem() != null)
                    _fileList.setItemChecked(-1, true);
                // select current
                view.setSelected(true);

                _longPressItmPos = position;

                return false;
            }
        });
        _fileList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                // clear selection
                if(_fileList.getSelectedItem() != null)
                    _fileList.setItemChecked(-1, true);
                // select current
                view.setSelected(true);

                // show import params
                _selectedFilePath = view.getTag().toString();

                if(getFileExtension(_selectedFilePath).toUpperCase().equals("DWG")) {
                    CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.DwgImportParams);
                    dlg.show(getSupportFragmentManager(), "custom");
                    return;
                }
                else if(getFileExtension(_selectedFilePath).toUpperCase().equals("STL")) {
                    CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.StlImportParams);
                    dlg.show(getSupportFragmentManager(), "custom");
                    return;
                }
                else if(getFileExtension(_selectedFilePath).toUpperCase().equals("PRC")) {
                    CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.PrcImportParams);
                    dlg.show(getSupportFragmentManager(), "custom");
                    return;
                }
                else if(getFileExtension(_selectedFilePath).toUpperCase().equals("DGN")) {
                    CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.DgnImportParams);
                    dlg.show(getSupportFragmentManager(), "custom");
                    return;
                }
                else if(getFileExtension(_selectedFilePath).toUpperCase().equals("OBJ")) {
                    CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.ObjImportParams);
                    dlg.show(getSupportFragmentManager(), "custom");
                    return;
                }

                view.setSelected(false);
                onOpen(_selectedFilePath);
                _selectedFilePath = null;
            }
        });

        VisualizeSdkJni.activate();

        VisualizeSdkJni.getGlobalParams(Settings);
    }

    private void onOpen(String filePath) {
        // go to second activity
        Intent intent = new Intent(App.getApplicationContext(), RenderActivity.class);
        intent.putExtra("filePath", filePath);
        startActivity(intent);
    }


    public static String getFileExtension(String filePath) {
        int lastIndexOf = filePath.lastIndexOf(".");
        if (lastIndexOf == -1) {
            return ""; // empty extension
        }
        String ext = filePath.substring(lastIndexOf + 1);
        return ext;
    }



    private void fillList() {
        String[] exts = getResources().getStringArray(R.array.file_extensions);

        ArrayList<String> fileExtArrayValues = new ArrayList<>(Arrays.asList(exts));
        ((FileAdapter)_listAdapter).setReadRecursive(false);
        ((FileAdapter)_listAdapter).setEnabledExtensions(fileExtArrayValues);
        ((FileAdapter)_listAdapter).rebuild(this);
    }

    public void onSearchButtonClick(View view) {
        _searchBar.setVisibility(_searchBar.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);
        _searchField.requestFocus();
        InputMethodManager imm = (InputMethodManager) getSystemService(Context.INPUT_METHOD_SERVICE);
        if (imm != null) {
            if(_searchBar.getVisibility() == View.VISIBLE)
                imm.showSoftInput(_searchField, InputMethodManager.SHOW_IMPLICIT);
            else
                imm.hideSoftInputFromWindow(_searchField.getWindowToken(), 0);
        }
    }

    public void onOptionsButtonClick(View view) {
        CustomDialogFragment dlg = new CustomDialogFragment(CustomDialogFragment.DialogType.MainActivityOptions);
        dlg.show(getSupportFragmentManager(), "custom");
    }

    @Override
    public void saveMarkup(String markupName) {

    }

    @Override
    public void loadMarkup(String markupName) {

    }

    @Override
    public void setupList(ListView listView) {

    }

    @Override
    public void onImportDialogAccepted() {
        onOpen(_selectedFilePath);
    }

    public void onChooseDwgColorClick(final View view) {
        AmbilWarnaDialog dialog = new AmbilWarnaDialog(this, 0, new AmbilWarnaDialog.OnAmbilWarnaListener() {
            @Override
            public void onOk(AmbilWarnaDialog dialog, int color) {
                view.setBackgroundColor(color);

            }

            @Override
            public void onCancel(AmbilWarnaDialog dialog) {
                // cancel was selected by the user
            }
        });
        AlertDialog dlg = dialog.getDialog();
        dlg.setTitle("Choose color:");
        dialog.show();
    }
}
