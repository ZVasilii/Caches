#include "dl_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pages.h"


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

int find(long long int page_name, struct cell* cache_part)
{
	if (find_cell(cache_part, page_name) != NULL)
		return 1;
	else
		return 0;
}

long long int fast_get_page()    //input one page
{
	return 0;
}

void Cache(int c, int pages_count)			//main function of ARC
{									//c is parameter of cache size
									//pages_count is count of pages

	//printf("Start caching\n");
	int p = 0;
	long long int page_name;
	int len_T1 = 0, len_T2 = 0, len_T3 = 0, len_B2 = 0;  //
	struct cell* T1 = make_list(0);
	struct cell* T2 = make_list(0);            //initialization of cache parts
	struct cell* B1 = make_list(0);
	struct cell* B2 = make_list(0);
	
	for (int i = 0; i < pages_count; i++)				//loop of cache working
	{
		page_name = fast_get_page();

		if (find(page_name, T1) || find(page_name, T2))				//case 1
		{
			//move x to the top of T2
		}
		else if (find(page_name, B1))							//case 2
		{
			//p = min(c, p + max(cachesize(B2)/cachesize(B1), 1);
			//replace(p);
			//move x to the top of T2
			//place x into the cache (???)
		}
		else if (find(page_name, B2))							//case 3
		{
			//p = max(0, p - max(cachesize(B1)/cachesize(B2), 1);
			//replace(p);
			//move x to the top of T2
			//place x into the cache (???)
		}
		else											//case 4
		{
			if (cachesize(L1) == c)						//case 4.1
				if (cachesize(T1) < c)
				{
					//delete LRU page of B1
					//replace(p)
				}
				else
				{
					//delete LRU page of T1
					//remove it from the cache
				}
			if ((cachesize(L1) < c) && ((cañhesize(L1) + cañhesize(L2)) >= c))
				if ((cashesize(L1) + cashesize(L2)) == 2 * c)
				{
					//delete the LRU page of B2
					//replace(p)
				}
			//put x at the top of T1
			//place it into the cache
		}
	}

	destroy_list(T1);
	destroy_list(B1);
	destroy_list(T2);
	destroy_list(B2);
	//printf("Stop caching");
}