#include "PAGE.h"

// LRU page replacement algorithm

void LRU(PAGE_LIST* pl) {
    page* current = pl->headOfList;
    page* swapOutPage = pl->headOfList;
    int lru = current->LONE;
    int hits = 0;
    int counter = 0;
    
    while (current) {
        if (current->LONE < lru) {    //compares the when the page was accessed last to implement the algorithm
            swapOutPage = current;
            lru = current->LONE;
            hits++;
           
        }


        current = current->next;
        counter++;
    }

    // if (DEBUG == 1) printf("EVICTED ones :: p[%03d] c:%02d l:%02f\n", swapOutPage->pid, swapOutPage->counter, swapOutPage->LONE);
    swapOutPage->pid = -1;
    swapOutPage->PageNo = -1;
     
     
    // Calculates hit ratio
    float ratio = (float)hits / (float)(counter);

    // Prints hit ratio
    printf("Hit ratio: %.2f\n", ratio);
}
