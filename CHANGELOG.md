# Changelog

## 2.0.0

**Breaking:** Full rebrand from `apxor_flutter` to `anthra_flutter`.

- Pub package name is now `anthra_flutter`; replace dependency and all `import 'package:apxor_flutter/...'` with `package:anthra_flutter/...`.
- Main API class is `AnthraFlutter` (was `ApxorFlutter` on mobile; web now matches).
- `ApxNavigationObserver` → `AnthraNavigationObserver`.
- Library export: use `anthra_flutter.dart` as the primary import; `apxor.dart` was removed.
- `apxor_widget.dart` → `anthra_widget.dart` (`AnthraWidget` unchanged).
- Android plugin package: `com.anthra.flutter`, plugin class `AnthraFlutterPlugin`.
- iOS pod: `anthra_flutter`, plugin class `AnthraFlutterPlugin`.
- Method channels: `plugins.flutter.io/anthra_flutter`, `plugins.flutter.io/anthra_commands`; per-view channels use `plugins.flutter.io/anthra_view_*` (Android) and `plugins.flutter.io/anthra_embeddedView*` (iOS embedded cards).
- Platform view IDs: `com.anthra.flutter/AnthraEmbedView` (Android), `com.anthra.flutter/anthra_embeddedCard` (iOS).
- Web plugin registration class: `FlutterAnthraWeb` (was `FlutterApxorWeb`).
- WebView JS bridge: `window.Apxor` and `ApxorFlutter` handler names in injected scripts are **unchanged** for compatibility with existing Apxor web/RTM content.
- Native Apxor Android/iOS SDK dependencies (Maven AARs, CocoaPods `Apxor-*`) are unchanged.

## 1.0.0

- Initial flutter SDK release

## 1.0.1

- Added debug logs and try-catch blocks

## 1.0.5

- Fixed actions for invisble views 
- Added custom user id support

## 1.0.6

- Added Support for iOS
- Added Support for Web
- Added Support for WebView

## 1.1.2

- Added support for Embedded Cards

## 1.1.3

- Added check if element is mounted before accessing widget

## 1.1.5

- Removed string manipulations in the log statements in MainThread.

## 1.1.7

- Fixed race condition in receiver handling (iOS).