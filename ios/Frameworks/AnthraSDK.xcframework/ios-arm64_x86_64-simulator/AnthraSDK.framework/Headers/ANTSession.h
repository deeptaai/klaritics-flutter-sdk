#ifndef APXSession_h
#define APXSession_h

#import "CommonProtocols.h"
#import "ANTEvent.h"
#import "ANTInfo.h"

@interface ANTSession : ANTInfo <ANTEventListener>

-(instancetype) initWithLaunchType:(NSString*) launchType;

-(void) stopSession;
-(void) setSessionAttribute:(id)value forKey:(NSString *)key;
-(NSDictionary*) sessionAttributes;
-(void) markSessionAsFatal;
-(void) updateDuration:(NSDate *) date;
-(void) updateEndTime;

@end

#endif /* APXSession_h */
