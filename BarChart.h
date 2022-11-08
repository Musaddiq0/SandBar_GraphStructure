#ifndef BAR_GRAPH_SAND_PROBLEM_BARCHART_H
#define BAR_GRAPH_SAND_PROBLEM_BARCHART_H

#include <vector>
#include <sstream>
#include <iomanip>
#include "Bar.h"

class BarChart {

public:
    BarChart() : vectorBars(), total_sand_units(0), max_bar_height(0) {}

    void addBar(unsigned long bar_height) {
        max_bar_height = max_bar_height < bar_height ? bar_height : max_bar_height;
        vectorBars.emplace_back(bar_height);
    }

    long long calculate() {
        return calculate(0);
    }

   long long getTotalSandUnits() const {
        return total_sand_units;
    }

    std::string drawHorizontal() const {

        auto txt_width = std::to_string(max_bar_height).size() + 1;

        std::stringstream ss;

        ss << std::left;

        for (long long level = max_bar_height + 3; level > -2; --level) {

            ss << " ";
            for (int j = 0; j < vectorBars.size(); ++j) {
                const Bar &bar = vectorBars[j];
                long long height = bar.getBarHeight(),
                        sand_height = bar.getSandHeight();
                long long difference = level - (sand_height + height);

                if (level == -1) {
//            we are drawing the X axis

                    ss << std::setw(txt_width) << std::to_string(height);
                } else if (level == 0) {
//            we are drawing the horizontal line

                    if (j < vectorBars.size() - 1) {
//
                        ss << std::setw(txt_width) << std::setfill('-') << "-" << std::setfill(' ');
                    } else {
                        ss << "-";
                    }
                } else if ((difference == 0 && sand_height > 0)) {
//            we are drawing the horizontal line for sand_height value

                    ss << std::setw(txt_width) << "-";
                } else if (level <= height) {
//            we are drawing the bar height

                    ss << std::setw(txt_width) << "|";
                } else if ((difference < 0)) {
//            we are drawing the sand height

                    ss << std::setw(txt_width) << ".";
                } else if (difference == 1 && sand_height > 0) {
//            we are drawing the sand height value

                    ss << std::setw(txt_width) << std::to_string(sand_height);
                } else {

                    ss << std::setw(txt_width) << " ";
                }
            }

            ss << "\n";



        }

        return ss.str();


    }

    [[nodiscard]] std::string drawVertical() const {


        auto txt_width = std::to_string(max_bar_height).size() + 1;
//        int txt_width = ;
        std::stringstream ss;



        for (const Bar &bar:vectorBars) {

            long long height = bar.getBarHeight(),
                    sand_height = bar.getSandHeight();

            ss << std::setw(txt_width) << std::to_string(height);


            ss << " |";

            ss << repeat("- ", height);

            if (sand_height > 0) {
                switch (sand_height) {
                    default:

                        ss << repeat(". ", sand_height - 1);
                    case 1:
                        ss << "| " + std::to_string(sand_height);

                }
            }
            ss << "\n";
        }

        return ss.str();
    }

protected:
    long long calculate(unsigned int start) {

        unsigned int cur = start, next = start + 1;

        for (unsigned int i = next; i < vectorBars.size(); ++i) {

            if (vectorBars[i] < vectorBars[cur]) {
                if (!(vectorBars[i] < vectorBars[next])) {
                    next = i;
                }
                continue;
            }
            calculateSand(cur, i);
            cur = i;
            next = i + 1;
        }

        if (next < vectorBars.size()) {
            calculateSand(cur, next);
            calculate(next);
        }

        return total_sand_units;


    }

    void calculateSand(unsigned int begin, unsigned int end) {

        if ((end - begin) < 2) {
            return;
        }
        Bar *smallerBar;

        if (vectorBars.at(begin) < vectorBars.at(end)) {
            smallerBar = &vectorBars.at(begin);
        } else {
            smallerBar = &vectorBars.at(end);
        }

        for (unsigned int i = begin + 1; i < end; ++i) {
            vectorBars.at(i).setSandHeight(*smallerBar);
            total_sand_units += vectorBars.at(i).getSandHeight();
        }

    }


// Function which return string by concatenating it.
 static std::string repeat(std::string s, long long n) {
        // Copying given string to temparory string.
        std::string s1 = s;

        for (int i = 1; i < n; i++)
            s += s1; // Concatinating strings

        return s;
    }


private:
    std::vector<Bar> vectorBars;
    unsigned long total_sand_units;
    unsigned long max_bar_height;

};


#endif //BAR_GRAPH_SAND_PROBLEM_BARCHART_H
