# 大二上规划 · 三模块项目（2026/9 — 2027/1）

> 一个仓库，三个产品：自研 allocator → mini-Tensor 库 → GEMM 优化。
> 简历一句话：「C 实现 CPU 张量库，存储后端为自研 allocator（free list + 边界合并 + 分箱优化，对比 ptmalloc 差距分析），GEMM 分块/SIMD/多线程优化」。
>
> ⚠️ 目标不是"达到 ptmalloc 水平"（那是 30 年工业工程，不可能也不必要）——目标是**读懂 ptmalloc 核心设计、移植 1 个机制（分箱）、能讲清差距**。

---

## 最终产品形态

```
csapp-lab/
├── malloc/                    ← 产品 1：my_malloc.h/.c + test_random + ptmalloc-对比.md
├── tensor/                    ← 产品 2：tensor.h/.c + ops + demo.c（两层 MLP 前向）
│   ├── gemm_naive.c           ← 产品 3：4 个 GEMM 版本
│   ├── gemm_blocked.c
│   ├── gemm_simd.c
│   ├── gemm_parallel.c
│   └── bench_gemm.c
└── README.md                  ← 首页：架构图 + 性能表
```

关系：my_malloc 分配 Tensor 的 data → 张量库调用 gemm。

---

## 验收标准（三个数字，缺一个就不算完成）

1. **GEMM 提速表**：naive → +分块 → +SIMD → +多线程，每一级提速都有 benchmark 数字和"为什么快"的解释
2. **allocator 测试**：随机 10000 次 alloc/free/realloc 零错误，valgrind/ASan 零泄漏
3. **ptmalloc 对比文档**：能讲清我的合并策略 vs glibc 的 bins 设计，至少 3 个具体差异

---

## 时间表（16 周，周粒度）

| 周 | 日期 | 内容 |
|----|------|------|
| W1 | 9/1-9/6 | **复习收尾**：Ch3 笔记 3.1-3.5.5 自检题全过 + 重做 2.63 / 2.78 |
| W2 | 9/7-9/13 | §3.6.1-3.6.6 条件码 + cmp/test + 跳转指令 |
| W3 | 9/14-9/20 | §3.6.7-3.6.8 循环翻译 + §3.7 过程调用（栈帧、call/ret） |
| W4 | 9/21-9/27 | §3.8 数组 + §3.9 struct/union |
| W5 | 9/28-10/4 | §3.10 缓冲区溢出 + **Ch3 总复习**（国庆前半段） |
| W6 | 10/5-10/11 | malloc v0：块结构 + sbrk + first-fit（穿插读 Ch9.1-9.2 heap 概念） |
| W7 | 10/12-10/18 | malloc v1：块切分 + free + 右侧合并 |
| W8 | 10/19-10/25 | malloc v2：边界标记 + 左右合并 + realloc |
| W9 | 10/26-11/1 | malloc 测试周：随机 10000 次 + valgrind + **读 ptmalloc 写对比文档** |
| W10 | 11/2-11/8 | Tensor v0：结构体（data 用 my_malloc）+ create/free/打印（穿插 Ch6.1-6.3 缓存） |
| W11 | 11/9-11/15 | Tensor v1：逐元素算子 + broadcast + view/reshape |
| W12 | 11/16-11/22 | Tensor v2：朴素 matmul + 正确性测试（穿插 Ch5 快速过） |
| W13 | 11/23-11/29 | GEMM 分块 + SIMD（AVX2） |
| W14 | 11/30-12/6 | GEMM 多线程（OpenMP）+ benchmark 四版本对比 |
| W15 | 12/7-12/13 | MLP demo 跑通 + README/架构图/性能表 |
| W16 | 12/14-12/20 | 简历草稿 + 收尾整理；**之后期末周冻结，课程优先** |

**里程碑检查点**：W5 末 Ch3 完成 → W9 末 malloc 完成 → W14 末 GEMM 完成 → W16 末简历草稿。

---

## 每天怎么过（3-4 小时）

- 1.5h：CS:APP 阅读 + 笔记（周任务对应章节）
- 1.5h：写代码（malloc/tensor 周任务）
- 0.5h：整理 commit + push

**最低要求**：打开笔记或代码 10 分钟 + 一条 commit。做多算赚。

---

## 保险丝：学期中途被课程压住时，按顺序砍

1. 砍 GEMM 多线程 → 2. 砍 SIMD → 3. 砍 MLP demo → 4. 砍 realloc

**保底线（砍完也必须完成）**：malloc 核心（alloc/free/合并）+ Tensor v0-v2 + GEMM 分块。
保底线 = 简历上依然成立的项目。

---

## 铁律

1. **课程和 GPA 永远优先**。期中/期末周计划冻结，之后顺延，不算断档
2. **断档不补旧债**：第二天从当天周任务继续；连续 3 天连最低要求都没做到，来找我
3. **国庆（10/1-10/7）是加速器**：时间多可以提前，但不加任务——提前完成就休息
4. **不做 autograd、不做完整算子库**——那是寒假/大二下的事，这学期碰了必翻车

---

## 寒假预告（2027/1 底-2 月）

- GEMM CUDA 版（Colab T4 或学校机器）——简历上加"GPU 优化"一行
- CS:APP 第 8、9 章完整读（进程 + 虚拟内存）
- 开始收集面试八股

---

*计划定于 2026-09-01。执行从 W1 复习收尾开始。*
