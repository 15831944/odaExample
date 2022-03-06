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

#ifndef _BFC_TOPIC_FOLDER_H
#define _BFC_TOPIC_FOLDER_H

#include "BcfCommon.h"
#include "OdGUID.h"
#include "OdArray.h"
#define STL_USING_MAP
#include "OdaSTL.h"

/** \details
Contains declarations related to working with BCF files content.
*/
namespace OdBcf {

  class OdBcfMarkup;
  typedef OdSmartPtr<OdBcfMarkup> OdBcfMarkupPtr;

  class OdBcfVisualizationInfo;
  typedef OdSmartPtr<OdBcfVisualizationInfo> OdBcfVisualizationInfoPtr;
  
  /** \details 
  A data type that represents an array of smart pointers to <link OdBcf::OdBcfVisualizationInfo, OdBcfVisualizationInfo> objects.
  */
  typedef OdArray<OdBcfVisualizationInfoPtr> OdBcfVisualizationInfoArray;

  /** \details
  A class that provides functionality for working with a BCF topic folder.
  */
  class BCF_EXPORT OdBcfTopicFolder : public OdRxObject
  {
  public:

    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdBcfTopicFolder);
    //DOM-IGNORE-END

    /** \details
    Creates a new topic folder object.
    \param pMarkup           [in] A smart pointer to the markup of the topic folder.
    \param visualizationInfo [in] An array of smart pointers to visualization information about topics.
    \returns A smart pointer to the created <link OdBcf::OdBcfTopicFolder, OdBcfTopicFolder> instance.
    */
    static OdSmartPtr<OdBcfTopicFolder> createObject(
      const OdBcfMarkupPtr              &pMarkup, 
      const OdBcfVisualizationInfoArray &visualizationInfo);

    /** \details
    Checks whether the topic folder instance has all required fields initialized.
    \returns true if all required fields are initialized; otherwise the method returns false.
    */
    virtual bool validate() const;

    /** \details
    Sets the markup for the topic folder object.
    \param markupValue [in] A smart pointer to the <link OdBcf::OdBcfMarkup, OdBcfMarkup> object to be set.
    */
    void setMarkup(const OdBcfMarkupPtr &markupValue);

    /** \details
    Retrieves the topic folder's markup.
    \returns A smart pointer to the <link OdBcf::OdBcfMarkup, OdBcfMarkup> object that represents the markup.
    \remarks 
    The markup object returned by the method can be modified in the calling subroutine.
    */
    OdBcfMarkupPtr& getMarkup();

    /** \details
    Retrieves the topic folder's markup.
    \returns A smart pointer to the <link OdBcf::OdBcfMarkup, OdBcfMarkup> object that represents the markup.
    \remarks 
    The markup object returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfMarkupPtr& getMarkup() const;

    /** \details
    Defines whether the topic folder's markup is not initialized.
    \returns true if the markup object is not initialized; otherwise, the method returns false.
    */
    bool isMarkupUnset() const;

    /** \details
    Sets the visualization information for the topic folder object.
    \param visualizationInfoValue [in] An array of smart pointers to <link OdBcf::OdBcfVisualizationInfo, OdBcfVisualizationInfo> objects that represents the visualizaion information to be set.
    */
    void setVisualizationInfo(const OdBcfVisualizationInfoArray &visualizationInfoValue);

    /** \details
    Retrieves the topic folder's visualization information.
    \returns An array of smart pointers to <link OdBcf::OdBcfVisualizationInfo, OdBcfVisualizationInfo> objects that represents the visualization information.
    \remarks 
    The array returned by the method can be modified in the calling subroutine.
    */
    OdBcfVisualizationInfoArray& getVisualizationInfo();

    /** \details
    Retrieves the topic folder's visualization information.
    \returns An array of smart pointers to <link OdBcf::OdBcfVisualizationInfo, OdBcfVisualizationInfo> objects that represents the visualization information.
    \remarks 
    The array returned by the method can't be modified in the calling subroutine.
    */
    const OdBcfVisualizationInfoArray& getVisualizationInfo() const;

    /** \details
    Defines whether the topic folder's visualization information is not initialized.
    \returns true if the visualization information is not initialized; otherwise, the method returns false.
    */
    bool isVisualizationInfoUnset() const;


    //DOM-IGNORE-BEGIN
  protected:
    /**A smart pointer to the topic folder's <link OdBcf::OdBcfMarkup, markup> object.*/
    OdBcfMarkupPtr              m_pMarkup;
    /**An array of smart pointers to <link OdBcf::OdBcfVisualizationInfo, OdBcfVisualizationInfo> objects that represents the topic folder's visualization information.*/
    OdBcfVisualizationInfoArray m_visualizationInfo;
    //DOM-IGNORE-END
  };

  /** \details 
  A data type that represents a smart pointer to an <link OdBcf::OdBcfTopicFolder, OdBcfTopicFolder> object.
  */
  typedef OdSmartPtr<OdBcfTopicFolder> OdBcfTopicFolderPtr;

  /** \details
  A data type that represents an STD map of pairs consisting of OdGUID and a pointer to an <link OdBcf::OdBcfTopicFolder, OdBcfTopicFolder> objects.
  */
  typedef std::map<OdGUID, OdBcfTopicFolderPtr> OdBcfTopicFolderMap;

} //namespace OdBcf

#endif // _BFC_TOPIC_FOLDER_H
