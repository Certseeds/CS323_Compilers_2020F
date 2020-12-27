#!/usr/bin/env python3
# coding=utf-8
'''
Github: https://github.com/Certseeds/CS323_Compilers_2020F
Organization: SUSTech
Author: nanoseeds
Date: 2020-11-03 19:37:49
LastEditors: nanoseeds
LastEditTime: 2020-11-03 20:49:39
'''
import pathlib
import subprocess

DATA = pathlib.Path('data')


def jsonchecker_output(json_file):
    out = subprocess.check_output(['./jc.out', json_file])
    return out.decode().strip()


def check_jsonchecker_correct():
    for datafile in ['citm_catalog', 'twitter']:
        jsonfile = DATA / f'{datafile}.json'
        out = jsonchecker_output(jsonfile)
        print(f'For {jsonfile.name}:', end=' ')
        assert out == '1'
        print('CORRECT')
        print('-' * 80)
    else:
        print('All success!')


def check_jsonchecker_error():
    for casefile in DATA.glob('case_*.json'):
        out = jsonchecker_output(casefile)
        answer = f'duplicate key: "{casefile.name[5:6]}"'
        print(f'For {casefile.name}:', end=' ')
        assert out == answer
        print('CORRECT')
        print('-' * 80)
    else:
        print('All success!')


if __name__ == "__main__":
    check_jsonchecker_error()
    check_jsonchecker_correct()
