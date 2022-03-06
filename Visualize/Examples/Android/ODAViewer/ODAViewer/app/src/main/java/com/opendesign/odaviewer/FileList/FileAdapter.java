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
package com.opendesign.odaviewer.FileList;

import android.content.Context;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Filterable;
import android.widget.ListView;

import com.opendesign.odaviewer.R;

import java.io.File;
import java.io.FileFilter;
import java.util.ArrayList;
import java.util.Comparator;

public class FileAdapter extends ArrayAdapter<FileInfo> implements Filterable {

    boolean mReadRecurcevly;
    ArrayList<String> mExtEntries;

    private Handler mPdHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            notifyDataSetChanged();
        }
    };
    private Handler mDataHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            FileInfo new_file = (FileInfo) msg.obj;
            add(new_file);
        }
    };

    public FileAdapter(Context context) {
        super(context, R.layout.file_list_row);
        mReadRecurcevly = false;
        mExtEntries = new ArrayList<String>();
    }

    @Override
    public void notifyDataSetChanged() {

        setNotifyOnChange(false);
        sort(new Comparator<FileInfo>() {
            @Override
            public int compare(FileInfo o1, FileInfo o2) {
                return o1.FileName.compareToIgnoreCase(o2.FileName);
            }
        });
        setNotifyOnChange(true);

        super.notifyDataSetChanged();
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
                    mDataHandler.sendMessage(mDataHandler.obtainMessage(0, new FileInfo(files[index].getAbsolutePath(), files[index].getName(), files[index].length())));
                }
            }
        }
    }

    private void _rebuildSync() {
        File sdcard = Environment.getExternalStorageDirectory();
        File downloads = Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS);
        if (sdcard.isDirectory()) {
            _readDir(sdcard);
        }
        if(downloads.isDirectory())
            _readDir(downloads);
    }

    public void rebuild(Context ctx) {
        this.clear();
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
            FileInfo item = (FileInfo) getItem(position);
            return item.getView(position, convertView, parent);
        } catch (Exception e) {
            return null;
        }
    }
}
