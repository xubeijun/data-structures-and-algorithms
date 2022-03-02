/*
[线性表-顺序表](https://baike.baidu.com/item/%E7%BA%BF%E6%80%A7%E8%A1%A8)
[顺序表](https://zh.wikipedia.org/wiki/%E9%A1%BA%E5%BA%8F%E8%A1%A8)

线性表的顺序存储结构是指用一段地址连续的存储单元依次存储线性表的数据元素。

《数据结构-入门指南》 - xubeijun/续杯君
[第1节 线性表是什么 - 线性表的顺序存储结构](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-001/what-is-linear-list)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 3

typedef int ElemType;

typedef struct {
    ElemType *data;
    int length;
} SqList;


/**
 * [init 初始化线性空表L]
 * @param  L [线性表L指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool init(SqList *L){
    L->data = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));
    if(!L->data){
        return false;
    }
    L->length = 0;
    return true;
}

/**
 * [isEmpty 线性表L是否为空表]
 * @param  L [线性表L指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool isEmpty(SqList *L){
    if(L->length == 0){
        return true;
    }else{
        return false;
    }
}

/**
 * [insert 在线性表L的位置i处，插入元素x]
 * @param  L [线性表L指针]
 * @param  i [位置i]
 * @param  x [元素x]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool insert(SqList *L, int i, ElemType x){
    if((i < 1) || (i > L->length+1) || (L->length == MAXSIZE)){
        return false;
    }

    for (int j = L->length-1; j >= i-1; j--){
        L->data[j+1] = L->data[j];
    }

    L->data[i-1] = x;
    L->length++;
    return true;
}

/**
 * [length 返回线性表L的长度，即元素的个数。]
 * @param  L [线性表L指针]
 * @return int [返回线性表L的长度]
 */
int length(SqList *L){
    return L->length;
}

/**
 * [get 返回线性表L中，第i个位置的元素值。]
 * @param  L [线性表L指针]
 * @param  i [位置i]
 * @param  x [位置i元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool get(SqList *L, int i, ElemType *x){
    if(i < 1 || i > L->length){
        return false;
    }

    *x = L->data[i-1];
    return true;
}

/**
 * [prior 返回线性表L中，第i个位置的前驱元素元素值。]
 * @param  L [线性表L指针]
 * @param  i [位置i]
 * @param  x [位置i前驱元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool prior(SqList *L, int i, ElemType *x){
    return get(L, i-1, x);
}

/**
 * [next 返回线性表L中，第i个位置的后继元素元素值。]
 * @param  L [线性表L指针]
 * @param  i [位置i]
 * @param  x [位置i后继元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool next(SqList *L, int i, ElemType *x){
    return get(L, i+1, x);
}

/**
 * [locate 返回线性表L中，元素x的首次出现的位置。]
 * @param  L [线性表L指针]
 * @param  x [元素x]
 * @return int [返回元素x的位置，如果不存在返回-1]
 */
int locate(SqList *L, ElemType x){
    int pos = -1;
    for (int i = 0; i < L->length; ++i){
        if(L->data[i] == x){
            pos = i+1;
            break;
        }
    }
    return pos;
}

/**
 * [traverse 遍历输出所有元素值]
 * @param L [线性表L指针]
 */
void traverse(SqList *L){
    for (int i = 0; i < L->length; ++i){
        printf("pos is %d, x is %d \n\n", i, L->data[i]);
    }
}

/**
 * [delete 在线性表L的位置i处。删除其元素。]
 * @param  L [线性表L指针]
 * @param  i [位置i]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool delete(SqList *L, int i){
    if(i < 1 || i > L->length){
        return false;
    }

    for (int j = i; j < L->length; j++){
        L->data[j-1] = L->data[j];
    }

    L->length--;

    return true;
}

/**
 * [clear 将线性表清空，清除所有元素。]
 * @param L [线性表L指针]
 */
void clear(SqList *L){
    if(L->length != 0){
         memset(L, 0, MAXSIZE*sizeof(ElemType));
    }
    L->length = 0;
}

/**
 * [destroy 将线性表销毁，释放内存。]
 * @param L [线性表L指针]
 */
void destroy(SqList *L){
    free(L->data);
    L->data = NULL;
    L->length = 0;
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

    SqList L;

    flag = init(&L);
    printf("operation - init \n init flag is %s \n\n", isValid(flag));

    flag = isEmpty(&L);
    printf("operation - isEmpty \n empty flag is %s \n\n", isValid(flag));

    pos = 1;
    elem = 11;
    flag = insert(&L,pos,elem);
    printf("operation - insert \n insert flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    pos = 2;
    elem = 12;
    flag = insert(&L,pos,elem);
    printf("operation - insert \n insert flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    pos = 3;
    elem = 13;
    flag = insert(&L,pos,elem);
    printf("operation - insert \n insert flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    len = length(&L);
    printf("operation - length \n length is %d \n\n", len);

    pos = 2;
    elem = 0;
    flag = get(&L,pos,&elem);
    printf("operation - get \n get flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    pos = 2;
    elem = 0;
    flag = prior(&L,pos,&elem);
    printf("operation - prior \n prior flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    pos = 2;
    elem = 0;
    flag = next(&L,pos,&elem);
    printf("operation - next \n next flag is %s, pos is %d, x is %d \n\n", isValid(flag), pos, elem);

    elem = 12;
    pos = locate(&L, elem);
    printf("operation - locate \n locate position is %d, x is %d \n\n", pos, elem);

    pos = 2;
    flag = delete(&L,pos);
    printf("operation - delete \n delete flag is %d, pos is %d \n\n", flag, pos);

    printf("operation - traverse \n \n\n");
    traverse(&L);

    clear(&L);
    printf("operation - clear \n \n\n");

    destroy(&L);
    printf("operation - destroy \n \n\n");

    return 0;
}