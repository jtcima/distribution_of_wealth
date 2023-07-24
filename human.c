#include "human.h"

int isEscapePressed() {
    struct termios oldAttr, newAttr;
    tcgetattr(STDIN_FILENO, &oldAttr);
    newAttr = oldAttr;
    newAttr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newAttr);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldAttr);

    if (ch == 27) // ASCII value of the Escape key is 27
        return 1;
    return 0;
}


//create a human test subject
struct Human create_human(int _id, int iq_class, int max_iq)
{
    struct Human human;
    human.id = _id;
    human.iq = rand()%(max_iq-iq_class+1) + iq_class;
    human.wealth = 10.0;
    return human;
}

//create batch of humans test subjects
int create_human_dataset()
{
    int n = 0;
    //iq >= 130, datasize*2.3/100
    for(int i = 0; i < HUMAN_SIZE*2/100; i++)
    {
        if((HUMAN_SIZE - n) >= 0)
        {
            humans[n] = create_human(n, 130, 200);
            n++;
        }
    }

    //iq <=129 and iq >= 120, datasize*7/100
    for(int i = 0; i < HUMAN_SIZE*7/100; i++)
    {
        if((HUMAN_SIZE - n) >= 0)
        {
            humans[n] = create_human(n, 120, 129);
            n++;
        }
    }

    //iq <=119 and >=110, datasize*17/100
    for(int i = 0; i < HUMAN_SIZE*17/100; i++)
    {
        if((HUMAN_SIZE - n) >= 0)
        {
            humans[n] = create_human(n, 110, 119);
            n++;
        }
    }

    //iq <=109 and >=90, datasize*50/100
    for(int i = 0; i < HUMAN_SIZE*50/100; i++)
    {
        if((HUMAN_SIZE - n) >= 0)
        {
            humans[n] = create_human(n, 90, 109);
            n++;
        }
    }

    //iq <=89 and >=80, datasize*16/100
    for(int i = 0; i < HUMAN_SIZE*16/100; i++)
    {
        if((HUMAN_SIZE - n) >= 0)
        {
            humans[n] = create_human(n, 80, 89);
            n++;
        }
    }

    //iq <=79 and >=70, datasize*6/100
    for(int i = 0; i < HUMAN_SIZE*6/100; i++)
    {
        if((HUMAN_SIZE - n) >= 0)
        {
            humans[n] = create_human(n, 70, 79);
            n++;
        }
    }

    //iq <=70, datasize*2/100
    for(int i = 0; i < HUMAN_SIZE*2/100; i++)
    {
        if((HUMAN_SIZE - n) >= 0)
        {
            humans[n] = create_human(n, 0, 70);
            n++;
        }
    }
    return 0;
}

float calculate_mean()
{
    float total_iq;
    for (int i = 0; i < HUMAN_SIZE; i++)
    {
        total_iq += humans[i].iq;
    }

    return total_iq/HUMAN_SIZE;
}

struct Luck create_luck(bool _good)
{
    struct Luck luck;
    luck.id = rand()%HUMAN_SIZE;
    luck.chance = rand()%2 + 1;
    luck.isGood = _good;

    return luck;
}

int create_lucks()
{
    int n = 0;

    //create good luck
    for (int i = 0; i < LUCK_SIZE/2; i++)
    { 
        lucks[n] = create_luck(1);
        n++;
    }

    for (int i = 0; i < LUCK_SIZE/2; i++)
    { 
        if((LUCK_SIZE - n) >= 0)
        {
            lucks[n] = create_luck(0);
            n++;
        }
        
    }
    return 0;
}

void apply_luck_to_human(float mean)
{

    for (int i = 0; i < HUMAN_SIZE; i++)
    {
        for(int n = 0; n < LUCK_SIZE; n++)
        {
            if(humans[i].id == lucks[n].id)
            {
                float wealth = humans[i].wealth;
                uint32_t iq = humans[i].iq;

                if(lucks[n].isGood == 1)
                {
                    if(iq > mean)
                    {
                        humans[i].wealth = wealth + (wealth*iq/MAX_IQ*(iq-mean)/100)*lucks[n].chance;
                    }
                    if(iq < mean)
                    {
                        humans[i].wealth = wealth + (wealth*iq/MAX_IQ*(1-fabs(iq-mean)/100)*(1-fabs(iq-mean)/100)/100)*lucks[n].chance;
                    }
                }

                if(lucks[n].isGood == 0)
                {
                    humans[i].wealth = wealth/2;
                }
            }
        }
    }
    return;
}