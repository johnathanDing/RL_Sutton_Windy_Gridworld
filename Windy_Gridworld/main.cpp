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
    
    // Take a look at the GridWorld first
    visualizer.drawWindyWorld(std::vector<std::tuple<int, int>> (1, std::tuple<int, int> (0, 0)));
    
    
    
    return 0;
    
}
