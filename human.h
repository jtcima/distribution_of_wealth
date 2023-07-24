#ifndef HUMAN_H
#define HUMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <termios.h>


#define HUMAN_SIZE 100
#define LUCK_SIZE HUMAN_SIZE/2
#define MAX_IQ 200

struct Human
{
    uint32_t id;
    uint32_t iq;
    float wealth;    
};

struct Luck
{
    uint32_t id;
    uint32_t chance;
    bool isGood;
};

struct Luck lucks[LUCK_SIZE];
struct Human humans[HUMAN_SIZE];
struct Human create_human(int _id, int iq_class, int max_iq);
int create_human_dataset();
float calculate_mean();
int create_lucks();
struct Luck create_luck(bool _good);
void apply_luck_to_human(float mean);
int isEscapePressed();

//good luck
//if iq > mean
//new_wealth = org_wealth+(iq/max_iq * org_wealth*abs((iq-mean))/100)*chances
//if iq < mean
//new_wealth = org_wealth*chances+(iq/max_iq * org_wealth*chances*abs((1-abs((iq-mean)))/100*(1-abs((iq-mean))/100)/100))
//new_wealth = org_wealth*0.5


#endif