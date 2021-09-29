//
//  WindyPolicy.cpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/28/21.
//

#include "WindyPolicy.hpp"

windyPolicy::windyPolicy (const windyEnv& input_windy_env, double input_epsilon) :
windy_env_ref(input_windy_env),
epsilon_soft(input_epsilon)
{
    std::cout << "Windy Policy initialized!" << "\n";
}


void windyPolicy::updateStateActionValCross (std::tuple<int, int> curr_state, std::tuple<int, int> curr_move, int reward, std::tuple<int, int> next_state, std::tuple<int, int> next_move, double alpha_lr, double gamma_discount)
{
    // Make sure the inquired states and actions are initialized first
    if (state_action_space.find(curr_state) == state_action_space.end()) {
        std::vector<std::tuple<int, int>> allMoves (windy_env_ref.availableCrossMoves(curr_state));
        state_action_space.insert(std::pair<std::tuple<int, int>, std::vector<std::tuple<int, int>>>
                                  (curr_state, allMoves));
        state_action_value.insert(std::pair<std::tuple<int, int>, std::vector<double>>
                                  (curr_state, std::vector<double> (static_cast<int>(allMoves.size()), 0.0)));
    }
    if (state_action_space.find(next_state) == state_action_space.end()) {
        std::vector<std::tuple<int, int>> allMoves (windy_env_ref.availableCrossMoves(next_state));
        state_action_space.insert(std::pair<std::tuple<int, int>, std::vector<std::tuple<int, int>>>
                                  (next_state, allMoves));
        state_action_value.insert(std::pair<std::tuple<int, int>, std::vector<double>>
                                  (next_state, std::vector<double> (static_cast<int>(allMoves.size()), 0.0)));
    }
    
    // Iterators to find corresponding actions
    std::vector<std::tuple<int, int>>::iterator iter_curr_move, iter_next_move;
    iter_curr_move = std::find(state_action_space.at(curr_state).begin(), state_action_space.at(curr_state).end(), curr_move);
    iter_next_move = std::find(state_action_space.at(next_state).begin(), state_action_space.at(next_state).end(), next_move);
    // Indices to the corresponding actions
    int idx_curr_move = static_cast<int>(std::distance(state_action_space.at(curr_state).begin(), iter_curr_move));
    int idx_next_move = static_cast<int>(std::distance(state_action_space.at(next_state).begin(), iter_next_move));
    
    // Make the state-action value update
    state_action_value.at(curr_state)[idx_curr_move] += alpha_lr * (reward + gamma_discount *           state_action_value.at(next_state)[idx_next_move] - state_action_value.at(curr_state)[idx_curr_move]);
}


void windyPolicy::updateStateActionValKing (std::tuple<int, int> curr_state, std::tuple<int, int> curr_move, int reward, std::tuple<int, int> next_state, std::tuple<int, int> next_move, double alpha_lr, double gamma_discount)
{
    // Make sure the inquired states and actions are initialized first
    if (state_action_space.find(curr_state) == state_action_space.end()) {
        std::vector<std::tuple<int, int>> allMoves (windy_env_ref.availableKingMoves(curr_state));
        state_action_space.insert(std::pair<std::tuple<int, int>, std::vector<std::tuple<int, int>>>
                                  (curr_state, allMoves));
        state_action_value.insert(std::pair<std::tuple<int, int>, std::vector<double>>
                                  (curr_state, std::vector<double> (static_cast<int>(allMoves.size()), 0.0)));
    }
    if (state_action_space.find(next_state) == state_action_space.end()) {
        std::vector<std::tuple<int, int>> allMoves (windy_env_ref.availableKingMoves(next_state));
        state_action_space.insert(std::pair<std::tuple<int, int>, std::vector<std::tuple<int, int>>>
                                  (next_state, allMoves));
        state_action_value.insert(std::pair<std::tuple<int, int>, std::vector<double>>
                                  (next_state, std::vector<double> (static_cast<int>(allMoves.size()), 0.0)));
    }
    
    // Iterators to find corresponding actions
    std::vector<std::tuple<int, int>>::iterator iter_curr_move, iter_next_move;
    iter_curr_move = std::find(state_action_space.at(curr_state).begin(), state_action_space.at(curr_state).end(), curr_move);
    iter_next_move = std::find(state_action_space.at(next_state).begin(), state_action_space.at(next_state).end(), next_move);
    // Indices to the corresponding actions
    int idx_curr_move = static_cast<int>(std::distance(state_action_space.at(curr_state).begin(), iter_curr_move));
    int idx_next_move = static_cast<int>(std::distance(state_action_space.at(next_state).begin(), iter_next_move));
    
    // Make the state-action value update
    state_action_value.at(curr_state)[idx_curr_move] += alpha_lr * (reward + gamma_discount *           state_action_value.at(next_state)[idx_next_move] - state_action_value.at(curr_state)[idx_curr_move]);
}


std::tuple<int, int> windyPolicy::getPolicyMove (std::tuple<int, int> curr_state) const
{
    // Static random number generators
    static std::mt19937 mersenneEng (static_cast<std::mt19937::result_type>(std::time(nullptr)));
    static std::uniform_real_distribution<double> epsilonRNG (0.0, 1.0);
    // Get the action pool from the state
    std::vector<std::tuple<int, int>> allMoves (state_action_space.at(curr_state));
    // If chance goes to exploration
    if (epsilonRNG(mersenneEng) <= epsilon_soft) {
        std::uniform_int_distribution<int> randomMoveRNG (0, static_cast<int>(allMoves.size())-1);
        return allMoves[randomMoveRNG(mersenneEng)];
    }
    // Or if chance goes to greedy
    else {
        std::vector<double>::const_iterator iter_greedy;
        iter_greedy = std::max_element(state_action_value.at(curr_state).begin(), state_action_value.at(curr_state).end());
        int idx_greedy (static_cast<int>(std::distance(state_action_value.at(curr_state).begin(), iter_greedy)));
        return state_action_space.at(curr_state)[idx_greedy];
    }
}


double windyPolicy::getStateActionVal(std::tuple<int, int> curr_state, std::tuple<int, int> curr_move) const
{
    //Iterator to find the action(move)
    std::vector<std::tuple<int, int>>::const_iterator iter_move;
    iter_move = std::find(state_action_space.at(curr_state).begin(), state_action_space.at(curr_state).end(),
                            curr_move);
    // Calculate the index
    int idx_move (static_cast<int>(std::distance(state_action_space.at(curr_state).begin(), iter_move)));
    return state_action_value.at(curr_state)[idx_move];
}

