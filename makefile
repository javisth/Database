# make file
all:
	gcc cc.h  
	gcc ccadd.c -o ccadd 
	gcc ccitem.c -o ccitem
	gcc ccedit.c -o ccedit
	gcc ccdel.c -o ccdel
	gcc ccmatch.c -o ccmatch
	gcc ccyear.c -o ccyear
	gcc cclist.c -o cclist
