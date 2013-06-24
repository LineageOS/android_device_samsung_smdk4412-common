/*
 * Copyright (C) 2013 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.cyanogenmod.settings.device;

import android.content.Context;
import android.content.SharedPreferences;
import android.preference.CheckBoxPreference;
import android.preference.Preference;
import android.preference.Preference.OnPreferenceChangeListener;
import android.preference.PreferenceManager;
import android.util.AttributeSet;
import android.util.Log;

public class BlAutoBrightness extends CheckBoxPreference implements OnPreferenceChangeListener {

    private static final String FILE = "/sys/class/backlight/panel/auto_brightness";

    private static final String MANUAL = "0";
    private static final String AUTO_INDOOR1 = "1";

    public BlAutoBrightness(Context context, AttributeSet attrs) {
        super(context, attrs);
        this.setOnPreferenceChangeListener(this);
    }

    public static boolean isSupported() {
        return Utils.fileExists(FILE);
    }

    /**
     * Restore setting from SharedPreferences. (Write to kernel.)
     * @param context       The context to read the SharedPreferences from
     */
    public static void restore(Context context) {
        if (!isSupported()) {
            return;
        }

        SharedPreferences sharedPrefs = PreferenceManager.getDefaultSharedPreferences(context);
        Utils.writeValue(FILE, sharedPrefs.getBoolean(DeviceSettings.KEY_BL_AUTO_BRIGHTNESS, false) ? AUTO_INDOOR1 : MANUAL);
    }

    public boolean onPreferenceChange(Preference preference, Object newValue) {
        Utils.writeValue(FILE, (Boolean)newValue ? AUTO_INDOOR1 : MANUAL);
        return true;
    }
}
