#include "PAGE.h"

//FIFO page replacement algorithm 

void FCFS(PAGE_LIST *pl)
{
    page *current = pl->headOfList;
    page *swap_out_page = pl->headOfList;
    int counter = 0;
    int hits = 0;

    while (current)
    {
        if (current->FTBOUGHT < swap_out_page->FTBOUGHT)  //compares last page fault time to swap 
        {
            swap_out_page = current;
           hits++;
        }
        current = current->next;
        counter++;
    }
    // if (DEBUG == 1)
    //     printf("EVICTED ones :: p[%03d] c:%02d l:%02f\n", swap_out_page->pid, swap_out_page->counter, swap_out_page->LONE);
    swap_out_page->pid = -1;
    swap_out_page->PageNo = -1;

    // Calculates hitratio
    float ratio = (float)hits / (float)(counter);

    // Prints hit ratio
    printf("Hit ratio: %.2f\n", ratio);
}
