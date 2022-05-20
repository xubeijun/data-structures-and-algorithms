/*
[中缀表示法 - 维基百科](https://zh.m.wikipedia.org/zh-hans/%E4%B8%AD%E7%BC%80%E8%A1%A8%E7%A4%BA%E6%B3%95)
[逆波兰表示法 - 维基百科](https://zh.m.wikipedia.org/zh-hans/%E9%80%86%E6%B3%A2%E5%85%B0%E8%A1%A8%E7%A4%BA%E6%B3%95)

表达式求值的基本策略：将中缀表达式转换为后缀表达式，然后求值。

《数据结构-入门指南》 - xubeijun/续杯君
[第3节 堆栈是什么 - 堆栈的链式存储实现](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-003/what-is-stack)

2组测试用例

19-(2+3*2)/4+6=

2*(9+6/3-5)+4=


*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXSIZE 255

// 操作数类型
typedef double OpdType;

// 运算符类型
typedef char OprType;

// 字符指针
typedef char *CharPtr;

// 节点类型 OPERAND=0:操作数, OPERATOR=1:运算符
typedef enum {OPERAND, OPERATOR} NodeTag;

typedef struct IRNode{
    NodeTag tag;
    union{
        OpdType operand;
        OprType operator;
    };
    struct IRNode *next;
} IRNode, *IRList;

typedef struct LinkStack{
    IRList top;
    int count;
} LinkStack, *IRStack;

// 初始化空堆栈
bool init(IRStack *S);

// 堆栈是否为空
bool isEmpty(IRStack S);

// 清空堆栈
void clear(IRStack *S);

// 销毁堆栈
void destroy(IRStack *S);

// 返回堆栈中栈顶的元素值
bool get(IRStack S, IRList *L);

// 入栈新元素为新栈顶
bool push(IRStack *S, IRList L);

// 对栈顶元素进行出栈
bool pop(IRStack *S, IRList *L);

// 复制堆栈节点，从src复制到dest
bool copyNode(IRList src, IRList *dest);

// 遍历堆栈
void traverse(IRStack S);

// 反转堆栈
void reverseStack(IRStack *S);

// 获取输入字符串
void getInput(CharPtr *exp);

// 获取中缀表达式
bool getInfix(IRStack *S, char *str);

// 将中缀表达式转换为后缀表达式
bool converter(IRStack S, IRStack *RPN);

// 后缀表达式求值
bool evaluate(IRStack RPN, OpdType *x);

// 分割字符
void strsub(CharPtr str, CharPtr *hp,  CharPtr *tp, NodeTag *tag);

// 是否优先入栈的运算符
bool isPriority(OprType M, OprType N);

// 四则运算
double arithmetic(double x, double y, OprType operator);

/**
 * [init 初始化空堆栈]
 * @param  S [堆栈二级指针]
 * @return bool [是否完成]
 */
bool init(IRStack *S){
    *S = (IRStack)malloc(sizeof(LinkStack));
    
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
bool isEmpty(IRStack S){
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
void clear(IRStack *S){
    IRList M = (*S)->top;
    IRList N;

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
void destroy(IRStack *S){
    if(*S){
        clear(S);
        free(*S);
        *S = NULL;
    }
}

/**
 * [get 返回堆栈中栈顶的元素]
 * @param  S [堆栈指针]
 * @param  L [栈顶元素]
 * @return bool [是否成功]
 */
bool get(IRStack S, IRList *L){
    if(isEmpty(S)){
        return false;
    }else{
        *L = S->top;
        return true;
    }
}

/**
 * [push 入栈新元素为新栈顶]
 * @param  S [堆栈二级指针]
 * @param  L [入栈元素]
 * @return bool [是否成功]
 */
bool push(IRStack *S, IRList L){
    L->next   = (*S)->top;
    (*S)->top = L;

    (*S)->count++;

    return true;
}

/**
 * [pop 对栈顶元素进行出栈]
 * @param  S [堆栈二级指针]
 * @param  L [对栈元素]
 * @return bool [是否成功]
 */
bool pop(IRStack *S, IRList *L){
    if(isEmpty(*S)){
        return false;
    }

    (*L)       = (*S)->top;
    (*S)->top  = (*L)->next;
    (*L)->next = NULL;

    (*S)->count--;

    return true;
}

/**
 * [traverse 遍历堆栈]
 * @param S [堆栈指针]
 */
void traverse(IRStack S){
    IRList P;
    for (P = S->top; P; P = P->next){
        if(P->tag == OPERAND){
            printf("%f", P->operand);
        }else{
            printf("%c", P->operator);
        }
    }

    printf("\n operation - traverse end \n\n");
}

/**
 * [reverseStack 反转堆栈，保证调用的顺序]
 * @param  S [堆栈二级指针]
 * @return   [description]
 */
void reverseStack(IRStack *S){
    IRList PrePtr = NULL, PostPtr = NULL, M = (*S)->top;

    while(M){
        PostPtr = M->next;

        if(PrePtr){
            M->next = PrePtr;
        }else{
            M->next = NULL;
        }

        PrePtr = M;

        if(!PostPtr){
            (*S)->top = M;
        }

        M = PostPtr;
    }
}

/**
 * [getInput 获取字符串]
 * @param  exp [二级指针字符串]
 * 
 */
void getInput(CharPtr *exp){
    char *result;

    printf( "Enter expression string and which is terminated by an equals sign: \n");

    result = fgets(*exp, MAXSIZE, stdin);
    if(result == NULL){
        printf("stdin format is error \n");
        exit(-1);
    }

    // '\0' ASCII is 0
    (*exp)[strcspn(*exp, "\r\n")] = 0;

    printf( "Enter expression string is end. \n\n");
}

/**
 * [getInfix 获取中缀表达式]
 * @param  S   [堆栈二级指针]
 * @param  str [字符串]
 * @return bool [是否成功]
 */
bool getInfix(IRStack *S, CharPtr str){
    bool f;
    NodeTag tag;
    int strLen = strlen(str);

    f = init(S);
    if(!f){
        return false;
    }

    if(strlen(str) <= 0){
        return false;
    }

    char dest[strLen];
    strncpy(dest, str, strLen);
    dest[strLen] = '\0';

    CharPtr sub = dest;

    char hpSub[strLen];
    char tpSub[strLen];

    CharPtr hp = hpSub;
    CharPtr tp = tpSub;

    while(strlen(sub) > 0){
        IRList L;

        strsub(sub, &hp, &tp, &tag);

        memset(sub, '\0', strlen(sub)+1);

        if(strlen(tp) > 0){
            strncpy(sub, tp, strlen(tp));
        }

        if(strcmp(hp, "=") == 0){
            continue;
        }

        L = (IRList)malloc(sizeof(IRNode));
        
        if(!L){
            return false;
        }

        L->tag = tag;

        if(tag == OPERAND){
            L->operand = atof(hp);
        }else{
            L->operator = *hp;
        }

        f = push(S, L);

        if(!f){
            return false;
        }
    }

    reverseStack(S);

    return true;
}

/**
 * [strsub 分割字符]
 * @param str [字符串]
 * @param hp  [表头字符串]
 * @param tp  [表尾字符串]
 * @param tag [表头节点类型]
 */
void strsub(CharPtr str, CharPtr *hp,  CharPtr *tp, NodeTag *tag){
    int pos = 0;
    int strLen = strlen(str);
    const char opr[] = "+-*/()=";
    const char opd[] = "0123456789";

    *tag = OPERAND;

    if(strchr(opr, str[0])){
        *tag = OPERATOR;
    }

    for (int i = 0; i <= strLen; ++i){
        if(strchr(opr, str[i])){
            pos = (pos==0)?(pos+1):pos;
            break;
        }else if(strchr(opd, str[i])){
            pos++;
            continue;
        }else{
            printf("the string %s include invalid character %c. \n", str, str[i]);
            exit(-1);
        }
    }

    memset(*hp, '\0', pos+1);
    if(pos > 0){
        strncpy(*hp, str, pos);
    }
    
    int tpPos = strLen - pos;
    memset(*tp, '\0', tpPos+1);
    if(strLen > pos){
        strncpy(*tp, str+pos, tpPos);
    }
}

/**
 * [converter 将中缀表达式转换为后缀表达式]
 * @param  S   [中缀表达式的堆栈指针]
 * @param  RPN [后缀表达式的堆栈二级指针]
 * @return bool [是否成功]
 *
 *运算数：直接输出；
 *左括号：入栈；
 *右括号：将栈顶的运算符出栈并输出，直到遇到左括号，其出栈但不输出；
 *运算符：
 *  若优先级大于栈顶运算符，则入栈；
 *  若优先级小于或等于栈顶运算符，则将栈顶运算符出栈并输出，在与新的栈顶运算符进行比较，直到优先级大于栈顶运算符为止，则入栈；
 *如果各个对象处理完毕，则输出堆栈中存留的运算符
 */
bool converter(IRStack S, IRStack *RPN){
    bool f;
    IRStack OPR;
    IRList P,N;

    f = init(RPN);
    if(!f){
        return false;
    }

    f = init(&OPR);
    if(!f){
        return false;
    }

    for (P = S->top; P; P = P->next){
        f = copyNode(P, &N);
        
        if(!f){
            return false;
        }

        if(P->tag == OPERAND){
            f = push(RPN, N);

            if(!f){
                return false;
            }
        }else{
            switch(P->operator){
                case '(' :
                    f = push(&OPR, N);

                    if(!f){
                        return false;
                    }
                    break;
                case ')' :
                    while(OPR->count > 0){
                        IRList M;

                        f = pop(&OPR, &M);
                        if(!f){
                            return false;
                        }

                        if(strcmp(&(M->operator), "(") == 0){
                            break;
                        }

                        f = push(RPN, M);

                        if(!f){
                            return false;
                        }
                    }
                    break;
                default :
                    while(!isEmpty(OPR)){
                        IRList M;
                        f = get(OPR, &M);
                        if(!f){
                            return false;
                        }

                        f = isPriority(P->operator, M->operator);
                        if(!f){
                            IRList M;
                            // low priority
                            f = pop(&OPR, &M);
                            if(!f){
                                return false;
                            }

                            f = push(RPN, M);
                            if(!f){
                                return false;
                            }

                            if(isEmpty(OPR)){
                                f = push(&OPR, N);
                                if(!f){
                                    return false;
                                }
                                break;
                            }
                        }else{
                            // hight priority
                            f = push(&OPR, N);
                            if(!f){
                                return false;
                            }
                            break;
                        }
                    }

                    if(isEmpty(OPR)){
                        f = push(&OPR, N);
                        if(!f){
                            return false;
                        }
                    }
            }
        }
    }

    while(!isEmpty(OPR)){
        IRList M;
        f = pop(&OPR, &M);
        if(!f){
            return false;
        }

        f = push(RPN, M);
        if(!f){
            return false;
        }
    }

    destroy(&OPR);

    reverseStack(RPN);

    return true;
}

/**
 * [copyNode 复制堆栈节点，从src复制到dest]
 * @param  src  [节点来源]
 * @param  dest [复制目标]
 * @return      [description]
 */
bool copyNode(IRList src, IRList *dest){
    *dest = (IRList)malloc(sizeof(IRNode));
        
    if(!(*dest)){
        return false;
    }

    (*dest)->tag = src->tag;

    if((*dest)->tag == OPERAND){
        (*dest)->operand = src->operand;
    }else{
        (*dest)->operator = src->operator;
    }

    return true;
}

/**
 * [isPriority 是否优先入栈的运算符]
 * @param  M [运算符]
 * @param  topN [栈顶运算符]
 * @return   [description]
 */
bool isPriority(OprType M, OprType topN){
    bool f = false;

    switch(M){
        case '*' :
        case '/' :
            if(strchr("(", topN)){
                f = true;
            }
            if(strchr("+-", topN)){
                f = true;
            }
            break;
        case '+' :
        case '-' :
            if(strchr("(", topN)){
                f = true;
            }
            break;
        case '(' :
            f = true;
            break;
    }

    return f;
}

/**
 * [evaluate 后缀表达式求值]
 * @param  RPN [后缀堆栈]
 * @param  x   [计算结果]
 * @return     [description]
 */
bool evaluate(IRStack RPN, OpdType *x){
    bool f;
    IRStack R; //store result
    IRList P;
    double atom;

    f = init(&R);
    if(!f){
        return false;
    }

    for (P = RPN->top; P; P = P->next){
        IRList M,Head,Tail;

        if(P->tag == OPERAND){
            f = copyNode(P, &M);
            if(!f){
                return false;
            }

            f = push(&R, M);
            if(!f){
                return false;
            }
        }else{
            f = pop(&R, &Tail);
            if(!f){
                return false;
            }

            f = pop(&R, &Head);
            if(!f){
                return false;
            }

            atom = arithmetic(Head->operand, Tail->operand, P->operator);

            M = (IRList)malloc(sizeof(IRNode));
            if(!M){
                return false;
            }

            M->tag = OPERAND;
            M->operand = atom;

            f = push(&R, M);
            if(!f){
                return false;
            }
        }
    }

    if(R->count != 1){
        return false;
    }

    *x = R->top->operand;

    destroy(&R);

    return true;
}

/**
 * [arithmetic 四则运算]
 * @param  x        [首位运算数]
 * @param  y        [末位运算数]
 * @param  operator [运算符]
 * @return double   [运算值]
 */
double arithmetic(double x, double y, OprType operator){
    double res;

    switch(operator){
        case '*' :
            res = x*y;
            break;
        case '/' :
            if(y == 0){
                printf("the divisor can't be zero");
                exit(-1);
            }
            res = x/y;
            break;
        case '+' :
            res = x+y;
            break;
        case '-' :
            res = x-y;
            break;
        default :
            printf("the %c is invalid operator  \n\n", operator);
            exit(-1);
    }

    return res;
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
    char buf[MAXSIZE];
    CharPtr exp = buf;
    OpdType x;
    IRStack infix;
    IRStack reverse;

    getInput(&exp);
    printf("operation - getInput \n the expression string is: %s \n\n", exp);

    f = getInfix(&infix, exp);
    printf("operation - getInfix \n it is %s \n\n", isValid(f));

    printf("operation - traverse Infix notation, its count is %d \n\n", infix->count);
    traverse(infix);

    f = converter(infix, &reverse);
    printf("operation - converter \n it is %s \n\n", isValid(f));

    printf("operation - traverse Reverse Polish notation, its count is %d \n\n", reverse->count);
    traverse(reverse);

    f = evaluate(reverse, &x);
    printf("operation - evaluate \n it is %s, the result is %f \n\n", isValid(f), x);

    destroy(&infix);

    destroy(&reverse);

    return 0;
}