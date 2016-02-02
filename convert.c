#include <stdio.h>
#include <stdlib.h>
#include "design.h"
#include "define.h"
#include "url.h"
#include "cookie.h"

int itemcount = 0;

int getstring(char *, char *, char *);

void main(int argc, char *argv[]){
	int i,j;
	char c;
	char tmp[MAX_CHAR];
	char *pBuf;
	char tmpname[MAX_REGISTER][MAX_CHAR];
	Cookie *ck;

	ck = (Cookie *)malloc(sizeof(Cookie));
	/** クッキーの初期化 **/
	init_cookie(ck);
	/** **/
	/**フォームデータをget **/
	pBuf = (char *)malloc(MAX_CHAR * MAX_REGISTER + 100);
	if (pBuf == NULL) {
		err();
		return;
	}

	for (i = 0; (c = getchar()) != EOF; i++) {
		if (c != '\r' && c != '\n'){
			pBuf[i] = c;
		}else{
			i--;
		}
	}
	pBuf[i] = '\0';


	for(i = 0; i < MAX_REGISTER; i++){
		sprintf(tmp,"name%d",i);
		getstring(pBuf, tmp, tmpname[i]);

		if( (strcmp(tmpname[i],"_no_data_") != 0) &&(strcmp(tmpname[i],"_no_element_") != 0) ){
			strncpy(ck->name[itemcount],tmpname[i],MAX_CHAR);
			itemcount++;
		}
	};

	if (itemcount <= 0) {
		err();
		return;
	}

	ck->amount = itemcount;

	printf("Content-type:text/html\n");
	/** cookieに出力 **/
	set_cookie(ck);
	printf("\n");

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>変換中</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");

	/*デバッグ用*/
	/*
	printf("itemcount is %d<BR>\n",itemcount);
	printf("ck->amount is %d<BR>\n",ck->amount);

	printf("<BR>");
	for(i = 0; i < MAX_REGISTER; i++){
		printf("tmpname[%d]:%s<BR>\n",i,tmpname[i]);
	}
	printf("<BR>");
	for(i = 0; i < MAX_REGISTER; i++){
		printf("ck->name[%d]:%s<BR>\n",i,ck->name[i]);
	}
	*/
	/** リダイレクト文を **/

	printf("<script>location.href=\"compare.cgi\"</script>\n");



	printf("</BODY>\n");
	printf("</HTML>\n");
	return;
}

int getstring(char *src, char *element, char *dest)
{
	int len;
	char *data, *amp;
	char *temp;


	len = (int)strlen(src) + 1;
	temp = (char *)malloc(len);

	len = (int)strlen(src);
	if (len >= 1024) {
		err();
		free(temp);
		return -1;
	}

	strcpy(temp, src);

	data = strstr(temp, element);
	if(data == NULL) {
		strcpy(dest, "_no_element_");
		free(temp);
		return -2;
	}

	len = (int)strlen(element) + 1;

	amp = strstr(data, "&");
	if (amp == NULL) {
		strcpy(dest, data + len);
		if (dest[0] == '\0') {
			strcpy(dest, "_no_data_");
			free(temp);
			return 0;
		}
		free(temp);
		return 1;
	}
	data[(int)(amp-data)] = '\0';
	strcpy(dest, data + len);

	if (dest[0] == '\0') {
		strcpy(dest, "_no_data_");
		free(temp);
		return 0;
	}
	free(temp);
	return 0;
}