min:
	gcc  main_test.c dl_cells.c dl_list.c ARC.c -DDELAY -DTIME  -DSTATS   -o TEST

debug:
	gcc  main_test.c dl_cells.c dl_list.c ARC.c -Wall -Wpedantic  -DDELAY -DPRINT_REQ -DTIME -DCOLORS -DSTATS -DPRINT  -g  -o TEST

contest:
	gcc  main_test.c dl_cells.c dl_list.c ARC.c  -DCONTEST  -o TEST	

normal:
	gcc  main_test.c dl_cells.c dl_list.c ARC.c -DDELAY -DTIME -DPRINT -DCOLORS -DSTATS  -o TEST

