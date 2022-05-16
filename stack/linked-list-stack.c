/*
[堆栈 - 百度百科](https://baike.baidu.com/item/%E5%A0%86%E6%A0%88/1682032)

堆栈的链式存储结构实际上就是一个单链表，叫做栈链，插入和删除只能在栈顶进行操作。

《数据结构-入门指南》 - xubeijun/续杯君
[第3节 堆栈是什么 - 堆栈的链式存储实现](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-003/what-is-stack)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int ElemType;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}  LNode, *LinkList;

typedef struct LinkStack{
    LinkList top;
    int count;
} LinkStack, *LStack;

// 初始化空堆栈
bool init(LStack *S);

// 堆栈是否为空
bool isEmpty(LStack S);

// 清空堆栈
void clear(LStack *S);

// 销毁堆栈
void destroy(LStack *S);

// 遍历输出堆栈所有元素值
void traverse(LStack S);

// 返回堆栈中栈顶的元素值
bool get(LStack S, ElemType *x);

// 入栈新元素为新栈顶
bool push(LStack *S, ElemType x);

// 对栈顶元素进行出栈
bool pop(LStack *S, ElemType *x);

// 返回堆栈的长度
int length(LStack S);

/**
 * [init 初始化空堆栈]
 * @param  S [堆栈二级指针]
 * @return bool [是否完成]
 */
bool init(LStack *S){
    *S = (LStack)malloc(sizeof(LinkStack));
    
    if(!*S){
        return false;
    }

    (*S)->top   = NULL;
    (*S)->count = 0;

    return true;
}

/**
 * [isEmpty 堆栈是否为空]
 * @param  S [堆栈指针]
 * @return bool [是否为空]
 */
bool isEmpty(LStack S){
    if(S->count == 0){
        return true;
    }else{
        return false;
    }
}

/**
 * [clear 清空堆栈]
 * @param S [堆栈指针]
 */
void clear(LStack *S){
    LinkList M = (*S)->top;
    LinkList N;

    while(M){
        N = M->next;
        free(M);
        M = NULL;
        M = N;
    }

    (*S)->top   = NULL;
    (*S)->count = 0;
}

/**
 * [destroy 销毁堆栈]
 * @param S [堆栈指针]
 */
void destroy(LStack *S){
    if(*S){
        clear(S);
        free(*S);
        *S = NULL;
    }
}

/**
 * [traverse 遍历输出堆栈所有元素值]
 * @param S [堆栈指针]
 */
void traverse(LStack S){
    LinkList M = S->top;
    int i      = S->count;

    printf("operation - traverse start \n\n");

    while(M){
        printf("pos is %d, x is %d \n\n", i--, M->data);
        M = M->next;
    }
}

/**
 * [get 返回堆栈中栈顶的元素]
 * @param  S [堆栈指针]
 * @param  x [栈顶元素]
 * @return bool [是否成功]
 */
bool get(LStack S, ElemType *x){
    if(isEmpty(S)){
        return false;
    }else{
        *x = S->top->data;
        return true;
    }
}

/**
 * [push 入栈新元素为新栈顶]
 * @param  S [堆栈二级指针]
 * @param  x [入栈元素]
 * @return bool [是否成功]
 */
bool push(LStack *S, ElemType x){
    LinkList M = (LinkList)malloc(sizeof(LNode));

    if(!M){
        return false;
    }

    M->data = x;
    M->next = (*S)->top;
    (*S)->top = M;
    (*S)->count++;

    return true;
}

/**
 * [pop 对栈顶元素进行出栈]
 * @param  S [堆栈二级指针]
 * @param  x [对栈元素]
 * @return bool [是否成功]
 */
bool pop(LStack *S, ElemType *x){
    LinkList M;

    if(isEmpty(*S)){
        return false;
    }

    M         = (*S)->top;
    *x        = M->data;
    (*S)->top = M->next;

    free(M);
    M = NULL;

    (*S)->count--;

    return true;
}

/**
 * [length 返回堆栈的长度]
 * @param  S [堆栈指针]
 * @return int [返回堆栈的长度]
 */
int length(LStack S){
    return S->count;
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
    bool f;
    int len;
    ElemType x,m,n;

    LStack S;

    f = init(&S);
    printf("operation - init \n it is %s \n\n", isValid(f));

    f = isEmpty(S);
    printf("operation - isEmpty \n it is %s \n\n", isValid(f));

    x = 1;
    f = push(&S, x);
    printf("operation - push \n it is %s x is %d \n\n", isValid(f), x);

    x = 2;
    f = push(&S, x);
    printf("operation - push \n it is %s x is %d \n\n", isValid(f), x);

    len = length(S);
    printf("operation - length \n its length is %d \n\n", len);

    f = get(S, &m);
    printf("operation - get \n it is %s x is %d \n\n", isValid(f), m);

    f = pop(&S, &n);
    printf("operation - pop \n it is %s x is %d \n\n", isValid(f), n);

    traverse(S);
    printf("operation - traverse end \n\n");

    clear(&S);
    printf("operation - clear \n\n");

    destroy(&S);
    printf("operation - destroy \n\n");

    return 0;
}