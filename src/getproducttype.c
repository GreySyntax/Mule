/*
 *  getproducttype.c
 *  mule
 *
 *  Created by GreySyntax on 21/06/2010.
 *  Copyright 2010 NSPwn. All rights reserved.
 *
 */
#include <stdio.h>
#include "MobileDevice.h"

void am_preformtask(struct am_device_notification_callback_info *info, void *foo) {
	struct am_device *apple_device = info->dev;
	
	if (! info->msg == ADNCI_MSG_CONNECTED) {
		
		printf("[AMDevice] Failed to Connect\r\n");
		CFRunLoopStop(CFRunLoopGetCurrent());
		exit(-1);		
	}
	
	if (! AMDeviceConnect(apple_device)) {
		
		printf("[AMDevice] Connected.\r\n");
		
		if (AMDeviceIsPaired(apple_device)) {
			
			printf("[AMDevice] Paired.\r\n");
			
			if (AMDeviceValidatePairing(apple_device) == 0) {
				
				printf("[AMDevice] Validated Pairing.\r\n");
				
				if (! AMDeviceStartSession(apple_device)) {
					
					printf("[AMDevice] Session Started.\r\n");
					
					CFStringRef pstr = AMDeviceCopyValue(apple_device, 0, CFSTR("ProductType"));
					CFStringRef pstr2 = AMDeviceCopyValue(apple_device, 0, CFSTR("ProductVersion"));
					
					char *value = (char *) malloc(512);
					char *value2 = (char *) malloc(512);
					
					//MIDIObjectGetStringProperty(ref, propertyID, &pstr);
					CFStringGetCString(pstr, value, 512, 0);
					CFStringGetCString(pstr2, value2, 512, 0);
					CFRelease(pstr);
					CFRelease(pstr2);
					printf("%s:%s\r\n", value, value2);
					
					CFRunLoopStop(CFRunLoopGetCurrent());
					exit(1);	
				}
			}
		}
	}
}

static void am_dfuconnect(struct am_recovery_device *rdev) {
	
	printf("[AMDevice] Device Connected in DFU mode.\r\n");
	
}

static void am_recoveryconnect(struct am_recovery_device *rdev) {
	
	printf("[AMDevice] Device Connected in Recovery mode.\r\n");
}

void am_recoverydisconnect(struct am_recovery_device *rdev) {
	//    cout << "DisconnectRecoveryCallback" << endl;
	// this is a stub, but it looks like it gives a Bus error if you don't use it.
}

int main (int argc, const char * argv[]) {
	
	printf("\r\nMule (getproducttype) - Copyright GreySyntax NSPwn.com 2010\r\n\r\n");
	
	struct am_device_notification *notif;
	AMDeviceNotificationSubscribe((am_device_notification_callback) am_preformtask, 0, 0, 0, &notif);
	AMRestoreRegisterForDeviceNotifications(am_dfuconnect, am_recoveryconnect, NULL, am_recoverydisconnect, 0, NULL);
	CFRunLoopRun();
	
    return 0;
}
