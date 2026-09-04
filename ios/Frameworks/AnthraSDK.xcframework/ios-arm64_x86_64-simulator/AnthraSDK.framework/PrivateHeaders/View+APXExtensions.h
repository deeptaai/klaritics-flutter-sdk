//
//  View+APXExtensions.h
//  ApxorSDK
//
//  Created by Sravanthi on 01/09/23.
//  Copyright © 2023 Apxor. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@interface UIView (APXExtension)

- (void)applyGradientWithColors:(NSArray *)colors frame:(CGRect)frame startPoint:(CGPoint)start endPoint:(CGPoint)end maskPath:(UIBezierPath * _Nullable)maskPath;

@end

NS_ASSUME_NONNULL_END
