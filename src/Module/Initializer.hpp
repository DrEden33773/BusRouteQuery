/**
 * @file Initializer.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-11-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Resource/GraphPool.hpp"
#include "../Resource/InitializerPool.hpp"
#include "../Utility/FileManager.hpp"
#include "../Utility/Graph.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <utility>

namespace Module {

class Initializer {
    using Graph      = Utility::Graph<std::string>;
    using EdgeList   = Graph::EdgeList;
    using WEdgeList  = Graph::WEdgeList;
    using VertexList = Graph::VertexList;
    using El         = EdgeList;
    using WEL        = WEdgeList;
    using VL         = VertexList;
    using fs_path    = std::filesystem::path;

    const fs_path& src_path      = Utility::FileManager::Filename::SourceFile;
    const fs_path& test_src_path = Utility::FileManager::Filename::TestSrcFile;

    fs_path      old_src_path;
    std::fstream src_file;

    /// @brief @b Parser
private:
    std::unordered_set<char> number {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
    };
    std::unordered_set<char> splitter {
        ',',
    };
    void vex_splitter(
        const std::string&     receiver,
        std::set<std::string>& all_vex_set
    ) {
        using Resource::All_Category;
        using Resource::All_Vex;
        using Resource::All_WeightedEdge;
        using Resource::Category_Vex_Map;
        using Resource::Category_WEdge_Map;

        std::string              vex;
        std::vector<std::string> curr_category_vex;
        for (const char& curr : receiver) {
            if (!splitter.contains(curr)) {
                // still don't get a vex
                vex.push_back(curr);
            } else {
                // get a vex, push it
                curr_category_vex.push_back(vex);
                all_vex_set.insert(vex);
                // and join a category
                std::string the_category = All_Category<std::string>->back();
                Category_Vex_Map<
                    std::string, std::string>
                    ->insert(std::make_pair(
                        the_category,
                        curr_category_vex
                    ));
                // clear the vex
                vex.clear();
                // clear curr_category_vex
                curr_category_vex.clear();
            }
        }
        // now, there must be a vex unjoined
        curr_category_vex.push_back(vex);
        all_vex_set.insert(vex);
        // get current category
        std::string the_category = All_Category<std::string>->back();
        // join the last vex into category
        Category_Vex_Map<
            std::string, std::string>
            ->insert(std::make_pair(
                the_category,
                curr_category_vex
            ));
        vex.clear();
        curr_category_vex.clear();
        // category_vex is ready

        // now deal with edge
        for (size_t i = 0; i < curr_category_vex.size() - 1; ++i) {
            const std::string& from_vex = curr_category_vex.at(i);
            const std::string& to_vex   = curr_category_vex.at(i + 1);
            All_WeightedEdge<std::string>->push_back(
                std::make_tuple(from_vex, to_vex, 1)
            );
        }

        // now join all the edges into `category_edge_map`
        Category_WEdge_Map<
            std::string, std::string>
            ->insert(
                std::make_pair(
                    the_category,
                    *All_WeightedEdge<std::string>
                )
            );
    }
    void parser() {
        using Resource::All_Category;
        using Resource::All_Vex;

        std::string           receiver;
        std::set<std::string> all_vex_set;

        while (src_file >> receiver) {
            if (number.contains(receiver.front())) {
                // received category
                Resource::All_Category<std::string>->push_back(receiver);
                receiver.clear();
            } else {
                vex_splitter(receiver, all_vex_set);
            }
        }
        // now, only have to deal with `All_Vex`
        // `all_vex_set` is ordered
        for (auto&& curr_vex : all_vex_set) {
            Resource::All_Vex<std::string>->push_back(curr_vex);
        }
        // Initialized:
        //      All_Vex
        //      All_Category
        //      All_WeightedEdge
        //      Category_Vex_Map
        //      Category_WEdge_Map
    }

    /// @brief @b FileOpt
private:
    bool if_need_to_move_src = true;
    void locate_origin_src() {
        bool if_opt_source_exist = std::filesystem::exists(src_path);
        if (if_opt_source_exist) {
            bool if_opt_source_empty = std::filesystem::is_empty(src_path);
            if (!if_opt_source_empty) {
                // should not ReLocate the src
                if_need_to_move_src = false;
                return;
            }
        }
        while (true) {
            std::cout << "Please input the `Path` of source file " << std::endl;
            std::cout << R"( E.G. => C:/Path/Name.txt | C:\\Path\\Name.txt )" << std::endl;
            std::cout << ">>> ";
            std::cin >> old_src_path;
            if (!std::filesystem::exists(old_src_path)) {
                std::cout << "Input path DO NOT EXIST! Please try again... " << std::endl;
                std::cout << std::endl;
                old_src_path.clear();
            } else {
                std::cout << std::endl;
                break;
            }
        }
    }
    void copy_to_src() {
        if (!if_need_to_move_src) {
            return;
        }
        Utility::FileManager::copy_source_file_from(old_src_path);
        std::cout << "Successfully get source file. It had been moved to: " << std::endl;
        std::cout << "\t" << src_path << std::endl;
        std::cout << std::endl;
    }
    void scan_src() {
        src_file.open(src_path, std::fstream::in);
        if (!src_file.is_open()) {
            throw std::runtime_error("Cannot open Source File!");
        }
        parser();
        src_file.close();
    }

private:
    void make_test_src() {
        using std::string;
        string category_1 = "1路";
        string category_2 = "2路";
        string category_3 = "3路";
        string route_1    = "A,B,C";
        string route_2    = "B,D,E";
        string route_3    = "D,E,F";

        std::vector<std::pair<string, string>> info {
            {"1路",  "A,B,C"},
            { "2路", "B,D,E"},
            { "3路", "D,E,F"},
        };

        src_file.open(test_src_path, std::fstream::out);
        if (!src_file.is_open()) {
            throw std::runtime_error("Cannot open Source File!");
        }
        for (auto&& [category, route] : info) {
            src_file << category << " " << route << std::endl;
        }
        src_file.close();
    }
    void scan_test_src() {
        src_file.open(test_src_path, std::fstream::in);
        if (!src_file.is_open()) {
            throw std::runtime_error("Cannot open Source File!");
        }
        parser();
        src_file.close();
    }

public:
    static void Init() {
        Initializer Init_Process;

        std::cout << "Initializer is working..." << std::endl;
        std::cout << std::endl;

        Init_Process.locate_origin_src();
        Init_Process.copy_to_src();
        Init_Process.scan_src();

        std::cout << "SourceFile is scanned, Vertex/EdgeWithWeight/Category Initialized!" << std::endl;
        std::cout << std::endl;
    }

    static void Test() {
        Initializer Init_Process;

        std::cout << "Start to test the Initializer..." << std::endl;
        std::cout << std::endl;

        Init_Process.make_test_src();
        Init_Process.scan_test_src();

        std::cout << "Test of the Initializer is end." << std::endl;
        std::cout << std::endl;
    }
};

} // namespace Module