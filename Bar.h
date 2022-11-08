#ifndef BAR_GRAPH_SAND_PROBLEM_BAR_H
#define BAR_GRAPH_SAND_PROBLEM_BAR_H

#include <string>

class Bar {

public:
    explicit Bar(unsigned long height) : height(height), sand_height(0) {

    }

    bool operator<(const Bar &other) const {
        return height < other.height;
    }

    void setSandHeight(const Bar &other) {
        if (*this < other) {
            sand_height = other.height - height;
        } else {
            sand_height = 0;
        }
    }

    unsigned long getSandHeight() const {
        return sand_height;
    }
    unsigned long getBarHeight() const {
        return height;
    }


//    std::string drawVertical(long long level) const {
//        long long difference = level - (sand_height + height);
//        if (level == -1) {
////            we are drawing the X axis
//            return std::to_string(height);
//        } else if ((level == 0) || (difference == 0 && sand_height > 0)) {
////            we are drawing the vertical line
//            return "-";
//        } else if (level <= height) {
////            we are drawing the bar height
//            return "|";
//        } else if ((difference < 0)) {
////            we are drawing the sand height
//            return ".";
//        } else if (difference == 1 && sand_height > 0) {
////            we are drawing the sand height value
//            return std::to_string(sand_height);
//        } else {
//            return " ";
//        }
//    }
//
//    std::string repeatStr(std::string str, unsigned int count) {
//        return str.append(str.c_str(), 5);
//    }
//
//    std::string drawHorizontal() {
//        std::string bar_line = std::to_string(height) + " |" + repeatStr("- ", height);
//
//
//        if (sand_height > 0) {
//            switch (sand_height) {
//
//                default:
//                    bar_line += repeatStr(". ", sand_height - 1);
//                case 1:
//                    bar_line += "| " + std::to_string(sand_height);
//
//            }
//        }
//
//
//        return bar_line + "\n";
//    }


private:
    unsigned long height;
    unsigned long sand_height;
};


#endif //BAR_GRAPH_SAND_PROBLEM_BAR_H
