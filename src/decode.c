#include "decode.h"
#include "string.h"
#include "stdio.h"


decoded getresults (char *code) {
	decoded temp;
	char header[20];
	char varible[20];
	sscanf(code,"%s %s",header,varible);
	if(!strcmp(header,cmd_move)) {
			temp.cmd = make_move;
			strcpy(temp.var,varible);
	}
	return temp;
}