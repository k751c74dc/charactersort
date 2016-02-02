#include "cookie.h"
#include "design.h"
#include "url.h"

void main(int argc, char *argv[]){
	Cookie *ck;
	int i;

	ck = (Cookie *)malloc(sizeof(Cookie));

	init_cookie(ck);

	/** Cookieを読み込み **/
	get_cookie(ck);

	printf("Content-type:text/html\n");
	set_cookie(ck);

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>結果発表</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();

	/** rankingを元に，出力させます **/
	for(i = 0;i < ck->amount;i++) {
		switch(i) {
			case 0: printf("<FONT size = \"6\">");
			break;
			case 1: printf("<FONT size = \"4\">");
			break;
			case 2: printf("<FONT size = \"3\">");
			break;
		}
		printf("第%d位 ： %s <BR>",i+1,ck->name[(int)ck->score[i]]);
	}

	footer();

	printf("</BODY>\n");
	printf("</HTML>\n");

	return;
}
