#include "dl_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pages.h"

const int c = 10;

struct list {
	struct cell* head;
	int size;
};

void replace(p)
{
	// if ((cachesize(T1) >=1) && ((find(x, B2) && (cachesize(T1) == p)) || (cachesize(T1) >= p)))
	//{
	//move LRU page of T1 to the bottom of B1
	//remove it from the cache
	//}
	// else
	//{
	//move LRU page of T2 to the bottom of B2
	//remove it from the cache
	//}
}

int fast_get_page(long long int page_name, struct list* T1, struct list* T2, struct list* B1, struct list* B2, int *p)			//main function of ARC
{									

	//int p = 0;
	//long long int page_name;
	//struct cell* T1 = make_list(0);
	//struct cell* T2 = make_list(0);            //initialization of cache parts
	//struct cell* B1 = make_list(0);
	//struct cell* B2 = make_list(0);
	int T1_size = (*T1).size;

	struct cell* page_in_T1 = find_cell(T1, page_name);
	struct cell* page_in_T2 = find_cell(T2, page_name);
	if ((page_in_T1 != NULL) || (page_in_T2 != NULL))				//case 1
	{
		//move x to the top of T2
		if (page_in_T1 != NULL)
		{
			destroy_cell(page_in_T1);
			(*T1).size--;
		}
		if (page_in_T2 != NULL)
			destroy_cell(page_in_T2);
		//function of moving x to the top of T2
		return 0;
	}

	struct cell* page_in_B1 = find_cell(B1, page_name);
	if (page_in_B1 != NULL)							//case 2
	{
		*p = min(c, p + max(((*B2).size) /((*B1).size), 1));
		replace(p);
		//function of moving x to the top of T2
		//place x into the cache (???)
		return 0;
	}

	struct cell* page_in_B2 = find_cell(B2, page_name);
	if (page_in_B2 != NULL)								//case 3
	{
		*p = max(0, p - max(((*B1).size) / ((*B2).size), 1));
		replace(p);
		//function of moving x to the top of T2
		//place x into the cache (???)
		return 0;
	}


	int L1_size = (((*B1).size) + ((*T1).size));
	int L2_size = (((*B2).size) + ((*T2).size));
	if (L1_size == c)						//case 4.1
		if (((*T1).size) < c)
		{
			//delete LRU page of B1
			replace(p);
		}
		else
		{
			//delete LRU page of T1
			//remove it from the cache
		}			
	else if ((L1_size < c) && ((L1_size + L2_size) >= c))  //case 4.2
		if ((L1_size + L2_size) == (2 * c))
		{
			//delete the LRU page of B2
			replace(p);
		}		

		//put x at the top of T1
		//place it into the cache
		slow_get_page(page_name);
}