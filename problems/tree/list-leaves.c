/*
03-树2 List Leaves

Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer N (≤10) which is the total number of nodes in the tree -- and hence the nodes are numbered from 0 to N−1. Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node. If the child does not exist, a "-" will be put at the position. Any pair of children are separated by a space.

Output Specification:

For each test case, print in one line all the leaves' indices in the order of top down, and left to right. There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

Sample Input:

8
1 -
- -
0 -
2 7
- -
- -
5 -
4 6

Sample Output:

4 1 5

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MaxSize 10
#define ElementType char
#define DataType int
#define Tree int
#define Null -1

struct TreeNode{
    ElementType data;
    Tree left;
    Tree right;
} T1[MaxSize];

typedef struct QNode{
    DataType data;
    struct QNode *next;
}  QNode, *QNodePtr;

typedef struct{
    QNodePtr front;
    QNodePtr rear;
} Queue;

Queue createQueue(){
    Queue Q;

    // Q = (Queue)malloc(sizeof(Queue));

    Q.front = Q.rear = (QNodePtr)malloc(sizeof(QNode));
    Q.front->next = NULL;

    return Q;
}

bool isEmpty(Queue Q){
    if(Q.front == Q.rear){
        return true;
    }else{
        return false;
    }
}

bool insert(Queue *Q, DataType x){
    QNodePtr P;

    P       = (QNodePtr)malloc(sizeof(QNode));
    P->data = x;
    P->next = NULL;

    (*Q).rear->next = P;
    (*Q).rear       = P;

    return true;
}

bool delete(Queue *Q, DataType *x){
    QNodePtr P;

    if(isEmpty(*Q)){
        return false;
    }

    P                = (*Q).front->next;
    
    *x               = P->data;
    (*Q).front->next = P->next;
    
    if((*Q).rear == P){
        (*Q).rear = (*Q).front;
    }

    free(P);
    P = NULL;

    return true;
}

Tree buildTree(struct TreeNode T[]){
    int x, N, root = Null, checkRoot[MaxSize] = {0};
    char cLeft, cRight;

    x = scanf("%d", &N);
    if(x != 1){
        printf("input is fail \n");
        exit(-1);
    }

    for(int i = 0; i < N; i++){
        T[i].data = i;
        x = scanf("\n%c %c",&cLeft, &cRight);
        if(x != 2){
            printf("input is fail \n");
            exit(-1);
        }

        if(cLeft != '-'){
            T[i].left = cLeft-'0';
            checkRoot[T[i].left] = 1;
        }else{
            T[i].left = Null;
        }

        if(cRight != '-'){
            T[i].right = cRight-'0';
            checkRoot[T[i].right] = 1;
        }else{
            T[i].right = Null;
        }
    }

    for (int i = 0; i < N; ++i){
        if(checkRoot[i] == 0){
            root = i;
            break;
        }
    }

    return root;
}

void levelOrderLeaves(Tree R1){
    Queue Q;
    DataType i;
    char *preStr;
    bool isFirst = true;

    Q = createQueue();

    insert(&Q, R1);

    while(!isEmpty(Q)){
        delete(&Q, &i);

        if(T1[i].left == Null && T1[i].right == Null){
            preStr = isFirst?"":" ";
            printf("%s%d", preStr,T1[i].data);
            isFirst = false;
        }

        if(T1[i].left != Null){
            insert(&Q, T1[i].left);
        }

        if(T1[i].right != Null){
            insert(&Q, T1[i].right);
        }
    }
}

int main(){
    Tree R1;

    // printf("input - 请输入T的数据样本 \n");
    R1 = buildTree(T1);

    // printf("result - 叶结点结果 \n");
    levelOrderLeaves(R1);

    return 0;
}