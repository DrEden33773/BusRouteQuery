/**
 * @file TaskManager.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-03
 *
 * @copyright Copyright (c) 2022
 *
 */

// #include "Module/PreExecuter.hpp"
#include "Module/Initializer.hpp"
#include "Module/Query.hpp"
#include "Module/Register.hpp"

namespace TaskManager {

void RunAllTasks() {
    // using Module::PreExecuter;
    using Module::Initializer;
    using Module::Querier;
    using Module::Register;

    Initializer::Init();
    Register::Registry();
    Querier::Query();
}

} // namespace TaskManager
