#ifndef ApxorPlugin_h
#define ApxorPlugin_h
#import "UIKit/UIKit.h"

@protocol AnthraPlugin <NSObject>

-(BOOL) initialize:(NSDictionary *)config;
-(BOOL) start;
-(BOOL) stop;

@end

#endif /* ApxorPlugin_h */
