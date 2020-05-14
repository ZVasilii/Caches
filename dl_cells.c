#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "pages.h"
#include "dl_list.h"



struct cell {
    struct cell* prev;
    struct cell* next;
    long long int data;
    struct cache_t* cache_ptr;
};

static void close_hole(struct cell* c);

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

void destroy_cell(struct cell* c) {
    assert(c != NULL);
    close_hole(c);
    free(c);
}

struct cell* place_cell_before(struct cell* c, struct cell* place) {
    assert(c != NULL);
    assert(place != NULL);
    close_hole(c);
    c->prev = place->prev;
    if(c->prev != NULL)
    {
        c->prev->next = c;
    }
    c->next = place;
    place->prev = c;
    return c;
}

struct cell* place_cell_after(struct cell* c, struct cell* place) {
    assert(c != NULL);
    assert(place != NULL);
    close_hole(c);
    c->next = place->next;
    if(c->next != NULL) {
        c->next->prev = c;
    }
    c->prev = place;
    place->next = c;
    return c;
}

long long int cell_name(struct cell* c) {
    assert(c != NULL);
    return c->data;
}

struct cell* next_cell(struct cell* c) {
    assert(c != NULL);
    return c->next;
}

struct cell* prev_cell(struct cell* c) {
    assert(c != NULL);
    return c->prev;
}

void destroy_all_cells(struct cell* c) {
    struct cell* s;
    assert(c != NULL);
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

struct cell* set_page(struct cell* c, struct cache_t* new_page) {
    assert(c != NULL);
    c->cache_ptr = new_page;
    return c;
}

struct cache_t* cell_page(struct cell* c) {
    assert(c != NULL);
    return c->cache_ptr;
}

static void close_hole(struct cell* c) {
    if(c->prev != NULL) {
        c->prev->next = c->next;
    }
    if(c->next != NULL) {
        c->next->prev = c->prev;
    }
}

struct cell* make_cell_n(long long int name) {
    struct cell* c;
    c = make_cell();
    c->data = name;
    return c;
}

struct cell* make_cell_p(struct cache_t* new_page) {
    struct cell* c;
    c = make_cell();
    c->cache_ptr = new_page;
    return c;
}

struct cell* make_cell_np(long long int name, struct cache_t* new_page) {
    struct cell* c;
    c = make_cell();
    c->cache_ptr = new_page;
    c->data = name;
    return c;
}

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

unsigned long long cell_num(struct cell* c) {
    unsigned long long len = 1;
    struct cell *s;
    assert(c != NULL);
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
    assert(c != NULL);
    if(c->prev == NULL) {
        return 1;
    }
    return 0;
}

int is_last(struct cell* c) {
    assert(c != NULL);
    if(c->next == NULL) {
        return 1;
    }
    return 0;
}

void change_cell_name(struct cell* c, long long int new_name) {
    assert(c != NULL);
    c->data = new_name;
}

struct cell* extract_cell(struct cell* c) {
    assert(c != NULL);
    close_hole(c);
    return c;
}
