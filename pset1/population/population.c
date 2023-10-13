#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int begin = 0;
    int end = 0;
    int years = 0;
    // TODO: Prompt for start size
    do{
        begin = get_int("Start size: ");
    }while(begin < 9);

    // TODO: Prompt for end size
    do{
        end = get_int("End size: ");
    }while(end < begin);
    // TODO: Calculate number of years until we reach threshold
     while(end > begin){
        years+=1;
        begin = begin + begin / 3 - begin / 4;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}