/**
 * @file Executer.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Resource/AlgorithmPool.hpp"
#include "../Resource/GraphPool.hpp"
#include "../Utility/FileManager.hpp"
#include "../Utility/Graph.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <utility>

namespace Module {

class Executer {
    using fs_path = std::filesystem::path;

    void execute_Floyd() {
        std::cout << "Floyd Algorithm has been discarded, request has been ignored...";
        std::cout << std::endl
                  << std::endl;
    }
    void execute_Dijkstra() {
        std::cout << "Now, execute `Dijkstra Algorithm Plus` for later query...";
        std::cout << std::endl
                  << std::endl;

        Resource::AlgorithmPool<std::string>::getDijkstra()->execute_algorithm();

        std::cout << "Done!";
        std::cout << std::endl
                  << std::endl;
    }

public:
    static void Exec() {
        Executer Exec_Process;
        Exec_Process.execute_Dijkstra();
    }
};

} // namespace Module