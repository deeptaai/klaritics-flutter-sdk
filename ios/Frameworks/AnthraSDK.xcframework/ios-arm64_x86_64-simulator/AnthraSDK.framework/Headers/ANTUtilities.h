#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <sys/utsname.h>
#import "APXTypes.h"
#import "APXView.h"

#define APXPathPrefix @"APX"
#define APXNativeIDPrefix @"[apx_"
#define APXNativeIDSuffix @"_apx]"

@class UIApplication;
@interface ANTUtilities : NSObject

+(void) initializeDateFormatter;
+(ANTTime) installationDate;
+(BOOL) isFirstSession;
+(NSString* _Nullable) deviceName;

+(NSDictionary*_Nonnull) addTwoDictionaries:(NSDictionary*_Nonnull) one and: (NSDictionary*_Nonnull) two;
+(NSString*_Nullable) getStringFromDate:(NSDate *_Nullable)date;
+(NSDate*_Nullable)getDateFromString:(NSString *_Nonnull)dateString;
+(NSDate*_Nullable) dateFromAPXDateString:(NSString*_Nonnull) dateString;
+(NSString*_Nullable) dateAPXStringFromNSDate:(NSDate*_Nonnull) date;
+(ANTTime) timeIntervalFromAPXDateString:(NSString*_Nonnull) dateString;
+(NSString*_Nullable) dateAPXStringFromTimeInterval:(ANTTime) timeInterval;
+(NSString*_Nullable) getHashForModule:(NSString*_Nonnull) module;
+(void) saveHash:(NSString*_Nonnull) value ForModule:(NSString*_Nonnull) module;
+(BOOL) saveConfig:(NSData*_Nonnull) config atPath:(NSString*_Nonnull) path;
+(NSDictionary *_Nullable) readConfigAtRelativePath:(NSString*_Nonnull)filePath;
+(NSDictionary *_Nullable) readConfig:(NSString*_Nonnull) filePath;

#pragma mark - JSON Utility Methods
+(NSData*_Nullable) jsonDataFromNSDictionary:(NSDictionary*_Nonnull) dictionary;
+(NSDictionary*_Nullable) dictionaryFromNSData:(NSData*_Nonnull) data;
+(NSDictionary*_Nullable) dictionaryFromJsonString:(NSString*_Nonnull) string;
+(NSString*_Nullable) jsonStringFromNSDictionary:(NSDictionary*_Nonnull) dictionary;
+(NSArray*_Nullable) arrayFromJsonString:(NSString*_Nonnull) string;
+(NSString*_Nullable) jsonStringFromNSArray:(NSArray*_Nonnull) array;

#pragma mark - object utils
+ (BOOL)isValidObject:(id)obj;

#pragma mark - vc methods
+ (UIViewController *_Nullable)topViewController:(UIViewController *_Nonnull)rootViewController;

#pragma mark - text utils
+ (BOOL)isNumericString:(NSString*_Nonnull)aString;
+ (BOOL)isValidString:(NSString*_Nullable)aString;
+ (BOOL)isInvalidString:(NSString*_Nullable)aString;
+ (UIFont *_Nullable)fontWithName:(NSString *_Nullable)name size:(CGFloat)size;
+ (UIFont *_Nullable)fontWithName:(NSString *_Nullable)name size:(CGFloat)size style:(NSString *_Nonnull)style;
+ (UIFont *_Nullable)fontWithName:(NSString *_Nullable)name size:(CGFloat)size style:(NSString *_Nonnull)style weight:(NSString *_Nonnull)weight;
+ (NSTextAlignment)alignmentForString:(NSString *_Nonnull)alignment;

#pragma mark - adaptive text utils
+ (UIFont *_Nullable)fontWithName:(NSString *_Nullable)name size:(CGFloat)size adaptiveText:(BOOL)adaptiveText;
+ (UIFont *_Nullable)fontWithName:(NSString *_Nullable)name size:(CGFloat)size style:(NSString *_Nonnull)style adaptiveText:(BOOL)adaptiveText;
+ (UIFont *_Nullable)fontWithName:(NSString *_Nullable)name size:(CGFloat)size style:(NSString *_Nonnull)style weight:(NSString *_Nonnull)weight adaptiveText:(BOOL)adaptiveText;

#pragma mark - dictionary utils

+ (BOOL)isValidDictionary:(NSDictionary*)aDict;
+ (BOOL)isInvalidDictionary:(NSDictionary*)aDict;
+ (NSDictionary * __nullable)dictionaryByRemovingNullsAndEmptyValues:(NSDictionary * __nullable) inputDict;

#pragma mark - Window utils
+(UIWindow* _Nullable)keyWindow;

#pragma mark - View utils
+ (NSArray *_Nonnull)ignoredViews;
+ (UIView *_Nullable)getViewWithIdentifier:(NSString *)viewIdentifier searchType:(NSString *)searchType;
+ (UIView *_Nullable)getViewWithIdentifier:(NSString *)viewIdentifier searchType:(NSString *)searchType inView:(UIView *)superView;
+ (void)constructCustomViewHierarchyForView:(UIView *_Nonnull)parentView withRoot:(APXView *_Nonnull)root ignoringViews:(NSArray *_Nonnull)ignoreViews withAuxiliaryTableView:(UITableView *_Nullable)tableView andCollectionView:(UICollectionView *_Nullable)collectionView;
+ (void)logAPXViewWithRoot:(APXView *)root separator:(NSMutableString *)separator;
+ (void)logViewWithRoot:(UIView *)view separator:(NSMutableString *)separator;
+ (void)sortSubViewsWithRootView:(APXView *)root;
+ (BOOL)isViewRect:(CGRect)viewRect insideWindowRect:(CGRect)windowRect windowThreshold:(CGFloat)windowThreshold;
+ (NSArray *)sortArrayBasedOnArea:(NSArray *)array;

+ (UIView *_Nullable)getViewWithFindConfig:(NSDictionary *)findConfig inView:(UIView *)superView;
+ (UIView *_Nullable)getViewWithFindConfig:(NSDictionary *)findConfig;
+ (bool)validateText:(NSString *)text withEval:(NSDictionary *)evaluation;

#pragma mark - reactnative helper method
+ (NSString *_Nullable)getNativeIDForView:(UIView *)view;

#pragma mark - Color Utilities
+ (UIColor *_Nonnull)colorFromHexString:(NSString *_Nullable)hex;

#pragma mark - Range for Count
+ (NSString *_Nonnull)rangeForCount:(NSInteger)count;

#pragma mark - Device Token
+ (NSString *)stringWithDeviceToken:(NSData *)deviceToken;

#pragma mark - Config utils
+ (NSDictionary *_Nullable)getPIDMIDDictFromString:(NSString *_Nonnull)pidmidString;
+ (NSDictionary *_Nullable)iDKeyDictionaryForConfigs:(NSArray *_Nonnull)configs;
+ (BOOL)doesConfig:(NSDictionary*_Nonnull)config containsPID:(NSString *_Nonnull)pid;
+ (NSMutableDictionary*)dictionaryByRemovingEntryWithPID:(NSString *_Nonnull)pid fromConfig:(NSMutableDictionary *_Nonnull)config;
+ (NSArray*_Nonnull)getAllPIDsInConfig:(NSDictionary *_Nonnull)config;
+ (void)logAppEventWithCampaignDiagnosticsForConfig:(NSDictionary *)config title:(NSString *)title reason:(NSString *)reason;
+ (NSString *)getVariantCodeForConfig:(NSDictionary *)config;
+ (BOOL)isUrlSchemePresent:(NSString *)scheme;
@end
