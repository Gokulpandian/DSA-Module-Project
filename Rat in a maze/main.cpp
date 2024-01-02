#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<vector<char>> generateMaze(int n, int wallPercentage) {
    vector<vector<char>> maze(n, vector<char>(n, 'o'));

    int numWalls = (wallPercentage * n * n) / 100;
    for (int i = 0; i < numWalls; ++i) {
        int row = rand() % n;
        int col = rand() % n;
        maze[row][col] = '|';
    }

    maze[0][0] = 'S';
    maze[n - 1][n - 1] = 'E';

    return maze;
}

void printMaze(const vector<vector<char>>& maze) {
    for (const auto& row : maze) {
        for (char cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

bool findPath(vector<vector<char>>& maze, int row, int col) {
    if (row < 0 || row >= maze.size() || col < 0 || col >= maze[0].size() || maze[row][col] == '|' || maze[row][col] == 'X') {
        return false;
    }

    maze[row][col] = 'X'; 

    if (row == maze.size() - 1 && col == maze[0].size() - 1) {
        return true; 
    }

    if (findPath(maze, row + 1, col) || findPath(maze, row - 1, col) || findPath(maze, row, col + 1) || findPath(maze, row, col - 1)) {
        return true;
    }

    maze[row][col] = 'o'; 
    return false;
}

int main() {
    srand(static_cast<unsigned>(time(0))); 

    int n, wallPercentage;
    vector<vector<char>> maze;

    cout << "Enter the size of the maze (n): ";
    cin >> n;

    cout << "Enter the percentage of walls: ";
    cin >> wallPercentage;

    maze = generateMaze(n, wallPercentage);

    cout << "\nGenerated Maze:\n";
    printMaze(maze);

    while (true) {
        cout << "\n1. Print the path\n";
        cout << "2. Generate another puzzle\n";
        cout << "3. Exit the game\n";
        cout << "Enter your choice (1/2/3): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                if (maze.empty()) {
                    cout << "Please generate a puzzle first.\n";
                } else {
                    vector<vector<char>> tempMaze = maze;
                    if (findPath(tempMaze, 0, 0)) {
                        cout << "\nPath Found:\n";
                        printMaze(tempMaze);
                    } else {
                        cout << "\nNo path found.\n";
                    }
                }
                break;
            case 2:
                cout << "Enter the size of the maze (n): ";
                cin >> n;

                cout << "Enter the percentage of walls: ";
                cin >> wallPercentage;

                maze = generateMaze(n, wallPercentage);

                cout << "\nGenerated Maze:\n";
                printMaze(maze);
                break;
            case 3:
                cout << "Exiting the game.\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}


