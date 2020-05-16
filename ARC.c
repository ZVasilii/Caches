
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "pages.h"
#include "dl_list.h"
#include "ARC.h"
#include "conditions.h"


extern size_t cachesize;

long long int imax (long long int a, long long int b)   //simply max
{
	if (a >=b) return a;
	else return b;
}

long long int imin(long long int a, long long int b)	//simply min
{
	if (a <=b) return a;
	else return b;
}


void replace(unsigned long long *p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2)
{
	struct cell* page_in_B2 = find_list_elem(B2, page_name);
	if (((T1->length) >=1) && (((page_in_B2 != NULL) && ((T1->length) == (*p))) || ((T1->length) >= (*p))))
	{												//(if T1 is not empty) and <{(we found page in B2) and (length_T1 == p)}  or (length_T1 >= p)>
													//oldest of T1 -> newest in B1, and delete from cache_memory
		/*
		move LRU page of T1 to the top of B1
		remove it from the cache
		*/
		replace_lf_to_head(T1, B1, T1->end);
		struct cache_t* temp = cell_cache(B1->head);
		temp->flag = 0;
	}
	else											//else
	{												//oldest of T2 -> newest in B2, and delete from cache_memory
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
	#ifdef PRINT_REQ
	printf("CACHE_MISS!\n");
	#endif

	#ifdef DELAY
	my_delay(MEM_DELAY);
	#endif
	
	//copying page with page_name from mem to cache_mem
	int i = 0;
	struct page_t* page_in_mem = find_page(page_name, mem);   //pointer on page in mem with this page_name
	assert(page_in_mem && "No such page in memory");
	for (i = 0; i < cachesize; i++)				//trying to find free space in cache_mem
		if (cache_mem[i].flag == 0)
		{
			//if we found, place there new page by copying it from memory
			cache_mem[i].flag = 1;
			memcpy(&cache_mem[i].page, page_in_mem, sizeof(struct page_t));
			assert(((cache_mem + i) != NULL) && "Mem to cache");
			return (cache_mem + i);
		}
	exit(666);
}

struct cell* fast_get_page(unsigned long long* p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem, long long int* T_hits)			//main function of ARC
{		
	#ifdef DELAY
	my_delay(CACHE_DELAY);
	#endif

	struct cell* page_in_T1 = find_list_elem(T1, page_name);
	struct cell* page_in_T2 = find_list_elem(T2, page_name);

	if ((page_in_T1 != NULL) || (page_in_T2 != NULL))				//case 1: hit in T1 or T2
	{																//put on top of T2
		/*
		move x to the top of T2
		*/
		(*T_hits)++;
		//printf("HIT!\n");
		if (page_in_T1 != NULL)
			return replace_lf_to_head(T1, T2, page_in_T1);
		if (page_in_T2 != NULL)
			return replace_lf_to_head(T2, T2, page_in_T2);
	}

	struct cell* page_in_B1 = find_list_elem(B1, page_name);

	if (page_in_B1 != NULL)											//case 2: hit in B1 
	{																//change p, replace smth, put page from B1 to T2 and put it in cache_mem
		/*
		p = min(c, p + max(cachesize(B2)/cachesize(B1), 1);
		replace(p);
		move x to the top of T2
		place x into the cache
		*/
		*p = imin(cachesize, *p + imax((B2->length) / (B1->length), 1));
		replace(p, page_name, T1, T2, B1, B2);
		replace_lf_to_head(B1, T2, page_in_B1);
		struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);
		assert(temp != NULL && "Page B1");
		set_cache(T2->head, temp);
		return T2->head;
	}

	struct cell* page_in_B2 = find_list_elem(B2, page_name);

	if (page_in_B2 != NULL)											//case 3: hit in B2
	{																//change p, replace smth, put page from B2 to T2 and put it in cache_mem
		/*
		p = max(0, p - max(cachesize(B1)/cachesize(B2), 1);
		replace(p);
		move x to the top of T2
		place x into the cache
		*/
		*p = imax(0, *p - imax((B1->length) / (B2->length), 1));
		replace(p, page_name, T1, T2, B1, B2);
		replace_lf_to_head(B2, T2, page_in_B2);
		struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);
		assert(temp != NULL && "Page B2");
		set_cache(T2->head, temp);
		return T2->head;
	}


	unsigned long long L1_length = (B1->length) + (T1->length);						//L1 and L2 sizes
	unsigned long long L2_length = (B2->length) + (T2->length);
	if (L1_length == cachesize)			//case 4.1: L1 is full
		if (((T1->length)) < cachesize)								//if T1 is still not full
		{																//delete oldest in B1 and change smth(oldest in T1 -> newest in B1)
			/*
			delete LRU page of B1
			replace(p)
			*/
			delete_last_elem(B1);
			replace(p, page_name, T1, T2, B1, B2);
		}
		else															//if T1 if full
			{															//delete oldest in T1 and delete its mem
			/*
			delete LRU page of T1
			remove it from the cache
			*/
			struct cache_t* temp = cell_cache(T1->end);
			temp->flag = 0;
			delete_last_elem(T1);
		}			
	else if ((L1_length < cachesize) && ((L1_length + L2_length) >= cachesize))		//case 4.2: if L1 is not full, but together L1+L2 more than cachesize
	{																	//if L1+L2 full exactly (= 2*cachesize), delete oldest in B2
																		//but ALWAYS change smth
		/*
		if ()
			delete the LRU page of B2
		replace(p)
		*/
		if ((L1_length + L2_length) == (2 * cachesize))
			delete_last_elem(B2);

		replace(p, page_name, T1, T2, B1, B2);
		}
	/*
	put x at the top of T1
	place it into the cache
	*/
	struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);			//case: no hit, so create new and put it in mem and on top of T1
	assert(temp != NULL && "Case 4.2");
	insert_in_head(T1, page_name, temp);
	return T1->head;
}