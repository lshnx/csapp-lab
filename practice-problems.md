# CS:APP 练习题精选（含原题 + 答案）

> 每道题一个 `.c` 文件，编译跑过再勾。卡住 15 分钟直接看答案。

---

## 第 2 章

---

### 2.58 · 检测大小端

**题目**：写一个函数 `is_little_endian`，当在小端机器上运行时返回 1，否则返回 0。代码需能移植到任何机器，不论字长。

**答案**：
```c
#include <stdio.h>

int is_little_endian() {
    int x = 1;
    unsigned char *p = (unsigned char *)&x;
    return p[0] == 1;
}

int main() {
    printf("%d\n", is_little_endian());  // x86-64 → 1
    return 0;
}
```

**原理**：`int x = 1` 在小端机器低地址存 `01`、大端存 `00`。把 `&x` 强转成 `unsigned char*` 指向第一个字节，检查它是 0 还是 1。

✅ 已做 — `p2_58.c`

---

### 2.61 · 位级表达式

**题目**：写表达式，使用位运算（`&` `|` `^` `~` `!`），条件成立时返回 1：

A. x 的所有位都是 1  
B. x 的所有位都是 0  
C. x 的最低有效字节的所有位都是 1  
D. x 的最高有效字节的所有位都是 0  

**答案**：
```c
#include <stdio.h>

int main() {
    int x;

    x = 0xFFFFFFFF;   printf("A:%d B:%d C:%d D:%d\n",
        !~x,              // A: 所有位都是 1  ⇔ ~x == 0  ⇔ !~x == 1
        !x,               // B: 所有位都是 0  ⇔ x == 0   ⇔ !x == 1
        !~(x & 0xFF),     // C: 低 8 位全为 1 ⇔ (x&0xFF) == 0xFF ⇔ ~(x&0xFF) == 0
        !((x >> 24) & 0xFF)  // D: 高 8 位全为 0 ⇔ (x>>24)&0xFF == 0
    );

    x = 0x00000000;   printf("A:%d B:%d C:%d D:%d\n",
        !~x, !x, !~(x & 0xFF), !((x >> 24) & 0xFF));

    x = 0x00FF0000;   printf("A:%d B:%d C:%d D:%d\n",
        !~x, !x, !~(x & 0xFF), !((x >> 24) & 0xFF));

    return 0;
}
```

**逐行解释**：
- `!~x`：`~` 按位取反。若 x 全 1，`~x` = 0，`!0` = 1。否则 `~x` ≠ 0，`!非零` = 0。
- `!x`：x 为 0 时 `!0` = 1，否则 = 0。
- `!~(x & 0xFF)`：`x & 0xFF` 提出低 8 位。低 8 位全 1（= 0xFF）时 `~0xFF = 0`，`!0 = 1`。
- `!((x >> 24) & 0xFF)`：`x >> 24` 把最高字节挪到最低，`& 0xFF` 取那 8 位，若全 0 则 `!0 = 1`。

✅ 已做 — `p2_61.c`

---

### 2.63 · 用逻辑右移实现算术右移

**题目**：在允许使用逻辑右移但不保证算术右移的机器上，实现 `sra`——算术右移 k 位。再用 `sra` 实现 `srl`——逻辑右移。

**答案**：
```c
#include <stdio.h>

/* 算术右移：高位补符号位 */
unsigned sra(int x, int k) {
    int xsrl = (unsigned) x >> k;  // 逻辑右移
    int w = sizeof(int) << 3;       // w = 32
    // 若 x<0 且 k>0，需把高位补 1
    int mask = (int) -1 << (w - k); // 高 k 位为 1，低(w-k)位为 0
    // 若 x>=0，mask 应该为 0（不补任何 1）
    int m = 1 << (w - 1);           // 符号位掩码
    mask &= !(x & m) - 1;           // x>=0 时 mask 清零的魔法
    return xsrl | mask;
}

/* 逻辑右移：高位补 0 */
unsigned srl(unsigned x, int k) {
    unsigned xsra = (int) x >> k;  // 算术右移
    int w = sizeof(int) << 3;
    int mask = (int) -1 << (w - k); // 高 k 位掩码
    mask &= 0;                       // TODO: 留给你完成
    return xsra & ~mask;            // 把符号位延伸的部分清零
}

int main() {
    printf("sra(-128, 2) = %d  (expect -32)\n", sra(-128, 2));
    return 0;
}
```

⬜ 待做 — `p2_63.c`

---

### 2.64 · 奇数个 1 检测

**题目**：写函数 `odd_ones(x)`，当 x 的二进制表示包含奇数个 1 时返回 1，否则返回 0。只允许用 `! ~ & ^ | + << >>`，最多 12 个运算符。

**答案**：
```c
#include <stdio.h>

int odd_ones(unsigned x) {
    x ^= x >> 16;   // 高 16 位 XOR 低 16 位
    x ^= x >> 8;    // 折叠到 8 位
    x ^= x >> 4;    // 折叠到 4 位
    x ^= x >> 2;    // 折叠到 2 位
    x ^= x >> 1;    // 折叠到 1 位
    return x & 1;   // 最低位 = 1 的个数的奇偶性
}

int main() {
    printf("odd_ones(0x1)  = %d (expect 1)\n", odd_ones(0x1));
    printf("odd_ones(0x3)  = %d (expect 0)\n", odd_ones(0x3));
    printf("odd_ones(0x7)  = %d (expect 1)\n", odd_ones(0x7));
    printf("odd_ones(0xF)  = %d (expect 0)\n", odd_ones(0xF));
    printf("odd_ones(0xA)  = %d (expect 0)\n", odd_ones(0xA));
    return 0;
}
```

**原理**：XOR = 不进位加法。每次折叠把所有位的 1 的奇偶性压缩到更低位的范围。最终最低位 = 奇数个 1 时为 1。

⬜ 待做 — `p2_64.c`

---

### 2.68 · 位掩码生成

**题目**：写函数 `lower_one_mask(n)`，返回一个 int，其低 n 位为 1，高位为 0。1 ≤ n ≤ w。最多 10 个运算符。

**答案**：
```c
#include <stdio.h>

int lower_one_mask(int n) {
    int w = sizeof(int) << 3;    // w = 32
    return (unsigned) -1 >> (w - n);
}

int main() {
    printf("n=1:  0x%08X (expect 0x00000001)\n", lower_one_mask(1));
    printf("n=8:  0x%08X (expect 0x000000FF)\n", lower_one_mask(8));
    printf("n=16: 0x%08X (expect 0x0000FFFF)\n", lower_one_mask(16));
    printf("n=32: 0x%08X (expect 0xFFFFFFFF)\n", lower_one_mask(32));
    return 0;
}
```

**原理**：`(unsigned)-1` = 全 1（0xFFFFFFFF）。逻辑右移 `w-n` 位 → 低 n 位为 1，高位为 0。

⬜ 待做 — `p2_68.c`

---

### 2.71 · 截断 + 符号扩展

**题目**：你被分配维护一个字的压缩程序。任务：写函数 `xbyte(packed_word, bytenum)`，从 `packed_word`（无符号 int）中提取并符号扩展指定编号的字节。字节编号 0（最低位）~ 3（最高位）。

**答案**：
```c
#include <stdio.h>

typedef unsigned packed_t;

/* 从 32 位字中提取第 bytenum 个字节并符号扩展为 int */
int xbyte(packed_t word, int bytenum) {
    // 把目标字节左移到最高字节位置，强转 int 后算术右移回到最低
    int left_shift = (3 - bytenum) << 3;   // (3-b)*8
    return (int) (word << left_shift) >> 24;
}

int main() {
    packed_t w;

    w = 0x00123480;   // 字节 1 = 0x34 (正)
    printf("xbyte(w, 1) = %d (expect 52)\n", xbyte(w, 1));

    w = 0x0012FF00;   // 字节 1 = 0xFF (-1)
    printf("xbyte(w, 1) = %d (expect -1)\n", xbyte(w, 1));

    w = 0xFF123480;   // 字节 3 = 0xFF (-1)
    printf("xbyte(w, 3) = %d (expect -1)\n", xbyte(w, 3));

    return 0;
}
```

**原理**：
1. `word << left_shift`：把目标字节推到最高位
2. `(int)`：强转有符号 int
3. `>> 24`：算术右移 → 符号位扩展一直补到低位

⬜ 待做 — `p2_71.c`

---

### 2.75 · 无符号 × 有符号的高 64 位

**题目**：已知库函数 `unsigned unsigned_high_prod(unsigned x, unsigned y)` 返回 `x*y` 的高 32 位。用这个函数实现 `signed_high_prod(int x, int y)`——返回两个补码数乘积的高 32 位。提示：利用 `x' = x + x_{w-1}·2^w`（即 T2U 和 U2T 的关系）。

**答案**：
```c
#include <stdio.h>

unsigned unsigned_high_prod(unsigned x, unsigned y); // 已有

int signed_high_prod(int x, int y) {
    int w = sizeof(int) << 3;
    // 把补码转无符号：x' = x + x_{w-1}·2^w
    // x'·y' = x·y + x_{w-1}·y·2^w + y_{w-1}·x·2^w + x_{w-1}·y_{w-1}·2^{2w}
    // 高 32 位 = unsigned_high_prod(x', y') - x_{w-1}·y - y_{w-1}·x
    int x_sign = (unsigned) x >> (w - 1);  // 0 or 1
    int y_sign = (unsigned) y >> (w - 1);
    unsigned ux = (unsigned) x;
    unsigned uy = (unsigned) y;

    unsigned hi = unsigned_high_prod(ux, uy);
    return (int) (hi - x_sign * uy - y_sign * ux);
}

/* 简单测试版 unsigned_high_prod（64 位模拟） */
unsigned unsigned_high_prod(unsigned x, unsigned y) {
    unsigned long long prod = (unsigned long long) x * y;
    return (unsigned)(prod >> 32);
}

int main() {
    printf("signed_high_prod(100000, 200000) = %d\n", signed_high_prod(100000, 200000));
    printf("signed_high_prod(-100000, 200000) = %d\n", signed_high_prod(-100000, 200000));
    return 0;
}
```

⬜ 待做 — `p2_75.c`

---

### 2.77 · 乘法用移位替代

**题目**：只用移位、加法和减法实现 `x * K`，其中 K 取值 17, -7, 60, -112。先写出 K 的二进制分解。

**答案**：
```c
#include <stdio.h>

// K = 17  = 16 + 1 = 2^4 + 2^0
int mul17(int x) { return (x << 4) + x; }

// K = -7  = -(8 - 1) = -(2^3 - 2^0)
int mul_neg7(int x) { return x - (x << 3); }

// K = 60  = 64 - 4 = 2^6 - 2^2
int mul60(int x) { return (x << 6) - (x << 2); }

// K = -112 = -(128 - 16) = -(2^7 - 2^4)
int mul_neg112(int x) { return (x << 4) - (x << 7); }

int main() {
    int x = 5;
    printf("5*17=%d  %d\n",      x*17,      mul17(x));
    printf("5*(-7)=%d %d\n",     x*(-7),    mul_neg7(x));
    printf("5*60=%d  %d\n",      x*60,      mul60(x));
    printf("5*(-112)=%d %d\n",   x*(-112),  mul_neg112(x));
    return 0;
}
```

**分解方法**：把 K 写成 `±(2^a ± 2^b ± ...)`。编译器自动帮你做这个优化——你写 `x*17` 就行，但你读汇编时要能认出 `(x<<4)+x`。

⬜ 待做 — `p2_77.c`

---

### 2.78 · 除以 2^k（向零取整）

**题目**：写函数 `divide_power2(x, k)`，计算 `x / 2^k`，向零取整（和 C 一样）。`0 ≤ k ≤ w-1`。

**答案**：
```c
#include <stdio.h>

int divide_power2(int x, int k) {
    // 负数需要加偏置 (1<<k)-1
    int is_neg = (unsigned) x >> ((sizeof(int) << 3) - 1);  // 0 or -1
    int bias = (1 << k) - 1;
    // is_neg 为 -1（全 1）时 bias 生效，为 0 时 bias 被 mask 清掉
    return (x + (is_neg & bias)) >> k;
}

int main() {
    printf("divide_power2(15, 2) = %d (expect 3)\n", divide_power2(15, 2));
    printf("divide_power2(-15, 2) = %d (expect -3)\n", divide_power2(-15, 2));
    printf("divide_power2(8, 3) = %d (expect 1)\n", divide_power2(8, 3));
    printf("divide_power2(-8, 3) = %d (expect -1)\n", divide_power2(-8, 3));
    return 0;
}
```

**原理**：补码除法直接算术右移 → 向负无穷取整。C 要求向零取整。负数时加偏置 `2^k-1` 补偿。

⬜ 待做 — `p2_78.c`

---

### 2.84 · IEEE 754 三类值比较

**题目**：填写浮点数比较 `<=` `<` `==` `!=` 的真值表。假设 `x` 和 `y` 是 float，考虑：+0、-0、+∞、-∞、NaN、正常正数、正常负数。

**答案**：

| 比较 | +0 vs -0 | +∞ vs +∞ | NaN vs NaN | NaN vs 任意值 | +∞ vs 3.0 |
|------|----------|----------|------------|--------------|-----------|
| `x == y` | 1 | 1 | **0** | **0** | 0 |
| `x != y` | 0 | 0 | **1** | **1** | 1 |
| `x < y` | 0 | 0 | 0 | 0 | 0 |
| `x <= y` | 1 | 1 | 0 | 0 | 0 |

**关键结论**：
- **`+0 == -0`** → true（IEEE 754 视 ±0 为相等）
- **`NaN == NaN`** → **false**（NaN 是唯一不满足 `x == x` 的值）
- 任何和 NaN 的比较（`<` `<=` `>` `>=` `==` `!=`）→ 除了 `!=` 外全部返回 false
- `+∞ == +∞` → true

```c
#include <stdio.h>
#include <math.h>

int main() {
    float pos_zero = 0.0f;
    float neg_zero = -0.0f;
    float inf = 1.0f / 0.0f;
    float nan = 0.0f / 0.0f;

    printf("+0 == -0: %d\n", pos_zero == neg_zero);     // 1
    printf("+inf == +inf: %d\n", inf == inf);             // 1
    printf("NaN == NaN: %d\n", nan == nan);               // 0
    printf("NaN != NaN: %d\n", nan != nan);               // 1
    printf("isnan(NaN): %d\n", isnan(nan));               // 1
    return 0;
}
```

⬜ 待做 — `p2_84.c`

---

### 2.87 · 8 位迷你浮点

**题目**：用 1 符号 + 4 指数（bias=7）+ 3 尾数的迷你浮点格式，写出下列值的位表示：

**答案**：

| 值 | 二进制 | 十六进制 | 说明 |
|----|--------|----------|------|
| 0 | `0 0000 000` | `0x00` | 非规格化，尾数全 0 |
| -0 | `1 0000 000` | `0x80` | 符号位 = 1 |
| 最小非规格化正数 | `0 0000 001` | `0x01` | M=0.001, E=-6 → 1/512 |
| 最大非规格化数 | `0 0000 111` | `0x07` | M=0.111, E=-6 → 7/512 |
| 最小规格化数 | `0 0001 000` | `0x08` | M=1.000, E=-6 → 1/64 |
| 1.0 | `0 0111 000` | `0x38` | M=1.000, E=0 |
| 最大规格化数 | `0 1110 111` | `0x77` | M=1.111, E=7 → 240 |
| +∞ | `0 1111 000` | `0x78` | exp 全 1, frac 全 0 |
| NaN | `0 1111 001` | `0x79` | exp 全 1, frac ≠ 0 |
| -1.5 | `1 0111 100` | `0xBC` | -1.5 = -1.1×2⁰, M=1.100, frac=100 |

```c
// 注意：C 不直接支持 8 位浮点，下面用 float 近似演示
#include <stdio.h>

int main() {
    printf("1.0 在 8-bit 迷你浮点中 = 0x38\n");
    printf("-1.5 在 8-bit 迷你浮点中 = 0xBC\n");
    printf("最关键：非规格化→规格化是平滑过渡的\n");
    return 0;
}
```

⬜ 待做 — `p2_87.c`

---

### 2.92 · 浮点取反

**题目**：写函数 `float_negate(float f)`，返回 `-f`。如果 `f` 是 NaN，直接返回 `f`。

**答案**：
```c
#include <stdio.h>

float float_negate(float f) {
    unsigned u = *(unsigned*)&f;
    unsigned sign = u >> 31;
    unsigned exp = (u >> 23) & 0xFF;
    unsigned frac = u & 0x7FFFFF;

    if (exp == 0xFF && frac != 0)  // NaN → 原样返回
        return f;

    // 翻转符号位
    u ^= (1U << 31);
    return *(float*)&u;
}

int main() {
    float a = 3.14f;
    float b = 0.0f / 0.0f;  // NaN
    printf("neg(%.2f) = %.2f\n", a, float_negate(a));
    printf("neg(NaN) is NaN: %d\n", b != b);  // NaN ≠ NaN
    printf("neg(NaN) returned same: %d\n", float_negate(b) != float_negate(b));
    return 0;
}
```

**原理**：浮点取反只需翻转符号位（bit 31）。NaN 检测：exp 全 1 且 frac ≠ 0。

⬜ 待做 — `p2_92.c`

---

### 2.93 · 浮点绝对值

**题目**：写函数 `float_absval(float f)`，返回 `|f|`。若 NaN，返回原值。

**答案**：
```c
#include <stdio.h>

float float_absval(float f) {
    unsigned u = *(unsigned*)&f;
    unsigned exp = (u >> 23) & 0xFF;
    unsigned frac = u & 0x7FFFFF;

    if (exp == 0xFF && frac != 0)  // NaN
        return f;

    u &= ~(1U << 31);  // 清符号位
    return *(float*)&u;
}

int main() {
    float a = -3.14f;
    float b = 5.0f;
    float nan = 0.0f / 0.0f;
    printf("abs(%.2f) = %.2f\n", a, float_absval(a));
    printf("abs(%.2f) = %.2f\n", b, float_absval(b));
    printf("abs(NaN) is NaN: %d\n", float_absval(nan) != float_absval(nan));
    return 0;
}
```

⬜ 待做 — `p2_93.c`

---

## 第 3 章

---

### 3.1 · 操作数类型识别

**题目**：下列每个操作数是立即数、寄存器还是内存引用？

| 操作数 | 类型 | 如果是内存引用，地址表达式是什么？ |
|--------|------|----------------------------------|
| `$0x108` | 立即数 | — |
| `(%rax)` | 内存引用 | `R[%rax]` |
| `-12(%rbp)` | 内存引用 | `R[%rbp] - 12` |
| `%eax` | 寄存器 | — |
| `(%rax, %rcx, 4)` | 内存引用 | `R[%rax] + R[%rcx]×4` |
| `$0xFF` | 立即数 | — |
| `9(%rdx, %rcx)` | 内存引用 | `R[%rdx] + R[%rcx] + 9` |

⬜ 待做 — `p3_01.c`

---

### 3.2 · mov 指令和 C 赋值对应

**题目**：写出完成下列 C 赋值语句的 mov 指令：

| C 语句 | 汇编 | 说明 |
|--------|------|------|
| `a = b;` | `movl %edx, %eax` | a 在 %eax, b 在 %edx |
| `*p = v;` | `movq %rax, (%rcx)` | p 在 %rcx, v 在 %rax |
| `v = *p;` | `movq (%rcx), %rax` | |
| `c = (char) x;` | `movb %al, (%rdi)` | c 是 char*，只传低字节 |

⬜ 待做 — `p3_02.c`

---

### 3.3 · movzbl vs movsbl 效果

**题目**：写 C 程序演示 `unsigned char` 转 `int`（零扩展）和 `char` 转 `int`（符号扩展）的不同结果。然后 `gcc -Og -S` 看汇编，找到 `movzbl` 和 `movsbl`。

**答案**：
```c
#include <stdio.h>

int uchar_to_int(unsigned char c) { return c; }  // movzbl
int schar_to_int(signed char c)   { return c; }  // movsbl

int main() {
    printf("unsigned char 255 → int: %d\n", uchar_to_int(255));   // 255
    printf("signed char -1   → int: %d\n", schar_to_int(-1));     // -1
    return 0;
}
```

编译看汇编：
```bash
gcc -Og -S p3_03.c && grep -E 'movzbl|movsbl' p3_03.s
```

⬜ 待做 — `p3_03.c`

---

### 3.5 · 反汇编 mov 指令

**题目**：写出下列机器码对应的汇编指令（x86-64，小端）：

| 机器码 | 反汇编 | 说明 |
|--------|--------|------|
| `48 89 C3` | `movq %rax, %rbx` | 48=REX.W(64bit), 89=mov r/m, C3=ModRM |
| `48 C7 C3 01 00 00 00` | `movq $1, %rbx` | C7=mov imm→r/m |
| `8B 45 FC` | `movl -4(%rbp), %eax` | 8B=mov r/m→r, 45=ModRM（-4(%rbp)）, FC=-4 |

⬜ 待做 — `p3_05.c`

---

### 3.6 · LEA 计算

**题目**：下列 LEA 指令的目的寄存器值是多少？假设 `%rax = x`，`%rcx = y`：

| LEA 指令 | 结果 | 说明 |
|----------|------|------|
| `leaq 9(%rax), %rdx` | x+9 | 简单加法 |
| `leaq (%rax, %rcx), %rdx` | x+y | 两个寄存器相加 |
| `leaq (%rax, %rcx, 4), %rdx` | x+4y | 比例变址 |
| `leaq 7(%rax, %rax, 8), %rdx` | 7+9x | 7 + x + x×8 |

**关键**：LEA 不访问内存——它只是"计算那个地址"，然后把地址存进寄存器。相当于一条指令做 `a×k + b`。

⬜ 待做 — `p3_06.c`

---

### 3.7 · 算术指令效果

**题目**：写出下列每条指令执行后 `%rax` 的值（假设初始 `%rax = 10`，`%rcx = 3`）：

| 指令 | 结果 | 说明 |
|------|------|------|
| `addq %rcx, %rax` | 13 | 10+3 |
| `subq %rcx, %rax` | 7 | 10-3 |
| `imulq %rcx, %rax` | 30 | 10×3 |
| `salq $2, %rax` | 40 | 10×4（左移 2 位） |
| `sarq $1, %rax` | 5 | 10/2（算术右移） |

⬜ 待做 — `p3_07.c`

---

### 3.8 · 移位量

**题目**：x86-64 移位指令的移位量可以写在哪里？分两种情况回答。

**答案**：
- 移位量 = 1 → 直接写在指令里：`salq $1, %rax`
- 移位量 > 1 → 放在 `%cl` 寄存器里：`movb $4, %cl; salq %cl, %rax`

移位量还可以是立即数（1 字节），但不能是任意内存或寄存器——**只能是立即数或 `%cl`**。

⬜ 待做 — `p3_08.c`

---

### 3.13 · 条件码设置

**题目**：下列指令执行后 ZF、SF、OF 的值：

| 指令 | ZF | SF | OF | 说明 |
|------|-----|-----|-----|------|
| `cmpq $5, %rax`（rax=5） | 1 | 0 | 0 | 相等→ZF=1 |
| `testq %rax, %rax`（rax=0） | 1 | 0 | 0 | 0→ZF=1 |
| `cmpq $5, %rax`（rax=3） | 0 | 1 | 0 | 3-5=-2<0→SF=1 |
| `addq $1, %rax`（rax=MAX） | 0 | 1 | 1 | 溢出变 MIN |

⬜ 待做 — `p3_13.c`

---

### 3.15 · 跳转指令对应 goto

**题目**：把下列 `if` 语句翻译成 `goto` 版本，再翻译成汇编：

```c
if (x > y)
    a = 1;
else
    b = 2;
```

**goto 版本**：
```c
if (x <= y) goto else_label;
a = 1;
goto done;
else_label:
b = 2;
done:
```

**汇编**（x→%rdi, y→%rsi, a→%eax, b→%ebx）：
```asm
cmpq %rsi, %rdi
jle  .L2        # x <= y → else
movl $1, %eax   # a = 1
jmp  .L3
.L2:
movl $2, %ebx   # b = 2
.L3:
```

⬜ 待做 — `p3_15.c`

---

### 进度追踪

| 章 | 完成 | 总计 |
|----|------|------|
| 第 2 章 | ✅ 2.58 ✅ 2.61 | 13 |
| 第 3 章 | 0 | 20 |
