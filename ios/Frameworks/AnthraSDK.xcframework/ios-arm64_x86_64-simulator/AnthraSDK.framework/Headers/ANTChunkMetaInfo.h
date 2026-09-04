#import <Foundation/Foundation.h>
#import "ANTInfo.h"

@interface ANTChunkMetaInfo : ANTInfo
-(instancetype) initWith:(NSString*) sid cid:(NSUInteger)cid start:(NSUInteger)start end:(NSUInteger)end reportingTimes:(NSArray*)ts;
@end
