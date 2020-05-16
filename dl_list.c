#include <stdio.h>
#include <assert.h>

#include "pages.h"
#include "dl_list.h"


//creating dl_list without any cells
struct list_t* make_list() {
    struct list_t* l;
    l = (struct list_t*)calloc(1, sizeof (struct list_t));
    if(l == NULL) {
        return NULL;
    }
    l->length = 0;
    l->head = NULL;
    l->end = NULL;
    return l;
}

//destroying dl_list with all cells in it
void destroy_list(struct list_t* l) {
    assert((l != NULL)  && "list not existed");
    if(l->head != NULL) {
        destroy_all_cells(l->head);
    }
    free(l);
}


struct cell* find_list_elem(struct list_t* l, long long int name) {
    struct cell *c;
    assert((l != NULL)  && "list not existed");
    c = l->head;
    c = find_cell(c, name);
    return c;
}

struct cell* insert_to_head(struct list_t* l, struct cell* c) {
    assert((l != NULL)  && "list not existed");
    assert((c != NULL)  && "cell not existed");
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
    assert((cur != NULL) && "list not existed");
    assert((next != NULL) && "list not existed");
    if(c == NULL) {
        return NULL;
    }
    assert((cur->head != NULL) && "no cells for replacing");
    if(c == cur->head) {
        cur->head = next_cell(cur->head);
    }
    if(c == cur->end) {
        cur->end = prev_cell(cur->end);
    }
    c = extract_cell(c);
    cur->length--;
    insert_to_head(next, c);
    return c;
}

void delete_last_elem(struct list_t* l) {
    struct cell* c;
    assert((l != NULL) && "list not existed");
    assert((l->end != NULL) && "nothing to delete");
    c = l->end;
    l->end = prev_cell(l->end);
    if(l->end == NULL) {
        l->head = NULL;
    }
    destroy_cell(c);
    l->length--;
}

//printing dl_list in format |name1, name2, name3|
void print_list(struct list_t* l) {
    struct cell* c = NULL;
    assert((l != NULL) && "printing list not existed");
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

//printing all four lists
void print_all_lists(struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2) {
    assert((T1 != NULL) && (T2 != NULL) && (B1 != NULL) && (B2 != NULL) && "not all printing lists are existed");
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
