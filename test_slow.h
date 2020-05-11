#pragma once



enum Size
{
	MEM_SIZE = 100,
	REQ_SIZE = 10,
	DATA_SIZE = 60
};

struct page 
{
	int index;
	char data[DATA_SIZE];
};

void slow_get_page (struct page* target, struct page* mem, int n);
struct page* create_fill_mem (size_t size);
void request(int size, struct page* mem);
void print_mem(struct page* mem);
void print_page(struct page* target);





