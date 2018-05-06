/*********************************************
 prog4-3.c
 Student ID:26001701940
 Name:崎山雄司
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

void insert_at(struct list *list, int index, struct element *elem);
void delete_at(struct list *list, int index);
struct list *append(struct list *first, struct list *second);

struct list *create_list()
{
    struct list *List = (struct list *) malloc(sizeof(struct list));
    List -> top = List -> rear = NULL;
    List -> size = 0;
    return List;
}

struct element *create_element(int value)
{
    struct element *temp = (struct element *)malloc(sizeof(struct element));
    temp -> value = value;
    temp -> next = temp->prev = NULL;
    return temp;
}

void print_list(struct list *list)
{
    struct list  temp = *list;
    while(temp.top != NULL){
        printf("value : %d\n",temp . top-> value);
        temp . top = temp . top -> next;
    }
}

void print_reverse_list(struct list *list)
{
    struct list  temp = *list;
    while(temp.rear != NULL){
        printf("value : %d\n",temp . rear-> value);
        temp . rear = temp . rear -> prev;
    }
}

void insert_front(struct list *list, struct element *elem)
{
    list -> size ++;
    if(list -> top == NULL){
        list -> top = elem;
        list -> rear=  elem;
        return;
    } else {
        elem -> next = list -> top;
        list -> top = elem;
    }
}

void insert_rear(struct list *list, struct element *elem)
{
    list -> size ++;
    if(list -> rear == NULL){
        list -> top = list -> rear = elem;
        return;
    } else {
        struct element *temp = list -> rear;
        temp -> next = elem;
        elem -> prev = temp;
        list -> rear = elem;
    }
}

void delete_front(struct list *list)
{
    //list size is 0
    if(list -> top == NULL) return;
    //list size is 1
    if(list -> top -> next == NULL){
        free(list -> top -> next);
        list -> top =list -> rear = NULL;
        list -> size --;
        return;
    }
    struct element *erased = list -> top;
    list -> top = erased -> next;
    erased -> next -> prev = NULL;
    list -> size --;
    free(erased);
}

void delete_rear(struct list *list)
{
    //list size is 0
    if(list -> top == NULL) return;
    //list size is 1
    if(list -> top -> next == NULL){
        free(list -> top -> next);
        list -> top =list -> rear = NULL;
        return;
    }
    struct element *erased = list -> rear;
    list -> rear = erased -> prev;
    erased -> prev -> next = NULL;
    list -> size --;
    free(erased);
}

int size_of_list(struct list *list)
{
    int size = 0;
    struct list temp = *list;
    while(temp.top   != NULL){
        size++;
        if(temp.top)
            temp.top = temp.top -> next;
    }
    return size;
    
}

struct element *get_from_list(struct list *list, int index)
{
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    
    struct element *cur = list->top;
    for (int i = 0; i < list->size; i++) {
        if (i == index) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void insert_at(struct list *list, int index, struct element *elem)
{
    
}

void delete_at(struct list *list, int index)
{
    
}

struct list *append(struct list *first, struct list *second)
{
    return NULL;
}

/*=============================================*/

int main()
{
    return 0;
}
