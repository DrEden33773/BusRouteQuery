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

    struct RouteInfo {
        std::vector<T> route {};
        int            transfer_time = 0;

        RouteInfo() = default;
    };
    std::vector<RouteInfo> available_route {};
    std::vector<RouteInfo> best_route {};

    void get_available_route() {
        // TODO(eden):
    }
    void get_best_route() {
        // 0. special case
        if (available_route.empty()) {
            return;
        }
        // 1. sort
        std::sort(
            available_route.begin(),
            available_route.end(),
            [](const RouteInfo& lhs, const RouteInfo& rhs) {
                return lhs.route.size() < rhs.route.size();
            }
        );
        // 2. select the min only
        best_route       = available_route;
        int  min_dist    = best_route.front().route.size();
        auto delete_from = std::find_if(
            best_route.begin(),
            best_route.end(),
            [&min_dist](const RouteInfo& curr) {
                return curr.route.size() > min_dist;
            }
        );
        best_route.erase(delete_from, best_route.end());
    }

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
    }
};

} // namespace Utility