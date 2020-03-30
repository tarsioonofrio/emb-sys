#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
typedef void *(*state_func)();

//int inc0 = 0, inc1 = 0;
//int inb0 = 0, inb1 = 0;
int door0 = 0, door1 = 0;
int c, req;

int kbhit(void);
void *idle();
void *middle();
void *leave();

void *idle(){
	fprintf(stderr, "Idle user\n");
    door0 = 0;
    door1 = 0;
	if ((req == 1) | (req == 2)) return middle();
	return idle;
}

void *middle(){
	fprintf(stderr, "Locked in middle of gates, waiting officer action\n");
    door0 = 1;
    door1 = 1;
	if (req == 3)	return idle;
	if (req == 4)	return leave;
	return middle;
}

void *returning(){
    fprintf(stderr, "Returning to original local\n");
    door0 = 0;
    door1 = 1;
    if (req == 1) return idle();
    return returning;
}

void *leave(){
	fprintf(stderr, "Leave gate\n");
    door0 = 1;
    door1 = 0;
    if (req == 2) return idle;
	return leave;
}

int main(){
	state_func curr_state = idle;

	while(1){
		curr_state = (state_func)(*curr_state)();
		fprintf(stderr, "Locked door: %d %d\n", door0, door1);
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
