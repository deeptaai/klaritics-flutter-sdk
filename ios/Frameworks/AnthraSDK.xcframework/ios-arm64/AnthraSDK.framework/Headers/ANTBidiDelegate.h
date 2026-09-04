//
//  APXBidiEventProtocol.h
//  ApxorSDK
//
//  Created by Ramcharan  on 20/07/23.
//  Copyright © 2023 Apxor. All rights reserved.
//

#ifndef ANTBidiEventProtocol_h
#define ANTBidiEventProtocol_h

#import <Foundation/Foundation.h>

typedef void (^Receiver)(NSDictionary *response);

@protocol ANTBidiDelegate <NSObject>

- (void)sendAndGetWithData:(NSDictionary *)data receiver:(Receiver)receiver;
- (void)receiveAndRespondWithData:(NSDictionary *)data receiver:(Receiver)receiver;


@end


#endif /* ANTBidiEventProtocol_h */
