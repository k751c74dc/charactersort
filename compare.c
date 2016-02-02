#include "url.h"
#include "cookie.h"
#include "design.h"

void main(int argc, char *argv[]){
	Cookie *ck;

	ck = (Cookie *)malloc(sizeof(Cookie));

	init_cookie(ck);

	/** Cookieを読み込み **/
	get_cookie(ck);

	/** フォームデータをget **/
	/** もしなかったら(初めの状態)，最初ってこと **/
	/** 全て埋まったら，sort.cにリダイレクト **/

	/** フォームデータからCookie(データ構造)を上書きする **/

	printf("Content-type:text/html\n");
	/** cookieに出力 **/
	set_cookie(ck);
	printf("\n");

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>どっちがいい?</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();

	/** 隠しフォーム形式で 比較を **/
	/** 自身(compare.cgi)に送信 **/

	footer();
	printf("</BODY>\n");
	printf("</HTML>\n");
	return;
}