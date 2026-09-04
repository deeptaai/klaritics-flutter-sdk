#import <Foundation/Foundation.h>
#import "CommonProtocols.h"
#import "ANTInfo.h"
#import "ANTEvent.h"

@interface ANTUser : ANTInfo
-(void) setUserAttribute:(id)value forKey:(NSString *)key;
-(NSDictionary*) userAttributes;

@end
