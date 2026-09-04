package com.anthra.flutter;

import android.content.Context;
import androidx.annotation.Nullable;
import androidx.annotation.NonNull;
import io.flutter.plugin.common.StandardMessageCodec;
import io.flutter.plugin.platform.PlatformView;
import io.flutter.plugin.platform.PlatformViewFactory;
import io.flutter.plugin.common.BinaryMessenger;
import java.util.Map;

class AnthraEmbedViewFactory extends PlatformViewFactory {
  private final BinaryMessenger binaryMessenger;

  public AnthraEmbedViewFactory(BinaryMessenger binaryMessenger) {
    super(StandardMessageCodec.INSTANCE);
    this.binaryMessenger = binaryMessenger;
  }

  @NonNull
  @Override
  public PlatformView create(@NonNull Context context, int id, @Nullable Object args) {
    final Map<String, Object> creationParams = (Map<String, Object>) args;
    return new AnthraEmbedView(context, id, creationParams, binaryMessenger);
  }
}
