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
	int flag; // to check the status of something
	char change; // to store whether there needs to be a change or not
	char changed; // to store the desired change
	int attribute; // to store the attribute number that needs changing

	if(argc != 2) {
		fprintf(stderr, "Usage: ccedit id\n");
		exit(1);
	}
	// opening the file
	fp = fopen("ccdb", "r+");
	if(fp == NULL) {
		perror("fopen");
		exit(2);
	}
	// locking the file
	flock(fileno(fp), LOCK_EX);
	flag = 0;
	// setting the file pointer to the beginning of the file
	fseek(fp, sizeof(CComp), SEEK_SET);
	// searching for the required item that needs editing
	while(fread(&item, sizeof(CComp), 1, fp) > 0) {
		inum = atoi(argv[1]);

		// if i find the item, i set status to 1
		if (item.id == inum) {
			flag = 1;
		}
		else {
			flag = 0;
		}
		// i ask for the appropriate changes and make them
		if(flag == 1) {
			printf("(1) Name: %s\n", item.name);
			printf("(2) Maker: %s\n", item.maker);
			printf("(3) CPU: %s\n", item.cpu);
			printf("(4) Year: %d\n", item.year);
			printf("(5) Desc: %s\n", item.desc);
			printf("Do you want to change any attribute? (y/n)\n");
			scanf("%s",&change);
			if(change == 'y') {
				printf("Which attribute number would you like to change?\n");
				scanf("%d", &attribute);
				if (attribute) {
					printf("Please enter the required change you would like to make\n");
					if(attribute == 1) {
						scanf("%s", &changed);
						strncpy(item.name, &changed, Nname);
					}
					if(attribute == 2) {
						scanf("%s", &changed);
						strncpy(item.maker, &changed, Nmaker);
					}
					if(attribute == 3) {
						scanf("%s", &changed);
						strncpy(item.cpu, &changed, Ncpu);
					}
					if(attribute == 4) {
						scanf("%s", &changed);
						item.year = atoi(&changed);
					}
					if(attribute == 5){
						scanf("%s", &changed);
						strncpy(item.desc, &changed, Ndesc);
					}
					// i write the new changes to the file
					fseek(fp, item.id * sizeof(CComp), SEEK_SET);
					fwrite(&item, sizeof(CComp), 1, fp);
					

				}
				else {
					printf("You have entered an invalid attribute number\n");
				}
			}
			printf("\n");
			break;
		}
	}

	flock(fileno(fp), LOCK_UN);
	fclose(fp);
}
