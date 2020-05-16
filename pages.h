/*
INFORMATION
**************
Header with constants 
and declarations of functions with pages/memory

YOU CAN CHANGE THE PARAMETRS OF THE PROGRAM HERE
*/



#pragma once

#include <stddef.h>

///List Declaration given in dl_list.h
struct list_t;


/*
CONSTANTS
*********************************
MEM_SIZE = Memory size (In pages)
REQ_SIZE = Quantity of requested pages (in pages)
DATA_SIZE = Size of "Pseudo-Data" in one page (bytes)
CACHE_SIZE = Cache Size (In Pages)
FAST = Request Page Mode Using Cache
SLOW = Page request mode, bypassing the cache, directly from memory
MEM_DELAY = Artificial delay when accessing memory (In milliseconds)
CACHE_DELAY = Artificial delay accessing the cache (In milliseconds)
*/

enum Size
{
    MEM_SIZE = 10000,
    REQ_SIZE = 10,
    DATA_SIZE = 60,
    CACHE_SIZE = 5,

};


enum Mode 
{
	FAST = 1,
	SLOW = 0,
};

enum Delays
{
	MEM_DELAY = 1,
	CACHE_DELAY = 1,
};

///Page structure
///Index - individual for every page
///Data - pseudo-information in every page
struct page_t
{
    long long int index;
    char data[DATA_SIZE];
};

///Cache-memory 
///Page - see above
///Flag = 1, if cache-cell is full, else = 0
struct cache_t
{
	struct page_t page;
	int flag;
};


///Functions with pages and memory
void slow_get_page (struct page_t* target, struct page_t* mem, long long int number);
struct page_t* create_fill_mem (size_t size);
void request(int mode, int size, unsigned long long* p,struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem);
void print_mem(struct page_t* mem);
void print_page(struct page_t* target);
struct cache_t* create_fill_cache (size_t size);
void remove_mem(struct page_t* mem);
void remove_cache(struct cache_t* cache_mem);
struct page_t* find_page(long long int number, struct page_t* mem);
void clear_everything(struct page_t* mem, struct cache_t* cache, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2);


//Delay and colors function
void my_delay(int millis);
void color_on(const char* str);
void color_off();


//Function for testing in contest mode
void contest_testing(unsigned long long * p,
					struct list_t* T1, 
					struct list_t* T2, 
					struct list_t* B1, 
					struct list_t* B2, 
					struct page_t* mem, 
					struct cache_t* cache_mem,
					FILE* inp);
