//
//  Windy_Visualizer.hpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/29/21.
//

#ifndef WindyVisualizer_hpp
#define WindyVisualizer_hpp

#include "GridWorld.hpp"
#include "WindyEnv.hpp"
#include "WindyPolicy.hpp"
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

/// Class that creates the visualization of windy GridWorld
class WindyVisualizer
{
private:
    // Stores GridWorld
    vector_2D grid;
    // Easy access to starting position
    std::tuple<int, int> startPos;
    // Easy access to goal position
    std::tuple<int, int> goalPos;
    // SFML game window
    sf::RenderWindow gridWindow;
    // Pixel size for a single grid
    int gridPixel;
    
public:
    /// Constructor of the Visualizer class
    /// @param inputGridWorld Constant reference to an input gridWorld class
    /// @param inputGridPixel (Optional) Desired pixel number for each grid edge in the visualizer window
    WindyVisualizer(const gridWorld& inputGridWorld, int inputGridPixel = 200);
    
    /// Function that draws a full episode of grid positions on GridWorld
    /// @param gridPosEpisode Vector containing a full episode of positions on GridWorld
    void drawWindyWorld (std::vector<std::tuple<int, int>> gridPosEpisode);
    
private:
    /// Starts a GridWorld window
    void startWindow ();
    
    /// Draws a full GridWorld on the game window
    void drawGridWorld ();
    
    /// Draws the current grid position in GridWorld
    /// @param gridPos Current state position
    void drawGridPos (std::tuple<int, int> gridPos);
};

#endif /* WindyVisualizer_hpp */
