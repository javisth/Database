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
	int date1;
	int date2;
	int flag; // to check the status of something

	if(argc != 3) {
		fprintf(stderr, "Usage: ccyear date date\n");
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
	// setting the file pointer to the beginning of the file
	fseek(fp, sizeof(CComp), SEEK_SET);
	// comparing and finding the year between two dates
	while(fread(&item, sizeof(CComp), 1, fp) > 0) {
		date1 = atoi(argv[1]);
		date2 = atoi(argv[2]);

		// if i find my year between the two dates, i set status to 1
		if (item.year >= date1 && item.year <= date2) {
			flag = 1;
		}
		else {
			flag = 0;
		}
		// i print item information if i find the year
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
