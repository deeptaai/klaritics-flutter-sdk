#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "CommonProtocols.h"
#import "ANTEvent.h"
#import "ANTChunk.h"
#import "ANTSession.h"
#import "ANTUser.h"
#import "ANTChunkMetaInfo.h"
#import "ANTAppInfo.h"
#import "ANTDeviceInfo.h"
#import "ANTSDKInfo.h"
#import "ANTBidiDelegate.h"


/**
 *  Holds Core Plugin components
 *  Holds Configuration Manager, APXDataHandler, APXEventHandler
 *  SPOC for all modules - All API are expected to be threadsafe
 */
NS_ASSUME_NONNULL_BEGIN

@interface ANTController : NSObject<ANTEventListener>

@property (readwrite) BOOL actionInProgress;
@property (readwrite) BOOL actionBeingShownInApp;
@property (readonly) BOOL enableSDK;
@property (readonly) BOOL isSDKInitCalled;
@property (readonly) BOOL isSDKInitCompleted;
@property (readonly) NSString * _Nonnull applicationIdentifier;

// Convinience methods (removes unnecessary computations)
@property (readonly) ANTSession * _Nonnull session;
@property (readonly) ANTUser * _Nonnull user;
@property (readonly) ANTAppInfo * _Nonnull appInfo;
@property (readonly) ANTDeviceInfo * _Nonnull deviceInfo;
@property (readonly) ANTSDKInfo * _Nonnull sdkInfo;


#pragma mark -  Lifecycle methods
+ (instancetype _Nonnull) sharedController;
-(void) initialize;
-(void) initializeWithAnthraID:(NSString *)appId;

#pragma mark - Public APIS
-(void) setUserIdentifier:(NSString * __nonnull)identifier;
-(void) logScreenWithName:(NSString *)title;
-(void) logClientEventWithName:(NSString * __nonnull)eventName info:(NSDictionary *)info;
-(void) logClientEventWithName:(NSString * __nonnull)eventName info:(NSDictionary *)info shouldFlatten:(BOOL)flatten;
-(void) logInternalEventWithName:(NSString * __nonnull)eventName info:(NSDictionary * __nullable)info;
-(void) logAppEventWithName:(NSString * __nonnull)eventName info:(NSDictionary *)info;
-(void) logAppEventWithName:(NSString * __nonnull)eventName info:(NSDictionary *)info isAggregate:(BOOL)isAggregate;
-(void) logAppEventWithName:(NSString * __nonnull)eventName info:(NSDictionary *)info shouldFlatten:(BOOL)flatten isAggregate:(BOOL)isAggregate;
-(void) logDeviceToken:(id __nonnull)token;
-(void) setUserCustomInfo:(NSDictionary * __nonnull)userCustomInfo;
-(void) setSessionCustomInfo:(NSDictionary*_Nonnull)sessionCustomInfo;
-(void) reportCustomError:(NSError*_Nonnull)error withInfo:(NSDictionary* __nullable)info;
-(NSString*) getDeviceID;
-(NSString*) getHardwareModel;
-(void)handleDeeplinkWithURL:(NSURL *_Nonnull) url;
-(void) screenRefreshed;

#pragma mark - Cordova methods
-(void) markAsCordova;
-(BOOL) isCordova;

#pragma mark - ReactNative methods
-(void) markAsReactNative;
-(BOOL) isReactNative;

#pragma mark - SwiftUI methods
-(void) markAsSwiftUI;
-(BOOL) isSwiftUI;

#pragma mark - Flutter methods
-(void) markAsFlutter;
-(BOOL) isFlutter;
-(id<ANTBidiDelegate>) getBidiEventsBusWithKey:(NSString *) name;
-(void) registerForBidiEventsBus:(id<ANTBidiDelegate>) bus WithKey:(NSString *) key ;

#pragma mark - Test device methods
- (void)setTestDeviceStatus:(BOOL)status;
- (BOOL)isTestDevice;

#pragma mark - Timer methods
- (void) registerForTimerNotificationWithInterval:(double)interval closure:(void (^)(NSTimer * _Nonnull timer))block;

#pragma mark - Event Handling methods
-(void) dispatchEvent:(ANTEvent *_Nonnull)event;
-(void) registerForEventWithType:(ANTEventType) event listener:(id<ANTEventListener> _Nonnull) listener;
-(void) deregisterForEventWithType:(ANTEventType) event listener:(id<ANTEventListener> _Nonnull) listener;
-(void) registerIdentifer:(NSString*_Nonnull) identifier withListener:(id<ANTEventListener> _Nonnull) listener;
-(void) deRegisterIdentifer:(NSString*_Nonnull) identifier withListener:(id<ANTEventListener>_Nonnull) listener;
-(void) executeAfterDelay:(NSTimeInterval) delayInSeconds block:(dispatch_block_t _Nonnull ) block;
-(ANTTime) currentSDKTimeInMillis;
- (NSArray *) filterEventsProps:(NSArray *)events;

#pragma mark - Session handling methods
-(void) startSessionWithLaunchType:(NSString*_Nonnull) launchType;
-(void) updateChunkEndTime;
-(NSInteger) getLifetimeSessionCount;
-(void) incrementLifetimeSessionCount;

#pragma mark - Retention day methods
-(NSInteger) getRetentionDay;

#pragma mark - User info sending method
-(void) sendUserInfo;
- (NSDictionary *)filterUserProperties:(NSDictionary *)props;

#pragma mark - stop conditions
- (NSDictionary *)retrieveNudgeOrSurveyShownDetails:(NSString *)configId;
- (void)persistNudgeOrSurveyShownDetails:(NSDictionary *)details forConfigId: (NSString *)configId;
- (void)addKeyValueForConfigId:(NSString *)configId forKey:(NSString *)key withValue:(id)value;
- (id)retrieveValueForConfigId:(NSString *)configId forKey:(NSString *)key;
- (void)removeStopConditionsForConfigId:(NSString*)configId;

#pragma mark - stories
- (void) insertDataIntoStories:(NSDictionary *)data;
- (void) removeStoriesConfigForConfigId:(NSString *)configId;
#pragma mark - get screen name
- (NSString *) getCurrentScreenName;
- (NSString *) getCurrentCustomScreenName;

#pragma mark - Networking proxy methods
-(void) getDataFromURLPath:(NSString*_Nonnull)configURL completionHandler:(void (^)(NSData *, NSURLResponse *, NSError *))block;
-(void) postDataToURL:(NSString*) configURL withRequestBodyDictionary:(NSDictionary*)requestData headerFields:(NSDictionary* _Nullable)headers completionHandler:(void (^)(NSData *, NSURLResponse *, NSError *))completionHandler;
-(void) makeDeleteRequestToURLPath:(NSString*_Nonnull)configURL headerFields:(NSDictionary* _Nullable)headers completionHandler:(void (^)(NSData *, NSURLResponse *, NSError *))block;

-(void) getDataFromURL:(NSString*_Nonnull)configURL completionHandler:(void (^)(NSData *, NSURLResponse *, NSError *))block;

#pragma mark - Datahandler proxy methods
-(void) setAndSaveEnableSDKState:(BOOL) status;
-(void) saveUserInfo;
-(void) saveSessionInfoWithIndentifier:(NSString *_Nonnull) sessionId;
-(void) saveEvent:(ANTEvent *_Nonnull)event;
-(void) saveLifetimeEvent:(ANTEvent *_Nonnull)event;
-(void) saveFrequencyInfo:(NSDictionary *)info withIdentifier:(NSString *)identifier;
-(NSDictionary *_Nullable) getLifetimeCountForEvents:(NSArray<NSString *>*)events;
-(void)saveConditionConfig:(NSDictionary *)info withIdentifier:(NSString *)identifier;
-(NSDictionary *)retrieveConditionConfigWithIdentifier:(NSString *)identifier;
-(NSDictionary *)retrieveConditionConfig;
- (void)removeConditionConfigWithIdentifier:(NSString *)identifier;
-(void)persistConditionConfig:(NSDictionary *)config;
-(NSInteger) getLifetimeCountForEventWithName:(NSString *)eventName;
-(void) processAggregateEventWithEvent:(ANTEvent*)event;
-(NSArray*_Nonnull) retrieveAggregateEventsWithSessionIdentifier:(NSString*)identifier;
-(void) saveEvent:(ANTEvent *_Nonnull)event inSession:(NSString *_Nonnull) sessionId;
-(NSString *_Nonnull) getSessionId;
-(void) markFatalAndUpdateDuration:(NSDate *_Nullable) duration inSession:(NSString *_Nonnull) identifier;
-(void) saveChunkMetaInfo:(ANTChunkMetaInfo*_Nonnull) event;
-(void) updateChunkMetaInfo:(ANTChunkMetaInfo*_Nonnull) event;
-(void) updateChunkMetaStatus:(ANTChunk*_Nonnull) event;
-(NSArray*_Nonnull) getEventsBetween:(NSUInteger) start endInterval:(NSUInteger) end withIdentifier:(NSString*_Nonnull) identifier eventType:(NSString*_Nullable) eventType;
-(NSUInteger) numberOfEventsWithIdentifier:(NSString*_Nonnull) sessionIdentifier;
-(void) deleteChunkMetaInfo:(ANTChunk*_Nonnull) event;
-(void) deleteAggregateEventsWithSessionId:(NSString*)sessionId;
-(NSArray*_Nonnull) retrieveChunkMetaInfo;
-(NSArray*_Nonnull) getSessions;
-(void) deleteSession:(NSString*_Nonnull) sessionIdentifier;
-(ANTUser*_Nonnull) retrieveUser;
-(ANTSession *_Nonnull) retrieveSessionInfoWithIdentifier:(NSString *_Nonnull) identifier;
-(void) deleteItemAtPath:(NSString *_Nonnull) path;
-(NSDictionary *_Nullable) retrieveFrequencyConfigWithIdentifier:(NSString *)identifier;

-(void) retrieveImageAtPath:(NSString*_Nonnull)path persistFileName:(NSString *_Nonnull)fileName directoryName:(NSString *) directoryName withCompletionHandler:(void(^)(NSData *)) completionHandler;
-(void) removeDirectoryForConfigId:(NSString*) configId;
- (void) removeItemAtFilePath:(NSString *)path;
- (NSArray *)retrieveDataFromStoriesWithTableName:(NSString *)tableName;
- (id)getProperty:(NSString *)property FromEventWithName:(NSString *)eventName;

#pragma mark - event queue methods
- (BOOL)checkEventForEventQueue:(ANTEvent *)event;
- (void)addEventToEventQueue:(ANTEvent *)event;
- (void)dispatchEventFromEventQueue;

@end

NS_ASSUME_NONNULL_END
