<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-09-17 11:48:24
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-09-19 17:47:37
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
## Project 1
# 词法分析与语法分析

### Part 1 预览
我们的目标是,通过整个project体系,为SPL(SUSTech Programming Language,一个类C的语言)写出一个编译器;支持一些相似的操作符,并且支持基本的读写操作,虽然砍掉了很多语法,但是还是图灵完备的.

我们希望最后将SPL编译到MIPS32上,project会将其分为 `词法分析与语法分析`,`语义检查`,`中间代码生成`,`目标代码生成`四部分.最后,我们希望编译器编译出来的产物可以在MIPS仿真器上可以运行.

我们提供了拥有全部环境的虚拟机,但是也可以在本机上配置环境,具体请看part 2.

在project1,我们会使用C,基于`GNU flex` && `GNU Bison`, 实现自己的词法,语法解析器.现代的编译器也一般是将词法,语法分析交给它们(lex/flex, yacc/bison)进行自动生成.但是,虽然现成的工具令人不需要太多的理论知识就可以完成project1,但是这并不意味着理论知识不重要(别忘了理论课还有作业),课上将会学习正则表达式,上下文无关语法.项目中主要要进行的是正则表达式的书写.

需要注意的是,这个工作是以后工作的基石,所以,尽量保持代码的可维护性,可拓展性,(以及足够的测试,注释).

### Part 2,Lab环境

#### 前言
我们已经提过了,Lab提供了一个配置好环境的Ubuntu 18.04-64bit虚拟机,可以用它开发.但是,本机开发也行.只要拥有以下必要的环境.
+ GCC version 7.4.0
+ GNU Make version 4.1
+ GNU Flex version 2.6.4
+ GNU Bison version 3.0.4
+ Python version 3.6.8
+ urwid (Python module) 2.0.1
+ Spim version 8.0

配置脚本为[enviroment.sh](./enviorment.sh)

#### 虚拟机部分
虚拟机可以在[this](http://10.20.38.233:2333/course/cs323-compilers/)下载,login as `student:compiler`

### Part 3: 词法分析中的Flex
Flex是一个快速的词法分析器生成器(fast lex).需要指定要匹配的模式以及每个模式匹配之后的操作.Flex会使用文件中的正则表达式,并生成可识别所有模式的组合NFA，然后将其转换为等效的DFA，并尽可能的精简自动机，最后生成 实现词法分析器的C代码. Flex与它的前身Lex(由Lesk和Schmidt设计)相似，并且具有许多相似之处. 尽管我们将在项目中使用Flex，但几乎所有使用的功能都在Lex中提供.

本部分旨在快速介绍Flex,为project提供参考。有关Flex的更多信息，使用`runinfo flex`或阅读文档[page1](https://www.epaperpress.com/lexandyacc/download/flex.pdf) 

#### 3.1 略

#### 3.2 也略

#### 3.3更多特性
1. `yylineno`
内置的行数统计器,
在Definitions处添加`%option yylineno`即可使用.
2. `input` && `output`
可以在识别之后,读取缓冲区内的字符.以使用代码解析,而不是写表达式
比如读取注释
``` flex
"//" {char c; while((c=input())) != '\n';}
```
识别到//后,读取到换行符为止,其他的都抛弃.
3. `yytext`,`yylength`,`yyless` and `yymore`
yytext: 本次识别出来的字符.
yylength: yytext的长度.
yyless(int n): 把yytext的yylength-n个字符,放回输入流
yymore: 将下次分析的词汇接在本次的yytext后面.(我感觉像递归)
example字符串:

"And God said,\"Let therebe light,\" and there was light."

``` flex
\"[^\"]*\":{
    if(yytext[yyleng-2] == ’\\’) {
        yyless(yyleng-1);
        yymore();
    } else {
        /* process the string literal */
    }
}
```
识别出来的第一次是"And God said,\",然后(yylength-(yylength-1))=1,"被放回里面,接着是"Let therebe light,\",然后也是放回一个,

#### 3.4 手写Lexer
为了实现词法分析器，先读附录A,读取Token和详细解释. 此时应该为Token写正则,您应该为前四个标记编写正则表达式，然后这一步骤的动作比较简单. 在此阶段，工作只是识别每个Token，因此您可以简单地用相应的action打印出Token:

``` flex
"TYPE" {printf("${TYPE} %s\n",yytext);}
```

为了报错,可以用这个兜底规则

``` flex
. { printf("Error type A at Line %d: Unknown characters \’%s\’\ n",yylineno, yytext); }
```

样例1:
``` c
int test_spl(){
    int i = 0,j = 1;
    float i = 1;
}
```
输出
``` 
TYPE int
ID test_spl
LP
RP
LC
TYPE int
ID i
ASSIGN
INT 0
COMMA
ID j
ASSIGN
INT 1
SEMI
TYPE float
ID i
ASSIGN
INT 1
SEMI
RC
```