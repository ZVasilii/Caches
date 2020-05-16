/*
INFORMATION
****************************
Header with ARC functions
*/

/*
imax - function of finding max long long int element from given two
imin - function of finding min long long int element from given two
replace - function of replacing elements in cache due to some conditions (mostly due to parameter p and cache sizes)
insert_in_head - function insert new cell in given part of cache with given cache_mem pointer and page_name
from_mem_to_cache_mem - copying page with given page_name from memory to cache_memory
fast_get_page - main function of ARC, it uses ARC algorithm to cache given page 
*/

#pragma once

#include "pages.h"
#include "dl_list.h"


void replace(unsigned long long *p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2);
struct cell* insert_in_head(struct list_t* part, long long int page_name, struct cache_t* cache_ptr);
struct cache_t* from_mem_to_cache_mem(long long int page_name, struct page_t* mem, struct cache_t* cache_mem);
struct cell* fast_get_page( unsigned long long* p, 
							long long int page_name, 
							struct list_t* T1, 
							struct list_t* T2, 
							struct list_t* B1, 
							struct list_t* B2, 
							struct page_t* mem, 
							struct cache_t* cache_mem, 
							long long int* T_hits);
	

long long int imax (long long int a, long long int b);
long long int imin(long long int a, long long int b);