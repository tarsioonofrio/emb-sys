#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
typedef void *(*state_func)();

//int inc0 = 0, inc1 = 0;
//int inb0 = 0, inb1 = 0;
int door0 = 0, door1 = 0, first_door = -1;
int c, req = -1;

int kbhit(void);
void *idle();
void *middle();
void *leave();

void *idle(){
	fprintf(stderr, "Idle user\n\n");
    door0 = 0;
    door1 = 0;
    first_door = req;
	if ((req == 1) | (req == 2)) return middle;
	return idle;
}

void *middle(){
    if (first_door == 1) fprintf(stderr, "User went through the outside door\n");
    else fprintf(stderr, "User went through the inside door\n");

    fprintf(stderr, "Locked in middle of gates, waiting officer action. PRESS 1 to unlock outside door or PRESS 2 to unlock inside door\n\n");

    door0 = 1;
    door1 = 1;
    if (first_door == 1) {
        if (req == 1) {
            //fprintf(stderr, "***");
            return idle;
        }
        if (req == 2) return leave;
    }
    else if (first_door == 2){
        if (req == 2) return idle;
        if (req == 1) return leave;
    }
	return middle;
}

void *returning(){
    if (first_door == 1) fprintf(stderr, "User came back through the outside door\n\n");
    else fprintf(stderr, "User came back through the inside door\n\n");

    if (first_door == 1) {
        door0 = 0;
        door1 = 1;
        if (req == 1) return idle;
    }
    else if (first_door == 2){
        door0 = 1;
        door1 = 2;
        if (req == 2) return idle;
    }
    return returning;
}

void *leave(){
    if (first_door == 1) fprintf(stderr, "User can leave the gate when going through the outside door, press 2\n\n");
    else fprintf(stderr, "User can leave the gate when going through the inner door, press 1\n\n");

    if (first_door == 1) {
        door0 = 1;
        door1 = 0;
        if (req == 2) {
            fprintf(stderr, "User left the gate\n\n");
            return idle;
        }
    }
    else if (first_door == 2){
        door0 = 0;
        door1 = 1;
        if (req == 1) {
            fprintf(stderr, "User left the gate\n\n");
            return idle;
        }
    }
	return leave;
}

int main(){
	state_func curr_state = idle;

	while(1){
		curr_state = (state_func)(*curr_state)();
		fprintf(stderr, "Locked door: Inside %d, Outside %d\n", door0, door1);
		sleep(1);
		req = -1;
        //if (kbhit() && !up_act && !down_act){
		if (kbhit()){
			c = getchar();
			if (c >= '0' && c <= '9')
				req = c - 48;

		}
    }
	return 0;
}
