//
//  WindyPolicy.hpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/28/21.
//

#ifndef WindyPolicy_hpp
#define WindyPolicy_hpp

#include "GridWorld.hpp"
#include "WindyEnv.hpp"
#include <vector>
#include <random>
#include <time.h>
#include <map>
#include <iterator>
#include <iostream>

/// Class containing computed policy to the windy GridWorld problem
class windyPolicy
{
private:
    // A constant reference to a windyEnv class instance.
    // For easy access to envrionment functions.
    const windyEnv& windy_env_ref;
    // To store state-action space (S-A)
    std::map<std::tuple<int, int>, std::vector<std::tuple<int, int>>> state_action_space;
    // To store state-action value
    std::map<std::tuple<int, int>, std::vector<double>> state_action_value;
    // Epsilon parameter for soft policy
    double epsilon_soft;
    
public:
    /// Constructor for the windyPolicy class.
    /// @param input_windy_env Constant reference to the input windyEnv class instance
    /// @param input_epsilon Input for the epsilon parameter
    windyPolicy (const windyEnv& input_windy_env, double input_epsilon = 0.2);
    
    /// For cross move policies, updates the state-action value according to SARSA
    /// @param curr_state S: current state
    /// @param curr_move A: current action
    /// @param reward R: reward to current step
    /// @param next_state S: next state
    /// @param next_move A: next action
    /// @param alpha_lr Learning rate parameter
    /// @param gamma_discount Episode discount parameter
    void updateStateActionValCross (std::tuple<int, int> curr_state, std::tuple<int, int> curr_move,
                               int reward,
                               std::tuple<int, int> next_state, std::tuple<int, int> next_move,
                               double alpha_lr, double gamma_discount);
    
    /// For king move policies, updates the state-action value according to SARSA
    /// @param curr_state S: current state
    /// @param curr_move A: current action
    /// @param reward R: reward to current step
    /// @param next_state S: next state
    /// @param next_move A: next action
    /// @param alpha_lr Learning rate parameter
    /// @param gamma_discount Episode discount parameter
    void updateStateActionValKing (std::tuple<int, int> curr_state, std::tuple<int, int> curr_move,
                               int reward,
                               std::tuple<int, int> next_state, std::tuple<int, int> next_move,
                               double alpha_lr, double gamma_discount);
    
    /// Returns the policy action (Cross Move) according to epsilon-soft greedy policy
    /// @param curr_state Current state inquired
    std::tuple<int, int> getPolicyCrossMove (std::tuple<int, int> curr_state, bool soft_flag = true) const;
    
    /// Returns the policy action (King Move) according to epsilon-soft greedy policy
    /// @param curr_state Current state inquired
    std::tuple<int, int> getPolicyKingMove (std::tuple<int, int> curr_state, bool soft_flag = true) const;
    
    /// Returns the state-action value inquired
    /// @param curr_state Current state
    /// @param curr_move Current action
    double getStateActionVal (std::tuple<int, int> curr_state, std::tuple<int, int> curr_move) const;
};

#endif /* WindyPolicy_hpp */
