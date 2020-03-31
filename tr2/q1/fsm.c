#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
typedef void *(*state_func)();

//int inc0 = 0, inc1 = 0;
//int inb0 = 0, inb1 = 0;
unsigned int door[2] = {0};
unsigned int user[3] = {0};

int first_door = -1;
int c, req = -1;
state_func prev_state;


int kbhit(void);
void *idle();
void *middle();
void *door1();
void *door2();

void *idle(){
	fprintf(stderr, "Idle. PRESS 1 to try to get into the bank using external door or PRESS 2 to try to get out on the bank using internal door.\n\n");
    door[0] = 0;
    door[1] = 0;

    user[0] = 0;
    user[1] = 0;
    user[2] = 0;
    first_door = req;
	if ((req == 1) | (req == 2)) return middle;
	return idle;
}

void *middle(){
    fprintf(stderr, "Locked in middle of gates, waiting officer action. Officer PRESS 3 to unlock external door or PRESS 4 to unlock internal door\n\n");

    door[0] = 1;
    door[1] = 1;

    user[0] = 0;
    user[1] = 1;
    user[2] = 0;

    if (req == 3) return door1;
    if (req == 4) return door2;
	return middle;
}

void *door1(){
    fprintf(stderr, "User can leave the gate when going through the outside door, PRESS 1 to get into the street.\n\n");

    door[0] = 1;
    door[1] = 0;

    user[0] = 1;
    user[1] = 0;
    user[2] = 0;

    if (req == 1) {
        fprintf(stderr, "User left the gate\n\n");
        return idle;
    }
	return door1;
}

void *door2(){
    fprintf(stderr, "User can leave the gate when going through the inner door, PRESS 2 to get enter the bank.\n\n");

    door[0] = 0;
    door[1] = 1;

    user[0] = 0;
    user[1] = 0;
    user[2] = 1;

    if (req == 2) {
        fprintf(stderr, "User left the gate\n\n");
        return idle;
    }
    return door2;
}
int main(){
	state_func curr_state = idle;

	while(1){
		curr_state = (state_func)(*curr_state)();
		//fprintf(stderr, "Locked door: Inside %d, Outside %d\n", door[0], door[1]);
        fprintf(stderr, "Place\tUser\tDoor1\tUser\tDoor2\tUser\tPlace\n");
        fprintf(stderr, "Street\t%d\t%d\t%d\t%d\t%d\tBank\n", user[0], door[0], user[1], door[1], user[2]);
        fprintf(stderr, "\n");
		sleep(1);
		req = -1;
		if (kbhit()){
			c = getchar();
			if (c >= '0' && c <= '9')
				req = c - 48;

		}
    }
	return 0;
}
