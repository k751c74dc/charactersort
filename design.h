#include <stdio.h>

int header();
int footer();
int err();

int header(){
	printf("<div class=\"container-fluid\">\n");
	return 0;
}

int footer(){
	printf("</div>\n");
	printf("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js\"></script>\n");
	printf("<script src=\"js/bootstrap.min.js\"></script>\n");
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
