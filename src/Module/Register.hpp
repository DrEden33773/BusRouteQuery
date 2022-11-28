/**
 * @file Register.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Resource/AlgorithmPool.hpp"
#include "../Resource/GraphPool.hpp"
#include "../Resource/InitializerPool.hpp"
#include "../Utility/FileManager.hpp"
#include "../Utility/Graph.hpp"

#include <iostream>
#include <stdexcept>

namespace Module {

class Register {
    using Graph   = Utility::Graph<std::string>;
    using Floyd   = Utility::Floyd<std::string>;
    using fs_path = std::filesystem::path;

    void register_Graph() {
        std::cout << "Now, register `graph` with `vertex_list` and `weighted_edge_list`...";
        std::cout << std::endl
                  << std::endl;
        Resource::GraphPool<std::string>::Register(
            *Resource::InitializerPool::All_Vex<std::string>,
            *Resource::InitializerPool::All_WeightedEdge<std::string>,
            false
        );
        std::cout << "Successfully registered `graph`!";
        std::cout << std::endl
                  << std::endl;
    }
    void register_Floyd() {
        std::cout << "Floyd Algorithm has been discarded, request has been ignored...";
        std::cout << std::endl
                  << std::endl;
    }
    void register_Dijkstra() {
        std::cout << "Start to register `Dijkstra Algorithm Plus`...";
        std::cout << std::endl
                  << std::endl;
        Resource::AlgorithmPool<std::string>::RegisterDijkstra(
            *Resource::GraphPool<std::string>::get()
        );
        std::cout << "Successfully registered `Dijkstra Algorithm Plus`!";
        std::cout << std::endl
                  << std::endl;
    }

public:
    static void Registry() {
        Register Registry_Process;
        Registry_Process.register_Graph();
    }
};

} // namespace Module