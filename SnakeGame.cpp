#include <iostream>  // For standard input/output
#include <conio.h>   // For keyboard input functions like kbhit and getch
#include <windows.h> // For Windows-specific functions like Sleep, gotoxy
#include <cstdlib>   // For random number generation (rand, srand)
#include <ctime>     // For seeding random numbers with time

using namespace std;

#define MAX_LENGTH 1000 // Maximum length of the snake

// Directions for snake movement
const char DIR_UP = 'U';
const char DIR_DOWN = 'D';
const char DIR_LEFT = 'L';
const char DIR_RIGHT = 'R';

int consoleWidth, consoleHeight;

// Function to initialize the console screen dimensions
void initScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

// Structure representing a point (x, y) on the console
struct Point
{
    int xCoord;
    int yCoord;
    Point() : xCoord(0), yCoord(0) {}             // Default constructor
    Point(int x, int y) : xCoord(x), yCoord(y) {} // Constructor with parameters
};

// Snake class representing the snake entity
class Snake
{
    int length;     // Current length of the snake
    char direction; // Current direction of the snake
public:
    Point body[MAX_LENGTH]; // Array to store the snake's body segments

    // Constructor to initialize snake's starting position and direction
    Snake(int x, int y) : length(1), direction(DIR_RIGHT)
    {
        body[0] = Point(x, y); // Initial position of the snake's head
    }

    // Method to get the current length of the snake
    int getLength()
    {
        return length;
    }

    // Method to change the direction of the snake based on user input
    void changeDirection(char newDirection)
    {
        // Prevents reversing direction to avoid immediate collision
        if (newDirection == DIR_UP && direction != DIR_DOWN)
            direction = newDirection;
        else if (newDirection == DIR_DOWN && direction != DIR_UP)
            direction = newDirection;
        else if (newDirection == DIR_LEFT && direction != DIR_RIGHT)
            direction = newDirection;
        else if (newDirection == DIR_RIGHT && direction != DIR_LEFT)
            direction = newDirection;
    }

    // Method to move the snake and check for collisions or food
    bool move(Point food)
    {
        // Move each segment to the position of the previous one
        for (int i = length - 1; i > 0; i--)
        {
            body[i] = body[i - 1];
        }

        // Update the head's position based on the current direction
        switch (direction)
        {
        case DIR_UP:
            body[0].yCoord -= 1;
            break;
        case DIR_DOWN:
            body[0].yCoord += 1;
            break;
        case DIR_RIGHT:
            body[0].xCoord += 1;
            break;
        case DIR_LEFT:
            body[0].xCoord -= 1;
            break;
        }

        // Check if the snake bites itself
        for (int i = 1; i < length; i++)
        {
            if (body[0].xCoord == body[i].xCoord && body[0].yCoord == body[i].yCoord)
            {
                return false; // Snake collision with itself
            }
        }

        // Check if the snake eats the food
        if (body[0].xCoord == food.xCoord && body[0].yCoord == food.yCoord)
        {
            body[length] = Point(body[length - 1].xCoord, body[length - 1].yCoord);
            length++; // Increase snake's length
        }

        return true;
    }
};

// Board class representing the game board
class Board
{
    Snake *snake;                // Pointer to the snake object
    const char SNAKE_BODY = 'O'; // Character representing the snake body
    Point food;                  // Current food position
    const char FOOD = 'o';       // Character representing the food
    int score;                   // Player's score
public:
    // Constructor to initialize the game board, spawn initial food, and create snake
    Board() : score(0)
    {
        spawnFood();               // Place initial food on the board
        snake = new Snake(10, 10); // Create the snake at position (10, 10)
    }

    // Destructor to clean up dynamically allocated memory
    ~Board()
    {
        delete snake;
    }

    // Method to get the current score
    int getScore()
    {
        return score;
    }

    // Method to spawn food at a random location on the board
    void spawnFood()
    {
        int x = rand() % consoleWidth;
        int y = rand() % consoleHeight;
        food = Point(x, y); // Set new food position
    }

    // Method to display the current score at the top center of the console
    void displayCurrentScore()
    {
        gotoxy(consoleWidth / 2, 0);
        cout << "Score: " << score;
    }

    // Method to set the console cursor position to (x, y)
    void gotoxy(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }

    // Method to draw the game board, snake, and food
    void draw()
    {
        system("cls"); // Clear the console
        // Draw the snake
        for (int i = 0; i < snake->getLength(); i++)
        {
            gotoxy(snake->body[i].xCoord, snake->body[i].yCoord);
            cout << SNAKE_BODY;
        }
        // Draw the food
        gotoxy(food.xCoord, food.yCoord);
        cout << FOOD;

        displayCurrentScore(); // Display the score
    }

    // Method to update the game state (move snake, check for collisions, handle food)
    bool update()
    {
        bool isAlive = snake->move(food);
        if (!isAlive)
            return false; // End game if snake collides with itself

        // Check if the snake eats the food
        if (food.xCoord == snake->body[0].xCoord && food.yCoord == snake->body[0].yCoord)
        {
            score++;     // Increase score
            spawnFood(); // Spawn new food
        }
        return true;
    }

    // Method to get user input and change snake direction
    void getInput()
    {
        if (kbhit())
        {                      // Check if a key is pressed
            int key = getch(); // Get the pressed key
            // Change direction based on key pressed
            if (key == 'w' || key == 'W')
                snake->changeDirection(DIR_UP);
            else if (key == 'a' || key == 'A')
                snake->changeDirection(DIR_LEFT);
            else if (key == 's' || key == 'S')
                snake->changeDirection(DIR_DOWN);
            else if (key == 'd' || key == 'D')
                snake->changeDirection(DIR_RIGHT);
        }
    }
};

// Main function to run the game
int main()
{
    srand(time(0));             // Seed random number generator
    initScreen();               // Initialize screen dimensions
    Board *board = new Board(); // Create game board

    // Game loop: update state, get input, and draw
    while (board->update())
    {
        board->getInput();
        board->draw();
        Sleep(100); // Delay to control game speed
    }

    // Game over: display final score
    cout << "Game over!" << endl;
    cout << "Final score: " << board->getScore() << endl;

    delete board; // Clean up the board
    return 0;
}
