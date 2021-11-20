#include <iostream>
#include <fstream>
#include <map>
#include <memory>
#include "sort_algo.h"
#include "log_duration.h"
#include "query_factory.h"
#include "drawing.h"


using namespace std::literals;

void PrintUsage(std::ostream& out = std::cerr) {
    out << "Please use cmp or cmp \"filename\" or view \"type\""s << std::endl;
}

std::map<sort::Type, std::vector<double>> getSortTimes(int n, int step) {
    std::map<sort::Type, std::vector<double>> result;
    for (sort::Type type : sort::ALL_TYPES) {
        std::unique_ptr<sort::Algoritm> algorithm = sort::Factory::getFactory(type).Construct(n, step);
        std::vector<double> time_stamps = algorithm->Process();
        result[type] = std::move(time_stamps);
    }
    return result;
}

void printMapToOstream(std::ostream& out, std::map<sort::Type, std::vector<double>> map, int step) {
    if (map.empty()) {
        return;
    }
    // store pointers to current elements
    std::vector<std::vector<double>::iterator> ptrs;
    int size = 0;
    out << "N"s << '\t';
    for (auto& [type, array] : map) {
        out << sort::typeToString(type) << '\t';
        ptrs.push_back(array.begin());
        // all arrays are the same size
        size = array.size();
    }
    out << '\n';
    int N = 0;
    for (int i = 0; i < size; ++i) {
        out << N << '\t';
        N += step;
        for (int j = 0; j < ptrs.size(); ++j) {
            out << *ptrs.at(j) << '\t';
            ++ptrs.at(j);
        }
        out << '\n';
    }
    out.flush();
}

int main(int argc, char* argv[]) {
    // here processing next cmds:
    // cmp - сравнить сложность сортировок, вывести на экран
    // cmp "filename" - сравнить сложность сортировок, вывести в csv файл
    // view "type" - отобразить на экране процесс сортировки
    // type допускается следующим:
    // bubble, shaker, comb, isertion, selection, quick, merge, heap
    //testDraw();
    if (argc < 2) {
        PrintUsage();
        return 1;
    }
    const std::string_view mode(argv[1]);
    if (mode == "cmp"sv) {
        if (argc == 3) {
            // вывести результаты в файл
            std::string name(argv[2]);
            std::ofstream ofile(name);
            printMapToOstream(ofile, getSortTimes(1000, 10), 10);
            std::cout << "save succesfully"s << std::endl;
        } else {
            draw::plot(getSortTimes(1000, 10), 10);
        }
    } else if (mode == "view"sv) {

    } else {
        PrintUsage();
        return 1;
    }
    return 0;
}
