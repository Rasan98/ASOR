#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/utsname.h>

int main() {
	struct utsname buf;
	if (uname(&buf) == -1){
		printf("uname error: %i --> %s\n", errno, strerror(errno));
	}
	
	printf("NombreSO --> %s\nNombreNodo --> %s\nRelease --> %s\nVersion --> %s\nMachine --> %s\n", buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
	return 1;
}

