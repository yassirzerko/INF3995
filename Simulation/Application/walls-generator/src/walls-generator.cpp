#include "walls-generator.h"

/****************************************/
/****************************************/

WallsGenerator::WallsGenerator() :
    heightEnv_(DEFAULT_HEIGHT), 
    widthEnv_(DEFAULT_WIDTH),
    nAgents_(DEFAULT_NUMBER_AGENTS)
    {}

/****************************************/
/****************************************/

WallsGenerator::WallsGenerator(size_t heightEnv, size_t widthEnv, size_t nAgents) :
    heightEnv_(heightEnv),
    widthEnv_(widthEnv),
    nAgents_(nAgents < MAX_NUMBER_AGENTS && nAgents > MIN_NUMBER_AGENTS ? nAgents : DEFAULT_NUMBER_AGENTS)
    {}

/****************************************/
/****************************************/

void WallsGenerator::GenerateWalls() 
{
    InitializeGrid();
    InitializeAgents();
    srand (time(NULL));

    bool isValid = false;
    while (!isValid) {
        for (int i = 0; i < NUMBER_OF_STEPS_AGENTS; i++) {
            for (Agent& agent : agents_) {
                grid_.at(agent.currentX).at(agent.currentY).is_taken = true;
                DecideNextAction(agent);
            }
        }
        // Verify that all the corners of the grid are included in the corrdiors
        isValid = CheckTakenGridElementsRate() 
            && grid_.at(0).at(widthEnv_ - 1).is_taken
            && grid_.at(heightEnv_ - 1).at(0).is_taken 
            && grid_.at(heightEnv_ - 1).at(widthEnv_ - 1).is_taken; 
    }

    CheckWallsFromBottom();
    CheckWallsFromRight();

    std::cout << "Printing Grid ... " << std::endl;
    for (std::vector<GridElement>& col : grid_) {
        for (GridElement& element : col) {
            std::cout << element.is_taken << " | ";
        }
        std::cout << std::endl;
    }

    BuildHorizontalWalls();
    BuildVerticalWalls();

    AddDoorsInsideHorizontalWalls();
    AddDoorsInsideVerticalWalls();
}

/****************************************/
/****************************************/

bool WallsGenerator::CheckTakenGridElementsRate() 
{
    size_t counter = 0;
    for (std::vector<GridElement>& col : grid_) {
        for (GridElement& element : col) {
            if (element.is_taken)
                counter++;
        }
    }
    return (float)counter / (DEFAULT_HEIGHT * DEFAULT_WIDTH) > DEFAULT_MINIMUM_TAKEN_ELEMENTS_RATE;
}

/****************************************/
/****************************************/

void WallsGenerator::CheckWallsFromBottom() 
{
    for (size_t i = 0; i < heightEnv_; i++) {
        bool state = grid_.at(0).at(i).is_taken;
        for (size_t j = 0; j < widthEnv_; j++) {
            if (state != grid_.at(j).at(i).is_taken) {
                grid_.at(j-1).at(i).bottomWall = true;
                state = grid_.at(j).at(i).is_taken;
            }
        }
    }
}

/****************************************/
/****************************************/

void WallsGenerator::CheckWallsFromRight() 
{
    for (size_t i = 0; i < widthEnv_; i++) {
        bool state = grid_.at(i).at(0).is_taken;
        for (size_t j = 0; j < heightEnv_; j++) {
            if (state != grid_.at(i).at(j).is_taken) {
                grid_.at(i).at(j-1).rightWall = true;
                state = grid_.at(i).at(j).is_taken;
            } 
        }
    }
}

/****************************************/
/****************************************/

void WallsGenerator::BuildVerticalWalls() 
{
    for (size_t i = 0; i < heightEnv_; i++) {
        Wall wall = {0 , 0, 0};
        for (size_t j = 0; j < widthEnv_; j++) {
            if  (grid_.at(j).at(i).rightWall) {
                if (wall.length != 0) {
                    verticalWalls_.back().length += 1;
                } else {
                    wall = {(float)j, (float)i+1, 1, "V" + std::to_string(verticalWalls_.size())};
                    verticalWalls_.push_back(wall);
                }
            } else {
                wall = {0 , 0, 0};
            }
        }
    }
}

/****************************************/
/****************************************/

void WallsGenerator::BuildHorizontalWalls() 
{
    for (size_t i = 0; i < widthEnv_; i++) {
        Wall wall = {0 , 0, 0};
        for (size_t j = 0; j < heightEnv_; j++) {
            if  (grid_.at(i).at(j).bottomWall) {
                if (wall.length != 0) {
                    horizontalWalls_.back().length += 1;
                } else {
                    wall = {(float)i+1, (float)j, 1, "H" + std::to_string(horizontalWalls_.size())};
                    horizontalWalls_.push_back(wall);
                }
            } else {
                wall = {0 , 0, 0};
            }
        }
    }
}

/****************************************/
/****************************************/

void WallsGenerator::AddDoorsInsideVerticalWalls() 
{
    for (Wall& wall : verticalWalls_) {
        if (wall.length > 1) {
            float tempLength = wall.length;
            wall.length = tempLength/2 - 0.5f;
            Wall newWall = {
                wall.positionX + wall.length + 1,
                wall.positionY,
                tempLength/2 - 0.5f,
                "V" + std::to_string(verticalWalls_.size())
            };
            verticalWalls_.push_back(newWall);
        }
    }
}

/****************************************/
/****************************************/

void WallsGenerator::AddDoorsInsideHorizontalWalls() 
{
    for (Wall& wall : horizontalWalls_) {
        if (wall.length > 1) {
            float tempLength = wall.length;
            wall.length = tempLength/2 - 0.5f;
            Wall newWall = {
                wall.positionX,
                wall.positionY + wall.length + 1,
                tempLength/2 - 0.5f,
                "H" + std::to_string(horizontalWalls_.size())
            };
            horizontalWalls_.push_back(newWall);
        }
    }
}

/****************************************/
/****************************************/

void WallsGenerator::ExportWallsToArgos() 
{
    std::cout << "Exporting ARGoS elements to the file " << FILE_EXPORT_PATH << "... " << std::endl;
    std::ofstream experimentFile(FILE_EXPORT_PATH, std::ofstream::out);
    experimentFile << "    <!--Begin-->" << std::endl;
    for (const Wall wall : verticalWalls_) {
        experimentFile << GenerateWallElement(wall, true);
    }
    for (const Wall wall : horizontalWalls_) {
        experimentFile << GenerateWallElement(wall, false);
    }
    experimentFile << "    <!--End-->" << std::endl;
}

/****************************************/
/****************************************/

std::string WallsGenerator::GenerateWallElement(const Wall wall, bool vertical) 
{
    std::string size = "";
    std::string pos = "";
    if (vertical) {
        size = std::to_string(wall.length) + ", " + DEFAULT_WALL_SIZE_Y + ", " + DEFAULT_WALL_SIZE_Z;
        pos = std::to_string((float)wall.positionX + (float)wall.length / 2) + ", " + std::to_string(wall.positionY) + ", 0";
    } else {
        size = DEFAULT_WALL_SIZE_X + ", " + std::to_string(wall.length) + ", " + DEFAULT_WALL_SIZE_Z;
        pos = std::to_string(wall.positionX) + ", " + std::to_string((float)wall.positionY + (float)wall.length / 2) + ", 0";
    }
    return  "    <box id=\"wall_" + wall.id + "\" size=\"" + size + "\" movable=\"false\">\n" +
            "      <body position=\"" + pos + "\" orientation=\"0,0,0\" />\n" +
            "    </box>\n"
    ;
}

/****************************************/
/****************************************/

void WallsGenerator::InitializeGrid() 
{
    std::cout << "Initializing Grid ..." << std::endl;
    grid_.resize(widthEnv_);
    for (std::vector<GridElement>& col : grid_) {
        col.resize(heightEnv_);
    }

    for (std::vector<GridElement>& col : grid_) {
        for (GridElement& element : col) {
            element.is_taken = false;
            element.bottomWall = false;
            element.rightWall = false;
        }
    }
}

/****************************************/
/****************************************/

void WallsGenerator::InitializeAgents() 
{
    std::cout << "Initializing Agents ..." << std::endl;
    agents_.resize(nAgents_);
    agents_.at(0) = {5, 5, down};
    if (nAgents_ < 2)
        return ;
    agents_.at(1) = {4, 4, up};
    if (nAgents_ < 3)
        return ;
    agents_.at(2) = {4, 5, up};
    if (nAgents_ < 4)
        return ;
    agents_.at(3) = {5, 4, down};
}

/****************************************/
/****************************************/

void WallsGenerator::DecideNextAction(Agent& agent) 
{
    size_t x = agent.currentX;
    size_t y = agent.currentY;
    Direction direction = agent.direction;
    do {
        x = agent.currentX; y = agent.currentY;
        float pourcentage = (float)rand() / RAND_MAX;
        if (pourcentage > MAX_POURCENTAGE_THRESHHOLD) {
            // Go Straight
            x = direction == right              ? x + 1 : x;
            x = direction == left && x > 0      ? x - 1 : x;
            y = direction == down               ? y + 1 : y;
            y = direction == up && y > 0        ? y - 1 : y;
        } else if (pourcentage > MIN_POURCENTAGE_THRESHHOLD) {
            // Turn Right
            x = direction == up                 ? x + 1 : x;
            x = direction == down && x > 0      ? x - 1 : x;
            y = direction == right              ? y + 1 : y;
            y = direction == left && y > 0      ? y - 1 : y;
        } else {
            // Turn Left
            x = direction == down               ? x + 1 : x;
            x = direction == up && x > 0        ? x - 1 : x;
            y = direction == left               ? y + 1 : y;
            y = direction == right && y > 0     ? y - 1 : y;
        }
    } while (x < 0 || x >= widthEnv_ || y < 0 || y >= heightEnv_);
    agent.currentX = x; agent.currentY = y; agent.direction = direction;
}

/****************************************/
/****************************************/
