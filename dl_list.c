#include "dl_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

struct cell {
    struct cell* prev;
    struct cell* next;
    long long int data;
    void* pointer;
};


struct cell* make_cell(long long int name) {
    struct cell* c;
    c = (struct cell*) calloc(1, sizeof (struct cell));
    if(c == NULL) {
        return NULL;
    }
    c->prev = NULL;
    c->next = NULL;
    c->data = name;
    c->pointer = NULL;
    return c;
}

void destroy_cell(struct cell* c) {
    assert(c != NULL);
    free(c);
}

struct cell* place_cell_before(struct cell* c, struct cell* place) {
    assert(c != NULL);
    assert(place != NULL);

    if(c->prev != NULL) {
        c->prev->next = c->next;
    }
    if(c->next != NULL) {
        c->next->prev = c->prev;
    }

    c->prev = place->prev;
    if(c->prev != NULL) {
        c->prev->next = c;
    }
    c->next = place;
    place->prev = c;
    return c;
}

struct cell* place_cell_after(struct cell* c, struct cell* place) {
    assert(c != NULL);
    assert(place != NULL);

    if(c->prev != NULL) {
        c->prev->next = c->next;
    }
    if(c->next != NULL) {
        c->next->prev = c->prev;
    }

    c->next = place->next;
    if(c->next != NULL) {
        c->next->prev = c;
    }
    c->prev = place;
    place->next = c;
    return c;
}

int cell_name(struct cell* c) {
    return c->data;
}

struct cell* next_cell(struct cell* c) {
    return c->next;
}

struct cell* prev_cell(struct cell* c) {
    return c->prev;
}
