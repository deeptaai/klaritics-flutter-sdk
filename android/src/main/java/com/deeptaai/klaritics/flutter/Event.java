package com.deeptaai.klaritics.flutter;

import static com.deeptaai.klaritics.Constants.INTERNAL_EVENTS;

import com.deeptaai.klaritics.models.BaseAnthraEvent;

import org.json.JSONObject;

public final class Event extends BaseAnthraEvent {
    private final String name;
    private final JSONObject data;

    public Event(String name, JSONObject data) {
        this.name = name;
        this.data = data;
    }

    @Override
    public JSONObject getJSONData() {
        return data;
    }

    @Override
    public String getEventType() {
        return INTERNAL_EVENTS;
    }

    @Override
    public String getEventName() {
        return name;
    }
}
