#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>


using namespace std;

// Define the grid size
const int GRID_SIZE = 20;

// Define the maximum score
const int MAX_SCORE = 50;

// Define the symbols for the snake, food, and empty space
const char SNAKE_SYMBOL = 'O';
const char FOOD_SYMBOL = 'X';
const char EMPTY_SYMBOL = ' ';

// Define the directions that the snake can move
const int LEFT = 0;
const int RIGHT = 1;
const int UP = 2;
const int DOWN = 3;

// Define the structure for the snake
struct Snake
{
	int x;
	int y;
	int direction;
};

// Define the structure for the food
struct Food
{
	int x;
	int y;
};

// Declare the functions
void InitializeGame(Snake& snake, Food& food);
void UpdateSnake(Snake& snake);
bool CheckCollision(Snake& snake, Food& food);
void GenerateFood(Food& food, Snake& snake);
void DrawGrid(Snake& snake, Food& food);


int main()
{
	srand(time(NULL));

	// Create the snake and food
	Snake snake;
	Food food;

	// Initialize the game
	InitializeGame(snake, food);

	// Set the initial score to 0
	int score = 0;

	// Main game loop
	while (true)
	{
		if (_kbhit())
		{
			// Get the input from the user
			char input = _getch();

			// Set the direction of the snake based on the input
			if (input == 'w')
			{
				snake.direction = UP;
			}
			else if (input == 's')
			{
				snake.direction = DOWN;
			}
			else if (input == 'a')
			{
				snake.direction = LEFT;
			}
			else if (input == 'd')
			{
				snake.direction = RIGHT;
			}
		}

		// Check if the snake has collided with the food
		if (CheckCollision(snake, food))
		{
			// Generate new food
			GenerateFood(food, snake);

			// Increase the score
			score++;
		}

		// Draw the grid
		DrawGrid(snake, food);

		// Update snake
		UpdateSnake(snake);

		// Check if the snake has reached the maximum score or collided with a wall or itself
		if (score == MAX_SCORE || snake.x == 0 || snake.x == GRID_SIZE + 1 || snake.y == 0 || snake.y == GRID_SIZE + 1)
		{
			// End the game
			break;
		}

		// Delay the game to slow down the snake's movement
		Sleep(100);

	}

	// Display the final score
	cout << "Your final score is: " << score << endl;

	return 0;
}



// Initialize the game
void InitializeGame(Snake& snake, Food& food)
{
	// Set the snake's initial position and direction
	snake.x = GRID_SIZE / 2;
	snake.y = GRID_SIZE / 2;
	snake.direction = RIGHT;

	// Generate the initial food
	GenerateFood(food, snake);
}

// Update the snake's position
void UpdateSnake(Snake& snake)
{
	// Save the current position
	int x = snake.x;
	int y = snake.y;

	// Update the position based on the direction
	if (snake.direction == LEFT)
	{
		x--;
	}
	else if (snake.direction == RIGHT)
	{
		x++;
	}
	else if (snake.direction == UP)
	{
		y--;
	}
	else if (snake.direction == DOWN)
	{
		y++;
	}

	// Update the snake's position
	snake.x = x;
	snake.y = y;
}


// Check if the snake has collided with the food
bool CheckCollision(Snake& snake, Food& food)
{
	// Check if the snake's position matches the food's position
	return snake.x == food.x && snake.y == food.y;
}

// Generate new food
void GenerateFood(Food& food, Snake& snake)
{
	// Generate new food at a random position on the grid
	food.x = rand() % GRID_SIZE + 1;
	food.y = rand() % GRID_SIZE + 1;
}

// Draw the grid
void DrawGrid(Snake& snake, Food& food)
{
	// Clear the screen
	system("cls");

	// Draw the top border
	cout << "+";
	for (int i = 0; i < GRID_SIZE; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;

	// Draw the grid
	for (int y = 0; y < GRID_SIZE; y++)
	{
		cout << "|";
		for (int x = 0; x < GRID_SIZE; x++)
		{
			// Check if the current position is the snake's position
			if (x == snake.x && y == snake.y)
			{
				cout << SNAKE_SYMBOL;
			}
			// Check if the current position is the food's position
			else if (x == food.x && y == food.y)
			{
				cout << FOOD_SYMBOL;
			}
			// Otherwise, print an empty space
			else
			{
				cout << EMPTY_SYMBOL;
			}
		}
		cout << "|" << endl;
	}

	// Draw the bottom border
	cout << "+";
	for (int i = 0; i < GRID_SIZE; i++)
	{
		cout << "-";
	}
	cout << "+" << endl;
}