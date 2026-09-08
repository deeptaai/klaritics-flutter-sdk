//
//  KlariticsFlutterPlugin.m
//

#import "./include/klaritics_flutter/KlariticsFlutterPlugin.h"
#import <Klaritics/ANTController.h>
#import <Klaritics/ANTBidiDelegate.h>
#import "./include/klaritics_flutter/KlariticsFlutterBidiEventBus.h"

static FlutterBasicMessageChannel *command_channel = nil;
static FlutterBasicMessageChannel *card_channel = nil;
static NSObject<FlutterPluginRegistrar>* registar = nil;

@implementation KlariticsFlutterPlugin {
    id<ANTBidiDelegate> bus;
}

- (instancetype)init {
    self = [super init];
    return self;
}

// Registers the plugin with the Klaritics SDK. Called after [Klaritics setup:]
// has initialized the SDK (via the "setup" method channel from Dart).
- (void)registerWithSdk {
    [[ANTController sharedController] registerForEventWithType:ANTEventTypeInternal listener:self];
    [[ANTController sharedController] markAsFlutter];
    bus = [[KlariticsFlutterBidiEventBus alloc] init];
    [[ANTController sharedController] registerForBidiEventsBus:bus WithKey:@"APXOR_FLUTTER_W"];
}

+(void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {

    // method channel for communication between flutter and Klaritics
    FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"plugins.flutter.io/klaritics_flutter"
            binaryMessenger:[registrar messenger]];
    KlariticsFlutterPlugin* instance = [[KlariticsFlutterPlugin alloc] init];
    [registrar addMethodCallDelegate:instance channel:channel];

    registar = registrar;

    // basic message channel for communication between Klaritics and flutter
    command_channel = [FlutterBasicMessageChannel messageChannelWithName:@"plugins.flutter.io/klaritics_commands" binaryMessenger:[registrar messenger] codec:[FlutterJSONMessageCodec sharedInstance]];
}


- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    if ([@"setup" isEqualToString:call.method]) {
        id appIdVal = [call.arguments valueForKey:@"appId"];
        id hostVal = [call.arguments valueForKey:@"host"];
        BOOL appIdValid = [appIdVal isKindOfClass:[NSString class]] && [(NSString *)appIdVal length] > 0;
        BOOL hostValid = [hostVal isKindOfClass:[NSString class]] && [(NSString *)hostVal length] > 0;
        if (!appIdValid || !hostValid) {
            result([FlutterError errorWithCode:@"Klaritics"
                                        message:@"Klaritics cannot be initialized: `appId` and `host` are required in setup"
                                        details:nil]);
            return;
        }
        KlariticsConfig *config = [[KlariticsConfig alloc] initWithAppId:(NSString *)appIdVal host:(NSString *)hostVal];
        [Klaritics setup:config];
        [self registerWithSdk];
        result(nil);
    } else if ([@"logAppEvent" isEqualToString:call.method]) {
        NSDictionary *info;
        if ([call.arguments valueForKey:@"attrs"] != [NSNull null]) {
            info = [call.arguments valueForKey:@"attrs"];
        } else {
            info = nil;
        }
        [Klaritics logAppEventWithName:[call.arguments valueForKey:@"name"] info:info];
        [command_channel sendMessage:@{@"name" : @"hello"}];
        result(nil);
    } else if ([@"logClientEvent" isEqualToString:call.method]) {
        NSDictionary *info;
        if ([call.arguments valueForKey:@"attrs"] != [NSNull null]) {
            info = [call.arguments valueForKey:@"attrs"];
        } else {
            info = nil;
        }
        [Klaritics logClientEventWithName:[call.arguments valueForKey:@"name"] info:info];
        result(nil);
    }  else if ([@"logInternalEvent" isEqualToString:call.method]) {
        NSDictionary *info;
        if ([call.arguments valueForKey:@"attrs"] != [NSNull null]) {
            info = [call.arguments valueForKey:@"attrs"];
        } else {
            info = nil;
        }
        [[ANTController sharedController] logInternalEventWithName:[call.arguments valueForKey:@"name"] info:info];
        result(nil);
    } else if ([@"setUserIdentifier" isEqualToString:call.method]) {
        [Klaritics setUserIdentifier: [call.arguments valueForKey:@"userId"]];
        result(nil);
    } else if ([@"setUserAttributes" isEqualToString:call.method]) {
        [Klaritics setUserCustomInfo: call.arguments];
        result(nil);
    } else if ([@"setSessionAttributes" isEqualToString:call.method]) {
        [Klaritics setSessionCustomInfo: call.arguments];
        result(nil);
    } else if ([@"setCurrentScreenName" isEqualToString:call.method]) {
        [Klaritics logScreenWithName:[call.arguments valueForKey:@"name"]];
        result(nil);
    } else if ([@"trackScreen" isEqualToString:call.method]){
        [Klaritics logScreenWithName:[call.arguments valueForKey:@"name"]];
        result(nil);
    } else if ([@"getDeviceId" isEqualToString:call.method]) {
        if ([Klaritics getDeviceID]){
            result([Klaritics getDeviceID]);
        } else {
            result(nil);
        }
    } else if ([@"gfn" isEqualToString:call.method]) {
        result(@(0));
    } else if ([@"getDimensions" isEqualToString:call.method]) {
        result(@{@"height": @200});
    } else {
        NSArray *layout = [call.arguments valueForKey:@"r"];
        NSNumber *time = [call.arguments valueForKey:@"t"];
        NSMutableDictionary *data = [NSMutableDictionary dictionary];
        [data setValue:layout forKey:@"r"];
        if ([@"dr" isEqualToString:call.method]) {
            [[ANTController sharedController] logInternalEventWithName:[@"d_" stringByAppendingString:[time stringValue]] info:data];
        } else if ([@"fr" isEqualToString:call.method]) {
            [[ANTController sharedController] logInternalEventWithName:[@"f_" stringByAppendingString:[time stringValue]] info:data];
        } else if ([@"avf" isEqualToString:call.method]) {
            [[ANTController sharedController] logInternalEventWithName:[@"avf_" stringByAppendingString:[time stringValue]] info:data];
        }
    }
}
- (void)onEvent:(ANTEvent *)event {
    NSMutableDictionary *data = [[event getAdditionalInfo] mutableCopy];
    NSString *eName = event.identifier;
    [data setValue:eName forKey:@"name"];
    if ([eName isEqualToString:@"d"] || [eName isEqualToString:@"f"] || [eName isEqualToString:@"iwv"] || [eName isEqualToString:@"avf"]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            [command_channel sendMessage:data];
        });
    } else if ([eName isEqualToString:@"apx_redirection"]) {
        NSMutableDictionary *eData = [NSMutableDictionary dictionary];
        [eData setValue:data[@"url"] forKey:@"u"];
        [eData setValue:@(-1) forKey:@"t"];
        [eData setValue:@"redirect" forKey:@"name"];
        dispatch_async(dispatch_get_main_queue(), ^{
            [command_channel sendMessage:eData];
        });
    } else if ([eName isEqualToString:@"EC"]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            card_channel = [FlutterBasicMessageChannel messageChannelWithName:[NSString stringWithFormat:@"plugins.flutter.io/klaritics_embeddedView%@",[data valueForKey:@"id"]] binaryMessenger:[registar messenger]
            codec:[FlutterJSONMessageCodec sharedInstance]];
            [card_channel sendMessage:data];
        });
    }
}

@end
