#ifndef APXPostman_h
#define APXPostman_h

NS_ASSUME_NONNULL_BEGIN

@interface ANTPostman : NSObject

+ (NSURLSession *)sharedSession;
- (void)getDataFromURLPath:(NSString *)path completionHandler:(void (^)(NSData *, NSURLResponse *, NSError *))completionHandler;
- (void)postDataToURL:(NSString*)path withRequestBodyDictionary:(NSDictionary*)requestData headerFields:(NSDictionary* _Nullable)headers completionHandler:(void (^)(NSData *, NSURLResponse *, NSError *))completionHandler;
- (void)makeDeleteRequestToURLPath:(NSString *)path headerFields:(NSDictionary*)headers completionHandler:(void (^)(NSData *, NSURLResponse *, NSError *))completionHandler;

- (void)getDataFromURL:(NSString *)path completionHandler:(void (^)(NSData *, NSURLResponse *, NSError *))completionHandler;

@end

NS_ASSUME_NONNULL_END

#endif /* APXPostman_h */
