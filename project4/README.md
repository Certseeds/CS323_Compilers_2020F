<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2021-01-30 16:21:38
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-30 16:30:24
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->

# <div>CS323 Compiler</div>

## <div> Project4-Assembly-Generate  Report</div>

**Grade**: No HandIn

**SID**:  $********$

**Name**:  nanoseeds

### Intermediate-Code Generation-中间代码生成部分

在汇编代码生成部分,我们引入了新的类来翻译中间代码,放到了`mipsAsm.[ch]pp`中,其中

基本思想为不管理寄存器,基于栈管理变量,不做任何窥孔优化,保证可以将提供的样例翻译为汇编代码.

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