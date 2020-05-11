#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "pages.h"

//Creating memory
struct page_t* create_fill_mem (size_t size)
{
	srand(time(NULL));
	struct page_t* mem = (struct page_t*) calloc (size, sizeof(struct page_t));
	assert(mem && "CreateFill");
	for(int i = 0; i < size; i++)
	{
		mem[i].index = i;
		for (int j = 0; j < DATA_SIZE; j++)
			mem[i].data[j] = rand() % 127;
	}
	return mem;
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
void slow_get_page (struct page_t* target, struct page_t* mem, int n)
{
	assert(mem && "Get_P");
	assert(target && "Get_P");
	target->index = mem[n].index;
	memcpy(target->data, mem[n].data, DATA_SIZE * sizeof(char));

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
	assert(mem != NULL);
	request(REQ_SIZE, mem);
	free(mem);
	return 0;
}
*/