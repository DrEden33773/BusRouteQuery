/**
 * @file Query.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Resource/AlgorithmPool.hpp"
#include "../Resource/GraphPool.hpp"
#include "../Utility/FileManager.hpp"
#include "../Utility/Graph.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace Module {

class Querier {
    Querier() = default;
    std::string source;
    std::string end;

    void input() {
        using Resource::AlgorithmPool;
        using Resource::GraphPool;
        using std::string;
        while (true) {
            std::cout << "Please input the `source` and `end` station..." << std::endl;
            std::cout << ">>> ";
            std::cin >> source >> end;
            std::cout << std::endl;
            if (GraphPool<string>::get()->if_has_vex(source)
                && GraphPool<string>::get()->if_has_vex(end)) {
                break;
            } else {
                std::cout << "You've input at least one invalid station! Try again...";
                std::cout << std::endl;
                std::cout << std::endl;
                source.clear();
                end.clear();
            }
        }
    }
    void query() {
        using Resource::AlgorithmPool;

        AlgorithmPool<std::string>::getDijkstra()
            ->query(source, end); // SUCCESS

        AlgorithmPool<std::string>::getMinTransfer()
            ->query(source, end); // BUG
    }

public:
    static void Query() {
        Querier query_process;
        query_process.input();
        query_process.query();
    }
};

} // namespace Module
