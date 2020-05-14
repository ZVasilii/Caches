#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include "dl_list.h"
#include "pages.h"
#include "ARC.h"



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
	printf("################################");
	printf("\n");
	printf("Page requested!\n");
	printf("Index: %d\n", target -> index);
	printf("Data: ");
	for (int j = 0; j < DATA_SIZE; j++)
	{
		printf("%c", target -> data[j]);
	}
	printf("\n");
	printf("################################");
	printf("\n");
}

//Getting page without caching
void slow_get_page (struct page_t* target, struct page_t* mem, int number)
{
	assert(mem && "Get_P");
	assert(target && "Get_P");
	struct page_t* page = find_page(number, mem);
	memcpy(target, page,  sizeof(struct page_t));
	#ifdef DELAY
	my_delay(MEM_DELAY);
	#endif

}

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


//Testing function that requests page with random index
void request(   int mode, 
				int size,
				int* p,struct list_t* T1, 
				struct list_t* T2, struct list_t* B1, 
				struct list_t* B2, 
				struct page_t* mem, 
				struct cache_t* cache_mem)
{
	assert(mem && "Request");
	srand(time(NULL));
	struct page_t* target = (struct page_t*) calloc (1, sizeof(struct page_t));
	long long int req_n = 0;
	struct cell* buffer = (struct cell*) calloc (1, sizeof(struct cell));


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
		for (int i = 0; i < size; i++)
		{
			req_n = rand() % MEM_SIZE;
			buffer =  fast_get_page(p, req_n, T1, T2, B1, B2, mem, cache_mem);
			memcpy(target, &(buffer -> cache_ptr -> page), sizeof(struct page_t));

			#ifdef PRINT
			print_page(target);
			#endif
		}
	}
	free(buffer);
	free(target);
}

void my_delay(int millis)
{
	millis *=1000;
	clock_t start_time = clock(); 
  
    while (clock() < start_time + millis) 
    {}
}

int main()
{
	int p = 0; //Param for ARC algorithm

	long int start_t = 0.0;
	long int end_t = 0.0;

	struct page_t*  mem = create_fill_mem(MEM_SIZE);
	struct cache_t* cache_mem = create_fill_cache(2 * CACHE_SIZE);
	struct list_t* T1 = make_list();
	struct list_t* T2 = make_list();
	struct list_t* B1 = make_list();
	struct list_t* B2 = make_list();

	assert(mem != NULL);

	#ifdef TIME
	start_t = clock();
	#endif

	printf("Request from memory\n");
	request(SLOW, REQ_SIZE, &p, T1, T2, B1, B2, mem, cache_mem);

	#ifdef TIME
	end_t = clock();
	printf("Time spent on slow request: %lg seconds\n", ((double) (end_t - start_t))/CLOCKS_PER_SEC);
	#endif



	#ifdef TIME
	start_t = clock();
	#endif

	printf("Request from cache\n");
	request(FAST, REQ_SIZE, &p, T1, T2, B1, B2, mem, cache_mem);
	
	#ifdef TIME
	end_t = clock();
	printf("Time spent on fast request: %lg seconds\n", ((double) (end_t - start_t))/CLOCKS_PER_SEC);
	#endif

	clear_everything(mem, cache_mem, T1, T2, B1, B2);

	return 0;
}

