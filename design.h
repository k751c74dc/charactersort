#include <stdio.h>

int header();
int footer();
int err();

int header(){

	return 0;
}

int footer(){
	return 0;
}

int err(){
	printf("Content-type:text/html\n\n");
	printf("<HTML>\n");
	printf("<HEAD>\n");
	printf("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
	printf("<TITLE>Error</TITLE>\n");
	printf("</HEAD>\n");
	printf("<BODY>\n");
	printf("error!");
	printf("</BODY>\n");
	printf("</HTML>\n");
	return 0;
}