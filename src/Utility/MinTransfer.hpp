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
#include <utility>
#include <vector>

namespace Utility {

template <typename T>
class MinTransfer {
    using CVMap_t = Resource::CVMap<std::string, std::string>;

    const CVMap_t& Category_Vex_Map = *Resource::Category_Vex_Map<std::string, std::string>;

    struct VexInfo {
        T              vex {};
        std::vector<T> route_to_vex {};
        int            transfer_time = 0;

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

private:
    void show_result() {
    }
    void search() {
        std::unordered_set<T> visited_vex;
        std::queue<VexInfo>   queue;
        queue.push(VexInfo(source, { source }));
        visited_vex.insert(source);

        while (!queue.empty()) {
            size_t curr_level_size = queue.size();
            while (curr_level_size > 0) {
                // 1. get curr_vex
                VexInfo& curr_info = queue.front();
                T&       curr_vex  = curr_info.vex;
                // 2. check if curr_vex == end_vex
                if (curr_vex == end) {
                }
                // 3. get all adj vex
                std::vector<T>&& adj_vex_list
                    = FindAllAdjVex(curr_vex);

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
        show_result();
    }
};

} // namespace Utility