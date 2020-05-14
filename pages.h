#pragma once

#include <stddef.h>

struct list_t;


enum Size
{
    MEM_SIZE = 10,
    REQ_SIZE = 10,
    DATA_SIZE = 60,
    CACHE_SIZE = 2,

};

enum Mode 
{
	FAST = 1,
	SLOW = 0,
};

enum Delays
{
	MEM_DELAY = 10,
	CACHE_DELAY = 10,
};

struct page_t
{
    int index;
    char data[DATA_SIZE];
};

struct cache_t
{
	struct page_t page;
	int flag;
};


void slow_get_page (struct page_t* target, struct page_t* mem, int number);
struct page_t* create_fill_mem (size_t size);
void request(int mode, int size, int* p,struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem);
void print_mem(struct page_t* mem);
void print_page(struct page_t* target);
struct cache_t* create_fill_cache (size_t size);
void remove_mem(struct page_t* mem);
void remove_cache(struct cache_t* cache_mem);
struct page_t* find_page(int number, struct page_t* mem);
void clear_everything(struct page_t* mem, struct cache_t* cache, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2);

void my_delay(int millis);

