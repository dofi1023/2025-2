#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    // the number of temperatures to analyse
    int n;
    int min = 5526;
    int arr[10000];
    int index;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        // a temperature expressed as an integer ranging from -273 to 5526
        scanf("%d", &arr[i]);
    }

    for(int i = 0; i<n;i++){
        if(arr[i] < 0) {
            if((arr[i] * -1) < min) {
                min = arr[i] * -1;
                index = i;
            }
        }
        else {
            if(arr[i] <= min){
                min = arr[i];
                index = i;
            }
        }
    }

    printf("%d\n", arr[index]);
    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    return 0;
}