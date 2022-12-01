/**
 * @file main.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Resource/GraphPool.hpp"
#include "Resource/InitializerPool.hpp"

#include "Test/RunTests.hpp"

#include <string>
#include <utility>
#include <vector>

class issues {
    static std::vector<std::pair<int, char>> codeInfo;

    static bool comparision_policy(
        std::pair<int, char>& a,
        std::pair<int, char>& b
    ) {
        return a.first < b.first;
    }
    static void method_a() {
        std::sort(
            codeInfo.begin(),
            codeInfo.end(),
            [](
                std::pair<int, char>& a,
                std::pair<int, char>& b
            ) -> bool {
                return a.first < b.first;
            }
        );
    }
    static void method_b() {
        std::sort(
            codeInfo.begin(),
            codeInfo.end(),
            comparision_policy
        );
    }
};

int main(int argc, char** argv) {
    Test::RunTests();
}
