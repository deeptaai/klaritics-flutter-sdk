//
//  APXFlutterBidiEventBus.h
//  ApxorSDK
//
//  Created by Ramcharan  on 20/07/23.
//  Copyright © 2023 Apxor. All rights reserved.
//

#ifndef APXBidiEvents_h
#define APXBidiEvents_h

#import "AnthraSDK/ANTBidiDelegate.h"

@interface ANTFlutterBidiEventBus: NSObject <ANTBidiDelegate,ANTEventListener>

@end

#endif /* APXBidiEvents_h */
