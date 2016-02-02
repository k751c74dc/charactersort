#include <stdio.h>
#include "design.h"
#include "define.h"

void main(int argc, char *argv[]){
	int i;
	printf("Content-type:text/html\n\n");

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>データ入力</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();

	/** ここにフォームを入力 **/
	printf("<form action=\"convert.cgi\" method=\"post\">\n");

	for ( i = 0; i < MAX_REGISTER; i++){
		printf("<p>");
		printf("データ%d:<input type=\"text\" name=\"name[%d]\" size=\"40\">\n",i,i);
		printf("</p>");
	}

	printf("<p>");
	printf("<input type=\"submit\" value=\"送信\"><input type=\"reset\" value=\"リセット\">\n");
	printf("</p>");

	printf("</form>");
	/** フォームここまで **/

	footer();
	printf("</BODY>\n");
	printf("</HTML>\n");
	return;
}