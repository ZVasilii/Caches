#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "pages.h"

//Creating main memory of MEM_SIZE
struct page_t* create_fill_mem (size_t size)
{
	srand(time(NULL));
	struct page_t* mem = (struct page_t*) calloc (size, sizeof(struct page_t));
	assert(mem && "CreateFillMem");
	for(int i = 0; i < size; i++)
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
struct page_t* find_page(int number, struct page_t* mem)
{
	assert(mem && "Find_P");
	for(int i = 0; i < MEM_SIZE; i++)
	{
		if (mem[i].index == number)
			return mem + i;
	}
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
	printf("Index: %d\n", target -> index);
	printf("Data: ");
	for (int j = 0; j < DATA_SIZE; j++)
	{
		printf("%c", target -> data[j]);
	}
	printf("\n");
}

//Getting page without caching
void slow_get_page (struct page_t* target, struct page_t* mem, int number)
{
	assert(mem && "Get_P");
	assert(target && "Get_P");
	struct page_t* page = find_page(number, mem, MEM_SIZE);
	memcpy(target, page,  sizeof(struct page_t));

}

//Testing function that requests page with random index
void request(int size, struct page_t* mem)
{
	assert(mem && "Request");
	srand(time(NULL));
	struct page_t* target = (struct page_t*) calloc (1, sizeof(struct page_t));
	int req_n = 0;
	for (int i = 0; i < size; i++)
	{
		req_n = rand() % MEM_SIZE;
		slow_get_page(target, mem, req_n); 

		#ifdef PRINT
		printf("%d page requested\n", req_n);
		print_page(target);
		#endif

	}
	free(target);
}

/*
int main()
{
	struct page_t*  mem = create_fill_mem(MEM_SIZE);
	struct cache_t* cache = create_fill_cache(CACHE_SIZE);
	assert(mem != NULL);
	request(REQ_SIZE, mem);
	free(mem);
	return 0;
}
*/
