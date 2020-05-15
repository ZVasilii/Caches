#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "pages.h"
#include "dl_list.h"



struct list_t* make_list() {
    struct list_t* l;
    l = (struct list_t*) calloc(1, sizeof (struct list_t));
    assert(l != NULL);
    l->length = 0;
    l->last_found = NULL;
    l->head = NULL;
    l->end = NULL;
    return l;
}

void destroy_list(struct list_t* l) {
    assert(l != NULL);
    if(l->head != NULL) {
        destroy_all_cells(l->head);
    }
    free(l);
}

struct cell* find_list_elem(struct list_t* l, long long int name) {
    struct cell *c, *s;
    assert(l != NULL);
    c = l->head;
    s = find_cell(c, name);
    l->last_found = s;
    return s;
}

struct cell* insert_to_head(struct list_t* l, struct cell* c) {
    assert(l != NULL);
    assert(c != NULL);
    if(l->head != NULL) {
        place_cell_before(c, l->head);
    }
    l->head = c;
    l->length++;
    if(l->end == NULL) {
        l->end = c;
    }
    return c;
}

struct cell* replace_lf_to_head(struct list_t* cur, struct list_t* next, struct cell* c) {
    assert(cur != NULL);
    assert(cur->head != NULL);
    assert(next != NULL);
    if(c != NULL) {
        cur->last_found = c;
    }
    if(cur->last_found == NULL) {
        return NULL;
    }
    if(cur->last_found == cur->head) {
        cur->head = next_cell(cur->head);
    }
    if(cur->last_found == cur->end) {
        cur->end = prev_cell(cur->end);
    }
    c = extract_cell(cur->last_found);
    cur->last_found = NULL;
    cur->length--;
    insert_to_head(next, c);
    return c;
}

void delete_last_elem(struct list_t* l) {
    struct cell* c;
    assert(l != NULL);
    assert(l->end != NULL);
    c = l->end;
    l->end = prev_cell(l->end);
    if(l->end == NULL) {
        l->head = NULL;
    }
    destroy_cell(c);
    l->length--;
}

void print_list(struct list_t* l) {
    struct cell* c = NULL;
    assert(l != NULL);
    printf("|");
    if(l->head != NULL) {
        printf("%lld", cell_name(l->head));
        c = next_cell(l->head);
    }
    while(c != NULL) {
        printf(", %lld", cell_name(c));
        c = next_cell(c);
    }
    printf("|");
}

void print_all_lists(struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2)
{
    printf("T1:");
    print_list(T1);
    printf("\n");
    printf("T2:");
    print_list(T2);
    printf("\n");
    printf("B1:");
    print_list(B1);
    printf("\n");
    printf("B2:");
    print_list(B2);
    printf("\n");
}