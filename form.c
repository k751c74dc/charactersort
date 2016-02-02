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
	printf("<link href=\"css/bootstrap.min.css\" rel=\"stylesheet\">\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();

	printf("<h1>\n");
	printf("キャラクターソート with PageRank\n");
	printf("</h1>\n");
	printf("<p>\n");
	printf("ページランクアルゴリズムにより、入力した事柄の好感度ランキングを作成します。");
	printf("</p>\n");

	/** ここにフォームを入力 **/
	printf("<form action=\"convert.cgi\" method=\"post\" accept-charset=\"UTF-8\">\n");

	for ( i = 0; i < MAX_REGISTER; i++){
		printf("<p>\n");
		printf("データ%d:<input type=\"text\" name=\"name%d\" size=\"40\">\n",i,i);
		printf("</p>\n");
	}

	printf("<p>\n");
	printf("<input type=\"submit\" class=\"btn btn-primary\" value=\"送信\"><input type=\"reset\" class=\"btn btn-default\" value=\"リセット\">\n");
	printf("</p>\n");

	printf("</form>\n");
	/** フォームここまで **/

	footer();
	printf("</BODY>\n");
	printf("</HTML>\n");
	return;
}