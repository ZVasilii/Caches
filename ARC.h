#pragma once

void replace(unsigned long long *p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2);
struct cell* insert_in_head(struct list_t* part, long long int page_name, struct cache_t* cache_ptr);
struct cache_t* from_mem_to_cache_mem(long long int page_name, struct page_t* mem, struct cache_t* cache_mem);
struct cell* fast_get_page(unsigned long long* p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem, long long int* T_hits);	

long long int imax (long long int a, long long int b);
long long int imin(long long int a, long long int b);