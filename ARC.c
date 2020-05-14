
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "pages.h"
#include "dl_list.h"
#include "ARC.h"

/*
struct list_t {
	struct cell* head;
	unsigned long long length;
	struct cell* end;
	struct cell* last_found;
};

struct cell {
	struct cell* prev;
	struct cell* next;
	long long int data;
	struct cache_t* cache_ptr;
};
*/

int max (int a, int b)
{
	if (a >=b) return a;
	else return b;
}

int min(int a, int b)
{
	if (a <=b) return a;
	else return b;
}


void replace(int *p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem)
{
	struct cell* page_in_B2 = find_list_elem(B2, page_name);
	if (((T1->length) >=1) && (((page_in_B2 != NULL) && ((T1->length) == (*p))) || ((T1->length) >= (*p))))
	{
		/*
		move LRU page of T1 to the top of B1
		remove it from the cache
		*/
		replace_lf_to_head(T1, B1, T1->end);
		struct cache_t* temp = cell_cache(B1->head);
		temp->flag = 0;
	}
	else
	{
		/*
		move LRU page of T2 to the top of B2
		remove it from the cache
		*/
		replace_lf_to_head(T2, B2, T2->end);
		struct cache_t* temp = cell_cache(B2->head);
		temp->flag = 0;
	}
}

struct cell* insert_in_head(struct list_t* part, long long int page_name, struct cache_t* cache_ptr)
{
	//insert new cell in this part with these cache_ptr and page_name
	struct cell* new_head = make_cell_np(page_name, cache_ptr);
	return insert_to_head(part, new_head);
}

struct cache_t* from_mem_to_cache_mem(long long int page_name, struct page_t* mem, struct cache_t* cache_mem)
{
	#ifdef DELAY
	printf("CACHE_MISS!\n");
	my_delay(MEM_DELAY);
	#endif
	
	//copying page with page_name from mem to cache_mem
	int i = 0;
	struct page_t* page_in_mem = find_page(page_name, mem);
	assert(page_in_mem && "No such page in memory");
	for (i = 0; i < CACHE_SIZE; i++)
		if (cache_mem[i].flag == 0)
		{
			cache_mem[i].flag = 1;
			memcpy(&cache_mem[i].page, page_in_mem, sizeof(struct page_t));
			assert(((cache_mem + i) != NULL) && "Mem to cache");
			return (&cache_mem[i]);
		}
	assert((i == CACHE_SIZE) && "No free space in cache memory");
}

struct cell* fast_get_page(int* p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem)			//main function of ARC
{		
	#ifdef DELAY
	my_delay(CACHE_DELAY);
	#endif

	/*
	int p = 0;
	long long int page_name;
	struct cell* T1 = make_list(0);
	struct cell* T2 = make_list(0);            //initialization of cache parts
	struct cell* B1 = make_list(0);
	struct cell* B2 = make_list(0);
	*/
	struct cell* page_in_T1 = find_list_elem(T1, page_name);
	struct cell* page_in_T2 = find_list_elem(T2, page_name);

	if ((page_in_T1 != NULL) || (page_in_T2 != NULL))				//case 1
	{
		/*
		move x to the top of T2
		*/
		if (page_in_T1 != NULL)
			return replace_lf_to_head(T1, T2, page_in_T1);
		if (page_in_T2 != NULL)
			return replace_lf_to_head(T2, T2, page_in_T2);
	}

	struct cell* page_in_B1 = find_list_elem(B1, page_name);

	if (page_in_B1 != NULL)											//case 2
	{
		/*
		p = min(c, p + max(cachesize(B2)/cachesize(B1), 1);
		replace(p);
		move x to the top of T2
		place x into the cache
		*/
		*p = min(CACHE_SIZE, *p + max((B2->length) / (B1->length), 1));
		replace(p, page_name, T1, T2, B1, B2, mem, cache_mem);
		replace_lf_to_head(B1, T2, page_in_B1);
		struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);
		assert(temp != NULL && "Page B1");
		set_cache(T2->head, temp);
		return T2->head;
	}

	struct cell* page_in_B2 = find_list_elem(B2, page_name);

	if (page_in_B2 != NULL)											//case 3
	{
		/*
		p = max(0, p - max(cachesize(B1)/cachesize(B2), 1);
		replace(p);
		move x to the top of T2
		place x into the cache
		*/
		*p = max(0, *p - max((B1->length) / (B2->length), 1));
		replace(p, page_name, T1, T2, B1, B2, mem, cache_mem);
		replace_lf_to_head(B2, T2, page_in_B2);
		struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);
		assert(temp != NULL && "Page B2");
		set_cache(T2->head, temp);
		return T2->head;
	}


	int L1_length = (B1->length) + (T1->length);
	int L2_length = (B2->length) + (T2->length);
	if (L1_length == CACHE_SIZE)												//case 4.1
		if (((T1->length)) < CACHE_SIZE)
		{
			/*
			delete LRU page of B1
			replace(p)
			*/
			delete_last_elem(B1);
			replace(p, page_name, T1, T2, B1, B2, mem, cache_mem);
		}
		else
		{
			/*
			delete LRU page of T1
			remove it from the cache
			*/
			struct cache_t* temp = cell_cache(T1->end);
			temp->flag = 0;
			delete_last_elem(T1);
		}			
	else if ((L1_length < CACHE_SIZE) && ((L1_length + L2_length) >= CACHE_SIZE))		//case 4.2
		if ((L1_length + L2_length) == (2 * CACHE_SIZE))
		{
			/*
			delete the LRU page of B2
			replace(p)
			*/
			delete_last_elem(B2);
			replace(p, page_name, T1, T2, B1, B2, mem, cache_mem);
		}
	/*
	put x at the top of T1
	place it into the cache
	*/
	struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);
	assert(temp != NULL && "Case 4.2");
	insert_in_head(T1, page_name, temp);
	return T1->head;
}