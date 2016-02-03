#include "cookie.h"
#include "design.h"
#include "url.h"

int main(int argc, char *argv[]){
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
	/** CSSの読み込み **/
	printf("<link href=\"css/bootstrap.min.css\" rel=\"stylesheet\">\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	header();
	/** rankingを元に，出力させます **/
	for(i = 0;i < ck->amount;i++) {
		j = i;
		while(j >= 1 && ck->score[ranking[j-1]] - ck->score[ranking[j]] < 0) {
			tmp = ranking[j];
			ranking[j] = ranking[j-1];
			ranking[j-1] = tmp;
			j--;
		}
	}

	printf("<table class=\"table table-hover\">\n");
	printf("<thead>\n<tr>\n");
	printf("<th>順位</th>\n<th>データ名</th><th>重要度</th>\n");

	printf("</tr>\n</thead>\n");

	for(i = 0;i < ck->amount;i++) {
		printf("<tr>\n<td>\n");
		switch(i) {
			case 0: printf("<FONT size = \"6\">");
			break;
			case 1: printf("<FONT size = \"5\">");
			break;
			case 2: printf("<FONT size = \"4\">");
			break;
		}
		url_decode(ck->name[ranking[i]],strlen(ck->name[ranking[i]]));
		printf("第%d位",i+1);
		printf("</td>\n<td>\n");
		printf("%s",ck->name[ranking[i]]);
		printf("</td>\n<td>\n");
		printf("(%f)",ck->score[ranking[i]]*100);

		printf("</td>\n</tr>\n");
	}




	printf("</tbody>\n</table>\n");

	footer();

	printf("<a href=\"https://twitter.com/share\" class=\"twitter-share-button\" data-url=\"http://www.quickresponse.sakura.ne.jp/\"data-text=");

	printf("\"好感度ランキング！ ");
	for (i = 0; i < 3; i++){
		printf("第%d位:%s ",i+1,ck->name[ranking[i]]);
	}
	printf("\"");
	printf("data-lang=\"ja\" data-size=\"large\" data-hashtags=\"キャラクターソート\" data-dnt=\"true\">ツイート</a>	<script>!function(d,s,id){var js,fjs=d.getElementsByTagName(s)[0],p=/^http:/.test(d.location)?'http':'https';");
	printf("if(!d.getElementById(id)){js=d.createElement(s);js.id=id;js.src=p+'://platform.twitter.com/widgets.js';	fjs.parentNode.insertBefore(js,fjs);}}(document, 'script', 'twitter-wjs');</script>");


	printf("</BODY>\n");
	printf("</HTML>\n");

	return 0;
}
