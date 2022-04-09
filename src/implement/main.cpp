#include "main.hpp"

int main(int argc, char** argv){
    string filePath = argv[1];
    ProductionSearch solver = ProductionSearch(filePath);
    solver.solve();

    return 0;
}