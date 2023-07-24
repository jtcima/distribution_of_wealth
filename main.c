#include "human.c"

int main(void)
{
    srand(time(NULL));
    
    create_human_dataset();
    float mean = calculate_mean();
    while(1)
    {
        create_lucks();
        apply_luck_to_human(mean);
        if(isEscapePressed())
        {
            printf("%.2f\n", mean);
            for(int i = 0; i < HUMAN_SIZE;i++)
            {
                printf("id: %u, iq: %u, wealth: %.2f\n",humans[i].id, humans[i].iq, humans[i].wealth);
            }
            printf("*************************************\n");
        }
    };

    return 0;
}