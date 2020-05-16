#MAKEFILE:
#Options:

#	contest - For testing in contest mode (HW8)
#	min - Output without printing pages
#	normal - output in the "canonical" form
#	debug - Output with debug information

#Conditional compilation flags and their meanings:

#	-DDELAY - Adds artificial delay when accessing memory/cache MEM_DELAY and CACHE_DELAY
#	-DTIME - Adds time counting which is spent during requests
#	-DPRINT - Adds the print of requested pages to the console
#	-DPRINT_REQ - Adds printing of auxiliary/debugging information when caching (List contents, CACHE MISS indicator)
#	-DSTATS - Adds printing of constant state information for further analysis
#	-DCOLORS - Colorizes boring life in bright colors (Works on Linux only)


min:
	gcc  main_test.c dl_cells.c dl_list.c ARC.c -DDELAY -DTIME  -DSTATS   -o TEST

debug:
	gcc  main_test.c dl_cells.c dl_list.c ARC.c -Wall -Wpedantic  -DDELAY -DPRINT_REQ -DTIME -DCOLORS -DSTATS -DPRINT  -g  -o TEST

contest:
	gcc  main_test.c dl_cells.c dl_list.c ARC.c  -DCONTEST  -o TEST	

normal:
	gcc  main_test.c dl_cells.c dl_list.c ARC.c -DDELAY -DTIME -DPRINT -DCOLORS -DSTATS  -o TEST

