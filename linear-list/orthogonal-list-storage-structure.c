/*
[十字链表 - 百度百科](https://baike.baidu.com/item/%E5%8D%81%E5%AD%97%E9%93%BE%E8%A1%A8)
[多链表 - 数据结构课程讲义 - Robert Holte](https://webdocs.cs.ualberta.ca/~holte/T26/mlinked-lists.html)

十字链表（英语：Orthogonal linked list）是计算机科学中的一种高级数据结构，在Linux内核中应用广泛。具体说，一个二维十字链表是链表的元素同时链接左右水平邻结点与上下垂直邻结点。这一方法可以推广到更高维以存储稀疏矩阵、图等数据集合。

十字链表是一种典型的多重链表，可以用来存储稀疏矩阵。

《数据结构-入门指南》 - xubeijun/续杯君
[第2节 常见链表有哪些 - 十字链表](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-002/the-common-linked-lists#orthogonal-list)

2组测试用例

行数：4
列数：3
非零元个数：4
三元组：(1,2,88)(3,1,27)(4,1,19)(4,3,66)

行数：5
列数：5
非零元个数：8
三元组：(1,1,-3)(1,3,2)(2,4,-1)(3,2,4)(4,1,6)(4,5,5)(5,1,3)(5,3,2)

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int ElemType;

typedef struct OLNode {
    int  row, column; //行号与列号
    ElemType value; //值
    struct OLNode *right, *down; //同行、同列下一个元素的指针
}OLNode, *OLink;

typedef struct {
    OLink *rowHead; //行链表头指针
    OLink *colHead; //列链表头指针
    int  m, n, k; //矩阵的行数、列数和非零元个数
}OList;

/**
 * [insert 在十字链表L的位置m,n处，插入元素x]
 * @param  L [十字链表L指针]
 * @param  m [位置m行]
 * @param  n [位置n列]
 * @param  x [元素x]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool insert(OList *L, int m, int n, ElemType x){
    OLNode *p = NULL, *cur = NULL;

    if((m < 1) || (m > L->m) || (n < 1) || (n > L->n)){
        return false;
    }

    p = (OLNode *)malloc(sizeof(OLNode));

    if(!p){
        return false;
    }

    p->row    = m;
    p->column = n;
    p->value  = x;
    p->right  = NULL;
    p->down   = NULL;

    // insert to row
    if(L->rowHead[m-1] == NULL || L->rowHead[m-1]->column > n){
        p->right        = L->rowHead[m-1];
        L->rowHead[m-1] = p;
    }else{
        cur = L->rowHead[m-1];
        while(cur){
            // The node currently exists todo
            if(cur->row == m && cur->column == n){
                free(p);
                p = NULL;
                return false;
            }

            // [cur p null] or [cur p cur->right null]
            if(cur->right == NULL || cur->right->column > n){
                p->right   = cur->right;
                cur->right = p;
                break;
            }
            // next node
            cur = cur->right;
        }
    }

    // insert to column
    if(L->colHead[n-1] == NULL || L->colHead[n-1]->row > m){
        p->down         = L->colHead[n-1];
        L->colHead[n-1] = p;
    }else{
        cur = L->colHead[n-1];
        while(cur){
            // The node currently exists todo
            if(cur->row == m && cur->column == n){
                free(p);
                p = NULL;
                return false;
            }

            // [cur p null] or [cur p cur->down null]
            if(cur->down == NULL || cur->down->row > m){
                p->down   = cur->down;
                cur->down = p;
                break;
            }
            // next node
            cur = cur->down;
        }
    }

    L->k++;
    return true;
}

/**
 * [init 初始化十字链表L-稀疏矩阵]
 * @param  L [十字链表L指针]
 * @param  m [矩阵的行数]
 * @param  n [矩阵的列数]
 * @param  k [矩阵的非零元个数]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool init(OList *L, int m, int n, int k){
    int  row, column, x;
    ElemType value;
    bool flag;

    if(m < 0 || n < 0 || k < 0){
        return false;
    }
    
    L->m       = m;
    L->n       = n;
    L->rowHead = NULL;
    L->colHead = NULL;

    L->rowHead = (OLink *)malloc(m*sizeof(OLink));
    L->colHead = (OLink *)malloc(n*sizeof(OLink));

    if(!L->rowHead || !L->colHead){
        return false;
    }

    for (int i = 0; i < m; ++i){
        L->rowHead[i] = NULL;
    }

    for (int i = 0; i < n; ++i){
        L->colHead[i] = NULL;
    }

    printf( "Enter nonzero elements: \n");
    for (int i = 0; i < k; i++){
        x = scanf("%*[^0123456789]%d,%d,%d]", &row, &column, &value);

        if(x!=3){
            printf("stdin format is error, iteration is %d k is %d x is %d \n",i,k,x);
            exit(-1);
        }

        flag = insert(L,row,column,value);

        if(!flag){
            printf("insert is error \n");
            exit(-1);
        }
    }

    return true;
}

/**
 * [isEmpty 十字链表L是否为空表]
 * @param  L [十字链表L指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool isEmpty(OList *L){
    if(L->k == 0){
        return true;
    }else{
        return false;
    }
}

/**
 * [length 返回十字链表L的长度，即元素的个数。]
 * @param  L [十字链表L指针]
 * @return int [返回十字链表L的长度]
 */
int length(OList *L){
    return L->k;
}

/**
 * [get 返回十字链表L中，第i个位置的元素值。]
 * @param  L [十字链表L指针]
 * @param  m [位置m行]
 * @param  n [位置n列]
 * @param  x [位置i元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool get(OList *L, int m, int n, ElemType *x){
    OLNode *p = NULL, *cur = NULL;

    if((m < 1) || (m > L->m) || (n < 1) || (n > L->n)){
        return false;
    }

    cur = L->rowHead[m-1];

    if(!cur){
         return false;
    }

    while(cur){
        if(cur->column == n ){
            p = cur;
            break;
        }

        // next node
        cur = cur->right;
    }

    if(!p){
        return false;
    }

    *x = p->value;
    return true;
}

/**
 * [prior 返回十字链表L中，第(m,n-1)元素值。]
 * @param  L [十字链表L指针]
 * @param  m [位置m行]
 * @param  n [位置n列]
 * @param  x [位置(m,n-1)元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool prior(OList *L, int m, int n, ElemType *x){
    return get(L, m,  n-1, x);
}

/**
 * [next 返回十字链表L中，第(m+1,n)元素值。]
 * @param  L [十字链表L指针]
 * @param  m [位置m行]
 * @param  n [位置n列]
 * @param  x [位置(m+1,n)元素值的指针地址]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool next(OList *L, int m, int n, ElemType *x){
    return get(L, m+1,  n, x);
}

/**
 * [locate 返回十字链表L中，元素值x的首次出现的节点位置。]
 * @param  L [十字链表L指针]
 * @param  x [元素值x]
 * @param  p [首次出现元素值x节点指针的指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool locate(OList *L, ElemType x, OLink *p){
    OLNode *cur = NULL;
    for (int i = 0; i < L->m; ++i){
        cur = L->rowHead[i];
        while(cur){
            if(cur->value == x){
                *p = cur;
                return true;
            }
            cur = cur->right;
        }
    }
    return false;
}

/**
 * [traverse 遍历输出所有元素值]
 * @param L [十字链表L指针]
 */
void traverse(OList *L){
    OLNode *p = NULL, *cur = NULL;

    for (int i = 0; i < L->m; ++i)
    {   
        cur = L->rowHead[i];
        while(cur){
            p = cur;
            printf("(%d,%d,%d)", p->row, p->column, p->value);
            cur = cur->right;
        }
    }
}

/**
 * [delete 在十字链表L的位置i处。删除其元素。]
 * @param  L [十字链表L指针]
 * @param  m [位置m行]
 * @param  n [位置n列]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool delete(OList *L, int m, int n){
    OLNode *p = NULL, *cur = NULL, *curCol = NULL, *pUp = NULL, *pLeft = NULL;

    if((m < 1) || (m > L->m) || (n < 1) || (n > L->n)){
        return false;
    }

    cur    = L->rowHead[m-1];
    curCol = L->colHead[n-1];

    if(!cur || !curCol){
         return false;
    }

    while(cur){
        if(cur->column == n ){
            p = cur;
            break;
        }

        pLeft = cur;

        // next node
        cur = cur->right;
    }

    while(curCol){
        if(curCol->row == m ){
            break;
        }

        pUp = curCol;

        // next node
        curCol = curCol->down;
    }

    if(!p){
        return false;
    }

    if(pLeft){
        pLeft->right = p->right;
    }

    if(pUp){
        pUp->down = p->down;
    }

    if(p == L->rowHead[m-1] && L->rowHead[m-1]->right == NULL){
        L->rowHead[m-1] = NULL;
    }

    if(p == L->colHead[n-1] && L->colHead[n-1]->down == NULL){
        L->colHead[n-1] = NULL;
    }

    free(p);
    p = NULL;
    L->k--;

    return true;

}

/**
 * [clear 将十字链表清空，清除所有元素。]
 * @param L [十字链表L指针]
 */
void clear(OList *L){
    OLNode *p = NULL, *cur = NULL;

    for (int i = 0; i < L->m; ++i){
        cur = L->rowHead[i];
        while(cur){
            p   = cur;
            cur = cur->right;
            free(p);
            p = NULL;
            L->k--;
        }
        L->rowHead[i] = NULL;
    }

    for (int i = 0; i < L->n; ++i){
        L->colHead[i] = NULL;
    }
}

/**
 * [destroy 将十字链表销毁，释放内存。]
 * @param L [十字链表L指针]
 */
void destroy(OList *L){
    clear(L);

    free(L->rowHead);
    free(L->colHead);

    L->rowHead = L->colHead = NULL;
    L->m = L->n = L->k = 0;
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
    bool flag;
    int row,col,len;
    int m,n,k,x;
    ElemType elem;
    // OLNode *p = NULL;
    OLink p = NULL;

    printf( "Enter a Number of rows: ");
    x = scanf("%d",&m);

    if(x!=1){
        printf("stdin format is error \n");
        exit(-1);
    }

    printf( "Enter a Number of columns: ");
    x = scanf("%d",&n);

    if(x!=1){
        printf("stdin format is error \n");
        exit(-1);
    }

    printf( "Enter a Number of nonzero elements: ");
    x = scanf("%d",&k);

    if(x!=1){
        printf("stdin format is error \n");
        exit(-1);
    }

    OList L;
    flag = init(&L,m,n,k);
    printf("operation - init \n init flag is %s \n\n", isValid(flag));

    flag = isEmpty(&L);
    printf("operation - isEmpty \n empty flag is %s \n\n", isValid(flag));

    row = 1;
    col = 2;
    elem = 11;
    flag = insert(&L,row,col,elem);
    printf("operation - insert \n insert flag is %s, row is %d, col is %d, x is %d \n\n", isValid(flag), row, col, elem);

    row = 1;
    col = 2;
    elem = 66;
    flag = insert(&L,row,col,elem);
    printf("operation - insert \n insert flag is %s, row is %d, col is %d, x is %d \n\n", isValid(flag), row, col, elem);

    len = length(&L);
    printf("operation - length \n length is %d \n\n", len);

    row = 1;
    col = 2;
    elem = 0;
    flag = get(&L,row,col,&elem);
    printf("operation - get \n get flag is %s, row is %d, col is %d, x is %d \n\n", isValid(flag), row, col, elem);

    row = 1;
    col = 2;
    elem = 0;
    flag = prior(&L,row,col,&elem);
    printf("operation - prior \n prior flag is %s, row is %d, col is %d, x is %d \n\n", isValid(flag), row, col, elem);

    row = 1;
    col = 2;
    elem = 0;
    flag = next(&L,row,col,&elem);
    printf("operation - next \n next flag is %s, row is %d, col is %d, x is %d \n\n", isValid(flag), row, col, elem);

    elem = 11;
    flag = locate(&L, elem, &p);
    printf("operation - locate \n locate flag is %s, row is %d, col is %d, x is %d \n\n", isValid(flag), p?p->row:0, p?p->column:0, p?p->value:elem);

    row = 1;
    col = 2;
    flag = delete(&L,row,col);
    printf("operation - delete \n delete flag is %s, row is %d, col is %d \n\n", isValid(flag), row, col);

    printf("operation - traverse \n\n");
    traverse(&L);
    printf("\n operation - traverse is end \n\n");

    clear(&L);
    printf("operation - clear \n\n");

    destroy(&L);
    printf("operation - destroy \n\n");

    return 0;
}