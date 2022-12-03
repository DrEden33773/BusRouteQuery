/**
 * @file MinTransferNew.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Resource/InitializerPool.hpp"
#include "Dijkstra.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <queue>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Utility {

template <typename T>
class MinTransfer {
    std::unique_ptr<Dijkstra<T>> DijkstraAlgo = nullptr;
    Graph<T>*                    Data         = nullptr;
    int                          size         = 0;

public:
    explicit MinTransfer(Utility::Graph<T>& graph)
        : Data(&graph)
        , size(graph.size) {
        // basic check
        Data->make_sure_non_empty();
        Data->make_sure_weighted();
        // register DijkstraAlgo
        DijkstraAlgo = std::make_unique<Dijkstra<T>>(*Data);
    }

public:
    void query(const T& source, const T& end) {
        // 1. do basic query
        DijkstraAlgo->query(source, end);
        // 2. transfer
    }
};

} // namespace Utility