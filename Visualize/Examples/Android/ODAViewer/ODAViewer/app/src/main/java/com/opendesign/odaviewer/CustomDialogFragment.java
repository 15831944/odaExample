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

import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.fragment.app.DialogFragment;

import com.opendesign.odaviewer.ImportParams.DgnImportParams;
import com.opendesign.odaviewer.ImportParams.DwgImportParams;
import com.opendesign.odaviewer.ImportParams.ObjImportParams;
import com.opendesign.odaviewer.ImportParams.PrcImportParams;
import com.opendesign.odaviewer.ImportParams.StlImportParams;

import java.nio.ByteBuffer;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Objects;

public class CustomDialogFragment extends DialogFragment {

    enum DialogType {
        MainActivityOptions,
        RenderActivityOptions,
        MarkupSave,
        MarkupLoad,
        DwgImportParams,
        StlImportParams,
        PrcImportParams,
        DgnImportParams,
        ObjImportParams,
        Save
    }

    private DialogType mType;

    private DialogListener dialogListener;

    public CustomDialogFragment(DialogType type) {
        mType = type;
    }

    private String _pathForSave = null;

    @NonNull
    public Dialog onCreateDialog(Bundle savedInstanceState) {

        AlertDialog.Builder builder = new AlertDialog.Builder(getActivity());

        String title = "Settings";
        String posBtn = "OK";
        String negBtn = "Cancel";

        View rootView = null;
        switch (mType) {

            case MainActivityOptions:
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.settings_main_dialog, null);
                break;
            case RenderActivityOptions:
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.settings_render_dialog, null);
                break;
            case MarkupSave: {
                title = "Save markup";
                posBtn = "Save";
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.markup_save, null);
                break;
            }
            case MarkupLoad: {
                title = "Load markup";
                posBtn = "Load";
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.markup_load, null);
                break;
            }
            case DwgImportParams: {
                title = "DWG import parameters";
                posBtn = "Open";
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.dwg_import_params, null);
                break;
            }
            case StlImportParams: {
                title = "STL import parameters";
                posBtn = "Open";
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.stl_import_params, null);
                break;
            }
            case PrcImportParams: {
                title = "PRC import parameters";
                posBtn = "Open";
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.prc_import_params, null);
                break;
            }
            case DgnImportParams: {
                title = "DGN import parameters";
                posBtn = "Open";
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.dgn_import_params, null);
                break;
            }
            case ObjImportParams: {
                title = "OBJ import parameters";
                posBtn = "Open";
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.obj_import_params, null);
                break;
            }
            case Save: {
                title = "Save to .vsf";
                posBtn = "Save";
                rootView = Objects.requireNonNull(getActivity()).getLayoutInflater().inflate(R.layout.save_file, null);
                break;
            }
        }

        builder.setView(rootView);

        // setup list
        boolean isNeedKeyboard = false;

        switch (mType) {

            case MainActivityOptions:
                fillMainControls(rootView);
                break;
            case RenderActivityOptions:
                fillRenderControls(rootView);
                break;
            case MarkupSave: {
                EditText et = rootView.findViewById(R.id.markup_save_edit);
                et.requestFocus();
                isNeedKeyboard = true;
                break;
            }
            case MarkupLoad: {
                ListView lv = rootView.findViewById(R.id.markupsList);
                dialogListener.setupList(lv);
                // select first
                lv.setItemChecked(0, true);
                break;
            }
            case DwgImportParams:
                fillDwgImportParamsControls(rootView);
                break;
            case StlImportParams:
                fillStlImportParamsControls(rootView);
                break;
            case PrcImportParams:
                fillPrcImportParamsControls(rootView);
                break;
            case DgnImportParams:
                fillDgnImportParamsControls(rootView);
                break;
            case ObjImportParams:
                fillObjImportParamsControls(rootView);
                break;
            case Save:
                fillSaveControls(rootView);
                break;
        }

        builder.setTitle(title);
        builder.setIcon(R.mipmap.ic_launcher);
        builder.setPositiveButton(posBtn, new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        switch (mType) {

                            case MainActivityOptions:
                                applyMainSettings();
                                break;
                            case RenderActivityOptions:
                                applyRenderSettings();
                                break;
                            case MarkupSave: {
                                EditText et = getDialog().findViewById(R.id.markup_save_edit);
                                if(et != null) {
                                    String saveName = et.getText().toString();
                                    dialogListener.saveMarkup(saveName);
                                }
                                break;
                            }
                            case MarkupLoad: {
                                ListView lstView = getDialog().findViewById(R.id.markupsList);
                                String selectedStr = lstView.getAdapter().getItem(lstView.getCheckedItemPosition()).toString();
                                dialogListener.loadMarkup(selectedStr);
                                break;
                            }
                            case DwgImportParams:
                                applyDwgImportParams();
                                dialogListener.onImportDialogAccepted();
                                break;
                            case StlImportParams:
                                applyStlImportParams();
                                dialogListener.onImportDialogAccepted();
                                break;
                            case PrcImportParams:
                                applyPrcImportParams();
                                dialogListener.onImportDialogAccepted();
                                break;
                            case DgnImportParams:
                                applyDgnImportParams();
                                dialogListener.onImportDialogAccepted();
                                break;
                            case ObjImportParams:
                                applyObjImportParams();
                                dialogListener.onImportDialogAccepted();
                                break;
                            case Save:
                                saveFile();
                                break;
                        }
                    }
                });
        builder.setNegativeButton(negBtn, null);
        AlertDialog dlg = builder.create();
        if(isNeedKeyboard)
            Objects.requireNonNull(dlg.getWindow()).setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_STATE_VISIBLE);

        return dlg;
    }

    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        try {
            dialogListener = (DialogListener)context;
        } catch (ClassCastException e) {
            throw new ClassCastException(context.toString() + " must implement MarkupDialogListener");
        }
    }

    public interface DialogListener {
        void saveMarkup(String markupName);
        void loadMarkup(String markupName);
        void setupList(ListView listView);
        void onImportDialogAccepted();
    }

    private void applyMainSettings() {
        MainActivity.Settings.WcsEnabled = getSwitchValue(R.id.ms_wcsSwitch);
        MainActivity.Settings.FpsEnabled = getSwitchValue(R.id.ms_fpsSwitch);
        MainActivity.Settings.AnimationEnabled = getSwitchValue(R.id.ms_animSwitch);
        MainActivity.Settings.PartialOpenEnabled = getSwitchValue(R.id.ms_partialSwitch);
        MainActivity.Settings.UseLimitManager = getSwitchValue(R.id.ms_useLimitSwitch);
        EditText limitVal = getDialog().findViewById(R.id.ms_limitEditText);
        MainActivity.Settings.LimitValue = Long.valueOf(limitVal.getText().toString());
        MainActivity.Settings.SceneGraphEnabled = getSwitchValue(R.id.ms_useSceneGraphSwitch);
        MainActivity.Settings.FixedFrameRateEnabled = getSwitchValue(R.id.ms_ffr);
        SeekBar ffrVal = getDialog().findViewById(R.id.ms_ffrSeekBar);
        MainActivity.Settings.FixedFrameRateValue = ffrVal.getProgress();
        VisualizeSdkJni.setGlobalParams(MainActivity.Settings);
    }

    private void fillMainControls(View rootView) {
        setSwitch(rootView, R.id.ms_wcsSwitch, MainActivity.Settings.WcsEnabled);
        setSwitch(rootView, R.id.ms_fpsSwitch, MainActivity.Settings.FpsEnabled);
        setSwitch(rootView, R.id.ms_animSwitch, MainActivity.Settings.AnimationEnabled);

        Switch partialSw = rootView.findViewById(R.id.ms_partialSwitch);
        partialSw.setChecked(MainActivity.Settings.PartialOpenEnabled);
        partialSw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                Switch useLimitSw = getDialog().findViewById(R.id.ms_useLimitSwitch);
                useLimitSw.setEnabled(isChecked);

                int color = Objects.requireNonNull(getActivity()).getColor(isChecked ? R.color.enabledTextColor : R.color.disabledTextColor);
                TextView useLimitLbl = getDialog().findViewById(R.id.ms_useLimitTextView);
                useLimitLbl.setTextColor(color);

                if(useLimitSw.isChecked()) {
                    TextView limitValLbl = getDialog().findViewById(R.id.ms_limitTextView);
                    limitValLbl.setTextColor(color);
                    EditText limitVal = getDialog().findViewById(R.id.ms_limitEditText);
                    limitVal.setTextColor(color);
                }
            }
        });

        Switch useLimitSw = rootView.findViewById(R.id.ms_useLimitSwitch);
        useLimitSw.setChecked(MainActivity.Settings.UseLimitManager);
        useLimitSw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                (getDialog().findViewById(R.id.ms_limitEditText)).setEnabled(isChecked);

                int color = Objects.requireNonNull(getActivity()).getColor(isChecked ? R.color.enabledTextColor : R.color.disabledTextColor);
                TextView limitValLbl = getDialog().findViewById(R.id.ms_limitTextView);
                limitValLbl.setTextColor(color);
                EditText limitVal = getDialog().findViewById(R.id.ms_limitEditText);
                limitVal.setTextColor(color);
            }
        });

        EditText limitVal = rootView.findViewById(R.id.ms_limitEditText);
        limitVal.setText(String.valueOf(MainActivity.Settings.LimitValue));

        if(!MainActivity.Settings.PartialOpenEnabled) {
            (rootView.findViewById(R.id.ms_useLimitSwitch)).setEnabled(false);
            TextView useLimitLbl = rootView.findViewById(R.id.ms_useLimitTextView);
            useLimitLbl.setTextColor(Objects.requireNonNull(getActivity()).getColor(R.color.disabledTextColor));
            TextView limitValLbl = rootView.findViewById(R.id.ms_limitTextView);
            limitValLbl.setTextColor(Objects.requireNonNull(getActivity()).getColor(R.color.disabledTextColor));
            limitVal.setTextColor(Objects.requireNonNull(getActivity()).getColor(R.color.disabledTextColor));
            limitVal.setEnabled(false);
        }

        setSwitch(rootView, R.id.ms_useSceneGraphSwitch, MainActivity.Settings.SceneGraphEnabled);

        Switch ffrSw = rootView.findViewById(R.id.ms_ffr);
        ffrSw.setChecked(MainActivity.Settings.FixedFrameRateEnabled);
        ffrSw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                TextView ffrTxtView = getDialog().findViewById(R.id.ms_ffrTextView);
                SeekBar ffrVal = getDialog().findViewById(R.id.ms_ffrSeekBar);
                TextView ffrValLbl = getDialog().findViewById(R.id.ms_ffrValTextView);

                int color = Objects.requireNonNull(getActivity()).getColor(isChecked ? R.color.enabledTextColor : R.color.disabledTextColor);
                ffrTxtView.setTextColor(color);
                ffrValLbl.setTextColor(color);
                ffrVal.setEnabled(isChecked);
            }
        });

        SeekBar ffrVal = rootView.findViewById(R.id.ms_ffrSeekBar);
        ffrVal.setProgress(MainActivity.Settings.FixedFrameRateValue);
        ffrVal.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                TextView ffrValLbl = getDialog().findViewById(R.id.ms_ffrValTextView);
                ffrValLbl.setText(String.valueOf(progress));
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        TextView ffrValLbl = rootView.findViewById(R.id.ms_ffrValTextView);
        ffrValLbl.setText(String.valueOf(MainActivity.Settings.FixedFrameRateValue));
        if(!MainActivity.Settings.FixedFrameRateEnabled) {
            ffrVal.setEnabled(false);
            int color = Objects.requireNonNull(getActivity()).getColor(R.color.disabledTextColor);
            ffrValLbl.setTextColor(color);
            TextView ffrTxtView = rootView.findViewById(R.id.ms_ffrTextView);
            ffrTxtView.setTextColor(color);
        }
    }

    private void setSwitch(View rootView, int id, boolean isChecked) {
        Switch sw = rootView.findViewById(id);
        sw.setChecked(isChecked);
    }

    private boolean getSwitchValue(int id) {
        Dialog dlg = getDialog();
        if(dlg == null)
            return  false;
        Switch sw = dlg.findViewById(id);
        if(sw == null)
            return  false;
        return sw.isChecked();
    }

    private void applyRenderSettings() {
        MainActivity.Settings.WcsEnabled = getSwitchValue(R.id.rs_wcsSwitch);
        MainActivity.Settings.FpsEnabled = getSwitchValue(R.id.rs_fpsSwitch);
        MainActivity.Settings.AnimationEnabled = getSwitchValue(R.id.rs_animSwitch);
        MainActivity.Settings.FixedFrameRateEnabled = getSwitchValue(R.id.rs_ffrSwitch);
        SeekBar ffrVal = getDialog().findViewById(R.id.rs_ffrSeekBar);
        MainActivity.Settings.FixedFrameRateValue = ffrVal.getProgress();
        VisualizeSdkJni.setGlobalParams(MainActivity.Settings);
        VisualizeSdkJni.applyGlobalParams();
    }

    private void fillRenderControls(View rootView) {
        setSwitch(rootView, R.id.rs_wcsSwitch, MainActivity.Settings.WcsEnabled);
        setSwitch(rootView, R.id.rs_fpsSwitch, MainActivity.Settings.FpsEnabled);
        setSwitch(rootView, R.id.rs_animSwitch, MainActivity.Settings.AnimationEnabled);

        Switch ffrSw = rootView.findViewById(R.id.rs_ffrSwitch);
        ffrSw.setChecked(MainActivity.Settings.FixedFrameRateEnabled);
        ffrSw.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                int color = Objects.requireNonNull(getActivity()).getColor(isChecked ? R.color.enabledTextColor : R.color.disabledTextColor);
                TextView lbl = getDialog().findViewById(R.id.rs_ffrLbl);
                lbl.setTextColor(color);
                SeekBar sb = getDialog().findViewById(R.id.rs_ffrSeekBar);
                sb.setEnabled(isChecked);
                TextView valTxtView = getDialog().findViewById(R.id.rs_ffrValTextView);
                valTxtView.setTextColor(color);
            }
        });

        SeekBar sb = rootView.findViewById(R.id.rs_ffrSeekBar);
        sb.setProgress(MainActivity.Settings.FixedFrameRateValue);
        sb.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                TextView valTxtView = getDialog().findViewById(R.id.rs_ffrValTextView);
                valTxtView.setText( String.valueOf(progress) );
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        TextView valTxtView = rootView.findViewById(R.id.rs_ffrValTextView);
        valTxtView.setText( String.valueOf(MainActivity.Settings.FixedFrameRateValue) );

        if(!MainActivity.Settings.FixedFrameRateEnabled) {
            int color = Objects.requireNonNull(getActivity()).getColor(R.color.disabledTextColor);
            TextView lbl = rootView.findViewById(R.id.rs_ffrLbl);
            lbl.setTextColor(color);
            sb.setEnabled(false);
            valTxtView.setTextColor(color);
        }
    }

    private void fillDwgImportParamsControls(View rootView) {
        DwgImportParams dwgParams = new DwgImportParams();
        VisualizeSdkJni.getDwgImportParams(dwgParams);

        setSwitch(rootView, R.id.dwg_StoreSourceSwitch, dwgParams.StoreSource);
        setSwitch(rootView, R.id.dwg_ClearEmptyObjectsSwitch, dwgParams.ClearEmptyObjects);

        Switch mtSwitch = rootView.findViewById(R.id.dwg_EnableMTSwitch);
        mtSwitch.setChecked(dwgParams.EnableMT);
        mtSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                int color = Objects.requireNonNull(getActivity()).getColor(isChecked ? R.color.enabledTextColor : R.color.disabledTextColor);
                TextView lbl = getDialog().findViewById(R.id.dwg_MaxThreadsTxt);
                lbl.setTextColor(color);
                EditText threadsCnt = getDialog().findViewById(R.id.dwg_threadsCnt);
                threadsCnt.setEnabled(isChecked);
            }
        });

        EditText threadsCnt = rootView.findViewById(R.id.dwg_threadsCnt);
        threadsCnt.setText( String.valueOf(dwgParams.ThreadsCount) );

        int color = Objects.requireNonNull(getActivity()).getColor(mtSwitch.isChecked() ? R.color.enabledTextColor : R.color.disabledTextColor);
        TextView lbl = rootView.findViewById(R.id.dwg_MaxThreadsTxt);
        lbl.setTextColor(color);
        threadsCnt.setEnabled(mtSwitch.isChecked());

        setSwitch(rootView, R.id.dwg_BrepAsBrepSwitch, dwgParams.ImportBrepAsBrep);
        setSwitch(rootView, R.id.dwg_lowMemorySwitch, dwgParams.LowMemoryImport);

        View colorBtn = rootView.findViewById(R.id.dwg_colorBtn);
        if(colorBtn != null) {
            byte[] bytes = ByteBuffer.allocate(4).putInt(dwgParams.BackgroundColor).array();
            bytes[0] = (byte)0xFF;
            byte R = bytes[3];
            bytes[3] = bytes[1];
            bytes[1] = R;
            ByteBuffer buf = ByteBuffer.wrap(bytes);
            int reversed = buf.getInt();
            colorBtn.setBackgroundColor(reversed);
        }
    }

    private void applyDwgImportParams() {
        DwgImportParams dwgParams = new DwgImportParams();
        dwgParams.StoreSource = getSwitchValue(R.id.dwg_StoreSourceSwitch);
        dwgParams.ClearEmptyObjects = getSwitchValue(R.id.dwg_ClearEmptyObjectsSwitch);
        dwgParams.EnableMT = getSwitchValue(R.id.dwg_EnableMTSwitch);
        EditText threadsCntTxt = getDialog().findViewById(R.id.dwg_threadsCnt);
        dwgParams.ThreadsCount = Integer.parseInt( threadsCntTxt.getText().toString() );
        dwgParams.ImportBrepAsBrep = getSwitchValue(R.id.dwg_BrepAsBrepSwitch);
        dwgParams.LowMemoryImport = getSwitchValue(R.id.dwg_lowMemorySwitch);

        View colorBtn = getDialog().findViewById(R.id.dwg_colorBtn);
        if(colorBtn != null) {
            Drawable background = colorBtn.getBackground();
            if (background instanceof ColorDrawable) {
                int col = ((ColorDrawable) background).getColor();
                byte[] bytes = ByteBuffer.allocate(4).putInt(col).array();
                byte B = bytes[3];
                bytes[3] = bytes[1];
                bytes[1] = B;
                ByteBuffer buf = ByteBuffer.wrap(bytes);
                dwgParams.BackgroundColor = buf.getInt();
            }
        }

        VisualizeSdkJni.setDwgImportParams(dwgParams);
    }

    private void fillStlImportParamsControls(View rootView) {
        StlImportParams params = new StlImportParams();
        VisualizeSdkJni.getStlImportParams(params);

        setSwitch(rootView, R.id.stl_fixNormalsSwitch, params.FixNormals);
        setSwitch(rootView, R.id.stl_UnifyDuplVertSwitch, params.UnifyDuplicatedVertices);
        setSwitch(rootView, R.id.stl_calcNormalsSwitch, params.CalculateNormalsAtVertices);
    }

    private void applyStlImportParams() {
        StlImportParams params = new StlImportParams();
        params.FixNormals = getSwitchValue(R.id.stl_fixNormalsSwitch);
        params.UnifyDuplicatedVertices = getSwitchValue(R.id.stl_UnifyDuplVertSwitch);
        params.CalculateNormalsAtVertices = getSwitchValue(R.id.stl_calcNormalsSwitch);
        VisualizeSdkJni.setStlImportParams(params);
    }

    private void fillPrcImportParamsControls(View rootView) {
        PrcImportParams params = new PrcImportParams();
        VisualizeSdkJni.getPrcImportParams(params);

        setSwitch(rootView, R.id.prc_StoreSource, params.StoreSource);
        setSwitch(rootView, R.id.prc_ClearEmptyObjects, params.ClearEmptyObjects);
        setSwitch(rootView, R.id.prc_RearrangeObjects, params.RearrangeObjects);
        setSwitch(rootView, R.id.prc_ImportBrepAsBrep, params.ImportBrepAsBrep);
    }

    private void applyPrcImportParams() {
        PrcImportParams params = new PrcImportParams();
        params.StoreSource = getSwitchValue(R.id.prc_StoreSource);
        params.ClearEmptyObjects = getSwitchValue(R.id.prc_ClearEmptyObjects);
        params.RearrangeObjects = getSwitchValue(R.id.prc_RearrangeObjects);
        params.ImportBrepAsBrep = getSwitchValue(R.id.prc_ImportBrepAsBrep);
        VisualizeSdkJni.setPrcImportParams(params);
    }

    private void fillDgnImportParamsControls(View rootView) {
        DgnImportParams params = new DgnImportParams();
        VisualizeSdkJni.getDgnImportParams(params);

        setSwitch(rootView, R.id.dgn_StoreSource, params.StoreSource);
        setSwitch(rootView, R.id.dgn_ClearEmptyObjects, params.ClearEmptyObjects);
        setSwitch(rootView, R.id.dgn_UseIsoFor3DObjects, params.UseIsolinesFor3DObjects);
    }

    private void applyDgnImportParams() {
        DgnImportParams params = new DgnImportParams();
        params.StoreSource = getSwitchValue(R.id.dgn_StoreSource);
        params.ClearEmptyObjects = getSwitchValue(R.id.dgn_ClearEmptyObjects);
        params.UseIsolinesFor3DObjects = getSwitchValue(R.id.dgn_UseIsoFor3DObjects);
        VisualizeSdkJni.setDgnImportParams(params);
    }

    private void fillObjImportParamsControls(View rootView) {
        ObjImportParams params = new ObjImportParams();
        VisualizeSdkJni.getObjImportParams(params);

        setSwitch(rootView, R.id.obj_CalcNormals, params.CalculateNormalsAtVertices);
        setSwitch(rootView, R.id.obj_FlipUVcs, params.FlipUVCoordinateSystem);
        setSwitch(rootView, R.id.obj_ImportBrepAsBrep, params.ImportBrepAsBrep);
    }

    private void applyObjImportParams() {
        ObjImportParams params = new ObjImportParams();
        params.CalculateNormalsAtVertices = getSwitchValue(R.id.obj_CalcNormals);
        params.FlipUVCoordinateSystem = getSwitchValue(R.id.obj_FlipUVcs);
        params.ImportBrepAsBrep = getSwitchValue(R.id.obj_ImportBrepAsBrep);
        VisualizeSdkJni.setObjImportParams(params);
    }

    private void fillSaveControls(View rootView) {
        RenderActivity ra = (RenderActivity)getActivity();
        if(ra != null) {
            Path path = Paths.get(ra.FilePath);
            _pathForSave = path.getParent().toString() + "/";
            EditText et = rootView.findViewById(R.id.save_edit);
            String fileName = path.getFileName().toString();
            String newFileName = fileName.substring(0, fileName.indexOf("."));
            et.setText(String.format("%s.vsf", newFileName));
        }
    }

    private void saveFile() {
        EditText et = getDialog().findViewById(R.id.save_edit);
        _pathForSave += et.getText().toString();
        VisualizeSdkJni.saveFile(_pathForSave, getSwitchValue(R.id.save_file_indexesSwitch));
    }
}
