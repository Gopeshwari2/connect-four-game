#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const int ROWS = 6;
const int COLS = 7;
vector<vector<char>> board(ROWS, vector<char>(COLS, ' '));  // Initialize with empty spaces

void initializeBoard() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            board[i][j] = ' ';  // Empty space
        }
    }
}

void printBoard() {
    for (int i = 0; i < COLS; ++i) {
        cout << "  " << i + 1 << ' ';
    }
    cout << endl;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << "| " << board[i][j] << ' ';
        }
        cout << '|' << endl;
        for (int j = 0; j < COLS; ++j) {
            cout << "----";
        }
        cout << '-' << endl;
    }
}
int getColumnInput() {
    int col;
    while (true) {
        cout << "Enter column (1-7): ";
        cin >> col;
        if (cin.fail() || col < 1 || col > 7) {
            cout << "Invalid input. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return col - 1;
        }
    }
}

int insertDisc(int col, char disc) {
    for (int row = ROWS - 1; row >= 0; --row) {
        if (board[row][col] == ' ') {  // Check for empty space
            board[row][col] = disc;
            return row;
        }
    }
    return -1;
}

bool checkWin(int row, int col, char disc) {
    int directions[4][2] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (auto &dir : directions) {
        int count = 1;
        for (int i = -1; i <= 1; i += 2) {
            int r = row + i * dir[0];
            int c = col + i * dir[1];
            while (r >= 0 && r < ROWS && c >= 0 && c < COLS && board[r][c] == disc) {
                count++;
                r += i * dir[0];
                c += i * dir[1];
            }
  }
        if (count >= 4) {
            return true;
        }
    }
    return false;
}

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void playGame(string player1, string player2, int &player1Wins, int &player2Wins) {
    initializeBoard();
    printBoard();
    int moveCount = 0;
    while (moveCount < ROWS * COLS) {
        string currentPlayer = (moveCount % 2 == 0) ? player1 : player2;
        char disc = (moveCount % 2 == 0) ? 'X' : 'O';
        cout << currentPlayer << " (" << disc << "): ";
        int col;
        while (true) {
            col = getColumnInput();
            if (board[0][col] == ' ') {  // Check for empty space
                break;
            } else {
                cout << "Column is full. Try a different column." << endl;
            }
        }
  int row = insertDisc(col, disc);
        clearScreen();
        printBoard();
        if (checkWin(row, col, disc)) {
            cout << currentPlayer << " (" << disc << ") is the winner! Congratulations!!" << endl;
            if (currentPlayer == player1) ++player1Wins;
            else ++player2Wins;
            return;
        }
        ++moveCount;
    }
    cout << "It's a draw! No winner." << endl;
}

bool askReplay() {
    char response;
    cout << "Do you want to play again? (y/n): ";
    cin >> response;
    return response == 'y' || response == 'Y';
}

int main() {
    string player1, player2;
    cout << "Enter name of Player 1: ";
    cin >> player1;
    cout << "Enter name of Player 2: ";
    cin >> player2;

    int player1Wins = 0, player2Wins = 0;
    do {
        playGame(player1, player2, player1Wins, player2Wins);
        cout << "Score - " << player1 << ": " << player1Wins << " " << player2 << ": " << player2Wins << endl;
    } while (askReplay());
    cout << "Thank you for playing Connect4!" << endl;
    return 0;
}
