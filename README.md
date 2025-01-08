# Snake Game

This is a simple Snake game implemented in C++ using the console for rendering. The game involves controlling a snake to eat food and grow in length, avoiding collisions with itself.

## Features
- **Console-Based Gameplay**: Play the classic Snake game directly in the console.
- **Dynamic Snake Movement**: Control the snake with the keyboard to navigate the game area.
- **Score Tracking**: Track your score based on the number of food items consumed.

## How to Play
1. **Objective**: Guide the snake to consume the food (`o`) that appears randomly on the screen. Each time the snake eats, it grows longer, and the score increases.
2. **Controls**:
   - `W` or `w`: Move up
   - `A` or `a`: Move left
   - `S` or `s`: Move down
   - `D` or `d`: Move right
3. **Game Over**: The game ends if the snake collides with itself. The final score is displayed when the game is over.

## Setup and Compilation

### Prerequisites
- A C++ compiler (e.g., `g++` or Visual Studio)
- Windows OS (for `windows.h` functions)

### Steps to Compile and Run
1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-repository/snake-game.git
   cd snake-game
   ```

2. **Compile the Code**:
   Use a C++ compiler to compile the source code:
   ```bash
   g++ -o snake_game snake_game.cpp -std=c++11
   ```

3. **Run the Game**:
   Execute the compiled program:
   ```bash
   ./snake_game
   ```

## Code Overview

### Key Components
- **`Point` Structure**: Represents a point in the console with `x` and `y` coordinates.
- **`Snake` Class**: Manages the snake's properties, movement, and interactions with food.
- **`Board` Class**: Handles the game logic, including rendering the snake and food, handling input, and updating the game state.
- **Main Loop**: Continuously updates the game state, processes input, and redraws the game until the game over condition is met.

## Customization
You can customize the game by:
- **Changing the Speed**: Modify the `Sleep(100)` function call to adjust the game speed.
- **Changing the Console Size**: Adjust the console window size for different playing areas.

## Known Issues
- The game is designed for Windows due to the use of `windows.h`. Running it on other operating systems might require changes.

## Contributions
Feel free to fork the repository and submit pull requests for improvements or bug fixes.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgements
- Inspired by the classic Snake game concept.
