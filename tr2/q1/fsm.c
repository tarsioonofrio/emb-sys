#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
typedef void *(*state_func)();

int inc0 = 0, inc1 = 0;
int inb0 = 0, inb1 = 0;
int out0 = 0, out1 = 0;
int c;

int kbhit(void);
void *idle();
void *entering();
void *middle();
void *waiting();
void *closing();

void *idle(){
	fprintf(stderr, "idle ");
    out0 = 0;
    out1 = 0;
	if (inc0 == 0)	return idle;
	if (inc0 == 1)	return entering;
	return 0;
}

void *entering(){
	fprintf(stderr, "entering ");
    out0 = 0;
    out1 = 1;
	if (inc0 == 1)	return entering;
	if (inc0 == 0)	return idle;
	return 0;
}

void *middle(){
	fprintf(stderr, "middle ");
    out0 = 1;
    out1 = 1;
	if (inb1 == 0)	return middle;
	if (inb1 == 1)	return waiting;
	return 0;
}
void *waiting(){
    fprintf(stderr, "waiting ");
    out0 = 1;
    out1 = 0;
    if (inc1 == 1)	return waiting;
    if (inc1 == 0)	return closing;
    return 0;
}
void *closing(){
	fprintf(stderr, "closing ");
    out0 = 1;
    out1 = 0;
    if (inc1 == 0)	return waiting;
    if (inc1 == 1)	return closing;
	return 0;
}

int main(){
	state_func curr_state = idle;

	while(1){
		curr_state = (state_func)(*curr_state)();
		fprintf(stderr, "out0 %d out1 %d\n", out0, out1);
		sleep(1);
        //if (kbhit() && !up_act && !down_act){
		if (kbhit()){
			c = getchar();
			if (c >= '0' && c <= '9')
				req = c - 48;
		}
	}
	
	return 0;
}
