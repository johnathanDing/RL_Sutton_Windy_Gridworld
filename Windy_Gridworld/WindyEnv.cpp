//
//  WindyEnv.cpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/24/21.
//

#include "WindyEnv.hpp"

windyEnv::windyEnv (gridWorld inputGrid) :
grid (inputGrid.getGrid()),
goalPos (inputGrid.getGoal())
{
    std::cout << "Windy Environment initialized!" << "\n";
}


std::vector<std::tuple<int, int>> windyEnv::availableCrossMoves(std::tuple<int, int> curr_state) const
{
    // List out all valid cross moves, and initialize the return result
    std::vector<std::tuple<int, int>> allCrossMoves {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    std::vector<std::tuple<int, int>> availableMoves;
    // If the move makes a valid next state, put it into return result
    for (std::tuple<int, int> move : allCrossMoves) {
        int i_next = std::get<0>(curr_state)+std::get<0>(move);
        int j_next = std::get<1>(curr_state)+std::get<1>(move);
        if (i_next>=0 && i_next<static_cast<int>(grid.size()) && j_next>=0 && j_next<static_cast<int>(grid[0].size())) {
            availableMoves.push_back(move);
        }
    }
    
    return availableMoves;
}


std::vector<std::tuple<int, int>> windyEnv::availableKingMoves(std::tuple<int, int> curr_state) const
{
    // List out all valid king moves, and initialize the return result
    std::vector<std::tuple<int, int>> allKingMoves {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1 ,-1}};
    std::vector<std::tuple<int, int>> availableMoves;
    // If the move makes a valid next state, put it into return result
    for (std::tuple<int, int> move : allKingMoves) {
        int i_next = std::get<0>(curr_state)+std::get<0>(move);
        int j_next = std::get<1>(curr_state)+std::get<1>(move);
        if (i_next>=0 && i_next<static_cast<int>(grid.size()) && j_next>=0 && j_next<static_cast<int>(grid[0].size())) {
            availableMoves.push_back(move);
        }
    }
    
    return availableMoves;
}


