/* 3.6.2 set 指令实验：8 种比较一次看全 */
/* 用法：gcc -Og -S set_instr.c && cat set_instr.s   ← 看汇编里每条 set 对应哪个条件 */
/*       gcc -Og set_instr.c -o set_instr && ./set_instr  ← 看 setl/setb 相反答案 */
#include <stdio.h>

int cmp_gt(long a, long b)  { return a > b;  }   /* setg  */
int cmp_ge(long a, long b)  { return a >= b; }   /* setge（可能带 xorl 花招） */
int cmp_lt(long a, long b)  { return a < b;  }   /* setl  */
int cmp_le(long a, long b)  { return a <= b; }   /* setle */
int cmp_a(unsigned long a, unsigned long b) { return a > b; } /* seta（无符号 above） */
int cmp_b(unsigned long a, unsigned long b) { return a < b; } /* setb（无符号 below） */
int cmp_eq(long a, long b)  { return a == b; }   /* sete  */
int cmp_ne(long a, long b)  { return a != b; }   /* setne */

int main(void) {
    printf("cmp_lt(-1, 1) = %d (有符号: 1)\n", cmp_lt(-1L, 1L));
    printf("cmp_b (-1, 1) = %d (无符号: 0，-1 = 2^64-1 > 1)\n",
           cmp_b((unsigned long)-1L, 1UL));
    printf("cmp_gt(-1, 1) = %d (有符号: 0)\n", cmp_gt(-1L, 1L));
    printf("cmp_eq(3, 3)  = %d (1)\n", cmp_eq(3L, 3L));
    printf("cmp_ne(3, 4)  = %d (1)\n", cmp_ne(3L, 4L));
    return 0;
}
