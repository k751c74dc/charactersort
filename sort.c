#include "cookie.h"
#include "design.h"

void main(int argc, char *argv[]) {
	Cookie *ck;

	ck = (Cookie *) malloc(sizeof(Cookie));

	init_cookie(ck);
	/** Cookieを読み込み **/
	get_cookie(ck);

	/** ソートさせます **/
	int i, j;
	float rank_vector[ck->amount];
	float temp_vector[ck->amount];
	float RANDOMWALK_RATIO = 0.15;
	int count = 0;
	int loopcount = 0;
	int tmp = 0;
	/* init rank_vector */

	for (i = 0; i < ck->amount; i++) {
		for (j = 0; j < ck->amount; j++) {
			tmp = tmp + ck->registeredLink[j][i];
		}
		for (j = 0; j < ck->amount; j++) {
			if (tmp == 0) {
				break;
			} else {
				ck->registeredLink[j][i] = ck->registeredLink[j][i] / tmp;
			}
		}
	}

	for (i = 0; i < ck->amount; i++) {
		rank_vector[i] = 1.0 / ck->amount;
	}
	do {
		/* compute next rank_vector */
		for (i = 0; i < ck->amount; i++) {
			temp_vector[i] = 0;
			for (j = 0; j < ck->amount; j++) {
				temp_vector[i] += rank_vector[j] * ck->registeredLink[i][j];
			}
			temp_vector[i] = (1.0 - RANDOMWALK_RATIO) * temp_vector[i] + RANDOMWALK_RATIO * (1.0 / ck->amount);
			/* replace (1.0/N_PAGES) to rank_vector[i] and see what happens! */
		}
		/* compute residual = ||temp_vector - rank_vector|| here ! */
		for (i = 0; i < ck->amount; i++) {
			if ((temp_vector[i] - rank_vector[i] <= 0.0000001) && (temp_vector[i] - rank_vector[i] >= -0.0000001)) {
				count++;
			} else {
				count = 0;
				break;
			}
		}
		if (count > 3 * ck->amount) {
			break;
		}

		/* reflect to current rank_vector */
		for (i = 0; i < ck->amount; i++) {
			rank_vector[i] = temp_vector[i];
		}
		loopcount++;
	} while (loopcount < 100);

	/* print result */
	/*  printf("----------\nloopcount : %d\n",loopcount);
	 for( i = 0; i < ck->amount; i++ ) {
	 printf("Page %d:%f\n",i,rank_vector[i]);
	 }
	 printf("----------\n");
	 */

	for (i = 0; i < ck->amount; i++) {
		ck->score[i] = rank_vector[i];
	}

	/*
	 for( i = 1; i < ck->amount; i++ ) {
	 j = i;
	 while(j >= 1 && rank_vector[j-1] - rank_vector[j] < 0) {
	 tmp = ck->score[j];
	 ck->score[j] = ck->score[i];
	 ck->score[i] = tmp;
	 j--;
	 }
	 }
	 */
	/** 結果をCookieのranking[]に出力させます　**/

	printf("Content-type:text/html\n");
	set_cookie(ck);

	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n");
	printf("<META HTTP-EQUIV=\"Refresh\" CONTENT=\"0; URL=result.cgi\">\n");
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
