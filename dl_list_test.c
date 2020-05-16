/*
INFORMATION
****************************
Functions for testing struct list
*/


#ifdef LIST_TEST

#include <assert.h>
#include <stdio.h>

#include "dl_list.h"

static struct list_t* fill_list_with_cells(struct list_t* l, int n);
static void reverse_cells(struct list_t* l, struct list_t* m, int n);
static void delete_cells(struct list_t* l, int n);

void dl_list_test() {
    const int n = 10000;
    struct list_t *l, *m;
    l = make_list();
    assert(l != NULL);
    l = fill_list_with_cells(l, n);
    printf("dl_list test level 1 complete\n");
    m = make_list();
    assert(m != NULL);
    reverse_cells(l, m, n);
    printf("dl_list test level 2 complete\n");
    delete_cells(m, n);
    destroy_list(l);
    destroy_list(m);
    printf("dl_list test level 3 complete\n");
    printf("dl_list test complete\n");
}

static struct list_t* fill_list_with_cells(struct list_t* l, int n) {
    int i;
    struct cell* c;
    assert(l != NULL);
    for(i = 0; i < n; i++) {
        c = make_cell_n((long long int) i);
        insert_to_head(l, c);
    }
    assert(l->length == (unsigned long long) n);
    c = l->head;
    for(i = 0; i < n - 1; i++) {
        assert(c != NULL);
        assert(cell_name(c) - 1 == cell_name(next_cell(c)));
        c = next_cell(c);
    }
    assert(c == l->end);
    return l;
}

static void reverse_cells(struct list_t* l, struct list_t* m, int n) {
    int i;
    struct cell* c;
    assert(l != NULL);
    assert(m != NULL);
    while(l->length != 0) {
        replace_lf_to_head(l, m, l->head);
    }
    assert(m->length == (unsigned long long) n);
    c = m->head;
    for(i = 0; i < n - 1; i++) {
        assert(c != NULL);
        assert(cell_name(c) + 1 == cell_name(next_cell(c)));
        c = next_cell(c);
    }
    assert(c == m->end);
}

static void delete_cells(struct list_t* l, int n) {
    assert(l != NULL);
    assert(l->length == (unsigned long long) n);
    while(n != 0) {
        assert(l->head != NULL);
        assert(l->end != NULL);
        assert(l->length > 0);
        delete_last_elem(l);
        n--;
    }
    assert(l->length == 0);
    assert(l->head == NULL);
    assert(l->end == NULL);
}
#endif
