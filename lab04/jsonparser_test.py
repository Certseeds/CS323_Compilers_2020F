#!/usr/bin/env python3
# coding=utf-8
'''
Github: https://github.com/Certseeds/CS323_Compilers_2020F
Organization: SUSTech
Author: nanoseeds
Date: 2020-09-29 20:02:46
LastEditors: nanoseeds
LastEditTime: 2020-09-30 01:07:40
'''
import pathlib
import re
import subprocess

DATA = pathlib.Path('data')


def jsonparser_output(json_file):
    out = subprocess.check_output(['./jp.out', json_file])
    return out.decode().strip()


def check_jsonchecker_fail_withlexical():
    data = DATA
    for failjson in data.glob('fail*.json'):
        out = jsonparser_output(failjson)
        if ('lexical error' not in out) or ('_EXCLUDE' in failjson.name):
            continue
        print(f'For file {failjson.name}:')
        print(out)
        print('-' * 80)


def check_jsonchecker_fail_syntaxonly():
    data = DATA
    recovered, total = 0, 0
    for failjson in data.glob('fail*.json'):
        out = jsonparser_output(failjson)
        if ('lexical error' in out) or ('_EXCLUDE' in failjson.name):
            continue
        print(f'For file {failjson.name}:')
        print('-' * 24)
        print(open(failjson).read())
        print('-' * 80)
        print(out)
        print('#' * 80)
        m = re.match(r'^syntax(.*?)recovered$', out)
        recovered += bool(m)
        total += 1
    print(f'Recovered/Total: {recovered}/{total}')


# check_jsonchecker_fail_withlexical()
check_jsonchecker_fail_syntaxonly()
