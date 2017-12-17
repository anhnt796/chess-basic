#ifndef _decode_h_
#define _decode_h_
static const char* cmd_move = "MOVE"; static const int make_move = 1;
static const char* cmd_new = "NEW"; static const int make_new = 2;
static const char* cmd_draw = "DRAW"; static const int make_draw = 3;

// Thạch
static const char* cmd_pcolor = "PCLR"; static const int make_pcolor = 4;

typedef struct
{
	int cmd;
	char var[4];	
} decoded; 
#endif