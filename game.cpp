


#include "util.h"
#include <iostream>
#include<string>
#include<fstream>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
bool menu = true, grid = false, play = false, leaderboards = false;
string leaderboard[11][2];
int p_bigship_[3],p_medship[2][3], p_smallship[3][3],p_smallest[4][3];
//for bot
int b_bigship_[3], b_medship[2][3], b_smallship[3][3], b_smallest[4][3];
int last_click_x, last_click_y;
int x = 60, y = 570;
bool p_turn = false, b_turn = false;
string name;
int score = 0;
int turns = 50;
void init()
{
	for (int i = 0; i < 3; i++)
	{
		p_bigship_[i] = 0;
		p_medship[0][i] = 0;
		p_medship[1][i]  =0;
		p_smallship[0][i] = 0;
		p_smallship[1][i] =0 ;
		p_smallship[2][i] = 0;
		p_smallest[0][i] = 0;
		p_smallest[1][i] = 0;
		p_smallest[2][i] = 0;
		p_smallest[3][i] =0 ;
		
	}
}

//battleship game
// 1. menu
// 2. grid
// 3. play
// 4. leaderboard
// 5. exit
// 6. game over
// 7. win
// 8. lose
// 9. draw
// 10. pause
// 11. resume
// 12. restart
// 13. quit
// 14. new game
// 15. save
// 16. load
// 17. settings
// 18. help
// 19. about
// 20. credits
// 21. exit
// 22. main menu
// 23. quit

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

int ind1=-1, ind2=-1;
bool missed = false, hit = false;
bool wins = false;
bool win()
{
	if (b_bigship_[0] == -99 && b_medship[0][0] == -99 && b_medship[1][0] == -99 && b_smallship[0][0] == -99 && b_smallship[1][0] == -99 && b_smallship[2][0] == -99 && b_smallest[0][0] == -99 && b_smallest[1][0] == -99 && b_smallest[2][0] == -99 && b_smallest[3][0] == -99)
		return true;
	return false;
}
bool turn = false;
int score2 = 0;
int hits = 0;
void simulate()
{
	int xcor = 50 * ((rand() % 400 + 100) / 50);
	int ycor = 50 * ((rand() % 500 + 200) / 50);
	if (xcor == p_bigship_[0] && ycor == p_bigship_[1])
	{
		score2 += 60;
		p_bigship_[0]=p_bigship_[1] = -99;
	}
	else if (xcor == p_medship[0][0] && ycor == p_medship[0][1])
	{
		score2 += 60;
		p_medship[0][0] = p_medship[0][1] = -99;

	}
	else if (xcor == p_medship[1][0] && ycor == p_medship[1][1])
	{
		score2 += 60;
		p_medship[0][0] = p_medship[0][1] = -99;
		p_medship[1][2] = -99;
	}
	else if (xcor == p_smallship[0][0] && ycor == p_smallship[0][1])
	{
		score2 += 60;
		p_smallship[0][0] = p_smallship[0][1] = -99;
		p_smallship[0][2] = -99;
	}
	else if (xcor == p_smallship[1][0] && ycor == p_smallship[1][1])
	{
		score2 += 60;
		p_smallship[1][0] = p_smallship[1][1] = -99;
		p_smallship[1][2] = -99;
	}
	else if (xcor == p_smallship[2][0] && ycor == p_smallship[2][1])
	{
		score2 += 60;
		p_smallship[2][0] = p_smallship[2][1] = -99;
		p_smallship[2][2] = -99;
	}
	else if (xcor == p_smallest[0][0] && ycor == p_smallest[0][1])
	{
		score2 += 60;
		p_smallest[0][0] = p_smallest[0][1] = -99;
		p_smallest[0][2] = -99;
	}
	else if (xcor == p_smallest[1][0] && ycor == p_smallest[1][1])
	{
		score2 += 60;
		p_smallest[1][0] = p_smallest[1][1] = -99;

	}
	else if (xcor == p_smallest[2][0] && ycor == p_smallest[2][1])
	{
		score2 += 60;
		p_smallest[02][0] = p_smallest[02][1] = -99;

		p_smallest[2][2] = -99;
	}
	else if (xcor == p_smallest[3][0] && ycor == p_smallest[3][1])
	{
		score2 += 60;
		p_smallest[03][0] = p_smallest[03][1] = -99;

		p_smallest[3][2] = -99;
	}
	turn = false;
}
bool gameover()
{
	if (p_bigship_[0] == -99 && p_medship[0][0] == -99 && p_medship[1][0] == -99 && p_smallship[0][0] == -99 && p_smallship[1][0] == -99 && p_smallship[2][0] == -99 && p_smallest[0][0] == -99 && p_smallest[1][0] == -99 && p_smallest[2][0] == -99 && p_smallest[3][0] == -99)
		return true;
	return false;
}
bool winss = false;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//Red Square
	//draw grid
	if (menu)
	{
		DrawString(400, 550, "PLAY");
		DrawString(400, 600, "LEADERBOARD");
		DrawString(400, 650, "EXIT");
	}
	if (grid == true) {
		DrawString(300, 800, "Set Your Board or PRESS A for Auto");
		float* coloor;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if(100+50*i==p_bigship_[0] && 200+50*j==p_bigship_[1])
					DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[BLUE]);
				else if((100+50*i==p_medship[0][0] && 200+50*j==p_medship[0][1]) || (100 + 50 * i == p_medship[1][0] && 200 + 50 * j == p_medship[1][1]))//100,200,600,700
					DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[RED]);
				else if((100 + 50 * i == p_smallship[0][0] && 200 + 50 * j == p_smallship[0][1])|| (100 + 50 * i == p_smallship[1][0] && 200 + 50 * j == p_smallship[1][1])|| (100 + 50 * i == p_smallship[2][0] && 200 + 50 * j == p_smallship[2][1]))
					DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[PURPLE]);
				else if ((100 + 50 * i == p_smallest[0][0] && 200 + 50 * j == p_smallest[0][1]) || (100 + 50 * i == p_smallest[1][0] && 200 + 50 * j == p_smallest[1][1]) || (100 + 50 * i == p_smallest[2][0] && 200 + 50 * j == p_smallest[2][1]) || (100 + 50 * i == p_smallest[3][0] && 200 + 50 * j == p_smallest[3][1]))
					DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[GREEN]);

				else
					DrawSquare(100+50  * i, 200 + 50 * j, 50, colors[WHITE]);//100,200,550,650
			}
		}
		float* color;
		if (p_bigship_[2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if(p_bigship_[0] == 0)
			DrawRectangle(650, 300-50 - 50, 200, 15, color);
		if (p_medship[0][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if(p_medship[0][0]==0)
			DrawRectangle(650, 350 - 50 - 50, 150, 15, color);
		if (p_medship[1][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if (p_medship[1][0] == 0)
			DrawRectangle(650, 400 - 50 - 50, 150, 15, color);
		if (p_smallship[0][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if (p_smallship[0][0] == 0)
			DrawRectangle(650, 450 - 50 - 50, 100, 15, color);
		if (p_smallship[1][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if (p_smallship[1][0] == 0)
			DrawRectangle(650, 500 - 50 - 50, 100, 15, color);
		if (p_smallship[2][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if (p_smallship[2][0] == 0)
			DrawRectangle(650, 550 - 50 - 50, 100, 15, color);
		if (p_smallest[0][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if (p_smallest[0][0] == 0)
			
			DrawRectangle(650, 600 - 50 - 50, 100, 15, color);
		if (p_smallest[1][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if (p_smallest[1][0] == 0)
			DrawRectangle(650, 650 - 50 - 50, 50, 15, color);
		if (p_smallest[2][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if (p_smallest[2][0] == 0)
			DrawRectangle(650, 700 - 50 - 50, 50, 15, color);
		if (p_smallest[3][2])
			color = colors[BLUE];
		else
			color = colors[RED];
		if (p_smallest[3][0] == 0)
			DrawRectangle(650, 750 - 50-50, 50, 15, color);
		
		
		
		
	}
	if (play)
	{
		DrawString(300, 800, "PLAYER SCORE: " + to_string(score));
		DrawString(600, 800, "COMPUTER SCORE: " + to_string(score2));
		for (int i = 0; i < 10;i++)
		{
			for (int j = 0; j < 10; j++)
			{
				//if (100 + 50 * i == b_bigship_[0] && 200 + 50 * j == b_bigship_[1])
				//	DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[BLUE]);
				//else if ((100 + 50 * i == b_medship[0][0] && 200 + 50 * j == b_medship[0][1]) || (100 + 50 * i == b_medship[1][0] && 200 + 50 * j == b_medship[1][1]))//100,200,600,700
				//	DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[RED]);
				//else if ((100 + 50 * i == b_smallship[0][0] && 200 + 50 * j == b_smallship[0][1]) || (100 + 50 * i == b_smallship[1][0] && 200 + 50 * j == b_smallship[1][1]) || (100 + 50 * i == b_smallship[2][0] && 200 + 50 * j == b_smallship[2][1]))
				//	DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[PURPLE]);
				//else if ((100 + 50 * i == b_smallest[0][0] && 200 + 50 * j == b_smallest[0][1]) || (100 + 50 * i == b_smallest[1][0] && 200 + 50 * j == b_smallest[1][1]) || (100 + 50 * i == b_smallest[2][0] && 200 + 50 * j == b_smallest[2][1]) || (100 + 50 * i == b_smallest[3][0] && 200 + 50 * j == b_smallest[3][1]))
				//	DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[GREEN]);
				//else
					DrawSquare(100 + 50 * i, 200 + 50 * j, 50, colors[WHITE]);
				
			}
		}
		DrawString(700, 500, "TURNS LEFT: " + to_string(turns));
		if (win())
		{
			play = false;
			wins = true;
		}
		if (gameover())
		{
			play = false;
			winss = true;
		}
		if(turn)
			simulate();
		if (turns == 0)
		{
			if (score > score2)
			{
				play = false;
				wins = true;
			}
			else
			{
				play = false;
				winss = true;
			}
		}
		
	}
	if (wins)
	{
		DrawString(600, 400, "PLAYER WINS");
	}
	if (winss)
	{
		
		DrawString(600, 400, "COMPUTER WINS");
	}
	if (leaderboards)
	{
		DrawString(600, 600, "LEADERBOARD");
		for (int i = 0; i < 10; i++)
		{
			DrawString(600, 550 - 50 * i, to_string(i + 1) + ". " + leaderboard[i][0] + " " + leaderboard[i][1]);		
		}
	}
	glutSwapBuffers(); // do not modify this line..

}
int inrect(int last_click_x,int last_click_y,int x, int y, int w, int h)
{
	
	if (last_click_x >= x && last_click_x <= x + w && last_click_y >= y && last_click_y <= y + h) {
		return 1;
	}
	return -99;
}

void readfile()
{
	fstream files("leaderboard.txt");
	string line;
	int i = 0;
	while (getline(files, line,' '))
	{
		leaderboard[i][0] = line;
		getline(files, line);
		leaderboard[i][1] = line;
		i++;

	}
	files.close();
	for(int i = 0; i < 10; i++)
	{
		cout << leaderboard[i][0] << '\t' << leaderboard[i][1] << endl;
	}
	
}
void writefile()
{
	leaderboard[10][0] = name;
	leaderboard[10][1] = to_string(score);
	for (int i = 0; i < 11; i++)
	{
		for (int j = i+1; j < 11; j++)
		{
			if (stoi(leaderboard[i][1]) > stoi(leaderboard[j][1]))
			{
				string temp[2];
				temp[0] = leaderboard[i][0];
				temp[1] = leaderboard[i][1];
				leaderboard[i][0] = leaderboard[j][0];
				leaderboard[i][1] = leaderboard[j][1];
				leaderboard[j][0] = temp[0];
				leaderboard[j][1] = temp[1];
			}
		}
	}
	ofstream files("leaderboard.txt");
	for (int i = 10; i >0; i--)
	{
		files << leaderboard[i][0] << ' ' << leaderboard[i][1] << endl;
	}
	files.close();
	
}
bool collision(int rx1, int ry1, int rl1, int rw1, int rx2, int ry2, int rl2, int rw2)
{
	if (rx1 + rw1 >= rx2 && rx1 <= rx2 + rw2 && ry1 + rl1 >= ry2 && ry1 <= ry2 + rl2)
		return true;
	return false;
}
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */
void randomize()
{
	
		p_bigship_[0] = 50*((rand()%400+100)/50);
		p_bigship_[1] = 50*((rand() % 500 + 100)/50);
		
		p_medship[0][0] = 50 * ((rand() % 400 + 100) / 50);
		p_medship[0][1] = 50 * ((rand() % 500 + 100) / 50);
		while (collision(p_medship[0][0], p_medship[0][1], 150, 150, p_bigship_[0], p_bigship_[1], 200, 200))
		{
			p_medship[0][0] = 50 * ((rand()  % 400 + 100) / 50);
			p_medship[0][1] = 50 * ((rand()  % 500 + 100) / 50);
		}
		p_medship[1][0] = 50 * ((rand() % 400 + 100) / 50);
		p_medship[1][1] = 50 * ((rand() % 500 + 100) / 50);
		while ((collision(p_medship[1][0], p_medship[1][1], 150, 150, p_bigship_[0], p_bigship_[1], 200, 200) && collision(p_medship[1][0], p_medship[1][1], 150, 150, p_medship[0][0], p_medship[0][1], 150, 150)));
		{
			p_medship[1][0] = 50 * ((rand() % 400 + 100) / 50);
			p_medship[1][1] = 50 * ((rand() % 500 + 100) / 50);
		}
		p_smallship[0][0] = 50 * ((rand() % 400 + 100) / 50);
		p_smallship[0][1] = 50 * ((rand() % 500 + 100) / 50);
		while ((collision(p_smallship[0][0], p_smallship[0][1], 100, 100, p_bigship_[0], p_bigship_[1], 200, 200) && collision(p_smallship[0][0], p_smallship[0][1], 100, 100, p_medship[0][0], p_medship[0][1], 150, 150) && collision(p_smallship[0][0], p_smallship[0][1], 100, 100, p_medship[1][0], p_medship[1][1], 150, 150)))
		{
			p_smallship[0][0] = 50 * ((rand() % 400 + 100) / 50);
			p_smallship[0][1] = 50 * ((rand() % 500 + 100) / 50);
		}
		p_smallship[1][0] = 50 * ((rand() % 400 + 100) / 50);
		p_smallship[1][1] = 50 * ((rand() % 500 + 100) / 50);
		while ((collision(p_smallship[1][0], p_smallship[1][1], 100, 100, p_bigship_[0], p_bigship_[1], 200, 200) && collision(p_smallship[1][0], p_smallship[1][1], 100, 100, p_medship[0][0], p_medship[0][1], 150, 150) && collision(p_smallship[1][0], p_smallship[1][1], 100, 100, p_medship[1][0], p_medship[1][1], 150, 150) && collision(p_smallship[1][0], p_smallship[1][1], 100, 100, p_smallship[0][0], p_smallship[0][1], 100, 100)))
		{
			p_smallship[1][0] = 50 * ((rand() % 400 + 100) / 50);
			p_smallship[1][1] = 50 * ((rand() % 500 + 100) / 50);
		}
		p_smallship[2][0] = 50 * ((rand() % 400 + 100) / 50);
		p_smallship[2][1] = 50 * ((rand() % 500 + 100) / 50);
		while ((collision(p_smallship[2][0], p_smallship[2][1], 100, 100, p_bigship_[0], p_bigship_[1], 200, 200) && collision(p_smallship[2][0], p_smallship[2][1], 100, 100, p_medship[0][0], p_medship[0][1], 150, 150) && collision(p_smallship[2][0], p_smallship[2][1], 100, 100, p_medship[1][0], p_medship[1][1], 150, 150) && collision(p_smallship[2][0], p_smallship[2][1], 100, 100, p_smallship[0][0], p_smallship[0][1], 100, 100) && collision(p_smallship[2][0], p_smallship[2][1], 100, 100, p_smallship[1][0], p_smallship[1][1], 100, 100)))
		{
			p_smallship[2][0] = 50 * ((rand() % 400 + 100) / 50);
			p_smallship[2][1] = 50 * ((rand() % 500 + 100) / 50);
		}
		p_smallest[0][0] = 50 * ((rand() % 400 + 100) / 50);
		p_smallest[0][1] = 50 * ((rand() % 500 + 100) / 50);
		while ((collision(p_smallest[0][0], p_smallest[0][1], 50, 50, p_bigship_[0], p_bigship_[1], 200, 200) && collision(p_smallest[0][0], p_smallest[0][1], 50, 50, p_medship[0][0], p_medship[0][1], 150, 150) && collision(p_smallest[0][0], p_smallest[0][1], 50, 50, p_medship[1][0], p_medship[1][1], 150, 150) && collision(p_smallest[0][0], p_smallest[0][1], 50, 50, p_smallship[0][0], p_smallship[0][1], 100, 100) && collision(p_smallest[0][0], p_smallest[0][1], 50, 50, p_smallship[1][0], p_smallship[1][1], 100, 100) && collision(p_smallest[0][0], p_smallest[0][1], 50, 50, p_smallship[2][0], p_smallship[2][1], 100, 100)))
		{
			p_smallest[0][0] = 50 * ((rand() % 400 + 100) / 50);
			p_smallest[0][1] = 50 * ((rand() % 500 + 100) / 50);
		}
		p_smallest[1][0] = 50 * ((rand() % 400 + 100) / 50);
		p_smallest[1][1] = 50 * ((rand() % 500 + 100) / 50);
		while ((collision(p_smallest[1][0], p_smallest[1][1], 50, 50, p_bigship_[0], p_bigship_[1], 200, 200) && collision(p_smallest[1][0], p_smallest[1][1], 50, 50, p_medship[0][0], p_medship[0][1], 150, 150) && collision(p_smallest[1][0], p_smallest[1][1], 50, 50, p_medship[1][0], p_medship[1][1], 150, 150) && collision(p_smallest[1][0], p_smallest[1][1], 50, 50, p_smallship[0][0], p_smallship[0][1], 100, 100) && collision(p_smallest[1][0], p_smallest[1][1], 50, 50, p_smallship[1][0], p_smallship[1][1], 100, 100) && collision(p_smallest[1][0], p_smallest[1][1], 50, 50, p_smallship[2][0], p_smallship[2][1], 100, 100) && collision(p_smallest[1][0], p_smallest[1][1], 50, 50, p_smallest[0][0], p_smallest[0][1], 50, 50)))
		{
			p_smallest[1][0] = 50 * ((rand() % 400 + 100) / 50);
			p_smallest[1][1] = 50 * ((rand() % 500 + 100) / 50);
		}
		p_smallest[2][0] = 50 * ((rand() % 400 + 100) / 50);
		p_smallest[2][1] = 50 * ((rand() % 500 + 100) / 50);
		while ((collision(p_smallest[2][0], p_smallest[2][1], 50, 50, p_bigship_[0], p_bigship_[1], 200, 200) && collision(p_smallest[2][0], p_smallest[2][1], 50, 50, p_medship[0][0], p_medship[0][1], 150, 150) && collision(p_smallest[2][0], p_smallest[2][1], 50, 50, p_medship[1][0], p_medship[1][1], 150, 150) && collision(p_smallest[2][0], p_smallest[2][1], 50, 50, p_smallship[0][0], p_smallship[0][1], 100, 100) && collision(p_smallest[2][0], p_smallest[2][1], 50, 50, p_smallship[1][0], p_smallship[1][1], 100, 100) && collision(p_smallest[2][0], p_smallest[2][1], 50, 50, p_smallship[2][0], p_smallship[2][1], 100, 100) && collision(p_smallest[2][0], p_smallest[2][1], 50, 50, p_smallest[0][0], p_smallest[0][1], 50, 50) && collision(p_smallest[2][0], p_smallest[2][1], 50, 50, p_smallest[1][0], p_smallest[1][1], 50, 50)))
		{
			p_smallest[2][0] = 50 * ((rand() % 400 + 100) / 50);
			p_smallest[2][1] = 50 * ((rand() % 500 + 100) / 50);
		}
		p_smallest[3][0] = 50 * ((rand() % 400 + 100) / 50);
		p_smallest[3][1] = 50 * ((rand() % 500 + 100) / 50);
		while ((collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_bigship_[0], p_bigship_[1], 200, 200) && collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_medship[0][0], p_medship[0][1], 150, 150) && collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_medship[1][0], p_medship[1][1], 150, 150) && collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_smallship[0][0], p_smallship[0][1], 100, 100) && collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_smallship[1][0], p_smallship[1][1], 100, 100) && collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_smallship[2][0], p_smallship[2][1], 100, 100) && collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_smallest[0][0], p_smallest[0][1], 50, 50) && collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_smallest[1][0], p_smallest[1][1], 50, 50) && collision(p_smallest[3][0], p_smallest[3][1], 50, 50, p_smallest[2][0], p_smallest[2][1], 50, 50)))
		{
			p_smallest[3][0] = 50 * ((rand() % 400 + 100) / 50);
			p_smallest[3][1] = 50 * ((rand() % 500 + 100) / 50);
		}
		
		

	
}
void randomize2()
{

	b_bigship_[0] = 50 * ((rand() % 400 + 100) / 50);
	b_bigship_[1] = 50 * ((rand() % 500 + 200) / 50);

	b_medship[0][0] = 50 * ((rand() % 400 + 100) / 50);
	b_medship[0][1] = 50 * ((rand() % 500 + 200) / 50);
	while (collision(b_medship[0][0], b_medship[0][1], 150, 150, b_bigship_[0], b_bigship_[1], 200, 200))
	{
		b_medship[0][0] = 50 * ((rand() % 400 + 100) / 50);
		p_medship[0][1] = 50 * ((rand() % 500 + 200) / 50);
	}
	b_medship[1][0] = 50 * ((rand() % 400 + 100) / 50);
	b_medship[1][1] = 50 * ((rand() % 500 + 200) / 50);
	while ((collision(b_medship[1][0], b_medship[1][1], 150, 150, b_bigship_[0], b_bigship_[1], 200, 200) && collision(b_medship[1][0], b_medship[1][1], 150, 150, b_medship[0][0], b_medship[0][1], 150, 150)));
	{
		b_medship[1][0] = 50 * ((rand() % 400 + 100) / 50);
		b_medship[1][1] = 50 * ((rand() % 500 + 200) / 50);
	}
	b_smallship[0][0] = 50 * ((rand() % 400 + 100) / 50);
	b_smallship[0][1] = 50 * ((rand() % 500 + 200) / 50);
	while ((collision(b_smallship[0][0], b_smallship[0][1], 100, 100, b_bigship_[0], b_bigship_[1], 200, 200) && collision(b_smallship[0][0], b_smallship[0][1], 100, 100, b_medship[0][0], b_medship[0][1], 150, 150) && collision(b_smallship[0][0], b_smallship[0][1], 100, 100, b_medship[1][0], b_medship[1][1], 150, 150)))
	{
		b_smallship[0][0] = 50 * ((rand() % 400 + 100) / 50);
		b_smallship[0][1] = 50 * ((rand() % 500 + 200) / 50);
	}
	b_smallship[1][0] = 50 * ((rand() % 400 + 100) / 50);
	b_smallship[1][1] = 50 * ((rand() % 500 + 200) / 50);
	while ((collision(b_smallship[1][0], b_smallship[1][1], 100, 100, b_bigship_[0], b_bigship_[1], 200, 200) && collision(b_smallship[1][0], b_smallship[1][1], 100, 100, b_medship[0][0], b_medship[0][1], 150, 150) && collision(b_smallship[1][0], b_smallship[1][1], 100, 100, b_medship[1][0], b_medship[1][1], 150, 150) && collision(b_smallship[1][0], b_smallship[1][1], 100, 100, b_smallship[0][0], b_smallship[0][1], 100, 100)))
	{
		b_smallship[1][0] = 50 * ((rand() % 400 + 100) / 50);
		b_smallship[1][1] = 50 * ((rand() % 500 + 200) / 50);
	}
	b_smallship[2][0] = 50 * ((rand() % 400 + 100) / 50);
	b_smallship[2][1] = 50 * ((rand() % 500 + 200) / 50);
	while ((collision(b_smallship[2][0], b_smallship[2][1], 100, 100, b_bigship_[0], b_bigship_[1], 200, 200) && collision(b_smallship[2][0], b_smallship[2][1], 100, 100, b_medship[0][0], b_medship[0][1], 150, 150) && collision(b_smallship[2][0], b_smallship[2][1], 100, 100, b_medship[1][0], b_medship[1][1], 150, 150) && collision(b_smallship[2][0], b_smallship[2][1], 100, 100, b_smallship[0][0], b_smallship[0][1], 100, 100) && collision(b_smallship[2][0], b_smallship[2][1], 100, 100, b_smallship[1][0], b_smallship[1][1], 100, 100)))
	{
		b_smallship[2][0] = 50 * ((rand() % 400 + 100) / 50);
		b_smallship[2][1] = 50 * ((rand() % 500 + 200) / 50);
	}
	b_smallest[0][0] = 50 * ((rand() % 400 + 100) / 50);
	b_smallest[0][1] = 50 * ((rand() % 500 + 200) / 50);
	while ((collision(b_smallest[0][0], b_smallest[0][1], 50, 50, b_bigship_[0], b_bigship_[1], 200, 200) && collision(b_smallest[0][0], b_smallest[0][1], 50, 50, b_medship[0][0], b_medship[0][1], 150, 150) && collision(b_smallest[0][0], b_smallest[0][1], 50, 50, b_medship[1][0], b_medship[1][1], 150, 150) && collision(b_smallest[0][0], b_smallest[0][1], 50, 50, b_smallship[0][0], b_smallship[0][1], 100, 100) && collision(b_smallest[0][0], b_smallest[0][1], 50, 50, b_smallship[1][0], b_smallship[1][1], 100, 100) && collision(b_smallest[0][0], b_smallest[0][1], 50, 50, b_smallship[2][0], b_smallship[2][1], 100, 100)))
	{
		b_smallest[0][0] = 50 * ((rand() % 400 + 100) / 50);
		b_smallest[0][1] = 50 * ((rand() % 500 + 200) / 50);
	}
	b_smallest[1][0] = 50 * ((rand() % 400 + 100) / 50);
	b_smallest[1][1] = 50 * ((rand() % 500 + 200) / 50);
	while ((collision(b_smallest[1][0], b_smallest[1][1], 50, 50, b_bigship_[0], b_bigship_[1], 200, 200) && collision(b_smallest[1][0], b_smallest[1][1], 50, 50, b_medship[0][0], b_medship[0][1], 150, 150) && collision(b_smallest[1][0], b_smallest[1][1], 50, 50, b_medship[1][0], b_medship[1][1], 150, 150) && collision(b_smallest[1][0], b_smallest[1][1], 50, 50, b_smallship[0][0], b_smallship[0][1], 100, 100) && collision(b_smallest[1][0], b_smallest[1][1], 50, 50, b_smallship[1][0], b_smallship[1][1], 100, 100) && collision(b_smallest[1][0], b_smallest[1][1], 50, 50, b_smallship[2][0], b_smallship[2][1], 100, 100) && collision(b_smallest[1][0], b_smallest[1][1], 50, 50, b_smallest[0][0], b_smallest[0][1], 50, 50)))
	{
		b_smallest[1][0] = 50 * ((rand() % 400 + 100) / 50);
		b_smallest[1][1] = 50 * ((rand() % 500 + 200) / 50);
	}
	b_smallest[2][0] = 50 * ((rand() % 400 + 100) / 50);
	b_smallest[2][1] = 50 * ((rand() % 500 + 200) / 50);
	while ((collision(b_smallest[2][0], b_smallest[2][1], 50, 50, b_bigship_[0], b_bigship_[1], 200, 200) && collision(b_smallest[2][0], b_smallest[2][1], 50, 50, b_medship[0][0], b_medship[0][1], 150, 150) && collision(b_smallest[2][0], b_smallest[2][1], 50, 50, b_medship[1][0], b_medship[1][1], 150, 150) && collision(b_smallest[2][0], b_smallest[2][1], 50, 50, b_smallship[0][0], b_smallship[0][1], 100, 100) && collision(b_smallest[2][0], b_smallest[2][1], 50, 50, b_smallship[1][0], b_smallship[1][1], 100, 100) && collision(b_smallest[2][0], b_smallest[2][1], 50, 50, b_smallship[2][0], b_smallship[2][1], 100, 100) && collision(b_smallest[2][0], b_smallest[2][1], 50, 50, b_smallest[0][0], b_smallest[0][1], 50, 50) && collision(b_smallest[2][0], b_smallest[2][1], 50, 50, b_smallest[1][0], b_smallest[1][1], 50, 50)))
	{
		b_smallest[2][0] = 50 * ((rand() % 400 + 100) / 50);
		b_smallest[2][1] = 50 * ((rand() % 500 + 200) / 50);
	}
	b_smallest[3][0] = 50 * ((rand() % 400 + 100) / 50);
	b_smallest[3][1] = 50 * ((rand() % 500 + 200) / 50);
	while ((collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_bigship_[0], b_bigship_[1], 200, 200) && collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_medship[0][0], b_medship[0][1], 150, 150) && collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_medship[1][0], b_medship[1][1], 150, 150) && collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_smallship[0][0], b_smallship[0][1], 100, 100) && collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_smallship[1][0], b_smallship[1][1], 100, 100) && collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_smallship[2][0], b_smallship[2][1], 100, 100) && collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_smallest[0][0], b_smallest[0][1], 50, 50) && collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_smallest[1][0], b_smallest[1][1], 50, 50) && collision(b_smallest[3][0], b_smallest[3][1], 50, 50, b_smallest[2][0], b_smallest[2][1], 50, 50)))
	{
		b_smallest[3][0] = 50 * ((rand() % 400 + 100) / 50);
		b_smallest[3][1] = 50 * ((rand() % 500 + 200) / 50);
	}




}
void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
	

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		if (leaderboard)
		{
			menu = true;
			leaderboards = false;
		}
		else
		{
			writefile();

			exit(1); // exit the program when escape key is pressed.
		}
	}
	if (key == 'l' || key == 'L')
	{
		leaderboards = true;
		menu = false;
	}
	if (key == 'l' || key == 'L')
	{
		if (menu)
		{
			leaderboards = true;
			menu = false;
		}

	}
	if(key=='e'|| key=='E')
	{
		if (menu)
			exit(1);
	}
	if (key == 'a' || key == 'A')
	{
		if (grid)
		{
			randomize();
			grid = false;
			play = true;
			randomize2();
		}
	}
	if (key == 'p' || key == 'P') //Key for placing the bomb
	{
		if (menu)
		{
			menu = false;
			grid = true;
		}
		//do something if b is pressed
		cout << "b pressed" << endl;

	}
	glutPostRedisplay();
}



/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
bool pressed = false;
/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
bool check(int x,int y)
{
	if (x == p_bigship_[0] && y == p_bigship_[1])
		return false;
	if (x == p_medship[0][0] && y == p_medship[0][1])
		return false;
	if (x == p_medship[1][0] && y == p_medship[1][1])
		return false;
	if (x == p_smallship[0][0] && y == p_smallship[0][1])
		return false;
	if (x == p_smallship[1][0] && y == p_smallship[1][1])
		return false;
	if (x == p_smallship[2][0] && y == p_smallship[2][1])
		return false;
	if (x == p_smallest[0][0] && y == p_smallest[0][1])
		return false;
	if (x == p_smallest[1][0] && y == p_smallest[1][1])
		return false;
	if (x == p_smallest[2][0] && y == p_smallest[2][1])
		return false;
	if (x == p_smallest[3][0] && y == p_smallest[3][1])
		return false;
	return true;
		
	
	
}

void MouseClicked(int button, int state, int x, int y) {

	
	if (button == GLUT_LEFT_BUTTON && state==GLUT_DOWN) // dealing only with left button
	{
		int a = x;
		int b = y;
		if (play && inrect(x,abs(y-840),100,200,500,500)==1)
		{
			turn = true;
			turns--;
			int x = 50 * ((a / 50));
			int y = 50 * (((b -840)/ 50));
			cout << "hit" << endl;
			cout << x << "   " << y << endl;
			if (x == b_bigship_[0] && abs(y - 0) == b_bigship_[1])
			{
				hits = 0;
				b_bigship_[0] = -99;
				b_bigship_[1] = -99;
				score += 10;
			}
			else if (x == b_medship[0][0] && abs(y - 0) == b_medship[0][1])
			{
				hits = 0;
				score += 60;
				b_medship[0][0] = b_medship[0][1] = -99;
			}
			else if (x == b_medship[1][0] && abs(y - 0) == b_medship[1][1])
			{
				hits = 0;
				score +=60;
				b_medship[1][0] = b_medship[1][1] = -99;
			}
				
			else if (x == b_smallship[0][0] && abs(y - 0) == b_smallship[0][1])
			{
				hits = 0;
				score += 60;
				b_smallship[0][0] = b_smallship[0][1] = -99;
			}
			else if (x == b_smallship[1][0] && abs(y - 0) == b_smallship[1][1])
			{

				hits = 0;
				score += 60;

				b_smallship[1][0] = b_smallship[1][1] = -99;
			}
			else if (x == b_smallship[2][0] && abs(y - 0) == b_smallship[2][1])
			{
				hits = 0;
				score += 60;
				b_smallship[2][0] = b_smallship[2][1] = -99;
			}
			else if (x == b_smallest[0][0] && abs(y - 0) == b_smallest[0][1])
			{
				hits = 0;
				score += 60;
				b_smallest[0][0] = b_smallest[0][1] = -99;
			}
			else if (x == b_smallest[1][0] && abs(y - 0) == b_smallest[1][1])
			{
				hits = 0;
				score += 60;
				b_smallest[1][0] = b_smallest[1][1] = -99;
			}
			else if (x == b_smallest[2][0] && abs(y - 0) == b_smallest[2][1])
			{
				hits = 0;
				score += 60;
				b_smallest[2][0] = b_smallest[2][1] = -99;
			}
			else if (x == b_smallest[3][0] && abs(y - 0) == b_smallest[3][1])
			{
				hits = 0;
				score += 60;
				b_smallest[3][0] = b_smallest[3][1] = -99;
			}
			else
			{
				hits++;
				if (hits > 2)
					score -= 20;
			}
			
		}
		if (p_bigship_[2]!=0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500)==1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y-840) / 50);
				if (inrect(xco + 50, yco , 100, 200, 500, 500)==1 && inrect(xco + 100, yco , 100, 200, 500, 500)==1 && inrect(xco+150,yco,100,200,500,500)==1)
				{
					if(check(xco,yco))
					{
						p_bigship_[0] = xco;
						p_bigship_[1] = yco;
						p_bigship_[2] = 0;
					}
				}
			}
			else
				p_bigship_[2] = 0;
		}
		if (p_medship[0][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco + 50, yco, 100, 200, 500, 500) && inrect(xco + 100, yco, 100, 200, 500, 500) == 1)
				{
					if(check(xco,yco))
					{
						p_medship[0][0] = xco;
						p_medship[0][1] = yco;
						p_medship[0][2] = 0;
					}
				}
			}
			else
				p_medship[0][2] = 0;
		}
		if (p_medship[1][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco + 50, yco, 100, 200, 500, 500) && inrect(xco + 100, yco, 100, 200, 500, 500) == 1)
				{
					if(check(xco,yco))
					{
						p_medship[1][0] = xco;
						p_medship[1][1] = yco;
						p_medship[1][2] = 0;
					}
				}
			}
			else
				p_medship[1][2] = 0;
		}
		if (p_smallship[0][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco + 50, yco, 100, 200, 500, 500) == 1)
				{
					if (check(xco, yco))
					{
						p_smallship[0][0] = xco;
						p_smallship[0][1] = yco;
						p_smallship[0][2] = 0;
					}
				}
			}
			else
				p_smallship[0][2] = 0;
		}
		if (p_smallship[1][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco + 50, yco, 100, 200, 500, 500) == 1)
				{
					if (check(xco, yco))
					{
						p_smallship[1][0] = xco;
						p_smallship[1][1] = yco;
						p_smallship[1][2] = 0;
					}
				}
			}
			else
				p_smallship[1][2] = 0;
		}
		if (p_smallship[2][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco + 50, yco, 100, 200, 500, 500) == 1)
				{
					if (check(xco, yco))
					{
						p_smallship[2][0] = xco;
						p_smallship[2][1] = yco;
						p_smallship[2][2] = 0;
					}
				}
			}
			else
				p_smallship[2][2] = 0;
		}
		if (p_smallest[0][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco , yco, 100, 200, 500, 500) == 1)
				{
					if (check(xco, yco))
					{
						p_smallest[0][0] = xco;
						p_smallest[0][1] = yco;
						p_smallest[0][2] = 0;
					}
				}
			}
			else
				p_smallest[0][2] = 0;
		}
		if (p_smallest[1][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco, yco, 100, 200, 500, 500) == 1)
				{
					if (check(xco, yco))
					{
						p_smallest[1][0] = xco;
						p_smallest[1][1] = yco;
						p_smallest[1][2] = 0;
					}
				}
			}
			else
				p_smallest[1][2] = 0;
		}
		if (p_smallest[2][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco + 50, yco, 100, 200, 500, 500) == 1)
				{
					if (check(xco, yco))
					{
						p_smallest[2][0] = xco;
						p_smallest[2][1] = yco;
						p_smallest[2][2] = 0;
					}
				}
			}
			else
				p_smallest[2][2] = 0;
		}
		if (p_smallest[3][2] != 0)
		{
			last_click_x = x;
			last_click_y = abs(y - 840);
			cout << "LAST" << last_click_x << "  " << last_click_y << endl;
			if (inrect(last_click_x, last_click_y, 100, 200, 500, 500) == 1)
			{
				int xco = 50 * (x / 50);
				int yco = 50 * (abs(y - 840) / 50);
				if (inrect(xco + 50, yco, 100, 200, 500, 500) == 1)
				{
					if (check(xco, yco))
					{
						p_smallest[3][0] = xco;
						p_smallest[3][1] = yco;
						p_smallest[3][2] = 0;
					}
				}
			}
			else
				p_smallest[3][2] = 0;
		}
		
		else if (grid);
		{
			if (p_bigship_[0] <= 0)
			{
				if(inrect(x, abs(y - 840), 650, 200, 200, 20)==1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_bigship_[2] = 1;
				}
			
			}
			if (p_medship[0][0] <= 0)
			{
				if (inrect(x, abs(y - 840), 650, 250, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_medship[0][2] = 1;
				}
					
			}
			if (p_medship[1][0] <= 0)
			{
				if (inrect(x, abs(y - 840), 650, 300, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_medship[1][2] = 1;
				}
			}
			if (p_smallship[0][0] <= 0)
			{
				if (inrect(x, abs(y - 840), 650, 350, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_smallship[0][2] = 1;
				}
			}
			if (p_smallship[1][0] <= 0)
			{
				if (inrect(x, abs(y - 840), 650, 400, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_smallship[1][2] = 1;
				}
			}
			if (p_smallship[2][0] <= 0)
			{
				if (inrect(x, abs(y - 840), 650, 450, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_smallship[2][2] = 1;
				}
			}
			if (p_smallest[0][0] <= 0)
			{
				if (inrect(x, abs(y - 840), 650, 500, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_smallest[0][2] = 1;
				}
			}
			if (p_smallest[1][0] <= 0)
			{
				if (inrect(x, abs(y - 840), 650, 550, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_smallest[1][2] = 1;
				}
			}
			if (p_smallest[2][0] <= 0)
			{
				if (inrect(x, abs(y - 840), 650, 600, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_smallest[2][2] = 1;
				}
			}
			if (p_smallest[3][0] <=0 )
			{
				if (inrect(x, abs(y - 840), 650, 650, 200, 20) == 1)
				{
					for (int i = 2; i < 3; i++)
					{
						p_bigship_[i] = 0;
						p_medship[0][i] = 0;
						p_medship[1][i] = 0;
						p_smallship[0][i] = 0;
						p_smallship[1][i] = 0;
						p_smallship[2][i] = 0;
						p_smallest[0][i] = 0;
						p_smallest[1][i] = 0;
						p_smallest[2][i] = 0;
						p_smallest[3][i] = 0;

					}
					p_smallest[3][2] = 1;
				}
			}
			
		
				
			
		}
					

	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
			cout<<"Right Button Pressed"<<endl;

	}
	last_click_x = x;
	last_click_y = abs(y-840);
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {
	srand(time(0));
	randomize2();
	cout << "Enter name" << endl;
	cin >> name;
	readfile();
	int width = 1366, height = 840; // i have set my window size to be 800 x 600
	init();
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("BAttleship"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	
	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}


