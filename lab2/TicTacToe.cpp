#include <iostream>
#include <vector>

using namespace std;

class TicTacToe
{

    int board[3][3];

public:
    void clearBoard()
    {
        int boardlen = 3;
        for (int i = 0; i < boardlen; i++)
        {
            for (int j = 0; j < boardlen; j++)
            {
                board[i][j] = 0;
            }
        }
    }
    void to_string() const
    {
        int boardlen = 3;
        int j = 0;
        for (int i = 0; i < boardlen; i++)
        {

            cout << board[i][j] << " | " << board[i][j + 1] << " | " << board[i][j + 2] << endl;
            if (i < 2)
                cout << "---------" << endl;
        }
        cout << endl;
        return;
    }
    int gameStatus() const
    {
        for (int x = 0; x < 3; x++)
        {
            if ((board[0][x] == board[1][x]) && (board[1][x] == board[2][x]) && board[0][x] != 0)
                return board[0][x];
            if ((board[x][0] == board[x][1]) && (board[x][1] == board[x][2]) && board[x][0] != 0)
                return board[x][0];
        }
        if ((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) && board[0][0] != 0)
            return board[0][0];
        if ((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]) && board[0][2] != 0)
            return board[0][2];
        int boardlen = 3;
        for (int i = 0; i < boardlen; i++)
        {
            for (int j = 0; j < boardlen; j++)
            {
                if (board[i][j] == 0)
                    return 0;
            }
        }
        return 3;
    }
    bool move(int player, int row, int col)
    {
        if (row < 0 || col < 0 || row > 2 || col > 2)
            return false;
        if (board[row][col] == 0)
        {
            board[row][col] = player;
            return true;
        }
        else
            return false;
    }
    TicTacToe()
    {
        clearBoard();
    }
};

int main()
{
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    int p1 = 1;
    int p2 = 2;
    int turn = 1;
    int m1 = 0;
    int m2 = 0;
    TicTacToe board;
    while (board.gameStatus() == 0)
    {
        if (turn % 2 != 0)
        {
            while (true)
            {
                cout << "Play 1 move: enter row and column: " << endl;
                board.to_string();
                cin >> m1 >> m2;
                if (board.move(p1, m1, m2))
                    break;
                else
                    cout << "Invalid move " << endl;
            }
        }
        else
        {
            while (true)
            {
                cout << "Play 2 move: enter row and column: " << endl;
                board.to_string();
                cin >> m1 >> m2;
                if (board.move(p2, m1, m2))
                    break;
                else
                    cout << "Invalid move " << endl;
            }
        }
        turn++;
        if (board.gameStatus() == 1)
        {
            board.to_string();
            cout << "Player 1 wins!" << endl;

            break;
        }
        if (board.gameStatus() == 2)
        {

            board.to_string();
            cout << "Player 2 wins!" << endl;
            break;
        }
        if (board.gameStatus() == 3)
        {

            board.to_string();
            cout << "Draw" << endl;
            break;
        }
    }
}