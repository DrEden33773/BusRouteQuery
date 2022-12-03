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

    void register_OriginalGraph() {
        std::cout << "Now, register `graph` with `vertex_list` and `weighted_edge_list`...";
        std::cout << std::endl
                  << std::endl;
        Resource::GraphPool<std::string>::RegisterOriginal(
            *Resource::InitializerPool::All_Vex<std::string>,
            *Resource::InitializerPool::All_WeightedEdge<std::string>,
            false
        );
        std::cout << "Successfully registered `graph`!";
        std::cout << std::endl
                  << std::endl;
    }
    void register_Dijkstra() {
        std::cout << "Start to register `Dijkstra Algorithm`...";
        std::cout << std::endl
                  << std::endl;
        Resource::AlgorithmPool<std::string>::RegisterDijkstra(
            *Resource::GraphPool<std::string>::getOriginal()
        );
        std::cout << "Successfully registered `Dijkstra Algorithm`!";
        std::cout << std::endl
                  << std::endl;
    }
    void register_MinTransfer() {
        std::cout << "Start to register `MinTransfer Algorithm`...";
        std::cout << std::endl
                  << std::endl;
        Resource::AlgorithmPool<std::string>::RegisterMinTransfer(
            *Resource::GraphPool<std::string>::getTransfer()
        );
        std::cout << "Successfully registered `MinTransfer Algorithm`!";
        std::cout << std::endl
                  << std::endl;
    }

    /// @b core
    void register_TransferGraph() {
    }

public:
    static void Registry() {
        Register Registry_Process;
        Registry_Process.register_OriginalGraph();
        Registry_Process.register_Dijkstra();
    }
};

} // namespace Module