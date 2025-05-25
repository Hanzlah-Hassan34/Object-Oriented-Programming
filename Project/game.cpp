
//============================================================================
// Name        : Brick Breker Game
// Author      : Hanzlah Hassan
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game ...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include "CImg.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

// for basic math functions such as cos, sin, sqrt
using namespace std;
using namespace cimg_library;
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for String
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class StringClass
{
public:
	// int to string conversion
	string int_to_string(int num)
	{
		string temp = "";
		int i = 0;
		if (num == 0)
			temp += '0';
		while (num != 0)
		{
			int tempInt = num % 10;
			char a = tempInt + 48;
			temp = a + temp;
			num /= 10;
		}
		return temp;
	}
	// int to string conversion
	int string_to_int(string str)
	{
		int temp = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			temp *= 10;
			temp += str[i] - 48;
		}
		return temp;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Classes for All Shapes
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Shape
{
protected:
	int base;
	int radius;
	const int triBase;

public:
	Shape() : base(50), triBase(32)
	{

		radius = 10;
	}
	int getBase()
	{
		return base;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for circle
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Circle : public Shape
{

public:
	// display the circle

	void display(int x, int y, char colour, int radiusLocal = 0)
	{
		radius += radiusLocal;
		if (colour == 'R')
			DrawCircle(x, y, radius, colors[RED]);
		else if (colour == 'G')
			DrawCircle(x, y, radius, colors[GREEN]);
		else if (colour == 'Y')
			DrawCircle(x, y, radius, colors[YELLOW]);
		else if (colour == 'B')
			DrawCircle(x, y, radius, colors[BLUE]);
		else if (colour == 'P')
			DrawCircle(x, y, radius, colors[DEEP_PINK]);
		else if (colour == 'O')
			DrawCircle(x, y, radius, colors[ORANGE_RED]);
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for Round Rectangle
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class RoundRectangle
{

public:
	// display the RoundRectangle

	void display(int x, int y, char colour, int heightLocal = 0, int widthLocal = 0, int i = 13) // #change colour
	{

		if (colour == 'R')
			DrawRoundRect(x, y, widthLocal, heightLocal, colors[RED], i);
		else if (colour == 'G')
			DrawRoundRect(x, y, widthLocal, heightLocal, colors[GREEN], i);
		else if (colour == 'Y')
			DrawRoundRect(x, y, widthLocal, heightLocal, colors[YELLOW], i);
		else if (colour == 'B')
			DrawRoundRect(x, y, widthLocal, heightLocal, colors[BLUE], i);
		else if (colour == 'P')
			DrawRoundRect(x, y, widthLocal, heightLocal, colors[DEEP_PINK], i);
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for triangle
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class triangle : public Shape
{
public:
	// display the triangle

	void display(int x, int y, char col)
	{
		if (col == 'Y')
			DrawTriangle(x, y, x + 20, y, x + 10, y + 20, colors[YELLOW]); // 9 to ajust in centre
		else if (col == 'B')
			DrawTriangle(x, y, x + 20, y, x + 10, y + 20, colors[BLUE]); // 9 to ajust in centre
		else if (col == 'G')
			DrawTriangle(x, y, x + 20, y, x + 10, y + 20, colors[GREEN]);	  // 9 to ajust in centre
		else if (col == 'P')												  // #set initials for each level brick
			DrawTriangle(x, y, x + 20, y, x + 10, y + 20, colors[DEEP_PINK]); // 9 to ajust in centre
		else if (col == 'R')
			DrawTriangle(x, y, x + 20, y, x + 10, y + 20, colors[RED]); // 9 to ajust in centre
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for rectangle
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Rectangle : public Shape
{
protected:
	int height;

public:
	// constructor
	Rectangle()
	{
		height = 20;
	}
	// display the Rectangle

	void display(int x, int y, char col, int heightlocal = 0, int width = 0)
	{
		if (heightlocal == 0)
			heightlocal = height;
		if (width == 0)
			width = base;
		if (col == 'Y')
			DrawRectangle(x, y, width, heightlocal, colors[22]);
		else if (col == 'B')
			DrawRectangle(x, y, width, heightlocal, colors[BLUE]);
		else if (col == 'G') // #
			DrawRectangle(x, y, width, heightlocal, colors[GREEN]);
		else if (col == 'P') // #set initials for each level brick
			DrawRectangle(x, y, width, heightlocal, colors[DEEP_PINK]);
		else if (col == 'R')
			DrawRectangle(x, y, width, heightlocal, colors[RED]);
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for square
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Square : public Shape
{
	int length;

protected:
	Square() // constructor
	{
		length = 20;
	}
	// display the Square

	void display(int x, int y, char col)
	{
		if (col == 'Y')
			DrawSquare(x, y, length, colors[YELLOW]);
		else if (col == 'B')
			DrawSquare(x, y, length, colors[BLUE]);
		else if (col == 'G') // #
			DrawSquare(x, y, length, colors[GREEN]);
		else if (col == 'P') // #set initials for each level brick
			DrawSquare(x, y, length, colors[DEEP_PINK]);
		else if (col == 'R')
			DrawSquare(x, y, length, colors[RED]);
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for Lives
//////
//////////////////////////////////////////////////////////////////////////////////////////////////////
class Lives : public Circle
{
protected:
	int numOfLives;
	int livesInitialX;
	int livesInitialY;

public:
	Lives() // contructor
	{
		resetLives();
	}
	void operator--(int) // decrease the lives
	{
		numOfLives -= 1;
	}
	void display() // display the remaining lives
	{
		DrawString(30, 20, "LIVES:  ", colors[GREEN]);
		for (int i = 0; i < numOfLives; i++)
		{
			for (int i = 0; i < numOfLives; i++)
			{
				Circle::display(livesInitialX + (i * 25), livesInitialY, 'O');
			}
		}
	}
	void resetLives() // reset the lives
	{
		numOfLives = 2;
		livesInitialX = 150;
		livesInitialY = 40;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for Ball
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Ball
{
	Circle circle;

protected:
	float ballX;
	float ballY;
	char ballColour;
	char ballMoveX;
	char ballMoveY;

public:
	Ball() // contructor
	{
		resetBall();
	}
	void operator=(const Ball &copy) // = overloading
	{
		ballX = copy.ballX;
		ballY = copy.ballY;
		ballColour = copy.ballColour;
		ballMoveX = copy.ballMoveX;
		ballMoveY = copy.ballMoveY;
	}
	void resetBall() // reset to initials
	{
		ballX = 350;
		ballY = 110;
		ballColour = 'R';
		ballMoveX = 'R';
		ballMoveY = 'U';
	}
	// setters
	void setBallMoveX(char move)
	{
		ballMoveX = move;
	}
	void setBallMoveY(char move)
	{
		ballMoveY = move;
	}
	void setBallColour(char color)
	{
		ballColour = color;
	}
	void setBallX(float x)
	{
		ballX = x;
	}

	void setBallY(float y)
	{
		ballY = y;
	}
	// getters
	char getBallMoveX()
	{
		return ballMoveX;
	}
	char getBallMoveY()
	{
		return ballMoveY;
	}
	char getBallColour()
	{
		return ballColour;
	}
	int getballX()
	{
		return ballX;
	}
	int getballY()
	{
		return ballY;
	}
	// display
	void display()
	{
		circle.display(ballX, ballY, ballColour);
	}
	// adjust X as according to speed
	void operator+(float x)
	{
		ballX += x;
	}
	void operator-(float x)
	{
		ballX -= x;
	}
	// adjust y as according to speed
	void operator-=(float y)
	{
		ballY -= y;
	}
	void operator+=(float y)
	{
		ballY += y;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for Paddles
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Paddle : public RoundRectangle
{
protected:
	// for paddle 1
	int paddleX1;
	int paddleY1;
	int height1;
	int width1;
	char colour1;
	// for paddle 2
	int paddleX2;
	int paddleY2;
	int height2;
	int width2;
	char colour2;
	/// total paddles
	static int numOfPaddles;

public:
	Paddle()
	{
		resetPaddle();
	}

	void resetPaddle(int x = 100, int y = 55, int y2 = 580)
	{
		paddleX1 = x;
		paddleY1 = y;
		height1 = 25;
		width1 = 100;
		colour1 = 'B';
		// for two
		paddleX2 = x;
		paddleY2 = y2;
		height2 = 25;
		width2 = 100;
		colour2 = 'B';
	}

	// Setter functions
	void setPaddleX1(int x)
	{
		paddleX1 = x;
	}

	void setPaddleY1(int y)
	{
		paddleY1 = y;
	}

	void setHeight1(int h)
	{
		height1 = h;
	}

	void setWidth1(int w)
	{
		width1 = w;
	}

	void setColour1(char c)
	{
		colour1 = c;
	}

	void setPaddleX2(int x)
	{
		paddleX2 = x;
	}
	void setNumberOfPaddles(int x)
	{
		numOfPaddles = x;
	}
	void setPaddleY2(int y)
	{
		paddleY2 = y;
	}

	void setHeight2(int h)
	{
		height2 = h;
	}

	void setWidth2(int w)
	{
		width2 = w;
	}

	void setColour2(char c)
	{
		colour2 = c;
	}

	// Getter functions
	int getPaddleX1()
	{
		return paddleX1;
	}

	int getPaddleY1()
	{
		return paddleY1;
	}

	int getHeight1()
	{
		return height1;
	}

	int getWidth1()
	{
		return width1;
	}
	int getWidth2()
	{
		return width2;
	}
	char getColour1()
	{
		return colour1;
	}

	int getPaddleX2()
	{
		return paddleX2;
	}

	int getPaddleY2()
	{
		return paddleY2;
	}

	int getHeight2()
	{
		return height2;
	}

	char getColour2()
	{
		return colour2;
	}
	// display paddles
	void display()
	{
		RoundRectangle::display(paddleX1, paddleY1, colour1, height1, width1);
		if (numOfPaddles == 2)
			RoundRectangle::display(paddleX2, paddleY2, colour2, height2, width2);
	}
};
int Paddle::numOfPaddles = 1;
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for Levels
//////
/////////////////////////////////////////////////////////////////////////////////////////////////////
class Level : public Lives // public Paddle
{
protected:
	int level;
	 int pattern[20][15];
	 int count[20][15];
	Paddle P;

public:
	Level()
	{
		level = 1;
		// //#remove

		setLevel();
		reset();
	}
	void reset() // reset for next level
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				pattern[i][j] = 0;
				count[i][j] = 0;
			}
		}
	}
	void setLevel() // set the level setting for next level
	{
		resetLives();
		reset();
		level++;
		setPattern();
		if (level == 3)
			P.setNumberOfPaddles(2);
	}
	void setPattern() // set pattern for different levels
	{
		reset();
		if (level == 1)
			setPatternFor1();
		else if (level == 2)
			setPatternFor2();
		else if (level == 3)
			setPatternFor3();
		// static int count=0;
		// count++;
		// cout <<"PP "<<count<<endl;
	}

	void setPatternFor1() // pattern for level 1
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (i >= 5 && i <= 12)
					pattern[i][j] = 1;
			}
		}
	}
	void setPatternFor2() // pattern for level 1
	{
		int count = 0; // 4 =height
		int height = 4;
		int width = 5;
		bool check = false;
		for (int i = 0; i < width * height; i++)
		{
			if (i % height == 0 && i != 0)
			{
				if (check == false)
					count++;
				else
					count--;
			}

			if (count == height / 2)
				check = true;
			for (int j = 0; j < 15; j++)
			{
				if (j / width == count)
				{
					pattern[i][j] = 1;
				}
				else
					pattern[i][j] = 0;
			}
		}
	}

	int brick(int num, int k, int l) // for setting the bricks
	{
		if (num == 0)
			return l;
		pattern[k][l] = 1;
		return brick(num - 1, k, l + 1);
	}

	int space(int i, int k, int l) // for leaving the emppty spaces
	{
		if (i <= 0)
			return l;
		pattern[k][l] = 0;
		return space(i - 1, k, l + 1);
	}
	int getLevel()
	{
		return level;
	}
	void drawPattern(int num, int i, int l, int realValue) // main recurrison function
	{
		if (num == 0)
			return;
		if (i == 0)
			l = brick(num - 1, realValue - num, l);
		else
			l = brick(num, realValue - num, l);

		l = space(i + i - 1, realValue - num, l);
		l = brick(num, realValue - num, l);

		drawPattern(num - 1, i + 1, 2, realValue);
		// reverse order
		l = 2;
		if (i == 0)
			l = brick(num - 1, num + realValue - 2, l);
		else
			l = brick(num, num + realValue - 2, l);

		l = space(i + i - 1, num + realValue - 2, l);
		l = brick(num, num + realValue - 2, l);
	}
	void setPatternFor3()
	{
		//  14 for 8 down and then start
		int num = 12 / 2;
		drawPattern(num, 0, 2, 14);
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for  Holding the PlayersRecord
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class PlayerRecord
{
protected:
	string playerName;
	string playerID;

public:
	PlayerRecord()
	{
		playerName = "Hanzlah";
		playerID = "23i-0085";
	}
	void display()
	{
		DrawString(5, 680, "Name: " + playerName, colors[MISTY_ROSE]);
		DrawString(200, 680, "ID: " + playerID, colors[MISTY_ROSE]);
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for Counting the Score
//////
/////////////////////////////////////////////////////////////////////////////////////////////////////
class Score : public PlayerRecord, public StringClass
{
protected:
	static int score;

public:
	void updateScore()
	{
		score += 1;
	}
	int getScore()
	{
		return score;
	}
	void displayScore()
	{ // display both player record and score
		PlayerRecord::display();
		DrawString(450, 680, "Score:  " + int_to_string(score), colors[MISTY_ROSE]);
	}
};
int Score ::score = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for  Food Records
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Food : public triangle, public Square, public Circle, public Rectangle
{
protected:
	int foodX;
	int foodY;
	char color;

public:
	Food()
	{
		// as default should be no food
		foodX = -20;
		foodY = -100;
	}
	void operator=(Food &copy) // ... copy constructor
	{
		foodX = copy.foodX;
		foodY = copy.foodY;
		color = copy.color;
	}
	// setters
	void setFoodX(int x)
	{
		foodX = x;
	}

	void setFoodY(int y)
	{
		foodY = y;
	}
	void setColor(char c)
	{
		color = c;
	}

	// Getter
	char getColor() const
	{
		return color;
	}
	int getFoodX() const
	{
		return foodX;
	}

	int getFoodY() const
	{
		return foodY;
	}
	// display according to food type
	void display()
	{
		if (color == 'G')
			triangle::display(foodX, foodY, color);
		else if (color == 'P')
			Square::display(foodX, foodY, color);
		else if (color == 'B')
			Circle::display(foodX, foodY, color);
		else if (color == 'R')
			Rectangle::display(foodX, foodY, color, 15, 40);
		else if (color == 'Y')
			Square::display(foodX, foodY, color);
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for Brick
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Brick : public Level, public Score
{
protected:
	const int initialBrickX;
	const int initialBrickY;
	char blockType[20][15];
	Rectangle rectangle;
	bool LevelUpdated;

public:
	Brick() : initialBrickX(30), initialBrickY(580), LevelUpdated(false) // constructor
	{
		setPattern();
		setBlockType();
	}
	void checkLevelUpdate() // updates the level when all no brick
	{
		bool check = true;
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (pattern[i][j] == 1)
				{
					check = false; 
					break;
				}
			}
		}
		if (check)
		{
			setLevel();
			setBlockType();
			LevelUpdated = true;
		}
	}

	void setBlockType() // set colors of bricks
	{
		srand(time(NULL));
		// first count
		//
		//
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (pattern[i][j] == 1)
				{
					int n = rand() % 5;

					if (n == 0)
						blockType[i][j] = 'Y';
					else if (n == 1)
						blockType[i][j] = 'B';
					else if (n == 2)
						blockType[i][j] = 'R';
					else if (n == 3)
						blockType[i][j] = 'P';
					else if (n == 4)
						blockType[i][j] = 'G';
				}
				else
				{
					blockType[i][j] = 'W';
				}
			}
		}
	}

	void display() // display the bricks
	{
		checkLevelUpdate(); // check is need of update level or not

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{

				rectangle.display(initialBrickX + (j * 50), initialBrickY - (i * 20), blockType[i][j]);
			}
		}
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for  File Handling
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class FileHandling
{
protected:
	int highScore;

public:
	FileHandling()
	{
		highScore = 0;
	} // string to int
	int string_to_int(string str)
	{
		int temp = 0;
		for (int i = 0; str[i] != '\0'; i++)
		{
			temp *= 10;
			temp += str[i] - 48;
		}
		return temp;
	} // to write the names && scores
	void write(string name, int score)
	{
		ofstream file;
		file.open("record.txt", ios::app);
		if (!file)
		{
			cout << "\nFile not opened" << endl;
		}
		else
		{
			file << name << endl;
			file << score << endl;
		}
		file.close();
	}
	// to read the  high scoes
	int read()
	{
		ifstream file;
		file.open("record.txt");
		if (!file)
		{
			cout << "\nFile not opened " << endl;
		}
		else
		{
			int temp = 0;
			int i = 0;
			string tempStr = "";
			while (!file.eof())
			{

				getline(file, tempStr);
				if (i % 2 == 1)
				{
					temp = string_to_int(tempStr);

					if (temp > highScore)
					{
						highScore = temp;
					}
				}
				i++;
			}
		}
		file.close();

		return highScore;
	}
};
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for  Stages(HOme ,Game,GameOver)
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Stages : public FileHandling, public Paddle, public Brick
{
public:
	static int stage;
	string name;
	string password;
	bool turn; // which box of login is deicded to fill by click;
	bool gameOver;

public:
	Stages()
	{
		name = "";
		password = "";
		turn = false;
		gameOver = false;
	}
	// Setters
	void setStage(int s)
	{
		stage = s;
	}

	void setName(const string &n)
	{
		name = n;
	}

	void setPassword(const string &p)
	{
		password = p;
	}

	void setTurn(bool t)
	{
		turn = t;
	}

	// Getters
	int getStage() const
	{
		return stage;
	}
	 bool getGameOver()
	{
		return gameOver;
	};
	virtual int getLevel() { return -1; };
	virtual void operator++(int) {};
	// virtual void setPaddleX1(int x) {};
	const string &getName() const
	{
		return name;
	}

	const string &getPassword() const
	{
		return password;
	}

	bool getTurn() const
	{
		return turn;
	}

	 void setGameOver(bool var)
	{
		gameOver = var;
	}
	virtual void addBall(int x)
	{
	}
	virtual void ResetGame()
	{
	}
	// dispaly each stage
	virtual void display()
	{
		if (stage == 1)
		{

			DrawRoundRect(200, 450, 400, 40, colors[RED], 20);
			DrawTriangle(400, 500, 350, 450, 450, 450, colors[BLACK]);
			DrawString(230, 460, "  LOGIN  ", colors[BLACK]);
			DrawString(450, 460, "  PAGE  ", colors[BLACK]);

			// name
			DrawRoundRect(190, 380, 170, 40, colors[RED], 20);
			DrawRectangle(190, 380, 20, 60, colors[BLACK]);
			DrawString(220, 390, "   NAME  ", colors[BLACK]);
			DrawRectangle(380, 380, 220, 40, colors[RED]);
			DrawString(400, 390, name, colors[BLACK]);
			// password
			DrawRoundRect(190, 310, 170, 40, colors[RED], 20);
			DrawRectangle(190, 310, 20, 60, colors[BLACK]);
			DrawString(220, 320, " PASSWORD ", colors[BLACK]);
			DrawRectangle(380, 310, 220, 40, colors[RED]);
			string temp = "";
			for (int i = 0; i < password.length(); i++)
			{
				temp += '*';
			}
			DrawString(400, 320, temp, colors[BLACK]);
			// play button
			DrawRoundRect(370, 200, 60, 60, colors[RED], 20);
			DrawTriangle(390, 250, 390, 210, 420, 230, colors[BLACK]);
		}

		else if (stage == 2)
		{ // game over  when
		}
		else if (stage == 3)
		{
			DrawLine(0, 400, 810, 400, 5, colors[WHITE]);
			DrawString(285, 420, "!!!  GAME OVER  !!!", colors[RED]);
			DrawLine(0, 460, 810, 460, 4, colors[WHITE]);
			DrawString(250, 360, "DO YOU WANT TO Continue..?\n", colors[RED]);
			DrawRoundRect(290, 290, 70, 40, colors[RED], 5);
			DrawString(300, 300, "YES", colors[BLACK]);
			DrawRoundRect(430, 290, 70, 40, colors[RED], 5);
			DrawString(440, 300, "NO", colors[BLACK]);
			if (gameOver == false)
			{
				level =- 1;
				stage = 2;
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 15; j++)
					{
						pattern[i][j] = 0;
					}
				}
				resetPaddle();
				checkLevelUpdate();
				// ResetGame();
			}
		}
		else if (stage == 4)
		{
			DrawLine(0, 400, 810, 400, 5, colors[WHITE]);
			DrawString(285, 420, "!!!  YOU WON THE GAME  !!!", colors[RED]);
			DrawLine(0, 460, 810, 460, 4, colors[WHITE]);
			DrawString(250, 360, "DO YOU WANT TO RESTART..?\n", colors[RED]);
			DrawRoundRect(290, 290, 70, 40, colors[RED], 5);
			DrawString(300, 300, "YES", colors[BLACK]);
			DrawRoundRect(430, 290, 70, 40, colors[RED], 5);
			DrawString(440, 300, "NO", colors[BLACK]);
			// if (gameOver == false)
			// {
			// 	level -= 1;
			// 	stage = 2;
			// 	for (int i = 0; i < 15; i++)
			// 	{
			// 		for (int j = 0; j < 20; j++)
			// 		{
			// 			pattern[i][j] = 0;
			// 		}
			// 	}
			// 	checkLevelUpdate();
			// }
		}
	}
};
int Stages::stage = 1;
/////////////////////////////////////////////////////////////////////////////////////////////////////
///////
///////              Class for Holding the Checks and dispaly for Game
//////
////////////////////////////////////////////////////////////////////////////////////////////////////
class Game : public Stages
{
protected:
	///  number of balls and its timer
	Ball *ball;
	int numOfBalls;
	int *timerOfBall;
	// number of foods
	Food *food;
	int numOfFoods;
	// for ball speed control
	int ballSpeedX;
	float ballAngleY;
	bool speedUp;
	bool speedDown;
	// resume
	bool resume;

public:
	Game()
	{
		ResetGame();
		gameOver = false;
	}
	void ResetGame()
	// set all to initials
	{

		ballSpeedX = 3;
		ballAngleY = 3;
		numOfBalls = 1;
		ball = new Ball[numOfBalls];
		numOfFoods = 0;
		food = new Food[numOfFoods];
		speedDown = false;
		speedUp = false;
		resume = false;
		timerOfBall = new int[numOfBalls];
		timerOfBall[0] = -1;
		gameOver = true;
		resetLives();
		
	}
	void addBall(int num)
	// add balls in array
	{
		Ball *tempBall = new Ball[numOfBalls + num];

		int i = 0;
		for (; i < numOfBalls; i++)
		{
			tempBall[i] = ball[i];
			// copy constructor as inherited deleted as base deleted for = operator
		}
		if (num == 2)
		{
			tempBall[i] + 50;
		}
		numOfBalls += num;

		ball = tempBall;
	}
	void addTime(int add = 2)
	// add the time of balls to array
	{
		int *temp = new int[numOfBalls + add];
		int i = 0;
		for (; i < numOfBalls; i++)
		{
			temp[i] = numOfBalls;
		}
		for (int j = 0; j < add; j++)
		{
			if (add == 1)
				temp[i] = -1;
			else
				temp[i] = 0;
			i++;
		}
		timerOfBall = temp;
	}
	// reomve timer for ball
	void removeTime(int i, int count)
	{
		int tempNum = i;
		i = tempNum % 10;
		tempNum /= 10;
		int *temp = new int[numOfBalls - count];
		int k = 0;

		for (int j = 0; j < numOfBalls; j++)
		{
			if (i == j)
			{
				i = tempNum % 10;
				tempNum /= 10;
			}
			else
			{
				temp[k] = timerOfBall[j];
				k++;
			}
		}
		count--;

		timerOfBall = temp;
	}
	// add food
	void addFood(int row, int column, char color)
	{ // add food in array
		Food *tempFood = new Food[numOfFoods + 1];

		int i = 0;
		for (; i < numOfFoods; i++)
		{
			tempFood[i] = food[i]; // copy constructor as inherited deleted as base deleted for = operator
		}
		// #add i j
		tempFood[i].setFoodX((column * 50) + 30 + 10); // 10 to be in centre
		tempFood[i].setFoodY(580 - (row * 20));
		tempFood[i].setColor(color);

		numOfFoods += 1;

		food = tempFood;
	}
	// reomve food in array

	void removeFood(int i)
	{ // remove array
		Food *tempFood = new Food[numOfFoods - 1];

		int k = 0;
		for (int j = 0; j < numOfFoods; j++)
		{
			if (i == j)
			{
				continue;
			}
			else
			{

				tempFood[k] = food[j];
				k++;
			}
		}
		numOfFoods--;
		food = tempFood;
	}
	// remove ball at index
	void removeBall(int i, int count)
	{
		// remove ball
		Ball *tempBall = new Ball[numOfBalls - count];
		int temp = i;

		int k = 0;
		i = temp % 10;
		temp /= 10;
		for (int j = 0; j < numOfBalls; j++)
		{
			if (i == j)
			{
				i = temp % 10;
				temp /= 10;
				continue;
			}
			else
			{
				tempBall[k] = ball[j];
				k++;
			}
		}

		numOfBalls -= count;
		ball = tempBall;
	}
	// display all
	void display()
	{ // all games requirements

		if (LevelUpdated == true || (gameOver == false && stage == 3))
		{
			LevelUpdated = false;
			ResetGame();
		}
		Paddle::display();
		brickCountCheck();
		Brick::display();
		displayBorder();
		// balldisplay
		for (int i = 0; i < numOfBalls; i++)
		{
			ball[i].display();
		}
		// display food
		Score::displayScore();
		checkLives();
		Lives::display();
		checkFood();
		for (int i = 0; i < numOfFoods; i++)
		{
			food[i].display();
		}
	}
	// check the lives number
	void checkLives()
	{
		int count = 0;
		int a = 0;
		for (int i = numOfBalls - 1; i >= 0; i--)
		{
			if (ball[i].getballY() < 0)
			{
				count += 1;
				a *= 10;
				a += i;

				// to remove ball from array
			}
			if (level == 3)
			{
				if (ball[i].getballY() > 600)
				{
					count += 1;
					a *= 10;
					a += i;
				}
			}
		}

		if (count != 0)
		{

			removeTime(a, count);
			removeBall(a, count);
		}
		if (numOfBalls == 0)
		{

			numOfLives--;

			if (numOfLives > 0)
			{
				addTime(1);
				addBall(1);
			}
			resume = true;
			if (numOfLives == 0)
			{
				// #gameover
				gameOver = true;
				ResetGame();
			}
		}
	}
	// check the count of bricks
	void brickCountCheck()
	{
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 15; j++)
			{

				if (blockType[i][j] == 'G')
				{
					if (count[i][j] >= 1)
					{
						pattern[i][j] = 0;
						addFood(i, j, blockType[i][j]);

						blockType[i][j] = 'W';
						Score::updateScore();
					}
				}
				// #play whole game is level correctly update
				else if (blockType[i][j] == 'P')
				{
					if (count[i][j] >= 2)
					{
						pattern[i][j] = 0;
						addFood(i, j, blockType[i][j]);
						blockType[i][j] = 'W';
						updateScore();
					}
				}
				else if (blockType[i][j] == 'B')
				{
					if (count[i][j] >= 3)
					{
						pattern[i][j] = 0;
						addFood(i, j, blockType[i][j]);
						blockType[i][j] = 'W';
						updateScore();
					}
				}
				else if (blockType[i][j] == 'R')
				{
					if (count[i][j] >= 3)
					{
						pattern[i][j] = 0;
						addFood(i, j, blockType[i][j]);
						blockType[i][j] = 'W';
						updateScore();
					}
				}
				else if (blockType[i][j] == 'Y')
				{
					if (count[i][j] >= 2)
					{
						pattern[i][j] = 0;
						addFood(i, j, blockType[i][j]);
						blockType[i][j] = 'W';
						updateScore();
					}
				}
			}
		}
	}
	// setter
	// check the balls for collision and change direction
	void checkBall()
	{

		//  check for paddles
		for (int k = 0; k < numOfBalls; k++)
		{ // for paddle 1
			// for y
			if (ball[k].getballY() - 10 <= paddleY1 + 25 && ball[k].getballY() - 10 > paddleY1)
			{
				// for x-axis of paddle

				if ((ball[k].getballX() + 10 >= paddleX1 && ball[k].getballX() < paddleX1 + (width1 / 2)))
				{
					ball[k].setBallMoveX('L');
					ball[k].setBallMoveY('U');

					Paddle::colour1 = ball[k].getBallColour();
					// ballAngleY=ball[k].getballX() + 10 - paddleX1;
					// ballAngleY/=30;
				}
				else if (ball[k].getballX() >= paddleX1 + (width1 / 2) && ball[k].getballX() - 10 <= paddleX1 + width1)
				{

					ball[k].setBallMoveX('R');
					ball[k].setBallMoveY('U');
					Paddle::colour1 = ball[k].getBallColour();
					// ballAngleY=ball[k].getballX() - paddleX1+(width1/2);
					// ballAngleY/=30;
				}
			}
			// for paddle 2
			if (level == 3)
			{
				if (ball[k].getballY() + 10 <= paddleY2 + 25 && ball[k].getballY() + 10 > paddleY2)
				{
					// for x-axis
					if ((ball[k].getballX() + 10 >= paddleX2 && ball[k].getballX() < paddleX2 + (width2 / 2)))
					{
						ball[k].setBallMoveX('L');
						ball[k].setBallMoveY('D');

						Paddle::colour2 = ball[k].getBallColour();
					}
					else if (ball[k].getballX() >= paddleX2 + (width2 / 2) && ball[k].getballX() - 10 <= paddleX2 + width2)
					{

						ball[k].setBallMoveX('R');
						ball[k].setBallMoveY('D');
						Paddle::colour2 = ball[k].getBallColour();
					}
				}
			}
			// check for wall
			if (ball[k].getballX() - 10 <= 30 || (ball[k].getballX() + 10 >= 780))
			{
				if (ball[k].getBallMoveX() == 'L')
					ball[k].setBallMoveX('R');
				else if (ball[k].getBallMoveX() == 'R')
					ball[k].setBallMoveX('L');
			}

			if (ball[k].getballY() + 10 >= 600 && level != 3)
			{
				ball[k].setBallMoveY('D');
			}
		}
		// check for bricks
		for (int k = 0; k < numOfBalls; k++)
		{
			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (pattern[i][j] == 1)
					{
						// check for left side
						if ((ball[k].getballX() + 10 >= ((j * 50) + 30) && (ball[k].getballX() + 10 <= ((j * 50) + 30 + 25))) && (((ball[k].getballY() + 10 > (580 - (i * 20))) && (ball[k].getballY() + 10 < (580 - (i * 20) + 10))) || ((ball[k].getballY() - 10 < 600 - (i * 20)) && ball[k].getballY() - 10 > 600 - (i * 20) - 10)))
						{

							ball[k].setBallMoveX('L');
							count[i][j] += 1;
							ball[k].setBallColour(blockType[i][j]);
						} // foe right side
						else if ((ball[k].getballX() - 10 <= ((j * 50) + 80) && ball[k].getballX() - 10 >= ((j * 50) + 80 - 10)) && (((ball[k].getballY() + 10 > (580 - (i * 20))) && (ball[k].getballY() + 10 < (580 - (i * 20) + 10))) || ((ball[k].getballY() - 10 < 600 - (i * 20)) && ball[k].getballY() - 10 > 600 - (i * 20) - 10)))
						{

							ball[k].setBallMoveX('R');

							count[i][j] += 1;
							ball[k].setBallColour(blockType[i][j]);
						}
						// upword
						if ((ball[k].getballY() - 10 <= (600 - (i * 20)) && ball[k].getballY() - 10 >= (600 - (i * 20)) - 10) && (((ball[k].getballX() + 10 > ((j * 50) + 30)) && (ball[k].getballX() + 10 < ((j * 50) + 80))) || ((ball[k].getballX() - 10 > ((j * 50) + 30)) && (ball[k].getballX() - 10 < ((j * 50) + 80)))))
						{

							ball[k].setBallMoveY('U');
							count[i][j] += 1;
							ball[k].setBallColour(blockType[i][j]);
						}
						else if ((ball[k].getballY() + 10 >= (580 - (i * 20)) && ball[k].getballY() + 10 <= (580 - (i * 20) + 10)) && (((ball[k].getballX() + 10 > ((j * 50) + 30)) && (ball[k].getballX() + 10 < ((j * 50) + 80))) || ((ball[k].getballX() - 10 > ((j * 50) + 30)) && (ball[k].getballX() - 10 < ((j * 50) + 80)))))
						{

							ball[k].setBallMoveY('D');
							// lower
							count[i][j] += 1;
							ball[k].setBallColour(blockType[i][j]);
						}
						// update count the
					}
				}
			}
		}
	}
	// check for actions of foos on strike with paddle
	void checkFood()
	{
		static int timerCount = 0;
		static int timeOfball = 0;
		for (int i = 0; i < numOfFoods; i++)
		{
			// check for below
			if (food[i].getFoodY() < 0)
			{
				removeFood(i);
			}
			// check for paddle
			if (food[i].getFoodY() >= paddleY1 && food[i].getFoodY() <= paddleY1 + height1)
			{
				// for square and triangle as base is 20
				if (food[i].getColor() == 'G' || food[i].getColor() == 'P' || food[i].getColor() == 'Y')
				{
					if ((food[i].getFoodX() >= paddleX1 && food[i].getFoodX() <= paddleX1 + width1) || (food[i].getFoodX() + 20 >= paddleX1 && food[i].getFoodX() + 20 <= paddleX1 + width1))
					{
						if (food[i].getColor() == 'G')
						{
							// as screen not range

							width1 *= 2;

							if (width1 > 750)
							{
								width1 = 750;
							}
							if (paddleX1 + width1 > 750)
							{
								paddleX1 = 750 - width1;
								if (paddleX1 == 0)
								{
									paddleX1 += 30;
								}
							}
							paddleX2 = paddleX1;
							width2 = width1;
						}
						if (food[i].getColor() == 'P')
						{
							width1 /= 2;
							if (width1 < 20)
							{
								width1 = 20;
							}
							width2 = width1;
						} // yellow food
						if (food[i].getColor() == 'Y')
						{
							addTime(2);
							addBall(2);
						}

						removeFood(i);
					}
				}
				// for rectangle
				else if (food[i].getColor() == 'R')
				{
					if ((food[i].getFoodX() >= paddleX1 && food[i].getFoodX() <= paddleX1 + width1) || (food[i].getFoodX() + 40 >= paddleX1 && food[i].getFoodX() + 40 <= paddleX1 + width1))
					{
						// ! if already
						if (speedUp == false)
						{
							ballSpeedX += 3;
							ballAngleY += 3;
						}
						speedUp = true;
						speedDown = false;
						timerCount = 0;
						removeFood(i);
					}
				}
			}
			// for circle blue food
			if (food[i].getColor() == 'B')
			{
				if (food[i].getFoodY() - 10 <= paddleY1 && food[i].getFoodY() - 10 >= paddleY1 - height1)
				{
					if ((food[i].getFoodX() + 10 >= paddleX1 && food[i].getFoodX() + 10 <= paddleX1 + width1) || (food[i].getFoodX() - 10 >= paddleX1 && food[i].getFoodX() - 10 <= paddleX1 + width1))
					{
						// ! if already
						if (speedDown == false && ballSpeedX >= 3)
						{
							ballSpeedX -= 2;
							ballAngleY -= 2;
						}
						speedDown = true;
						speedUp = false;
						timerCount = 0;

						removeFood(i);
					}
				}
			}
		}
		// timer for food
		if (speedUp == true && resume == false)
		{
			displayTimeBar(timerCount);
			timerCount++;
			if (timerCount == 300)
			{
				ballSpeedX = 3;
				ballAngleY = 3;
				speedUp = false;
				timerCount = 0;
			}
		}
		if (speedDown == true && resume == false)
		{
			displayTimeBar(timerCount);
			timerCount++;

			if (timerCount == 300)
			{
				ballSpeedX = 3;
				ballAngleY = 3;
				speedDown = false;
				timerCount = 0;
			}
		}
		checkTime();
	}
	void displayTimeBar(int time)
	{
		int temp = time / 30;
		temp = 10 - temp;
		DrawString(5, 640, "TimeBar: ", colors[MISTY_ROSE]);
		for (int i = 0; i < temp; i++)
		{
			DrawRoundRect((i * 35) + 110, 640, 30, 20, colors[i + 10], 4);
		}
	}
	// check the counter of time of balls
	void checkTime()
	{
		int a = 0;
		int count = 0;
		for (int i = numOfBalls - 1; i >= 0; i--)
		{
			if (timerOfBall[i] >= 300)
			{
				a *= 10;
				a += i;
				count += 1;
				// timerOfBall[i] = 0;
				// removeTime(i);
				// removeBall(i);
			}
		}
		if (count != 0)
		{
			removeTime(a, count);
			removeBall(a, count);
		}
	}
	// #Game +3 will add three ball
	// continue the for next level
	
	void operator++(int)
	{
		checkBall();
		if (resume)
		{
			// resume display
			static int timer = 0;
			timer++;
			if (timer <= 100)
			{
				DrawString(400, 180, "3", colors[MISTY_ROSE]);
			}
			else if (timer <= 200)
			{
				DrawString(400, 180, "2", colors[MISTY_ROSE]);
			}
			else if (timer <= 300)
			{
				DrawString(400, 180, "1", colors[MISTY_ROSE]);
				if (timer == 300)
				{
					resume = false;
					timer = 0;
				}
			}
		}
		else
		{
			// move ball
			for (int i = 0; i < numOfBalls; i++)
			{
				if (ball[i].getBallMoveX() == 'L')
					ball[i] - ballSpeedX;
				else if (ball[i].getBallMoveX() == 'R')
				{
					ball[i] + ballSpeedX;
				}
				// y axis
				if (ball[i].getBallMoveY() == 'U')
					ball[i] += ballAngleY;
				else if (ball[i].getBallMoveY() == 'D')
					ball[i] -= ballAngleY;
			}
			// move food
			for (int i = 0; i < numOfFoods; i++)
			{
				food[i].setFoodY(food[i].getFoodY() - 1);
			}
			// run timer
			for (int i = 1; i < numOfBalls; i++)
			{
				if (timerOfBall[i] != -1)
					timerOfBall[i] += 1;
			}
		}
	}
	~Game()
	{
		if (ball != NULL)
		{
			delete[] ball;
			ball = NULL;
		}
		if (food != NULL)
		{
			delete[] food;
			food = NULL;
		}
	}
	// display the border of the game
	void displayBorder()
	{
		for (int i = 0; i < 30; i++)
		{

			DrawRoundRect(0, i * 20, 30, 20, colors[i + 2], 8);
			DrawRoundRect(780, i * 20, 30, 20, colors[i + 2], 10);
		}
		if (level == 3)
		{
			for (int i = 0; i < 27; i++)
			{
				DrawRoundRect(i * 30, 600, 30, 20, colors[i + 2], 13);
			}
		}
		else
		{
			for (int i = 0; i < 27; i++)
			{
				DrawRoundRect(i * 30, 600, 30, 20, colors[i + 2], 15);
			}
		}
	}
};
void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
Stages *boardGlobal = new Stages;
// display game Function
void GameDisplay()
{

	glClearColor(0, 0,	  // 148.0/255/Green Component/,
				 0.0, 0); // Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);
	static Game *game = new Game;
	static Stages *stage = new Stages;

	if (boardGlobal->getStage() == 2)
	{

		boardGlobal = game;

		if (boardGlobal->getGameOver() == true && boardGlobal->getLevel() == 4)
		{

			boardGlobal->write(boardGlobal->getName(), boardGlobal->getScore());

			// stage++;
			boardGlobal->setStage(boardGlobal->getStage() + 2);
		}
		else if (boardGlobal->getGameOver() == true)
		{
			boardGlobal->write(boardGlobal->getName(), boardGlobal->getScore());
			// cout << boardGlobal->getScore()<<endl;
			boardGlobal->setStage(boardGlobal->getStage() + 1);
		}
		else
		{

			DrawString(600, 680, " Hi.Score: " + boardGlobal->int_to_string(boardGlobal->read()), colors[MISTY_ROSE]);
			// Game::checkBall();
			// Game::operator++(0);
			// Game::display();
			(*boardGlobal)++;
			boardGlobal->display();
		}
	}
	else
	{

		boardGlobal = stage;
		boardGlobal->display();

		// if (boardGlobal->getGameOver() == false && boardGlobal->getStage() == 3)
		// {
		// }
	}

	// Update the colors
	glutPostRedisplay();
	glutSwapBuffers(); // do not modify this line..
}
void NonPrintableKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
	{
		// what to do when left key is pressed...
	}
	else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
	{
	}
	else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
	{
	}
	else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
	{
	}
	glutPostRedisplay();
}
void PrintableKeys(unsigned char key, int x, int y)
{
	if (key == 27 /* Escape key ASCII*/)
	{
		exit(1); // exit the program when escape key is pressed.
	}
	if (boardGlobal->getStage() == 1)
	{
		// #mouse
		if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9'))
		{
			if (boardGlobal->getTurn() == false)
			{
				char a = key;

				string temp = boardGlobal->getName() + a;
				boardGlobal->setName(temp);
			}
			else if (boardGlobal->getTurn() == true)
			{
				char a = key;

				string temp = boardGlobal->getPassword() + a;
				boardGlobal->setPassword(temp);
			}
		}
	}
	else if (key == 'w' || key == 'W' && boardGlobal->getStage() == 2)
	{
		if (boardGlobal->getPaddleX2() > 40)
			boardGlobal->setPaddleX2(boardGlobal->getPaddleX2() - 30);
	}
	else if (key == 'r' || key == 'R')
	{
		if (boardGlobal->getPaddleX2() < 780 - boardGlobal->getWidth2() - 30)
		{
			boardGlobal->setPaddleX2(boardGlobal->getPaddleX2() + 30);
		}
	}
	glutPostRedisplay();
}
void Timer(int m)
{
	glutTimerFunc(100, Timer, 0);
	glutPostRedisplay();
}
void MousePressedAndMoved(int x, int y)
{
	// cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y)
{
	// ( ../2) for mid arrow
	if (x >= 30 + (boardGlobal->getWidth1() / 2) && x <= 780 - (boardGlobal->getWidth1() / 2))
	{
		boardGlobal->setPaddleX1(x - (boardGlobal->getWidth1() / 2)); // to stat design at - mid of width
	}
	glutPostRedisplay();
}
void MouseClicked(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && boardGlobal->getStage() == 1) // dealing only with left button
	{
		// cout << " X  " << x << "  y  " << y << endl;
		if (x >= 380 && x <= 500 && y >= 280 && y <= 320)
		{
			boardGlobal->setTurn(false);
		}
		else if (x >= 380 && x <= 500 && y >= 350 && y <= 390)
		{
			boardGlobal->setTurn(true);
		}
		else if (x >= 370 && x <= 430 && y >= 440 && y <= 500 && boardGlobal->getPassword() == "1234")
		{
			boardGlobal->setStage(2);
		}
	}
	else if (button == GLUT_LEFT_BUTTON && (boardGlobal->getStage() == 3) || boardGlobal->getStage() == 4) // dealing only with left button
	{

		if (x >= 290 && x <= 360 && y >= 360 && y <= 410)
		{
			boardGlobal->setGameOver(false);
		}
		else if (x >= 430 && x <= 500 && y >= 360 && y <= 410)
			exit(1);
	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		cout << "Right Button Pressed" << endl;
	}
	glutPostRedisplay();
}
int main(int argc, char *argv[])
{
	int width = 810, height = 700;				  // i have set my window size to be 800 x 600
	InitRandomizer();							  // seed the random number generator...
	glutInit(&argc, argv);						  // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(400, 50);			  // set the initial position of our window
	glutInitWindowSize(width, height);			  // set the size of our window
	glutCreateWindow("OOP Project By Hanzlah");	  // set the title of our game window
	SetCanvasSize(width, height);				  // set the number of pixels...
	glutDisplayFunc(GameDisplay);				  // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys);			  // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys);			  // tell library which function to call for printable ASCII characters
	glutTimerFunc(1000.0, Timer, 0);
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved);	  // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	glutMainLoop();
	return 1;
}
#endif