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
	int inum;
	int flag;


	if(argc != 2) {
		fprintf(stderr, "Usage: ccedel id\n");
		exit(1);
	}

	fp = fopen("ccdb", "r+");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}
	flock(fileno(fp), LOCK_EX);
	flag = 0;
	fseek(fp, sizeof(CComp), SEEK_SET);
	while(fread(&item, sizeof(CComp), 1, fp) > 0) {
		inum = atoi(argv[1]);


		if (item.id == inum) {
			flag = 1;
		}
		else {
			flag = 0;
		}

		if(flag == 1) {
			strncpy(item.name, "", Nname);
			strncpy(item.maker, "", Nmaker);
			strncpy(item.cpu, "", Ncpu);
			item.year = 0;
			strncpy(item.desc, "", Ndesc);
			fseek(fp, item.id * sizeof(CComp), SEEK_SET);
			item.id = 0;
			fwrite(&item, sizeof(CComp), 1, fp);	
			break;
		}
	}

	flock(fileno(fp), LOCK_UN);
	fclose(fp);
}
