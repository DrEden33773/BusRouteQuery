/**
 * @file StaticMemberTest.hpp
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
#include <vector>

namespace Test {

struct Something {
    int property = 0;
    ~Something() {
        std::cout << "Destruct something, curr property is " << property << std::endl;
        std::cout << std::endl;
    }
};

class Single {
    static std::shared_ptr<Something> something;

public:
    static void register_with(int a) {
        if (something) {
            something.reset();
        }
        something           = std::make_shared<Something>();
        something->property = a;
        std::cout << "registered with property => " << something->property << std::endl;
        std::cout << std::endl;
    }
    static void change_with(int b) {
        if (!something) {
            register_with(b);
        } else {
            std::cout << "original property => " << something->property << std::endl;
            std::cout << std::endl;
            something->property = b;
            std::cout << "changed property => " << something->property << std::endl;
            std::cout << std::endl;
        }
    }
    static std::shared_ptr<Something> get() {
        std::shared_ptr<Something> ret = something;
        return ret;
    }
    static void show_property() {
        std::cout << "current property => " << something->property << std::endl;
        std::cout << std::endl;
    }
};

std::shared_ptr<Something> Single::something = nullptr;

void StaticMemberTest() {
    Single::register_with(1);
    Single::register_with(2);
    Single::change_with(3);

    std::shared_ptr<Something> temp = Single::get();
    temp->property                  = 1;

    Single::show_property();
}

} // namespace Test