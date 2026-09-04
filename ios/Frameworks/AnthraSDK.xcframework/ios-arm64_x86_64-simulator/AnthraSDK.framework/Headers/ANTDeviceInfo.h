#import <Foundation/Foundation.h>
#import "ANTInfo.h"

@interface ANTDeviceInfo : ANTInfo

- (NSString*)getDeviceID;
- (NSString*)getHardwareModel;
- (void)logDeviceToken:(NSString *)token;

@end
