#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char **argv){
	FILE *fp;
	fp = fopen(argv[1], "r+");
	char line[255];
	int proc, addr;
	char rw;
	int count = 0;
	while(!feof(fp)){
		//fgets(line, 255, fp);
		fscanf(fp, "%d %c %x", &proc, &rw, &addr);
		//printf("%s\n", line);
		if(proc == atoi(argv[2])){
			count++;
			printf("%d\t%c\t%08x\n",proc, rw, addr);
		}
	}
	fclose(fp);
	printf("#the count is %d\n", count);
}
