#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
		int fl;
		char buf[1];
		buf[0]='1';
		fl = open("/sys/class/gpio/gpio21/value",O_RDWR);
		
		write(fl,buf,1);
		
		close(fl);
		
		return 0;
}
