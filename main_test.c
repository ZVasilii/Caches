/*
Welcome to our project!

The goal of our project: implementing one of the caching strategies - ARC

ARC - Adaptive Replacement Cache 
You can read more in this article:
http://theory.stanford.edu/~megiddo/pdf/IEEE_COMPUTER_0404.pdf

Authors of the project: 1st year students of FRTK:

	Alexander Latikov
	Sergey Koshelev
	Zaitsev Vasilii

Development Date: May 2020

A brief overview of the files included in our project:

	dl_list.h and dl_list.c - functions and auxiliary structures for the "List" structure
	dl_list_test.c - Testing system for a List
	dl_cells.c - functions and auxiliary structures for the "List cell" structure
	ARC.c and ARC.h - Main ARC Cache Emulation Algorithm
	pages.h - Header with constants and basic structures
	main_test.c - Testing system, user interface, data output for analysis <You are here>
	ARC_readme.txt - more about what is happening in ARC
	dl_list_readme.txt - more on how to use the dl_list functions
	colors.h - Header with materials for changing the color of text in the console

LICENSE - GNU GENERAL PUBLIC LICENSE
*/


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "dl_list.h"
#include "pages.h"
#include "ARC.h"
#include "colors.h"
#include "conditions.h"


size_t cachesize = 0;  ///Size of cache

//Creating main memory of MEM_SIZE
struct page_t* create_fill_mem (size_t size)
{
	srand((unsigned int)time(NULL));
	struct page_t* mem = (struct page_t*) calloc (size, sizeof(struct page_t));
	assert(mem && "CreateFillMem");
	for(unsigned int i = 0; i < size; i++)
	{
		mem[i].index = i;
		for (int j = 0; j < DATA_SIZE; j++)
			mem[i].data[j] = rand() % 127;
	}
	return mem;
}


//Creating cache_memory of CACHE_SIZE
struct cache_t* create_fill_cache (size_t size)
{
	struct cache_t* cache_mem = (struct cache_t*) calloc (size, sizeof(struct cache_t));
	assert(cache_mem && "CreateFillCache");
	return cache_mem;
}


//Removing main memory
void remove_mem(struct page_t* mem)
{
	free(mem);
	mem = NULL;
}


//Removing cache
void remove_cache(struct cache_t* cache_mem)
{
	free(cache_mem);
	cache_mem = NULL;
}


//Finding page in memory 
struct page_t* find_page(long long int number, struct page_t* mem)
{
	assert(mem && "Find_P");
	for(int i = 0; i < MEM_SIZE; i++)
	{
		if (mem[i].index == number)
			return mem + i;
	}
	exit(404);
}


//Printing memory
void print_mem(struct page_t* mem)
{
	assert(mem && "Print");
	for(int i = 0; i < MEM_SIZE; i++)
	{
		print_page(mem + i);	
	}

}



//Printing requested page
void print_page(struct page_t* target)
{
	assert(target && "Print");
	printf("\n");
	color_on(BLUE);
	printf("################################");
	color_off();
	printf("\n");
	printf("Page requested!\n");
	printf("Index: %lld\n", target -> index);
	printf("Data: ");
	for (int j = 0; j < DATA_SIZE; j++)
	{
		printf("%c", target -> data[j]);
	}
	printf("\n");
	color_on(BLUE);
	printf("################################");
	color_off();
	printf("\n");
}


//Getting page,  bypassing the cache, directly from memory
void slow_get_page (struct page_t* target, struct page_t* mem, long long int number)
{
	assert(mem && "Get_P");
	assert(target && "Get_P");
	struct page_t* page = find_page(number, mem);
	memcpy(target, page,  sizeof(struct page_t));
	#ifdef DELAY
	my_delay(MEM_DELAY);
	#endif

}

///CLEAR EVERYTHING!!!
void clear_everything(  struct page_t*  mem,
				    	struct cache_t* cache,
						struct list_t* T1,
						struct list_t* T2,
						struct list_t* B1,
						struct list_t* B2)
{
	remove_mem(mem);
	remove_cache(cache);
	destroy_list(T1);
	destroy_list(T2);
	destroy_list(B1);
	destroy_list(B2);
} 

///Toggle console-color on
void color_on(const char* str)
{
	printf("%s\n", str);
}

///Toggle console-color off
void color_off()
{
	printf(RES);
}



//Testing function that requests page with random index
void request(   int mode, 
				int size,
				unsigned long long * p,struct list_t* T1, 
				struct list_t* T2, struct list_t* B1, 
				struct list_t* B2, 
				struct page_t* mem, 
				struct cache_t* cache_mem)
{
	assert(mem && "Request");
	srand((unsigned int)time(NULL));
	struct page_t* target = (struct page_t*) calloc (1, sizeof(struct page_t));
	long long int req_n = 0;
	struct cell* buffer = NULL;


	if (mode == SLOW)
	{
		for (int i = 0; i < size; i++)
		{
			req_n = rand() % MEM_SIZE;
			slow_get_page(target, mem, req_n); 

			#ifdef PRINT
			print_page(target);
			#endif
		}
	}

	if (mode == FAST)
	{
		long long int T_hits = 0;
		for (int i = 0; i < size; i++)
		{
			req_n = rand() % MEM_SIZE;

			buffer =  fast_get_page(p, req_n, T1, T2, B1, B2, mem, cache_mem, &T_hits);

			#ifdef PRINT_REQ
			print_all_lists(T1, T2, B1, B2);
			#endif

			assert(buffer != NULL);
			assert(cell_cache(buffer) != NULL);
			assert(&(cell_cache(buffer)->page)!= NULL);
			memcpy(target, &(cell_cache(buffer)->page), sizeof(struct page_t));

			#ifdef PRINT
			print_page(target);
			#endif
		}
		color_on(MAGENTA);
		printf("Number of requests: %d\n", size);
		printf("Number of hits: %lld\n", T_hits);
		printf("Hit ratio %lg percents\n", (double) T_hits/ (double) size * 100);
		color_off();
	}
	buffer = NULL;
	free(target);
}

///Artificial Delay function
void my_delay(int millis)
{
	millis *=1000;
	clock_t start_time = clock(); 
  
    while (clock() < start_time + millis) 
    {}
}

///Testing functions for contest mode
void contest_testing(unsigned long long * p,
					struct list_t* T1, 
					struct list_t* T2, 
					struct list_t* B1, 
					struct list_t* B2, 
					struct page_t* mem, 
					struct cache_t* cache_mem,
					FILE* inp)
{
	long long int page_n;
	long long int T_hits = 0;
	long long int req_qt = 0;

	while (fscanf(inp, "%lld", &page_n) == 1)
	{
		fast_get_page(p, page_n, T1, T2, B1, B2, mem, cache_mem, &T_hits);
		req_qt++;
	}
	printf("Number of requests: %lld\n", req_qt);
	printf("Number of hits: %lld\n", T_hits);
	printf("Hit ratio %lg percents\n", (double) T_hits/ (double) req_qt * 100);
	
}


///General function
int main()
{
	

	///Initializing the size of the cache
	#ifdef CONTEST 
	fscanf(stdin , "%lu", &cachesize);
	#endif

	#ifndef CONTEST 
	cachesize = CACHE_SIZE;
	#endif



	
	unsigned long long p = 0; //Param for ARC algorithm

	///Initializing main structures
	struct page_t*  mem = create_fill_mem(MEM_SIZE);
	struct cache_t* cache_mem = create_fill_cache(cachesize);
	struct list_t* T1 = make_list();
	struct list_t* T2 = make_list();
	struct list_t* B1 = make_list();
	struct list_t* B2 = make_list();

	assert((mem != NULL) && (cache_mem!= NULL) && (T1!= NULL) && (T2!= NULL) && (B1!= NULL) && (B2!= NULL));

	///Initializing parametrs for time-counting functions
	#ifdef TIME
	long int start_t = 0;
	long int end_t = 0;
	double slow_t = 0.0;
	double fast_t = 0.0;
	#endif

	#ifdef TIME
	start_t = clock();
	#endif

	///Testing in contest mode
	#ifdef CONTEST 
	contest_testing(&p, T1, T2, B1, B2, mem, cache_mem, stdin);
	#endif

	///"Canonical" mode of the programm
	#ifndef CONTEST
	///Slow requesting, without cache
	color_on(RED);
	printf("Request from memory\n");
	color_off();
	request(SLOW, REQ_SIZE, &p, T1, T2, B1, B2, mem, cache_mem);
	#endif

	#ifdef TIME
	end_t = clock();
	slow_t = ((double) (end_t - start_t))/CLOCKS_PER_SEC;
	#endif

	#ifdef TIME
	start_t = clock();
	#endif

	#ifndef CONTEST
	///Fast requesting, using ARC
	color_on(RED);
	printf("Request from cache\n");
	color_off();
	request(FAST, REQ_SIZE, &p, T1, T2, B1, B2, mem, cache_mem);
	#endif
	
	///Time-counting functions
	#ifdef TIME
	end_t = clock();
	color_on(RED);
	fast_t = ((double) (end_t - start_t))/CLOCKS_PER_SEC;
	printf("Time spent on slow request: %lg seconds\n", slow_t);
	printf("Time spent on fast request: %lg seconds\n", fast_t);
	color_off();
	#endif



	///Wanna see some statistics????
	#ifdef STATS

	color_on(GREEN);
	printf("**********************\n");
	printf("STATS:\n");
	printf("Memory size = %d\n", MEM_SIZE);
	printf("Cache size = %lu\n", cachesize);
	printf("Memory delay = %d millis\n", MEM_DELAY);
	printf("Cache delay  = %d millis\n", CACHE_DELAY);
	printf("Number of requests = %d\n", REQ_SIZE);
	printf("**********************\n");
	printf("\n");
	color_off();

	#endif

	///Always clear the memory after yourself!
	clear_everything(mem, cache_mem, T1, T2, B1, B2);

	return 0;
}

