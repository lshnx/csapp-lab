# C++ Primer（前 482 页）恢复计划

> 目标：恢复"读过但忘了"的 C++ 特有层知识储备，建立"得心应手"的使用路径。
> 定位：附线，不占主线时间槽。2 周 × 30-45 分钟/天收工，之后每周 2-3 道 LeetCode（C++）保温。
> 范围：482 页 ≈ Ch1-13 开头。Ch14（运算符重载）、Ch15（继承多态）、Ch16（模板）**不在范围内**——之前没读到，这学期不碰，需要时（数据结构课/寒假）再学。
> 规则：编译跑通才算过；卡 15 分钟翻书；每天一个不攒；第 10 天综合题全程不翻书。

---

## 一、完整自查清单（约 45 个知识点，逐项打勾）

### Ch2 变量和基本类型
- [ ] 基本类型与大小（int/long/float/double/char）
- [ ] 字面值与转义序列
- [ ] 拷贝初始化 vs 列表初始化（花括号）
- [ ] 声明 vs 定义（extern）
- [ ] 引用：定义时必须初始化、绑定对象不可更换
- [ ] 指针 vs 引用（何时用哪个）
- [ ] const 对象（定义时必须初始化）
- [ ] const 引用（指向常量的引用）
- [ ] 指针和 const 的 4 种组合：`int* const` / `const int*` / `const int* const`
- [ ] **顶层 const vs 底层 const**（区分标准：顶层管"自己不能变"，底层管"指向的东西不能变"）
- [ ] constexpr 与常量表达式
- [ ] auto（丢弃顶层 const、保留底层 const）
- [ ] decltype
- [ ] typedef / using 类型别名

### Ch3 字符串、向量和数组
- [ ] string 常用操作：getline、size、+、比较
- [ ] 范围 for（range for）
- [ ] vector：push_back、size、下标 vs at
- [ ] 迭代器：begin/end、+n、迭代器失效
- [ ] 数组 vs vector；数组名退化为指针

### Ch4-5 表达式与语句
- [ ] 类型转换：static_cast / 隐式转换
- [ ] throw / try / catch
- [ ] stdexcept 异常类（runtime_error 等）

### Ch6 函数
- [ ] 引用传参 vs 值传参
- [ ] const 形参
- [ ] 数组形参（退化为指针）
- [ ] 函数重载（靠参数列表区分）
- [ ] 默认实参
- [ ] inline 函数
- [ ] 返回引用（禁止返回局部对象的引用）

### Ch7 类
- [ ] class vs struct（默认访问权限不同）
- [ ] 成员函数与 this
- [ ] 构造函数、初始化列表、默认构造
- [ ] const 成员函数
- [ ] 友元（friend）

### Ch8 IO 库
- [ ] fstream：ifstream/ofstream 文件读写
- [ ] istringstream / ostringstream 字符串流

### Ch9-11 容器与算法
- [ ] 顺序容器：vector / deque / list / array 的区别与选择
- [ ] 容器通用操作：insert/erase、begin/end
- [ ] 泛型算法：sort / find / count / accumulate / copy / transform / find_if
- [ ] lambda：捕获列表 `[]` 的几种形式、参数、返回类型
- [ ] 关联容器：map / set / unordered_map / unordered_set
- [ ] map 的 `operator[]` vs `find`（**`[]` 会插入新键**）

### Ch12-13 动态内存与拷贝控制
- [ ] new / delete、动态数组
- [ ] shared_ptr：make_shared、引用计数、reset
- [ ] unique_ptr：独占所有权、make_unique、move 转移所有权
- [ ] weak_ptr：不增加引用计数，用 lock() 检查对象是否还在
- [ ] 拷贝构造 / 拷贝赋值 / 析构（**三法则**：需要其中一个就要三个都写）
- [ ] 深拷贝 vs 浅拷贝（有指针成员的类）
- [ ] 动态内存管理类的思想（StrVec 示例）

---

## 二、10 天恢复包（每天一个练习，打包一个簇）

| 天 | 主题 | 练习 |
|----|------|------|
| 1 | 变量定义形式 | 列表初始化/auto/decltype/引用各写一遍，再**故意写错**看编译器怎么骂 |
| 2 | const 全家 | 顶层 vs 底层 const 各举 3 例编译；constexpr 写一个 |
| 3 | 函数增强 | 重载 print 系列 + 默认实参 + 引用传参（不用指针） |
| 4 | string/vector/迭代器 | 成绩统计：范围 for + 迭代器两版都写 |
| 5 | 容器 + 泛型算法 | 用 sort/find/count/transform 把练习 4 的手写循环全替换掉 |
| 6 | lambda | sort 带 lambda 比较器、find_if 自定义条件 |
| 7 | map/set | 单词频次统计 + 去重（unordered 版也试一下） |
| 8 | 类 | Student 类：构造函数初始化列表、const 成员函数、this、友元 |
| 9 | 智能指针 + 拷贝控制 | 链表用 unique_ptr 管理；带指针成员的类实现三法则，验证深拷贝 |
| 10 | 综合 200 行 | 成绩管理系统：fstream 读文件 → map 统计 → 排序写回 + 异常处理，全程不翻书 |

---

## 三、通关标准

1. 自查清单逐项过：**能不看书写出典型用法**（不是背概念，是写代码）
2. 第 10 天综合题全程不翻书、编译跑通
3. 之后每周 2-3 道 LeetCode（C++）——一份时间三份收益：C++ 保温 + 数据结构练习 + 2027 实习面试铺路

---

## 四、执行位置

- 数据结构课用 C++ → 恢复包与课程作业**合并执行**，不开独立时间槽
- 数据结构课用 C → 恢复包放**睡前 30 分钟**槽，10 天收工
- 恢复完成后 LeetCode 保温放周末批次

*计划定于 2026-09-03。*
