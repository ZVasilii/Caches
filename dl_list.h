#ifndef DL_LIST_H
#define DL_LIST_H

struct cell;

struct cell* make_cell(long long int name);
void destroy_cell(struct cell* c);
void destroy_list(struct cell* c);
struct cell* place_cell_before(struct cell* c, struct cell* place);
struct cell* place_cell_after(struct cell* c, struct cell* place);
long long int cell_name(struct cell* c);
struct cell* next_cell(struct cell* c);
struct cell* prev_cell(struct cell* c);
struct cell* set_pointer(struct cell* c, void* pointer);
void* cell_pointer(struct cell* c);
struct cell* make_cell_p(long long int name, void* pointer);
struct cell* find_cell(struct cell* c, long long int name);
unsigned long long list_len(struct cell* c);

#endif // DL_LIST_H
