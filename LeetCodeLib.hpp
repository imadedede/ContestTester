/*
 * LeetCode 用ライブラリ
 * C++14
*/
#ifndef LEETCODE_LIB_HPP
#define LEETCODE_LIB_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include <string>

// 標準リスト
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 連続するデータ構造を変換する
class Converter {
public:
    // vector<int> を ListNode に変換
    ListNode *VecToListNode(const std::vector<int> &v) const {
        if (v.empty()) return nullptr;
        ListNode *head = new ListNode(v[0], nullptr);
        ListNode *p = head;
        for (std::size_t i = 1; i < v.size(); i++) {
            ListNode *next = new ListNode(v[i], nullptr);
            p->next = next;
            p = next;
        }
        return head;
    }

    // ListNode を vector<int> に変換
    std::vector<int> ListNodeToVec(const ListNode *node) const {
        std::vector<int> v;
        for (auto n = node; n != nullptr; n = n->next) {
            v.push_back(n->val);
        }
        return v;
    }

    // vector<str> を vector<int> に変換
    std::vector<int> VecStrToVecInt(const std::vector<std::string> &vs) const {
        std::vector<int> v;
        v.reserve(vs.size());
        for (const std::string &elm: vs) {
            v.emplace_back(std::stoi(elm));
        }
        return v;
    }
};

// 標準入力を処理する
class Input {
public:
    // 入力文字列を一行取得
    std::string Line() const {
        std::string line;
        getline(std::cin, line);
        return line;
    }

    // 入力トークンを string 型として取得
    std::string Str() const {
        std::string s;
        std::cin >> s;
        // 次が Input::Line() でも呼び出せるように直後の改行を捨てる
        if (std::cin.peek() == '\n') {
            std::cin.ignore();
        }
        return s;
    }

    // 入力トークンを int 型として取得
    int Int() const {
        return std::stoi(Str());
    }

    // 文字列に括弧があれば削る
    std::string DeleteBracket(const std::string &s) const {
        if (s.size() == 0) return s;
        const std::size_t open_index = (s[0] == '[' ? 1 : 0);
        const std::size_t s_size =
            s.size() - (s[s.size() - 1] == ']' ? 1 : 0) - open_index;
        return s.substr(open_index, s_size);
    }

    // 入力文字列を CSV と解釈して vector<string> 配列に格納して返す
    std::vector<std::string> ParseCsvStr() const {
        std::istringstream iss {DeleteBracket(Line())};
        std::vector<std::string> v;
        std::string s;
        while (getline(iss, s, ',')) {
            v.push_back(s);
        }
        return v;
    }

    // 入力文字列を CSV と解釈して vector<int> 配列に格納して返す
    std::vector<int> ParseCsv() const {
        return Converter().VecStrToVecInt(ParseCsvStr());
    }

    // 入力文字列を CSV と解釈して ListNode リストに格納して返す
    ListNode *ParseListNode() const {
        return Converter().VecToListNode(ParseCsv());
    }

    // 複数行 CSV を vector<vector<int>> にまとめて返す
    std::vector<std::vector<int>> ParseCsvVec() const {
        Input in;
        const int rows = in.Int();
        std::vector<std::vector<int>> vvi;
        for (int i = 0; i < rows; i++) {
            vvi.push_back(in.ParseCsv());
        }
        return vvi;
    }
};

// 標準出力する
class Printer {
public:
    template <class Container>
    void Con(const Container &c) const {
        if (c.cbegin() == c.cend()) {
            std::cout << "[]\n";
            return;
        }
        auto iter = c.cbegin();
        std::cout << "[" << *iter;
        for (iter++; iter != c.cend(); iter++) {
            std::cout << "," << *iter;
        }
        std::cout << "]\n";
    }

    // std::vector<T> の中身を出力
    template<typename T>
    void Vector(const std::vector<T> &v) const {
        Con(v);
    }

    // std::vector<vector<T> の中身を出力
    template<typename T>
    void VecVec(const std::vector<std::vector<T>> &vv) const {
        if (vv.empty()) {
            std::cout << "\n";
            return;
        }
        for (const auto &v: vv) {
            Vector(v);
        }
    }

    // ListNode の中身を出力
    void ListNode(const ListNode* node) const {
        Converter c;
        Vector<int>(c.ListNodeToVec(node));
    }

    // 値を出力
    template<typename T>
    void Any(T x) const {
        std::cout << x << "\n";
    }

    // 真偽値だけ特殊化
    template<>
    void Any(bool x) const {
        std::cout << (x ? "true" : "false") << "\n";
    }
};

#endif // LEETCODE_LIB_HPP
