/*
树的后序遍历
03-树3 Tree Traversals Again

An inorder binary tree traversal can be implemented in a non-recursive way with a stack. For example, suppose that when a 6-node binary tree (with the keys numbered from 1 to 6) is traversed, the stack operations are: push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop(). Then a unique binary tree (shown in Figure 1) can be generated from this sequence of operations. Your task is to give the postorder traversal sequence of this tree.

Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer N (≤30) which is the total number of nodes in a tree (and hence the nodes are numbered from 1 to N). Then 2N lines follow, each describes a stack operation in the format: "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.

Output Specification:

For each test case, print the postorder traversal sequence of the corresponding tree in one line. A solution is guaranteed to exist. All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.

Sample Input:

6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop

Sample Output:

3 4 2 6 5 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MaxSize 30
#define ElementType int
#define Tree int
#define Null -1

// is first print
bool isFirst = true;

struct TreeNode{
    ElementType data;
    Tree left;
    Tree right;
} T1[MaxSize];

typedef struct SqNode{
    ElementType data[MaxSize];
    int top;
}  SqNode, *Stack;

bool init(Stack *S){
    *S = (Stack)malloc(sizeof(SqNode));
    if(!*S){
        return false;
    }

    (*S)->top = -1;
    return true;
}

bool isEmpty(Stack S){
    if(S->top == -1){
        return true;
    }else{
        return false;
    }
}

bool isFull(Stack S){
    if(S->top == MaxSize-1){
        return true;
    }else{
        return false;
    }
}

bool top(Stack S, ElementType *x){
    if(isEmpty(S)){
        return false;
    }else{
        *x = S->data[S->top];
        return true;
    }
}

bool push(Stack *S, ElementType x){
    if(isFull(*S)){
        return false;
    }

    (*S)->data[++(*S)->top] = x;
    return true;
}

bool pop(Stack *S, ElementType *x){
    if(isEmpty(*S)){
        return false;
    }

    *x = (*S)->data[(*S)->top--];
    return true;
}

int getInput(int preOrder[], int inOrder[]){
    int x, N, popNum = 0, inNum = 0,subPre = 0, subIn = 0;
    char optStr[5];
    Stack S;
    bool optFlag = false;

    x = scanf("%d", &N);
    if(x != 1){
        printf("input is fail \n");
        exit(-1);
    }

    optFlag = init(&S);
    if(!optFlag){
        printf("init stack is fail \n");
        exit(-1);
    }

    for(int i = 0; i < 2*N; i++){
        x = scanf("\n%s", optStr);

        if(x != 1){
            printf("input is fail\n");
            exit(-1);
        }

        if(strcmp(optStr, "Push") == 0){
            x = scanf("\n%d", &inNum);
            if(x != 1){
                printf("input is fail\n");
                exit(-1);
            }

            preOrder[subPre++] = inNum;
            push(&S, inNum);
        }

        if(strcmp(optStr, "Pop") == 0){
            pop(&S, &popNum);

            inOrder[subIn++] = popNum;
        }
    }

    return N;
}

// posInR means that the position of root in InOrder.
Tree buildTree(struct TreeNode T[], int N, int *preOrder, int *inOrder){
    Tree R1; //root
    int posInR, subNumL, subNumR;

    if(N == 0){
        return Null; // return -1
    }

    R1 = preOrder[0];

    for (posInR = 0; posInR < N; ++posInR){
        if(preOrder[0] == inOrder[posInR]){
            break;
        }
    }

    subNumL = posInR;
    subNumR = N - (posInR + 1);

    T1[R1].data  = R1;
    T1[R1].left  = buildTree(T1, subNumL, preOrder+1, inOrder);
    T1[R1].right = buildTree(T1, subNumR, preOrder+(subNumL+1), inOrder+(subNumL+1));

    return R1;
}

void postOrder(Tree R1){
    if(R1 != Null){
        postOrder(T1[R1].left);
        postOrder(T1[R1].right);

        if(isFirst){
            printf("%d", T1[R1].data);
        }else{
            printf(" %d", T1[R1].data);
        }

        isFirst = false;
    }
}

int main(){
    int preOrder[MaxSize], inOrder[MaxSize], nodeNum;
    Tree R1;

    // printf("input - 请输入T的数据样本 \n");
    nodeNum = getInput(preOrder, inOrder);

    R1 = buildTree(T1, nodeNum, preOrder, inOrder);

    // printf("result - 后序遍历 \n");
    postOrder(R1);

    return 0;
}