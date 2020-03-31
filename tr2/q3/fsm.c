#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

typedef void *(*state_func)();

unsigned int door[4] = {0};
int c, req = -1;
int speed = 0, roll=0;
int button = 0;
clock_t start_t, end_t, total_t;
//state_func prev_state;


int kbhit(void);
void *idle();
void *active();
void *wait();
void *eval();
void *eject();


void *idle(){
    fprintf(stderr, "Idle. Doors can be opened\n");

    if (button == 1) return active;
    return idle;
}

void *activate(){
    fprintf(stderr, "Ejection system activated\n");

    button = 0;
    start_t = clock();
    return wait;
}

void *wait(){
    fprintf(stderr, "All doors locked\n");
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    if (button == 1) return eval;
    return wait;

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
                if (req == 0) button = 1;
                if (req == 1)
                    speed = speed + 100;
                if (req == 2)
                    roll = roll - 100;
                if (req == 3)
                    roll = roll + 100;
                if (req == 4)
                    roll = roll - 100;

            }
        }

    }
    return 0;
}
