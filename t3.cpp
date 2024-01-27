#include <iostream>
#include <cstdlib>
#include <ctime>
#include<conio.h>
using namespace std;

void DisplayBoard(char arr[3][3]) {
    cout<<"\n\n\n\n\n";
    int m=0,n=0;
    for (int i = 0; i < 3; i++) {
    	cout<<"_____________\n";
        for (int j = 0; j < 3; j++) {
        	cout<<"| "<<arr[i][j]<<" ";
        }
        cout<<"| ";
        cout << endl;
    }
    cout<<"_____________\n";
}

bool isBoardFull(char arr[3][3]) {
    // Check if the board is full
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

void TakeInput(char arr[3][3], char ch) {
    int input;
    int i, j;
    do {
        cout << "\nEnter box position (1-9): ";
        cin >> input;
        // Convert to array indices
        i = (input - 1) / 3;
        j = (input - 1) % 3;

    } while (input < 1 || input > 9 || arr[i][j] != ' ');

    arr[i][j] = ch;
}

bool isWin(char arr[3][3]) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; i++) {
        if ((arr[i][0] == arr[i][1] && arr[i][1] == arr[i][2] && arr[i][0] != ' ') ||
            (arr[0][i] == arr[1][i] && arr[1][i] == arr[2][i] && arr[0][i] != ' ')) {
            return true;
        }
    }

    if ((arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] != ' ') ||
        (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[0][2] != ' ')) {
        return true;
    }

    return false;
}

bool MakeWinningMove(char arr[3][3], char ch, int& i, int& j) {
    // Check rows
    for (int row = 0; row < 3; row++) {
        if (arr[row][0] == ch && arr[row][1] == ch && arr[row][2] == ' ') {
            i = row;
            j = 2;
            return true;
        } else if (arr[row][1] == ch && arr[row][2] == ch && arr[row][0] == ' ') {
            i = row;
            j = 0;
            return true;
        } else if (arr[row][0] == ch && arr[row][2] == ch && arr[row][1] == ' ') {
            i = row;
            j = 1;
            return true;
        }
    }

    // Check columns
    for (int col = 0; col < 3; col++) {
        if (arr[0][col] == ch && arr[1][col] == ch && arr[2][col] == ' ') {
            i = 2;
            j = col;
            return true;
        } else if (arr[1][col] == ch && arr[2][col] == ch && arr[0][col] == ' ') {
            i = 0;
            j = col;
            return true;
        } else if (arr[0][col] == ch && arr[2][col] == ch && arr[1][col] == ' ') {
            i = 1;
            j = col;
            return true;
        }
    }

    // Check diagonals
    if (arr[0][0] == ch && arr[1][1] == ch && arr[2][2] == ' ') {
        i = 2;
        j = 2;
        return true;
    } else if (arr[1][1] == ch && arr[2][2] == ch && arr[0][0] == ' ') {
        i = 0;
        j = 0;
        return true;
    } else if (arr[0][2] == ch && arr[1][1] == ch && arr[2][0] == ' ') {
        i = 2;
        j = 0;
        return true;
    } else if (arr[1][1] == ch && arr[2][0] == ch && arr[0][2] == ' ') {
        i = 0;
        j = 2;
        return true;
    } else if (arr[0][2] == ch && arr[2][0] == ch && arr[1][1] == ' ') {
        i = 1;
        j = 1;
        return true;
    }

    return false;
}

bool MakeBlockingMove(char arr[3][3], char opponent, int& i, int& j) {
    return MakeWinningMove(arr, opponent, i, j);
}

void ComputerMove(char arr[3][3], char ch) {
    int i, j;

    // Check for blocking opponent's winning move
    if (MakeBlockingMove(arr, (ch == 'X') ? 'O' : 'X', i, j)) {
        cout << "Computer chooses box " << (i * 3 + j + 1) << " to block!" << endl;
    }
    // Check for winning move
    else if (MakeWinningMove(arr, ch, i, j)) {
        cout << "Computer chooses box " << (i * 3 + j + 1) << " to win!" << endl;
    }
    // Make a random move
    else {
    	if(arr[1][1]==' ')
    	{
    		i=1,j=1;
		}
		else{
	        do {
	            i = rand() % 3;
	            j = rand() % 3;
	        } while (arr[i][j] != ' ');
    	}
    }

    arr[i][j] = ch;
}


void GameLoop(char arr[3][3], bool isComputer) {
    char currentPlayer = 'X';
    char computerPlayer = 'O';

    do {
    	system("cls");
        DisplayBoard(arr);

        if (isComputer && currentPlayer == computerPlayer) {
            ComputerMove(arr, computerPlayer);
        } else {
            TakeInput(arr, currentPlayer);
        }

        if (isWin(arr)) {
            DisplayBoard(arr);
            if (isComputer && currentPlayer == computerPlayer) {
                cout << "Computer wins!" << endl;
            } else {
                cout << "Player " << currentPlayer << " wins!" << endl;
            }
            return;
        }

        if (isBoardFull(arr)) {
            DisplayBoard(arr);
            cout << "It's a draw!" << endl;
            return;
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    } while (true);
}

int main() {
	char again;
	do{
    char board[3][3] = { { ' ', ' ', ' ' },
                         { ' ', ' ', ' ' },
                         { ' ', ' ', ' ' } };

    int choice;
    do{
    cout << "Choose game mode:" << endl;
    cout << "1. Two-player game" << endl;
    cout << "2. Play with computer" << endl;
    cout << "\nEnter your choice : ";
    cin >> choice;
    if(choice!=1 && choice!=2)
    	cout<<"\n\aInvalid choice.\n";
}while(choice!=1 && choice!=2);

    srand(static_cast<unsigned>(time(0)));

    if (choice == 1)
        GameLoop(board, false);
    else
        GameLoop(board, true);
        cout<<"\nDo you want to play again? Press Y or y for yes else any key to exit : ";
        again=getch();
}while(again=='y' || again=='Y');
    return 0;
}

