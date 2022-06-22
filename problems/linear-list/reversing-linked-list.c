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

typedef struct LNode{
    int data;
    int next;
} LNode;


// 读取输入
void readInput(int *Head, int *N, int *K, LNode L[]);

// 反转链表
int reversing(LNode L[], int Head, int N, int K);

// 打印链表
void printList(LNode L[], int Head);


void readInput(int *Head, int *N, int *K, LNode L[]){
    int x, addrFront, data, addrRear, rear, validNum;

    x = scanf("%d %d %d", Head, N, K);
    if(x != 3){
        printf("input is fail \n");
        exit(-1);
    }

    for(int i=0; i < *N; i++){
        x = scanf("%d %d %d", &addrFront, &data, &addrRear);
        if(x != 3){
            printf("input is fail \n");
            exit(-1);
        }

        L[addrFront].data = data;
        L[addrFront].next = addrRear;
    }

    rear = *Head;

    for (validNum = 1; validNum <= *N; ++validNum){
        rear = L[rear].next;
        if(rear == -1){
            break;
        }
    }

    *N = validNum;
}

// 1 2 3 4 5 6 7 8 data
// 0 1 2 3 4 5 6 7 index
// 0 1 2
//       3 4 5
//             6 7
int reversing(LNode L[], int Head, int N, int K){
    int rear; //反转子链操作时的头结点

    int revLoop = N / K; //反转子链表的次数
    int loopIndex; //当前反转操作次数的下标

    int revHead;  // 反转子链的头结点, eg. 2,5
    int revLast;  // 反转子链的最后一个结点, eg. 0, 3
    
    int prev; // 反转操作时的前节点 - 单链表无法找到前节点，只能设置中间变量记录
    int curNext; // 反转操作时的下一个节点

    rear    = Head;
    prev    = Head;
    curNext = L[rear].next; // 避免编译时warning未定义初始值

    // printf("operation - reversing revLoop: %d \n", revLoop);

    // 依次反转子链
    for(loopIndex = 0; loopIndex < revLoop; ++loopIndex){
        // 反转当前段的子链
        for (int i = 0; i < (K-1); ++i){
            // printf("for-loop-1 i: %d loopIndex: %d rear: %.5d curNext: %.5d prev: %.5d \n", i, loopIndex, rear, curNext, prev);

            curNext         = L[rear].next;
            L[rear].next    = L[curNext].next;
            L[curNext].next = prev;
            prev            = curNext;

            // printf("for-loop-2 i: %d loopIndex: %d rear: %.5d curNext: %.5d prev: %.5d \n", i, loopIndex, rear, curNext, prev);
        }

        // 反转子链的头结点
        revHead = curNext;

        // 上段子链的最后一个节点连接当前子链的头结点
        if(loopIndex > 0){
            L[revLast].next = revHead;
        }

        // 第一个反转子链的头结点为整个反转链表的头结点
        if(loopIndex == 0){
            Head = revHead;
        }

        // 反转子链的最后一个结点
        revLast = rear;

        // 待反转子链操作时的开始节点
        rear = L[rear].next;
        
        // 待反转子链操作时的前节点
        prev = rear;
    }

    return Head;
}


void printList(LNode L[], int Head){
    int rear;
    rear = Head;

    while(L[rear].next != -1){
        printf("%.5d %d %.5d\n", rear, L[rear].data, L[rear].next);
        rear = L[rear].next;
    }

    // last node
    printf("%.5d %d %d\n", rear, L[rear].data, L[rear].next);
}

int main(){
    int Head, N, K;
    LNode list[MAXSIZE];

    readInput(&Head, &N, &K, list);

    // printf("operation - readInput Head: %.5d N: %d K: %d \n", Head, N, K);

    if(K > 1){
        Head = reversing(list, Head, N, K);
    }

    // printf("operation - reversing Head: %.5d \n", Head);
    printList(list, Head);


    return 0;
}
