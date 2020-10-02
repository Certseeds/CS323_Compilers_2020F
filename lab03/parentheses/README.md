<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-02 22:45:31
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-10-02 22:48:00
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
### 合法的括号

这部分的目的在于,使用flex和bison,实现判断一个[](){}序列的括号是否匹配.

TODO主要在于`syntax.y`

坑点在于yyerror,这个里面需要在失败时对变量进行修改.