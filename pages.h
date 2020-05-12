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

void slow_get_page (struct page_t* target, struct page_t* mem, int n);
struct page_t* create_fill_mem (size_t size);
void request(int size, struct page_t* mem);
void print_mem(struct page_t* mem);
void print_page(struct page_t* target);




