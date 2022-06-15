/*

一元多项式的乘法与加法运算

设计函数分别求两个一元多项式的乘积与和。

输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式:
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。

输入样例:
4 3 4 -5 2 6 1 -2 0
3 5 20 -7 4 3 1

输出样例:
15 24 -25 22 30 21 -10 20 -21 8 35 6 -33 5 14 4 -15 3 18 2 -6 1
5 20 -4 4 -5 2 9 1 -2 0

《数据结构-入门指南》 - xubeijun/续杯君
[第5节 应用实例：两个一元多项式的乘积与和](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-005/polynomial-addition-and-multiplication)

[02-线性结构2 一元多项式的乘法与加法运算 - 掘金](https://juejin.cn/post/7014325372502147109)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PolyNode{
    int coefficient;
    int exponent;
    struct PolyNode *next;
} PolyNode, *Polynomial;

// 读取一元多项式
Polynomial readPoly();

// 计算一元多项式的乘积
Polynomial mult(Polynomial M, Polynomial N);

// 计算一元多项式的和
Polynomial add(Polynomial M, Polynomial N);

// 打印一元多项式
void printPoly(Polynomial P);

// 添加新节点到链表上
void attach(int coef, int expon, Polynomial *Rear);

Polynomial readPoly(){
    int count, coef, expon, x;
    Polynomial P,Rear,temp;

    // printf( "Enter a count of array: \n");
    x = scanf("%d",&count);

    P = (Polynomial)malloc(sizeof(struct PolyNode));
    if(!P){
        printf("malloc node is fail \n");
        exit(-1);
    }

    P->next  = NULL;

    Rear = P;

    // printf( "Enter an array, split by spaces: \n");
    for (int i = 0; i < count; i++){
        x = scanf("%d %d", &coef, &expon);

        if(x != 2){
            printf("stdin format is error \n");
            exit(-1);
        }

        attach(coef, expon, &Rear);
    }

    temp = P;
    P    = P->next;
    free(temp);
    temp = NULL;

    return P;
}

void attach(int coef, int expon, Polynomial *Rear){
    Polynomial P;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    if(!P){
        printf("malloc node is fail \n");
        exit(-1);
    }

    P->coefficient = coef;
    P->exponent    = expon;
    P->next        = (*Rear)->next;

    (*Rear)->next  = P;
    *Rear          = P;

}

Polynomial mult(Polynomial M, Polynomial N){
    Polynomial P,Rear,Tm,Tn,temp;
    int coef, expon;

    if(!M || !N){
        return NULL;
    }

    P = (Polynomial)malloc(sizeof(struct PolyNode));
    if(!P){
        printf("malloc node is fail \n");
        exit(-1);
    }

    P->next  = NULL;

    Tm = M;

    while(Tm){
        Tn   = N;
        Rear = P;

        while(Tn){
            coef  = Tm->coefficient * Tn->coefficient;
            expon = Tm->exponent + Tn->exponent;

            while(Rear->next && Rear->next->exponent > expon){
                Rear = Rear->next;
            }

            if(Rear->next && Rear->next->exponent == expon){
                coef = Rear->next->coefficient + coef;
                if(coef != 0){
                    Rear->next->coefficient = coef;
                }else{
                    temp       = Rear->next;
                    Rear->next = temp->next;
                    free(temp);
                    temp = NULL;
                }
            }else{
                if(coef != 0){
                    attach(coef, expon, &Rear);
                }
            }

            Tn = Tn->next;
        }

        Tm = Tm->next;
    }

    temp = P;
    P    = P->next;
    free(temp);
    temp = NULL;

    return P;
}

Polynomial add(Polynomial M, Polynomial N){
    Polynomial P,Rear,temp,remain;
    int coef, expon;

    P = (Polynomial)malloc(sizeof(struct PolyNode));
    if(!P){
        printf("malloc node is fail \n");
        exit(-1);
    }

    P->next  = NULL;

    Rear = P;

    while(M && N){
        if(M->exponent == N->exponent){
            coef  = M->coefficient + N->coefficient;
            expon = M->exponent;

            M = M->next;
            N = N->next;
        }else if(M->exponent > N->exponent){
            coef  = M->coefficient;
            expon = M->exponent;

            M = M->next;
        }else{
            coef  = N->coefficient;
            expon = N->exponent;

            N = N->next;
        }

        if(coef != 0){
            attach(coef, expon, &Rear);
        }
    }

    remain = M?M:(N?N:NULL);

    while(remain){
        coef = remain->coefficient;
        expon = remain->exponent;
        attach(coef, expon, &Rear);
        remain = remain->next;
    }

    temp = P;
    P    = P->next;
    free(temp);
    temp = NULL;

    return P;
}

void printPoly(Polynomial P){
    if(!P){
        printf("0 0");
    }

    while(P){
        printf("%d %d", P->coefficient, P->exponent);
        P = P->next;
        if(P){
            printf(" ");
        }
    }

    printf("\n");
}

int main(){
    Polynomial P1, P2, PM, PA;

    P1 = readPoly();
    P2 = readPoly();
    PM = mult(P1, P2);
    PA = add(P1, P2);

    // printf( "Polynomial multiplication result is: \n");
    printPoly(PM);
    // printf( "Polynomial addition result is: \n");
    printPoly(PA);

    return 0;
}
