#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * The while loop represents the game.
 * Each iteration represents a turn of the game
 * where you are given inputs (the heights of the mountains)
 * and where you have to print an output (the index of the mountain to fire on)
 * The inputs you are given are automatically updated according to your last actions.
 **/

int main()
{
    while(1){
        int mmax= 0;
        int index = 0;

        for(int i = 0; i<8 ; i++){
            int motn;
            scanf("%d", &motn);
            if(motn > mmax){
                mmax = motn;
                index = i;
            }
        }
        printf("%d\n", index);
    }

    return 0;
}