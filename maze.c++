#include <iostream>
#include <queue>
using namespace std;

int rows, cols;
int maze[100][100];
int visited[100][100];
int parent[100][100][2];

// Directions: Right, Left, Down, Up
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void printPath(int x, int y) {
    if (x == -1) return;
    printPath(parent[x][y][0], parent[x][y][1]);
    cout << "(" << x << "," << y << ") ";
}

void displayMazeWithPath(int startX, int startY, int endX, int endY) {
    char display[100][100];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1)
                display[i][j] = '.';
            else
                display[i][j] = '#';
        }
    }
    
    int x = endX, y = endY;
    while (x != -1) {
        display[x][y] = '*';
        int tempX = parent[x][y][0];
        int tempY = parent[x][y][1];
        x = tempX;
        y = tempY;
    }
    
    display[startX][startY] = 'S';
    display[endX][endY] = 'E';
    
    cout << "\n===== Maze with Path =====\n\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << display[i][j] << " ";
        }
        cout << endl;
    }
    
    cout << "\nLegend:\n";
    cout << "S = Start | E = End | * = Path | # = Wall | . = Road\n";
}

bool solveMaze(int startX, int startY, int endX, int endY) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    visited[startX][startY] = 1;
    parent[startX][startY][0] = -1;
    parent[startX][startY][1] = -1;
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        if (x == endX && y == endY) {
            cout << "\nshortest Path Found\n";
            cout << "Start Point: (" << startX << "," << startY << ")\n";
            cout << "End Point: (" << endX << "," << endY << ")\n";
            cout << "Path: ";
            printPath(x, y);
            cout << endl;
            displayMazeWithPath(startX, startY, endX, endY);
            return true;
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                if (maze[nx][ny] == 1 && !visited[nx][ny]) {
                    visited[nx][ny] = 1;
                    parent[nx][ny][0] = x;
                    parent[nx][ny][1] = y;
                    q.push({nx, ny});
                }
            }
        }
    }
    return false;
}

int main() {
    cout << "========================================\n";
    cout << "     Maze Solver using BFS Algorithm    \n";
    cout << "========================================\n\n";
    
    cout << "Enter number of rows: ";
    cin >> rows;
    cout << "Enter number of columns: ";
    cin >> cols;
    
    cout << "\nEnter the maze (1 = path, 0 = wall):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> maze[i][j];
        }
    }
    
    int startX = -1, startY = -1;
    int endX = -1, endY = -1;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (maze[i][j] == 1) {
                startX = i;
                startY = j;
                break;
            }
        }
        if (startX != -1) break;
    }
    
    for (int i = rows - 1; i >= 0; i--) {
        for (int j = cols - 1; j >= 0; j--) {
            if (maze[i][j] == 1) {
                endX = i;
                endY = j;
                break;
            }
        }
        if (endX != -1) break;
    }
    
    if (startX == -1 || endX == -1) {
        cout << "\nError: No path found in the maze!\n";
        return 0;
    }
    
    if (solveMaze(startX, startY, endX, endY)) {
        cout << "\n successfully reached the end!\n";
    } else {
        cout << "\n No path exists from start to end!\n";
    }
    
    cout << "\n========================================\n";
    cout << "          Complexity Analysis           \n";
    cout << "========================================\n";
    cout << "Time Complexity: O(rows * cols)\n";
    cout << "Space Complexity: O(rows * cols)\n";
    
    return 0;
}