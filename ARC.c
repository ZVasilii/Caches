/*
INFORMATION
*************************************************
This file contains ARC Algorithm itelf

imax - function of finding max long long int element from given two
imin - function of finding min long long int element from given two
replace - function of replacing elements in cache due to some conditions (mostly due to parameter p and cache sizes)
insert_in_head - function insert new cell in given part of cache with given cache_mem pointer and page_name
from_mem_to_cache_mem - copying page with given page_name from memory to cache_memory
fast_get_page - main function of ARC, it uses ARC algorithm to cache given page 
*/




#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>

#include "pages.h"
#include "dl_list.h"
#include "ARC.h"
#include "conditions.h"



extern size_t cachesize; //From function main_test.c



long long int imax (long long int a, long long int b)   

{
	//simply max
	if (a >=b) return a;
	else return b;
}

long long int imin(long long int a, long long int b)	
{
	//simply min
	if (a <=b) return a;
	else return b;
}


void replace(unsigned long long *p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2)

{
	assert((p!= NULL) && (*p <= cachesize) && "Incorrect parameter p in replace");
	assert((p!= NULL) && (T1!= NULL) &&  (T2!= NULL) &&  (B1!= NULL) && (B2!= NULL) && "Get null pointer in replace");

	

	//here decision is made due to param p: should program put the oldest of T1 or T2 to the ghost part of cache
	struct cell* page_in_B2 = find_list_elem(B2, page_name);
	if (((T1->length) >=1) && ((page_in_B2 && ((T1->length) == (*p))) || ((T1->length) >= (*p))))
	{												//if program should chose the oldest in T1
		/*
		move LRU page of T1 to the top of B1
		remove this page from the cache
		*/
		struct cell* B1_head = replace_lf_to_head(T1, B1, T1->end);
		assert((B1_head == B1->head) && (B1_head != NULL) && "error with replace_lf_to_head in replace_B1");
		struct cache_t* temp = cell_cache(B1->head);
		assert((temp != NULL) && (temp->flag == 1) && "cell_cache return false pointer on cache_mem in replace_B1");
		temp->flag = 0;
	}
	else											
	{												//else (it should take the oldest in T2)
		/*
		move LRU page of T2 to the top of B2
		remove this page from the cache
		*/
		struct cell* B2_head = replace_lf_to_head(T2, B2, T2->end);
		assert((B2_head == B2->head) && (B2_head != NULL) && "error with replace_lf_to_head in replace_B2");
		struct cache_t* temp = cell_cache(B2->head);
		assert((temp != NULL) && (temp->flag == 1) && "cell_cache return false pointer on cache_mem in replace_B2");
		temp->flag = 0;
	}
}

struct cell* insert_in_head(struct list_t* part, long long int page_name, struct cache_t* cache_ptr)
{
	assert(part && cache_ptr && "Get null pointer in insert_in_head");

	//creating new cell with give page_name and pointer on cache mem, then put it on top of cache_part
	struct cell* new_head = make_cell_np(page_name, cache_ptr);
	assert((new_head!= NULL) && "make_cell_np return NULL in insert_in_head");
	struct cell* part_head = insert_to_head(part, new_head);
	assert((part_head == part->head) && "wrong insert in head");
	return part_head;
}

struct cache_t* from_mem_to_cache_mem(long long int page_name, struct page_t* mem, struct cache_t* cache_mem)
{
	assert(mem && cache_mem && "Get null pointer in from_mem_to_cache_mem");

	#ifdef PRINT_REQ
	printf("CACHE_MISS!\n");
	#endif

	#ifdef DELAY
	my_delay(MEM_DELAY);
	#endif
	
	size_t i = 0;
	struct page_t* page_in_mem = find_page(page_name, mem);   //try to find pointer on page in memory with this page_name
	assert((page_in_mem!= NULL) && "No such page in memory");

	for (i = 0; i < cachesize; i++)				//trying to find free space in cache_mem
		if (cache_mem[i].flag == 0)

		{
			//if we found, place there new page by copying it from memory and turn on flag, that this cell is not empty
			cache_mem[i].flag = 1;
			memcpy(&cache_mem[i].page, page_in_mem, sizeof(struct page_t));
			assert(((cache_mem + i) != NULL) && "Mem to cache");
			return (cache_mem + i);
		}

	assert((i < cachesize) && "No free space in cache_mem");

	return NULL;
}



struct cell* fast_get_page( unsigned long long* p, 
							long long int page_name, 
							struct list_t* T1, 
							struct list_t* T2, 
							struct list_t* B1, 
							struct list_t* B2, 
							struct page_t* mem, 
							struct cache_t* cache_mem, 
							long long int* T_hits)

{		
	assert(p && T1 && T2 && B1 && B2 && mem && cache_mem && T_hits && "Get null pointer in fast_get_page");
	assert(((T1->length + T2->length) <= cachesize) && "Too big real cache");

	#ifdef DELAY
	my_delay(CACHE_DELAY);
	#endif


	//case 1: hit in T1 or T2
	struct cell* page_in_T1 = find_list_elem(T1, page_name);
	struct cell* page_in_T2 = find_list_elem(T2, page_name);
	if ((page_in_T1 != NULL) || (page_in_T2 != NULL))				
	{															
		/*
		move this page to the top of T2
		*/
		(*T_hits)++;
		if (page_in_T1 != NULL)
		{
			struct cell* T2_head = replace_lf_to_head(T1, T2, page_in_T1);
			assert(T2_head && (T2_head == T2->head) && "Case 1, hit in T1");
			return T2_head;
		}
		else
		{
			struct cell* T2_head = replace_lf_to_head(T2, T2, page_in_T2);
			assert(T2_head && (T2_head == T2->head) && "Case 1, hit in T2");
			return T2_head;
		}
	}


	//case 2: hit in B1 
	struct cell* page_in_B1 = find_list_elem(B1, page_name);
	if (page_in_B1 != NULL)											
	{																
		/*
		change p using equation: p = min(c, p + max(cachesize(B2)/cachesize(B1), 1);
		replace smth in cache using function <replace>;
		then put found page to the top of T2
		and place it into the cache
		*/


		*p = imin(cachesize, *p + imax((B2->length) / (B1->length), 1));
		replace(p, page_name, T1, T2, B1, B2);
		replace_lf_to_head(B1, T2, page_in_B1);

		struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);
		assert(temp && "Case 2, copy to cache_mem");
		set_cache(T2->head, temp);
		return T2->head;
	}


	//case 3: hit in B2
	struct cell* page_in_B2 = find_list_elem(B2, page_name);
	if (page_in_B2 != NULL)											
	{									
		/*
		change p using equation: p = max(0, p - max(cachesize(B1)/cachesize(B2), 1);
		replace smth in cache using function <replace>;
		then put found page to the top of T2
		and place it into the cache
		*/
		*p = imax(0, *p - imax((B1->length) / (B2->length), 1));


		replace(p, page_name, T1, T2, B1, B2);
		replace_lf_to_head(B2, T2, page_in_B2);
		struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);
		assert(temp && "Case 3, copy to cache_mem");
		set_cache(T2->head, temp);
		return T2->head;
	}


	//case 4: new page
	unsigned long long L1_length = (B1->length) + (T1->length);						//L1 and L2 sizes
	unsigned long long L2_length = (B2->length) + (T2->length);

	if (L1_length == cachesize)											//case 4.1: L1 is full
		if (((T1->length)) < cachesize)									//if T1 is still not full
		{																//delete oldest in B1 and change smth(oldest in T1 -> newest in B1)

		assert(((L1_length + L2_length) <= 2 * cachesize) && "Too big cache");

												

			/*
			delete LRU page of B1
			replace smth using <replace>
			*/
			delete_last_elem(B1);
			replace(p, page_name, T1, T2, B1, B2);
		}
		else											
			{												//if T1 if full			
			/*
			delete LRU page of T1
			remove it from the cache
			*/
			struct cache_t* temp = cell_cache(T1->end);
			assert(temp && (temp->flag == 1) && "Case 4.1, wrong pointer on cache memory");
			temp->flag = 0;
			delete_last_elem(T1);
		}			

	else if ((L1_length < cachesize) && ((L1_length + L2_length) >= cachesize))		//case 4.2: if L1 is not full, but together L1+L2 more than cachesize
	{																				//if L1+L2 full exactly (= 2*cachesize), delete oldest in B2
																					//but ALWAYS change smth

		/*
		if L1+L2 full exactly (= 2*cache_size),
			delete the LRU page of B2
		ALWAYS: replace smth using <replace>
		*/
		if ((L1_length + L2_length) == (2 * cachesize))
			delete_last_elem(B2);

		replace(p, page_name, T1, T2, B1, B2);
		}
	/*
	put new page at the top of T1
	place it into the cache
	*/
	struct cache_t* temp = from_mem_to_cache_mem(page_name, mem, cache_mem);
	assert(temp && "Case 4, copying from memory");
	struct cell* T1_head = insert_in_head(T1, page_name, temp);
	assert(T1_head && (T1->head == T1_head) && "Case 4, wrong insert in head");
	return T1->head;
}