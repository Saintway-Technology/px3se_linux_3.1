#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	int ret;
	char cmd[512]={0};

	usleep(2*1000*1000);
	system("echo 1 > /sys/class/rfkill/rfkill0/state");
	usleep(1*1000*1000);
	system("chmod 777 /dev/ttyS0");
	if(argv[1] != NULL) {
		fprintf(stderr,"rkbt argv %s\n",argv[1]);
		sprintf(cmd,"hciattach /dev/%s bcm43xx 115200 &",argv[1]);
		system(cmd);
	} else {
		system("hciattach /dev/ttyS0 bcm43xx 115200 &");
	}
	usleep(5*1000*1000);
	system("/usr/libexec/bluetooth/bluetoothd --compat -n &");
	system("sdptool add A2SNK");
	system("hciconfig hci0 up");
	system("hciconfig hci0 piscan");
	system("pulseaudio --start -v");
    	usleep(2000*1000);
    	system("pulseaudio --start -v");//try again,confirm pulseaudio is start
    	usleep(2000*10000);
	system("hciattach /dev/ttyS0 bcm43xx 115200 &");

}
