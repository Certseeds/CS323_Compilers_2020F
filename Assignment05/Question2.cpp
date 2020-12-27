/*
 * @Github: https://github.com/Certseeds/CS323_Compilers_2020F
 * @Organization: SUSTech
 * @Author: nanoseeds
 * @Date: 2020-11-29 14:31:17
 * @LastEditors: nanoseeds
 * @LastEditTime: 2020-12-15 21:07:53
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