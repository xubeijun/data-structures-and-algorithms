/*
[广义表 - 百度百科](https://baike.baidu.com/item/%E5%B9%BF%E4%B9%89%E8%A1%A8)
[广义表#头尾链表存储表示 - 维基百科](https://zh.wikipedia.org/wiki/%E5%B9%BF%E4%B9%89%E8%A1%A8#%E5%A4%B4%E5%B0%BE%E9%93%BE%E8%A1%A8%E5%AD%98%E5%82%A8%E8%A1%A8%E7%A4%BA)

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
        struct{
            struct GLNode *hp; //表头指针域
            struct GLNode *tp; //表尾指针域
        }ptr; // 表结点的指针域
    };
}GLNode, *GList;

// 初始化广义表
bool init(GList *L);

// 生成广义表初始节点
bool buildNode(GList *L);

// 创建广义表
bool create(GList *L, GListStr str);

// 获取广义字符串的节点类型
void getStrTag(GListStr str, ElemTag *hpTag);

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
void printGList(GList L, bool f);


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
    *L = NULL;

    return true;
}

/**
 * [buildNode 生成广义表初始节点]
 * @param  L [广义表L的二级指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool buildNode(GList *L){
    *L = (GList)malloc(sizeof(GLNode));

    if(!(*L)){
        return false;
    }

    (*L)->tag = LIST;
    (*L)->ptr.hp  = NULL;
    (*L)->ptr.tp  = NULL;

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
    GList M,N;

    // 空表
    if(strcmp(str,emp) == 0){
        init(L);
        return true;
    }

    f = buildNode(L);
    if(!f){
        // 生成初始节点失败
        return false;
    }

    getStrTag(str, &hpTag);
    if(hpTag == ATOM){
        strncpy(&atom,str,1);

        (*L)->tag = ATOM;
        (*L)->atom = atom;
    }else{
        (*L)->tag = LIST;
        M         = *L;
        // 去除括号
        memset(sub, '\0', sizeof(sub));
        strncpy(sub, str+1, strlen(str)-2);

        while(strlen(sub) > 0){
            strsub(sub, &hpSub, &tpSub, &hpTag);

            f = create(&(M->ptr.hp), hpSub);
            if(!f){
                // 表头递归生成失败
                return false;
            }

            if(strlen(sub) == strlen(hpSub)){
                break;
            }

            if(strlen(tpSub) > 0){
                f= buildNode(&N);
                if(!f){
                    // 生成初始节点失败
                    return false;
                }

                M->ptr.tp = N;

                memset(sub, '\0', sizeof(sub));
                strncpy(sub, tpSub, strlen(tpSub));
                memset(hpSub, '\0', sizeof(hpSub));
                memset(tpSub, '\0', sizeof(tpSub));
            }
            M = N;
        }

    }

    return true;
}

/**
 * [getStrTag 获取广义字符串的节点类型]
 * @param str   [获取广义字符串]
 * @param hpTag [节点类型]
 */
void getStrTag(GListStr str, ElemTag *hpTag){
    *hpTag = ATOM;
    GListStr item;

    memset(item,'\0',sizeof(item));

    if(strlen(str) > 0){
        strncpy(item, str, 1);
        if(strcmp(item, "(") == 0){
            *hpTag = LIST;
        }
    }
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
    int len = 0;

    if(L){
        for(len = 0; L; len++){
            L = L->ptr.tp;
        }
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

    // 空表
    if(!L){
        return 1;
    }

    // L为原子
    if(L->tag == ATOM){
        return 0;
    }

    while(L){
        dep = depth(L->ptr.hp);
        if(dep > max){
            max = dep;
        }
        L = L->ptr.tp;
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
    bool f;
    GList M;
    f = buildNode(&M);
    if(!f){
        return false;
    }
    M->ptr.hp = v;
    M->ptr.tp = *L;
    *L = M;

    return true;
}

/**
 * [delete 在广义表L中使用头插法，删除其元素。]
 * @param  L [广义表L的二级指针]
 * @param  x [被删除的结点x的二级指针]
 * @return bool [返回是否完成标识，操作成功则为true，否则为false。]
 */
bool delete(GList *L, GList *x){
    GList M;
    if(!L){
        printf("L does not exist. \n");
        return false;
    }

    M         = (*L);
    *L        = (*L)->ptr.tp;

    M->ptr.tp = NULL;
    copyGList(M, x);

    free(M);
    M = NULL;

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
        printf("L is empty, it has no head. \n");
        return false;
    }

    buildNode(x);

    copyGList(L->ptr.hp, x);

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
        printf("L is empty, it have no tail. \n");
        return false;
    }

    if(L->ptr.tp){
        buildNode(x);
        copyGList(L->ptr.tp, x);
    }else{
        return false;
    }

    return true;
}

/**
 * [copyGList 复制广义表]
 * @param src  [复制来源广义表]
 * @param dest [复制目标广义表]
 */
void copyGList(GList src, GList *dest){
    if(!src){
        init(dest);
    }else{
        if(!(*dest)){
            buildNode(dest);
        }
        (*dest)->tag = src->tag;

        if(src->tag == ATOM){
            (*dest)->atom = src->atom;
        }else{
            copyGList(src->ptr.hp, &((*dest)->ptr.hp));
            copyGList(src->ptr.tp, &((*dest)->ptr.tp));
        }
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
        printGList(L, true);
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
        }else{
            printATOM(L->ptr.hp);
            if(L->ptr.tp){
                printf(",");
            }
            printATOM(L->ptr.tp);
        }
    }
}

/**
 * [printGList 遍历输出带括号的广义表]
 * @param L [广义表L的指针]
 * @param f [bool 是否输出外层括号]
 */
void printGList(GList L, bool f){
    if(!L){
        printf("()");
    }else{
        if(L->tag == ATOM){
            printf("%c", L->atom);
        }else{
            if(f){
                printf("(");
            }

            if(L->ptr.hp){
                bool bracket = (L->ptr.hp->tag == LIST)?true:false;
                printGList(L->ptr.hp, bracket);
            }

            if(L->ptr.tp){
                printf(",");
                printGList(L->ptr.tp, false);
            }

            if(f){
                printf(")");
            }
        }
    }
}

/**
 * [clear 将广义表清空，清除所有元素。]
 * @param L [广义表L的二级指针]
 */
void clear(GList *L){
    destroy(L);
}

/**
 * [destroy 将广义表销毁，释放内存。]
 * @param L [广义表L的二级指针]
 */
void destroy(GList *L){
    GList H,T;
    if(*L){
        if((*L)->tag == LIST){
            H = (*L)->ptr.hp;
            T = (*L)->ptr.tp;

            destroy(&H);
            destroy(&T);
        }

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

    create(&M, s1);
    f = insert(&L, M);
    printf("operation - insert \n it is %s \n\n", isValid(f));

    printf("operation - traverse after insert \n\n");
    traverse(L, BRACKET);

    f = delete(&L, &N);
    printf("operation - delete \n it is %s \n\n", isValid(f));

    printf("operation - traverse delete Node \n\n");
    traverse(N, BRACKET);

    printf("operation - traverse after delete \n\n");
    traverse(L, BRACKET);
    
    f = getHead(L, &H);
    printf("operation - getHead \n it is %s \n\n", isValid(f));

    if(f){
        printf("operation - traverse after getHead \n\n");
        traverse(H, BRACKET);
    }

    f = getTail(L, &T);
    printf("operation - getTail \n it is %s \n\n", isValid(f));

    if(f){
        printf("operation - traverse after getTail \n\n");
        traverse(T, BRACKET);
    }

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