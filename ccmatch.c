#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include "cc.h"

int
main(int argc, char *argv[])
{
	CComp item;
	FILE *fp;
	char *name;
	char *maker;
	char *model;
	int flag; // to check the status of something

	if(argc != 2) {
		fprintf(stderr, "Usage: ccmatch string\n");
		exit(1);
	}
	// opening the file
	fp = fopen("ccdb", "r");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}
	// locking the file
	flock(fileno(fp), LOCK_EX);
	flag = 0;
	// move file pointer to beginning of file
	fseek(fp, sizeof(CComp), SEEK_SET);
	// searching for substrings in the file
	while(fread(&item, sizeof(CComp), 1, fp) > 0) {
		name = strstr(item.name, argv[1]);
		maker = strstr(item.maker, argv[1]);
		model = strstr(item.cpu, argv[1]);
		// if i find the substring in any of the variables i set status to 1
		if (name || maker || model) {
			flag = 1;
		}
		else {
			flag = 0;
		}
		// if i find the substring, i print the required items
		if(flag == 1) {
			printf("Name: %s\n", item.name);
			printf("Maker: %s\n", item.maker);
			printf("CPU: %s\n", item.cpu);
			printf("Year: %d\n", item.year);
			printf("ID: %d\n", item.id);
			printf("Desc: %s\n", item.desc);
			printf("\n");
		}
	}

	flock(fileno(fp), LOCK_UN);
	fclose(fp);
}
