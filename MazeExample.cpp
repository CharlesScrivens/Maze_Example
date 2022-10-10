#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@       @                     @         @     @             @         @
@ @@@ @ @ @@@@@@@ @@@@@ @@@@@ @ @@@@@@@@@ @ @@@ @ @@@ @@@@@@@ @@@@@ @@@
@   @ @ @ @     @ @   @     @   @         @     @   @ @       @   @   @
@ @@@ @ @@@ @@@ @ @ @ @@@@@ @@@@@ @@@@@@@@@@@@@@@ @ @ @ @@@@@@@@@ @@@ @
@ @   @     @   @ @ @       @             @     @ @ @ @   @     @   @ @
@@@ @@@@@@@@@ @@@@@ @@@@@@@@@ @@@@@@@@@@@@@ @@@ @ @ @@@@@ @@@ @ @ @ @ @
@ @       @ @ @     @       @   @   @       @ @ @ @           @   @ @ @
@ @@@@@@@ @ @ @@@ @@@ @@@@@ @@@ @ @ @ @@@@@@@ @ @@@@@@@ @@@@@@@@@@@@@ @
@       @ @ @   @         @     @ @   @   @     @     @ @     @   @   @
@@@@@@@ @ @ @@@ @@@@@@@@@@@@@@@@@ @@@@@ @@@ @@@@@ @@@ @@@ @@@ @ @ @ @ @
@         @                       @               @       @     @   @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/


void SolveMaze(int row, int col, char maze[][100], int rowSz, int colSz, bool foundEnd) {

    if (foundEnd)   // base case for end found
    {
        return;
    }

    if (row < 0 || col < 0 || row >= rowSz || col >= colSz) // base case for being in bounds. CHECK FIRST
    {
        return;
    }

    if (maze[row][col] == '.')  // base case for previous spot
    {
        return;
    }

    if (maze[row][col] == 'F') // base case to show breadcrumb
    {
        foundEnd = true;
        return;
    }

    if (maze[row][col] ==  '@') // another base case for walls
    {
        return;
    }

    maze[row][col] = '.';   // breadcrumb

    SolveMaze(row - 1, col, maze, rowSz, colSz, foundEnd);  // go north
    SolveMaze(row + 1, col, maze, rowSz, colSz, foundEnd);  // go south
    SolveMaze(row, col + 1, maze, rowSz, colSz, foundEnd);  // go east
    SolveMaze(row, col - 1, maze, rowSz, colSz, foundEnd);  // go west

    if(!foundEnd)
        maze[row][col] = ' ';

}

int main()
{
    ifstream mazeFile("maze.txt");
    char maze[100][100]; // make larger than required

    // Initialize the maze
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++) {
            maze[i][j] = ' ';
        }

    int row = 0;
    int startRow, startCol;

    // Read the file line by line an initialize the maze
    string line;
    while (getline(mazeFile, line)) {
        cout << line << endl;
        for (int i = 0; i < (int) line.length(); i++) {
            maze[row][i] = line[i];
            if (maze[row][i] == 'S') {
                startRow = row;
                startCol = i;
                maze[row][i] = ' ';
            }
        }
        row++;
    }

    cout << "Start Position: (" << startRow << "," << startCol << ")" << endl;

    // figure out the number of rows and columns
    int rowSz = row;
    int colSz = line.length();

    bool foundEnd = false;

    string finaldir = "";
    string currDir = "";
    SolveMaze(startRow, startCol, maze, rowSz, colSz, &foundEnd);

    cout << "Directions: " << finaldir << endl;

    // Print out the maze with the path shown
    for (int i = 0; i < rowSz; i++) {
        for (int j = 0; j < colSz; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }

    return 0;
}
