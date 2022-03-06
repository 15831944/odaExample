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

#ifndef _PRCFILER_INCLUDED_
#define _PRCFILER_INCLUDED_ 
 

#include "PrcFilerController.h"

class OdPrcFilerController;
class OdPrcAuditInfo;

/** \details 
<group PRC_Input_Output_Operations>

This is an abstract class that implements .prc file input/output operations.
*/
class PRC_TOOLKIT OdPrcFiler : public OdRxObject
{
private:
  OdUInt32                          m_version;
  mutable OdPrcFilerControllerPtr   m_pFilerController;

  bool isVersionValid() const;

protected:
  OdPrcFiler(OdUInt32 version);

public:
  //DOM-IGNORE-BEGIN
  ODPRCRX_DECLARE(OdPrcFiler)
  //DOM-IGNORE-END
  
  /** \details
  Destroys the filer object.
  */
  virtual ~OdPrcFiler();

  /** \details
  Sets a new file controller object for the filer.
  
  \param pFilerController [in]  A pointer to a new file controller object to be set.
  */
  virtual void setController(OdPrcFilerController * pFilerController);

  /** \details
  Sets a new PRC format version value for the filer to work with.
  
  \param version [in] New PRC format version to be set.
  */
  virtual void setVersion(OdUInt32 version);
  
  /** \details
  Returns the current PRC format version for the filer.*/
  virtual OdUInt32 version() const;

  /** \details
  Returns the current file controller used for working with the filer.*/
  virtual OdPrcFilerController* controller() const;
  
  /** \details
  Moves the file pointer to the specified location in the filer.
  
  \param offset [in] A new position offset for the file pointer (in bytes).
  \param seekType [in] A seek type identifier.
    
  <table>
    Name                    Value       Description
    OdDb::kSeekFromStart    SEEK_SET    The new position is counted from the beginning of the file (file pointer will be moved to the count of bytes specified with offset parameter from the beginning of the file).
    OdDb::kSeekFromCurrent  SEEK_CUR    The new position of the file pointer is counted from the current position (new position = current position + offset).
    OdDb::kSeekFromEnd      SEEK_END    The new position is counted from the end of the file (file pointer will be moved to the count of bytes specified with offset parameter from the end of the file).
  </table>
  
  \remarks
  The default implementation of this function does nothing but throw an exception.
  */
  virtual OdUInt64 seek(OdInt64 offset, OdDb::FilerSeekType seekType) = 0;
  
  /** \details
  Returns the current file pointer position of the filer.
  
  \remarks 
  The default implementation of this function does nothing but throw an exception.
  */
  virtual OdUInt64 tell() = 0;
  
  /** \details
  Returns the current length of the .prc file associated with the filer.
  
  \remarks
  The default implementation of this function does nothing but throw an exception.
  */
  virtual OdUInt64 length() = 0;

  /** \details
  Starts a new data block in the file associated with the filer.
  
  \param pBlockName [in] The name of the block to be started.
  */
  virtual void levelIn(const char *pBlockName);
  
  /** \details
  Starts a new data block for an array in the file associated with the filer.
  
  \param pArrayName [in] The name of the array data block to be written.
  \param size [in] The size of the array block.
  
  \remarks
  This method does nothing and should be reimplemented.
  */  
  virtual void arrayIn(const char *pArrayName, OdUInt32 size);

  /** \details
  Starts an element data block in the file associated with the filer.
  
  \param pElementName [in] A name of an element data block to be written.
  \param index [in] An index of an element to be written.
  
  \remarks
  This method does nothing and should be reimplemented.
  */
  virtual void arrayElemIn(const char *pElementName, OdUInt32 index);
  
  /** \details 
  Finishes a data block in the file associated with the filer.
  
  \remarks
  This method does nothing and should be reimplemented.
  */
  virtual void levelOut();

  /** \details 
  Returns audit information from the filer.*/
  OdPrcAuditInfo * getAuditInfo() const;
};

SMARTPTR(OdPrcFiler);

#endif //_PRCRWFiler_INCLUDED_

