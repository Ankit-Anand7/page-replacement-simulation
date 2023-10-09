#include "PAGE.h"
#include <stdlib.h>
#include <time.h>

// Random page replacement algorithm

void Random(PAGE_LIST* PRM) {
    page* current = PRM->headOfList;
    page* swapOutPage = PRM->headOfList;
    int counter = 0;
    int hits = 0;
    
    
    // Seed the random number generator
    srand(time(NULL));

    while (current) {
        if (current->pid > 0 && (rand() % 2 == 0)) {
            swapOutPage = current;
            hits++;
        }

        current = current->next;
        counter++;
    }

    swapOutPage->pid = -1;
    swapOutPage->PageNo = -1;

    // Calculates hit/miss ratio
    float ratio = (float)hits / (float)(counter);

    // Prints hit ratio
    printf("Hit ratio: %.2f\n", ratio);
}
