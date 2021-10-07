//
//  Windy_Visualizer.cpp
//  Windy_Gridworld
//
//  Created by Xiaoyue Ding on 9/29/21.
//

#include "WindyVisualizer.hpp"

WindyVisualizer::WindyVisualizer (const gridWorld& inputGridWorld, int inputGridPixel) :
grid(inputGridWorld.getGrid()),
startPos(inputGridWorld.getStart()),
goalPos(inputGridWorld.getGoal()),
gridPixel(inputGridPixel)
{
    std::cout << "Windy Visualizer Initialized!" << "\n";
}


void WindyVisualizer::startWindow() {
    // Get the grid size of the GridWorld
    int rowNum (static_cast<int>(grid.size()));
    int colNum (static_cast<int>(grid[0].size()));
    // Get the pixel size of the GridWorld
    int windowHeight (rowNum * gridPixel);
    int windowWidth (colNum * gridPixel);
    // Start the game window and set vertical sync
    gridWindow.create(sf::VideoMode(windowWidth, windowHeight), "Johnathan's Windy GridWorld");
    gridWindow.setVerticalSyncEnabled(true);
}


void WindyVisualizer::drawGridWorld() {
    // Get the grid size of the GridWorld
    int rowNum (static_cast<int>(grid.size()));
    int colNum (static_cast<int>(grid[0].size()));
    
    // Set up a single rectangle with inward edge lines
    sf::RectangleShape singleGrid (sf::Vector2f(static_cast<float>(gridPixel), static_cast<float>(gridPixel)));
    singleGrid.setOutlineColor(sf::Color::White);
    singleGrid.setOutlineThickness(-1.0);
    
    // Draw the entire GridWorld
    for (int i_row (0); i_row < rowNum; ++i_row) {
        for (int i_col (0); i_col < colNum; ++i_col) {
            // Draw the first row as bottom. Personal preference
            singleGrid.setPosition(i_col*static_cast<float>(gridPixel), (rowNum-1-i_row)*static_cast<float>(gridPixel));
            
            // Fill the grid with white (no wind), pink (weak wind), and red (strong wind) colors
            // Specially mark the starting position as yellow and goal position as blue
            if (std::make_tuple(i_row, i_col) == startPos) {
                singleGrid.setFillColor(sf::Color::Yellow);
            }
            else if (std::make_tuple(i_row, i_col) == goalPos) {
                singleGrid.setFillColor(sf::Color::Blue);
            }
            else {
                singleGrid.setFillColor(sf::Color(255*grid[i_row][i_col]/3, 0, 0));
            }
            
            // Draw the rectangle into buffer
            gridWindow.draw(singleGrid);
        }
    }
}


void WindyVisualizer::drawGridPos(std::tuple<int, int> gridPos) {
    // Set up moving object and fill with blue color
    sf::RectangleShape objectPos (sf::Vector2f(static_cast<float>(gridPixel), static_cast<float>(gridPixel)));
    objectPos.setFillColor(sf::Color::Green);
    // Set the position of moving object
    float object_x (std::get<1>(gridPos) * static_cast<float>(gridPixel));
    float object_y (std::get<0>(gridPos) * static_cast<float>(gridPixel));
    objectPos.setPosition(object_x, object_y);
    // Draw the object into buffer
    gridWindow.draw(objectPos);
}


void WindyVisualizer::drawWindyWorld(std::vector<std::tuple<int, int>> gridPosEpisode) {
    // Get the length of the episode
    int episodeLen (static_cast<int>(gridPosEpisode.size()));
    // Starting index
    int i_pos (0);
    // Open the window if it's not already
    if (gridWindow.isOpen() == false) {
        startWindow();
    }
    // Grid-drawing loop
    while (gridWindow.isOpen()) {
        // Create the event object
        sf::Event event;
        
        // Follow the event commands
        while (gridWindow.pollEvent(event)) {
            
            // If close, close
            if (event.type == sf::Event::Closed) {
                std::cout << "User closed the window!" << "\n";
                gridWindow.close();
            }
            
            // If the space key is pressed, move to the next grid position to draw
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                ++i_pos;
            }
            
            // If full episode is depleted, close the window
            if (i_pos == episodeLen) {
                std::cout << "Reached the end of the episode!" << "\n";
                gridWindow.close();
            }
            
            // Clear the window for the next update
            gridWindow.clear(sf::Color::White);
            // Draw the GridWorld first
            drawGridWorld();
            // Then draw the moving object position
            drawGridPos(gridPosEpisode[i_pos]);
            
            // Push the drawings in buffer to display
            gridWindow.display();
        }
    }
}
