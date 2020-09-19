<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-09-19 21:47:34
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-09-20 00:26:53
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->
<h2 style="text-align:center">CS323 Assignment 1</h2>

**Name**: nanoseeds  
**SID**: \*\*\*\*\*\*\*\*

### Question1 
When aCcompiler compiles the following statement, how many tokens will itgenerate?

#### Answer:
`int a3 = a * 3;`
will be analysis to Tokens
``` flex
TYPE int
ID a3
ASSIGN
ID a
MUL
INT 3
SEMI
```
so, it will be analysis to 7 tokens.

### Question 2
In a string of length n(n >0), how many of the following are there?
1. Prefixes  
Answer:  
prefixs is a string that delete 0 or multiply characters from string.
so the answer is $n+1$,which begin at delete 0 to delete all n characters.
2. proper prefixes(A proper prefix is prefix of a string which are not $\epsilon$ and not equal to s itself).  
Answer:  
we know that a proper prefixes is prefixes of a string except the string itself and null. so , the answer is $n-1$.  
PS: the proper prefixes is write as 'true prefixes'.  
3. Prefixes of length m.($0<m≤n$)     
Answer:  
There only exist one prefix for a const value m of a string length n.  
which means the string delete (m-n) in the backend.  
4. Suffixes of length m.($0<m≤n$)   
Answer:  
There only exist one suffix for a const value m of a string length n.  
which means the string delete (m-n) in the frontend.  
5. Proper prefixes of length m($0<m≤n$)   
Answer:  
In this case, we find that if $m==n$,then there do not exist proper prefixes.  
if($0<m<n$), then there exist one proper prefixes.  
6. Substrings(A substring of s is obtained by deleting any prefix and any suffix from s. inlcude itself and $\epsilon$)  
Answer:  
first of all, Substrings' length range is [0,n].  
second , the length is n, so we can view the string as n char with n+1 blocks, what we should do is do double divide in n+1 blocks, the middle part is the substring.  
so Answer is $\tbinom{n+1}{2}$(select 2 from n+1).  
7. subsequence (A subsequence of s is any string formed by deleting zero or more not necessarily consecutive  positions of s. For example, baan is a subsequence of banana.)    
Answer:  
first of all, subsequence' length range is [0,n].  
for a subsequence length m, we should delete (m-n) chars in the n characters, which is $\tbinom{n}{n-m}=\tbinom{n}{m}$.(select m from n elements)  
so the sum is $\sum_{m=0}^{n}{\tbinom{n}{m}}$  

ALL in ALL
1-7's answer is 

| Order |                                                 Answer |
| :---- | -----------------------------------------------------: |
| 1     |                                                  $n+1$ |
| 2     |                                                  $n-1$ |
| 3     |                                                    $1$ |
| 4     |                                                    $1$ |
| 5     | $\begin{cases}  0, & m==n \\\\ 1, & 0<m<n \end{cases}$ |
| 6     |                                      $\tbinom{n+1}{2}$ |
| 7     |                        $\sum_{m=0}^{n}{\tbinom{n}{m}}$ |

### Question 3
Describe the languages denoted by the following regular expressions
1. First we simply it.
$((\epsilon|a)^{*}b^{*})^{*}=(a^{*}b^{*})^{*}$
PS:$\epsilon$ is guaranteed in a closure
what's more, i can find that in the text book's page 122(of English version, or Chinese version's page 76, Example3.4's sample 4). we can find $(a|b)^{*} == (a^*b^*)^*$
then we can say that, the regular expressions will match all strings that construct on characters a or b(and it's length from $0$ to $\infty$)
2. $(a|b)^*a(a|b)(a|b)$   
first because the end part do not have *, so the language's min-length is at least 3, which means front-part is zero and backend part is 3.  
and we can descript the language, it's length is at least 3, which third character from last is `a`  and other characters is `a` or `b`.
3. $a^*ba^*ba^*ba^*$  
first, the length is at least 3.  
second, this regular expressions match a string that length > 3, and was a string that construct by 3 `b` and ($0$ to $\infty$) `a` (any order can match it).

### Question 4
