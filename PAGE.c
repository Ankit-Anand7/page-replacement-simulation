#include "PAGE.h"


//function to initialise all pages and store in a linked list

void initialize_all_pages(PAGE_LIST* pl) {
    pl->headOfList = malloc(sizeof(page));
    page* it = pl->headOfList;
    int i;
    for(i=0;i<TOTAL_PAGE;i++) {
        it->pid = -1; it->PageNo = -1;
        it->next = NULL;
        if(i < 99) {
            it->next = malloc(sizeof(page));
            it = it->next;
        }
    }
}

// function to display all pages and memory map for them

void disp_page(PAGE_LIST* pl) {
    
    
       page* it = pl->headOfList;
        int cnt = 0;
        while (it) {
            if (it->pid > 0) {
                printf("|%c|", 'A' + (it->pid % 26)); // Display process name
            } else {
                printf(".");
            }
            cnt++;
            if ((cnt % 10) == 0) printf("\n");
            it = it->next;
        }
        printf("\n");
    }
   



// Function to find free pages in memory

int find_free_pages(PAGE_LIST* pl,int counter) {
    page* it = pl->headOfList;
    while(it) {
        if(it->pid == -1) { // page is not in use or taken by any process;
            counter--;
        }
        if(!counter) return 1;
        it = it->next;
    }
    return 0;
}

//Function to check if the page is in memory

int if_page_present_in_memory(PAGE_LIST* pl,int pid,int PageNo) {
    page* it = pl->headOfList;
    while(it) {
        if(it->pid == pid && it->PageNo == PageNo) return 1;
        it = it->next;
    }
    return 0;
}

//Function to search available pages in memory, -1 indicates page is available

page* register_page(PAGE_LIST* pl) {
    page* it = pl->headOfList;
    while(it) {
        if(it->pid == -1) return it;
        it = it->next;
    }
    return NULL;
}


//Function to free the memory occupied by the process

void release_memory(PAGE_LIST* pl,int pid) {
    page* it = pl->headOfList;
    while(it) {
        if(it->pid == pid) {
            it->pid = -1;
            it->PageNo = -1;
        }
        it = it->next;
    }
}


//Function to make reference to next page keeping in mind the given locality of reference

int find_next_page(int curr_page_no,int max_page_size) {
    int x = rand()%10;
    if(x < 7) {
        x = curr_page_no+(rand()%3)-1 < 0;
    } else {
        x = rand()%max_page_size;
        while(abs(x-curr_page_no) <= 1) x = rand()%max_page_size;
    }
    if(x < 0) x = 0;
    if(x >= 100) x = max_page_size-1;
    return x;
}


// Function to search specific pages which are free

page* next_free_page_id(PAGE_LIST* pl,int pid,int PageNo) {
    page* it = pl->headOfList;
    while(it) {
        if(it->pid == pid && it->PageNo == PageNo) return it;
        it = it->next;
    }
    return NULL;
}



// Function to sort all processes based on their arrival time

int compare_ToA(const void* a,const void* b) {
    return ((process*)a)->arrivalTime - ((process*)b)->arrivalTime;
}
