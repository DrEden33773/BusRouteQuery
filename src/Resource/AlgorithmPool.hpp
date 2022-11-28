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
#include "../Utility/DijkstraPlus.hpp"
#include "../Utility/Floyd.hpp"
#include "../Utility/Graph.hpp"

#include <memory>
#include <stdexcept>

namespace Resource {

template <typename T>
requires Utility::StdOut<T>
class AlgorithmPool {
    using Graph        = Utility::Graph<T>;
    using Floyd        = Utility::Floyd<T>;
    using DijkstraPlus = Utility::DijkstraPlus<T>;

    static std::shared_ptr<Floyd>        Floyd_Algorithm;
    static std::shared_ptr<DijkstraPlus> DijkstraPlus_Algorithm;

    static void UnregisteredFloydException() {
        throw std::runtime_error("You've not registered a Floyd Algorithm!");
    }
    static void UnregisteredDijkstra() {
        throw std::runtime_error("You've not registered a Dijkstra Algorithm!");
    }

public:
    // You can't use ConstructorFunc
    AlgorithmPool() = delete;

    /**
     * @brief Register
     *
     * @param graph
     */
    static void RegisterFloyd(
        Graph& graph
    ) {
        if (Floyd_Algorithm) {
            Floyd_Algorithm.reset();
        }
        Floyd_Algorithm = std::make_shared<Floyd>(graph);
    }
    static void RegisterDijkstra(
        Graph& graph
    ) {
        if (DijkstraPlus_Algorithm) {
            DijkstraPlus_Algorithm.reset();
        }
        DijkstraPlus_Algorithm = std::make_shared<DijkstraPlus>(graph);
    }

    /**
     * @brief get
     *
     * @return auto
     */
    static auto getFloyd() {
        if (!Floyd_Algorithm) {
            UnregisteredFloydException();
        }
        return Floyd_Algorithm;
    }
    static auto getDijkstra() {
        if (!DijkstraPlus_Algorithm) {
            UnregisteredDijkstra();
        }
        return DijkstraPlus_Algorithm;
    }

    /**
     * @brief set
     *
     * @param graph
     */
    static void setFloyd(
        Graph& graph
    ) {
        Floyd_Algorithm.reset();
        Floyd_Algorithm = std::make_shared<Floyd>(graph);
    }
    static void setDijkstra(
        Graph& graph
    ) {
        DijkstraPlus_Algorithm.reset();
        DijkstraPlus_Algorithm = std::make_shared<DijkstraPlus>(graph);
    }
};

} // namespace Resource