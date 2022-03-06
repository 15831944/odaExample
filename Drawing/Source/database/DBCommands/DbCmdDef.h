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
// Debug commands container
//

#ifndef CMD_DEF
#define CMD_DEF(a,b)
#define DO_UNDEF_CMD_DEF
#endif

#ifndef CMD_DEF2
#define CMD_DEF2(a,b) CMD_DEF(a,b)
#define DO_UNDEF_CMD_DEF2
#endif

#ifndef CMD_DEF3
#define CMD_DEF3(a,b,c) CMD_DEF(a,b)
#define DO_UNDEF_CMD_DEF3
#endif



//              Command Name            Group Name

CMD_DEF ( TDFILEPRODUCT         , ODDB_COMMANDS_GROUP_NAME)
CMD_DEF ( ERASE                 , ODDB_COMMANDS_GROUP_NAME)
CMD_DEF ( EXPLODE               , ODDB_COMMANDS_GROUP_NAME)
CMD_DEF3( REDO                  , ODDB_COMMANDS_GROUP_NAME,   OdEdCommand::kNoUndoMarker)
CMD_DEF ( SETVAR                , ODDB_COMMANDS_GROUP_NAME)
CMD_DEF3( UNDO                  , ODDB_COMMANDS_GROUP_NAME,   OdEdCommand::kNoUndoMarker)
CMD_DEF ( UPDATEFIELD           , ODDB_COMMANDS_GROUP_NAME)
CMD_DEF2( VIEW                  , ODDB_COMMANDS_GROUP_NAME)
CMD_DEF ( DIMSTYLE              , ODDB_COMMANDS_GROUP_NAME)
CMD_DEF ( IMAGEQUALITY          , ODDB_COMMANDS_GROUP_NAME)


#ifdef DO_UNDEF_CMD_DEF
#undef DO_UNDEF_CMD_DEF
#undef CMD_DEF
#endif

#ifdef DO_UNDEF_CMD_DEF2
#undef DO_UNDEF_CMD_DEF2
#undef CMD_DEF2
#endif

#ifdef DO_UNDEF_CMD_DEF3
#undef DO_UNDEF_CMD_DEF3
#undef CMD_DEF3
#endif
