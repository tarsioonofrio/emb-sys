#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef void *(*state_func)();

unsigned int door[4] = {0};
int c, req = -1;
int speed = 0, roll=0;
int button = 0;
clock_t start_t;
double total_time = 0;
//state_func prev_state;
char string_state[256];

int kbhit(void);
void *idle();
void *activate();
void *wait();
void *eval();
void *eject();


void *idle(){
    sprintf(string_state, "%s", "Idle. Ejection system not activated.");

    if (button == 1) return activate;
    return idle;
}

void *activate(){
    sprintf(string_state, "%s", "Ejection system activated.");

    button = 0;
    start_t = clock();
    return wait;
}

void *wait(){
    total_time = (double)(clock() - start_t) / CLOCKS_PER_SEC;
    sprintf(string_state, "%s %f seconds", "Waiting for button to be pressed again.", total_time);

    if ((button == 1) & (total_time <= 1)) {
        fprintf(stderr, "oi\n");
        return eval;
    }
    if (total_time > 1) {
        total_time = 0;
        return idle;
    }

    return wait;
}

void *eval(){
    sprintf(string_state, "%s", "Evaluation ejection avionic conditions.");

    if ((roll < 60) & (roll > -60))  {
        return eject;
    }
    return activate;
}

void *eject(){
    sprintf(string_state, "%s", "Seat ejected.");

    if ((roll > 60) & (roll < -60))  {
        return eject;
    }
    return activate;
}

int main(){
    state_func curr_state = idle;

    while(1){
        curr_state = (state_func)(*curr_state)();
        fprintf(stderr, "Speed %d Km/h | Roll %d | Warning: %s\n", speed, roll, string_state);
        sleep(1);
        req = -1;
        if (kbhit()){
            c = getchar();
            if (c >= '0' && c <= '9') {
                req = c - 48;
                if (req == 0) button = 1;
                if (req == 1)
                    speed = speed + 10;
                if (req == 2)
                    speed = speed - 10;
                if (req == 3)
                    roll++;
                if (req == 4)
                    roll--;
            }
        }
    }
    return 0;
}
