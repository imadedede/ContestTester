#!/usr/bin/env python3

import sys
import os.path
import codecs
import subprocess

TEST_CASE_EXTENSION     = '.txt'    # テストケーファイルの拡張子
CASE_DELIMITERS         = [         # テストケースファイル内のテストケース区切り
    '__EXAMPLE_SPLITTER\n',
    '__TESTCASE\n',
    '__CASE\n'
]
PAIR_DELIMITERS         = [         # テストケースファイル内の入出力例の区切り
    '__PAIR_SPLITTER\n',
    '__PAIR\n'
]

# テスト対象プログラムの実行時間を制限する
TIMEOUT_COMMAND         = ['timeout', '-k', '1', '5']

# エラーコードを文字列に変換
ERRCODE_TO_STR          = {
    124 : 'TLE',
}

# テスト結果を出力
class ResultPrinter():
    def __init__(self, input, expect, result):
        self.input = input
        self.expect = expect
        self.stdout = result[0]
        self.err = result[1:]
    # OK の時の出力文字列を生成
    def ok(self, input):
        return 'OK!:{}{}'.format(
            '\n' if input.count('\n') > 1 else '', input)
    # NG の時の出力文字列を生成
    def ng(self, input, expect, stdout, stderr, runtime_err):
        output = ('NG...\n{}'
                  '+EXPECT:\n{}'
                  '+BUT:\n{}').format(input, expect, stdout)
        if stderr:
            output += '+stderr:\n{}'.format(stderr)
        if runtime_err:
            err_msg = ''
            if runtime_err in ERRCODE_TO_STR:
                err_msg = ' ' + ERRCODE_TO_STR[runtime_err]
            output += "+Runtime Error:{}{}\n".format(runtime_err, err_msg)
        return output
    # 結果を判定して出力する
    def print(self):
        is_correct = (self.expect == self.stdout) and not self.err[1]
        output = (self.ok(self.input) if is_correct
            else self.ng(self.input, self.expect, self.stdout, *self.err))
        print(output, end='')
        return is_correct

# シェルでプログラムを実行する
class Shell():
    def __init__(self, program_file, stdinput):
        self.program_file = './' + program_file
        self.stdinput = stdinput
    # 実行した結果の標準出力を取得
    def exec(self):
        p = subprocess.Popen(TIMEOUT_COMMAND + [self.program_file],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p.stdin.write(self.stdinput.encode('utf8'))
        out, error = p.communicate()
        return out.decode('utf8'), error.decode('utf8'), p.returncode

# テストケースファイルを読み込む
class ImportTestCase():
    def __init__(self, filename):
        self.filename = filename
    # 区切りフォーマットの検査
    def check_delimiter(self, text, list):
        for delimiter in list:
            if delimiter in text:
                return delimiter
        return None
    # テストケースの取得
    def load_test_cases(self):
        with codecs.open(self.filename, 'r', 'utf8') as file:
            text = file.read()
        # テストケース区切りの検出
        case_delimiter = self.check_delimiter(text, CASE_DELIMITERS)
        if not case_delimiter:
            print('No Test Cases!!!!!!')
            sys.exit()
        # 入出力ペア区切りの検出
        pair_delimiter = self.check_delimiter(text, PAIR_DELIMITERS)
        if not pair_delimiter:
            print('Invalid Format File!!!!!!')
            sys.exit()
        # テストケースの分割
        pre_test_cases = [test_case.split(pair_delimiter)
            for test_case in text.split(case_delimiter)
            if pair_delimiter in test_case]
        # 入出力ペアがそろっていないテストケースを除外
        test_cases = [test_case 
            for test_case in pre_test_cases
            if all(test_case)]
        return test_cases

# 名前がテストケースのファイル名であることを確認する
class TestCaseFile():
    def __init__(self):
        argvs = sys.argv
        self.program = argvs[1] if len(argvs) > 1 else None
    # プログラム名とテストケース名を取得
    def fetch_filename(self):
        # 引数があるか確認
        if not self.program:
            print('No Execution Filename in Argment!!!!!!!!!')
            sys.exit()
        # 引数のファイルが存在するか確認
        program_file = self.program
        test_case_file = os.path.basename(self.program) + TEST_CASE_EXTENSION
        run_ok = os.path.exists(program_file) and os.path.exists(test_case_file)
        if not run_ok:
            print('No such file!!!!!!!')
            sys.exit()
        return program_file, test_case_file

# エントリポイント
if __name__ ==  '__main__':
    # 引数からプログラム名とテストケースファイル名を取得
    program_file, test_case_file = TestCaseFile().fetch_filename()

    # テストケース集をテストケースファイルから取得
    test_cases = ImportTestCase(test_case_file).load_test_cases()

    # テストケースを実行して結果を見本と比較
    all_ok = True
    for input, expect in test_cases:
        result = Shell(program_file, input).exec()
        all_ok = ResultPrinter(input, expect, result).print() and all_ok
    if all_ok:
        print('OK!!! All TestCases are Clear!!!!!!!!!!!!')
