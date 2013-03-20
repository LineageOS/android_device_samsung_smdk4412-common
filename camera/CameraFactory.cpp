/*
 * Copyright (C) 2012 Homin Lee <suapapa@insignal.co.kr>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "CameraFactory"
#include <utils/Log.h>

#include "CameraFactory.h"

#ifdef SAMSUNG_S5P_JPEG_ENCODER
#include "S5PJpegEncoder.h"
#endif

#ifdef LIBJPEG_ENCODER
#include "LibJpegEncoder.h"
#endif
//#include "GnuExifTagger.h"

namespace android {

const char* camera_info_get_default_camera_param_str(int camera_id)
{
    // S5C73M3
    static const char* back_cam_init_params_str =
        "preview-size=960x720;"
        "preview-size-values=960x720,1280x720,640x480,352x288,320x240;"
        "preview-format=yuv420sp;"
        "preview-format-values=yuv420sp,yuv420p;"
        "preview-frame-rate=30;"
        "preview-frame-rate-values=10,15,20,30;"
        "preview-fps-range=15000,30000;"
        "preview-fps-range-values=(10000,10000),(15000,15000),(15000,30000),(30000,30000);"
        "picture-size=3264x2176;"
        "picture-size-values=640x480,960x720,1024x768,1280x720,1600x1200,2560x1920,3264x2448,2048x1536,3264x1836,2048x1152,3264x2176;"
        "picture-format=jpeg;"
        "picture-format-values=jpeg;"
        "jpeg-thumbnail-width=160;"
        "jpeg-thumbnail-height=120;"
        "jpeg-thumbnail-size-values=160x120,160x90,144x96,0x0;"
        "jpeg-thumbnail-quality=100;"
        "jpeg-quality=100;"
        "rotation=0;"
        "orientation=90;"
        "min-exposure-compensation=-4;"
        "max-exposure-compensation=4;"
        "exposure-compensation-step=0.5;"
        "exposure-compensation=0;"
        "whitebalance=auto;"
        "whitebalance-values=auto,incandescent,fluorescent,daylight,cloudy-daylight;"
        "effect=none;"
        "effect-values=none,mono,negative,sepia,solarize,posterize,washed,vintage-warm,vintage-cold,point-blue,point-red-yellow,point-green,cartoonize;"
        "antibanding=auto;"
        "antibanding-values=auto,50hz,60hz,off;"
        "scene-mode=auto;"
        "scene-mode-values=auto,portrait,landscape,night,beach,snow,sunset,fireworks,sports,party,candlelight,dusk-dawn,fall-color,text,back-light;"
        "focus-mode=auto;"
        "focus-mode-values=auto,macro,infinity;"
        //"focus-mode-values=auto,infinity,macro,fixed,continuous-picture,continuous-video;"
        //"focus-distances=0.15,1.20,Infinity;"
        //"focus-areas=(0,0,0,0,0);"
        //"max-num-focus-areas=1;"
        "flash-mode=off;"
        "flash-mode-values=off,auto,on,torch;"
        "video-size=1280x720;"
        "video-size-values=1920x1080,1280x720,960x720,720x480,640x480,352x288,320x240,176x144;"
        "video-frame-format=yuv420sp;"
        "focal-length=370;"
        "zoom_supported=1;"
        "smooth_zoom_supported=0;"
        "zoom-ratios=100,102,104,109,111,113,119,121,124,131,134,138,146,150,155,159,165,170,182,189,200,213,222,232,243,255,283,300,319,364,400;"
        "zoom=0;"
        "max-zoom=30";

    return back_cam_init_params_str;
}

int camera_info_get_number_of_cameras(void)
{
    return 1;
}

int camera_info_get_camera_info(int camera_id, struct camera_info* info)
{
    info->facing = CAMERA_FACING_BACK;
    info->orientation = 0;

    return 0;
}

EncoderInterface* get_encoder(void)
{
    EncoderInterface* encoder = NULL;

#if 0 //def SAMSUNG_S5P_JPEG_ENCODER
    ALOGI("creating S5PJpegEncoder...");
    encoder = new S5PJpegEncoder();
#endif

#ifdef LIBJPEG_ENCODER
    ALOGI("creating LibJpegEncoder...");
    encoder = new LibJpegEncoder();
#endif

    ALOGW_IF(encoder == NULL, "No jpeg encoder specified!");

    return encoder;
}

TaggerInterface* get_tagger(void)
{
    ALOGW("No tagger exists!");
    TaggerInterface* tagger = NULL; //new GnuExifTagger();
    return tagger;
}

};
