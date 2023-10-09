#include "PAGE.h"


int main(int argc, char* argv[]) {  //Command line arguments

    int sim_time_stamp = 0;/// simulator timestamp


//allocates memory as per different process sizes
    
int *process_size_in_pages = malloc(sizeof(int)*4);
    process_size_in_pages[0] = 5;
    process_size_in_pages[1] = 11;
    process_size_in_pages[2] = 17;
    process_size_in_pages[3] = 31;


//pointer to the Page
    page *page_pointer;

    //Calls page replacement algorithms as entered by user in command line
    
    void (*page_rep_algorithm)(PAGE_LIST*);
    if (argc != 2){
        printf("Choose one option among these algorithms:\n1)First In First Out (FIFO)\n2)Least Recently Used (LRU)\n3)Random\n");
        return -1;
    }
    
    
//Calls function as entered in command line

    if(strcmp(argv[1], "FCFS") == 0){
        page_rep_algorithm = FCFS;
    }else if(strcmp(argv[1], "LRU") == 0){
        page_rep_algorithm = LRU;
    }else if(strcmp(argv[1], "Random") == 0){
        page_rep_algorithm = Random;
    }else {
printf("*******\n");
        printf("Options to run for simulation : FCFS, LRU or Random.Choose one from these three\n");
printf("*******\n");

        return -1;
    }

    int total_processes_swapped = 0;  //keeps count of total no of swapped processes

    srand(0);
    int i;
    
    //Page replacement simulation, will be carried out 5 times for each algorithm 

    for(i = 0; i < 5; i++) {
        printf("\n============ Simulation In Progress  %d ============\n", i+1);

        PAGE_LIST pl;
        initialize_all_pages(&pl);
        process Process[TOTAL_NO_OF_PROCESSES];
	int i;
        

        //Generates random 150 processes
        for(i=0;i<TOTAL_NO_OF_PROCESSES;i++) {
            Process[i].pid = i;
            Process[i].pageSize = process_size_in_pages[rand()%4]; //Process size as instructed in MB(pages)
            Process[i].arrivalTime = rand()%60; //Assigns arrival time to generated processes
            Process[i].duration = rand() % PROCESS_DURATION;// maximum process duration
            Process[i].currPage = 0; // all processes begin with page 0
        }
        qsort(Process,TOTAL_NO_OF_PROCESSES,sizeof(process),compare_ToA);  //sorts all processes on basis or arrival time

        int index = 0; // index to the start of Process queue
        

        for(sim_time_stamp = 0; sim_time_stamp < TOTAL_DURATION; sim_time_stamp++) {

            //looking for new process at start of every second
            while(index < TOTAL_NO_OF_PROCESSES && Process[index].arrivalTime <= sim_time_stamp) {

		 //To check if atleast four pages are free
                if(find_free_pages(&pl,4)) {

			// if free ,bring in to the memory
                    page* pg = register_page(&pl);
                    pg->pid = Process[index].pid;
                    pg->PageNo = Process[index].currPage;
                    pg->FTBOUGHT = 1.0*sim_time_stamp;
                    pg->counter = 1;
                    pg->LONE = sim_time_stamp;
                    printf("Page- %d for process id- %d arrival time - %f\n",Process[index].currPage,Process[index].pid,pg->FTBOUGHT);
                    total_processes_swapped++;
                    index++;
                } 
                // exits loop if not available
                else break;
            }
	    int i;
            for(i=0;i<10;i++) {
		int j;
		for(j=0;j<index;j++) if(Process[j].duration > 0) {
                    Process[j].currPage = find_next_page(Process[j].currPage,Process[j].pageSize);
                    if(if_page_present_in_memory(&pl,Process[j].pid,Process[j].currPage)) {

                        page_pointer = next_free_page_id(&pl,Process[j].pid,Process[j].currPage);
                        if (page_pointer == NULL){
                            printf("Something went  wrong , returned null : pid %d page:: %d\n", Process[j].pid, Process[j].currPage);
                            return -1;
                        }

                        page_pointer->counter++;
                        page_pointer->LONE = sim_time_stamp;
                        continue;
                    }
                    // Display memory map
printf("Memory Map:\n");
disp_page(&pl);


                    //Referred page not in memory,loads the referred page in memory

                    page* new_page = register_page(&pl);
                    if(!new_page) {
printf("--------\n");

                        printf("Memory full, full list of pages:\n");
                        disp_page(&pl);

                        page_rep_algorithm(&pl);
                        disp_page(&pl);

                        new_page = register_page(&pl);
                    }
                    new_page->pid = Process[j].pid;
                    new_page->PageNo = Process[j].currPage;
                    new_page->FTBOUGHT = sim_time_stamp+(0.1*i);
                    new_page->LONE = sim_time_stamp+(0.1*i);
                    new_page->counter = 0;
                    printf("Page:%d for process %d process size:%d MB process duration:%d seconds brought in at %f\n",Process[j].currPage,Process[j].pid,Process[j].pageSize,Process[j].duration,new_page->FTBOUGHT);
                    total_processes_swapped++;

                }



            }
	    int j;
            // loopto rellease memory occupied by process
            for(j=0;j<index;j++) if(Process[j].duration > 0) {
                Process[j].duration--;
                if(Process[j].duration == 0) {
printf("#####\n");
                    printf("Process id %d is done. Memory is getting freed to be used \n",Process[j].pid);
printf("####\n");
                    release_memory(&pl,Process[j].pid);
                }
            }


            usleep(900); //the program sleeps for 0.9ms
        }
    }
    

    printf("Average number of processes that were successfully swapped in %d\n", (total_processes_swapped / 5));  //Prints average no of swapped processes


return 0;
}