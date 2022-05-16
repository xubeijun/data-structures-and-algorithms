/*

Given a sequence of K integers {N_1, N_2, ..., N_K}. A continuous subsequence is defined to be {N_i, N_i+1, ..., N_j} where 1≤i≤j≤K. The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.

Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.

Input Specification:
Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer K (≤10000). The second line contains K numbers, separated by a space.

Output Specification:
For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices i and j (as shown by the sample case). If all the K numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.

Sample Input:
10
-10 1 2 3 4 -5 -23 3 7 -21
Sample Output:
10 1 4

---

给定K个整数组成的序列{N_1, N_2, ..., N_K}，“连续子列”被定义为{N_i, N_i+1, ..., N_j}，其中 1≤i≤j≤K。“最大子列和”则被定义为所有连续子列元素的和中最大者。例如给定序列{ -2, 11, -4, 13, -5, -2 }，其连续子列{ 11, -4, 13 }有最大的和20。现要求你编写程序，计算给定整数序列的最大子列和。

输入格式:
输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。

输出格式:
对于每个测试用例，在一行中输出最大和，以及最大子序列的第一个和最后一个数字。数字必须用一个空格分隔，但行尾不得有多余的空格。如果最大子序列不是唯一的，请输出索引为 i 和 j 的子序列（如示例案例所示）。如果所有 K 数均为负数，则其最大和定义为 0，并且您应该输出整个序列的第一个和最后一个数字。

输入样例:
6
-10 1 2 3 4 -5 -23 3 7 -21

输出样例:
10 1 4

01-复杂度2 Maximum Subsequence Sum

《数据结构-入门指南》 - xubeijun/续杯君
[第1节 线性表是什么 - 线性表的顺序存储结构](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-003/section-001/what-is-linear-list)

5组测试用例
1
5

5
-1 -2 -3 0 -5

5
-1 -2 -3 -4 -5

10
-10 1 2 3 4 -5 -23 3 7 -21

15
1 2 3 4 -5 -23 3 7 5 -20 0 4 6 7 -10
*/

#include <stdio.h>
#include <stdlib.h>

/**
 * 最大子序列的结构体
 * maxSum 最大子序列的和
 * firstNum 最大子序列的首位索引
 * lastNum 最大子序列的末位索引
 */
typedef struct maxSub{
    int maxSum;
    int firstNum;
    int lastNum;
} ms;

/**
 * [maxSubSum description]
 * @param ptr  [最大子序列的结构体指针]
 * @param arr  [线性数组]
 * @param size [线性数组元素个数]
 */
void maxSubSum(struct maxSub *ptr, int arr[], int size){
    int i;
    int curSum=0,firstIdx=0,count=0;
    ptr->maxSum=0;

    for (i = 0; i < size; i++){
        curSum += arr[i];
        if(curSum > ptr->maxSum){
            ptr->maxSum   = curSum;
            ptr->firstNum = arr[firstIdx];
            ptr->lastNum  = arr[i];
        }else if(curSum < 0){
            curSum = 0;
            if(i < size-1){
                firstIdx = i+1;
            }
        }

        if(arr[i] >= 0){
            count++;
        }
    }

    if(count == 0){
        ptr->firstNum = arr[0];
        ptr->lastNum  = arr[size-1];
    }

    if(ptr->maxSum == 0 && count > 0){
        ptr->firstNum = 0;
        ptr->lastNum  = 0;
    }
}

int main(){
    int k,i,x;

    // printf( "Enter a count of array: ");
    x = scanf("%d",&k);

    if(x!=1){
        printf("stdin format is error \n");
        exit(-1);
    }

    int list[k];

    // printf( "Enter an array, split by spaces: ");
    for (i = 0; i < k; i++){
        x = scanf("%d",&list[i]);

        if(x!=1){
            printf("stdin format is error \n");
            exit(-1);
        }
    }

    ms m;

    maxSubSum(&m, list, k);

    printf("%d %d %d", m.maxSum, m.firstNum, m.lastNum);
    return 0;
}