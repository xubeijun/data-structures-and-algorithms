/*
[堆栈 - 百度百科](https://baike.baidu.com/item/%E5%A0%86%E6%A0%88/1682032)

堆栈的顺序存储结构通常由一维数组和一个记录栈顶位置的变量组成。

《数据结构-入门指南》 - xubeijun/续杯君
[第3节 堆栈是什么 - 堆栈的顺序存储实现](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-003/what-is-stack)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 10

typedef int ElemType;

typedef struct SqNode{
    ElemType *data;
    int top;
    int MaxSize;
}  SqNode, *SqStack;

// 初始化空堆栈
bool init(SqStack *S);

// 堆栈是否为空
bool isEmpty(SqStack S);

// 堆栈是否已满
bool isFull(SqStack S);

// 清空堆栈
void clear(SqStack *S);

// 销毁堆栈
void destroy(SqStack *S);

// 遍历输出堆栈所有元素值
void traverse(SqStack S);

// 返回堆栈中栈顶的元素值
bool get(SqStack S, ElemType *x);

// 入栈新元素为新栈顶
bool push(SqStack *S, ElemType x);

// 对栈顶元素进行出栈
bool pop(SqStack *S, ElemType *x);

// 返回堆栈的长度
int length(SqStack S);

/**
 * [init 初始化空堆栈]
 * @param  S [堆栈二级指针]
 * @return bool [是否完成]
 */
bool init(SqStack *S){
    *S = (SqStack)malloc(sizeof(SqNode));
    if(!*S){
        return false;
    }

    (*S)->data = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));
    if(!(*S)->data){
        return false;
    }

    (*S)->top     = -1;
    (*S)->MaxSize = MAXSIZE;
    return true;
}

/**
 * [isEmpty 堆栈是否为空]
 * @param  S [堆栈指针]
 * @return bool [是否为空]
 */
bool isEmpty(SqStack S){
    if(S->top == -1){
        return true;
    }else{
        return false;
    }
}

/**
 * [isFull 堆栈是否已满]
 * @param  S [堆栈指针]
 * @return bool [是否已满]
 */
bool isFull(SqStack S){
    if(S->top == S->MaxSize-1){
        return true;
    }else{
        return false;
    }
}

/**
 * [clear 清空堆栈]
 * @param S [堆栈指针]
 */
void clear(SqStack *S){
    (*S)->data = NULL;
    (*S)->top  = -1;
}

/**
 * [destroy 销毁堆栈]
 * @param S [堆栈指针]
 */
void destroy(SqStack *S){
    free((*S)->data);
    (*S)->data = NULL;

    (*S)->top  = -1;

    free((*S));
    *S = NULL;
}

/**
 * [traverse 遍历输出堆栈所有元素值]
 * @param S [堆栈指针]
 */
void traverse(SqStack S){
    printf("operation - traverse start \n\n");

    if(!isEmpty(S)){
        for (int i = S->top; i >= 0; --i){
            printf("pos is %d, x is %d \n\n", i, S->data[i]);
        }
    }
}

/**
 * [get 返回堆栈中栈顶的元素]
 * @param  S [堆栈指针]
 * @param  x [栈顶元素]
 * @return bool [是否成功]
 */
bool get(SqStack S, ElemType *x){
    if(isEmpty(S)){
        return false;
    }else{
        *x = S->data[S->top];
        return true;
    }
}

/**
 * [push 入栈新元素为新栈顶]
 * @param  S [堆栈二级指针]
 * @param  x [入栈元素]
 * @return bool [是否成功]
 */
bool push(SqStack *S, ElemType x){
    if(isFull(*S)){
        return false;
    }

    (*S)->data[++(*S)->top] = x;
    return true;
}

/**
 * [pop 对栈顶元素进行出栈]
 * @param  S [堆栈二级指针]
 * @param  x [对栈元素]
 * @return bool [是否成功]
 */
bool pop(SqStack *S, ElemType *x){
    if(isEmpty(*S)){
        return false;
    }

    *x = (*S)->data[(*S)->top--];
    return true;
}

/**
 * [length 返回堆栈的长度]
 * @param  S [堆栈指针]
 * @return int [返回堆栈的长度]
 */
int length(SqStack S){
    return (S->top + 1);
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

    SqStack S;

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