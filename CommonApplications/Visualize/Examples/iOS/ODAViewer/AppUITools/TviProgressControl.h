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

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef NSString*(^StringGenerationBlock)(CGFloat progress);
typedef NSAttributedString*(^AttributedStringGenerationBlock)(CGFloat progress);

/** Class that represents CircleProgressBar itself.
 
 CircleProgressBar can be initialized programmatically or using InterfaceBuilder.
 
 To change progress in CircleProgressBar just use:
 
 [ setProgress:(CGFloat) animated:(BOOL)animated];
 
 Interface provides ability to customize each element of CircleProgressBar independently;
 
 */
IB_DESIGNABLE
@interface TviProgressControl : UIView

/// @brief Width of Progress Bar
@property (nonatomic) IBInspectable CGFloat progressBarWidth;
/// @brief Progress color in Progress Bar
@property (nonatomic) IBInspectable UIColor *progressBarProgressColor;
/// @brief Track color in Progress Bar
@property (nonatomic) IBInspectable UIColor *progressBarTrackColor;
/// @brief Start Angle
@property (nonatomic) IBInspectable CGFloat startAngle;

/// @brief Whether HintView should be shown or not
@property (nonatomic) IBInspectable BOOL hintHidden;
/// @brief Inner spacing between Progress Bar and Hint View
@property (nonatomic) IBInspectable CGFloat hintViewSpacing;
/// @brief Hint View Background Color
@property (nonatomic) IBInspectable UIColor *hintViewBackgroundColor;
/// @brief Hint View Text Font
@property (nonatomic) IBInspectable UIFont *hintTextFont;
/// @brief Hint View Text Color
@property (nonatomic) IBInspectable UIColor *hintTextColor;

/** Used to set block that generates NSString according to progress, to show it in Hint View
 
 @param StringGenerationBlock block with CGFloat progress parameter, that returns NSString*
 */
- (void)setHintTextGenerationBlock:(StringGenerationBlock)generationBlock;

/** Used to set block that generates NSAttributedString according to progress, to show it in Hint View
 
 @param AttributedStringGenerationBlock block with CGFloat progress parameter, that returns NSAttributedString*
 */
- (void)setHintAttributedGenerationBlock:(AttributedStringGenerationBlock)generationBlock;

/// @brief Current ProgressBar's progress (Read-Only)
/// To change ProgressBar's progress use setProgress:animated:
@property (nonatomic, readonly) IBInspectable CGFloat progress;

/// @brief Indicates of there is ongoing animation
@property (nonatomic, readonly) BOOL isAnimating;

/** Used to set progress with animation or without
 
 @param progress progress to be set
 @param animated should control animate progress change or not
 */
- (void)setProgress:(CGFloat)progress animated:(BOOL)animated;

/** Used to set progress with animation and custom duration
 
 @param progress progress to be set
 @param animated should control animate progress change or not
 @param duration animation duration (default is 0.2f)
 */
- (void)setProgress:(CGFloat)progress animated:(BOOL)animated duration:(CGFloat)duration;

/// Used to stop ongoing animation
- (void)stopAnimation;

@end

NS_ASSUME_NONNULL_END
