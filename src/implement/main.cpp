#include "main.hpp"

int main(int argc, char** argv){
    string filePath = argv[1];
    UncertainSearch solver = UncertainSearch(filePath);
    solver.solve();

    return 0;
}