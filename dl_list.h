#pragma once

struct cell;
struct page_t;

struct cell* make_cell(long long int name);
void destroy_cell(struct cell* c);
void destroy_list(struct cell* c);
struct cell* place_cell_before(struct cell* c, struct cell* place);
struct cell* place_cell_after(struct cell* c, struct cell* place);
long long int cell_name(struct cell* c);
struct cell* next_cell(struct cell* c);
struct cell* prev_cell(struct cell* c);
struct cell* set_page(struct cell* c, struct page_t* new_page);
void* cell_page(struct cell* c);
struct cell* make_cell_p(long long int name, struct page_t* new_page);
struct cell* find_cell(struct cell* c, long long int name);
unsigned long long list_len(struct cell* c);
int is_first(struct cell* c);
int is_last(struct cell* c);

void list_test();