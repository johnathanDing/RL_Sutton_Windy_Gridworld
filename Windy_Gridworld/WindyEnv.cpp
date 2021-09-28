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
    m = static_cast<int>(grid.size());
    n = static_cast<int>(grid[0].size());
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
        if (i_next>=0 && i_next<m && j_next>=0 && j_next<n) {
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
        if (i_next>=0 && i_next<m && j_next>=0 && j_next<n) {
            availableMoves.push_back(move);
        }
    }
    
    return availableMoves;
}


windyResponse windyEnv::getSteadyWindResp(std::tuple<int, int> curr_state, std::tuple<int, int> curr_move) const
{
    // Initialize return result
    windyResponse response;
    // Get the position as if no wind is present
    int i_next_noWind (std::get<0>(curr_state)+std::get<0>(curr_move));
    int j_next_noWind (std::get<1>(curr_state)+std::get<1>(curr_move));
    
    // Get the wind condition and initialize actual next position
    int wind (grid[std::get<0>(curr_state)][std::get<1>(curr_state)]);
    int i_next, j_next;
    // Consider the effect of wind, if there is any
    if (wind != 0) {
        // Bound the wind effect to within GridWorld
        i_next = std::max(0, std::min(m, i_next_noWind + wind));
        j_next = j_next_noWind;
    }
    else {
        i_next = i_next_noWind;
        j_next = j_next_noWind;
    }
    
    // Construct the response struct
    response.next_state = std::make_tuple(i_next, j_next);
    response.reward = -1;
    response.finished = (response.next_state == goalPos);
    
    return response;
}


windyResponse windyEnv::getStochasticWindResp(std::tuple<int, int> curr_state, std::tuple<int, int> curr_move) const
{
    // Initialize return result
    windyResponse response;
    // Get the position as if no wind is present
    int i_next_noWind (std::get<0>(curr_state)+std::get<0>(curr_move));
    int j_next_noWind (std::get<1>(curr_state)+std::get<1>(curr_move));
    
    // Initialize the random number generator for stochastic wind
    static std::mt19937 mersenneEng {static_cast<std::mt19937::result_type>(std::time(nullptr))};
    static std::uniform_int_distribution<int> randomWind (-1, 1);
    
    // Get the wind condition and initialize actual next position
    int wind (grid[std::get<0>(curr_state)][std::get<1>(curr_state)]);
    int i_next, j_next;
    // Consider the effect of wind, if there is any
    if (wind != 0) {
        // Bound the wind effect to within GridWorld
        // Apply the stochastic wind effect as well
        i_next = std::max(0, std::min(m, i_next_noWind + wind + randomWind(mersenneEng)));
        j_next = j_next_noWind;
    }
    else {
        i_next = i_next_noWind;
        j_next = j_next_noWind;
    }
    
    // Construct the response struct
    response.next_state = std::make_tuple(i_next, j_next);
    response.reward = -1;
    response.finished = (response.next_state == goalPos);
    
    return response;
}
