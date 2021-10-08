//
//  GridWorld.cpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/24/21.
//

#include "GridWorld.hpp"


gridWorld::gridWorld(vector_2D inputGrid, std::tuple<int, int> inputStart, std::tuple<int, int> inputGoal) :
grid(inputGrid),
startPos(inputStart),
goalPos(inputGoal)
{
    std::cout << "GridWorld initialized!" << "\n";
}


vector_2D gridWorld::getGrid() const {
    return grid;
}


std::tuple<int, int> gridWorld::getStart() const {
    return startPos;
}


std::tuple<int, int> gridWorld::getGoal() const {
    return goalPos;
}
