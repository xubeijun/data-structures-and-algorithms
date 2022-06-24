/*

02-线性结构3 Reversing Linked List

Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L. For example, given L being 1→2→3→4→5→6, if K=3, then you must output 3→2→1→6→5→4; if K=4, you must output 4→3→2→1→5→6.

Input Specification:
Each input file contains one test case. For each case, the first line contains the address of the first node, a positive N (≤10^5) which is the total number of nodes, and a positive K (≤N) which is the length of the sublist to be reversed. The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.

Then N lines follow, each describes a node in the format:

Address Data Next
where Address is the position of the node, Data is an integer, and Next is the position of the next node.

Output Specification:

For each case, output the resulting ordered linked list. Each node occupies a line, and is printed in the same format as in the input.

Sample Input:

00100 6 4
00000 4 99999
00100 1 12309
68237 6 -1
33218 3 00000
99999 5 68237
12309 2 33218

Sample Output:

00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 -1

《数据结构-入门指南》 - xubeijun/续杯君
[第6节 应用实例：反转链表](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-006/reversing-linked-list)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100000

typedef int ElemType;

// static linked list
typedef struct SLNode{
    ElemType data;
    ElemType next;
} SLNode;

// singly linked list
typedef struct SNode{
    ElemType curPtr;
    ElemType data;
    ElemType nextPtr;
    struct SNode *next;
}  SNode, *SList;

// stack
typedef struct Node{
    SList top;
    ElemType count;
    ElemType maxSize;
    ElemType subNums;
    ElemType head;
}Node, *Stack;

// queue
typedef struct LQueue{
    SList front;
    SList rear;
    int count;
} LQueue, *Queue;

// 读取元信息
Stack readMeta();

// 读取输入
Stack readInput(Stack S, SLNode L[]);

// 反转链表
Queue reversing(Stack S, SLNode L[]);

// 打印链表
void printList(Stack S, SLNode L[]);

// 入栈
void push(Stack *S, SList P);

// 出栈
SList pop(Stack *S);

// 初始化队列
Queue initQueue();

// 入队列
void insertQueue(Queue *Q, SList P);

// 遍历队列
void printQueue(Queue Q);

void push(Stack *S, SList P){
    P->next   = (*S)->top;
    (*S)->top = P;

    (*S)->count++;
}

SList pop(Stack *S){
    SList P;

    if((*S)->count == 0){
        printf("pop is fail \n");
        exit(-1);
    }

    P         = (*S)->top;
    (*S)->top = P->next;
    P->next   = NULL;

    (*S)->count--;

    return P;
}

Queue initQueue(){
    Queue Q;
    Q = (Queue)malloc(sizeof(LQueue));
    if(!Q){
        printf("malloc Queue is fail \n");
        exit(-1);
    }

    Q->front = Q->rear = (SList)malloc(sizeof(SNode));
    if(!Q->front){
        printf("malloc SList is fail \n");
        exit(-1);
    }

    Q->front->next = NULL;
    Q->count       = 0;

    return Q;
}

void insertQueue(Queue *Q, SList P){
    (*Q)->rear->nextPtr = P->curPtr;

    (*Q)->rear->next = P;
    (*Q)->rear       = P;

    (*Q)->count++;
}

void printQueue(Queue Q){
    SList P = Q->front->next;

    while(P){
        if(P->nextPtr != -1){
            printf("%.5d %d %.5d\n", P->curPtr, P->data, P->nextPtr);
        }else{
            printf("%.5d %d %d\n", P->curPtr, P->data, P->nextPtr);
        }
        P = P->next;
    }
}

Stack readMeta(){
    int x, Head, N, K;
    Stack S;

    S = (Stack)malloc(sizeof(struct Node));
    if(!S){
        printf("malloc Stack is fail \n");
        exit(-1);
    }

    x = scanf("%d %d %d", &Head, &N, &K);
    if(x != 3){
        printf("input is fail \n");
        exit(-1);
    }

    S->top     = NULL;
    S->count   = 0;
    S->maxSize = N;
    S->subNums = K;
    S->head    = Head;

    return S;
}

Stack readInput(Stack S, SLNode L[]){
    int x, curAddress, data, nextAddress, rear, validNums=0;

    for(int i=0; i < S->maxSize; i++){
        x = scanf("%d %d %d", &curAddress, &data, &nextAddress);
        if(x != 3){
            printf("input is fail \n");
            exit(-1);
        }

        L[curAddress].data = data;
        L[curAddress].next = nextAddress;
    }

    rear = S->head;

    for (int i=0; i < S->maxSize; i++){
        validNums++;
        rear = L[rear].next;

        if(rear == -1){
            break;
        }
    }

    S->maxSize = validNums;

    return S;
}

Queue reversing(Stack S, SLNode L[]){
    int revLoop = S->maxSize / S->subNums; // 反转子链表的次数
    int loopIndex; // 当前反转操作次数的下标
    int remainCount = S->maxSize - (revLoop * S->subNums); // 剩余不需要反转的元素数量

    int current; // 当前操作的节点地址

    SList P, temp; // 链表节点

    current = S->head;

    Queue Q;

    Q = initQueue();

    // 依次反转子链
    for(loopIndex = 0; loopIndex < revLoop; ++loopIndex){
        // 入栈
        for (int i = 0; i < S->subNums; ++i){
            P          = (SList)malloc(sizeof(struct SNode));
            P->curPtr  = current;
            P->data    = L[current].data;
            // P->nextPtr = L[current].next;
            push(&S, P);

            current = L[current].next;
        }

        // 出栈
        while(S->count > 0){
            temp = pop(&S);

            // 当剩余节点为零时，最后一个元素的nextPtr设置为-1
            if(remainCount == 0 && loopIndex == (revLoop-1)){
                temp->nextPtr = -1;
            }
            
            // 节点入队列
            insertQueue(&Q, temp);
        }
    }

    // 剩余节点入队列
    if(remainCount > 0){
        for (int i = 0; i < remainCount; ++i){
            P          = (SList)malloc(sizeof(struct SNode));
            P->curPtr  = current;
            P->data    = L[current].data;
            P->nextPtr = L[current].next;

            insertQueue(&Q, P);

            current = L[current].next;
        }
    }

    return Q;
}


void printList(Stack S, SLNode L[]){
    int rear;
    rear = S->head;

    while(L[rear].next != -1){
        printf("%.5d %d %.5d\n", rear, L[rear].data, L[rear].next);
        rear = L[rear].next;
    }

    // last node
    printf("%.5d %d %d\n", rear, L[rear].data, L[rear].next);
}

int main(){
    Stack S;
    Queue Q;
    SLNode list[MAXSIZE];

    S = readMeta();

    S = readInput(S, list);

    // printf("operation - readInput Head: %.5d N: %d K: %d \n", S->head, S->maxSize, S->subNums);
    
    if(S->subNums > 1){
        Q = reversing(S, list);
        printQueue(Q);
    }else{
        printList(S, list);
    }


    return 0;
}
