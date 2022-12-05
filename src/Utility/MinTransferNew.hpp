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

#include "../Resource/GraphPool.hpp"
#include "../Resource/InitializerPool.hpp"
#include "Dijkstra.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
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

    void show_min_transfer_time(const T& source, const T& end) {
        std::cout << "{ " << source << " -> " << end << " } min transfer time is => ";
        auto num_of_diff_category = DijkstraAlgo->Dist[Data->V_Index_Map[end]];
        std::cout << --num_of_diff_category;
        std::cout << std::endl;
        std::cout << std::endl;
    }
    void show_min_transfer_stations(const T& source, const T& end) {
        std::cout << "{ " << source << " -> " << end << " } transfer stations are => ";
        const std::list<T>& transfer_path = DijkstraAlgo->MinRoute[end];
        for (auto&& curr : transfer_path) {
            if (curr == transfer_path.front()
                || curr == transfer_path.back()) {
                continue;
            }
            std::cout << curr << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    void show_detailed_info(const T& source, const T& end) {
        using Resource::GraphPool;

        std::list<T> all_critical
            = DijkstraAlgo->return_shortest_route_between(
                source,
                end
            );

        std::cout << "Here's the detailed route : " << std::endl;

        auto iter  = all_critical.begin();
        auto final = std::prev(all_critical.end());

        while (iter != final) {
            T&                    curr = *iter;
            T&                    next = *(std::next(iter));
            Dijkstra<std::string> temp(*GraphPool<std::string>::getOriginal());
            temp.tiny_query(curr, next);
            iter = std::next(iter);
        }

        std::cout << std::endl;
    }

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
        DijkstraAlgo->execute_algorithm_from(source);
        // 2. show some info
        show_min_transfer_time(source, end);
        show_min_transfer_stations(source, end);
        // 3. show detailed info
        show_detailed_info(source, end); // BUG
    }
};

} // namespace Utility