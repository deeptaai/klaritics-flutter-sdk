#import <Foundation/Foundation.h>
#import "CommonProtocols.h"
#import "ANTEvent.h"


@interface ANTNavigationEvent : ANTEvent

-(instancetype) initWithViewControllerId:(NSString *) viewAPXControllerId;
-(instancetype) initWithNavigationId:(NSString *) navId andName:(NSString *) screenName;

@end

@interface APXCENavEvent : ANTEvent

-(instancetype) initWithViewControllerId:(NSString *) viewAPXControllerId;
-(instancetype) initWithNavigationId:(NSString *) navId andName:(NSString *) screenName;

@end
