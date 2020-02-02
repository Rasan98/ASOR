#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

int main() {
	struct tm* local;	
	time_t t;
	char date[100];

	if((t = time(NULL)) == -1){
		printf("time error --> %i: %s", errno, strerror(errno));
                return -1;
	}
	
	local = localtime(&t);
	
	setlocale(LC_ALL, "es_ES");
	
	strftime(date, 100, "%A, %d de %B de %Y, %H:%M", local);	
	
	printf("%s\n", date);

	return 1;
}

