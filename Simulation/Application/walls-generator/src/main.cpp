# include <iostream>
# include "walls-generator.h"

int main() {
    std::cout << "Welcome to the Walls Generator!" << std::endl;
    WallsGenerator* wallsGen = new WallsGenerator();
    if (wallsGen) {
        wallsGen->GenerateWalls();
        wallsGen->ExportWallsToArgos();
    }
    delete wallsGen;
}
