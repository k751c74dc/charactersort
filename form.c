#include <stdio.h>
#include "design.h"
#include "define.h"

int main(int argc, char *argv[]) {
	int i;
	printf("Content-type:text/html\n\n");

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>キャラクター名入力</TITLE>\n");
	printf("<link href=\"css/bootstrap.min.css\" rel=\"stylesheet\">\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();

	printf("<h1>\n");
	printf("キャラクターソート with PageRank\n");
	printf("</h1>\n");
	printf("<p>\n");
	printf("ページランクアルゴリズムにより、入力したキャラクターの好感度ランキングを作成します。<BR>各データは20文字までです。");
	printf("</p>\n");

	/** ここにフォームを入力 **/
	printf("<form action=\"convert.cgi\" method=\"post\" accept-charset=\"UTF-8\">\n");

	for (i = 0; i < MAX_REGISTER; i++) {
		printf("<div class=\"form-group\">\n");
		/*
		 printf("<label　class=\"sr-only\" for=\"%d\">データ%d</label>\n",i,i+1);
		 */
		printf("<input id=\"%d\" type=\"text\" class=\"form-control\" name=\"name%d\" placeholder=\"キャラ%d\" maxlength=\"%d\" style=\"width:350px;\" >\n", i, i, i + 1, 20);
		printf("</div>\n");
	}

	printf("<p>\n");
	printf("<input type=\"submit\" class=\"btn btn-primary\" value=\"送信\"><input type=\"reset\" class=\"btn btn-default\" value=\"リセット\">\n");
	printf("</p>\n");

	printf("</form>\n");
	/** フォームここまで **/

	footer();
	printf("</BODY>\n");
	printf("</HTML>\n");
	return 0;
}
