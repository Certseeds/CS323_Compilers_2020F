<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-08 11:01:33
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-08 12:21:37
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->

# <div> CS323 Compiler</div>

## <div> Project1-Lexer and Parser</div>

**SID**:  \*\*\*\*\*\*\*\*

**Name**:  nanoseeds  

### Lexer-词法分析部分

在词法分析部分,我们就引入了一个新的结构,Node,其中

``` c
struct Node {
    char *name;
    int nodes_num;
    union {
        int linenum;
        char char_value;
        int int_value;
        float float_value;
        char *string_value;
    };
    struct Node **nodes;
    void (*print)(int, struct Node *);
};
```

的主要亮点之处在于其内部内置了一个函数指针,从而一个struct使用可以通过node->print(space,node)来调用其自身的print函数,而不需要对struct做判断.

词法分析部分,主要是将使用正则表达式捕获的yytext加以分析之后,赋给union部分不同的值,并给予不同的`Node`以不同的函数指针.

这其中的难点主要在于

+ 有关字符串的部分里,C语言并不会给字符串的最后加`\0`,需要在赋值的时候手动加上去.

+ 在错误处理部分,如何令其既能判断出错误,在判断出错误之后又能继续做词法分析?
  - 如果是在出错后不返回Token的话,显然,bison那一边会忽略掉这一个,然后拿下一个的和上一个进行shift/reduce,后果一般是不匹配,之后会一路不匹配到失败.
  - 得到的方案是,对错误的匹配返回一个特定的`ILLEGAL_TOKEN`,同时加上Exp->Token的规则,令其可以被匹配上.
  - 以及在不合法ID名的判断上,因为都判断出了不合法ID,所以其可以在分析时被分析成ID,只不过会报错.
  -  如何令报错就不输出?采用了一个变量,报错就修改其为1,然后Bison内输出的时候就采用判断是否为1,为1就不输出,为0就输出的方法.

### Bison-语法分析部分

在语法分析部分,Token无论是非终结符还是终结符,都直接给予了`Node`类型,并在Token处直接定义类型.(PS:此处发现,必须要在flex中加入`%option yylineno`才可以使用yylloc)

对于Shift/reduce的冲突(PS:最典型的是`IF LP stmt RP else`哪里,使用了`%prec`指定优先级的方式)

对运算符之间的优先级,按照从上到下,优先级依次增高的方式来定义了优先级,同时也定义了结合性.

错误恢复部分并没有做太多额外的工作,这一部分定义了另外一个辅助的模块`yyerror_myself`,使用枚举来决定输出什么,这一部分主要困惑在于,`yyerror(const char const *s)`函数明明有传入值,但是无法直接决定传入值,其传入值总是一个意义不明的`syntax error`,导致需要自定义函数来输出错误.

对语法解析树的建立,一方面通过`Node`内的二级指针来管理`Node`之间的关系,另一方面使用了可变参数函数`void node_set_sub(struct Node *node, int num, ...)`来简化加入Node的步骤.

于此同时,为了print处最终的语法解析树,将`Program`节点赋给一个root_node的指针,并在主函数中调用其`print(int space,Node* node)`方法即可.

这一部分的难点主要在于错误恢复部分,由于`error`实质上属于通配符,所以添加`error`后出现的二义性问题非常严重,最终没有为所有的错误都添加错误恢复,只在保证冲突尽可能少的情况下尽可能多的加入了错误的处理.

### Makefile-整体组织方面

整体上,编译所需要的文件有`lex.l`,`main.c`,`node.c,node.h`,`yyerror_myself.c,yyerror_myself.h`,`syntax.y`.这七个.其中有五个辅助的文件. 主要是为了简化整体的结构所创建.

在Makefile的组织方面,主要难点在于遇到了动态库无法链接的问题,这个问题没有得到解决,反而是通过使用静态库解决了编译通过的问题.

### Bonus内容

Bonus内容并没有做多少,只做了对单行注释的识别.

### 样例分析

一共需要上交五个文件,其中至少两个Type A error,两个Type B error.所以在test文件夹中,

+ 1,3两个文件为A error
+ 4,5两个文件为B error
+ 2中无错误,需要解析出一个超长的解析树


<style type="text/css">
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