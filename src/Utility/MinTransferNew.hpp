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
    static constexpr int VEX_PER_LINE = 5;

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

private:
    /**
     * @warning `Discarded_Function`
     */
    void show_detailed_info(const T& source, const T& end) {
        throw std::runtime_error("Called a discarded function!");

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

private:
    std::list<T> give_best_sub_route_between(
        const T& source, const T& end
    ) {
        using Resource::Category_Vex_Map;
        using Resource::Category_VexSet_Map;
        using std::string;

        std::vector<std::list<T>> all_route;
        std::vector<T>            all_common_category;

        // 1. get `all_common_category`
        for (auto&& [Category, VexSet] : *Category_VexSet_Map<string, string>) {
            if (VexSet.contains(source)
                && VexSet.contains(end)) {
                all_common_category.push_back(Category);
            }
        }

        // 2. find route on each `common_category`
        for (auto&& category : all_common_category) {
            std::list<T>    an_route;
            std::vector<T>& full_route = (*Category_Vex_Map<string, string>)[category];

            auto source_iter = std::find(
                full_route.begin(),
                full_route.end(),
                source
            );
            auto end_iter = std::find(
                full_route.begin(),
                full_route.end(),
                end
            );

            if (std::distance(source_iter, end_iter) > 0) {
                // source -> ... -> end
                end_iter = std::next(end_iter);
                for (auto curr_iter = source_iter;
                     curr_iter != end_iter;
                     curr_iter = std::next(curr_iter)) {
                    an_route.push_back(*curr_iter);
                }
            } else {
                // end <- ... <- source
                end_iter = std::prev(end_iter);
                for (auto curr_iter = source_iter;
                     curr_iter != end_iter;
                     curr_iter = std::prev(curr_iter)) {
                    an_route.push_back(*curr_iter);
                }
            }

            all_route.push_back(an_route);
        }

        // 3. find the min_route
        auto min_route_iter = all_route.begin();
        auto curr           = all_route.begin();
        auto ed             = all_route.end();
        while (curr != ed) {
            if (curr->size() < min_route_iter->size()) {
                min_route_iter = curr;
            }
            curr = std::next(curr);
        }

        // 4. export the min_route
        return *min_route_iter;
    }
    void print_list_fmt(const std::list<T>& list) {
        int dist = list.size() - 1;
        int idx  = 0;
        for (auto&& vex : list) {
            if (idx % VEX_PER_LINE == 0) {
                std::cout << std::endl
                          << "\t";
            }
            std::cout << vex << " ";
            ++idx;
        }
        std::cout << "(dist = " << dist << ")";
        std::cout << std::endl;
    }
    void give_detailed_info(const T& source, const T& end) {
        std::cout << "Here's the detailed route : " << std::endl;
        std::list<T> all_critical
            = DijkstraAlgo->return_shortest_route_between(
                source,
                end
            );
        auto iter  = all_critical.begin();
        auto final = std::prev(all_critical.end());
        while (iter != final) {
            T&   curr           = *iter;
            T&   next           = *(std::next(iter));
            auto best_sub_route = give_best_sub_route_between(
                curr,
                next
            );
            print_list_fmt(
                best_sub_route
            );
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
        give_detailed_info(source, end);
    }
};

} // namespace Utility