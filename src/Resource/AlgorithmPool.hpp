/**
 * @file AlgorithmPool.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Utility/ConceptLib.hpp"
#include "../Utility/Dijkstra.hpp"
#include "../Utility/Graph.hpp"
#include "../Utility/MinTransferNew.hpp"

#include <memory>
#include <stdexcept>

namespace Resource {

template <typename T>
requires Utility::StdOut<T>
class AlgorithmPool {
    using Graph       = Utility::Graph<T>;
    using Dijkstra    = Utility::Dijkstra<T>;
    using MinTransfer = Utility::MinTransfer<T>;

    static std::shared_ptr<Dijkstra>    Dijkstra_Algorithm;
    static std::shared_ptr<MinTransfer> MinTransfer_Algorithm;

    static void UnregisteredDijkstra() {
        throw std::runtime_error("You've not registered a Dijkstra Algorithm!");
    }
    static void UnregisteredMinTransfer() {
        throw std::runtime_error("You've not registered a MinTransfer Algorithm!");
    }

public:
    // You can't use ConstructorFunc
    AlgorithmPool() = delete;

    /**
     * @brief Register
     *
     * @param graph
     */
    static void RegisterDijkstra(Graph& graph) {
        if (Dijkstra_Algorithm) {
            Dijkstra_Algorithm.reset();
        }
        // DijkstraPlus_Algorithm = std::make_shared<DijkstraPlus>(graph);
        Dijkstra_Algorithm = std::make_shared<Dijkstra>(graph);
    }
    static void RegisterMinTransfer(Graph& graph) {
        if (MinTransfer_Algorithm) {
            MinTransfer_Algorithm.reset();
        }
        MinTransfer_Algorithm = std::make_shared<MinTransfer>(graph);
    }

    /**
     * @brief get
     *
     * @return auto
     */
    static auto getDijkstra() {
        if (!Dijkstra_Algorithm) {
            UnregisteredDijkstra();
        }
        return Dijkstra_Algorithm;
    }
    static auto getMinTransfer() {
        if (!MinTransfer_Algorithm) {
            UnregisteredMinTransfer();
        }
        return MinTransfer_Algorithm;
    }

    /**
     * @brief set
     *
     * @param graph
     */
    static void setDijkstra(Graph& graph) {
        Dijkstra_Algorithm.reset();
        Dijkstra_Algorithm = std::make_shared<Dijkstra>(graph);
    }
    static void setMinTransfer(Graph& graph) {
        MinTransfer_Algorithm.reset();
        MinTransfer_Algorithm = std::make_shared<MinTransfer>(graph);
    }
};

template <typename T>
requires Utility::StdOut<T>
std::shared_ptr<Utility::Dijkstra<T>> AlgorithmPool<T>::Dijkstra_Algorithm = nullptr;

template <typename T>
requires Utility::StdOut<T>
std::shared_ptr<Utility::MinTransfer<T>> AlgorithmPool<T>::MinTransfer_Algorithm = nullptr;

} // namespace Resource