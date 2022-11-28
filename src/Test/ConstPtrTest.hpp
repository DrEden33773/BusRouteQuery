/**
 * @file ConstPtrTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <memory>
#include <vector>

namespace Test {

void ConstPtrTest() {
    std::shared_ptr<std::vector<int>> vec_ptr;
    vec_ptr.reset();
}

} // namespace Test