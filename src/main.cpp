/**
 * @file main.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Resource/GraphPool.hpp"
#include "Resource/InitializerPool.hpp"

#include "TaskManager.hpp"
#include "Test/RunTests.hpp"

int main(int argc, char** argv) {
    TaskManager::RunAllTasks();
}
