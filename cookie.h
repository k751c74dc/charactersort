#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

typedef struct {
	char name[MAX_REGISTER][MAX_CHAR * 3 + 1]; /** register name **/
	int registeredLink[MAX_REGISTER][MAX_REGISTER]; /** link State **/
	int ranking[MAX_REGISTER]; /** ranking **/
} Cookie;

int init_cookie(Cookie *);
int get_cookie(Cookie *);
int set_cookie(Cookie *);

int init_cookie(Cookie *ck) {
	int i, j;

	for (i = 0; i < MAX_REGISTER; i++) {
		strncpy(ck->name[i],"A",MAX_CHAR * 3 + 1);
		for(j = 0; j < MAX_REGISTER; j++){
			ck->registeredLink[i][j] = 0;
		}
		ck->ranking[i] = -1;
	}

	return 0;
}

/** reference at webings.net/c/cookie/ **/
int get_cookie(Cookie *ck) {
	int i ,j;
	int intcheck = 0;
	char cmpString[MAX_CHAR];
	char ctmp[MAX_CHAR];
	char *strck, *tp, *tp2;

	if ((strck = getenv("HTTP_COOKIE")) != NULL) {
		printf("$%s<BR>\n", strck);
		tp = strtok(strck, "=; ");
		printf("0$%s<BR>\n",tp);
		do {
			intcheck = 0;
			for (i = 0; i < MAX_REGISTER; i++) {
				sprintf(cmpString, "name[%d]", i);
				if (strcmp(tp, cmpString) == 0) {
					tp = strtok(NULL, "=; ");
					printf("1$%s<BR>\n",tp);
					/** registering **/
					strcpy(ck->name[i], tp);

					tp = strtok(NULL, "=; ");
					printf("0$%s<BR>\n",tp);
				}
			}
			for(i = 0; i < MAX_REGISTER; i++){
				for(j = 0; j < MAX_REGISTER; j++){
					sprintf(cmpString, "registeredLink[%d][%d]", i, j);
					if (strcmp(tp, cmpString) == 0) {
						tp = strtok(NULL, "=; ");
						printf("1$%s<BR>\n",tp);
						strcpy(ctmp, tp);
						ck->registeredLink[i][j] = atoi(ctmp);

						tp = strtok(NULL, "=; ");
						printf("0$%s<BR>\n",tp);
					}
				}
			}
			for(i = 0; i < MAX_REGISTER; i++){
				sprintf(cmpString, "ranking[%d]", i);
				if (strcmp(tp, cmpString) == 0) {
					tp = strtok(NULL, "=; ");
					printf("1$%s<BR>\n",tp);
					strcpy(ctmp, tp);
					ck->ranking[i] = atoi(ctmp);

					tp = strtok(NULL, "=; ");
					printf("0$%s<BR>\n",tp);
				}
			}

			if (intcheck == 0) {
				tp = strtok(NULL, "=; ");
			}
		} while ((tp = strtok(NULL, "=; ")) != NULL);
	}


/**
	if ((strck = getenv("HTTP_COOKIE")) != NULL){
		for(i=0; i<MAX_REGISTER; i++){
			tp = strtok(strck, ";");
			tp2 = strtok(tp, "=");
			sprintf(cmpString, "name[%d]", i);
			if (!strcmp(tp2, cmpString)){
				tp2 = strtok(NULL, "=");
				strncpy(ck->name[i], tp2, MAX_CHAR*3+1);
				printf("name[%d]=%s; ",i, ck->name[i]);
			}
		}
		for(i=0; i<MAX_REGISTER; i++){
			for(j=0; j<MAX_REGISTER; j++){
				tp = strtok(strck, ";");
				tp2 = strtok(tp, "=");
				sprintf(cmpString, "registeredLink[%d][%d]",i,j);
				if (!strcmp(tp2, cmpString)){
					tp2 = strtok(NULL, "=");
					ck->registeredLink[i][j] = atoi(tp2);
					printf("registeredLink[%d][%d]=%d; ",i,j,ck->registeredLink[i][j]);
				}
			}
		}
		for(i=0; i<MAX_REGISTER; i++){
			tp = strtok(strck, ";");
			tp2 = strtok(tp, "=");
			sprintf(cmpString, "ranking[%d]",i);
			if (!strcmp(tp2, cmpString)){
				tp2 = strtok(NULL, "=");
				ck->ranking[i] = atoi(tp2);
				printf("ranking[%d]=%d; ",i,ck->ranking[i]);
			}
		}
	}
**/

	return 0;
}

int set_cookie(Cookie *ck) {
	int i, j;

	for (i = 0; i < MAX_REGISTER; i++) {
		printf("Set-Cookie: ");
		printf("name[%d]=%s;\n", i, ck->name[i]);
	}
	for (i = 0; i < MAX_REGISTER; i++) {
		for(j = 0; j < MAX_REGISTER; j++){
			printf("Set-Cookie: ");
			printf("registeredLink[%d][%d]=%d;\n",i,j, ck->registeredLink[i][j]);
		}

	}
	for (i = 0; i < MAX_REGISTER; i++) {
		printf("Set-Cookie: ");
		printf("ranking[%d]=%d;\n", i,ck->ranking[i]);
	}
	printf("\n");

	return 0;
}
