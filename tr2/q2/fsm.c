#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
typedef void *(*state_func)();

//int inc0 = 0, inc1 = 0;
//int inb0 = 0, inb1 = 0;
int door[4] = {0};
int speed = 0, lock_back_door = 0;
int c, req = -1;
state_func prev_state;


int kbhit(void);
void *idle();
void *open();
void *back();
void *all();


void *idle(){
	fprintf(stderr, "Idle\n\n");

    prev_state = idle;
    //door[0] = 0;
    //door[1] = 0;
    //door[2] = 0;
    //door[3] = 0;

    if (lock_back_door == 1) return back;
	if (speed >= 30) return all;
    if ((req >= 1) & (req <= 4)) return open;

	return idle;
}

void *back(){
    fprintf(stderr, "Back doors locked\n");

    prev_state = back;
    //door[2] = 1;
    //door[3] = 1;

    if ((req == 1) | (req == 2)) return open;
    if (lock_back_door == 0){
        return idle;
    }
    if (speed >= 30) return all;

	return back;
}

void *all(){
    fprintf(stderr, "All doors locked\n");
    prev_state = all;

    //door[0] = 1;
    //door[1] = 1;
    //door[2] = 1;
    //door[3] = 1;

    if (speed < 30)
    {
        if (lock_back_door == 1) return back;
        if (lock_back_door == 0) return idle;
    }
}


void *open(){
    fprintf(stderr, "Open door %d\n\n", door[req -1]);
    door[req - 1] = ~door[req - 1];
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
        //if (kbhit() && !up_act && !down_act){
		if (kbhit()){
			c = getchar();
			if (c >= '0' && c <= '9') {
                req = c - 48;
                if (req == 6) ~lock_back_door;
                if (req == 7)
                    speed++;
                if (req == 8)
                    speed--;
                if (req == 9)
                    speed = speed + 5;
                if (req == 0)
                    speed = speed - 5;
            }
		}

    }
	return 0;
}
