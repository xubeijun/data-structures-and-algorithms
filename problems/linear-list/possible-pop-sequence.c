/*

02-线性结构4 Pop Sequence

Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.

Input Specification:
Each input file contains one test case. For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence of N numbers. All the numbers in a line are separated by a space.

Output Specification:
For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

Sample Input:

5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2


Sample Output:

YES
NO
NO
YES
NO

《数据结构-入门指南》 - xubeijun/续杯君
[第7节 应用实例：堆栈的弹出序列](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-007/possible-pop-sequence)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

// sequential stack
typedef struct SqNode{
    ElemType *data;
    ElemType top;
    ElemType maxSize;
}  SqNode, *SqStack;

// 初始化空堆栈
SqStack init(int maxSize);

// 堆栈是否为空
bool isEmpty(SqStack S);

// 堆栈是否已满
bool isFull(SqStack S);

// 返回堆栈中栈顶的元素值
ElemType get(SqStack S);

// 入栈新元素为新栈顶
bool push(SqStack *S, ElemType x);

// 对栈顶元素进行出栈
ElemType pop(SqStack *S);

// 销毁堆栈
void destroy(SqStack *S);

// 读取元信息
void readMeta(int *maxSize, int *pushNums, int *lineNums);

// 验证弹出顺序
void validPopSeq(int maxSize, int pushNums, int lineNums);

SqStack init(int maxSize){
    SqStack S;

    S = (SqStack)malloc(sizeof(SqNode));
    if(!S){
        printf("malloc SqStack is fail \n");
        exit(-1);
    }

    S->data = (ElemType *)malloc(maxSize*sizeof(ElemType));
    if(!S->data){
        return false;
    }

    S->top      = -1;
    S->maxSize  = maxSize;

    return S;
}

bool isEmpty(SqStack S){
    if(S->top == -1){
        return true;
    }else{
        return false;
    }
}

bool isFull(SqStack S){
    if(S->top == S->maxSize-1){
        return true;
    }else{
        return false;
    }
}

ElemType get(SqStack S){
    return S->data[S->top];
}

bool push(SqStack *S, ElemType x){
    if(isFull(*S)){
        return false;
    }

    (*S)->data[++(*S)->top] = x;
    return true;
}

ElemType pop(SqStack *S){
    return (*S)->data[(*S)->top--];
}

void destroy(SqStack *S){
    free((*S)->data);
    (*S)->data    = NULL;

    (*S)->top     = -1;
    (*S)->maxSize = 0;

    free((*S));
    *S = NULL;
}

void readMeta(int *maxSize, int *pushNums, int *lineNums){
    int x;

    x = scanf("%d %d %d", maxSize, pushNums, lineNums);
    if(x != 3){
        printf("input is fail \n");
        exit(-1);
    }
}

void validPopSeq(int maxSize, int pushNums, int lineNums){
    int x, line, seq, index, validNum;
    int popArrays[lineNums][pushNums];
    bool state, isValid = false;
    SqStack S;

    // read possible pop sequence
    for(line = 0; line < lineNums; line++){
        for(index=0; index < pushNums; index++){
            x = scanf("%d", &validNum);
            if(x != 1){
                printf("input is fail \n");
                exit(-1);
            }

            popArrays[line][index] = validNum;
        }
    }

    // valid possible pop sequence
    for(line = 0; line < lineNums; line++){
        index = 0;
        S     = init(maxSize);

        for (seq = 1; seq <= pushNums; ++seq){
            state = push(&S, seq);
            if(!state){
                break;
            }

            while(!isEmpty(S) && get(S) == popArrays[line][index]){
                pop(&S);
                index++;
            }
        }

        isValid = (index == pushNums)?true:false;

        destroy(&S);


        if(isValid){
            printf("YES");
        }else{
            printf("NO");
        }

        if(line != (lineNums-1)){
            printf("\n");
        }
    }
}

int main(){
    int maxSize, pushNums, lineNums;

    readMeta(&maxSize, &pushNums, &lineNums);

    validPopSeq(maxSize, pushNums, lineNums);
}
