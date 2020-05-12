#include "dl_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


/*
now we need to
1)connect parts of cache with initialization function of list (function initialization)
2)connect with function of getting page (function get_page)
3)create function of finding element in parts (function find)
4)get informmation about cache part size (maybe new function cachesize)
*/


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

void Cache(int c, int pages_count)			//main function of ARC
{									//c is parameter of cache size
									//pages_count is count of pages

	//printf("Start caching\n");
	int p = 0;
	struct page x;
	struct list T1 = initialization(...);
	struct list T2 = initialization(...);               //initialization of cache parts
	struct list B1 = initialization(...);
	struct list B2 = initialization(...);
	
	for (int i = 0; i < pages_count; i++)				//loop of cache working
	{
		x = get_page();

		if ((find(x, &T1) || (find(x, &T2))				//case 1
		{
			//move x to the top of T2
		}
		else if (find(x, &B1))							//case 2
		{
			//p = min(c, p + max(cachesize(B2)/cachesize(B1), 1);
			//replace(p);
			//move x to the top of T2
			//place x into the cache (???)
		}
		else if (find(x, &B2))							//case 3
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
			if ((cachesize(L1) < c) && ((cashesize(L1) + cashesize(L2)) >= c))
				if ((cashesize(L1) + cashesize(L2)) == 2 * c)
				{
					//delete the LRU page of B2
					//replace(p)
				}
			//put x at the top of T1
			//place it into the cache
		}
	}

	//printf("Stop caching");
}