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

private:
    void AdjustTransferGraph() {
        using Resource::GraphPool;
        using Resource::InitializerPool::Category_Vex_Map;
        using Resource::InitializerPool::Category_VexSet_Map;
        using std::string;

        auto& TransferGraph = *GraphPool<string>::getTransfer();

        for (auto&& [_, vexes] : *Category_Vex_Map<string, string>) {
            size_t size = vexes.size();
            for (size_t from = 0; from < size; ++from) {
                for (size_t to = from; to < size; ++to) {
                    const string& from_vex = vexes[from];
                    const string& to_vex   = vexes[to];
                    // insert arc on a undirected graph
                    TransferGraph.InsertArc(from_vex, to_vex, 1);
                }
            }
        }
    }

private:
    void register_OriginalGraph() {
        std::cout << "Now, register `Original Graph`...";
        std::cout << std::endl
                  << std::endl;

        Resource::GraphPool<std::string>::RegisterOriginal(
            *Resource::InitializerPool::All_Vex<std::string>,
            *Resource::InitializerPool::All_WeightedEdge<std::string>,
            false
        );

        std::cout << "Successfully registered `Original Graph`!";
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
        std::cout << "Start to register `Transfer Graph`...";
        std::cout << std::endl
                  << std::endl;

        // 1. copy the OriginalGraph
        Resource::GraphPool<std::string>::RegisterTransfer(
            *Resource::InitializerPool::All_Vex<std::string>,
            *Resource::InitializerPool::All_WeightedEdge<std::string>,
            false
        );
        // 2. adjust
        AdjustTransferGraph();

        std::cout << "Successfully registered `Transfer Graph`!";
        std::cout << std::endl
                  << std::endl;
    }

public:
    static void Registry() {
        Register Registry_Process;
        Registry_Process.register_OriginalGraph(); // success
        Registry_Process.register_Dijkstra();      // success
        Registry_Process.register_TransferGraph(); // success
        Registry_Process.register_MinTransfer();   // success
    }
};

} // namespace Module