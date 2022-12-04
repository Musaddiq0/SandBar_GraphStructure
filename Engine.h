#ifndef BAR_GRAPH_SAND_PROBLEM_ENGINE_H
#define BAR_GRAPH_SAND_PROBLEM_ENGINE_H

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <regex>
#include <random>
#include "BarChart.h"

class Engine {

public:
    void start() {
        do {
            displayTitle();
            getUserInput();
            processData();
            plotGraph();

        } while (run_again());
    }

protected:
    static void displayTitle() {
        std::cout << "Title: Bar Graph Sand Problem\n";
        std::cout << "Name: Sadiq Musaddique\n";
        std::cout << "SID NO: 9766103\n\n";
    }

    void getUserInput() {

        bool successful;
        do {
            std::cout << "\n"
                         "Please enter the bar graph data (positive integers) with spaces directly,"
                         " or enter a filename to read from a text file input, \n"
                         "or type \"Random\" to randomly generate a bar graph. \n"
                         "eg. 2 6 3 5 2 8 1 4 2 2 5 11 1 4 11 7 ...or... BarGraphInput.txt ...or... Random.\n "
                         "Enter Your Input:";

            std::string line;

            std::getline(std::cin, line, '\n');
            rtrim(line);

            if (std::regex_match(line, std::regex(".+\\.txt$"))) {
                successful = get_data_from_file(line);
            } else if (line == "Random") {
//                generate random data
                successful = get_random_data();
            } else {
                //            assume raw data was entered on the console

                successful = get_data_from_string(line);
                if (successful) {
                    std::cout << "Console Input Read Successfully\n";
                } else {
                    std::cout << "Error: Invalid Console Input Format Detected: '"+line+"'\n";

                }

            }


        } while (!successful);
    }

    void processData() {
        for (auto val:graph_data) {
            barChart.addBar(val);
        }
        barChart.calculate();
        std::cout << "\nAnswer: This bar graph can hold a total of " << barChart.getTotalSandUnits()
                  << " units of sand.\n";
    }


    void plotGraph() {
        std::cout << "Would you like to plot horizontally or vertically?\n"
                     "eg. horizontally ...or... h ...or... vertically ...or... v : ";
        std::string choice;

        std::getline(std::cin, choice, '\n');
        rtrim(choice);


        if (choice == "h" || choice == "horizontally") {
            std::cout << build_graph('h');
            save_graph('h');
        } else if (choice == "v" || choice == "vertically") {
            std::cout << build_graph('v');
            save_graph('v');
        } else {
            std::cout << "\nNo Valid choice was selected. Skipping....\n";
        }
    }




private:

    static std::string &rtrim(std::string &s) {
        auto it = std::find_if(s.rbegin(), s.rend(),
                               [](char c) {
                                   return !isspace(c);
                               });
        s.erase(it.base(), s.end());
        return s;
    }
    static bool run_again() {

        std::cout << "Please enter 'Y' or 'y' to run again or anything else to exit  \n";
        std::string line;
        std::getline(std::cin, line, '\n');

        rtrim(line);
        if (line == "y" || line == "Y") {
            std::cout<<"\n Restarting.....\n\n\n\n\n";
            return true;
        } else {
            std::cout<<"Thank you for using the bar graph sand program.\n"
                       "Goodbye!";
            return false;
        }


    }

    void save_graph(char choice = 'v') {
        std::string line;
        do {
            std::cout << "\nPlease enter a filename to save bar graph to text file or enter 'n' to not save.\n"
                         "eg. BarGraphResult.txt ...or... n. \n Enter choice:";
            std::getline(std::cin, line, '\n');
            rtrim(line);
            if (std::regex_match(line, std::regex(".+\\.txt$"))) {
                std::ofstream ofs(line, std::ofstream::out | std::ofstream::trunc);
                ofs << build_graph(choice);
                std::cout<<"The bar graph with sand has been saved as "+line+"\n";
                break;
            } else if (line == "n") {
                break;
            } else {
                std::cout << "Error: Invalid File Name Format Detected.\n";
            }
        } while (true);


    }

    std::string build_graph(char choice = 'v') {

        std::string graph = "\nASCII art bar graph plot showing sand on top of the graph:\n";

        if (choice == 'v') {
            graph += barChart.drawVertical();
        } else if (choice == 'h') {
            graph += barChart.drawHorizontal();
        }
        graph += "Total " + std::to_string(barChart.getTotalSandUnits()) + " units of sand.\n";

        return graph;

    }

    bool get_data_from_string(const std::string &line) {
        if (std::regex_match(line, std::regex("^(\\d+ )*\\d$"))) {
            std::stringstream ss(line);
            unsigned int data;
            while (!ss.eof()) {
                ss >> data;
                graph_data.push_back(data);
            }
            return true;
        }
        return false;
    }

    bool get_data_from_file(const std::string &file) {
        std::fstream fs(file);
        std::string line;
        if (fs.is_open()) {
//                std::cout << "Great: Valid File Detected\n";
            std::getline(fs, line, '\n');
            rtrim(line);
//                std::cout << line;
            auto result = get_data_from_string(line);

            if (!result) {
                std::cout << "Error: Invalid File Data Format Detected\n";
            } else {
                std::cout << "File \"" + file + "\" read successfully...\n";

                return true;
            }
        } else {
            std::cout << "Error: Invalid File Detected\n";
        }
        return false;
    }

    bool get_random_data() {
        std::random_device rd;  //Will be used to obtain a seed for the random number engine
        std::mt19937 gen(rd()); //seeded with rd()
        std::uniform_int_distribution<> distrib(1, 20); // random number b/w 1 and 20
        graph_data.reserve(16);
        std::cout << "\n";
        for (int n = 0; n < 16; ++n) {
            graph_data.push_back(distrib(gen));
            std::cout << graph_data.back() << " ";

        }
        std::cout << "\nRandom data generated successfully\n.";

        return true;
    }

private:
    std::vector<unsigned int> graph_data;
    BarChart barChart;
};


#endif //BAR_GRAPH_SAND_PROBLEM_ENGINE_H
