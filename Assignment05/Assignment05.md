<!--
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-11-28 21:10:42
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-11-29 17:39:12
 * @License: CC-BY-NC-SA_V4_0 or any later version 
 -->

# CS323 Assignment 5

**Name**: nanoseeds  
**SID**: \*\*\*\*\*\*\*\*

## Question 1:

For the SDD in `Figure 1`, give annotated parse trees for the following expressions:

1. (3 + 4) ∗ (5 + 6)n [20 points]
2. 1 ∗ 2 ∗ 3 ∗ (4 + 5)n [20 points]
3. (9 + 8 ∗ (7 + 6) + 5) ∗ 4n [20 points]

| PRODUCTION                           |                   SEMANTIC RULES |
| :----------------------------------- | -------------------------------: |
| $1)\space L \to E \space \textbf{n}$ |                  $L.val = E.val$ |
| $2)\space E \to E_{1} + T$           |      $E.val = E_{1}.val + T.val$ |
| $3)\space E \to T$                   |                  $E.val = T.val$ |
| $4)\space T \to T_{1} * F$           |      $T.val = T_{1}.val * F.val$ |
| $5)\space T \to F$                   |                  $T.val = F.val$ |
| $6)\space F \to (E)$                 |                  $F.val = E.val$ |
| $7)\space F \to \textbf{digit}$      | $F.val = \textbf{digit}.lexval;$ |


<div><div>Figure 1: Syntax-directed definition of a simple desk calculator</div></div>

## Answer_of_Question1

### PART1: $(3 + 4) ∗ (5 + 6)n$

<object data="./Question1_01.html" type="text/x-scriptlet" width=100% height=1000></object>

### PART2: $1 ∗ 2 ∗ 3 ∗ (4 + 5)n$

<embed src="./Question1_02.html" type="image/svg+xml" width=125% height=1000 />


### PART3: $(9+8*(7+6)+5)*4n$

<embed src="./Question1_03.html" type="image/svg+xml" width=125% height=1250 />

## Question 2:

What are all the topological sorts for the dependency graph of `Figure 2`?

One sort mentioned during lecture is 1, 2, 3, . . . , 9 (slide #16 of Chapter 4). [20 points]

<div>
  <img src="./Question2_01.png"><br />
  <div>Figure 2: A dependency graph</div>
</div>

## Answer_of_Question2

First, The $ PRODUCTION \space AND \space RULES$ is

| PRODUCTION                      |                                    SEMANTIC RULES |
| :------------------------------ | ------------------------------------------------: |
| $1)\space T \to FT'$            |                    $T'.inh=F.val \\ T.val=T'.syn$ |
| $2)\space T' \to *FT'_{1}$      | $T'_{1}.inh=T'.inh × F.val \\ T'.syn =T'_{1}.syn$ |
| $3)\space T' \to \epsilon$      |                                  $T'.syn =T'.inh$ |
| $4)\space F \to \textbf{digit}$ |                     $F.val=\textbf{digit}.lexval$ |


<div><div>Figure 3: An SDD based on a grammar suitable for top-down parsing</div></div>

THEN from the dependency graph, we can find the relation between nodes.

| before | after |
| :----- | ----: |
| 1      |     3 |
| 2      |     4 |
| 3      |     5 |
| 5      |     6 |
| 4      |     6 |
| 6      |     7 |
| 7      |     8 |
| 8      |     9 |

<div><div>Figure 4: order of nodes</div></div>

then we rewrite it as a input file

``` input
9 8
1 3
2 4
3 5
5 6
4 6
6 7
7 8
8 9

```

we use a Question2.cpp to slovthis question

``` cpp
/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-11-29 14:31:17
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-11-29 16:08:43
 */
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
using input_f = vector<std::pair<int, int>>;
using output_f = unordered_set<string>;
static input_f input;
static int number;
static output_f output;
static output_f nextoutput;
auto input_func = [] {
    int lines;
    std::cin >> number >> lines;
    input.resize(lines);
    for (auto &&i : input) {
        std::cin >> i.first >> i.second;
        i.first -= 1;
        i.second -= 1;
    }
    return 0;
}();
auto output_func = []() {
    for (auto &i: output) {
        string j(i);
        transform(j.begin(), j.end(), j.begin(), [](auto r) { return static_cast<char>(r + 1); });
        std::cout << "[ ";
        std::copy(j.begin(), j.end(), ostream_iterator<char>(cout, ", "));
        std::cout << "\b\b ";
        std::cout << "]," << std::endl;
    }
};

void toposort(const input_f &input);

int main() {
    toposort(input);
    output_func();
    return 0;
}

void toposort(const input_f &input) {
    vector<int> in(number, 0);
    for (const auto &i : input) {
        in[i.second]++;  // 计算入度
    }
    string begin = "";
    output.insert(begin);
    for (int order = 0; order < number; order++) {
        for (const auto &i : output) {
            //std::cout << i << std::endl;
            vector<int> tempin(in);
            for (const auto& j : i) {
                auto num = j - '0';
                for (const auto &k : input) {
                    if (k.first == num) {
                        tempin[k.second]--;
                        /* code */
                    }
                }
            }
            for (const auto& j : i) {
                tempin[j - '0'] = -1;
            }
            for (size_t j = 0; j < tempin.size(); j++) {
                if (tempin[j] == 0) {
                    nextoutput.insert(string(i).append(string(1, j + '0')));
                }
            }
        }
        std::swap(output, nextoutput);
        nextoutput.clear();
    }
}
```

then `g++ ./Question2.cpp -o q2.out;./q2.out < Question2.in`.

we got output:

``` output
[ 1, 2, 4, 3, 5, 6, 7, 8, 9 ],
[ 1, 3, 2, 4, 5, 6, 7, 8, 9 ],
[ 2, 1, 4, 3, 5, 6, 7, 8, 9 ],
[ 2, 4, 1, 3, 5, 6, 7, 8, 9 ],
[ 1, 3, 2, 5, 4, 6, 7, 8, 9 ],
[ 2, 1, 3, 4, 5, 6, 7, 8, 9 ],
[ 2, 1, 3, 5, 4, 6, 7, 8, 9 ],
[ 1, 2, 3, 5, 4, 6, 7, 8, 9 ],
[ 1, 3, 5, 2, 4, 6, 7, 8, 9 ],
[ 1, 2, 3, 4, 5, 6, 7, 8, 9 ],
```

## Question 3:

Below is a grammar for expressions involving operator $+$ and integer or floating-point operands. Floating-point numbers are distinguished by having a decimal point. Give an SDD to determine the type of each term $T$ and expression $E$. [20 points]

$$E \to E + T | T$$
$$T \to \textbf{num} \cdot \textbf{num} | \textbf{num}$$

## Answer_of_Question3

first of all, there just exist double type: int and float.  
second, each node just need to caclucate `*.type`

| PRODUCTION                    |                        SEMANTIC RULES |
| :---------------------------- | ------------------------------------: |
| $1)\space E \to E+T$          | $E.type=(E.type==float?float:F.type)$ |
| $2)\space E \to T$            |                       $E.type=T.type$ |
| $4)\space T \to T.T$          |                        $T.type=float$ |
| $4)\space T \to \textbf{num}$ |                          $T.type=int$ |


<link rel="stylesheet" type="text/css" href="./../markdown.css">

<style type="text/css">
h3{
  text-align: center;
}
</style>
