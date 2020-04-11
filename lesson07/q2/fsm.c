#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
typedef void *(*state_func)();

//int inc0 = 0, inc1 = 0;
//int inb0 = 0, inb1 = 0;
unsigned int door[4] = {0};
int speed = 0, lock_back_door = 0;
int c, req = -1, open_door = 0;
state_func prev_state;


int kbhit(void);
void *idle();
void *open();
void *back();
void *all();


void *idle(){
	fprintf(stderr, "Idle. Doors can be opened \n\n");

    prev_state = idle;

    fprintf(stderr, "lock_back_door % d\n\n", lock_back_door);
    fprintf(stderr, "req % d\n\n", req);

    if (lock_back_door == 1) return back;
	if (speed >= 30) return all;
    if ((req >= 1) & (req <= 4)) {
        open_door = req -1;
        return open;
    }

	return idle;
}

void *back(){
    fprintf(stderr, "Back doors locked\n");

    prev_state = back;

    if ((req == 1) | (req == 2)) {
        open_door = req - 1;
        return open;
    }
    if (lock_back_door == 0){
        return idle;
    }
    if (speed >= 30) return all;

	return back;
}

void *all(){
    fprintf(stderr, "All doors locked\n");

    prev_state = all;


    if (speed < 30)
    {
        if (lock_back_door == 1) return back;
        if (lock_back_door == 0) return idle;
    }
}


void *open(){
    fprintf(stderr, "Open door %d\n\n", req -1);

    door[open_door] = !door[open_door];

    return prev_state;
}


int main(){
	state_func curr_state = idle;

	while(1){
		curr_state = (state_func)(*curr_state)();
        fprintf(stderr, "Speed %d Km/h\n", speed);
		fprintf(stderr, "Opened doors:\n");
        fprintf(stderr, "\t  R L\n");
        fprintf(stderr, "\tF %d %d\n", door[0], door[1]);
        fprintf(stderr, "\tB %d %d\n", door[2], door[3]);
        fprintf(stderr, "\n\n");
		sleep(1);
		req = -1;
		if (kbhit()){
			c = getchar();
			if (c >= '0' && c <= '9') {
                req = c - 48;
                if (req == 6) lock_back_door = !lock_back_door;
                if (req == 7)
                    speed--;
                if (req == 8)
                    speed++;
                if (req == 9)
                    speed = speed - 5;
                if (req == 0)
                    speed = speed + 5;

            }
		}

    }
	return 0;
}
