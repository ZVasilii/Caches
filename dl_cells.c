//This file provides work with cells of the doubly linked list

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "dl_list.h"

struct cell {
    struct cell* prev;
    struct cell* next;
    long long int data;
    struct cache_t* cache_ptr;
};

//make cell without name, pointer and connection with other cells
struct cell* make_cell() {
    struct cell* c;
    c = (struct cell*) calloc(1, sizeof (struct cell));
    assert(c != NULL);
    c->prev = NULL;
    c->next = NULL;
    c->data = 0;
    c->cache_ptr = NULL;
    return c;
}

//make cell with name
struct cell* make_cell_n(long long int name) {
    struct cell* c;
    c = make_cell();
    c->data = name;
    return c;
}

//make cell with pointer
struct cell* make_cell_p(struct cache_t* new_page) {
    struct cell* c;
    c = make_cell();
    c->cache_ptr = new_page;
    return c;
}

//make cell with name and pointer
struct cell* make_cell_np(long long int name, struct cache_t* new_page) {
    struct cell* c;
    c = make_cell();
    c->cache_ptr = new_page;
    c->data = name;
    return c;
}

long long int cell_name(struct cell* c) {
    assert((c != NULL)  && "cell not existed");
    return c->data;
}

void change_cell_name(struct cell* c, long long int new_name) {
    assert((c != NULL)  && "cell not existed");
    c->data = new_name;
}

//next two functions for working with cell's pointer on cache
struct cell* set_cache(struct cell* c, struct cache_t* new_page) {
    assert((c != NULL)  && "cell not existed");
    c->cache_ptr = new_page;
    return c;
}

struct cache_t* cell_cache(struct cell* c) {
    assert((c != NULL)  && "cell not existed");
    return c->cache_ptr;
}

//extracting cell from list
//delete connections between c and its neighbours
//bind prev and next cells
struct cell* extract_cell(struct cell* c) {
    assert((c != NULL)  && "cell not existed");
    if(c->prev != NULL) {
        c->prev->next = c->next;
    }
    if(c->next != NULL) {
        c->next->prev = c->prev;
    }
    c->prev = NULL;
    c->next = NULL;
    return c;
}

void destroy_cell(struct cell* c) {
    assert((c != NULL)  && "cell not existed");
    c = extract_cell(c);
    free(c);
}

void destroy_all_cells(struct cell* c) { //all cells which are connected with c
    struct cell* s;
    assert((c != NULL)  && "cell not existed");
    while(1) {
        if(c->prev == c) {
            destroy_cell(c);
            break;
        }
        if(c->prev != NULL) {
            s = c->prev;
            destroy_cell(c);
            c = s;
            continue;
        }
        if(c->next != NULL) {
            s = c->next;
            destroy_cell(c);
            c = s;
            continue;
        }
        destroy_cell(c);
        break;
    }
}

struct cell* place_cell_before(struct cell* c, struct cell* place) { //place c before place
    assert((c != NULL)  && "cell not existed");
    assert((place != NULL)  && "cell not existed");
    c = extract_cell(c);
    c->prev = place->prev;
    if(c->prev != NULL)
    {
        c->prev->next = c;
    }
    c->next = place;
    place->prev = c;
    return c;
}

struct cell* place_cell_after(struct cell* c, struct cell* place) { //place c after place
    assert((c != NULL)  && "cell not existed");
    assert((place != NULL)  && "cell not existed");
    c = extract_cell(c);
    c->next = place->next;
    if(c->next != NULL) {
        c->next->prev = c;
    }
    c->prev = place;
    place->next = c;
    return c;
}

struct cell* next_cell(struct cell* c) {
    assert((c != NULL)  && "cell not existed");
    return c->next;
}

struct cell* prev_cell(struct cell* c) {
    assert((c != NULL)  && "cell not existed");
    return c->prev;
}

//tries to find cell with input name among connected with c
struct cell* find_cell(struct cell* c, long long int name) {
    struct cell *s;
    if(c == NULL) {
        return NULL;
    }
    if(c->data == name) {
        return c;
    }
    s = c->prev;
    while(s != NULL) {
        if(s->data == name) {
            return s;
        }
        if(s == c) {
            return NULL;
        }
        s = s->prev;
    }
    s = c->next;
    while(s != NULL) {
        if(s->data == name) {
            return s;
        }
        if(s == c) {
            return NULL;
        }
        s = s->next;
    }
    return NULL;
}

//count cells connected with c (including c)
unsigned long long cell_num(struct cell* c) {
    unsigned long long len = 1;
    struct cell *s;
    if(c == NULL) {
        return 0;
    }
    s = c->prev;
    while (s != NULL) {
        if(s == c) {
            return len;
        }
        len++;
        s = s->prev;
    }
    s = c->next;
    while (s != NULL) {
        len++;
        s = s->next;
    }
    return len;
}

int is_first(struct cell* c) {
    assert((c != NULL)  && "cell not existed");
    if(c->prev == NULL) {
        return 1;
    }
    return 0;
}

int is_last(struct cell* c) {
    assert((c != NULL)  && "cell not existed");
    if(c->next == NULL) {
        return 1;
    }
    return 0;
}