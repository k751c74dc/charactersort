#include "cookie.h"
#include "design.h"
#include "url.h"

void main(int argc, char *argv[]){
	Cookie *ck;
	int i,j,tmp;

	ck = (Cookie *)malloc(sizeof(Cookie));

	init_cookie(ck);

	/** Cookieを読み込み **/
	get_cookie(ck);

	printf("Content-type:text/html\n");
	set_cookie(ck);
	int ranking[ck->amount];
	
	for(i = 0;i < ck->amount;i++) {
		ranking[i] = i;
	}

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<TITLE>結果発表</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();

	/** rankingを元に，出力させます **/
	for(i = 0;i < ck->amount;i++) {
		j = i;
		while(j >= 1 && ck->score[j-1] - ck->score[j] < 0) {
			tmp = ranking[j];
			ranking[j] = ranking[j-1];
			ranking[j-1] = tmp;
			j--;
		}
	}
	
	for(i = 0;i < ck->amount;i++) {
		switch(i) {
		case 0: printf("<FONT size = \"6\">");
		break;
		case 1: printf("<FONT size = \"5\">");
		break;
		case 2: printf("<FONT size = \"4\">");
		break;
		}
		printf("第%d位 ： %s (%f)<BR>",i+1,ck->name[ranking[i]],ck->score[ranking[i]]*100);
	}

	footer();

	printf("</BODY>\n");
	printf("</HTML>\n");

	return;
}
