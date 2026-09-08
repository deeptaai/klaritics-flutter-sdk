// Copyright 2021, the Flutter project authors. Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

import 'package:flutter/material.dart';
import 'package:klaritics_flutter/klaritics_flutter.dart';
import 'package:url_strategy/url_strategy.dart';

import 'src/app.dart';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();

  // Use package:url_strategy until this pull request is released:
  // https://github.com/flutter/flutter/pull/77103

  // Use to setHashUrlStrategy() to use "/#/" in the address bar (default). Use
  // setPathUrlStrategy() to use the path. You may need to configure your web
  // server to redirect all paths to index.html.
  //
  // On mobile platforms, both functions are no-ops.
  setHashUrlStrategy();
  // setPathUrlStrategy();

  // Initialize the Klaritics SDK on Android and iOS in a single call.
  // Replace YOUR_APP_ID and YOUR_HOST with the values from your dashboard.
  final config = KlariticsConfig('YOUR_APP_ID');
  config.host = 'YOUR_HOST';
  await KlariticsFlutter.setup(config);

  runApp(const Bookstore());
}
