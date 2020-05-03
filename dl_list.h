#ifndef DL_LIST_H
#define DL_LIST_H

struct cell;

struct cell* make_cell(long long int name);
void destroy_cell(struct cell* c);
struct cell* place_cell_before(struct cell* c, struct cell* place);
struct cell* place_cell_after(struct cell* c, struct cell* place);
int cell_name(struct cell* c);
struct cell* next_cell(struct cell* c);
struct cell* prev_cell(struct cell* c);

#endif // DL_LIST_H
