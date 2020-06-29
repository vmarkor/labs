/*
 * 3. 
 * Реализовать функцию слияния двух отсортированных связных списков. 
 * Функция должнакорректно обрабатывать все крайние случаи
 * 
*/

#include <stdio.h>
#include "linked_list.h"

// Takes two sorted (descending) linked lists and merges them into new sorted list.
// If given not sorted lists, result is undefined.
linked_list* merge_sorted(linked_list* a, linked_list* b)
{
    linked_list* merged = calloc(1, sizeof(linked_list));

    int cur_a = 0;
    int cur_b = 0;
    int a_len = len(a);
    int b_len = len(b);
    
    while (cur_a + cur_b < a_len + b_len)
    {
        if (cur_a < a_len && cur_b >= b_len)
        {
            push(merged, a->next->el);
            a = a->next;
            cur_a++;
        }
        else if (cur_b < b_len && cur_a >= a_len)
        {
            push(merged, b->next->el);
            b = b->next;
            cur_b++;
        }
        else if (a->next->el >= b->next->el)
        {
            push(merged, a->next->el);
            a = a->next;
            cur_a++;
        }
        else if (b->next->el >= a->next->el)
        {
            push(merged, b->next->el);
            b = b->next;
            cur_b++;
        }
    }

    return merged;
}

void test_merge0()
{
    puts("\n---test0---\n");

    linked_list* a = calloc(1, sizeof(linked_list));
    linked_list* b = calloc(1, sizeof(linked_list));

    // push(a, 7);
    // push(a, 4);
    // push(a, 1);
    // push(a, -12);

    // push(b, 6);
    // push(b, 3);

    linked_list* merged = merge_sorted(a, b);

    puts("first: ");
    print(a);
    puts("\nsecond: ");
    print(b);
    puts("\nmerged: ");
    print(merged);
    puts("");

    free_list(a);
    free_list(b);
    free_list(merged);
}

void test_merge1()
{
    puts("\n---test1---\n");

    linked_list* a = calloc(1, sizeof(linked_list));
    linked_list* b = calloc(1, sizeof(linked_list));

    push(a, 7);
    // push(a, 4);
    // push(a, 1);
    // push(a, -12);

    // push(b, 6);
    // push(b, 3);

    linked_list* merged = merge_sorted(a, b);

    puts("first: ");
    print(a);
    puts("\nsecond: ");
    print(b);
    puts("\nmerged: ");
    print(merged);
    puts("");

    free_list(a);
    free_list(b);
    free_list(merged);
}

void test_merge2()
{
    puts("\n---test2---\n");

    linked_list* a = calloc(1, sizeof(linked_list));
    linked_list* b = calloc(1, sizeof(linked_list));

    // push(a, 7);
    // push(a, 4);
    // push(a, 1);
    // push(a, -12);

    push(b, 6);
    // push(b, 3);

    linked_list* merged = merge_sorted(a, b);

    puts("first: ");
    print(a);
    puts("\nsecond: ");
    print(b);
    puts("\nmerged: ");
    print(merged);
    puts("");

    free_list(a);
    free_list(b);
    free_list(merged);
}

void test_merge3()
{
    puts("\n---test3---\n");

    linked_list* a = calloc(1, sizeof(linked_list));
    linked_list* b = calloc(1, sizeof(linked_list));

    push(a, 7);
    push(a, 4);
    // push(a, 1);
    // push(a, -12);

    push(b, 6);
    push(b, 3);

    linked_list* merged = merge_sorted(a, b);

    puts("first: ");
    print(a);
    puts("\nsecond: ");
    print(b);
    puts("\nmerged: ");
    print(merged);
    puts("");

    free_list(a);
    free_list(b);
    free_list(merged);
}

void test_merge4()
{
    puts("\n---test4---\n");

    linked_list* a = calloc(1, sizeof(linked_list));
    linked_list* b = calloc(1, sizeof(linked_list));

    push(a, 7);
    push(a, 4);
    push(a, 1);
    push(a, -12);

    push(b, 6);
    push(b, 3);

    linked_list* merged = merge_sorted(a, b);

    puts("first: ");
    print(a);
    puts("\nsecond: ");
    print(b);
    puts("\nmerged: ");
    print(merged);
    puts("");

    free_list(a);
    free_list(b);
    free_list(merged);
}

void test_merge5()
{
    puts("\n---test5---\n");

    linked_list* a = calloc(1, sizeof(linked_list));
    linked_list* b = calloc(1, sizeof(linked_list));

    push(a, 1);
    push(a, 2);
    push(a, 3);
    push(a, 4);

    push(b, 3);
    push(b, 2);
    push(b, 1);

    linked_list* merged = merge_sorted(a, b);

    puts("first: ");
    print(a);
    puts("\nsecond: ");
    print(b);
    puts("\nmerged: ");
    print(merged);
    puts("");

    free_list(a);
    free_list(b);
    free_list(merged);
}

int main()
{
    test_merge0();
    test_merge1();
    test_merge2();
    test_merge3();
    test_merge4();
    test_merge5();
    return 0;
}
