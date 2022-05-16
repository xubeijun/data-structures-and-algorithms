/**
 *
 * [Binary search algorithm - wiki](https://en.wikipedia.org/wiki/Binary_search_algorithm)
 * 
 * [二分查找 - 百度百科](https://baike.baidu.com/item/%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE/10628618)
 * 
 * 二分查找也称折半查找（Binary Search），它是一种效率较高的查找方法。但是，折半查找要求线性表必须采用顺序存储结构，而且表中元素按关键字有序排列。
 *
 * 2组测试用例
 *
5
12 31 55 89 101
31

3
26 78 233
31
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch( List L, ElementType X );

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    // printf( "Enter a number of search: ");
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

/* 你的代码将被嵌在这里 */
List ReadInput(){
    int k,i,x;
    // printf( "Enter a count of array: ");
    x = scanf("%d",&k);

    if(x!=1){
        printf("stdin format is error \n");
        exit(-1);
    }

    List L;

    L->Last = k;

    if(!L->Last){
        printf("init list is error \n");
        exit(-1);
        // return false;
    }

    // printf( "Enter an array, split by spaces: ");
    for (i = 1; i <= k; i++){
        x = scanf("%d",&L->Data[i]);

        if(x!=1){
            printf("stdin format is error \n");
            exit(-1);
        }
    }

    return L;
}

Position BinarySearch( List L, ElementType X ){
    int low = 1;
    int high = L->Last;
    int pos = NotFound;

    while(low <= high){
        int mid = low + (high - low) / 2;
        if(L->Data[mid] == X){
            pos = mid;
            break;
        }else if(L->Data[mid] < X){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    // printf("pos is %d \n",pos);
    return pos;
}