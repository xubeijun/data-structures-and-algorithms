/*
[循环队列 - 百度百科](https://baike.baidu.com/item/%E5%BE%AA%E7%8E%AF%E9%98%9F%E5%88%97/3685773)

队列（queue）又称为伫列，具有一定操作约束的线性表，只允许在前端（队头，front）进行删除（delete），而在后端（队尾：rear）进行插入（insert）的运算。
数据项满足先进先出（FIFO, First In First Out）的原理运作。

队列的顺序存储结构通常由一维数组和一个记录队头（front）位置的变量以及一个记录队尾（rear）位置的变量组成。

循环队列（Circular Queue）是把顺序队列首尾相连。

当队列为空时，有front == rear。
当队列为满时，有front == (rear + 1) % MAXSIZE。
计算长度公式为：(rear - front + MAXSIZE) % MAXSIZE。

《数据结构-入门指南》 - xubeijun/续杯君
[第4节 队列是什么 - 循环队列的顺序存储结构](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-004/what-is-queue)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 6

typedef int ElemType;

typedef struct QNode{
    ElemType *data;
    int front;
    int rear;
    int maxSize;
}  QNode, *Queue;

// 初始化空队列
bool init(Queue *Q);

// 队列是否为空
bool isEmpty(Queue Q);

// 队列是否已满
bool isFull(Queue Q);

// 清空队列
void clear(Queue *Q);

// 销毁队列
void destroy(Queue *Q);

// 遍历输出队列所有元素值
void traverse(Queue Q);

// 在队列的队头，返回元素
bool get(Queue Q, ElemType *x);

// 在队列的队尾，插入元素
bool insert(Queue *Q, ElemType x);

// 在队列的队头，删除元素
bool delete(Queue *Q, ElemType *x);

// 返回队列的长度
int length(Queue Q);

/**
 * [init 初始化空队列]
 * @param  Q [队列二级指针]
 * @return bool [是否完成]
 */
bool init(Queue *Q){
    *Q = (Queue)malloc(sizeof(QNode));
    if(!*Q){
        return false;
    }

    (*Q)->data = (ElemType *)malloc(MAXSIZE*sizeof(ElemType));
    if(!(*Q)->data){
        return false;
    }

    (*Q)->front   = 0;
    (*Q)->rear    = 0;
    (*Q)->maxSize = MAXSIZE;

    return true;
}

/**
 * [isEmpty 堆栈是否为空]
 * @param  Q [队列指针]
 * @return bool [是否为空]
 */
bool isEmpty(Queue Q){
    if(Q->front == Q->rear){
        return true;
    }else{
        return false;
    }
}

/**
 * [isFull 队列是否已满]
 * @param  Q [队列指针]
 * @return bool [是否已满]
 */
bool isFull(Queue Q){
    if(Q->front == (Q->rear + 1) % Q->maxSize){
        return true;
    }else{
        return false;
    }
}

/**
 * [clear 清空队列]
 * @param Q [队列二级指针]
 */
void clear(Queue *Q){
    (*Q)->front = (*Q)->rear = 0;
}

/**
 * [destroy 销毁队列]
 * @param Q [队列二级指针]
 */
void destroy(Queue *Q){
    if(*Q){
        clear(Q);

        free((*Q)->data);
        (*Q)->data = NULL;

        free((*Q));
        *Q = NULL;
    }
}

/**
 * [traverse 遍历输出堆栈所有元素值]
 * @param Q [队列指针]
 */
void traverse(Queue Q){
    printf("operation - traverse start \n\n");

    if(!isEmpty(Q)){
        for (int pos = Q->front; pos != Q->rear; pos = (pos+1)%Q->maxSize){
            printf("pos is %d, x is %d \n\n", pos, Q->data[pos]);
        }
    }
}

/**
 * [get 在队列的队头，返回元素]
 * @param  Q [队列指针]
 * @param  x [元素]
 * @return bool [是否成功]
 */
bool get(Queue Q, ElemType *x){
    if(isEmpty(Q)){
        return false;
    }else{
        *x = Q->data[Q->front];
        return true;
    }
}

/**
 * [insert 在队列的队尾，插入元素]
 * @param  Q [队列二级指针]
 * @param  x [元素]
 * @return bool [是否成功]
 */
bool insert(Queue *Q, ElemType x){
    if(isFull(*Q)){
        return false;
    }

    (*Q)->data[(*Q)->rear] = x;
    (*Q)->rear = ((*Q)->rear + 1) % (*Q)->maxSize;
    return true;
}

/**
 * [delete 在队列的队头，删除元素]
 * @param  Q [队列二级指针]
 * @param  x [元素]
 * @return bool [是否成功]
 */
bool delete(Queue *Q, ElemType *x){
    if(isEmpty(*Q)){
        return false;
    }

    *x = (*Q)->data[(*Q)->front];
    (*Q)->front = ((*Q)->front + 1) % (*Q)->maxSize;
    return true;
}

/**
 * [length 返回队列的长度]
 * @param  Q [队列指针]
 * @return int [返回堆栈的长度]
 */
int length(Queue Q){
    return ((Q->rear - Q->front + Q->maxSize) % Q->maxSize);
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

    Queue Q;

    f = init(&Q);
    printf("operation - init \n it is %s \n\n", isValid(f));

    f = isEmpty(Q);
    printf("operation - isEmpty \n it is %s \n\n", isValid(f));

    // insert full element, n = MAXSIZE-1
    for (int i = 0; i < MAXSIZE-1; ++i){
        x = i;
        f = insert(&Q, x);
        printf("operation - insert \n it is %s x is %d \n\n", isValid(f), x);
    }

    traverse(Q);
    printf("operation - traverse after insert is end \n\n");

    len = length(Q);
    printf("operation - length \n its length is %d \n\n", len);

    f = get(Q, &m);
    printf("operation - get \n it is %s x is %d \n\n", isValid(f), m);

    // delete element, n = MAXSIZE-2
    for (int i = 0; i < MAXSIZE-2; ++i){
        f = delete(&Q, &n);
        printf("operation - delete \n it is %s x is %d \n\n", isValid(f), n);
    }

    traverse(Q);
    printf("operation - traverse after delete is end \n\n");

    // insert element, n = MAXSIZE-3
    for (int i = 0; i < MAXSIZE-3; ++i){
        x = i;
        f = insert(&Q, x);
        printf("operation - insert \n it is %s x is %d \n\n", isValid(f), x);
    }

    traverse(Q);
    printf("operation - traverse after insert is end \n\n");

    clear(&Q);
    printf("operation - clear \n\n");

    destroy(&Q);
    printf("operation - destroy \n\n");

    return 0;
}