#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "test_slow.h"

//Creating memory
struct page* create_fill_mem (size_t size)
{
	srand(time(NULL));
	struct page* mem = (struct page*) calloc (size, sizeof(struct page));
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
void print_mem(struct page* mem)
{
	assert(mem && "Print");
	for(int i = 0; i < MEM_SIZE; i++)
	{
		print_page(mem + i);	
	}

}

//Printing requested page
void print_page(struct page* target)
{
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
void slow_get_page (struct page* target, struct page* mem, int n)
{
	target->index = mem[n].index;
	memcpy(target->data, mem[n].data, DATA_SIZE * sizeof(char));

}

//Testing function that requests page with random index
void request(int size, struct page* mem)
{
	srand(time(NULL));
	struct page* target = (struct page*) calloc (1, sizeof(struct page));
	int req_n = 0;
	for (int i = 0; i < size; i++)
	{
		req_n = rand() % MEM_SIZE;
		slow_get_page(target, mem, req_n); 
		printf("%d page requested\n", req_n);
		print_page(target);
	}
	free(target);
}

int main()
{
	struct page*  mem = create_fill_mem(MEM_SIZE);
	assert(mem != NULL);
	request(REQ_SIZE, mem);
	free(mem);
	return 0;


}