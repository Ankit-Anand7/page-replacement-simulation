# page-replacement-simulation
Implemented page replacement algorithms (FIFO, LRU, Random) from memory management concepts of Operating Systems in C for simulating process execution, achieving an average hit/miss ratio of pages referenced by running jobs and successfully swapping in an average of [number] processes during each minute-long simulation.




#Introduction
-------------

We have written the program in C language and have successfully generated 150 processes satisfying given conditions in the assignment. We didn't made any system calls to generate any process.


#Workload Generation
--------------------
We generated 150 processes with the below details: <process name, process size in pages, arrival time, service duration>. The processes were randomly generated and even size distribution (among 5,11,17,31MB) was done by us.The service duration, too, was randomly generated and distributed to processes. The durations were of 1s,2s,3s,4s and 5s.The processes were then sorted according to their arrival times in a linked list.




#Paging
-------
Paging was done as per the suggested procedure of locality reference mentioned in the assignment.


******************
Assume as an example you are running a process that consists of 11 pages numbered 0 through 10. Assume when start executing this process there is only free 4 pages Physical memory frames. There are always 11 page-frames available on disk. When the process starts, none of its pages are in memory.

The process makes random references to its pages. Due to locality of reference, after referencing a page i, there is a 70% probability that the next reference will be to page i, i-1, or i+1. i wraps around from 10 to 0. In other words, there is a 70% probability that for a given i, ∆i will be -1, 0, or +1. Otherwise, |∆i| > 1.

2.2 Suggested procedure

To compute the next i, first generate a random number “r” from 0 through 10.
If 0 ≤ r < 7, then generate a random ∆i to be -1, 0, or +1.
For 7 ≤ r ≤ 10, randomly generate the new page reference “j,” 2 ≤ |∆i| ≤ 9
[ 0 ≤ j ≤ i-2 or i+2 ≤ j ≤ 10]
******************


Below functions were declared and defined in the program for paging,

find_free_page() -Function to find free pages 
if_page_present_in_memory()- Function to check if the page is in main memory
register_page()-Function to search all available pages in the memory
release_memory()-Function used to free the memory occupied by the processes
initialize_all_pages()- Functioned used to initialize all the pages stored in linked list
disp_page()- function to display memory map
find_next_page()-Function to make reference to next page keeping in mind the locality reference mentioned in the assignment
compare_ToA()-Function to compare and sort all processes based on their time of arrival
next_free_page_id()-Function to search free pages

All the functions required for paging are declared in the PAGE.h file and defined in the PAGE.c file which are subsequently called from the other files, whenever required.



NOTE
-----

The macros and structures are defined in PAGE.h file.

All the page replacement algorithms are implemented as separate files.



#Process Execution
------------------

Any process always starts at page-0, then every 100 ms the process references another memory location using the above locality of reference algorithm. Process continues referencing memory till its duration expires. For each memory reference have collected statistics <time-stamp in seconds, process Name, page-referenced, Page-in-memory, which process/page number will be evicted if needed> and printed the same.



#Simulator and Simulation Execution
-----------------------------------


We created 150 processes , as mentioned with mentioned details, and stored in a list after sorting them based on their arrival time.

Created 100 pages and stored it in a list and initialized them with a value of -1 indicating they are free initially.

One process is picked from the queue and it starts its execution only if 4 pages are free in  the free page list, otherwise the process waits until pages are available.

We generated required statistics whenever any process completes its execution or is evicted os starts execution, that is, for each memory reference.

Upon start of execution by any process , the process makes reference to random page every 100ms and we have printed statistics for each reference made by the process. 

If the memory is full  and a process makes a reference to any page that is not in memory, the selected "page replacement Algorithm" selected through command line is applied to choose a victim page and evict it to allocate memory for process making reference. 

We run the simulator for 5 times, each for 1 minute, for each of the algorithms (LRU,FIFO and Random) and printed a record <time stamp, process name, Enter/exit, Size in Pages, Service Duration, Memory-map>.

We calculated hit/miss ratio for each algorithm and printed the same for each simulation.

We also printed the average number of processes (over the 5 runs) that were successfully swapped-in (started execution),for each replacement algorithm.

To run the program:
Compile all the codes and generate an executable file. Run this file using ./filename followed by an argument specifying the desired page replacement algorithm. The available options are FCFS (First-Come, First-Served), LRU (Least Recently Used) and Random
