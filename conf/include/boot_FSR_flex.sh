#!/bin/sh
##########################################################################
# If not stated otherwise in this file or this component's LICENSE
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

 #* @file      boot_FSR.sh
 #* @brief     Orchestrates Flex-specific migration and factory-reset flows on stb devices.
 #* @details   - Reads current boot type and checks presence of x1hello.object and shell.object from local storage.  
 #*            - Implements EntOS migration use cases as per stb requirements (Trigger FSR for devices without pre-migration)
 #*            - Full System Reset (FSR) is triggered after setting the flag and calling /rebootNow.sh 
 #*            - EPIC links are:
 #*            - https://ccp.sys.comcast.net/browse/CPESP-7679
 #*            - Followed the HLA provided below:
 #*            - https://www.stb.bskyb.com/confluence/pages/viewpage.action?pageId=303447278#FlexSpecificMigrationusecasesStates&Flowcharts-EntOSFlow
 ###########################################################################

file_x1hello_obj="/opt/QT/home/data/x1hello.object"
file_shell_obj="/opt/QT/home/data/shell.object"
file_bootType="/tmp/bootType"
file_MigrationStatus="/opt/secure/persistent/MigrationStatus"
file_DataStore="/opt/secure/migration/migration_data_store.json"

status_xre="null"
current_bootType=$(<"$file_bootType")
current_bootType=${current_bootType:10}


if [ -z $LOG_PATH ]; then
    LOG_PATH="/opt/logs/"
fi

BOOTTYPE_LOG_FILE="$LOG_PATH/boottypescript.log"

boottypeLog() {
    echo "`/bin/timestamp`: $0: $*" >> $BOOTTYPE_LOG_FILE
}

do_FSR () {
    touch /tmp/data/.trigger_reformat
    sh /rebootNow.sh -s boot_FSR -r "entOS migration from RDK-V" -o "Rebooting the box for triggering FSR..."
}

boottypeLog "Checking for XRE experience on device..."
if [ -e "$file_x1hello_obj" ] || [ -e "$file_shell_obj" ]; then
     boottypeLog "The device has had XRE experience before, hence returning status as true"
     status_xre="true"
else
     boottypeLog "The device has not had XRE experience before, hence returning status as false"
     status_xre="false"
fi

if [ "$status_xre" != "true" ]; then
    if [ "$current_bootType" == "BOOT_INIT" ] || [ "$current_bootType" == "BOOT_NORMAL" ]; then
        boottypeLog "current BootType is $current_bootType and XRE experience is false"
    elif [ "$current_bootType" == "BOOT_MIGRATION" ]; then 
        if [ -e "$file_DataStore" ]; then
            boottypeLog "current BootType is $current_bootType and XRE experience is false"
        else
            #DataStore file is not present 
            boottypeLog "Triggering FSR since DataStore is not present"
            do_FSR
        fi 
    fi
elif [ "$status_xre" == "true" ]; then
    if [ "$current_bootType" == "BOOT_NORMAL" ]; then
        boottypeLog "current BootType is $current_bootType and XRE experience is true"
    elif [ "$current_bootType" == "BOOT_INIT" ]; then
          boottypeLog "Triggering FSR since XRE experience is true and current BootType is $current_bootType"
          do_FSR
    elif [ "$current_bootType" == "BOOT_MIGRATION" ]; then
          boottypeLog "current BootType is $current_bootType and XRE experience is true"
        if [ -e "$file_DataStore" ]; then
            boottypeLog "DataStore file is present"
        else
            #DataStore file is not present 
            boottypeLog "Triggering FSR since DataStore is not present"
            do_FSR
        fi
    fi    
fi
