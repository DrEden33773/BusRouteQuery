/**
 * @file GraphPool.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Utility/ConceptLib.hpp"
#include "../Utility/Graph.hpp"

#include <memory>
#include <stdexcept>

namespace Resource {

template <typename T>
requires Utility::StdOut<T>
class GraphPool {
    using Graph      = Utility::Graph<T>;
    using WEdgeList  = typename Graph::WEdgeList;
    using VertexList = typename Graph::VertexList;
    using WEL        = WEdgeList;
    using VL         = VertexList;

    static std::shared_ptr<Graph> OriginalGraph;
    static std::shared_ptr<Graph> TransferGraph;

    static void Unregistered_Original_Exception() {
        throw std::runtime_error("You've not registered Original_Graph!");
    }
    static void Unregistered_Transfer_Exception() {
        throw std::runtime_error("You've not registered Transfer_Specialized_Graph!");
    }

public:
    // You can't use ConstructorFunc
    GraphPool() = delete;

    /// @brief @b Register
    static void RegisterOriginal(
        const VL&   vl,
        const WEL&  wel,
        const bool& directed = false
    ) {
        if (OriginalGraph) {
            OriginalGraph.reset();
        }
        OriginalGraph = std::make_shared<Graph>(vl, wel, directed);
    }
    static void RegisterTransfer(
        const VL&   vl,
        const WEL&  wel,
        const bool& directed = false
    ) {
        if (TransferGraph) {
            TransferGraph.reset();
        }
        TransferGraph = std::make_shared<Graph>(vl, wel, directed);
    }

    /// @brief @b get
    static std::shared_ptr<Graph> getOriginal() {
        if (!OriginalGraph) {
            Unregistered_Original_Exception();
        }
        return OriginalGraph;
    }
    static std::shared_ptr<Graph> getTransfer() {
        if (!TransferGraph) {
            Unregistered_Transfer_Exception();
        }
        return TransferGraph;
    }

    /// @brief @b set
    static void setOriginal(
        const VL&   vl,
        const WEL&  el,
        const bool& directed = false
    ) {
        OriginalGraph.reset();
        OriginalGraph = std::make_shared<Graph>(vl, el, directed);
    }
    static void setTransfer(
        const VL&   vl,
        const WEL&  el,
        const bool& directed = false
    ) {
        TransferGraph.reset();
        TransferGraph = std::make_shared<Graph>(vl, el, directed);
    }
};

template <typename T>
requires Utility::StdOut<T>
std::shared_ptr<Utility::Graph<T>> GraphPool<T>::OriginalGraph = nullptr;

template <typename T>
requires Utility::StdOut<T>
std::shared_ptr<Utility::Graph<T>> GraphPool<T>::TransferGraph = nullptr;

} // namespace Resource