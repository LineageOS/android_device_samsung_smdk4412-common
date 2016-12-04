#!/bin/bash
#
# Copyright (C) 2016 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

set -e
DEVICE_COMMON=smdk4412-common
DEVICE=${DEVICE:-nodevice}
VENDOR=samsung

# Load extract_utils and do some sanity checks
MY_DIR="${BASH_SOURCE%/*}"
if [[ ! -d "$MY_DIR" ]]; then MY_DIR="$PWD"; fi

CM_ROOT="$MY_DIR"/../../..

HELPER="$CM_ROOT"/vendor/cm/build/tools/extract_utils.sh
if [ ! -f "$HELPER" ]; then
    echo "Unable to find helper script at $HELPER"
    exit 1
fi
. "$HELPER"

# Initialize the helper for common device
setup_vendor "$DEVICE_COMMON" "$VENDOR" "$CM_ROOT" true

# Copyright headers and common guards
write_headers "i9300 i9305 n7100 n8000 n8013 n8020 t0lte t0lteatt t0ltetmo i605 l900 r950 i925 n5100 n5110 n5120"

write_makefiles "$MY_DIR"/proprietary-files.txt

write_footers

if [ "$DEVICE" "!=" "nodevice" ]; then
    # Reinitialize the helper for the device-specific blobs
    setup_vendor "$DEVICE" "$VENDOR" "$CM_ROOT"

    # Copyright headers and guards
    write_headers

    # The device-specific blobs
    write_makefiles "$MY_DIR"/../$DEVICE/proprietary-files.txt

    # Done
    write_footers
fi
