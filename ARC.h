#pragma once

void replace(int *p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem);
struct cell* insert_in_head(struct list_t* part, long long int page_name, struct cache_t* cache_ptr);
struct cache_t* from_mem_to_cache_mem(long long int page_name, struct page_t* mem, struct cache_t* cache_mem);
struct cell* fast_get_page(int* p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem);	
int max(int a, int b);
int min(int a, int b);
