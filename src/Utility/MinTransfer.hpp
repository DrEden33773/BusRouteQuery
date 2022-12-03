/**
 * @file MinTransfer.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-01
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @warning @b TOO_SLOW!
 * @attention @b Discarded!
 *
 */

#pragma once

#include "../Resource/InitializerPool.hpp"
#include "Graph.hpp"

#include <algorithm>
#include <iostream>
#include <list>
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
    using CVMap    = Resource::CVMap<std::string, std::string>;
    using C_VS_Map = Resource::C_VS_Map<std::string, std::string>;

    const CVMap&    Category_Vex_Map    = *Resource::Category_Vex_Map<std::string, std::string>;
    const C_VS_Map& Category_VexSet_Map = *Resource::Category_VexSet_Map<std::string, std::string>;

    struct VexInfo {
        T                     vex {};
        std::vector<T>        route_to_vex {};
        std::unordered_set<T> visited_vex {};
        int                   transfer_time = 0;

        VexInfo() = default;
        explicit VexInfo(const T& vex)
            : vex(vex) { }
        explicit VexInfo(const T& vex, const std::vector<T>& route_to_vex)
            : vex(vex)
            , route_to_vex(route_to_vex) { }
    };
    struct RouteInfo {
        std::vector<T> route {};
        int            transfer_time = 0;

        RouteInfo() = default;
    };
    std::vector<RouteInfo> available_route {};
    std::vector<RouteInfo> best_route {};

    Graph<T>* Data = nullptr;
    int       size = 0;
    T         source {};
    T         end {};

    std::vector<T> FindAllAdjVex(const T& vex) {
        std::vector<int>&& adj_idx_list
            = Data->FindAllAdjIndex(vex);
        std::vector<T> ret;
        ret.reserve(adj_idx_list.size());
        for (const int& idx : adj_idx_list) {
            ret.emplace_back(
                Data->Index_V_Map[idx]
            );
        }
        return ret;
    }
    T GetCategoryOf(const T& vex) {
        for (auto&& [category, vexes] : Category_VexSet_Map) {
            if (vexes.contains(vex)) {
                return category;
            }
        }
        return T {};
    }

private:
    void show_result() {
        std::cout << "{ " << source << " -> " << end << " } min transfer_time route is => ";
        for (auto&& curr : best_route.front().route) {
            std::cout << curr << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
    void find_min_transfer() {
        // 0. special case
        if (available_route.empty()) {
            return;
        }
        // 1. sort
        std::sort(
            available_route.begin(),
            available_route.end(),
            [](const RouteInfo& lhs, const RouteInfo& rhs) {
                return lhs.transfer_time < rhs.transfer_time;
            }
        );
        // 2. remain the min only
        int  min_transfer_time = available_route.front().transfer_time;
        auto delete_from       = std::find_if(
            available_route.begin(),
            available_route.end(),
            [&min_transfer_time](const RouteInfo& curr) {
                return curr.transfer_time > min_transfer_time;
            }
        );
        available_route.erase(delete_from, available_route.end());
    }
    void find_min_route_in_min_transfer() {
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
    void search() {
        std::queue<VexInfo> queue;
        VexInfo             sourceInfo(source, { source });
        sourceInfo.visited_vex.insert(source);
        queue.push(sourceInfo);

        while (!queue.empty()) {
            size_t curr_level_size = queue.size();
            while (curr_level_size > 0) {
                // 1. get curr_vex
                VexInfo&               curr_info        = queue.front();
                T&                     curr_vex         = curr_info.vex;
                std::unordered_set<T>& curr_visited_vex = curr_info.visited_vex;
                // 2. check if curr_vex == end_vex
                if (curr_vex == end) {
                    // 3. find an available route, stop BFS on this branch
                    RouteInfo an_available_route;
                    an_available_route.route         = curr_info.route_to_vex;
                    an_available_route.transfer_time = curr_info.transfer_time;
                    available_route.push_back(an_available_route);
                } else {
                    // 3. get all adj vex, and join some of them into queue
                    std::vector<T>&& adj_vex_list
                        = FindAllAdjVex(curr_vex);
                    for (const T& adj_vex : adj_vex_list) {
                        if (!curr_visited_vex.contains(adj_vex)) {
                            // build info
                            VexInfo adj_vex_info = curr_info;
                            adj_vex_info.vex     = adj_vex;
                            adj_vex_info.visited_vex.insert(adj_vex);
                            adj_vex_info.route_to_vex.push_back(adj_vex);
                            if (GetCategoryOf(curr_vex) != GetCategoryOf(adj_vex)) {
                                adj_vex_info.transfer_time += 1;
                            }
                            // push_back info
                            queue.push(adj_vex_info);
                        }
                    }
                }
                // 4. remove curr_vex from queue
                queue.pop();
                // 5. update
                --curr_level_size;
            }
        }
    }

public:
    explicit MinTransfer(Utility::Graph<T>& graph)
        : Data(&graph)
        , size(graph.size) {
        // basic check
        Data->make_sure_non_empty();
        Data->make_sure_weighted();
    }
    void query(T& source, T& end) {
        this->source = source;
        this->end    = end;
        search();
        find_min_transfer();
        find_min_route_in_min_transfer();
        show_result();
    }
};

} // namespace Utility