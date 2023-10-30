#include "@base.h"



void ColorTerm::setColor(FILE *std_type, int attr, int fg, int bg)
{	
  
        char command[100]={0};

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	fprintf(std_type,"%s", command);
}

void ColorTerm::resetColor(FILE *std_type)
{
    int attr = ColorTerm::RESET;
    int fg = ColorTerm::BLACK;
    int bg= ColorTerm::WHITE;
  
        char command[13];

	/* Command is the control command to the terminal */
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	fprintf(std_type,"%s", command);
}
