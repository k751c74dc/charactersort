#include <stdio.h>
#include <design.h>

void main(int argc, char *argv[]){
	printf("Content-type:text/html\n\n");

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>データ入力</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();

	/** ここにフォームを入力 **/

	footer();
	printf("</BODY>\n");
	printf("</HTML>\n");
	return;
}