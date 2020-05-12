#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "dl_list.h"

static int comparator(const void* a, const void* b);
static int* generate_arr(unsigned long long size);
static void ins_sort(int* arr, unsigned long long size, int (*comp) (const void*, const void*));
static struct cell* make_arr_l(int* arr, unsigned long long size);
static void rewrite(int* arr, struct cell* arr_l, unsigned long long size);

void list_test() {
    unsigned long long size = 10000;
    int *arr, *arr_copy;
    arr = generate_arr(size);
    arr_copy = (int*) calloc(size, sizeof (int));
    assert(arr_copy != NULL);
    memcpy(arr_copy, arr, size * sizeof (int));
    qsort(arr, size, sizeof (int), comparator);
    ins_sort(arr_copy, size, comparator);
    assert(memcmp(arr, arr_copy, size * sizeof (int)) == 0);
    free(arr_copy);
    free(arr);
    printf("test complete");
}

static int comparator(const void* a, const void* b) {
    const int *x = (const int*) a;
    const int *y = (const int*) b;
    return *x - *y;
}

static int* generate_arr(unsigned long long size) {
    int* arr;
    unsigned long long i;
    arr = (int*) calloc(size, sizeof (int));
    assert(arr != NULL);
    srand(time(NULL));
    for(i = 0; i < size; i++) {
        arr[i] = rand() % 1000000;
    }
    return arr;
}

static void ins_sort(int* arr, unsigned long long size, int (*comp) (const void*, const void*)) {
    struct cell* arr_l, *n, *i, *buff;
    int x, y;
    assert(arr != NULL);

    arr_l = make_arr_l(arr, size);

    n = arr_l;
    do {
        n = next_cell(n);
        i = prev_cell(n);
        x = (int) cell_name(n);
        while(i != NULL) {
            y = (int) cell_name(i);
            if(comp(&y, &x) <= 0) {
                buff = prev_cell(n);
                place_cell_after(n, i);
                if(buff != i) {
                    n = buff;
                }
                break;
            }
            i = prev_cell(i);
        }
        if(i == NULL) {
            buff = prev_cell(n);
            arr_l = place_cell_before(n, arr_l);
            n = buff;
        }
    } while(is_last(n) == 0);

    rewrite(arr, arr_l, size);
    destroy_list(arr_l);
}

static struct cell* make_arr_l(int* arr, unsigned long long size) {
    struct cell *first, *cur, *last;
    unsigned long long i;
    assert(size > 0);
    assert(arr != NULL);

    first = make_cell_n((long long) arr[0]);
    assert(first != NULL);
    last = first;
    for(i = 1; i < size; i++) {
        cur = make_cell_n((long long) arr[i]);
        place_cell_after(cur, last);
        last = cur;
    }
    return first;
}

static void rewrite(int* arr, struct cell* arr_l,  unsigned long long size) {
    unsigned long long i;
    struct cell* cur;
    assert(arr != NULL);
    assert(arr_l != NULL);
    assert(size == list_len(arr_l));
    cur = arr_l;
    for(i = 0; i < size; i++) {
        assert(cur != NULL);
        arr[i] = (int) cell_name(cur);
        cur = next_cell(cur);
    }
}
