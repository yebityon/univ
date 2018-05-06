/*********************************************
 prog4-2.c
 Student ID:
 Name:
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//ここから
#include <iostream>
using namespace std;
//ここまでを消す
struct element {
    int value;
    struct element *prev;
    struct element *next;
};

struct list {
    struct element *top;
    struct element *rear;
    int size;
};

struct list *create_list();
struct element *create_element(int value);
void print_list(struct list *list);
void print_reverse_list(struct list *list);

void insert_front(struct list *list, struct element *elem);
void insert_rear(struct list *list, struct element *elem);
void delete_front(struct list *list);
void delete_rear(struct list *list);

int size_of_list(struct list *list);
struct element *get_from_list(struct list *list, int index);

struct list *create_list();
struct element *create_element(int value);
void print_list(struct list *list);
void print_reverse_list(struct list *list);

struct list *create_list()
{
    struct list *List = (struct list *) malloc(sizeof(struct list));
    List -> top = List -> rear = NULL;
    return List;
}

struct element *create_element(int value){
    struct element *temp = (struct element *)malloc(sizeof(struct element));
    temp -> value = value;
    temp -> next = temp->prev = NULL;
    return temp;
}

void print_list(struct list *list)
{
    struct list  temp = *list;
    while(temp.top != NULL){
        printf("value : %d\n",temp. top-> value);
        temp . top = temp . top -> next;
    }
    
}

void print_reverse_list(struct list *list)
{
    
    struct list * temp = list;
    while(temp->rear != NULL){
        printf("value : %d\n",temp -> rear-> value);
        temp -> rear = temp -> rear -> prev;
    }
}

void insert_front(struct list *list, struct element *elem)
{
    if(list -> top == NULL){
        list -> top  = elem;
    } else {
        struct element *temp = list -> top;
        list -> top  = elem;
        elem -> next = temp;
        temp -> prev = elem;
    }
}

void insert_rear(struct list *list, struct element *elem)
{
    //given list size is Zero
    if(list -> rear == NULL){
        list -> top = list -> rear = elem;
    } else {
        struct element *temp = list -> rear;
        list -> rear = elem;
        elem -> prev = temp;
        temp -> next = elem;
    }
}

void delete_front(struct list *list)
{
    if(list -> top == NULL){
        //given list size is zero
        // return NULL
        return;
    } else if(list -> rear == list -> top){
        //given list size is one
        struct element *temp =  list -> top;
        list -> top = list -> rear  = NULL;
        free(temp);
    } else {
        // temp will be erased
        struct element *temp = list -> top;
        list -> top = temp -> next;
        free(temp);
    }
}

void delete_rear(struct list *list)
{
}

int size_of_list(struct list *list)
{
    return 0;
}

struct element *get_from_list(struct list *list, int index)
{
    return NULL;
}

/*=============================================*/

int main()
{
    return 0;
}
void test1()
{
    struct list *list = create_list();
    
    struct element *e1 = create_element(10);
    struct element *e2 = create_element(20);
    
    list->top = e1;
    e1->next = e2;
    e1->prev = NULL;
    e2->next = NULL;
    e2->prev = e1;
    list->rear = e2;
    
    assert(list->top->value == 10);
    assert(list->top->next->value == 20);
    assert(list->rear->value == 20);
    assert(list->rear->prev->value == 10);
    
    print_list(list);
    printf("----\n");
    print_reverse_list(list);
    printf("Success: %s\n", __func__);
}

