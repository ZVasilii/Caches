/*
INFORMATION
**************
Header that unites all, that need for using doubly linked list
*/

//struct cell - cell of the dl_list
//you can work with it only using functions from dl_cells.h
//struct cache_t - only for using pointers on it
//
//struct list_t - shell for dl_list
//head - the first element of the list (no element - NULL)
//end - the last element of the list (no element - NULL)
//length - number of the list elements
//end and length exists only for convenience and more fast working
//
//functions in header are separated on blocks
//
//first block: for cells
//second block: for list_t
//third block: tests 

#pragma once



struct cache_t;
struct cell;



struct list_t {
    struct cell* head;
    unsigned long long length;
    struct cell* end;
};

//first block of functions
struct cell* make_cell();
struct cell* make_cell_n(long long int name);
struct cell* make_cell_p(struct cache_t* new_page);
struct cell* make_cell_np(long long int name, struct cache_t* new_page);
long long int cell_name(struct cell* c);
void change_cell_name(struct cell* c, long long int new_name);
struct cell* set_cache(struct cell* c, struct cache_t* new_page);
struct cache_t* cell_cache(struct cell* c);
struct cell* extract_cell(struct cell* c);
void destroy_cell(struct cell* c);
void destroy_all_cells(struct cell* c);
struct cell* place_cell_before(struct cell* c, struct cell* place);
struct cell* place_cell_after(struct cell* c, struct cell* place);
struct cell* next_cell(struct cell* c);
struct cell* prev_cell(struct cell* c);
struct cell* find_cell(struct cell* c, long long int name);
unsigned long long cell_num(struct cell* c);
int is_first(struct cell* c);
int is_last(struct cell* c);


//second block of functions
struct list_t* make_list();
void destroy_list(struct list_t* l);
struct cell* find_list_elem(struct list_t* l, long long int name);
struct cell* insert_to_head(struct list_t* l, struct cell* c);
struct cell* replace_lf_to_head(struct list_t* cur, struct list_t* next, struct cell* c);
void delete_last_elem(struct list_t* l);
void print_list(struct list_t* l);
void print_all_lists(struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2);


//third block of functions
//this functions under conditional compilation (watch readme)
void dl_cell_test();
void dl_list_test();
