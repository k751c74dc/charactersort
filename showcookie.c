#include "cookie.h"
void main(int argc, char *argv[]){
	Cookie *ck;
	int i, j;

	ck = (Cookie *)malloc(sizeof(Cookie));

	init_cookie(ck);

	get_cookie(ck);


	printf("Content-type:text/html\n");

	printf("\n");

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>cookie</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");

	for(i = 0; i < MAX_REGISTER; i++){
		printf("name[%d]:%s<BR>\n",i,ck->name[i]);
	}

	for(i = 0; i < MAX_REGISTER; i++){
		for(j = 0; j < MAX_REGISTER; j++){
			printf("registeredLink[%d][%d]:%s<BR>\n",i,j,ck->registeredLink[i][j]);
		}
	}

	for(i = 0; i < MAX_REGISTER; i++){
		printf("ranking[%d]:%d<BR>\n",i,ck->ranking[i]);
	}
	printf("</BODY>\n");
	printf("</HTML>\n");
	free(ck);
	return;
}
