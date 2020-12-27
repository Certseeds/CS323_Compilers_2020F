<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-11-14 23:01:33
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-12-15 21:54:35
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 * this used to be as `./src/SID-project2.md`
 -->

# <div>CS323 Compiler</div>

## <div> Project2-Semantic Analysis Report</div>

**SID**:  $********$

**Name**:  nanoseeds  

### Semantic Analysis-语义分析部分

在语义分析部分,我们就引入了一些新的类,放到了`type.cpp/hpp`中,其中

``` cpp
#include <string>
#include <variant>
#include <vector>
#include "node.hpp"
using std::string;
using std::variant;
using std::vector;
enum class CATEGORY {
    PRIMITIVE, ARRAY, STRUCTURE, FUNCTION
};
class Array;
class FieldList;
class Type {
    using PRIMI = variant<Node_TYPE, Array *, FieldList *>;
public:
    string name;
    CATEGORY category = CATEGORY::PRIMITIVE;
    PRIMI type;
    Type *returnType = nullptr; // 存储返回值的类型
    //vector<Type *> parms;
    Type() = default;
    Type(string _name, CATEGORY _category, PRIMI _type);
};
class Array {
public:
    Type *base;
    int size;
    Array(Type *base, int size);
};
class FieldList {
public:
    string name;
    Type *type = nullptr;
    FieldList *next = nullptr;
    FieldList() = default;
    FieldList(string name, Type *type, FieldList *next);
};
```

其中的亮点主要在于使用了Modern C++风格的variant,而不是union. 避免了enum的使用,使用enum class取而代之.

对于`int/float/char`,`category= CATEGORY::PRIMITIVE`,`type`内存储Node_Type作为类型

对于`struct`,`category = CATEGORY::STRUCTURE`,`type`内存储一个`FieldList*`存储内部变量.

对于`array`,`category = CATEGORY::ARRAY`,`type`内存储一个`Array*`来存储数组类型.

对于`function`,`category = CATEGORY::FUNCTION`,`type`内存储参数列表,使用`FieldList*`,而返回值使用一个`Type*`存储.

将所有和语义分析相关的代码放到了`visitSyntaxTree.cpp`中.

### 错误输出部分

使用一个独立的文件`semanticError.cpp`存储了所有的报错函数.

### Makefile-整体组织方面

在Makefile的组织方面,主要难点在于遇到了动态库无法链接,通过使用静态库解决了编译通过的问题.

### Bonus内容

Bonus内容并没有做多少,没有做关于scope与实等价的内容.

### 样例分析

一共需要上交10组Test Case,其中至少8种error,所以在test文件夹中,

+ 1-9无error.
+ 10中存在1-12,一共12种错误.

### Nov.14-2020提交Bug分析 & 不合理样例分析

#### Bug/Feature分析

1. 此日提交(后称Commit)中没有考虑函数数组作为参数的情况.(已修复)

2. Commit中对数组赋值的比较只考虑了维数,没有考虑维数长度(修复为都考虑)

3. Float与Int做运算会自动擢升到Float.(只实现了擢升,没什么影响,不修了)

4. 赋值语句不返回值(合理的设计,应该保留)

5. Commit中struct的声明名字与变量名不可重复,可以索引声明struct的名字当作变量名(设计问题,不予解决)

6. strcut内部的变量名暴露在符号表内(重大Bug,已修复.)

7. 函数调用中对Strcut.variable的变量支持出错(已修复)

8. 没有支持递归(已修正,涉及修改`syntax.y`)

#### 不合理样例

1. 样例中出现了两次struct中包含struct自身的情况,在类C语言中不应该出现.典型案例如下:

``` cpp
struct AST {//example 1
    struct AST children[10];
    int num_children;
};
struct node {//example 2
    struct node value;
    struct node left;
    struct node right;
    struct node parent;
    int value;
};
```

2. 出现多次函数声明中的变量与函数变量重名的情况:不知道是否是设计允许.

3. 重复定义变量 && 非全局作用域报错

``` cpp
a = 1;
b = 0.1;
int c = 20;
    if (a + b == 0.7) {
      int c = 10;// TODO,此处重复定义变量
      int k = 1;
      b + a = b;
    }
c = 1;
k = c;// TODO,全局作用域的话此处不应报错
```

4. 同名变量不同类型:

```cpp
int test1(int a, int b)
{
    while(0) {
        if(a) {
            int c = 1;
        } else if (b) {
            int d = a;
        }
        else {
            float c = 1.1;// TODO, 同名变量类型不同怎么处理?
        }
    }
    return 1;
}
```

PS: 因为这个Porject会使用很多同学交的test_case去判题,
同学们的test_case杂乱无章,会根据自己的假设乱加东西,上面说的struct嵌套,struct是否可重名,array比较的原理等都是如此,所以,问题在于最好在Report里把这些需求里没说,但是大家会按自己想法做的小细节都说个明白,拉个表单把每个都过一遍,讲一下设计思路,对自己的思路和学助判题也有帮助.

注: 本次project评分为手动判分,所以Report里说明思路后可以避免很多问题.

<style type="text/css">
*{
}
div{
  text-align: center;
}
div>div>div>div {
  text-align: center;
  border-bottom: 1px solid #d9d9d9;
  display: inline-block;
  padding: 2px;
}
div>img{
  border-radius: 0.3125em;
  box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);
}
</style>