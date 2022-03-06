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

//
// Debug command messages container
//

/*
#ifndef CMD_DEF
#define DO_UNDEF_CMD_DEF 1
#define CMD_DEF(CmdName, GroupName)
#endif
*/



//       CommandName   GroupName

//       prompts

CMD_MSG_DEF( kwdYesNoKwds,                OD_T("Yes No"))
CMD_MSG_DEF( pmtEnterVariableNameOr,      OD_T("Enter variable name or [?]%ls:"))
CMD_MSG_DEF( pmtEnterVariablesToList,     OD_T("Enter variable(s) to list <*>:"))
CMD_MSG_DEF( pmtEnterNewValueFor,         OD_T("Enter new value for %ls <%ls>:"))               // params: 1-VAR NAME, 2-VAR VALUE
CMD_MSG_DEF( pmtEnterNewValueForOrDot,    OD_T("Enter new value for %ls, or . for %ls <%ls>:"))  // params: 1-VAR NAME, 2-DEFAULT VALUE NAME, 3-VAR VALUE
CMD_MSG_DEF( pmtEnterNewValueForOrDotForNone,OD_T("Enter new value for %ls, or . for none <%ls>:"))// params: 1-VAR NAME, 2-VAR VALUE
CMD_MSG_DEF( pmtViewCmdEnterAnOption,     OD_T("Enter an option [?/Categorize/lAyer state/Orthographic/Delete/Restore/Save/Ucs/Window]:"))
CMD_MSG_DEF( kwdViewCmd1,                 OD_T("? Categorize lAyer Orthographic Delete Restore Save Ucs Window"))
CMD_MSG_DEF( kwdViewCmd2,                 OD_T("Save Delete Cancel"))
CMD_MSG_DEF( kwdViewCmd3,                 OD_T("Top Bottom Front BAck Left Right"))
CMD_MSG_DEF( pmtEnterViewNamesToDelete,   OD_T("Enter view name(s) to delete:"))
CMD_MSG_DEF( pmtEnterViewNameToRestore,   OD_T("Enter view name to restore:"))
CMD_MSG_DEF( pmtEnterViewNameToSave,      OD_T("Enter view name to save:"))
CMD_MSG_DEF( pmtEnterViewNameToEditLayerState,OD_T("Enter view name to edit Layer State or [?]:"))
CMD_MSG_DEF( pmtEnterViewNameToCategorize,OD_T("Enter view name to Categorize or [?]:"))
CMD_MSG_DEF( pmtEnterViewNameToList,      OD_T("Enter view name(s) to list <*>:"))
CMD_MSG_DEF( pmtViewAlreadyExistsReplaceIt,OD_T("View \"%ls\" already exists.  Replace it? <N>"))
CMD_MSG_DEF( pmtEnterAnOptionSaveDeleteCancel,OD_T("Enter an option [Save/Delete] <Cancel>:"))
CMD_MSG_DEF( pmtEnterCategoryNameOrForNone,OD_T("Enter category name or * for none, or [?]: <\"%ls\">"))
CMD_MSG_DEF( pmtEnterAnOptionOrthographic,OD_T("Enter an option [Top/Bottom/Front/BAck/Left/Right]<Top>:"))
//CMD_MSG_DEF( pmtEnterDimStyleNameToSet,   OD_T("Enter dimension style name:"))
CMD_MSG_DEF( pmtEnterImageQualitySetting, OD_T("Enter image quality setting [High/Draft] <%ls>:"))

CMD_MSG_DEF( msgRequiresAnIntegerBetween, OD_T("Requires an integer between %d and %d."))
CMD_MSG_DEF( msgRequires0or1onlyOrOptionKeyword,OD_T("Requires 0 or 1 only, or option keyword."))
CMD_MSG_DEF( msgCannotFindSpecifiedView,  OD_T("Cannot find view \"%ls\"."))
CMD_MSG_DEF( msgSpecifiedViewAlreadyExists,OD_T("View \"%ls\" already exists."))
CMD_MSG_DEF( msgUcsWillBeSavedWithView,   OD_T("UCSVIEW = 1  UCS will be saved with view"))
CMD_MSG_DEF( msgSavedViews,               OD_T("Saved views:"))
CMD_MSG_DEF( msgViewTabColumns,           OD_T("View name                        Space"))
CMD_MSG_DEF( msgUnknownVariableName,      OD_T("Unknown variable name.  Type SETVAR ? for a list of variables."))
CMD_MSG_DEF( msgROVariableValue,          OD_T("%ls = %ls (read only)"))
CMD_MSG_DEF( msgWorld,                    OD_T("World"))
CMD_MSG_DEF( msgDefault,                  OD_T("default"))
CMD_MSG_DEF( msgNWasWereNotAbleToBeExploded,OD_T("1 was not able to be exploded.\0%d were not able to be exploded."))
CMD_MSG_DEF( numFieldsFound,              OD_T("%d field(s) found."))
CMD_MSG_DEF( numFieldsUpdated,            OD_T("%d field(s) updated."))

CMD_MSG_DEF( kwdAutoControlBeginEndMarkBack,OD_T("Auto Control BEgin End Mark Back"))
CMD_MSG_DEF( kwdControl,                  OD_T("Control"))
CMD_MSG_DEF( pmtEnterTheNumberOfOperationsToUndo,OD_T("Enter the number of operations to undo or [Auto/Control/BEgin/End/Mark/Back] <1>:"))
CMD_MSG_DEF( pmtUndoCmdEnterAnOption,     OD_T("Enter an option [Control] <1>:"))
CMD_MSG_DEF( pmtEnterUNDOAutoModeOnOff,   OD_T("Enter UNDO Auto mode [ON/OFF] <%ls>:"))
CMD_MSG_DEF( pmtEnterAnUNDOControlOption, OD_T("Enter an UNDO control option [All/None/One/Combine] <All>:"))
CMD_MSG_DEF( pmtCombineZoomAndPanOperations,OD_T("Combine zoom and pan operations? [Yes/No] <Yes>:"))
CMD_MSG_DEF( msgUNDOCurrentSettings,      OD_T("UNDO Current settings: Auto = %ls, Control = %ls, Combine = %ls"))
CMD_MSG_DEF( msgNothingToUndo,            OD_T("Nothing to undo"))
CMD_MSG_DEF( msgNothingToRedo,            OD_T("Nothing to redo"))
CMD_MSG_DEF( msgEverythingHasBeenUndone,  OD_T("Everything has been undone"))
CMD_MSG_DEF( msgEverythingHasBeenRedone,  OD_T("Everything has been redone"))
CMD_MSG_DEF( kwdOnOff,                    OD_T("ON OFf"))
CMD_MSG_DEF( kwdAllNoneOneCombine,        OD_T("All None One Combine"))
CMD_MSG_DEF( kwdHighDraft,                OD_T("High Draft"))
CMD_MSG_DEF( pmtThisWillUndoEverything,   OD_T("This will undo everything. OK? <Y>"))
CMD_MSG_DEF( msgOn,                       OD_T("On"))
CMD_MSG_DEF( msgOff,                      OD_T("Off"))
CMD_MSG_DEF( msgHigh,                     OD_T("High"))
CMD_MSG_DEF( msgDraft,                    OD_T("Draft"))
CMD_MSG_DEF( msgNWasWereOnALockedLayer,   OD_T("1 was on a locked layer.\0%d were on a locked layer."))



/*
#ifdef DO_UNDEF_CMD_DEF
#undef CMD_DEF
#undef DO_UNDEF_CMD_DEF
#endif
*/
