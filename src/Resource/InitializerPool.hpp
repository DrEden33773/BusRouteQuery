/**
 * @file InitializerPool.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Utility/ConceptLib.hpp"
#include "../Utility/Graph.hpp"

#include <memory>
#include <stdexcept>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace Resource {

/// @brief @b Aliases

template <typename T>
using Graph = Utility::Graph<T>;

template <typename T>
using VertexList = typename Graph<T>::VertexList;

template <typename T>
using EdgeList = typename Graph<T>::EdgeList;

template <typename T>
using WEdgeList = typename Graph<T>::WEdgeList; // WEdge = WeightedEdge

template <typename T>
using CategoryList = std::vector<T>;

template <typename T>
using VL = VertexList<T>;

template <typename T>
using El = EdgeList<T>;

template <typename T>
using WEL = WEdgeList<T>; // WE = WeightedEdge

template <typename T>
using CL = CategoryList<T>;

template <typename K, typename V>
using CVMap = std::unordered_map<K, VL<V>>;

template <typename K, typename V>
using CWEMap = std::unordered_map<K, WEL<V>>; // WE = WeightedEdge

/**
 * @brief @b InitializerPool // inline namespace
 *
 */
inline namespace InitializerPool {
    template <typename T>
    requires Utility::StdOut<T>
    static const std::shared_ptr<VL<T>> All_Vex = std::make_shared<VL<T>>();

    template <typename T>
    requires Utility::StdOut<T>
    static const std::shared_ptr<WEL<T>> All_WeightedEdge = std::make_shared<WEL<T>>();

    template <typename T>
    requires Utility::StdOut<T>
    static const std::shared_ptr<CL<T>> All_Category = std::make_shared<CL<T>>();

    template <typename K, typename V>
    requires Utility::StdOut<K> and Utility::StdOut<V>
    static const std::shared_ptr<CVMap<K, V>> Category_Vex_Map = std::make_shared<CVMap<K, V>>();

    template <typename K, typename V>
    requires Utility::StdOut<K> and Utility::StdOut<V>
    static const std::shared_ptr<CWEMap<K, V>> Category_WEdge_Map = std::make_shared<CWEMap<K, V>>();

} // namespace InitializerPool

} // namespace Resource