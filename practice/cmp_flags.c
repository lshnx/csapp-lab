/* 条件码实验：编译成汇编，看 cmp 怎么"记账" */
int cmp_gt(long a, long b) {
    return a > b;       /* 有符号大于：看 SF 和 OF 的组合 */
}

int cmp_eq(long a, long b) {
    return a == b;      /* 相等：只看 ZF */
}

int cmp_ltu(unsigned long a, unsigned long b) {
    return a < b;       /* 无符号小于：看的是 CF */
}
