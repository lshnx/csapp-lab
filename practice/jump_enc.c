/* 3.6.4 跳转编码实验：看 eb/7e 这种机器码怎么算出跳转目标 */
/* 用法：gcc -Og -c jump_enc.c -o jump_enc.o && objdump -d jump_enc.o */

int abs_value(int x) {
    if (x < 0)
        x = -x;
    return x;
}

int sum_to(int n) {
    int s = 0;
    for (int i = 1; i <= n; i++)
        s += i;
    return s;
}
