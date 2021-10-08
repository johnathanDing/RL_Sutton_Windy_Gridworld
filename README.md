# Sutton's Windy Gridworld with Sarsa on-policy Time-Difference control

    Cross move with Steady wind     King move with Steady wind     King Move with Stochastic wind

<p float="center">
  <img src="./Examples/Trained_Episode_Cross_Steady.gif" width="32%" />
  <img src="./Examples/Trained_Episode_King_Steady.gif" width="32%" />
  <img src="./Examples/Trained_Episode_King_Stochastic.gif" width="32%" />
</p>

This project solves the Windy GridWorld problem in Sutton's textbook under various conditions, using Sarsa on-policy TD control.

This solution was written in C++ as main language, on Xcode 13.X platform. Visualization of race track requires installation of the SFML packages.
Unit testings were carried out using XCTest as well. All modules have tests except the visualization module, which cannot be supported by XCTest.


