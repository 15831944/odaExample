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




#ifndef _ODDBLAYERTABLETABLERECORD_INCLUDED
#define _ODDBLAYERTABLETABLERECORD_INCLUDED

#include "TD_PackPush.h"

#include "DbSymbolTableRecord.h"
#include "CmColor.h"
#include "DwgDeclareMembers.h"

class OdTvDbLayerTable;

/** \details
  <group OdTvDb_Classes>

  This class implements the layer record object, which represents a layer in the database. 
  This class inherits the base functionality of named records. 

  \sa
  TD_Db
    
  \sa
  <link db_layer_sample_table.html, Example of Working with the Layer Table Object>

  <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

  \sa
  <link db_layer.html, Working with Layers>

  OdTvDbLayerTable class
*/
class TOOLKIT_EXPORT OdTvDbLayerTableRecord : public OdTvDbSymbolTableRecord
{
public:
  DWGMAP_DECLARE_MEMBERS(OdTvDbLayerTableRecord);

  /** \details
    Builds an instance of the layer record object.
    
    \remarks
    Use the static pseudo-constructor instead it.
    See: <link db_layer_add_name.html, Adding and Naming Layers>
  */
  OdTvDbLayerTableRecord();

  typedef OdTvDbLayerTable TableType;


  /** \details
    Determines whether the layer record object is invisible and accessible for regenerating, 
    printing, selecting, and editing (DXF 70, bit 0x01) and returns True if the layer is frozen 
    or False if the layer is thawed.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::setIsFrozen() method
  */
  bool isFrozen() const;


  /** \details
    Sets the Freeze status as a Boolean value (DXF 70, bit 0x01). The initial value is False 
    (Thawed) by default.

    \param bStatus [in]  True - to freeze the layer, or False - to thaw the layer.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::isFrozen() method
  */
  void setIsFrozen( bool bStatus );


  /** \details
    Determines whether the layer record object is invisible (DXF 62, negative is off, positive 
    is on) and returns True if the layer is off (invisible) or False if the layer is on (visible).

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::setIsOff() method
  */
  bool isOff() const;


  /** \details
    Sets the On-Off status as a Boolean value (DXF 62). The initial value is False (Visible) by 
    default.

    \param bStatus [in]  True - to make the layer invisible (off), or False - to make the layer visible (on).

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::isOff() method
  */
  void setIsOff( bool bStatus );


  /** \details
    Returns true if and only if the layer is frozen in new viewports (DXF 70, bit 0x02).

    \sa
    OdTvDbLayerTableRecord::setVPDFLT() method
  */
  bool VPDFLT() const;


  /** \details
    Sets the Freeze status in new viewports for the layer as a Boolean value (DXF 70, bit 0x02).

    \param bStatus [in]  True - to specify the frozen layers for new viewports, or 
                False - to specify the thawed layers for new viewports.

    \sa
    OdTvDbLayerTableRecord::VPDFLT() method
  */
  void setVPDFLT( bool bStatus );


  /** \details
    Determines whether the layer record object is accessible for selecting and editing 
    (DXF 70, bit 0x04) and returns True if the layer is locked or False if the layer is editable.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::setIsLocked() method
  */
  bool isLocked() const;


  /** \details
    Sets the Lock status as a Boolean value (DXF 70, bit 0x04). The initial value is False 
    (Editable) by default.

    \param bStatus [in]  True - to lock the layer, or False - to unlock the layer.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::isLocked() method
  */
  void setIsLocked( bool bStatus );


  /** \details
    Determines whether the layer record object is accessible for printing (DXF 290) and 
    returns True if the layer is plottable or False if the layer is unplottable.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::setIsPlottable() method
  */
  bool isPlottable() const;


  /** \details
    Sets the Plot status as a Boolean value (DXF 290). The initial value is True (Plottable) 
    by default.

    \param bStatus [in]  True - to make the layer plottable, or False - to make the layer no plottable.

    \remarks
    Some layers cannot be set to plottable; e.g., the "Defpoints" Layer.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::isPlottable() method
  */
  void setIsPlottable( bool bStatus );


  /** \details
    Determines whether the layer record object is displayed for the host application and 
    returns True if the layer is hidden or False if the layer is shown.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::setIsHidden() method
  */
  bool isHidden() const;
  
  /** \details
    Determines whether the layer record object is displayed for the host application and 
    returns True if the layer is hidden or False if the layer is shown.

    \remarks
    The static isHidden() method checks the Hidden status for the specified layer ID.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::setIsHidden() method
  */
  static bool isHidden( const OdTvDbObjectId& idLayer );


  /** \details
    Sets the Hidden status as a Boolean value. The initial value is False (Shown) by default.

    \param bStatus [in]  True - to hide the layer, or False - to show the layer.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::isHidden() method
  */
  void setIsHidden( bool bStatus );


  /** \details
    Determines whether the layer record object is reconciled with another object and returns 
    True if the layer is reconciled, or False if the layer is not reconciled.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::setIsReconciled() method
  */
  bool isReconciled() const;
  
  /** \details
    Determines whether the layer record object is reconciled with another object and returns 
    True if the layer is reconciled, or False if the layer is not reconciled.

    \remarks
    The static isReconciled() method checks the Reconcile status for the specified layer ID.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::setIsReconciled() method
  */
  static bool isReconciled( const OdTvDbObjectId& idLayer );


  /** \details
    Sets the Reconcile status as a Boolean value.

    \param bStatus [in]  True - to set the Reconcile status, or False - to clear the Reconcile status.

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTableRecord::isReconciled() method
  */
  void setIsReconciled( bool bStatus = true );


  /** \details
    Returns the transparency for the layer record object (as XData). This transparency is 
    used when the Transparency property of an entity belonged to the layer is set to the byLayer 
    value. The actual transparency value can depend on the viewport in which the entity is rendered.

    \remarks
    The same layer can have different transparencies in different viewports. Therefore this method 
    is overdriven. The method without arguments returns the own transparency of the layer. 

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setTransparency() method
  */
  OdTvCmTransparency transparency() const;
  
  /** \details
    Returns the transparency for the layer record object (as XData). This transparency is 
    used when the Transparency property of an entity belonged to the layer is set to the byLayer 
    value. The actual transparency value can depend on the viewport in which the entity is rendered.

    \param idViewport  [in] Object ID of the viewport for which the transparency value should be obtained.
    \param pIsOverride [out] Pointer to the Boolean variable in which this method saves the result:  
                    True if it is the specific transparency previously specified for the viewport, or   
                    False if it is own transparency and the layer does not store a transparency for 
                    the specified viewport.

    \remarks
    The same layer can have different transparencies in different viewports. Therefore this method 
    is overdriven. The method with two arguments returns the specific transparency specified for 
    the viewport or own transparency if the specific transparency is not specified for the viewport.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setTransparency() method
  */
  OdTvCmTransparency transparency( const OdTvDbObjectId& idViewport, bool* pIsOverride = 0 ) const;


  /** \details
    Sets the transparency for the layer record object (as XData) and returns eOk if successful. 
    This transparency is used when the Transparency property of an entity belonged to this layer 
    is set to byLayer value. The initial value is byAlpha = 100% value (solid) by default. The same 
    entity can be rendered using different transparencies in different viewports.

    \param cmTransparency [in]  Reference to the transparency instance to be set as an Alpha-value in 
                       range 1 to 255.

    \remarks
    The same layer can have different transparencies in different viewports. Therefore this method 
    is overdriven. The method with one argument sets the own transparency of the layer. 

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    <link cm.html, Colors and Transparencies>

    OdTvDbLayerTableRecord::transparency() method
  */
  OdResult setTransparency( const OdTvCmTransparency& cmTransparency );
  
  /** \details
    Sets the transparency for the layer record object (as XData). 
    This transparency is used when the Transparency property of an entity belonged to this layer 
    is set to byLayer value. The initial value is byAlpha = 100% value (solid) by default. The same 
    entity can be rendered using different transparencies in different viewports.

    \param cmTransparency [in]  Reference to the transparency instance to be set as an Alpha-value in 
                       range 1 to 255.
    \param idViewport     [in] Object ID of the viewport in which the layer must have the specific transparency.

    \remarks
    The same layer can have different transparencies in different viewports. Therefore this method 
    is overdriven. The method with two arguments sets the specific transparency for the viewport.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    <link cm.html, Colors and Transparencies>

    OdTvDbLayerTableRecord::transparency() method
  */
  void setTransparency( const OdTvCmTransparency& cmTransparency, const OdTvDbObjectId& idViewport );


  /** \details
    Returns the color for the layer record object (DXF 62). This color is used when 
    the Color property of an entity belonged to the layer is set to byLayer value. The actual 
    color value can depend on the viewport in which the entity is rendered.

    \remarks
    The same layer can have different colors in different viewports. Therefore this method is 
    overdriven. The method without arguments returns the own color of the layer. 

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setColor() method
  */
  OdTvCmColor color() const;
  
  /** \details
    Returns the color for the layer record object (DXF 62). This color is used when 
    the Color property of an entity belonged to the layer is set to byLayer value. The actual 
    color value can depend on the viewport in which the entity is rendered.

    \param viewportId  [in] Object ID of the viewport for which the color value should be obtained.
    \param pIsOverride [out] Pointer to the Boolean variable in which this method saves the result:
                    True if it is the specific color previously specified for the viewport, or 
                    False if it is own color and the layer does not store a color for the 
                    specified viewport.

    \remarks
    The same layer can have different colors in different viewports. Therefore this method is 
    overdriven. The method with two arguments returns the specific color specified for the viewport or own color 
    if the specific color is not specified for the viewport.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setColor() method
  */
  OdTvCmColor color( const OdTvDbObjectId& viewportId, bool* pIsOverride = 0 ) const;


  /** \details
    Sets the color for the layer record object (DXF 62). This color is used when the 
    Color property of an entity belonged to this layer is set to byLayer value. The initial 
    value is Foreground (index 7) by default. The same entity can be rendered using different 
    colors in different viewports.

    \param cmColor    [in] Reference to the color instance to be set.

    \remarks
    The same layer can have different colors in different viewports. Therefore this method is 
    overdriven. The method with one argument sets the own color of the layer. 

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    <link cm.html, Colors and Transparencies>

    OdTvDbLayerTableRecord::color() method
  */
  void setColor( const OdTvCmColor& cmColor );
  
  /** \details
    Sets the color for the layer record object (DXF 62). This color is used when the 
    Color property of an entity belonged to this layer is set to byLayer value. The initial 
    value is Foreground (index 7) by default. The same entity can be rendered using different 
    colors in different viewports.

    \param cmColor    [in] Reference to the color instance to be set.
    \param idViewport [in] Object ID of the viewport in which the layer must have the specific color.

    \remarks
    The same layer can have different colors in different viewports. Therefore this method is 
    overdriven. The method with two arguments sets the specific color for the viewport.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    <link cm.html, Colors and Transparencies>

    OdTvDbLayerTableRecord::color() method
  */
  void setColor( const OdTvCmColor& cmColor, const OdTvDbObjectId& idViewport );

  
  /** \details
    Returns the color index for the layer record object (DXF 62). When the color method is 
    set to byColor, this method returns an equivalent color index.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setColorIndex() method
  */
  OdInt16 colorIndex() const;


  /** \details
    Sets the color index for the layer record object (DXF 62) as an Integer value. The initial   
    value is 7 (Foreground) by default.

    \param idxColor [in]  Color index in range 1 to 255.

    \remarks
    When the index outs the range 1 to 255, this method generates an exception. This method sets  
    the color method to byACI.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::colorIndex() method
  */
  void setColorIndex( OdInt16 idxColor );


  /** \details
    Returns the lineweight of the layer record object (DXF 370). This lineweight is used when  
    the Lineweight property of an entity belonged to this layer is set to ByLayer value. The actual 
    lineweight can depend on the viewport in which the entity is rendered.

    \remarks
    The same layer can have different lineweights in different viewports. Therefore this method is 
    overdriven. The method without arguments returns the own lineweight of the layer. 

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setLineWeight() method
  */
  OdDb::LineWeight lineWeight() const;
  
  /** \details
    Returns the lineweight of the layer record object (DXF 370). This lineweight is used when  
    the Lineweight property of an entity belonged to this layer is set to ByLayer value. The actual 
    lineweight can depend on the viewport in which the entity is rendered.

    \param idViewport  [in] Object ID of the viewport for which the lineweight should be obtained.
    \param pIsOverride [out] Pointer to the Boolean variable in which this method saves the result:
                    True if it is the specific lineweight previously specified for the viewport, or 
                    False if it is own lineweight and the layer does not store a lineweight for the 
                    specified viewport.

    \remarks
    The same layer can have different lineweights in different viewports. Therefore this method is 
    overdriven. The method with two arguments returns the specific lineweight specified for the 
    viewport or own lineweight if the specific lineweight is not specified for the viewport.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setLineWeight() method
  */
  OdDb::LineWeight lineWeight( const OdTvDbObjectId& idViewport, bool* pIsOverride = 0 ) const;


  /** \details
    Sets the lineweight for the layer record object (DXF 370). This lineweight is used when the 
    Lineweight property of an entity belonged to this layer is set to ByLayer value. The initial value 
    is kLnWtByLwDefault by default. The same entity can be rendered using different lineweights in 
    different viewports.

    \param kLnWtEnum  [in] Lineweight (value of the enumerator).

    \remarks
    The same layer can have different lineweights in different viewports. Therefore this method is 
    overdriven. The method with one argument sets the own lineweight of the layer. 

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::lineWeight() method
  */
  void setLineWeight( OdDb::LineWeight kLnWtEnum );
  
  /** \details
    Sets the lineweight for the layer record object (DXF 370). This lineweight is used when the 
    Lineweight property of an entity belonged to this layer is set to ByLayer value. The initial value 
    is kLnWtByLwDefault by default. The same entity can be rendered using different lineweights in 
    different viewports.

    \param kLnWtEnum  [in] Lineweight (value of the enumerator).
    \param idViewport [in] Object ID of the viewport in which the layer must have the specific lineweight.

    \remarks
    The same layer can have different lineweights in different viewports. Therefore this method is 
    overdriven. The method with two arguments sets the specific lineweight for the viewport.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::lineWeight() method
  */
  void setLineWeight( OdDb::LineWeight kLnWtEnum, const OdTvDbObjectId& idViewport );


  /** \details
    Returns the ID of the linetype record object associated with the layer record object 
    (DXF 6), or OdDb::kNULL when the layer is not associated with linetype. This linetype is 
    used when the Linetype property of an entity belonged to this layer is set to ByLayer value. 
    The actual linetype can depend on the viewport in which the entity is rendered.

    \remarks
    The same layer can have different linetypes in different viewports. Therefore this method is 
    overdriven. The method without arguments returns the own linetype of the layer. 

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setLinetypeObjectId() method
  */
  OdTvDbObjectId linetypeObjectId() const;
  
  /** \details
    Returns the ID of the linetype record object associated with the layer record object 
    (DXF 6), or OdDb::kNULL when the layer is not associated with linetype. This linetype is 
    used when the Linetype property of an entity belonged to this layer is set to ByLayer value. 
    The actual linetype can depend on the viewport in which the entity is rendered.

    \param idViewport  [in] Object ID of the viewport for which the linetype ID should be obtained.
    \param pIsOverride [out] Pointer to the Boolean variable in which this method saves the result:
                    True if it is the specific linetype previously specified for the viewport, or 
                    False if it is own linetype and the layer does not store a linetype for the 
                    specified viewport.

    \remarks
    The same layer can have different linetypes in different viewports. Therefore this method is 
    overdriven. The method with two arguments returns the specific linetype specified for the 
    viewport or own linetype if the specific linetype is not specified for the viewport.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setLinetypeObjectId() method
  */
  OdTvDbObjectId linetypeObjectId( const OdTvDbObjectId& idViewport, bool* pIsOverride = 0 ) const;


  /** \details
    Sets the ID of the linetype record object for the layer record object (DXF 6) as an 
    ObDbObjectId instance. This method associates layer and linetype. This linetype is used when 
    the Linetype property of an entity belonged to this layer is set to ByLayer value. The initial 
    value associates the layer with the "Continuous" linetype by default. The same entity can be 
    rendered using different linetypes in different viewports.

    \param idLinetype [in]  Object ID of the linetype record object to associate it with the layer,
                   or OdDb::kNull to disassociate the layer and linetype.

    \remarks
    The same layer can have different linetypes in different viewports. Therefore this method is 
    overdriven. The method with one argument sets the own linetype of the layer. 

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::linetypeObjectId() method
  */
  void setLinetypeObjectId( OdTvDbObjectId idLinetype );
  
  /** \details
    Sets the ID of the linetype record object for the layer record object (DXF 6) as an 
    ObDbObjectId instance. This method associates layer and linetype. This linetype is used when 
    the Linetype property of an entity belonged to this layer is set to ByLayer value. The initial 
    value associates the layer with the "Continuous" linetype by default. The same entity can be 
    rendered using different linetypes in different viewports.

    \param idLinetype [in]  Object ID of the linetype record object to associate it with the layer,
                   or OdDb::kNull to disassociate the layer and linetype.
    \param idViewport [in] Object ID of the viewport in which the layer must have the specific linetype.

    \remarks
    The same layer can have different linetypes in different viewports. Therefore this method is 
    overdriven. The method with two arguments sets the specific linetype for the viewport.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::linetypeObjectId() method
  */
  void setLinetypeObjectId( const OdTvDbObjectId& idLinetype, const OdTvDbObjectId& idViewport );


  /** \details
    Returns the ID of the material object associated with the layer record object (DXF 347) 
    or OdDb::kNULL when the layer is not associated with material. This material is used when 
    the Material property of an entity belonged to this layer is set to ByLayer value.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setMaterialId() method
  */
  OdTvDbObjectId materialId() const;


  /** \details
    Sets the ID of the material object for the layer record object (DXF 347) as an ObDbObjectId 
    instance. This method associates layer and material. The initial value associates the layer with 
    the "Global" material by default.

    \param idMaterial [in]  Object ID of the material object to associate it with the layer, 
                   or OdDb::kNull to disassociate the layer and material.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::materialId() method
  */
  void setMaterialId( OdTvDbObjectId idMaterial );


  /** \details
    Retuns the name of the plot style associated with the layer record object (DXF 390). This plot 
    style is used when the PlotStyle property of an entity belonged to this layer is set to ByLayer 
    value. The actual plot style can depend on the viewport in which the entity is rendered.

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::plotStyleNameId(), OdTvDbLayerTableRecord::setPlotStyleName() methods
  */
  OdString plotStyleName() const;
  
  /** \details
    Retuns the name of the plot style associated with the layer record object (DXF 390). This plot 
    style is used when the PlotStyle property of an entity belonged to this layer is set to ByLayer 
    value. The actual plot style can depend on the viewport in which the entity is rendered.


    \param idViewport  [in] Object ID of the viewport for which the plot style ID should be obtained.
    \param pIsOverride [out] Pointer to the Boolean variable in which this method saves the result:
                    True if it is the specific plot style previously specified for the viewport, or 
                    False if it is own plot style and the layer does not store a plot style for the 
                    specified viewport.

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::plotStyleNameId(), OdTvDbLayerTableRecord::setPlotStyleName() methods
  */
  OdString plotStyleName( const OdTvDbObjectId& idViewport, bool* pIsOverride = 0 ) const;


  /** \details
    Returns the ID of the plot style object associated with the layer record object (DXF 390) or 
    OdDb::kNULL when the layer is not associated with plot style. This plot style is used when the 
    PlotStyle property of an entity belonged to this layer is set to ByLayer value. The actual plot  
    style can depend on the viewport in which the entity is rendered.

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::plotStyleName(), OdTvDbLayerTableRecord::setPlotStyleName() methods
  */
  OdTvDbObjectId plotStyleNameId() const;
  
  /** \details
    Returns the ID of the plot style object associated with the layer record object (DXF 390) or 
    OdDb::kNULL when the layer is not associated with plot style. This plot style is used when the 
    PlotStyle property of an entity belonged to this layer is set to ByLayer value. The actual plot  
    style can depend on the viewport in which the entity is rendered.

    \param idViewport  [in] Object ID of the viewport for which the plot style ID should be obtained.
    \param pIsOverride [out] Pointer to the Boolean variable in which this method saves the result:
                    True if it is the specific plot style previously specified for the viewport, or 
                    False if it is own plot style and the layer does not store a plot style for the 
                    specified viewport.

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::plotStyleName(), OdTvDbLayerTableRecord::setPlotStyleName() methods
  */
  OdTvDbObjectId plotStyleNameId( const OdTvDbObjectId& idViewport, bool* pIsOverride = 0 ) const;


  /** \details
    Sets the name of the place holder object for the layer record object (DXF 390). This 
    method associates layer and plot style. The name is an OdString instance. This plot style 
    is used when the PlotStyle property of an entity belonged to this layer is set to ByLayer value. 
    The same entity can be rendered using different plot styles in different viewports.

    \param sPlotStyleName [in]  Plot style name as non-empty string.

    \remarks
    The same layer can have different plot styles in different viewports. Therefore this method is 
    overdriven. The method with one argument sets the own plot style of the layer using the plot style 
    name.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>
    
    <link OdTvDbPlaceHolder, OdTvDbPlaceHolder class>
    
    <link !!OVERLOADED_plotStyleName_OdDbLayerTableRecord, OdTvDbLayerTableRecord::plotStyleName()>, <link !!OVERLOADED_plotStyleNameId_OdDbLayerTableRecord, OdTvDbLayerTableRecord::plotStyleNameId()> methods
  */
  OdResult setPlotStyleName( const OdString& sPlotStyleName );
  
  /** \details
    Sets the name of the place holder object for the layer record object (DXF 390). This 
    method associates layer and plot style. The ID is an ObDbObjectId instance, the name is an 
    OdString instance. This plot style is used when the PlotStyle property of an entity belonged to 
    this layer is set to ByLayer value. The same entity can be rendered using different plot styles 
    in different viewports.

    \param sPlotStyleName [in]  Plot style name as non-empty string.
    \param idViewport     [in] Object ID of the viewport in which the layer must have the specific plot style.

    \remarks
    The same layer can have different plot styles in different viewports. Therefore this method is 
    overdriven. The method with two arguments sets the specific plot style for the viewport 
    using the plot style name.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>
    
    <link OdTvDbPlaceHolder, OdTvDbPlaceHolder class>
    
    <link !!OVERLOADED_plotStyleName_OdDbLayerTableRecord, OdTvDbLayerTableRecord::plotStyleName()>, <link !!OVERLOADED_plotStyleNameId_OdDbLayerTableRecord, OdTvDbLayerTableRecord::plotStyleNameId()> methods
  */
  void setPlotStyleName( const OdString& sPlotStyleName, const OdTvDbObjectId& idViewport);
  
  /** \details
    Sets the ID of the place holder object for the layer record object (DXF 390). This 
    method associates layer and plot style. The ID is an ObDbObjectId instance. 
    This plot style is used when the PlotStyle property of an entity belonged to 
    this layer is set to ByLayer value. The same entity can be rendered using different plot styles 
    in different viewports.
    
    \param idPlotStyle    [in] Object ID of the place holder object to associate it with the layer,
                       or OdDb::kNull to disassociate the layer and plot style.

    \remarks
    The same layer can have different plot styles in different viewports. Therefore this method is 
    overdriven. The method with one argument sets the own plot style of the layer using the plot style ID. 
    
    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>
    
    <link OdTvDbPlaceHolder, OdTvDbPlaceHolder class>
    
    <link !!OVERLOADED_plotStyleName_OdDbLayerTableRecord, OdTvDbLayerTableRecord::plotStyleName()>, <link !!OVERLOADED_plotStyleNameId_OdDbLayerTableRecord, OdTvDbLayerTableRecord::plotStyleNameId()> methods
  */
  void setPlotStyleName( OdTvDbObjectId idPlotStyle );
 

  /** \details
    Sets the ID of the place holder object for the layer record object (DXF 390). This 
    method associates layer and plot style. The ID is an ObDbObjectId instance. This plot style is used 
    when the PlotStyle property of an entity belonged to this layer is set to ByLayer value. 
    The same entity can be rendered using different plot styles in different viewports.

    \param idPlotStyle    [in] Object ID of the place holder object to associate it with the layer,
                       or OdDb::kNull to disassociate the layer and plot style.
    \param idViewport     [in] Object ID of the viewport in which the layer must have the specific plot style.

    \remarks
    The same layer can have different plot styles in different viewports. Therefore this method is 
    overdriven. The method with two arguments sets the specific plot style for the viewport 
    using the plot style ID.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>
    
    <link OdTvDbPlaceHolder, OdTvDbPlaceHolder class>
    
    <link !!OVERLOADED_plotStyleName_OdDbLayerTableRecord, OdTvDbLayerTableRecord::plotStyleName()>, <link !!OVERLOADED_plotStyleNameId_OdDbLayerTableRecord, OdTvDbLayerTableRecord::plotStyleNameId()> methods
  */
  void setPlotStyleName( const OdTvDbObjectId& idPlotStyle, const OdTvDbObjectId& idViewport);

  
  /** \details
    Returns the description for the layer record object.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::setDescription() method
  */
  OdString description() const;


  /** \details
    Sets the description for the layer record object as a String value up to 255 letters length. 
    The initial value is an empty string.

    \param sDescription [in]  Description as a String value.
    
    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_properties.html, Specific Properties of Layers>

    OdTvDbLayerTableRecord::description() method
  */
  void setDescription( const OdString& sDescription );


  /** \details
    Determines whether the layer record object is in-use when the generateUsageData() method  
    is called and returns True if the layer is in-use, or False if the layer is not use.
    
    \remarks
    Returns true when the generateUsageData() of the layer table object has not been called
    or this layer record object is not database resident.

    \sa
    <link db_layer_sample_record.html, Example of Working with the Layer Record Object>

    \sa
    <link db_layer_status.html, Status of Layers>

    OdTvDbLayerTable::generateUsageData() method
  */
  bool isInUse() const;


  virtual OdResult dwgInFields( OdTvDbDwgFiler* pFiler );

  virtual void dwgOutFields( OdTvDbDwgFiler* pFiler ) const;

  virtual OdResult dxfInFields( OdTvDbDxfFiler* pFiler );

  virtual void dxfOutFields( OdTvDbDxfFiler* pFiler ) const;

  virtual OdResult dxfInFields_R12( OdTvDbDxfFiler* pFiler );

  virtual void dxfOutFields_R12( OdTvDbDxfFiler* pFiler ) const;

  /*virtual OdResult subGetClassID( void* pClsid ) const;*/

  virtual OdResult subErase( bool erasing );

  virtual OdUInt32 subSetAttributes( OdGiDrawableTraits* pTraits ) const;

  virtual bool subWorldDraw( OdGiWorldDraw* pWd ) const;

  virtual void subViewportDraw( OdGiViewportDraw* pVd ) const;

  OdGiDrawable* drawable();

  void removeAllOverrides();

  void removeColorOverride( const OdTvDbObjectId& idViewport );

  void removeLinetypeOverride( const OdTvDbObjectId& idViewport );

  void removeLineWeightOverride( const OdTvDbObjectId& idViewport );

  void removePlotStyleOverride( const OdTvDbObjectId& idViewport );

  void removeTransparencyOverride( const OdTvDbObjectId& idViewport );

  void removeViewportOverrides( const OdTvDbObjectId& idViewport );

  bool hasOverrides( const OdTvDbObjectId& idViewport ) const;

  bool hasAnyOverrides() const;
};

/** \details
  The typified smart pointer for the layer record object. This template class is 
  specialization of the OdSmartPtr class for the OdTvDbLayerTableRecord object.

  \sa
  <link smart_pointers.html, Working with Smart Pointers>
*/
typedef OdSmartPtr<OdTvDbLayerTableRecord> OdTvDbLayerTableRecordPtr;

#include "TD_PackPop.h"

#endif // _ODDBLAYERTABLETABLERECORD_INCLUDED

