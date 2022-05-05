/*
[广义表 - 百度百科](https://baike.baidu.com/item/%E5%B9%BF%E4%B9%89%E8%A1%A8)
[广义表#扩展线性链表存储表示 - 维基百科](https://zh.wikipedia.org/wiki/%E5%B9%BF%E4%B9%89%E8%A1%A8#%E6%89%A9%E5%B1%95%E7%BA%BF%E6%80%A7%E9%93%BE%E8%A1%A8%E5%AD%98%E5%82%A8%E8%A1%A8%E7%A4%BA)

广义表（英语：Generalized List）是一种非线性的数据结构。但如果广义表的每个元素都是原子，它就变成了线性表。广义表广泛地用于人工智能等领域的LISP语言。

广义表一般记作 LS = (a1, a2, ···, an), n是它的长度，ai可以是单个元素(原子)，也可以是广义表(子表)，当广义表非空时，称第一个元素a1为LS的表头，称其余元素组成的表为LS的表尾。
注意：表头是元素(可以是原子，也可以是广表)，表尾一定是广义表。
E=(a, E)是一个递归的表。D=(( ),(e),(a,(b,c,d)))是多层次的广义表，长度为3，深度为3。例：((a),a)的表头是(a)，表尾是(a)，((a))的表头是(a)，表尾是( )。

《数据结构-入门指南》 - xubeijun/续杯君
[第2节 常见链表有哪些 - 广义表](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-002/the-common-linked-lists#generalized-list)

5组测试用例

()

(a,b)

(x,(a,b))

((x,(a,b)),y)

((x,(a,b)),((x,(a,b)),y))

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 默认输入字符串最大长度
#define MAXLEN 255

// 输出类型 ELEMENT=0:元素, BRACKET=1:括号
typedef enum {ELEMENT, BRACKET} OutTag;

// 复制类型 HEAD=0:表头, TAIL=1:表尾
typedef enum {HEAD, TAIL} CopyTag;

// 节点类型 ATOM=0:原子，LIST=1:子表
typedef enum {ATOM, LIST} ElemTag;

// 原子值类型
typedef char AtomType;

// 广义表字符串数组
typedef char GListStr[MAXLEN];

typedef struct GLNode {
    ElemTag tag; //节点类型
    union {
        AtomType atom; // 原子结点的值域
        struct GLNode *hp; // 表结点的表头指针
    };
    struct GLNode *tp; // 表尾指针，指向下一个元素结点
}GLNode, *GList;

// 初始化广义表
bool init(GList *L);

// 创建广义表
bool create(GList *L, GListStr str);

// 分割广义表字符串，获得表头字符串，表尾字符串，表头节点类型
void strsub(GListStr str,GListStr *hpSub, GListStr *tpSub, ElemTag *hpTag);

// 广义表是否为空表
bool isEmpty(GList L);

// 获取广义表长度
int length(GList L);

// 获取广义表深度
int depth(GList L);

// 广义表头插法插入
bool insert(GList *L, GList v);

// 广义表头插法删除
bool delete(GList *L, GList *x);

// 获取广义表的表头
bool getHead(GList L, GList *x);

// 获取广义表的表尾
bool getTail(GList L, GList *x);

// 复制广义表，从src复制到dest
void copyGList(GList src, GList *dest);

// 遍历广义表
void traverse(GList L, OutTag O);

// 遍历输出所有原子值
void printATOM(GList L);

// 遍历输出带括号的广义表
void printGList(GList L);

// 清空广义表节点
void clear(GList *L);

// 销毁广义表节点
void destroy(GList *L);

/**
 * [init 初始化广义表L，该空表的长度为0，深度为1]
 * @param  L [广义表L的二级指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool init(GList *L){
    *L = (GList)malloc(sizeof(GLNode));

    if(!(*L)){
        return false;
    }

    (*L)->tag = LIST;
    (*L)->hp  = NULL;
    (*L)->tp  = NULL;

    return true;
}

/**
 * [create 生成广义表，根据广义表字符串数组]
 * @param  L   [广义表L的二级指针]
 * @param  str [广义表字符串数组]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool create(GList *L, GListStr str){
    bool f;
    GListStr hpSub="", tpSub="", sub="", emp="()";
    ElemTag hpTag;
    AtomType atom;

    if(!(*L)){
        f = init(L);
        if(!f){
            // 广义表节点生成失败
            return false;
        }
    }

    // 空表
    if(strcmp(str,emp) == 0){
        return true;
    }

    strsub(str, &hpSub, &tpSub, &hpTag);

    if(hpTag == ATOM){
        strncpy(&atom,hpSub,1);

        (*L)->tag = ATOM;
        (*L)->atom = atom;
    }else{
        (*L)->tag = LIST;
        // 去除括号
        memset(sub, '\0', sizeof(sub));
        strncpy(sub, hpSub+1, strlen(hpSub)-2);
        f = create(&((*L)->hp), sub);
        if(!f){
            // 表头递归生成失败
            return false;
        }
    }

    if(strlen(tpSub) > 0){
        f = create(&((*L)->tp), tpSub);
        if(!f){
            // 表尾递归生成失败
            return false;
        }
    }

    return true;
}

/**
 * [strsub 分割广义表字符串]
 * @param  str   [广义表字符串数组]
 * @param  hpSub [表头字符串]
 * @param  tpSub [表尾字符串]
 * @param  hpTag [表头节点类型]
 */
void strsub(GListStr str,GListStr *hpSub, GListStr *tpSub, ElemTag *hpTag){
    int i, n = 0;
    int hpPos = 0;
    GListStr sub,item;
    *hpTag = ATOM;

    memset(sub,'\0',sizeof(sub));
    memset(item,'\0',sizeof(item));

    strncpy(sub, str, strlen(str));

    for (i = 0; i < strlen(sub); ++i){
        ++hpPos;

        strncpy(item,sub+i,1);

        if(i == 0 && strcmp(item, "(") == 0){
            *hpTag = LIST;
        }

        if(strcmp(item, "(") == 0){
            ++n;
        }
        if(strcmp(item, ")") == 0){
            --n;
        }

        if((*hpTag) == ATOM && strcmp(item, ",") == 0){
            break;
        }

        if((*hpTag) == LIST && n == 0){
            break;
        }
    }

    if(hpPos > 0){
        memset((*hpSub), '\0', sizeof((*hpSub)));
        strncpy((*hpSub), sub, hpPos);
        
    }

    if(strlen(sub) > hpPos){
        memset((*tpSub), '\0', sizeof((*tpSub)));
        if((*hpTag) == ATOM){
            strncpy((*tpSub), sub+(hpPos), strlen(sub)-(hpPos));
        }else{
            strncpy((*tpSub), sub+(hpPos+1), strlen(sub)-(hpPos+1));
        }
    }
}

/**
 * [isEmpty 广义表L是否为空表]
 * @param  L [广义表L的指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool isEmpty(GList L){
    if(!L){
        printf("L does not exist. \n");
        exit(-1);
    }

    if(L->tag == LIST && !L->hp && !L->tp){
        return true;
    }else{
        return false;
    }
}

/**
 * [length 返回广义表L的长度，最高层的节点个数。]
 * @param  L [广义表L的指针]
 * @return int [返回广义表L的长度]
 */
int length(GList L){
    int len;
    if(!L){
        printf("L does not exist. \n");
        exit(-1);
    }
    
    GList p = L->hp;

    for(len = 0; p; len++){
        p = p->tp;
    }

    return len;
}

/**
 * [length 返回广义表L的深度，表展开后所含括号的层数。]
 * @param  L [广义表L的指针]
 * @return int [返回广义表L的深度]
 */
int depth(GList L){
    int dep,max;
    GList p;

    if(!L){
        printf("L does not exist. \n");
        exit(-1);
    }

    // L为原子
    if(L && L->tag == ATOM){
        return 0;
    }

    // L为空表
    if(L && L->tag == LIST && !L->hp){
        return 1;
    }

    p = L->hp;

    while(p){
        dep = depth(p);
        if(dep > max){
            max = dep;
        }
        p = p->tp;
    }

    return max + 1;
}

/**
 * [insert 在广义表L中使用头插法，插入结点x]
 * @param  L [广义表L的二级指针]
 * @param  v [结点v]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool insert(GList *L, GList v){
    if(!(*L) || !v){
        printf("GList L or v does not exist. \n");
        return false;
    }
    v->tp = (*L)->hp;
    (*L)->hp = v;

    return true;
}

/**
 * [delete 在广义表L中使用头插法，删除其元素。]
 * @param  L [广义表L的二级指针]
 * @param  x [被删除的结点x的二级指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool delete(GList *L, GList *x){
    if(!L){
        printf("L does not exist. \n");
        return false;
    }

    if(!(*L)->hp){
        printf("L head node does not exist. \n");
        return false;
    }

    *x       = (*L)->hp;
    (*L)->hp = (*x)->tp;
    (*x)->tp = NULL;

    return true;
}

/**
 * [getHead 返回广义表L中的头结点。]
 * @param  L [广义表L的指针]
 * @param  x [头结点x的二级指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool getHead(GList L, GList *x){
    if(!L){
        printf("L does not exist. \n");
        return false;
    }

    if(L->hp){
        copyGList(L->hp, x);
        (*x)->tp  = NULL;
    }

    return true;
}

/**
 * [getTail 返回广义表L中的尾结点。]
 * @param  L [广义表L的指针]
 * @param  x [尾结点x的二级指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool getTail(GList L, GList *x){
    if(!L){
        printf("L does not exist. \n");
        return false;
    }

    if(L->hp && L->hp->tp){
        copyGList(L->hp->tp, &((*x)->hp));
    }

    return true;
}

/**
 * [copyGList 复制广义表]
 * @param src  [复制来源广义表]
 * @param dest [复制目标广义表]
 */
void copyGList(GList src, GList *dest){
    bool f;

    if(src){
        if(!(*dest)){
            f = init(dest);
            if(!f){
                printf("copyGList fails when calling init. \n");
                exit(-1);
            }
        }

        (*dest)->tag = src->tag;

        if(src->tag == ATOM){
            (*dest)->atom = src->atom;
        }else{
            copyGList(src->hp, &((*dest)->hp));
        }

        copyGList(src->tp, &((*dest)->tp));
    }
}

/**
 * [traverse 遍历输出所有元素值]
 * @param L [广义表L的指针]
 * @param O [输出类型]
 */
void traverse(GList L, OutTag O){
    if(O == ELEMENT){
        printATOM(L);
    }else{
        printGList(L);
    }

    printf("\n operation - traverse end \n\n");
}

/**
 * [printATOM 遍历输出所有原子值]
 * @param L [广义表L的指针]
 */
void printATOM(GList L){
    if(L){
        if(L->tag == ATOM){
            printf("%c", L->atom);
        }

        if(L->tag == LIST){
            printATOM(L->hp);
        }

        if(L->tp){
            printf(",");
            printATOM(L->tp);
        }
    }
}

/**
 * [printGList 遍历输出带括号的广义表]
 * @param L [广义表L的指针]
 */
void printGList(GList L){
    if(L){
        if(L->tag == ATOM){
            printf("%c", L->atom);
        }else{
            printf("(");
            printGList(L->hp);
            printf(")");
        }

        if(L->tp){
            printf(",");
            printGList(L->tp);
        }
    }
}

/**
 * [clear 将广义表清空，清除所有元素。]
 * @param L [广义表L的二级指针]
 */
void clear(GList *L){
    if(*L){
        if((*L)->hp){
            destroy(&(*L)->hp);
        }
    }
}

/**
 * [destroy 将广义表销毁，释放内存。]
 * @param L [广义表L的二级指针]
 */
void destroy(GList *L){
    GList H,T;
    if(*L){
        if((*L)->tag == LIST){
            H = (*L)->hp;
            destroy(&H);
        }

        T = (*L)->tp;
        destroy(&T);

        free(*L);
        (*L) = NULL;
    }
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
    int len, dep, x;
    GListStr str, s1 = "(m,n)";
    AtomType elem;
    GList L, M, N, H, T;

    printf( "Enter Generalized List: ");
    x = scanf("%s",str);

    if(x!=1){
        printf("stdin format is error \n");
        exit(-1);
    }

    printf("GListStr is %s \n\n", str);

    f = init(&L);
    printf("operation - init \n it is %s \n\n", isValid(f));

    f = isEmpty(L);
    printf("operation - isEmpty \n it is %s \n\n", isValid(f));

    f = create(&L, str);
    printf("operation - create \n it is %s \n\n", isValid(f));

    len = length(L);
    printf("operation - length \n it is %d \n\n", len);

    dep = depth(L);
    printf("operation - depth \n it is %d \n\n", dep);

    init(&M);
    create(&M, s1);
    f = insert(&L, M);
    printf("operation - insert \n it is %s \n\n", isValid(f));
    
    printf("operation - traverse all element with bracket which is after insert \n\n");
    traverse(L, BRACKET);

    init(&N);
    f = delete(&L, &N);
    printf("operation - delete \n it is %s \n\n", isValid(f));

    printf("operation - traverse all element with bracket which is after delete \n\n");
    traverse(L, BRACKET);
    
    init(&H);
    f = getHead(L, &H);
    printf("operation - getHead \n it is %s \n\n", isValid(f));

    printf("operation - traverse after getHead \n\n");
    traverse(H, BRACKET);

    init(&T);
    f = getTail(L, &T);
    printf("operation - getTail \n it is %s \n\n", isValid(f));

    printf("operation - traverse after getTail \n\n");
    traverse(T, BRACKET);


    printf("operation - traverse origin GList atom \n\n");
    traverse(L, ELEMENT);

    printf("operation - traverse origin GList with bracket \n\n");
    traverse(L, BRACKET);

    printf("operation - clear \n\n");
    clear(&L);

    printf("operation - traverse after clear \n\n");
    traverse(L, BRACKET);
    
    printf("operation - destroy \n\n");
    destroy(&L);
    
    printf("operation - traverse after destroy \n\n");
    traverse(L, BRACKET);

    return 0;
}