/*
[链表-维基](https://zh.wikipedia.org/wiki/%E9%93%BE%E8%A1%A8)
[双向链表-维基](https://zh.wikipedia.org/wiki/%E5%8F%8C%E5%90%91%E9%93%BE%E8%A1%A8)
[链式存储结构-百度百科](https://baike.baidu.com/item/%E9%93%BE%E5%BC%8F%E5%AD%98%E5%82%A8%E7%BB%93%E6%9E%84/4921270)

线性表的链式存储结构是指用一组任意的存储单元存储线性表的数据元素(这组存储单元可以是连续的,也可以是不连续的)。

双向链表（Double Linked List）是在单链表的每个节点中，再设置一个指向其前驱节点的指针域。

双向循环链表（Double Circular Linked List）只在双向链表的基础上，将其首尾节点进行双向连接。

《数据结构-入门指南》 - xubeijun/续杯君
[第1节 线性表是什么 - 链式存储结构的实现](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-001/what-is-linear-list)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int ElemType;

typedef struct DblNode{
    ElemType data;
    struct DblNode *prev,*next;
}  DblNode,*DblList;


/**
 * [init 初始化双向链表L]
 * @param  L [指向链表L指针的指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool init(DblList *L){
    (*L) = (DblList)malloc(sizeof(DblNode));
    if(!*L){
        return false;
    }

    (*L)->prev = NULL;
    (*L)->next = NULL;
    return true;
}

/**
 * [isEmpty 双向链表L是否为空表]
 * @param  L [双向链表L指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool isEmpty(DblList L){
    if(L->prev == NULL && L->next == NULL){
        return true;
    }else{
       return false;
    }
}

/**
 * [insert 在双向链表L的位置i处，插入元素x]
 * @param  L [双向链表L指针]
 * @param  i [位置i]
 * @param  x [元素x]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool insert(DblList L, int i, ElemType x){
    DblList p,s;
    int k=0;

    p = L;

    while(p && k < i-1){
        p = p->next;
        k++;
    }

    if(!p || (i-1 < 0)){
        return false;
    }

    s = (DblList)malloc(sizeof(DblNode));

    if(!s){
        return false;
    }

    s->data = x;

    s->next = p->next;
    s->prev = p;
    p->next = s;

    return true;
}

/**
 * [length 返回双向链表L的长度，即元素的个数。]
 * @param  L [双向链表L指针]
 * @return int [返回线性表L的长度]
 */
int length(DblList L){
    DblList p;
    int k=0;

    if(L){
        p = L->next;
        while(p){
            p = p->next;
            k++;
        }
    }

    return k;
}

/**
 * [get 返回双向链表L中，第i个位置的元素值。]
 * @param  L [双向链表L指针]
 * @param  i [位置i]
 * @param  x [位置i元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool get(DblList L, int i, ElemType *x){
    DblList p;
    int k=0;

    if(!L){
        return false;
    }

    p = L->next;

    while(p && k < i-1){
        p = p->next;
        k++;
    }

    if(!p || (i-1 < 0)){
        return false;
    }

    *x = p->data;
    return true;
}

/**
 * [prior 返回双向链表L中，第i个位置的前驱元素元素值。]
 * @param  L [双向链表L指针]
 * @param  i [位置i]
 * @param  x [位置i前驱元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool prior(DblList L, int i, ElemType *x){
    return get(L, i-1, x);
}

/**
 * [next 返回双向链表L中，第i个位置的后继元素元素值。]
 * @param  L [双向链表L指针]
 * @param  i [位置i]
 * @param  x [位置i后继元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool next(DblList L, int i, ElemType *x){
    return get(L, i+1, x);
}

/**
 * [locate 返回双向链表L中，元素x的首次出现的位置。]
 * @param  L [双向链表L指针]
 * @param  x [元素x]
 * @return int [返回元素x的位置，如果不存在返回-1]
 */
int locate(DblList L, ElemType x){
    int pos = -1;
    int k = 0;
    DblList p;

    if(!L){
        return pos;
    }

    p = L->next;

    while(p){
        k++;
        if(p->data == x){
            pos = k;
            break;
        }
        p = p->next;
    }

    return pos;
}

/**
 * [delete 在双向链表L的位置i处。删除其元素。]
 * @param  L [双向链表L指针]
 * @param  i [位置i]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool delete(DblList L, int i){
    DblList p;
    int k=0;

    if(!L){
        return false;
    }

    p = L->next;

    while(p && k < i-1){
        p = p->next;
        k++;
    }

    if(!p || (i-1 < 0)){
        return false;
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;

    free(p);

    return true;
}

/**
 * [traverse 遍历输出所有元素值]
 * @param L [双向链表L指针]
 */
void traverse(DblList L){
    DblList p;
    int k=0;

    if(!L){
        printf("traverse flag is false \n\n");
    }else{
        p = L->next;

        while(p){
            k++;
            printf("pos is %d, x is %d \n\n", k, p->data);
            p = p->next;
        }
    }
}

/**
 * [clear 将双向链表清空，清除所有元素。]
 * @param L [双向链表L指针]
 */
void clear(DblList L){
    DblList p,t;

    p = L->next;
    while(p){
        t = p->next;
        free(p);
        p = t;
    }
    L->prev = NULL;
    L->next = NULL;
}

/**
 * [destroy 将双向链表销毁，释放内存。]
 * @param L [指向链表L指针的指针]
 */
void destroy(DblList *L){
    DblList p,t;

    p = (*L)->next;
    while(p){
        t = p->next;
        free(p);
        p = t;
    }
    free(*L);
}

/**
 * [isValid 是否可用]
 * @param flag [bool 可用标识]
 * @return char [返回字符串，true返回成功，否则返回失败]
 */
char * isValid(bool flag){
    char *src;
    if(flag){
        src = "success";
    }else{
        src = "false";
    }

    return src;
}

int main(){
    bool flag;
    int pos;
    int len;
    ElemType elem;

    DblList L;

    flag = init(&L);
    printf("operation - init \n init flag is %s \n\n", isValid(flag));

    flag = isEmpty(L);
    printf("operation - isEmpty \n empty flag is %s \n\n", isValid(flag));

    pos = 1;
    elem = 11;
    flag = insert(L,pos,elem);
    printf("operation - insert \n insert flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    pos = 2;
    elem = 12;
    flag = insert(L,pos,elem);
    printf("operation - insert \n insert flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    pos = 3;
    elem = 13;
    flag = insert(L,pos,elem);
    printf("operation - insert \n insert flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    len = length(L);
    printf("operation - length \n length is %d \n\n", len);

    pos = 2;
    elem = 0;
    flag = get(L,pos,&elem);
    printf("operation - get \n get flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    pos = 2;
    elem = 0;
    flag = prior(L,pos,&elem);
    printf("operation - prior \n prior flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    pos = 2;
    elem = 0;
    flag = next(L,pos,&elem);
    printf("operation - next \n next flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    elem = 12;
    pos = locate(L, elem);
    printf("operation - locate \n locate position is %d, x is %d \n\n", pos, elem);

    pos = 2;
    flag = delete(L,pos);
    printf("operation - delete \n delete flag is %s, pos is %d \n\n", isValid(flag), pos);

    printf("operation - traverse \n \n\n");
    traverse(L);

    clear(L);
    printf("operation - clear \n \n\n");

    destroy(&L);
    printf("operation - destroy \n \n\n");

    return 0;
}