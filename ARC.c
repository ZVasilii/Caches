#include "dl_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pages.h"

const int c = 10;

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
	struct page_t* page_ptr;
};

void replace(int *p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2)
{
	/*
	if ((cachesize(T1) >=1) && ((find(x, B2) && (cachesize(T1) == p)) || (cachesize(T1) >= p)))
	/move LRU page of T1 to the bottom of B1
	remove it from the cache
	else
	move LRU page of T2 to the bottom of B2
	remove it from the cache
	*/
	struct cell* page_in_B2 = find_cell(B2, page_name);
	if (((T1->length) >=1) && (((page_in_B2 != NULL) && ((T1->length) == (*p))) || ((T1->length) >= (*p))))
	{
		/*
		move LRU page of T1 to the top of B1
		remove it from the cache
		*/
		replace_lf_to_head(T1, B1, NULL);
		//remove it from the cache
	}
	else
	{
		/*
		move LRU page of T2 to the top of B2
		remove it from the cache
		*/
		replace_lf_to_head(T2, B2, NULL);
		//remove it from the cache
	}
}

struct cell* insert_in_head(struct list_t* part, long long int page_name, struct page_t* page_ptr)
{
	struct cell* new_head = (struct cell*)calloc(1, sizeof(struct cell));
	assert(new_head == NULL);
	new_head->data = page_name;
	new_head->page_ptr = page_ptr;
	return insert_to_head(part, new_head);
}

struct cell* fast_get_page(long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, int *p)			//main function of ARC
{									
	/*
	int p = 0;
	long long int page_name;
	struct cell* T1 = make_list(0);
	struct cell* T2 = make_list(0);            //initialization of cache parts
	struct cell* B1 = make_list(0);
	struct cell* B2 = make_list(0);
	*/
	struct cell* page_in_T1 = find_cell(T1, page_name);
	struct cell* page_in_T2 = find_cell(T2, page_name);
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

	struct cell* page_in_B1 = find_cell(B1, page_name);
	if (page_in_B1 != NULL)							//case 2
	{
		/*
		p = min(c, p + max(cachesize(B2)/cachesize(B1), 1);
		replace(p);
		move x to the top of T2
		place x into the cache
		*/
		*p = min(c, p + max((B2->length) / (B1->length), 1));
		replace(p, page_name, T1, T2, B1, B2);
		replace_lf_to_head(B1, T2, page_in_B1);
		//place x into the cache
		return T2->head;
	}

	struct cell* page_in_B2 = find_cell(B2, page_name);
	if (page_in_B2 != NULL)								//case 3
	{
		/*
		p = max(0, p - max(cachesize(B1)/cachesize(B2), 1);
		replace(p);
		move x to the top of T2
		place x into the cache
		*/
		*p = max(0, p - max((B1->length) / (B2->length), 1));
		replace(p, page_name, T1, T2, B1, B2);
		replace_lf_to_head(B2, T2, page_in_B2);
		//place x into the cache 
		return T2->head;
	}


	int L1_length = (B1->length) + (T1->length);
	int L2_length = (B2->length) + (T2->length);
	if (L1_length == c)						//case 4.1
		if (((T1->length)) < c)
		{
			/*
			delete LRU page of B1
			replace(p)
			*/
			delete_last_elem(B1);
			replace(p, page_name, T1, T2, B1, B2);
		}
		else
		{
			/*
			delete LRU page of T1
			remove it from the cache
			*/
		}			
	else if ((L1_length < c) && ((L1_length + L2_length) >= c))  //case 4.2
		if ((L1_length + L2_length) == (2 * c))
		{
			/*
			delete the LRU page of B2
			replace(p)
			*/
			delete_last_elem(B2);
			replace(p, page_name, T1, T2, B1, B2);
		}
	/*
	put x at the top of T1
	place it into the cache
	*/
	//page_t* page_ptr = find_mem(page_name);
	insert_in_head(T1, page_name, page_ptr);
	//place it into the cache
	return T1->head;
}