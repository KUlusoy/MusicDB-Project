#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "musicdb.h"

int main()
{

    int idLastFour = 6011;
    // calculate a, b, etc rest of stuff in the requirements
    int a = (idLastFour / 10) % 10;
    int b = (idLastFour % 10);
    int S = (a + 2 * b) % 4;
    int T = b % 5;
    int D = a % 5;
    int L = (a + b) % 4;
    // displays
    printf("ENEB340 REPORT\n");
    printf("card: L=%d, D= %d, T= %d, S =  %d\n", L, D, T, S);
    return 0;
}