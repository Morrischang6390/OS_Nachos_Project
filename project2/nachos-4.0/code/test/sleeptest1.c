#include "syscall.h"
main()
	{
		int	n;
		for (n=9;n>5;n--){
			mySleep(10000000);
			PrintInt(n);
		}
	}
