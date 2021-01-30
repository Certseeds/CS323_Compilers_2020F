<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-12-27 11:50:04
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-04 11:42:12
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 * it used be `./report/StudentID-project3.md`
 -->

# <div>CS323 Compiler</div>

## <div> Project3-Intermediate-Code Generation Report</div>

**Grade**: 96/120

**SID**:  $********$

**Name**:  nanoseeds

### Intermediate-Code Generation-中间代码生成部分

在中间代码生成部分,我们引入了新的类来表示中间代码,放到了`interCode.[ch]pp`中,其中

``` cpp
#include <cstdint>
#include <string>
enum class OperandType {
    VARIABLE, // v1,t1, etc...
    // RETURN VALUE
    CONSTANT, // #0,#1, etc...
    ADDRESS,// &y9,
    POINTER,// *t9
    JUMP_LABEL, // label,function,GOTO,call
};
class Operand {
public:
    OperandType operandEnum;
    Operand(OperandType operandEnum, std::string variName);
    Operand(OperandType operandEnum, int32_t value);
    explicit Operand(OperandType operandEnum);
    union {
        std::string variName;
        int32_t value{0};
        std::string jumpLabel;
    };
    void print() const;
};
enum class InterCodeType {
    ASSIGN, ASSIGN_ADDRESS, ASSIGN_VALUE_IN_ADDRESS, COPY_VALUE_TO_ADDRESS, CALL,
    ADD, SUB, MUL, DIV,
    LABEL, GOTO,FUNCTION,
    RETURN, PARAM, ARG, READ, WRITE,
    DEC,IF_ELSE
};
class InterCode {
public:
    InterCodeType interCodeType;
    union {
        struct {
            Operand *left;
            Operand *right;
        } assign; // x := y,x := &y,x := *y, *x := y, x := CALL f, relop
        struct {
            Operand *result;
            Operand *op1;
            Operand *op2;
        } bioOp;// x := y `+,-,*,/` z
        Operand *labelElement;// LABEL,FUNCTION,GOTO
        Operand *SingleElement;// RETURN,PARAM,ARG,READ,WRITE
        struct {
            Operand *pointer;
            int32_t size;
        } dec;
        struct {
            Operand *left;
            Operand *operation;
            Operand *right;
            Operand *if_label;
            //Operand *else_label;
        } ifElse{nullptr, nullptr, nullptr, nullptr};
    };
    InterCode() = default;
    explicit InterCode(InterCodeType interCodeType);
    ~InterCode() = default;
    void print() const;
};
```

其中的亮点主要在于

+ 使用了两个类来存储中间代码,及其节点的结构.
+ 避免了enum的使用,使用enum class取而代之.
+ 使用枚举对应内部的结构.

对于`ASSIGN, ASSIGN_ADDRESS, ASSIGN_VALUE_IN_ADDRESS, COPY_VALUE_TO_ADDRESS, CALL`,对应`assign`,有两个Operand节点,中间输出`:=`

对于`ADD, SUB, MUL, DIV`,对应`bioOp`,有三个Operandd节点,中间输出对应的符号

对于`LABEL, GOTO,FUNCTION`,对应`labelElement`,有一个Operand节点,输出对应的跳转信息

对于`RETURN, PARAM, ARG, READ, WRITE`,对应`SingleElement`,有一个Operand节点,输出对应的信息

对于`DEC`,对应`dec`,有一个Operand节点,一个`int32_t size`的值存储对应的内存大小.

对于`IF_ELSE`,对应`ifElse`,有四个Operand节点,分别对应左右节点与比较符号,以及跳转信息.

对于每个`InterCode`与`Operand`,使用内部存储的枚举进行输出的判断,运行时决定输出内容.

将所有和中间代码生成相关的代码放到了`translate.[ch]pp`中.

### 中间代码生成步骤

中间代码存储在每个`Node*`中.

在解析语法树的过程中动态的对每个节点下的`Node*`,调用相应的解析函数,对下层节点`vector<interCode*>`中的中间代码进行处理,并最终全部复制进入本层节点的`vector<interCode*>`

解析到函数的最后,对节点内部的`vector<interCode*>`调用输出依次输出.

这里的主要难点在于解析时存在不确定性,需要补充`路由函数`,在运行时对节点做判断,分别调用不同的函数进行处理.

### Makefile-整体组织方面

在Makefile的组织方面,主要难点在于

1. 遇到了动态库无法链接,通过使用静态库解决了编译通过的问题.

2. 使用指定include路径解决了include,src文件夹无法分开的问题,简化了目录的结构.

3. target之间的组织关系,需要制定编译顺序.在这里,指定splc依赖所有静态库,所有静态库依赖.prepare,.prepare又依赖flex与bison的target.所以确保了flex,bison每次生成最新.

### Bonus内容

Bonus内容并没有做多少,没有做关于中间代码优化的内容.

### 样例分析

一共有10组Test Case供分析.可以分成两类

1. 无需输入: 1,3,6,9

#### Test Case 1

输出为`175 36 103`执行一共28条指令.

#### Test Case 3

输出为`2 3 5 7 11 13 17 19 23 29`执行一共4992条指令.

#### Test Case 6

输出为`1000003 1000002 3000002 1000003 2000001 2000003 1000003`执行一共149条指令.

#### Test Case 9

本样例非常耗时,需要等待片刻,输出为`370 371 407`执行一共85020条指令.

2. 需要输入: 2,4,5,7,8,10

#### Test Case 2

首先,对于虚拟机irsim来说,可以使用step来重复运行main,此时读取的参数为外部-i指定的.
所以,我们可以使用类似于`./irsim ./../test/test_3_r02.ir.test -i 1900,1,1900,3,1900,5,1900,7,1900,9,1900,11`的指令来对其进行测试.

接下来,我们将`./irsim ./../test/test_3_r02.ir.test -i 1900,1,1900,3,1900,5,1900,7,1900,9,1900,11`缩写为`test 1900,{1,3,5,7,9,11}`
并以此为凭据提供测试数据(PS:我们也在simulator中提供了test-case2的测试脚本)

对于`test 2000,{2}` 输出29,指令22条.   
对于`test 2000,{4,6,8,10,12}` 全部输出30,指令一共145条,且每次都是29条.  
对于`test 2000,{1,3,5,7,9,11}` 全部输出31,指令一共180条,且每次都是30条.

对于`test 1900,{2}` 输出28,指令23条.  
对于`test 1900,{4,6,8,10,12}` 全部输出30,指令一共150条,且每次都是30条.  
对于`test 1900,{1,3,5,7,9,11}` 全部输出31,指令一共186条,且每次都是31条.

对于`test 1984,{2}` 输出29,指令23条.   
对于`test 1984,{4,6,8,10,12}` 全部输出30,指令一共150条,且每次都是30条.  
对于`test 1984,{1,3,5,7,9,11}` 全部输出31,指令一共186条,且每次都是31条.

对于`test 1919,{2}` 输出28,指令24条.  
对于`test 1919,{4,6,8,10,12}` 全部输出30,指令一共155条,且每次都是31条.  
对于`test 1919,{1,3,5,7,9,11}` 全部输出31,指令一共192条,且每次都是32条.

#### Test Case 4

我们使用`1,-1,0,11,41,51,19`作为输入数据,输出为`1 1 1`,`-1 1 -1`,`0 0 0`,`11 121 1331`,`41 1681 68921`,`51 2601 132651`,`19 361 6859`
.总语句140条,且每次运行都为20条.

#### Test Case 5

我们使用`1,2,5,10,20,30,100`作为输入数据,输出为`1 1 5 55 6765 832040 354224848179261915075`
.总语句1614条,每次运行条数依次为`23,26,61,106,196,286,916`.

#### Test Case 7

我们使用`1001,13,1001,7,1001,11`作为输入数据,输出为`13 13 7 7 11 11`.总语句111条,每次运行条数都是37条.

#### Test Case 8

我们使用`1145141919810`作为输入数据,输出为`45`.总语句276条.

#### Test Case 10

我们使用`1 -1 0 11 22 33 -11 -22 -33`作为输入数据,输出为`1,-1,0,1,1,1,-1,-1,-1`.总语句106条,每次运行的语句分别为`9,14,14,9,9,9,14,14,14`条.




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