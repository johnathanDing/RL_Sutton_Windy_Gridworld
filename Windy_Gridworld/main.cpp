//
//  main.cpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/23/21.
//

#include "GridWorld.hpp"
#include "WindyEnv.hpp"
#include "WindyPolicy.hpp"
#include "WindyVisualizer.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using PolicyMove = std::function<std::tuple<int, int> (std::tuple<int, int>, bool)>;
using UpdateVal = std::function<void (std::tuple<int, int>, std::tuple<int, int>,
                                      int,
                                      std::tuple<int, int>, std::tuple<int, int>,
                                      double, double)>;
using GetResponse = std::function<windyResponse (std::tuple<int, int>, std::tuple<int, int>)>;

int main() {
    // Explicitly write out the grid world layout
    vector_2D grid (7, std::vector<int> {0, 0, 0, 1, 1, 1, 2, 2, 1, 0});
    std::tuple<int, int> startPos {3, 0};
    std::tuple<int, int> goalPos {3, 7};
    
    // Initialize the GridWorld classes
    gridWorld world (grid, startPos, goalPos);
    windyEnv environment (world);
    windyPolicy policy (environment, 0.1);
    WindyVisualizer visualizer (world);
    
    // Initialize learning parameters
    double alpha_lr (0.5);
    double gamma_discount (1.0);
    int time_limit (10000);
    
    // Record training data in a file
    int time_step (0), episode_count (0);
    std::vector<int> episode_num (time_limit, 0);
    
    // Record training statistics
    std::ofstream training_file ("Training_statistics.txt");
    if (!training_file) {
        // If somehow the file is not opened
        std::cerr << "Training recording file failed to open!" << "\n";
        return 1;
    }
    training_file << "# Recording training statistics: episode count vs time step:" << "\n";
    training_file << "# Time step | Episode count" << "\n";
    
    // Record training start time
    clock_t start_time (clock());
    
    // Take a look at the GridWorld first
    visualizer.drawWindyWorld(std::vector<std::tuple<int, int>> (1, std::tuple<int, int> (0, 0)));
    
    // Print a message
    std::cout << "Training has started!" << "\n";
    
    // Initialize starting state
    std::tuple<int, int> curr_state, next_state;
    std::tuple<int, int> curr_move, next_move;
    windyResponse response;
    
    // Decide which problem setup to use: Cross move or King move, Steady or Stochastic wind
    /// Cross move and Steady wind
//    PolicyMove getPolicyMove { std::bind(&windyPolicy::getPolicyCrossMove, &policy, std::placeholders::_1,
//                                         std::placeholders::_2) };
//    UpdateVal updateStateActionVal { std::bind(&windyPolicy::updateStateActionValCross, &policy, std::placeholders::_1,
//                                               std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
//                                               std::placeholders::_5, std::placeholders::_6, std::placeholders::_7) };
//    GetResponse getEnvResponse { std::bind(&windyEnv::getSteadyWindResp, &environment, std::placeholders::_1,
//                                           std::placeholders::_2) };
    
    /// King move and Steady wind
//    PolicyMove getPolicyMove { std::bind(&windyPolicy::getPolicyKingMove, &policy, std::placeholders::_1,
//                                         std::placeholders::_2) };
//    UpdateVal updateStateActionVal { std::bind(&windyPolicy::updateStateActionValKing, &policy, std::placeholders::_1,
//                                               std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
//                                               std::placeholders::_5, std::placeholders::_6, std::placeholders::_7) };
//    GetResponse getEnvResponse { std::bind(&windyEnv::getSteadyWindResp, &environment, std::placeholders::_1,
//                                           std::placeholders::_2) };
    /// King move and Schochastic wind
    PolicyMove getPolicyMove { std::bind(&windyPolicy::getPolicyKingMove, &policy, std::placeholders::_1,
                                         std::placeholders::_2) };
    UpdateVal updateStateActionVal { std::bind(&windyPolicy::updateStateActionValKing, &policy, std::placeholders::_1,
                                               std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
                                               std::placeholders::_5, std::placeholders::_6, std::placeholders::_7) };
    GetResponse getEnvResponse { std::bind(&windyEnv::getStochasticWindResp, &environment, std::placeholders::_1,
                                           std::placeholders::_2) };
    
    // Sarsa TD control loop.
    // Limit training time step to below 8000
    while (time_step < time_limit) {
        curr_state = world.getStart();
        curr_move = getPolicyMove(curr_state, true);
        response = getEnvResponse(curr_state, curr_move);
        // One episode
        while (!response.finished) {
            // Get next state-action pair
            next_state = response.next_state;
            next_move = getPolicyMove(next_state, true);
            // Update the state-action value according to SARSA
            updateStateActionVal(curr_state, curr_move, response.reward, next_state, next_move, alpha_lr, gamma_discount);
            // Prepare for the next round of iteration
            curr_state = next_state;
            curr_move = next_move;
            response = getEnvResponse(curr_state, curr_move);
            // Record the current episode count and write into file
            episode_num[time_step] = episode_count;
            training_file << time_step << " " << episode_count << std::endl;
            // Progress tracker
            if (time_step%100 == 0) {
                std::cout << "Time step " << time_step << " reached with episode count: " << episode_count << "\n";
            }
            // Then increment time step
            ++ time_step;
            // If time step limit is reached, no need to continue the episode
            if (time_step == time_limit) {
                break;
            }
        }
        // Increment episode counter
        ++ episode_count;
    }
    
    // Close recording file
    training_file.close();
    // Print total training time
    clock_t total_time (clock() - start_time);
    std::cout << "Total training time is: " << static_cast<double>(total_time)/CLOCKS_PER_SEC << " sec." << "\n";
    
    // Generate a fully trained episode with greedy policy to visualize
    std::vector<std::tuple<int, int>> episode;
    curr_state = world.getStart();
    curr_move = getPolicyMove(curr_state, true);
    response = getEnvResponse(curr_state, curr_move);
    // Episode loop
    while (!response.finished) {
        episode.push_back(curr_state);
        curr_state = response.next_state;
        curr_move = getPolicyMove(curr_state, true);
        response = getEnvResponse(curr_state, curr_move);
    }
    // Push in the goal state
    episode.push_back(curr_state);
    
    std::cout << "Total length of testing episode is: " << episode.size() << "\n";
    
    // Visualize the testing episode
    visualizer.drawWindyWorld(episode);
    
    return 0;
    
}
