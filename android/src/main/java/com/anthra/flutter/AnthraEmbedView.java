package com.anthra.flutter;

import android.content.Context;
import android.view.View;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import io.flutter.plugin.platform.PlatformView;
import java.util.Map;

import com.apxor.androidsdk.core.utils.Logger;
import com.apxor.androidsdk.plugins.realtimeui.ApxorWidget;

import io.flutter.plugin.common.BasicMessageChannel;
import io.flutter.plugin.common.JSONMessageCodec;
import io.flutter.plugin.common.BinaryMessenger;
import com.apxor.androidsdk.core.ce.ExecutionListener;

import org.json.JSONObject;

class AnthraEmbedView implements PlatformView {
    private ApxorWidget apxorView;
    private int tag = -1;
    private BasicMessageChannel<Object> viewChannel;

    AnthraEmbedView(@NonNull Context context, int id, @Nullable Map<String, Object> creationParams, final BinaryMessenger binaryMessenger) {
        try {
            tag = (int) creationParams.get("id");
            viewChannel = new BasicMessageChannel<>(
            binaryMessenger,
            "plugins.flutter.io/anthra_view_"+this.tag,
            JSONMessageCodec.INSTANCE
            );
        } catch (Exception e) {
            Logger.debug("Anthra","Flutter value key is not valid "+e.getMessage());
        }
        apxorView = new ApxorWidget(context,tag,"flutter",new ExecutionListener() {
            @Override
            public void onAfterExecute(Object result, boolean hasError) {
                Logger.debug("Anthra","Received dimensions from native "+result+""+hasError);
                if(result != null && viewChannel != null) {
                    if(result instanceof JSONObject) {
                        viewChannel.send(result);
                    }
                }       
            }
        });
    }

    @Override
    public View getView() {
        return apxorView;
    }

    @Override
    public void dispose() {
        viewChannel = null;
    }
}
