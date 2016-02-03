#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "define.h"

int url_encode(char *s, int len);
int url_unreserved(char c);

/** reference to tororo7.jimdo.com/2014/02/08/url-c/ **/
int url_encode(char *s, int len) {
	int i, aftlen, ofst;
	char *s1;

	aftlen = 0;
	// get encoded size
	for (i = 0; i < len; ++i) {
		if (url_unreserved(s[i]))
			aftlen += 1;
		else
			aftlen += 3;
	}
	s1 = malloc(aftlen + 1);

	ofst = 0;
	for (i = 0; i < len; ++i) {
		if (url_unreserved(s[i]))
			s1[ofst++] = s[i];
		else
			ofst += sprintf(s1 + ofst, "%%%02X", (unsigned char) s[i]);
	}
	s1[ofst++] = '\0';
	/**
	 for (i = 0; i < ofst; i++){
	 s[i] = s1[i];
	 }
	 s[i] = "\0";
	 **/
	 strcpy(s, s1);
	 free(s1);

	 return 0;
	}

	int url_unreserved(char c) {
		if ('a' <= c && c <= 'z')
			return 1;
		if ('0' <= c && c <= '9')
			return 1;
		if ('A' <= c && c <= 'Z')
			return 1;
		if (c == '-' || c == '.' || c == '_' || c == '~')
			return 1;
		return 0;
	}

/** reference to www.ipa.go.jp
 /security/awareness/vendor/
 programmingv1/b06_03_main.html **/
/* デコード処理*/
/* len はs が保持するデータのサイズ*/
 int url_decode(char *s, int len) {
	int i, j, k; /* カウンタ類*/
	char buf, *s1; /* 作業領域*/

	s1 = malloc(len + 1);/* エラー処理は省略*/

 	for (i = 0, j = 0; i < len; i++, j++) {
 		if (s[i] == '+') {
 			s1[j] = ' ';
 			continue;
 		}
 		if (s[i] != '%') {
 			s1[j] = s[i];
 			continue;
 		}
 		buf = '\0';
 		for (k = 0; k < 2; k++) {
 			buf *= 16;
 			if ((s[++i] >= 'A') && (s[i] <= 'F'))
 				buf += (s[i] - 'A' + 10);
 			else if ((s[i] >= '0') && (s[i] <= '9'))
 				buf += (s[i] - '0');
 			else {
				/* 16 進数ではない */
 				free(s1);
 				return -1;
 			}
 		}
 		s1[j] = buf;
 	}

	/* 書き戻し*/
 	for (i = 0; i < j; i++) {
 		s[i] = s1[i];
 	}

 	s[i] = '\0';

 	free(s1);
	/* データ長と文字列長のチェックこの処理を追加*/
 	if (i != (int) strlen(s)) {
 		return -1;
 	}
 	return 0;
 }
