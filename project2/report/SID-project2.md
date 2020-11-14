<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-11-14 23:01:33
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-14 23:59:59
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->

# <div> CS323 Compiler</div>

## <div> Project2-Semantic Analysis</div>

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