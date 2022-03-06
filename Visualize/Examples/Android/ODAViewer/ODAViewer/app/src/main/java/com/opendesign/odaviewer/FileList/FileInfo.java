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
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.opendesign.odaviewer.MainActivity;
import com.opendesign.odaviewer.R;

public class FileInfo {
    public String FilePath;
    public  String FileName;
    private long _fileSize;

    public FileInfo(String path, String file, long size) {
        FilePath = path;
        FileName = file;
        _fileSize = size;
    }

    public View getView(int position, View convertView, ViewGroup parent) {
        LayoutInflater inflater = (LayoutInflater) MainActivity.App.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        View view;
        view = inflater.inflate(R.layout.file_list_row, parent, false);
        view.setTag(FilePath);

        TextView filename_txt = (TextView) view.findViewById(R.id.filename);
        filename_txt.setText(FileName);

        TextView size_txt = (TextView) view.findViewById(R.id.size);
        long size = _fileSize;
        String metric;
        if (size > (1024 * 1024 * 1024)) {
            metric = " GB";
            size = size / (1024 * 1024 * 1024);
        } else if (size > (1024 * 1024)) {
            metric = " MB";
            size = size / (1024 * 1024);
        } else {
            metric = " KB";
            size = size / 1024;
        }
        size_txt.setText(size + metric);

        return view;
    }

    @Override
    public String toString() {
        return FileName;
    }
}
