/*


《数据结构-入门指南》 - xubeijun/续杯君
[第8节 应用实例：树的同构](https://www.xubeijun.com/column/data-structures/data-structures-start-guide/chapter-005/section-008/isomorphism-of-tree)

03-树1 树的同构

给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。

现给定两棵树，请你判断它们是否是同构的。

输入格式:

输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N (≤10)，即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“-”。给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。

输出格式:

如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1（对应图1）：

8
A 1 2
B 3 4
C 5 -
D - -
E 6 -
G 7 -
F - -
H - -
8
G - 4
B 7 6
F - -
A 5 1
H - -
C 0 -
D - -
E 2 -

输出样例1:
Yes

输入样例2（对应图2）：

8
B 5 7
F - -
A 0 3
C 6 -
H - -
D - -
G 4 -
E 1 -
8
D 6 -
B 5 -
E - -
H - -
C 0 2
G - 3
F - -
A 1 4

输出样例2:

No
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MaxSize 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode{
    ElementType data;
    Tree left;
    Tree right;
} T1[MaxSize], T2[MaxSize];

Tree buildTree(struct TreeNode T[]){
    int x, N, root = Null, checkRoot[MaxSize] = {0};
    char cLeft, cRight;

    x = scanf("%d", &N);
    if(x != 1){
        printf("input is fail \n");
        exit(-1);
    }

    for(int i = 0; i < N; i++){
        x = scanf("\n%c %c %c", &T[i].data, &cLeft, &cRight);
        if(x != 3){
            printf("input is fail \n");
            exit(-1);
        }

        if(cLeft != '-'){
            T[i].left = cLeft-'0';
            checkRoot[T[i].left] = 1;
        }else{
            T[i].left = Null;
        }

        if(cRight != '-'){
            T[i].right = cRight-'0';
            checkRoot[T[i].right] = 1;
        }else{
            T[i].right = Null;
        }
    }

    for (int i = 0; i < N; ++i){
        if(checkRoot[i] == 0){
            root = i;
            break;
        }
    }

    return root;
}

bool isomorphism(Tree R1, Tree R2){
    if(R1 == Null && R2 == Null){
        // 两棵树都为空
        return true;
    }else if((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null)){
        // 其中一棵树为空
        return false;
    }else if(T1[R1].data != T2[R2].data){
        // 两棵树的根节点数据不一致
        return false;
    }else if(T1[R1].left == Null && T2[R2].left == Null){
        // 两棵树的左子树为空
        return isomorphism(T1[R1].right, T2[R2].right);
    }else if((T1[R1].left != Null && T2[R2].left != Null) && (T1[T1[R1].left].data == T2[T2[R2].left].data)){
        // 两棵树的左子树不为空，且不需要交换左右子树
        return (isomorphism(T1[R1].left, T2[R2].left) && isomorphism(T1[R1].right, T2[R2].right));
    }else{
        // 需要交换左右子树
        return (isomorphism(T1[R1].left, T2[R2].right) && isomorphism(T1[R1].right, T2[R2].left));
    }
}

int main(){
    Tree R1, R2;

    // printf("input - 请输入T1和T2的数据样本 \n");
    R1 = buildTree(T1);
    R2 = buildTree(T2);

    // printf("result - 同构结果 \n");
    if(isomorphism(R1, R2)){
        printf("Yes\n");
    }else{
        printf("No\n");
    }

    return 0;
}