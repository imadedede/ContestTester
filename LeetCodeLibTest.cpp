#include <string>

#include "LeetCodeLib.hpp"

int main(void) {
    using namespace std;
    Converter c;
    Input in;
    Printer p;

    // 文字列の出力
    {
        string s(in.Line());
        p.Any(s);
    }
    {
        string s(in.Line());
        p.Any(s);
    }
    // bool 型の出力
    {
        string s(in.Line());
        p.Any(bool(true));
    }
    {
        string s(in.Line());
        p.Any(bool(false));
    }
    // CSV を vector にパースして出力
    {
        vector<int> v = c.VecStrToVecInt(in.ParseCsvStr());
        p.Vector<int>(v);
    }
    {
        vector<int> v = in.ParseCsv();
        p.Vector<int>(v);
    }
    {
        vector<int> v = in.ParseCsv();
        p.Vector<int>(v);
    }
    // CSV を ListNode にパースして出力
    {
        ListNode *n = in.ParseListNode();
        p.ListNode(n);
    }
    // 数値の取得
    {
        int i = in.Int();
        p.Any(i);
    }
    {
        int i = in.Int();
        p.Any(i);
    }
    {
        int i = in.Int();
        p.Any(i);
    }
    // Input.Int() 入力トークンの直後に改行があっても問題なく動くこと
    {
        vector<int> v = in.ParseCsv();
        p.Vector<int>(v);
    }
    {
        string s = in.Str();
        p.Any(s);
    }
    {
        string s = in.Str();
        p.Any(s);
    }
    {
        string s = in.Str();
        p.Any(s);
    }
    // 行列を取得
    {
        auto vvi = in.ParseCsvVec();
        p.VecVec(vvi);
    }
    // 空行列をプリント
    {
        vector<int> v;
        p.Vector(v);
        vector<vector<int>> vv;
        p.VecVec(vv);
    }
    return 0;
}