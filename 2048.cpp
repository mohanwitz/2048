/ 2048 Game using cpp

#include <iostream>
#include <stdlib.h>
#include <conio.h>
	using namespace std;
int random_index(int);
class Game;
class Game_AI
{
	int response;
	int apocalypse;
	char control;

  public:
	int max;
	int win;
	int plus;
	int grid[4][4];
	int bgrid[4][4];
	Game_AI()
	{
		win = 2048;
		max = 0;
		response = 0;
		apocalypse = 1;
	}
	void logic_flow(Game *);
	void game_end_check(Game *);
	void key_press();
	void start_grid();
	void update_grid();
	void fill_space();
	void spawn();
	void find_greatest_tile();
	void backup_grid();
	void undo();
	int full();
	int block_moves();
};
class Game : public Game_AI
{
	char option;
	string name;

  public:
	void display_grid();
	void display_help_screen();
	void display_win_screen();
	void display_loser_screen();
	char display_try_again_screen(int);
};
void Game_AI::key_press()
{
	char n = 'f';
	while (n != 'a' && n != 's' && n != 'd' && n != 'w' && n != 'r' && n != 'q' && n != 'u')
	{
		n = _getch();
	}
	control = n;
	;
}
void Game_AI::logic_flow(Game *execute)
{

	switch (control)
	{
	case 'w':
	case 'a':
	case 's':
	case 'd':
		execute->backup_grid();
		execute->fill_space();
		execute->update_grid();
		execute->fill_space();
		execute->find_greatest_tile();
		execute->display_grid();
		if (execute->full() && apocalypse)
		{
			response = -1;
			break;
		}
		else if (execute->block_moves())
		{
			execute->spawn();
			break;
		}
		else
		{
			response = 0;
			break;
		}

	case 'u':
		execute->undo();
		break;

	case 'r':
		execute->start_grid();
		break;

	case 'q':
		response = -1;
		break;
	}
}

void Game_AI::game_end_check(Game *screen)
{
	if (max == win)
	{
		screen->display_win_screen();

		if (screen->display_try_again_screen(0) == 'n')
			response = -1;
		else
			win *= 2;
	}

	else if (response == -1)
	{
		screen->display_loser_screen();

		if (screen->display_try_again_screen(1) == 'y')
		{
			screen->start_grid();
			response = 0;
		}
	}

	if (response == -1)
	{
		cout << "\n\n\t\t          Thank you for playing!!";
		exit(0);
	}
}

void Game_AI::start_grid()
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			grid[i][j] = 0;

	i = random_index(4);
	j = random_index(4);

	grid[i][j] = 2;

	i = random_index(4);
	j = random_index(4);

	grid[i][j] = 2;
}

void Game::display_grid()
{
	system("cls");

	cout << "\n        \t\t\t     2048 GAME\n\n\n ";
	for (int i = 0; i < 4; i++)
	{
		cout << "\t\t     |";

		for (int j = 0; j < 4; j++)
		{
			if (grid[i][j])
				printf("%4d    |", grid[i][j]);
			else
				printf("%4c    |", ' ');
		}

		cout << endl
			 << endl;
	}
	cout << "\n\n  \t\t      u - UNDO\tr - RESTART\tq - QUIT\n\n  \t\tw - UPWARD s - DOWNWARD A - LEFTWARD D - RIGHTWARD:";
}

int random_index(int x)
{
	int index;
	index = rand() % x + 0;

	return index;
}

void Game_AI::backup_grid()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			bgrid[i][j] = grid[i][j];
}

void Game_AI::fill_space()
{

	switch (control)
	{
	case 'w':
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (!grid[j][i])
				{
					for (int k = j + 1; k < 4; k++)
						if (grid[k][i])
						{
							grid[j][i] = grid[k][i];
							grid[k][i] = 0;
							break;
						}
				}
			}
		break;

	case 's':
		for (int i = 0; i < 4; i++)
			for (int j = 3; j >= 0; j--)
			{
				if (!grid[j][i])
				{
					for (int k = j - 1; k >= 0; k--)
						if (grid[k][i])
						{
							grid[j][i] = grid[k][i];
							grid[k][i] = 0;
							break;
						}
				}
			}
		break;
	case 'a':
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (!grid[i][j])
				{
					for (int k = j + 1; k < 4; k++)
						if (grid[i][k])
						{
							grid[i][j] = grid[i][k];
							grid[i][k] = 0;
							break;
						}
				}
			}
		break;

	case 'd':
		for (int i = 0; i < 4; i++)
			for (int j = 3; j >= 0; j--)
			{
				if (!grid[i][j])
				{
					for (int k = j - 1; k >= 0; k--)
						if (grid[i][k])
						{
							grid[i][j] = grid[i][k];
							grid[i][k] = 0;
							break;
						}
				}
			}
		break;
	}
}

void Game_AI::update_grid()
{
	plus = 0;
	apocalypse = 1;

	switch (control)
	{
	case 'w':
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
			{
				if (grid[j][i] && grid[j][i] == grid[j + 1][i])
				{
					apocalypse = 0;
					grid[j][i] += grid[j + 1][i];
					grid[j + 1][i] = 0;
				}
			}
		break;

	case 's':
		for (int i = 0; i < 4; i++)
			for (int j = 3; j > 0; j--)
			{
				if (grid[j][i] && grid[j][i] == grid[j - 1][i])
				{
					apocalypse = 0;
					grid[j][i] += grid[j - 1][i];
					grid[j - 1][i] = 0;
				}
			}
		break;

	case 'a':
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++)
			{
				if (grid[i][j] && grid[i][j] == grid[i][j + 1])
				{
					apocalypse = 0;
					grid[i][j] += grid[i][j + 1];
					grid[i][j + 1] = 0;
				}
			}
		break;

	case 'd':
		for (int i = 0; i < 4; i++)
			for (int j = 3; j > 0; j--)
			{
				if (grid[i][j] && grid[i][j] == grid[i][j - 1])
				{
					apocalypse = 0;
					grid[i][j] += grid[i][j - 1];
					grid[i][j - 1] = 0;
				}
			}
		break;
	}
}
void Game_AI::spawn()
{
	int i, j, k;

	do
	{
		i = random_index(4);
		j = random_index(4);
		k = random_index(10);

	} while (grid[i][j]);

	if (k < 2)
		grid[i][j] = 4;

	else
		grid[i][j] = 2;
}

void Game_AI::find_greatest_tile()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (grid[i][j] > max)
				max = grid[i][j];
}

int Game_AI::full()
{
	int k = 1;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			if (!grid[i][j])
				k = 0;
		}
	return k;
}
void Game::display_win_screen()
{
	system("cls");
	cout << endl
		 << endl;
	cout << "\n\t\t\t YOU WON THE GAME!!";
}
void Game::display_loser_screen()
{
	system("cls");
	cout << "\n\n\n\t\t\t  G A M E  O V E R!!   ";
}

char Game::display_try_again_screen(int lose)
{
	if (lose)
		cout << "\n\n\n\t     Would you like to try again (y/n) ?";
	else
		cout << "\n\n\n\t     Would you like to continue playing (y/n) ?";
	cin >> option;
	return option;
}

void Game_AI::undo()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			grid[i][j] = bgrid[i][j];
}

int Game_AI::block_moves()
{
	int k = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (bgrid[i][j] != grid[i][j])
			{
				k = 1;
				break;
			}
	return k;
}
int main()
{
	Game exec;
	exec.start_grid();
	while (1)
	{
		exec.display_grid();
		exec.key_press();
		exec.logic_flow(&exec);
		exec.game_end_check(&exec);
	}

	return 0;
}
