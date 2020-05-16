#pragma once

#include <stddef.h>

///List Declaration
struct list_t;

///Constants (See more in README)
enum Size
{
    MEM_SIZE = 100,
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
struct page_t
{
    long long int index;
    char data[DATA_SIZE];
};

///Cache-memory 
struct cache_t
{
	struct page_t page;
	int flag;
};



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

void my_delay(int millis);

