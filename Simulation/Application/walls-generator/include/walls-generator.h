#ifndef WALLS_GENERATOR_H
#define WALLS_GENERATOR_H

//Standard C++ libraries
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <random>
#include <vector>

#define FILE_EXPORT_PATH "bin/generated_argos_elements.txt"
#define DEFAULT_HEIGHT 10
#define DEFAULT_WIDTH 10

const std::string DEFAULT_WALL_SIZE_X = "0.1";
const std::string DEFAULT_WALL_SIZE_Y = "0.1";
const std::string DEFAULT_WALL_SIZE_Z = "2.0";
const float DEFAULT_MINIMUM_TAKEN_ELEMENTS_RATE = 0.4f;
const float MIN_POURCENTAGE_THRESHHOLD = 0.3f;
const float MAX_POURCENTAGE_THRESHHOLD = 0.6f;
const size_t NUMBER_OF_STEPS_AGENTS = 35;
const size_t DEFAULT_NUMBER_AGENTS = 4;
const size_t MIN_NUMBER_AGENTS = 1;
const size_t MAX_NUMBER_AGENTS = 4;

enum Direction
{
    right = 0,
    left,
    down,
    up
};

struct GridElement
{
    bool is_taken;
    bool rightWall;
    bool bottomWall;
};

struct Agent
{
    size_t currentX;
    size_t currentY;
    Direction direction; // 0 : right - 1 : left - 2 : down - 3 : up
};

struct Wall
{
    float positionX;
    float positionY;
    float length;
    std::string id;
};

class WallsGenerator
{

public:
    /* Class default constructor */
    WallsGenerator();
    /* Class constructor */
    WallsGenerator(size_t heightEnv, size_t widthEnv, size_t nAgents);
    /* Main function of the walls generating algorithm */
    void GenerateWalls();
    /* Export the dimensions and the positions of the walls to a file */
    void ExportWallsToArgos();

private:
    /* Intialization of the grid */
    void InitializeGrid();
    /* Intialization of the agents in different initial positions */
    void InitializeAgents();
    /* Vefiy the number of taken elements in the grid (elements in corridors) */
    bool CheckTakenGridElementsRate();
    /* Check if there is a wall from the bottom of every grid element */
    void CheckWallsFromBottom();
    /* Check if there is a wall from the right of every grid element */
    void CheckWallsFromRight();
    /* Add the vertical walls to the verticalWalls_ attribute */
    void BuildVerticalWalls();
    /* Add the horizontal walls to the horizontalWalls_ attribute */
    void BuildHorizontalWalls();
    /* Add doors inside vertical walls */
    void AddDoorsInsideVerticalWalls();
    /* Add doors inside horizontal walls */
    void AddDoorsInsideHorizontalWalls();
    /* Decide the next action to take depending on the current direction */
    void DecideNextAction(Agent &agent);
    /* Format the wall element into an XML box element */
    std::string GenerateWallElement(const Wall wall, bool vertical);

    std::vector<std::vector<GridElement>> grid_;
    std::vector<Agent> agents_;
    std::vector<Wall> horizontalWalls_;
    std::vector<Wall> verticalWalls_;
    size_t heightEnv_;
    size_t widthEnv_;
    size_t nAgents_;
};

#endif /* WALLS_GENERATOR */
