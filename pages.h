#pragma once

#include <stddef.h>

enum Size
{
    MEM_SIZE = 100,
    REQ_SIZE = 10,
    DATA_SIZE = 60,
    CACHE_SIZE = 10
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
void request(int size, struct page_t* mem);
void print_mem(struct page_t* mem);
void print_page(struct page_t* target);
struct cache_t* create_fill_cache (size_t size);
void remove_mem(struct page_t* mem);
void remove_cache(struct cache_t* cache_mem);
struct page_t* find_page(int number, struct page_t* mem, size_t size);




