#include "cookie.h"
#include "design.h"

void main(int argc, char *argv[]){
	Cookie *ck;

	ck = (Cookie *)malloc(sizeof(Cookie));

	init_cookie(ck);

	/** Cookieを読み込み **/
	get_cookie(ck);

	/** ソートさせます **/


	/** 結果をCookieのranking[]に出力させます　**/


	printf("Content-type:text/html\n");
	set_cookie(ck);
	printf("/n");

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>ソート中</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();

	/** リダイレクト文 **/

	footer();

	printf("</BODY>\n");
	printf("</HTML>\n");

	return;
}