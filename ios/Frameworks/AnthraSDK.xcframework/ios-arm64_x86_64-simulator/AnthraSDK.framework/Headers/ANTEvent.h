#import "ANTInfo.h"
#import "APXTypes.h"

typedef NS_ENUM(NSUInteger, ANTEventType) {
    ANTEventTypeSystem = 0,
    ANTEventTypeCENavigation = 1,
    ANTEventTypeNavigation = 2,
    ANTEventTypeUserInteraction = 3,
    ANTEventTypeApp = 4,
    ANTEventTypeClient = 5,
    ANTEventTypeAggregate = 6,
    ANTEventTypePush = 7,
    APXEventTypeInApp = 8,
    ANTEventTypeInline = 9,
    ANTEventTypeNudge = 10,
    ANTEventTypeInlineText = 11,
    ANTEventTypeInlineCoachmark = 12,
    APXEventTypeWalkthrough = 13,
    APXEventTypeScreenshot = 14,
    APXEventTypeSurvey = 15,
    APXEventTypeUser = 16,
    ANTEventTypeSession = 17,
    ANTEventTypeChunk = 18,
    APXEventTypeCustomError = 19,
    APXEventTypeCrash = 20,
    ANTEventTypeInternal = 21,
    APXEventTypeGoalsSatisfied = 22,
    APXEventTypeUserPropertiesSatisfied = 23,
    APXEventTypeUserPropertiesChanged = 24,
    APXEventTypeImmersive = 25,
    APXEventTypeOnBoarding = 26,
};

#define APXENUMSTRING(x)   [APXEvent typeToString(x)]

@class ANTEvent;

@protocol ANTEventListener <NSObject>

-(void) onEvent: (ANTEvent*) event;

@end

@protocol APXEventSource <NSObject>

-(void) logEvent:(NSString *) eventName info:(NSDictionary *) info time:(ANTTime) time;

@end


@interface ANTEvent : ANTInfo 

+ (NSString*)stringFromType:(ANTEventType)type;
+ (ANTEventType)typeFromString:(NSString*)string;

- (instancetype)initWithType:(ANTEventType)type;
- (ANTTime)createdTime;
- (void)setCreatedTime:(ANTTime)time;
- (ANTEventType)eventType;
- (void)setEventType:(ANTEventType)type;

@end


@interface ANTSessionEvent : ANTEvent

@end

@interface ANTChunkEvent : ANTEvent

@end

@interface APXSurveyEvent : ANTEvent

@end

@interface APXImmersiveEvent : ANTEvent

@end

@interface APXInlineEvent : ANTEvent

@end

@interface APXInAppEvent : ANTEvent

@end

@interface APXNudgeEvent : ANTEvent

@end

@interface ANTClientEvent : ANTEvent

@end

@interface ANTInternalEvent : ANTEvent

@end

@interface ANTAggregateEvent : ANTEvent

@end
