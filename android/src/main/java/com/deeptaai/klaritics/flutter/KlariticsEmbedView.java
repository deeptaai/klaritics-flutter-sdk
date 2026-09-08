package com.deeptaai.klaritics.flutter;

import android.content.Context;
import android.view.View;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import io.flutter.plugin.platform.PlatformView;
import java.util.Map;

import com.deeptaai.klaritics.utils.Logger;

import io.flutter.plugin.common.BasicMessageChannel;
import io.flutter.plugin.common.JSONMessageCodec;
import io.flutter.plugin.common.BinaryMessenger;

// NOTE: The embedded/realtime-UI widget is not yet available in klaritics-android-sdk 1.0.0
// (no realtime-UI plugin ships with the core SDK). This view is stubbed to an empty View so
// the plugin compiles and analytics keeps working. Re-implement using the Klaritics realtime-UI
// widget (formerly ApxorWidget + ExecutionListener) once that plugin is published.
class KlariticsEmbedView implements PlatformView {
    private final View embedView;
    private int tag = -1;
    private BasicMessageChannel<Object> viewChannel;

    KlariticsEmbedView(@NonNull Context context, int id, @Nullable Map<String, Object> creationParams, final BinaryMessenger binaryMessenger) {
        try {
            tag = (int) creationParams.get("id");
            viewChannel = new BasicMessageChannel<>(
            binaryMessenger,
            "plugins.flutter.io/klaritics_view_"+this.tag,
            JSONMessageCodec.INSTANCE
            );
        } catch (Exception e) {
            Logger.debug("Klaritics","Flutter value key is not valid "+e.getMessage());
        }
        // TODO(klaritics): replace with the Klaritics realtime-UI widget when available.
        embedView = new View(context);
    }

    @Override
    public View getView() {
        return embedView;
    }

    @Override
    public void dispose() {
        viewChannel = null;
    }
}
