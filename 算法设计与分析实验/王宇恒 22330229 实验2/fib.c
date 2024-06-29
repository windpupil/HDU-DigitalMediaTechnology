#include<stdio.h>

int fib(int n) {
    if (n < 2) {
        return n;
    }
    int p = 0, q = 0, r = 1;
    for (int i = 2; i <= n; ++i) {
        p = q;
        q = r;
        r = p + q;
    }
    return r;
}

int main() {
    int n;
    printf("请输入一个整数：");
    scanf("%d", &n);
    printf("斐波那契数列的第%d项为：%d\n", n, fib(n));
    return 0;
}