#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "design.h"
#include "define.h"
#include "url.h"
#include "cookie.h"

#define MAX 4000
int getstring(char *, char *, char *);

void main(int argc, char *argv[]){
	int i,len;
	char *pBuf;
	char name[10][100];

	len = atoi(getenv("CONTENT_LENGTH"));
	Cookie ck;
	ck = (Cookie *)malloc(sizeof(Cookie));
	/** クッキーの初期化 **/
	init_cookie(ck);

	/** **/

	if (len == 0 || len >= 2048) {
		err();
		return 0;
	};
	/**フォームデータをget **/
	for (i = 0; (c = getchar()) != EOF; i++) {
		if (c != '\r' && c != '\n')
			pBuf[i] = c;
		else
			i--;
	}
	pBuf[i] = '\0';

	/** Cookie構造体に入力 **/
	/** その際にnameにはパーセントエンコードで **/

	getstring(pBuf, "name0", name[0]);
	getstring(pBuf, "name1", name[1]);
	getstring(pBuf, "name2", name[2]);
	getstring(pBuf, "name3", name[3]);
	getstring(pBuf, "name4", name[4]);
	getstring(pBuf, "name5", name[5]);
	getstring(pBuf, "name6", name[6]);
	getstring(pBuf, "name7", name[7]);
	getstring(pBuf, "name8", name[8]);
	getstring(pBuf, "name9", name[9]);

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

	/** リダイレクト文を **/
	printf("<script>location.href=\"compare.cgi\"</script>\n");

	printf("</BODY>\n");
	printf("</HTML>\n");
	return;
}

int getstring(char *src, char *element, char *dest){

	int len;
	char *data, *amp;
	char *temp;

	len = (int)strlen(src) + 1;
	temp = (char *)malloc(len);

	len = (int)strlen(src);
	if (len >= 2048) {
		err();
		free(temp);
		return -1;
	}

	strcpy(temp, src);

	data = strstr(temp, element);
	if(data == NULL) {
		strcpy(dest, "");
		free(temp);
		return -2;
	}

	len = (int)strlen(element) + 1;

	amp = strstr(data, "&");

	if (amp == NULL) {
		strcpy(dest, data + len);
		if (dest[0] == '\0') {
			strcpy(dest, "");
			free(temp);
			return 0;
		}
		free(temp);
		return 1;
	}
	data[(int)(amp-data)] = '\0';
	strcpy(dest, data + len);

	if (dest[0] == '\0') {
		strcpy(dest, "");
		free(temp);
		return 0;
	}

	free(temp);
	return 0;
}