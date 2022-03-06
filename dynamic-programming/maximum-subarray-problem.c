/*
[Maximum subarray problem](https://en.wikipedia.org/wiki/Maximum_subarray_problem)

In computer science, 
the maximum sum subarray problem is the task of finding a contiguous subarray with the largest sum,
For example, for the array of values [−2, 1, −3, 4, −1, 2, 1, −5, 4], 
the contiguous subarray with the largest sum is [4, −1, 2, 1], with sum 6.

[最大子数列问题](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%AD%90%E6%95%B0%E5%88%97%E9%97%AE%E9%A2%98/22828059)
在计算机科学中，最大子数列问题的目标是在数列的一维方向找到一个连续的子数列，
使该子数列的和最大。例如，对一个数列 {−2, 1, −3, 4, −1, 2, 1, −5, 4}，
其连续子数列中和最大的是 {4, −1, 2, 1}, 其和为6。

《数据结构-入门指南》 - xubeijun/续杯君
[第4节 应用实例：最大子列和问题](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-002/section-004/contiguous-sequence-with-largest-sum)
*/

#include <stdio.h>

int maxSubSum(const int A[],int N)
{
    int ThisSum,MaxSum,i;
    ThisSum = MaxSum = 0;
    for(i =0; i < N; i++)
    {
        ThisSum += A[i];
        if(ThisSum > MaxSum)
            MaxSum = ThisSum;
        else if(ThisSum < 0)
            ThisSum = 0;
    }
    return MaxSum;
}

int main(){
    int sequence[] = {-2,1,-3,4,-1,2,1,-5,4};
    int n;
    n = sizeof(sequence) / sizeof(sequence[0]);
    int maxSum = maxSubSum(sequence,n);
    printf("maxSubSum= %d \n", maxSum);
    return 0;
}