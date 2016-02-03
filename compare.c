#include "url.h"
#include "cookie.h"
#include "design.h"

void main(int argc, char *argv[]) {
	int i, j, len, select;
	int right, left, row, column;
	char c;
	char *pBuf;
	char ctmp[MAX_CHAR], Rname[MAX_CHAR], Lname[MAX_CHAR];
	Cookie *ck;

	ck = (Cookie *) malloc(sizeof(Cookie));

	init_cookie(ck);

	/** Cookieを読み込み **/
	get_cookie(ck);

	len = atoi(getenv("CONTENT_LENGTH"));

	/** フォームデータをget **/
	/** もしなかったら(初めの状態)，最初ってこと **/
	pBuf = (char *) malloc(len + 1);
	if (pBuf == NULL) {
		err();
		return;
	}
	/**データを受け取る。**/
	//このとき改行文字等は除外しないと後で思わぬエラーが生じる
	for (i = 0; (c = getchar()) != EOF; i++) {

		if (c != '\r' && c != '\n')
			pBuf[i] = c;
		else
			i--;
	}
	//送られてきたデータの最後にはヌル文字がないので自分で付ける
	pBuf[i] = '\0';

	//生データから欲しいデータの文字列を切り分ける
	getstring(pBuf, "LEFT", ctmp);
	left = atoi(ctmp);
	getstring(pBuf, "RIGHT", ctmp);
	right = atoi(ctmp);
	getstring(pBuf, "ROW", ctmp);
	row = atoi(ctmp);
	getstring(pBuf, "COLUMN", ctmp);
	column = atoi(ctmp);

	/** フォームデータからCookie(データ構造)を上書きする **/
	if (column != row) {
		if (left == 1)
			ck->registeredLink[column][row] = 1;
		if (right == 1)
			ck->registeredLink[row][column] = 1;
	}
	if (left == 1 || right == 1)
		row++;

	select = 0;
	if (column == row) {
		row = 0;
		column++;
		if (column >= ck->amount)
			select = 1;
	}

	printf("Content-type:text/html\n");
	/** cookieに出力 **/
	set_cookie(ck);
	printf("\n");

	/** 全て埋まったら，sort.cにリダイレクト **/
	if (select == 1) {
		printf("<HTML>\n");
		printf("<HEAD>\n");
		printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
		printf("<TITLE>完了!</TITLE>\n");
		printf("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=sort.cgi \" />");
		printf("<link href=\"css/bootstrap.min.css\" rel=\"stylesheet\">\n");
		printf("</HEAD>\n");
		printf("</HTML>\n");
	} else {
		printf("<HTML>\n");
		printf("<HEAD>\n");
		printf(
			"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
		printf("<TITLE>どっちがいい?</TITLE>\n");
		printf("<link href=\"css/bootstrap.min.css\" rel=\"stylesheet\">\n");
		printf("</HEAD>\n");
		printf("<BODY>\n");
		header();

		/** 隠しフォーム形式で 比較を **/
		printf("[%d][%d]left:%d right:%d<p>", column, row, left, right);
		printf("<table><tr>");
		strcpy(Lname, ck->name[column]);
		url_decode(Lname, strlen(Lname));
		setnewLine(Lname);
		printf("<td><FORM METHOD=\"POST\" ACTION=\"compare.cgi\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"LEFT\" value=\"1\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"RIGHT\" value=\"0\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"COLUMN\" value=\"%d\">", column);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"ROW\" value=\"%d\">", row);
		printf("<INPUT TYPE=\"SUBMIT\" class=\"btn btn-default btn-block\" style=\"width:360px; height:220px; font-size:40pt\" VALUE=\"%s\">",Lname);
		printf("</FORM></td>");

		printf("<td><FORM METHOD=\"POST\" ACTION=\"compare.cgi\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"LEFT\" value=\"1\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"RIGHT\" value=\"1\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"COLUMN\" value=\"%d\">", column);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"ROW\" value=\"%d\">", row);
		/*printf("<INPUT TYPE=\"SUBMIT\" VALUE=\"引き分け\"><P>");*/
		printf("</FORM></td>");

		printf("<td><FORM METHOD=\"POST\" ACTION=\"compare.cgi\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"LEFT\" value=\"0\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"RIGHT\" value=\"0\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"COLUMN\" value=\"%d\">", column);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"ROW\" value=\"%d\">", row);
		/*printf("<INPUT TYPE=\"SUBMIT\" VALUE=\"どちらも知らない\"><P>");*/
		printf("</FORM></td>");


		strcpy(Rname, ck->name[row]);
		url_decode(Rname, strlen(Rname));
		setnewLine(Rname);
		printf("<td><FORM METHOD=\"POST\" ACTION=\"compare.cgi\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"LEFT\" value=\"0\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"RIGHT\" value=\"1\">");
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"COLUMN\" value=\"%d\">", column);
		printf("<INPUT TYPE=\"HIDDEN\" NAME=\"ROW\" value=\"%d\">", row);
		printf("<INPUT TYPE=\"SUBMIT\" class=\"btn btn-default btn-block\" style=\"width:360px; height:220px; font-size:40pt\" VALUE=\"%s\"><P>",Rname);
		printf("</FORM></td>");
		printf("</tr></table>");
		/** 自身(compare.cgi)に送信 **/

		for (i = 0; i < ck->amount; i++) {
			for (j = 0; j < ck->amount; j++) {
				printf("|[%d][%d]=%f|", i, j, ck->registeredLink[i][j]);
			}
			printf("<p>");

		}
		footer();
		printf("</BODY>\n");
		printf("</HTML>\n");
	}

	return;
}
int setnewLine(char *src){
	int len =12;
	if(strlen(src)<len)return -1;
	char src2[100];
	char src3[100]="\n";
	int i,j;
	j=1;
	for(i = len;src[i] != '\0';i++){
		src3[j] = src[i];
		j++;
	}
	strncpy(src2,src,len);
	strcat(src2,src3);
	printf("%s %s %s<p>",src,src2,src3);
	strcpy(src,src2);
	return 0;
}
int getstring(char *src, char *element, char *dest) {
	int len;
	char *data, *amp;
	char *temp;

	len = (int) strlen(src) + 1;
	temp = (char *) malloc(len);

	len = (int) strlen(src);
	if (len >= 1024) {
		err();
		free(temp);
		return -1;
	}

	strcpy(temp, src);

	data = strstr(temp, element);
	if (data == NULL) {
		strcpy(dest, "no element");
		free(temp);
		return -2;
	}

	len = (int) strlen(element) + 1;

	amp = strstr(data, "&");
	if (amp == NULL) {
		strcpy(dest, data + len);
		if (dest[0] == '\0') {
			strcpy(dest, "no data");
			free(temp);
			return 0;
		}
		free(temp);
		return 1;
	}
	data[(int) (amp - data)] = '\0';
	strcpy(dest, data + len);

	if (dest[0] == '\0') {
		strcpy(dest, "no data");
		free(temp);
		return 0;
	}

	free(temp);
	return 0;
}