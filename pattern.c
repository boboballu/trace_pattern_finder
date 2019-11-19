#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX 65535

int main(int argc, char **argv){
	FILE *fp;
	int proc=0;
	char rw;
	char c;
	int i;
	unsigned int addr;
	char line[1023];
	int ret;
	char *arg_identifier;
	enum {none, t, x, p, r} mode;

	if(argc < 1){
		printf("Args required: ./executable filename -t/x/p/r #(print trace/ print error string/just print without changing the source file/just print error)\n");
		exit(1);
	}
	for(i=2; i<argc; i++){
			arg_identifier = strstr(argv[i],"-");
			if(arg_identifier){
				if(*(arg_identifier+1) == 't'){
					mode = t;
				}
				else if(*(arg_identifier+1) == 'x'){
					mode = x;
				}
				else if(*(arg_identifier+1) == 'p'){
					mode = p;
				}
				else if(*(arg_identifier+1) == 'r'){
					mode = r;
				}
				else {
					mode = none;
				}
			}
		}
	fp = fopen(argv[1], "r+");
	if (fp == NULL){
		printf("File failed to open\n");
		exit(1);
	}

	while(1){
		ret = fscanf(fp, "%d %c %x", &proc, &rw, &addr);
		if(ret != 3){
			//fscanf(fp, "%s", line);
			fgets(line, MAX, fp);
			if(mode == x || mode==none) {
				printf("#found unknown char in trace: ");
				printf("%s\n", line);
			}

			if(mode != p){
				i = strlen(line);
				fseek(fp, -i, SEEK_CUR);
				// fscanf(fp, "%s", line);
				// printf("%d %s\n",i, line);
				while(i > 0){
					if(i == 1)
						putc('\n', fp);
					else
						putc('\t', fp);
					
					i--;
				}
				fseek(fp, 0, SEEK_CUR);
				//break;
			}
		}
		if(mode == p || mode==none || mode==t){
			printf("%d\t%c\t%08x\n", proc, rw, addr);
		}

		if(feof(fp)){
			break;
		}
	}
	//fflush(fp);
	fclose(fp);
}