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
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.List;

public class ObjectExplorerAdapter extends ArrayAdapter<String> {

    public ObjectExplorerAdapter(@NonNull Context context, List<String> content) {
        super(context, R.layout.object_explorer_item, content);
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {

        boolean expandable = TeighaDWGJni.getChildrenCount(position) > 0;

        View view = ((LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE)).inflate(R.layout.object_explorer_item, parent, false);
        TextView objectNameView = (TextView) view.findViewById(R.id.object_name);
        objectNameView.setText((position+1) + ". " + getItem(position));
        ImageView expandArrowView = (ImageView) view.findViewById(R.id.expand_arrow);
        expandArrowView.setVisibility(expandable ? View.VISIBLE : View.GONE);

        if(expandable) {
            view.setOnClickListener(v -> {
                clear();
                TeighaDWGJni.toChild(position);
                addAll(TeighaDWGJni.getCurrentObjects());
            });
        }
        return view;
    }


}
