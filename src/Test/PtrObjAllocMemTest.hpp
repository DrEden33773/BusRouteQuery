/**
 * @file PtrObjAllocMemTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <iostream>

namespace Test {

struct HelperStruct {
    unsigned a : 1 = 0;
};

/**
 * @note
        allocate memory for pointer is actually
            redirect the pointer to a `space_allocated` area of heap
        so if @param ptr is a @b `pointer_instance`, only it's direction will be changed
            that's to say, the original `pointer instance`'s direction haven't changed
        the correct way is to set @param ptr as a @b `pointer_instance_ref`
 *
 */
void HelperFunc(HelperStruct*& ptr) {
    ptr = new HelperStruct;
}

void PtrObjAllocMemTest() {
    HelperStruct* toAlloc = nullptr;
    HelperFunc(toAlloc);
    std::cout << toAlloc->a << std::endl;
    std::cout << std::endl;
    delete toAlloc;
}

} // namespace Test