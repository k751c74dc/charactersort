#include "url.h"
#include "cookie.h"

void main(int argc, char *argv[]){
	Cookie *ck;

	ck = (Cookie *)malloc(sizeof(Cookie));

	init_cookie(ck);

	/**フォームデータをget **/

	/** Cookie構造体に入力 **/
	/** その際にnameにはパーセントエンコードで **/

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

	printf("</BODY>\n");
	printf("</HTML>\n");
	return;
}