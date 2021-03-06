<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-10-30 22:42:41
 * @LastEditors: nanoseeds
 * @LastEditTime: 2021-01-04 22:59:41
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->

# CS323 Assignment 4: Bottom-Up Parsing Exercises

**Scores**: 100/100  
**Name**: nanoseeds  
**SID**: \*\*\*\*\*\*\*\*

## Question 1 (Simple LR):

Consider the following  grammar $G$:
$$S \to {\alpha}B$$
$$B \to S+B \mid \epsilon$$

1. Construct the SLR(1) parsing table for $G$. Please put down the detailed steps, including
the calculation of LR(0) item sets. [20 points]
2. Is the grammar SLR(1)? [10 points]
3. Can the SLR(1) parser accept the input string aaaa+++? If yes, please list the moves
made by the parser; otherwise, state the reason. Before parsing, please resolve conflicts
if any. [10 points]

## Answer_of_Question1

1. the augmented grammer of Question 1 is
$$S' \to S$$
$$S \to {\alpha}B$$
$$B \to S+B $$
$$B \to \epsilon$$

now we construct the items sets.

$I_0 = CLOSURE({S' \to \cdot S}) =  \{S' \to \cdot S,S \to \cdot \alpha B\}$

$I_1 = GOTO(I_0,S) = CLOSURE(\{S' \to S \cdot\})= \{S' \to S  \cdot\}$

$I_2 = GOTO(I_0,a) = CLOSURE(\{S \to \alpha \cdot B\})= \{S \to \alpha \cdot B,B \to \cdot S+B,B \to \cdot, S \to \cdot aB \}$

$GOTO(I_0,B) = CLOSURE(\{\})= \{\}$

$GOTO(I_0,+)$ can  not produce new item set.

In $I_1$, there do not have any next to accept except $\$$, so do not need to calclute the next.

$I_3 = GOTO(I_2,S) = CLOSURE(\{B \to S \cdot +B \}) =\{B \to S \cdot +B \}$ 

$GOTO(I_2,a) = CLOSURE(\{S \to \alpha \cdot B\}) = I_2$

$I_4 = GOTO(I_2,B) = CLOSURE(\{S \to \alpha B \cdot \}) = \{S \to \alpha B \cdot \}$

$GOTO(I_2,+)$ can not produce new item set.

$GOTO(I_3,S),GOTO(I_3,\alpha),GOTO(I_3,B)$ can not produce new item sets.

$I_5 = GOTO(I_3,+) = CLOSURE(\{B \to S+ \cdot B\}) = \{B \to S+ \cdot B,B \to \cdot S+B,B \to \cdot, S \to \cdot aB \}$

$I_4$ can not produce more item sets.

$GOTO(I_5,S) = CLOSURE(\{B \to S \cdot +B\}) = I_3$

$GOTO(I_5,\alpha) = CLOSURE(\{S \to a \cdot B\}) = I_2$ 

$GOTO(I_5,+)$ do not produce new item sets.

$I_6 = GOTO(I_5,B) = CLOSURE(\{B \to S+B \cdot\}) = \{B \to S+B \cdot\}$

$GOTO(I_6,\alpha),GOTO(I_6,B),GOTO(I_6,+),GOTO(I_6,S)$ do not produce new items


<div>
  <img src="./Question_01_01.png"><br />
  <div>graph for Item set specification family</div>
</div>

the FOLLOW function is below

$$FOLLOW(S')=FOLLOW(B)=FOLLOW(S)=\{\$,+\}$$

now we use the Item set specification family ,GOTO() and FOLLOW functions to produce the build the SLR(1) parsing table.

| 状态  | Action:$\alpha$ | Action:$+$ | Action:$\$$ | GOTO:$S'$ | GOTO:$S$ | GOTO:$B$ |
| :---: | :-------------: | :--------: | :---------: | :-------: | :------: | :------: |
| $I_0$ |       S2        |            |             |           |  $I_1$   |          |
| $I_1$ |                 |            |     acc     |           |          |          |
| $I_2$ |       S2        |     R4     |     R4      |           |  $I_3$   |  $I_4$   |
| $I_3$ |                 |     S5     |             |           |          |          |
| $I_4$ |                 |     R2     |     R2      |           |          |          |
| $I_5$ |       S2        |     R4     |     R4      |           |  $I_3$   |  $I_6$   |
| $I_6$ |                 |     R4     |     R4      |           |  $I_3$   |          |

2. there do not exist conflict, so it is a SLR(1) grammer.

3. it can accept input string `aaaa+++`

| order |     stack     | signal |    input    |           action           |
| :---- | :-----------: | :----: | :---------: | :------------------------: |
| (1)   |       0       |        | aaaa+++$\$$ |           Shift            |
| (2)   |      0 2      |   a    | aaa+++$\$$  |           Shift            |
| (3)   |     0 2 2     |   aa   |  aa+++$\$$  |           Shift            |
| (4)   |    0 2 2 2    |  aaa   |  a+++$\$$   |           Shift            |
| (5)   |   0 2 2 2 2   |  aaaa  |   +++$\$$   | Reduce by $B \to \epsilon$ |
| (6)   |   0 2 2 2 2   | aaaaB  |   +++$\$$   |       GOTO state $4$       |
| (7)   |  0 2 2 2 2 4  | aaaaB  |   +++$\$$   |    Reduce by $S \to aB$    |
| (8)   |   0 2 2 2 3   |  aaaS  |   +++$\$$   |           Shift            |
| (9)   |  0 2 2 2 3 5  | aaaS+  |   ++$\$$    | Reduce by $B \to \epsilon$ |
| (10)  |  0 2 2 2 3 5  | aaaS+B |   ++$\$$    |       GOTO state $6$       |
| (11)  | 0 2 2 2 3 5 6 | aaaS+B |   ++$\$$    |   Reduce by $B \to S+B$    |
| (12)  |   0 2 2 2 4   |  aaaB  |   ++$\$$    |    Reduce by $S \to aB$    |
| (13)  |    0 2 2 3    |  aaS   |   ++$\$$    |           Shift            |
| (14)  |   0 2 2 3 5   |  aaS+  |    +$\$$    | Reduce by $B \to \epsilon$ |
| (15)  |   0 2 2 3 5   | aaS+B  |    +$\$$    |       GOTO state $6$       |
| (16)  |  0 2 2 3 5 6  | aaS+B  |    +$\$$    |   Reduce by $B \to S+B$    |
| (17)  |    0 2 2 4    |  aaB   |    +$\$$    |    Reduce by $S \to aB$    |
| (18)  |     0 2 3     |   aS   |    +$\$$    |           Shift            |
| (19)  |    0 2 3 5    |  aS+   |    $\$$     | Reduce by $B \to \epsilon$ |
| (20)  |    0 2 3 5    |  aS+B  |    $\$$     |       GOTO state $6$       |
| (21)  |   0 2 3 5 6   |  aS+B  |    $\$$     |   Reduce by $B \to S+B$    |
| (22)  |     0 2 4     |   aB   |    $\$$     |    Reduce by $S \to aB$    |
| (23)  |      0 1      |   S    |    $\$$     |            acc             |

## Answer_of_Question2

### SubQuestion 1

the augmented grammer of Question 2 is:
$$1 : S' \to S$$
$$2 : S \to {\alpha}B$$
$$3 : B \to S+B $$
$$4 : B \to \epsilon$$

first:

$CLOSURE(\{S' \to \cdot S,\$\})$, in there, $[A \to \alpha \cdot B \beta,a]$,$A=S',\alpha=\beta=\epsilon,B=S,a=\$$, so for $B \to \gamma$ and b in $FIRST(\beta a)$ which is $S \to \alpha B$  and b can only be $\$$, so add $[S \to \cdot \alpha B,\$]$

$[A \to \alpha \cdot B \beta,a]$ for $[S \to \cdot \alpha B,\$]$, $A=S,\alpha=\epsilon,B=\alpha,\beta = B,a=\$$.in this case, B is a terminal, which can not produce more item.

so $I_0 = \{[S' \to \cdot S,\$],[S \to \cdot \alpha B, \$]\}$

GOTO($I_0$,S) = $CLOSURE(\{[S' \to S \cdot, \$]\}) =  \{[S' \to S \cdot, \$]\} = I_1$

$I_1=\{[S' \to S \cdot, \$]\}$

GOTO($I_0$,$\alpha$) = $CLOSURE(\{[S \to \alpha \cdot B, \$]\})$

in this case $A=S,\alpha = \alpha,B=B,\beta=\epsilon,a=\$$ so $B \to \gamma$ include $B \to S+B$ and $B \to \epsilon$. FIRST($\beta a$)=FISRT($) so b is just $\$$.

then for$[B \to \cdot S+B,\$]$, $A=B,\alpha = \epsilon,B=S,\beta=+B,a=\$$, so $B \to \gamma$ include $S \to \alpha B$, FIRST($\beta a$)= FIRST($+B\$$)=$+$, so b is $+$

so $I_2 = \{[S \to \alpha \cdot B,\$],[B \to \cdot S+B,\$],[B \to \cdot \epsilon,\$],[S \to \cdot \alpha B,+]\}$

we can not get more item sets from $I_0$

for $I_2$,

GOTO($I_2$,S) = $CLOSURE(\{[B \to S \cdot +B,\$]\})=\{[B \to S \cdot +B,\$]\} = I_3$

GOTO($I_2$,$\alpha$) = $CLOSURE(\{[S \to \alpha \cdot B,+]\})= \{[S \to \alpha \cdot B,+],[B \to \cdot S+B,+],[B \to \cdot \epsilon,+],[S \to \cdot \alpha B,+]\} = I_4$

GOTO($I_2$,B) = $CLOSURE(\{[S \to \alpha B \cdot,\$])\} = \{[S \to \alpha B \cdot,\$] =I_5$

for $I_3$

GOTO($I_3$,$+$) = $CLOSURE(\{[B \to S+ \cdot B,\$]\})$

in this case $A=B,\alpha = S+,B=B,\beta=\epsilon,a=\$$, so FIRST($\beta a$)=FIRST($\$$)=$\$$
the next is $[B \to \cdot S+B,\$],[B \to \cdot \epsilon,\$]$

so GOTO($I_3$,$+$) = $CLOSURE(\{[B \to S+ \cdot B,\$]\}) = \{[B \to S+ \cdot B,\$],[B \to \cdot S+B,\$],[B \to \cdot \epsilon,\$],[S \to \cdot \alpha B,+]\} = I_6$

for $I_4$

GOTO($I_4$,S) = $CLOSURE(\{[B \to S \cdot +B,+]\}) =\{[B \to S \cdot +B,+]\} = I_7$

GOTO($I_4$,$\alpha$) = $CLOSURE(\{[S \to \alpha \cdot B,+]\}) = I_4$

GOTO($I_4$,B)= $CLOSURE(\{[S \to \alpha B \cdot,+]\}) = \{[S \to \alpha B \cdot,+]\} = I_8$

for $I_5$, no more item sets.

for $I_6$

GOTO($I_6$,S)=$CLOSURE(\{[B \to S \cdot +B,\$]\})=\{[B \to S \cdot +B,\$]\} = I_3$

GOTO($I_6$,$\alpha$) = $CLOSURE(\{[S \to \alpha \cdot B,+]\})=I_4$

GOTO($I_6$,B) = $CLOSURE(\{[B \to S+B \cdot,\$]\})=\{[B \to S+B \cdot,\$]\} = I_9$

for $I_7$

GOTO($I_7$,+)=$CLOSURE(\{[B \to S+ \cdot B,+]\})=\{[B \to S+ \cdot B,+],[B \to \cdot S+B,+],[ B \to \cdot \epsilon,+],[S \to \cdot \alpha B,+]\} = I_{10}$

for $I_8$, no more item sets.

for $I_9$, no more item sets.

for $I_{10}$

GOTO($I_{10}$,B) = $CLOSURE(\{[B \to S+B \cdot,+]\}) = \{[B \to S+B \cdot,+]\}=I_{11}$

GOTO($I_{10}$,S) = $CLOSURE(\{[B \to S \cdot +B,+]\})=I_7$

GOTO($I_{10}$,$\alpha$)=$CLOSURE(\{[S \to \alpha \cdot B,+]\})=I_4$

no more item sets for $I_{11}$

|  state   | ACTION:$\alpha$ | ACTION:$+$ | ACTION:$\$$ | GOTO:S |  GOTO:B  |
| :------: | :-------------: | :--------: | :---------: | :----: | :------: |
|  $I_0$   |       S2        |            |             | $I_1$  |          |
|  $I_1$   |                 |            |     acc     |        |          |
|  $I_2$   |       S4        |     R4     |     R4      | $I_3$  |  $I_5$   |
|  $I_3$   |                 |     S6     |             |        |          |
|  $I_4$   |       S4        |     R4     |     R4      | $I_7$  |  $I_8$   |
|  $I_5$   |                 |            |     R2      |        |          |
|  $I_6$   |       S4        |     R4     |     R4      | $I_3$  |  $I_9$   |
|  $I_7$   |                 |    S10     |             |        |          |
|  $I_8$   |                 |     R2     |             |        |          |
|  $I_9$   |                 |            |     R3      |        |          |
| $I_{10}$ |       S4        |     R4     |     R4      | $I_7$  | $I_{11}$ |
| $I_{11}$ |                 |     R3     |             |        |          |

### SubQuestion 2

Yes, it can

| order |      stack      | signal |    input    |           action           |
| :---- | :-------------: | :----: | :---------: | :------------------------: |
| (0)   |        0        |        | aaaa+++$\$$ |           Shift            |
| (1)   |       0 2       |   a    | aaa+++$\$$  |           Shift            |
| (2)   |      0 2 4      |   aa   |  aa+++$\$$  |           Shift            |
| (3)   |     0 2 4 4     |  aaa   |  a+++$\$$   |           Shift            |
| (4)   |    0 2 4 4 4    |  aaaa  |   +++$\$$   | Reduce by $B \to \epsilon$ |
| (5)   |    0 2 4 4 4    | aaaaB  |   +++$\$$   |      GOTO state $I_8$      |
| (6)   |   0 2 4 4 4 8   | aaaaB  |   +++$\$$   | Reduce by $S \to \alpha B$ |
| (7)   |    0 2 4 4 7    |  aaaS  |   +++$\$$   |           Shift            |
| (8)   |  0 2 4 4 7 10   | aaaS+  |   ++$\$$    | Reduce by $B \to \epsilon$ |
| (9)   |  0 2 4 4 7 10   | aaaS+B |   ++$\$$    |    GOTO state $I_{11}$     |
| (10)  | 0 2 4 4 7 10 11 | aaaS+B |   ++$\$$    |   Reduce by $B \to S+B$    |
| (11)  |    0 2 4 4 8    |  aaaB  |   ++$\$$    | Reduce by $S \to \alpha B$ |
| (12)  |     0 2 4 7     |  aaS   |   ++$\$$    |           Shift            |
| (13)  |   0 2 4 7 10    |  aaS+  |    +$\$$    | Reduce by $B \to \epsilon$ |
| (14)  |   0 2 4 7 10    | aaS+B  |    +$\$$    |    GOTO state $I_{11}$     |
| (15)  |  0 2 4 7 10 11  | aaS+B  |    +$\$$    |   Reduce by $B \to S+B$    |
| (16)  |     0 2 4 8     |  aaB   |    +$\$$    | Reduce by $S \to \alpha B$ |
| (17)  |      0 2 7      |   aS   |    +$\$$    |           Shift            |
| (18)  |    0 2 7 10     |  aS+   |    $\$$     | Reduce by $B \to \epsilon$ |
| (19)  |    0 2 7 10     |  aS+B  |    $\$$     |    GOTO statet $I_{11}$    |
| (20)  |   0 2 7 10 11   |  aS+B  |    $\$$     |   Reduce by $B \to S+B$    |
| (21)  |      0 2 5      |   aB   |    $\$$     | Reduce by $S \to \alpha B$ |
| (22)  |       0 1       |   S    |    $\$$     |            acc             |

so the CLR(1) parse can accept the input string `aaaa+++`.

## Question 3 (Lookahead LR)

Consider the following  grammar $G$:
$$S \to {\alpha}B$$
$$B \to S+B \mid \epsilon$$

1. Construct the LALR(1) parsing table for G. Please put down the detailed steps,
including the merging of LR(1) item sets. [20 points]

2. Can the LALR(1) parser accept the input string aaaa+++? If yes, please list the
moves made by the parser; otherwise, state the reason. Before parsing, please resolve
conflicts if any. [10 points]

## Answer_of_Question3

### SubQuestion 1: LALR(1) parsing table

this step is the same as what CLR(1) step do, so in this step we just copy what we had done in Question 2

the augmented grammer of Question 3 is:
$$1 : S' \to S$$
$$2 : S \to {\alpha}B$$
$$3 : B \to S+B $$
$$4 : B \to \epsilon$$

first:

$CLOSURE(\{S' \to \cdot S,\$\})$, in there, $[A \to \alpha \cdot B \beta,a]$,$A=S',\alpha=\beta=\epsilon,B=S,a=\$$, so for $B \to \gamma$ and b in $FIRST(\beta a)$ which is $S \to \alpha B$  and b can only be $\$$, so add $[S \to \cdot \alpha B,\$]$

$[A \to \alpha \cdot B \beta,a]$ for $[S \to \cdot \alpha B,\$]$, $A=S,\alpha=\epsilon,B=\alpha,\beta = B,a=\$$.in this case, B is a terminal, which can not produce more item.

so $I_0 = \{[S' \to \cdot S,\$],[S \to \cdot \alpha B, \$]\}$

GOTO($I_0$,S) = $CLOSURE(\{[S' \to S \cdot, \$]\}) =  \{[S' \to S \cdot, \$]\} = I_1$

$I_1=\{[S' \to S \cdot, \$]\}$

GOTO($I_0$,$\alpha$) = $CLOSURE(\{[S \to \alpha \cdot B, \$]\})$

in this case $A=S,\alpha = \alpha,B=B,\beta=\epsilon,a=\$$ so $B \to \gamma$ include $B \to S+B$ and $B \to \epsilon$. FIRST($\beta a$)=FISRT($) so b is just $\$$.

then for$[B \to \cdot S+B,\$]$, $A=B,\alpha = \epsilon,B=S,\beta=+B,a=\$$, so $B \to \gamma$ include $S \to \alpha B$, FIRST($\beta a$)= FIRST($+B\$$)=$+$, so b is $+$

so $I_2 = \{[S \to \alpha \cdot B,\$],[B \to \cdot S+B,\$],[B \to \cdot \epsilon,\$],[S \to \cdot \alpha B,+]\}$

we can not get more item sets from $I_0$

for $I_2$,

GOTO($I_2$,S) = $CLOSURE(\{[B \to S \cdot +B,\$]\})=\{[B \to S \cdot +B,\$]\} = I_3$

GOTO($I_2$,$\alpha$) = $CLOSURE(\{[S \to \alpha \cdot B,+]\})= \{[S \to \alpha \cdot B,+],[B \to \cdot S+B,+],[B \to \cdot \epsilon,+],[S \to \cdot \alpha B,+]\} = I_4$

GOTO($I_2$,B) = $CLOSURE(\{[S \to \alpha B \cdot,\$])\} = \{[S \to \alpha B \cdot,\$] =I_5$

for $I_3$

GOTO($I_3$,$+$) = $CLOSURE(\{[B \to S+ \cdot B,\$]\})$

in this case $A=B,\alpha = S+,B=B,\beta=\epsilon,a=\$$, so FIRST($\beta a$)=FIRST($\$$)=$\$$
the next is $[B \to \cdot S+B,\$],[B \to \cdot \epsilon,\$]$

so GOTO($I_3$,$+$) = $CLOSURE(\{[B \to S+ \cdot B,\$]\}) = \{[B \to S+ \cdot B,\$],[B \to \cdot S+B,\$],[B \to \cdot \epsilon,\$],[S \to \cdot \alpha B,+]\} = I_6$

for $I_4$

GOTO($I_4$,S) = $CLOSURE(\{[B \to S \cdot +B,+]\}) =\{[B \to S \cdot +B,+]\} = I_7$

GOTO($I_4$,$\alpha$) = $CLOSURE(\{[S \to \alpha \cdot B,+]\}) = I_4$

GOTO($I_4$,B)= $CLOSURE(\{[S \to \alpha B \cdot,+]\}) = \{[S \to \alpha B \cdot,+]\} = I_8$

for $I_5$, no more item sets.

for $I_6$

GOTO($I_6$,S)=$CLOSURE(\{[B \to S \cdot +B,\$]\})=\{[B \to S \cdot +B,\$]\} = I_3$

GOTO($I_6$,$\alpha$) = $CLOSURE(\{[S \to \alpha \cdot B,+]\})=I_4$

GOTO($I_6$,B) = $CLOSURE(\{[B \to S+B \cdot,\$]\})=\{[B \to S+B \cdot,\$]\} = I_9$

for $I_7$

GOTO($I_7$,+)=$CLOSURE(\{[B \to S+ \cdot B,+]\})=\{[B \to S+ \cdot B,+],[B \to \cdot S+B,+],[ B \to \cdot \epsilon,+],[S \to \cdot \alpha B,+]\} = I_{10}$

for $I_8$, no more item sets.

for $I_9$, no more item sets.

for $I_{10}$

GOTO($I_{10}$,B) = $CLOSURE(\{[B \to S+B \cdot,+]\}) = \{[B \to S+B \cdot,+]\}=I_{11}$

GOTO($I_{10}$,S) = $CLOSURE(\{[B \to S \cdot +B,+]\})=I_7$

GOTO($I_{10}$,$\alpha$)=$CLOSURE(\{[S \to \alpha \cdot B,+]\})=I_4$

no more item sets for $I_{11}$

In conclusion:

$I_0$=$CLOSURE({[S' \to \cdot S,\$]})$  
$I_1$=$CLOSURE({[S' \to S \cdot,\$]})$  
$I_2$=$CLOSURE({[S \to \alpha \cdot B,\$]})$  
$I_3$=$CLOSURE({[B \to S \cdot +B,\$]})$  
$I_4$=$CLOSURE({[S \to \alpha \cdot B,+]})$  
$I_5$=$CLOSURE({[S \to \alpha B \cdot,\$]})$  
$I_6$=$CLOSURE({[B \to S+ \cdot B,\$]})$  
$I_7$=$CLOSURE({[B \to S \cdot +B,+]})$  
$I_8$=$CLOSURE({[S \to \alpha B \cdot,+]})$  
$I_9$=$CLOSURE({[B \to S+B \cdot,\$]})$  
$I_{10}$=$CLOSURE({[B \to S+ \cdot B,+]})$  
$I_{11}$=$CLOSURE({[B \to S+B \cdot,+]})$

1. $I_2$ and $I_4$ should merge to $I_{24}$
2. $I_3$ and $I_7$ should merge to $I_{37}$
3. $I_5$ and $I_8$ should merge to $I_{58}$
4. $I_6$ and $I_{10}$ should merge to $I_{6\&{10}}$
5. $I_9$ and $I_{11}$ should merge to $I_{9\&{11}}$

so the table is 

|     state     | ACTION:$\alpha$ | ACTION:$+$  | ACTION:$\$$ |  GOTO:S  |    GOTO:B     |
| :-----------: | :-------------: | :---------: | :---------: | :------: | :-----------: |
|     $I_0$     |    $S_{24}$     |             |             |  $I_1$   |               |
|     $I_1$     |                 |             |     acc     |          |               |
|   $I_{24}$    |    $S_{24}$     |     R4      |     R4      | $I_{37}$ |   $I_{58}$    |
|   $I_{37}$    |                 | $S_{6\&10}$ |             |          |               |
|   $I_{58}$    |                 |     R2      |     R2      |          |               |
| $I_{6\&{10}}$ |    $S_{24}$     |     R4      |     R4      | $I_{37}$ | $I_{9\&{11}}$ |
| $I_{9\&{11}}$ |                 |     R3      |     R3      |          |               |

### SubQuestion 2: parsing steps

yes , it can accept `aaaa+++`

| order |                       stack                        | signal |    input    |           action           |
| :---- | :------------------------------------------------: | :----: | :---------: | :------------------------: |
| (0)   |                         0                          |        | aaaa+++$\$$ |           Shift            |
| (1)   |                     0 $_{24}$                      |   a    | aaa+++$\$$  |           Shift            |
| (2)   |                  0 $_{24}\ _{24}$                  |   aa   |  aa+++$\$$  |           Shift            |
| (3)   |              0 $_{24}\ _{24}\ _{24}$               |  aaa   |  a+++$\$$   |           Shift            |
| (4)   |           0 $_{24}\ _{24}\ _{24}\ _{24}$           |  aaaa  |   +++$\$$   | Reduce by $B \to \epsilon$ |
| (5)   |           0 $_{24}\ _{24}\ _{24}\ _{24}$           | aaaaB  |   +++$\$$   |     GOTO state $_{58}$     |
| (6)   |       0 $_{24}\ _{24}\ _{24}\ _{24}\ _{58}$        | aaaaB  |   +++$\$$   | Reduce by $S \to \alpha B$ |
| (7)   |           0 $_{24}\ _{24}\ _{24}\ _{37}$           |  aaaS  |   +++$\$$   |           Shift            |
| (8)   |      0 $_{24}\ _{24}\ _{24}\ _{37}\ _{6\&10}$      | aaaS+  |   ++$\$$    | Reduce by $B \to \epsilon$ |
| (9)   |      0 $_{24}\ _{24}\ _{24}\ _{37}\ _{6\&10}$      | aaaS+B |   ++$\$$    |   GOTO state $_{9\&11}$    |
| (10)  | 0 $_{24}\ _{24}\ _{24}\ _{37}\ _{6\&10}\ _{9\&11}$ | aaaS+B |   ++$\$$    |   Reduce by $B \to S+B$    |
| (11)  |           0 $_{24}\ _{24}\ _{24}\ _{58}$           |  aaaB  |   ++$\$$    | Reduce by $S \to \alpha B$ |
| (12)  |              0 $_{24}\ _{24}\ _{37}$               |  aaS   |   ++$\$$    |           Shift            |
| (13)  |         0 $_{24}\ _{24}\ _{37}\ _{6\&10}$          |  aaS+  |    +$\$$    | Reduce by $B \to \epsilon$ |
| (14)  |         0 $_{24}\ _{24}\ _{37}\ _{6\&10}$          | aaS+B  |    +$\$$    |   GOTO state $_{9\&11}$    |
| (15)  |    0 $_{24}\ _{24}\ _{37}\ _{6\&10} \ _{9\&11}$    | aaS+B  |    +$\$$    |   Reduce by $B \to S+B$    |
| (16)  |              0 $_{24}\ _{24}\ _{58}$               |  aaB   |    +$\$$    | Reduce by $S \to \alpha B$ |
| (17)  |                  0 $_{24}\ _{37}$                  |   aS   |    +$\$$    |           Shift            |
| (18)  |             0 $_{24}\ _{37}\ _{6\&10}$             |  aS+   |    $\$$     | Reduce by $B \to \epsilon$ |
| (19)  |             0 $_{24}\ _{37}\ _{6\&10}$             |  aS+B  |    $\$$     |   GOTO state $_{9\&11}$    |
| (20)  |        0 $_{24}\ _{37}\ _{6\&10}\ _{9\&11}$        |  aS+B  |    $\$$     |   Reduce by $B \to S+B$    |
| (21)  |                  0 $_{24}\ _{58}$                  |   aB   |    $\$$     | Reduce by $S \to \alpha B$ |
| (22)  |                        0 1                         |   S    |    $\$$     |            acc             |

<link rel="stylesheet" type="text/css" href="./../markdown.css">
