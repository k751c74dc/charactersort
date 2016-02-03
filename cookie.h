#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"

typedef struct {
	char name[MAX_REGISTER][MAX_CHAR * 3 + 1]; /** register name **/
	float registeredLink[MAX_REGISTER][MAX_REGISTER]; /** link State **/
	float score[MAX_REGISTER]; /** score **/
	int amount;
} Cookie;

int init_cookie(Cookie *);
int get_cookie(Cookie *);
int set_cookie(Cookie *);

int init_cookie(Cookie *ck) {
	int i, j;

	for (i = 0; i < MAX_REGISTER; i++) {
		strncpy(ck->name[i], "", MAX_CHAR * 3 + 1);
		for (j = 0; j < MAX_REGISTER; j++) {
			ck->registeredLink[i][j] = 0;
		}
		ck->score[i] = -1;
	}
	ck->amount = 0;

	return 0;
}
/** reference at webings.net/c/cookie/ **/
int get_cookie(Cookie *ck) {
	int i, j;
	char cmpString[MAX_CHAR];
	char ctmp[MAX_CHAR];
	char *strck, *tp, *tp2;

	strck = (char *) malloc(sizeof(getenv("HTTP_COOKIE")));

	if ((strck = getenv("HTTP_COOKIE")) != NULL) {
		strcat(strck, "; ");
		tp = strtok(strck, "=; ");
		do {
			for (i = 0; i < MAX_REGISTER; i++) {
				sprintf(cmpString, "name[%d]", i);
				if (strcmp(tp, cmpString) == 0) {
					tp = strtok(NULL, "=; ");
					/** registering **/
					strcpy(ck->name[i], tp);

					tp = strtok(NULL, "=; ");
				}
			}
			for (i = 0; i < MAX_REGISTER; i++) {
				for (j = 0; j < MAX_REGISTER; j++) {
					sprintf(cmpString, "registeredLink[%d][%d]", i, j);
					if (strcmp(tp, cmpString) == 0) {
						tp = strtok(NULL, "=; ");
						strcpy(ctmp, tp);
						ck->registeredLink[i][j] = atof(ctmp);

						tp = strtok(NULL, "=; ");
					}
				}
			}
			for (i = 0; i < MAX_REGISTER; i++) {
				sprintf(cmpString, "score[%d]", i);
				if (strcmp(tp, cmpString) == 0) {
					tp = strtok(NULL, "=; ");
					strcpy(ctmp, tp);
					ck->score[i] = atof(ctmp);

					tp = strtok(NULL, "=; ");
				}
			}
			if (strcmp(tp, "amount") == 0) {
				tp = strtok(NULL, "=; ");
				strcpy(ctmp, tp);
				ck->amount = atoi(ctmp);
				tp = strtok(NULL, "=; ");
			}

		} while ((tp = strtok(NULL, "=; ")) != NULL);
	}

	return 0;
}

int set_cookie(Cookie *ck) {
	int i, j;

	for (i = 0; i < MAX_REGISTER; i++) {
		printf("Set-Cookie: ");
		printf("name[%d]=%s;\n", i, ck->name[i]);
	}
	for (i = 0; i < MAX_REGISTER; i++) {
		for (j = 0; j < MAX_REGISTER; j++) {
			printf("Set-Cookie: ");
			printf("registeredLink[%d][%d]=%f;\n", i, j, ck->registeredLink[i][j]);
		}

	}
	for (i = 0; i < MAX_REGISTER; i++) {
		printf("Set-Cookie: ");
		printf("score[%d]=%f;\n", i, ck->score[i]);
	}
	printf("Set-Cookie: ");
	printf("amount=%d;\n", ck->amount);
	printf("\n");

	return 0;
}
