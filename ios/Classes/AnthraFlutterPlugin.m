//
//  AnthraFlutterPlugin.m
//

#import "AnthraFlutterPlugin.h"
#import "AnthraSDK/ANTController.h"
#import "AnthraSDK/ANTBidiDelegate.h"
#import "ANTFlutterBidiEventBus.h"

static FlutterBasicMessageChannel *command_channel = nil;
static FlutterBasicMessageChannel *card_channel = nil;
static NSObject<FlutterPluginRegistrar>* registar = nil;

@implementation AnthraFlutterPlugin {
    id<ANTBidiDelegate> bus;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        [[ANTController sharedController] registerForEventWithType:ANTEventTypeInternal listener:self];
        [[ANTController sharedController] markAsFlutter];
        bus = [[ANTFlutterBidiEventBus alloc] init];
        [[ANTController sharedController] registerForBidiEventsBus:bus WithKey:@"APXOR_FLUTTER_W"];
    }
    return self;
}

+(void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {

    // method channel for communication between flutter and ApxorSDK
    FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"plugins.flutter.io/anthra_flutter"
            binaryMessenger:[registrar messenger]];
    AnthraFlutterPlugin* instance = [[AnthraFlutterPlugin alloc] init];
    [registrar addMethodCallDelegate:instance channel:channel];
    
    registar = registrar;
    
    // basic message channel for communication between ApxorSDK and flutter
    command_channel = [FlutterBasicMessageChannel messageChannelWithName:@"plugins.flutter.io/anthra_commands" binaryMessenger:[registrar messenger] codec:[FlutterJSONMessageCodec sharedInstance]];
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    if ([@"logAppEvent" isEqualToString:call.method]) {
        NSDictionary *info;
        if ([call.arguments valueForKey:@"attrs"] != [NSNull null]) {
            info = [call.arguments valueForKey:@"attrs"];
        } else {
            info = nil;
        }
        [AnthraSDK logAppEventWithName:[call.arguments valueForKey:@"name"] info:info];
        [command_channel sendMessage:@{@"name" : @"hello"}];
        result(nil);
    } else if ([@"logClientEvent" isEqualToString:call.method]) {
        NSDictionary *info;
        if ([call.arguments valueForKey:@"attrs"] != [NSNull null]) {
            info = [call.arguments valueForKey:@"attrs"];
        } else {
            info = nil;
        }
        [AnthraSDK logClientEventWithName:[call.arguments valueForKey:@"name"] info:info];
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
        [AnthraSDK setUserIdentifier: [call.arguments valueForKey:@"userId"]];
        result(nil);
    } else if ([@"setUserAttributes" isEqualToString:call.method]) {
        [AnthraSDK setUserCustomInfo: call.arguments];
        result(nil);
    } else if ([@"setSessionAttributes" isEqualToString:call.method]) {
        [AnthraSDK setSessionCustomInfo: call.arguments];
        result(nil);
    } else if ([@"setCurrentScreenName" isEqualToString:call.method]) {
        [AnthraSDK logScreenWithName:[call.arguments valueForKey:@"name"]];
        result(nil);
    } else if ([@"trackScreen" isEqualToString:call.method]){
        [AnthraSDK logScreenWithName:[call.arguments valueForKey:@"name"]];
        result(nil);
    } else if ([@"getDeviceId" isEqualToString:call.method]) {
        if ([AnthraSDK getDeviceID]){
            result([AnthraSDK getDeviceID]);
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
            card_channel = [FlutterBasicMessageChannel messageChannelWithName:[NSString stringWithFormat:@"plugins.flutter.io/anthra_embeddedView%@",[data valueForKey:@"id"]] binaryMessenger:[registar messenger]
            codec:[FlutterJSONMessageCodec sharedInstance]];
            [card_channel sendMessage:data];
        });
    }
}

@end
