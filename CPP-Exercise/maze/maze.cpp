#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include "maze.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

//add my own code
bool find_marker(char ch, char **maze, int height, int width, int& row, int& column)
{
	for (row = 0; row < height; row++)	
		for (column = 0; column < width; column++)
			if(maze[row][column] == ch)
				return true;

	row = column = -1;
	return false;
}

bool valid_solution(const char* path, char **maze, int height, int width)
{
	char paths[100];
	strcpy(paths, path);
	int start_row, start_column;
	//make sure there is a start position.
	
	char start = '>';
	if (!find_marker(start, maze, height, width, start_row, start_column))
	{
		cout << "There is no start position." << endl;
		return false;
	}
	//make sure there is an end position
	char end = 'X';
	int end_row, end_column;
	if (!find_marker(end, maze, height, width, end_row, end_column))
	{
		cout << "There is no end position." << endl;
		return false;
	}
	char temp;
	int i= 0;
	
	for (; paths[i+1]!= '\0'; i++)
	{
		temp = paths[i];
		if (!pathway(maze, temp, end, start_row, start_column))
			return false;
		if (start_row < 0 || start_row > height || start_column < 0 || start_column > width)
			return false;
	}
	
	temp = paths[i];
	if (!pathway(maze, temp, end, start_row, start_column))
		return false;
	if (start_row== end_row && start_column== end_column)
		return true;
	return false;

}

const char* find_path(char** maze, int height, int width, char start, char end)
{
	int start_row, start_column;
	if (!find_marker(start, maze, height, width, start_row, start_column))
		return "There is no start position.";
	
	char path[1000];
	path[0] = '\0';
	if (find_solution(maze, start_row, start_column, end, height, width, path))
		return path;
	else 
		return "no solution";
}

bool find_solution(char** maze, int& start_row, int& start_column, char end, int height, int width, char* path)
{
	char direction[5] = "ESNW";
	
	if(maze[start_row][start_column] == end)
	{
		maze[start_row][start_column] = '#';
		path[0] = '\0';
		return true;
	}
	

	int temp1, temp2;
	char temp3;
	
	for (int i = 0;i < 4;i++)
	{
		temp1 = start_row;
		temp2 = start_column;
		temp3 = maze[temp1][temp2];
		maze[temp1][temp2] = '#';//record the route
		
		if (pathway(maze, direction[i], end, start_row, start_column))
		{
			if (start_row >= 0 && start_row <= height && start_column >= 0 && start_column <= width)
			{
				if (find_solution(maze, start_row, start_column, end,height, width, &path[1]))
				{
					path[0] = direction[i];
					return true;
				}
			}
		}
		start_row = temp1;
		start_column = temp2;
		maze[start_row][start_column] = temp3;
	}
	return false;
}


bool pathway(char** maze, char path, char end, int& row, int& column)
{
	switch(path)
	{
		case 'E':
			column++; break;
		case 'W':
			column--; break;
		case 'S':
			row++; break;
		case 'N':
			row--; break;
		default:
			return false;
	}
	if (maze[row][column] == ' '||maze[row][column] == end)
		return true;
	else
		return false;
}
