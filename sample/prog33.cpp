/*********************************************
 prog3-3.c
 Student ID:26001701940
 Name:崎山雄司サキヤマ
 **********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int cnt =0;
struct element {
    int value;
    struct element *next;
};

struct list {
    struct element *top;
    int size;
};

struct list *create_list();
struct element *create_element(int value);
void print_list(struct list *list);

void insert_front(struct list *list, struct element *elem);
void insert_rearm(struct list *list, struct element *elem);
void delete_front(struct list *list);
void delete_rear(struct list *list);

int size_of_list(struct list *list);
struct element *get_from_list(struct list *list, int index);

struct list *create_list()
{
    struct list  *temp = (struct list *)malloc(sizeof(struct list));
    temp ->top = NULL;
    temp ->size= 0;
    return temp;
}

struct element *create_element(int value)
{
    struct element *temp;
    temp = (struct element *)malloc(sizeof(struct element));
    temp -> value = value;
    temp -> next = NULL;
    return temp;
}

void print_list(struct list *list)
{
    struct list temp = *list;
    while(temp.top!= NULL){
        printf("value %d\n",temp.top->value);
        temp.top = temp.top->next;
    }
}

void insert_front(struct list *list, struct element *elem)
{
    list -> size++;
    if(list ->top == NULL){
        list -> top = elem;
        list ->top -> next = NULL;
    }else{
        elem -> next = list -> top;
        list -> top = elem;
    }
}


void insert_rear(struct list *list, struct element *elem)
{
    struct list temp = *list;
    list -> size ++;
    if(temp.top == NULL){
        list -> top = elem;
        list ->top -> next = NULL;
    } else {
        while(temp.top -> next != NULL){
            temp.top  = temp.top -> next;
        }
        temp.top->next =  elem;
        temp.top -> next -> next = NULL;
    }
    
}

void delete_front(struct list *list)
{
    struct element *temp = list -> top;
    list -> top = list ->top ->next;
    free(temp);
    
}

void delete_rear(struct list *list)
{
    struct list temp = *list;
    struct list before = *list;
    //list size is 0
    if(list -> top == NULL) return;
    //list size is 1
    if(list -> top -> next == NULL){
        free(list -> top -> next);
        list -> top = NULL;
        return;
    }
    while(temp.top -> next  != NULL) {
        before.top = temp.top;
        temp.top = temp.top -> next;
    }
    
    struct element *erased = temp.top;
    before.top -> next = NULL;
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

/*=============================================*/

void test1()
{
    struct list *list = create_list();
    assert(size_of_list(list) == 0);
    insert_front(list, create_element(10));
    assert(list->top->value == 10);
    assert(get_from_list(list, 0)->value == 10);
    assert(size_of_list(list) == 1);
    insert_front(list, create_element(20));
    assert(get_from_list(list, 0)->value == 20);
    assert(get_from_list(list, 1)->value == 10);
    assert(size_of_list(list) == 2);
    
    print_list(list);
    printf("Success: %s\n", __func__);
}

void test2()
{
    struct list *list = create_list();
    assert(size_of_list(list) == 0);
    
    insert_front(list, create_element(10));
    printf("%d",get_from_list(list, 0)->value);
    assert(get_from_list(list, 0)->value == 10);
    assert(size_of_list(list) == 1);
    
    insert_front(list, create_element(20));
    assert(get_from_list(list, 0)->value == 20);
    assert(get_from_list(list, 1)->value == 10);
    assert(size_of_list(list) == 2);
    
    insert_front(list, create_element(30));
    assert(get_from_list(list, 0)->value == 30);
    assert(get_from_list(list, 1)->value == 20);
    assert(get_from_list(list, 2)->value == 10);
    
    assert(get_from_list(list, -1) == NULL);
    assert(get_from_list(list, 3) == NULL);
    
    print_list(list);
    printf("Success: %s\n", __func__);
}

void test3()
{
    struct list *list = create_list();
    assert(size_of_list(list) == 0);
    
    insert_rear(list, create_element(10));
    assert(get_from_list(list, 0)->value == 10);
    assert(size_of_list(list) == 1);
    
    insert_rear(list, create_element(20));
    assert(get_from_list(list, 0)->value == 10);
    assert(get_from_list(list, 1)->value == 20);
    assert(size_of_list(list) == 2);
    
    insert_rear(list, create_element(30));
    assert(get_from_list(list, 0)->value == 10);
    assert(get_from_list(list, 1)->value == 20);
    assert(get_from_list(list, 2)->value == 30);
    assert(size_of_list(list) == 3);
    
    print_list(list);
    printf("Success: %s\n", __func__);
}

void test4()
{
    struct list *list = create_list();
    assert(size_of_list(list) == 0);
    
    insert_front(list, create_element(10));
    assert(get_from_list(list, 0)->value == 10);
    assert(size_of_list(list) == 1);
    
    insert_front(list, create_element(20));
    assert(get_from_list(list, 0)->value == 20);
    assert(get_from_list(list, 1)->value == 10);
    assert(size_of_list(list) == 2);
    
    delete_front(list);
    assert(get_from_list(list, 0)->value == 10);
    assert(get_from_list(list, 1) == NULL);
    assert(size_of_list(list) == 1);
    
    delete_front(list);
    assert(list->top == NULL);
    assert(get_from_list(list, 0) == NULL);
    assert(size_of_list(list) == 0);
    
    insert_front(list, create_element(10));
    insert_front(list, create_element(30));
    assert(get_from_list(list, 0)->value == 30);
    assert(get_from_list(list, 1)->value == 10);
    assert(size_of_list(list) == 2);
    
    print_list(list);
    printf("Success: %s\n", __func__);
}

void test5()
{
    struct list *list = create_list();
    assert(size_of_list(list) == 0);
    
    insert_rear(list, create_element(10));
    assert(get_from_list(list, 0)->value == 10);
    assert(size_of_list(list) == 1);
    
    insert_rear(list, create_element(20));
    assert(get_from_list(list, 0)->value == 10);
    assert(get_from_list(list, 1)->value == 20);
    assert(size_of_list(list) == 2);
    delete_rear(list);
    assert(get_from_list(list, 0)->value == 10);
    assert(get_from_list(list, 1) == NULL);
    assert(size_of_list(list) == 1);
    
    delete_rear(list);
    assert(list->top == NULL);
    assert(get_from_list(list, 0) == NULL);
    assert(size_of_list(list) == 0);
    
    insert_rear(list, create_element(10));
    insert_rear(list, create_element(30));
    assert(get_from_list(list, 0)->value == 10);
    assert(get_from_list(list, 1)->value == 30);
    assert(size_of_list(list) == 2);
    
    print_list(list);
    printf("Success: %s\n", __func__);
}

void test6()
{
    struct list *list = create_list();
    assert(size_of_list(list) == 0);
    
    insert_front(list, create_element(20));
    assert(get_from_list(list, 0)->value == 20);
    assert(size_of_list(list) == 1);
    
    insert_rear(list, create_element(30));
    assert(get_from_list(list, 0)->value == 20);
    assert(get_from_list(list, 1)->value == 30);
    assert(size_of_list(list) == 2);
    
    insert_front(list, create_element(10));
    assert(get_from_list(list, 0)->value == 10);
    assert(get_from_list(list, 1)->value == 20);
    assert(get_from_list(list, 2)->value == 30);
    assert(get_from_list(list, 3) == NULL);
    assert(size_of_list(list) == 3);
    
    print_list(list);
    printf("Success: %s\n", __func__);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    
    return 0;
}
