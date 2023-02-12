/**
 * @file RunTests.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "ChineseCharTest.hpp"
#include "InitializerTest.hpp"
#include "PtrObjAllocMemTest.hpp"
#include "StaticMemberTest.hpp"

#include <functional>
#include <iostream>
#include <string>

namespace Test {

static const std::vector<std::function<void()>> AllTest {
    // StaticMemberTest,
    // ChineseCharTest,
    // PtrObjAllocMemTest,
    InitializerTest,
};

void RunTests() {
    for (auto&& func : AllTest) {
        func();
    }
}

} // namespace Test