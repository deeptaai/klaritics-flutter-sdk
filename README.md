# Klaritics Flutter SDK

> **Note: Flutter SDK supported version is `>= 3.0.1`**

Flutter wrapper for **Klaritics**.

## Integration

Add the `klaritics_flutter` dependency in `pubspec.yaml`

```yaml
dependencies:
  klaritics_flutter: ^1.0.0
```

Import it in your Dart code:

```dart
import 'package:klaritics_flutter/klaritics_flutter.dart';
```

### Initialize

Initialize the SDK **once** from Dart — this initializes both the Android and iOS native SDKs in a
single call. Do it in `main()` before `runApp`, and `await` it before logging any events. Replace
`YOUR_APP_ID` and `YOUR_HOST` with the values from your Klaritics dashboard.

```dart
Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();

  final config = KlariticsConfig('YOUR_APP_ID');
  config.host = 'YOUR_HOST';
  await KlariticsFlutter.setup(config);

  runApp(const MyApp());
}
```

> Because initialization happens from Dart, you do **not** need to call the native
> `Klaritics.setup(...)` in your Android `Activity`/`Application` or iOS `AppDelegate`.

### Android

- The Klaritics Android SDK is published to a private Maven repository. Add the repository in your
  project-level `android/build.gradle` (or `settings.gradle`) `repositories { }` block:

  ```groovy
  maven {
      url "https://asia-south1-maven.pkg.dev/org-infra-471907/klaritics-android-sdk"
  }
  ```

- Add the dependency in your `app/build.gradle` file:

  ```groovy
  dependencies {
    implementation "com.deeptaai.klaritics:klaritics-android-sdk:1.0.0"
  }
  ```

- Initialization is handled from Dart via `KlariticsFlutter.setup(config)` (see
  [Initialize](#initialize) above) — no native `Klaritics.setup(...)` call is required.

- If you use proguard, add the following in your `proguard-rules.pro` file:

  ```proguard
  -keep class com.deeptaai.klaritics.** { *; }
  -dontwarn com.deeptaai.klaritics.**
  ```

### iOS

The Klaritics iOS SDK is consumed via Swift Package Manager. This plugin declares the dependency
in its `Package.swift`, so with Flutter's Swift Package Manager support enabled it is added
automatically. No `AppDelegate` changes are needed — initialization is handled from Dart via
`KlariticsFlutter.setup(config)` (see [Initialize](#initialize) above).

## APIs

### Identifying Users

The Klaritics SDK automatically captures device IDs which the Klaritics backend uses to uniquely identify users.

If you want to, you can assign your own user IDs. This is particularly useful if you want to study a specific user with ease. To assign your own user ID, you can use

```dart
KlariticsFlutter.setUserIdentifier("<SOME_USER_ID>");
```

### User Attributes

There is often additional user identifying information, such as name and email address, connected with the external IDs.

To add some more attributes that are specific to a particular user,

```dart
KlariticsFlutter.setUserAttributes({
  'age': 27,
  'gender': "male",
});
```

### Session Attributes

A Session can be simply defined as user journey as he opens the app, until he closes the app. There can be various pieces of information that be very impactful when accumulated in a session. For example, location in a session can be useful to know exactly where, the user is utilizing the app most.

To add session attributes that are specific to a session,

```dart
KlariticsFlutter.setSessionAttributes({
  "network": "4G",
  "location": "Hyderabad",
});
```

### App Events

App events make it easier to analyze user behavior and optimize your product and marketing around common business goals such as improving user retention or app usage. You can also add additional information for any event.

To track an event with the event name and properties.

```dart
KlariticsFlutter.logAppEvent("Login", attributes: {
  "type": "Google",
  "language": "valyrian",
});
```

### Client Events

Events that are logged to reside on the client application are called client events, the data captured is not transferred to Klaritics.

These are typically logged to capture behavioural observations and interactions to nudge a user.

> Example:
>
> Soft back button, user reaching end of page, etc.

```dart
KlariticsFlutter.logClientEvent("SoftBackPressed", attributes: {
  "screenName": "Payment",
});
```