#import <Foundation/Foundation.h>
#import <os/log.h>

typedef NS_ENUM(NSUInteger, ANTLOGLEVEL) {
    ANT_INFO = 0,
    ANT_DEBUG = 1,
    ANT_WARN = 2,
    ANT_ERROR = 3,
    ANT_NONE = 9999
};

extern ANTLOGLEVEL LOG_LEVEL;

#define PrintThread1 \
do { \
    if ([NSThread isMainThread]) { \
        os_log(OS_LOG_DEFAULT, "***MainThread*** %{public}s-%{public}u", __func__, __LINE__); \
    } else { \
        os_log(OS_LOG_DEFAULT, "+++BGThread queue:%{public}s+++ %{public}s,%{public}u", \
            dispatch_queue_get_label(DISPATCH_CURRENT_QUEUE_LABEL), \
            __func__, __LINE__); \
    } \
} while (0)


#define Loginfo(x) \
do { \
    os_log(OS_LOG_DEFAULT, "<ANT INFO> %{public}s %{public}s:%{public}d", \
           [[x description] UTF8String], __FUNCTION__, __LINE__); \
} while (0)


#define Logdebug(x) \
do { \
    if (LOG_LEVEL <= ANT_DEBUG) \
        os_log(OS_LOG_DEFAULT, "<ANT DEBUG> %{public}s %{public}s:%{public}d", \
               [[x description] UTF8String], __FUNCTION__, __LINE__); \
} while (0)


#define Logwarn(x) \
do { \
    if (LOG_LEVEL <= ANT_WARN) \
        os_log(OS_LOG_DEFAULT, "<ANT WARN> %{public}s %{public}s:%{public}d", \
               [[x description] UTF8String], __FUNCTION__, __LINE__); \
} while (0)


#define Logerr(x) \
do { \
    if (LOG_LEVEL <= ANT_ERROR) \
        os_log(OS_LOG_DEFAULT, "<ANT ERROR> %{public}s %{public}s:%{public}d", \
               [[x description] UTF8String], __FUNCTION__, __LINE__); \
} while (0)


@interface ANTLogger: NSObject
+(void) setLogLevel:(ANTLOGLEVEL) logLevel;
@end
