//
//  WindyEnv.hpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/24/21.
//

#ifndef WindyEnv_hpp
#define WindyEnv_hpp

#include "GridWorld.hpp"
#include <vector>
#include <tuple>
#include <random>
#include <time.h>
#include <iostream>

/// Struct to store the environment response
struct windyResponse
{
    // Stores the next state in GridWorld
    std::tuple<int, int> next_state;
    // Reward to current step
    int reward;
    // Whether the current episode is finished (goal reached)
    bool finished;
};

/// Class the simualtes the windy enviroment. Can return available actions given a state, and/or environment response given a state and an action
class windyEnv
{
private:
    // To store the given GridWorld
    vector_2D grid;
    // For easy access to the finishing position
    std::tuple<int, int> goalPos;
    
public:
    /// Constructor of the Windy Environment
    /// @param inputWorld Input gridWorld class instance
    windyEnv(gridWorld inputWorld);
    
    /// Method that returns the full list of available cross moves (left, right, up, down) given a state
    /// @param curr_state Current state on the GridWorld
    std::vector<std::tuple<int, int>> availableCrossMoves(std::tuple<int, int> curr_state) const;
    
    /// Method that returns the full list of available king moves (left, right, up, down, and diagnals) given a state
    /// @param curr_state Current state on the GridWorld
    std::vector<std::tuple<int, int>> availableKingMoves(std::tuple<int, int> curr_state) const;
    
    /// Returns the environment response under steady wind (no random moves)
    /// @param curr_state Current state on the GridWorld
    /// @param curr_move Current action (move) to be applied on the state
    const windyResponse getSteadyWindResp(std::tuple<int, int> curr_state, std::tuple<int, int> curr_move) const;
    
    /// Returns the environment response under stochastic wind (with random moves)
    /// @param curr_state Current state on the GridWorld
    /// @param curr_move Current action (move) to be applied on the state
    const windyResponse getStochasticWindResp(std::tuple<int, int> curr_state, std::tuple<int, int> curr_move) const;
};

#endif /* WindyEnv_hpp */
