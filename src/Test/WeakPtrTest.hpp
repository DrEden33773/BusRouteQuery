/**
 * @file weak_ptr_test.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <memory>
#include <string>

namespace Test {

struct Teacher;
struct School;

struct Teacher {
    std::string           name;
    std::weak_ptr<School> school;
    ~Teacher() {
        std::cout << "destructed Teacher" << std::endl;
        std::cout << std::endl;
    }
};
struct School {
    std::string            name;
    std::weak_ptr<Teacher> leader;
    ~School() {
        std::cout << "destructed School" << std::endl;
        std::cout << std::endl;
    }
};

void WeakPtrTest() {
    auto university    = std::make_shared<School>();
    auto principal     = std::make_shared<Teacher>();
    university->leader = principal;
    principal->school  = university;
}

} // namespace Test