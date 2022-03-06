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

#ifndef _COLLADA_LIGHTTRAITS_INCLUDED_
#define _COLLADA_LIGHTTRAITS_INCLUDED_
#pragma once

#include "Gi/GiDrawable.h"
#include "DbBaseDatabase.h"
#include "Ge/GePoint3d.h"
#include "SmartPtr.h"
#include "Gi/GiLightTraitsData.h"

/** \details
  Provides a set of classes, structures and enumerations for exporting to a Collada file.
*/
namespace TD_COLLADA_EXPORT
{
  /** \details
    This class implements the distant light traits for exporting to a Collada file.
  */
  class ColladaDistantLightTraits : public OdGiDistantLightTraits
  {
    /** Pointer of the distant light traits. */
    OdGiDistantLightTraitsData* m_pData;
  public:

    /** \details
      Returns the intensity of the light source.

      \returns The intensity of the light source as a value of the double type.
    */
    virtual double intensity() const;

    /** \details
      Sets the distant light intensity.

      \param inten [in] The distant light intensity.
    */
    virtual void setIntensity( double inten );

    /** \details
      Returns the shadow parameters.

      \returns Shadow parameters as an OdGiShadowParameters instance.
    */
    virtual OdGiShadowParameters shadowParameters() const;

    /** \details
      Sets the shadow parameters.

      \param params [in] The shadow parameters.
    */
    virtual void setShadowParameters( const OdGiShadowParameters& params );

    /** \details
      Returns the distant light color.

      \returns The distant light color.
    */
    virtual OdCmEntityColor lightColor() const;

    /** \details
      Sets the distant light color.

      \param color [in] The distant light color.
    */
    virtual void setLightColor( const OdCmEntityColor& color );

    /** \details
      Checks whether the distant light is on or off.

      \returns The true value if the light is enabled, or false otherwise.
    */
    virtual bool isOn() const;
    
    /** \details
      Switches the distant light to the on or off.

      \param on [in] The distant light switch value.
    */
    virtual void setOn(bool on);

    /** \details
      Returns the distant light direction.

      \returns The distant light direction.
    */
    virtual OdGeVector3d lightDirection() const;

    /** \details
      Sets the distant light direction.

      \param vec [in] The distant light direction.
    */
    virtual void setLightDirection( const OdGeVector3d& vec );

    /** \details
      Checks whether the sun light is on.

      \returns The true value if this light is rendered as sunlight, or false otherwise.
    */
    virtual bool isSunlight() const;

    /** \details
      Switches the sun light to the on or off.
      
      \param isSunlight [in] The sun light value.
    */
    virtual void setIsSunlight( bool isSunlight );

    /** \details
      Sets the distant light physical intensity.
    
      \param fIntensity [in] The distant light physical intensity.
    */
    virtual void setPhysicalIntensity(double fIntensity);

    /** \details
      Returns the physical intensity of the distant light.

      \returns Physical intensity of the distant light as a value of the double type.
    */
    virtual double physicalIntensity() const;

    /** \details
      Sets color for the distant light lamp.

      \param color  [in]  RGB color value.
    */
    virtual void setLampColor(const OdGiColorRGB& color);

    /** \details
      Returns color of the light lamp.
    
      \returns The color of the distant light lamp as an OdGiColorRGB instance.
    */
    virtual OdGiColorRGB lampColor() const;

    /** \details
      Sets sky parameters for this distant light. Currently not implemented.

      \param params [in] The sky parameters for this distant light.
    */
    virtual void setSkyParameters(const OdGiSkyParameters &params);

    /** \details
      Returns sky parameters of this distant light. Currently not implemented.

      \returns The sky parameters of this distant light.
    */
    virtual void skyParameters(OdGiSkyParameters &params) const;

    /** \details
      Sets distant lights traits data.
    
      \param data [in] The distant lights traits data.
    */
    void setData(OdGiDistantLightTraitsData& data);
  };


  //-------------------------------------------------------------------------------------------------------------------

  /** \details
    This class implements the point light traits for exporting to a Collada file.
  */
  class ColladaPointLightTraits : public OdGiPointLightTraits
  {
    /** Pointer of the point light traits. */
    OdGiPointLightTraitsData* m_pData;
  public:

    /** \details
       Returns the point light intensity.

       \returns The point light intensity.
    */
    virtual double intensity() const;

    /** \details
       Sets the point light intensity.

       \param inten [in] The point light intensity.
    */
    virtual void setIntensity( double inten );

    /** \details
       Returns the shadow parameters.

       \returns The shadow parameters.
    */
    virtual OdGiShadowParameters shadowParameters() const;

    /** \details
       Sets the shadow parameters.

       \param params [in] The shadow parameters.
    */
    virtual void setShadowParameters( const OdGiShadowParameters& params );

    /** \details
       Returns the point light color.

       \returns The point light color.
    */
    virtual OdCmEntityColor lightColor() const;

    /** \details
       Sets the point light color.

       \param color [in] The point light color.
    */
    virtual void setLightColor( const OdCmEntityColor& color );

    /** \details
       Checks whether the point light is on or off.

       \returns The true value if the point light is enabled, or false otherwise.
    */
    virtual bool isOn() const;

    /** \details
       Switches the point light to on or off.

       \param on [in] The point light value.
    */
    virtual void setOn(bool on);

    /** \details
       Returns the point light position.

       \returns The point light position.
    */
    virtual OdGePoint3d position() const;

    /** \details
       Sets the point light position.

       \param pos [in] The point light position.
    */
    virtual void setPosition( const OdGePoint3d& pos );

    /** \details
      Returns the point light attenuation.

      \returns The point light attenuation.
    */
    virtual OdGiLightAttenuation lightAttenuation() const;


    /** \details
      Sets the point light attenuation.
    
      \param atten [in] The point light attenuation.
    */
    virtual void setAttenuation( const OdGiLightAttenuation& atten );

    /** \details
      Sets the physical intensity for this point light source in candela.
    
      \param fIntensity  [in]  Physical intensity of the point light in candela.
    */
    virtual void setPhysicalIntensity(double fIntensity);
    
    /** \details
      Returns the physical intensity for this point light source in candela.
    
      \returns Physical intensity of the point light as a value of the double type.
    */
    virtual double physicalIntensity() const;

    /** \details
      Sets the color for the point light lamp.
    
      \param color  [in]  RGB color value.
    */
    virtual void setLampColor(const OdGiColorRGB& color);

    /** \details
      Retrieves the color of the point light lamp.
    
      \returns Color of the point light lamp as an OdGiColorRGB instance.
    */
    virtual OdGiColorRGB lampColor() const;

    /** \details
      Sets whether this point should have an associated target grip displayed.
    
      \param bTarget  [in]  Flag that specifies whether to display a target grip for orienting the light.
    */
    virtual void setHasTarget(bool bTarget);

    /** \details
      Checks whether this point has an associated target grip displayed.
    
      \returns The true value if the light displays a target grip, or false otherwise.
    */
    virtual bool hasTarget() const;

    /** \details
      Sets target location of the light.
     
      \param loc  [in]  Location of the target. Must differ from the point light position.
    */
    virtual void setTargetLocation(const OdGePoint3d &loc);

    /** \details
      Returns target location of the light.
    
      \returns Target location of the light as an OdGePoint3d instance.
    */
    virtual OdGePoint3d targetLocation() const;

    /** \details
      Sets hemispherical distribution.
 
      \param loc  [in]  Hemispherical distribution.
    */
    virtual void setHemisphericalDistribution(bool bHemisphere);

    /** \details
      Returns whether hemispherical distribution is set.

      \returns The true value if hemispherical distribution is set, or false otherwise.
    */
    virtual bool hemisphericalDistribution() const;

    /** \details
      Sets trait data for point lights.
    
      \param data [in] The trait data for point lights.
    */
    void setData(OdGiPointLightTraitsData& data);
  };

  //-------------------------------------------------------------------------------------------------------------------

  /** \details
    This class implements the spotlight traits for exporting to a Collada file.
  */
  class ColladaSpotLightTraits : public OdGiSpotLightTraits
  {
    /** Pointer of spotlight traits. */
    OdGiSpotLightTraitsData* m_pData;
  public:
    /** \details
       Returns the spotlight intensity.

       \returns The spotlight intensity as a value of the double type.
    */
    virtual double intensity() const;

    /** \details
       Sets the spotlight intensity.

       \param inten [in] Spotlight intensity.
    */
    virtual void setIntensity( double inten );

    /** \details
       Returns the shadow parameters.

       \returns The shadow parameters.
    */
    virtual OdGiShadowParameters shadowParameters() const;

    /** \details
       Sets the shadow parameters.

       \param params [in] The shadow parameters.
    */
    virtual void setShadowParameters( const OdGiShadowParameters& params );

    /** \details
       Returns the spotlight color.

       \returns The spotlight color.
    */
    virtual OdCmEntityColor lightColor() const;

    /** \details
       Sets the spotlight color.

       \param color [in] The spotlight color.
    */
    virtual void setLightColor( const OdCmEntityColor& color );

    /** \details
       Checks whether the spotlight is on or off.

       \returns The true value if the spotlight is enabled, or false otherwise.
    */
    virtual bool isOn() const;

    /** \details
       Switches the spotlight to on or off.

       \param on [in] The point light switch value.
    */
    virtual void setOn(bool on);

    /** \details
      Returns the spotlight target point.

       \returns The spotlight target point.
    */
    virtual OdGePoint3d targetLocation() const;

    /** \details
       Sets the spotlight target point.

       \param loc [in] The spotlight target point.
    */
    virtual void setTargetLocation( const OdGePoint3d& loc );

    /** \details
      Returns the spotlight position.

       \returns The spotlight position.
    */
    virtual OdGePoint3d position() const;

    /** \details
       Sets the spotlight position.

       \param pos [in] The spotlight position.
    */
    virtual void setPosition( const OdGePoint3d& pos );

    /** \details
      Sets the spotlight attenuation.

      \param atten [in] The spotlight attenuation.
    */
    virtual void setAttenuation( const OdGiLightAttenuation& atten );

    /** \details
      Returns the spotlight attenuation.

      \returns The spotlight attenuation.
    */
    virtual OdGiLightAttenuation lightAttenuation() const;

    /** \details
      Returns the cone angle that produces the spotlight falloff.
    
      \returns Cone of the falloff as a value of the double type.
    */
    virtual double falloff() const;

    /** \details
      Sets the target location of the spotlight.
    
      \param hotspot  [in]  Hotspot cone angle, in radians. Defines the brightest part of the spotlight beam.
      \param falloff  [in]  Falloff angle, in radians. Defines the full cone of light.
    */
    virtual bool setHotspotAndFalloff( double hotspot, double falloff );

    /** \details
      Returns the hotspot.

      \returns The hotspot as a value of the double type.
    */
    virtual double hotspot() const;

    /** \details
      Sets the physical intensity for this spotlight source in candela.
    
      \param fIntensity  [in]  Physical intensity of the spotlight in candela.
    */
    virtual void setPhysicalIntensity(double fIntensity);

    /** \details
      Returns the physical intensity for this spotlight source in candela.
    
      \returns Physical intensity of the spotlight as a value of the double type.
    */
    virtual double physicalIntensity() const;

    /** \details
      Sets the color for the spotlight lamp.
    
      \param color  [in]  RGB color value.
    */
    virtual void setLampColor(const OdGiColorRGB& color);

    /** \details
      Returns the color of the spotlight lamp.
    
      \returns Color of the spotlight lamp as an OdGiColorRGB instance.
    */
    virtual OdGiColorRGB lampColor() const;

    /** \details
      Sets the trait data of the spotlights.
    
      \param data [in] The trait data of the spotlights.
    */
    void setData(OdGiSpotLightTraitsData& data);
  };
};

#endif // _COLLADA_LIGHTTRAITS_INCLUDED_

