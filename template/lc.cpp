/**
 * 
 * 
 */

#include "LeetCodeLib.hpp"

#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <utility>
#include <array>
#include <unordered_map>

// 以下、提出部分
using namespace std;
class Solution {
public:
    int answer(const string &s) {
        return s.size();
    }
};
// 以上、提出部分

// エントリポイント
int main(void) {
    using namespace std;
    Input in;
    Printer p;

    auto s = in.Line();
    auto ans = Solution().answer(s);

    p.Any(ans);
    return 0;
}
