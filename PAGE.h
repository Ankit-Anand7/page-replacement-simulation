#ifndef PAGING_H   //preprocessor directives
#define PAGING_H

#define DEBUG -1

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


//Macros

#define TOTAL_NO_OF_PROCESSES 150
#define TOTAL_DURATION 60
#define PROCESS_DURATION 6
#define TOTAL_PAGE 100

extern int clockSimulation;
extern int *pagingOptions;


//Defining process structure
typedef struct {
    int pid, pageSize, arrivalTime, duration, currPage;
} process;


//Defining page structure 

typedef struct page {
    int pid;
    int PageNo;
    struct page* next;

    float FTBOUGHT;  //time when page brought into the memory(fault time)
    float LONE;   //time when page was last accessed
    int counter;
} page;


//Linked list to store pages

typedef struct {
    page* headOfList;
} PAGE_LIST;

// Function to find pages which are free, defined in PAGE.c
int find_free_pages(PAGE_LIST*,int);


//Function to check if the page is in memory,  defined in PAGE.c
int if_page_present_in_memory(PAGE_LIST*,int,int);


//Function to search available pages in memory, -1 indicates page is available, defined in PAGE.c
page* register_page(PAGE_LIST*);


//Function to free the memory occupied by the process, defined in PAGE.c
void release_memory(PAGE_LIST*,int);


//function to initialise all pages and store in a linked list, defined in PAGE.c
void initialize_all_pages(PAGE_LIST*);


// function to display all pages and memory map for them, defined in PAGE.c
void disp_page(PAGE_LIST*);



//Function to make reference to next page keeping in mind the given locality of reference, defined in PAGE.c
int find_next_page(int,int);


// Function to sort all processes based on their arrival time, defined in PAGE.c
int compare_ToA(const void* ,const void*);


// Function to search specific pages which are free, defined in PAGE.c
page* next_free_page_id(PAGE_LIST*,int,int);


//Page replacement algorithm declarations, definitions in their respective files

void FCFS(PAGE_LIST*);
void LRU(PAGE_LIST*);
void Random(PAGE_LIST*);



#endif
