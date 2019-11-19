#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#define MAX 65535

int main(int argc, char **argv){
	FILE *fp1, *fp2;
	int proc;
	char rw;
	char c;
	int i;
	unsigned int addr;
	char line[1023];
	int ret;
	char *arg_identifier;
	char *check;

	fp1 = fopen(argv[1], "r+");
	if (fp1 == NULL){
		printf("File failed to open read file\n");
		exit(1);
	}
	if(argc > 2){
		fp2 = fopen(argv[2], "w");
		if(fp2 == NULL){
			printf("error opening write file\n");
			exit(1);
		}
	}
	while(!feof(fp1)){
		ret = fscanf(fp1, "%d %c %x", &proc, &rw, &addr);
		if(ret != 3){
			fgets(line, MAX, fp1);
			if(strcmp(argv[3], "ROI") == 0){
				check = strstr(line, "ROI");
				//printf("#ROI found\n");
			}
			else{
				printf("#unknown chars found: %s\n", line);
			}

		}
		else {
			if ((proc>=0)&&(proc<16)  &&  (rw=='r')||(rw=='w')  && (addr<= 0xffffffff)){
				if(argc>1){
					if(strcmp(argv[3], "ROI") == 0){
						if(check){
							fprintf(fp2, "%d\t%c\t%08x\n", proc, rw, addr);	
						}
					}
					else {
						fprintf(fp2, "%d\t%c\t%08x\n", proc, rw, addr);
					}
				}
			}
			else{
				printf("wrong instn: %d %c %08x\n", proc, rw, addr);
			}
		}
	}
	if(argc>1){
		fclose(fp2);
	}
	fclose(fp1);
}