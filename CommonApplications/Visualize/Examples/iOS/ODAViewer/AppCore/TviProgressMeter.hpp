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

#ifndef TviProgressMeter_hpp
#define TviProgressMeter_hpp

#include <stdio.h>

#import <UIKit/UIKit.h>
#include "Tv.h"
#import "../AppUITools/TviProgressControl.h"

class TviProgressMeter : public OdTvHostAppProgressMeter
{
public:
    TviProgressMeter(TviProgressControl *progressControl);
    virtual ~TviProgressMeter();
    
    /** \details
     Notification function called to initialize this ProgressMeter object.
     \param displayString [in]  String to be displayed.
     */
    virtual void start(const OdString& displayString = OdString::kEmpty);
    
    /** \details
     Notification function called to terminate this ProgressMeter object.
     */
    virtual void stop();
    
    /** \details
     Notification function called to increment this ProgressMeter object.
     
     \remarks
     The completion percentage may be calculated by dividing the number of times
     this function is called by the value set by setLimit.
     
     \remarks
     Throwing an exception indicates that the operation associated with this ProgressMeter object
     should be halted.
     */
    virtual void meterProgress();
    
    /** \details
     Notification function called to specify the maximum number of times this
     ProgressMeter object will be incremented.
     
     \param max [in]  Maximum meterProgress calls.
     */
    virtual void setLimit(int max);
    
protected:
    // progress bar
    TviProgressControl *m_pProgressControl;
    
    /** \details
     Limit
     */
    int                   m_nProgressLimit;
    
    /** \details
     Last value, that was set to the progress bar
     */
    int                   m_meterLastValue;
    
    /** \details
     Current progress pos
     */
    int                   m_nProgressPos;
};


#endif /* TviProgressMeter_hpp */
