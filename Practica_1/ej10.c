#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {
	
        printf("UID -->  %i\nEUID --> %i\n", getuid(), geteuid());
	
	struct passwd* inf;
	
	if ((inf = getpwuid(getuid())) == NULL){
		printf("getpwuid error --> %i: %s", errno, strerror(errno));
		return -1;
	}
	
	printf("Name --> %s\nHome --> %s\nDescription --> %s\n", inf->pw_name, inf->pw_dir, inf->pw_gecos);

	return 1;
}

