/* 3.6.5 实验：if/else 怎么翻译成 goto + 跳转 */
/* 用法：gcc -Og -c absdiff.c -o absdiff.o && objdump -d absdiff.o */
/* 观察点：①条件取反（C 里 x>y，汇编测 x<=y）②then 块末尾直接 ret（合并公共尾部） */

long absdiff(long x, long y) {
    long result;
    if (x > y)
        result = x - y;
    else
        result = y - x;
    return result;
}

long clamp_zero(long x) {
    if (x < 0) x = 0;   /* 无 else 的 if */
    return x;
}
