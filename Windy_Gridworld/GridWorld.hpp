//
//  GridWorld.hpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/24/21.
//

#ifndef GridWorld_hpp
#define GridWorld_hpp

#include <vector>
#include <tuple>
#include <time.h>
#include <iostream>

using vector_2D = std::vector<std::vector<int>>;

/// Class that stores and return a given grid world
class gridWorld
{
private:
    // To store the grid world
    vector_2D grid;
    // For easy access to starting and finishing positions
    std::tuple<int, int> startPos;
    std::tuple<int, int> goalPos;
    
public:
    /// Constructor of gridWorld class. Does not take any input as the GridWorld is pre-defined in problem.
    gridWorld(vector_2D inputGrid, std::tuple<int, int> inputStart, std::tuple<int, int> inputGoal);
    
    /// Returns the pre-defiend grid
    vector_2D getGrid() const;
    
    /// Returns the starting position
    std::tuple<int, int> getStart() const;
    
    /// Returns the goal position
    std::tuple<int, int> getGoal() const;
};


#endif /* GridWorld_hpp */
