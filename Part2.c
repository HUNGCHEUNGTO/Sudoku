

#include <stdio.h>
/* NO other header files are allowed */

/* NO global variables are allowed */


// Initialize the specified game board.
void initGameBoard(int gameBoard[][9], int puzzle[][9]) {

    // TODO: Complete this part
    // Hint: Copies the content of puzzle to gameBoard
    int i, j;
    for (i = 0; i < 9; i ++){
        for (j = 0; j < 9; j ++){
            gameBoard[i][j] = puzzle[i][j];
        }
    }
}

/* Display the specified game board on the screen.
   You are required to exactly follow the output format stated in the project specification.
   IMPORTANT: Using other output format will result in mark deduction. */
void printGameBoard(int gameBoard[][9]) {
    // TODO: Complete this part
    // Hint: 
    // 1. First, try to prints the content of gameBoard
    // 2. Use conditional statement to print ' ' or 'X' for the two cases (empty or selected cell).
    // 3. Add the borders, col/row numbers
    int i, j, k, a;
    printf("  012 345 678\n");

    for (i = 0; i < 9; i ++){
        if (i % 3 == 0) {
           for (a = 0; a < 13; a ++){
                if (a % 4 == 0) printf("+");
                else printf("-");
            }
            printf("\n");
        }
        printf("%d", i);
        for (j = 0; j < 9; j ++){
            if (j % 3 == 0) printf("|");
            if (gameBoard[i][j] == 0) printf(" ");
            else if (gameBoard[i][j] == 'X') printf("X");
            else printf("%d", gameBoard[i][j]);
        }
        printf("|\n");
    }
    for (a = 0; a < 13; a ++){
        if (a % 4 == 0) printf("+");
        else printf("-");
    }
    printf("\n");

}

/* inputBoard() reads a char '1' to '9', or 'H' from the player.
    You need to apply input validation, output error message, and ask the player to retry if its input is invalid.
    gameMode indicates if the game is run in Easy (0) or Hard (1) mode, so that you can determine if hint is allowed.
    *** The function returns 1 if 'H' is inputted (i.e., the player uses a hint), returns -1 if an invalid input is read, and 0 otherwise (valid input). ***
    IMPORTANT: Using other output format will result in mark deduction. */
//int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode, FILE* test){
int inputBoard(int gameBoard[][9], int x, int y, int sol[][9], int gameMode){
    // TODO: Complete this part
    // Hint: Use while loop to keep scanning input from the player
    char c; 
    printf("Input a number [or H: hint]: ");
    // getchar() should be commented before submission
    scanf("\n%c", &c);
    //fscanf(test, "\n%c", &c);

    //printf("%c", c);

    if (c != 'S' && c != 'H' && (c < '1' || c > '9')) {
        printf("Invalid Input.\n");
        return -1;
    }
    if (c == 'S'){
        return 'S';
    }

    if (c >= '1' && c <= '9'){
        gameBoard[x][y] = c - '0';
        return 0;
    } else {
        if (gameMode == 1){
            printf("No hint in Hardmode\n");
            return -1;
        } else {
            return 1;
        }
    } 

}



// This function outputs 1 if the gameBoard is finished (and identical to the solution), and 0 otherwise.
int checkFinish(int gameBoard[][9], int sol[][9]){
    // TODO: Complete this part
    int i, j;
    for (i = 0; i < 9; i ++){
        for (j = 0; j < 9; j ++){
            if (gameBoard[i][j] != sol[i][j]) 
                return 0;
        }
    }
    return 1;
}


/* ** Hard Mode **
    Check the (x, y) cell in the game board to see if it conflicts with other numbers in the same row/column/subgrid.
    You need to output messages to indicate incorrect answer.
    if (x,y) cell causes conflict in 2 or more categories, all such messages will be printed.
    The function returns 1 if (x, y) causes conflicts, and 0 otherwise.
    Hint: The return value can be used to update chances in main.
    IMPORTANT: Using other output format will result in mark deduction. */

int checkSolutionDetail(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int i, j, Pos, p, q, conflicts = 0;
    int check_row[9] = {0};
    int check_column[9] = {0};
    int check_subgrid[9] = {0};
    for (j = 0; j < 9; j ++){
        Pos = gameBoard[x][j];
        if (Pos){
            Pos--;
            if (check_row[Pos]){
                printf("Check again the numbers in row %d.\n", x);
                conflicts = 1;
                break;
            } else {
                check_row[Pos] = 1;
            }
        }
    }    
    for (i = 0; i < 9; i ++){
        Pos = gameBoard[i][y];
        if (Pos){
            Pos--;
            if (check_column[Pos]){
                printf("Check again the numbers in column %d.\n", y);
                conflicts = 1;
                break;
            } else {
                check_column[Pos] = 1;
            }
        }
    }

    p = x / 3 * 3;
    q = y / 3 * 3;
    for (i = 0; i < 3; i ++){
        for (j = 0; j < 3; j ++){
            Pos = gameBoard[p+i][q+j];
            if (Pos){
                Pos--;
                if (check_subgrid[Pos]){
                    printf("Check again the numbers in the subgrid where (%d,%d) is at.\n", x, y);
                    conflicts = 1;
                    break;
                } else {
                    check_subgrid[Pos] = 1;
                }
            }
        }
    }
    return conflicts;
}

/* ** Part 2 **
    checkFillable() checks the row/column/subgrid that the cell (x, y) resides at given the current gameBoard.
    It determines if all the numbers in the same row + column + subgrid contain all numbers 1 - 9, i.e., the cell (x, y) cannot be filled (or is locked).
    It returns 0 if cell (x, y) is locked; and returns 1 if the cell (x, y) can be filled */

int checkFillable(int gameBoard[][9], int x, int y){
    // TODO: Complete this part
    int check[10] = {0};
    int i, j, Pos, p, q;
    
        for (j = 0; j < 9; j ++){
            check[gameBoard[x][j]] = 1;
        }
        for (i = 0; i < 9; i ++){
            check[gameBoard[i][y]] = 1;
        }
        p = x/3 * 3;
        q = y/3 * 3;
        for (i = 0; i < 3; i ++){
            for (j = 0; j < 3; j ++){
                check[gameBoard[p+i][q+j]] = 1;
            }
        }
        for (i = 1; i < 10; i ++){
            if (!check[i]) return 1;
        }
    return 0;
}

/* 
    isLockBoard() determines if the input gameBoard contains a locked cell.
    If there is a locked cell, it prints a locked cell and returns 1.
    It returns 0 if the game board is free of locked cell
    Hint: loop through all empty cell and use checkFillable to aid in checking the cell.
    */
int isLockBoard(int gameBoard[][9]){
    // TODO: Complete this part
    int i;
    for (i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            if (gameBoard[i][j] == 0){
                if (!checkFillable(gameBoard, i, j)){
                    printf("Cell (%d, %d) is locked.\n", i, j);
                    printf("Board is locked\n");
                    return 1;
                }
            } 
        }
    }
    return 0;
}


/* ** Part 2: Save and Load** */
// the savePuzzle function saves the gameBoard and solution to the file "saveGame.txt"
// You may add parameter to this function, e.g, the file to save.
// The program returns 1 if it successfully saves the file, and 0 otherwise.
int savePuzzle(int gameBoard[][9], int sol[][9], FILE* saveGame){
    // TODO: Complete this part
    int i, j;
    for (i = 0; i < 9; i ++){
        fprintf(saveGame, "%d", gameBoard[i][0]);
        for (j = 1; j < 9; j ++){
            fprintf(saveGame, " %d", gameBoard[i][j]);
        }
        fprintf(saveGame, "\n");
    }
    fprintf(saveGame, "\n");

    for (i = 0; i < 9; i ++){
        fprintf(saveGame, "%d", sol[i][0]);
        for (j = 1; j < 9; j ++){
            fprintf(saveGame, " %d", sol[i][j]);
        }
        fprintf(saveGame, "\n");
    }
    printf("Game Saved.\n");
    return 1;
}

// the loadPuzzle function load the gameBoard and solution from the file "saveGame.txt"
// You may add parameter to this function, e.g, the file to load.
// The program returns 1 if it successfully loads the file, and 0 otherwise.
int loadPuzzle(int gameBoard[][9], int sol[][9], FILE* puzzle){
    // TODO: Complete this part
    int i, j;
    for (i = 0; i < 9; i ++){
        for (j = 0; j < 9; j ++){
            fscanf(puzzle, "%d", &gameBoard[i][j]);
        }
    }
    for (i = 0; i < 9; i ++){
        for (j = 0; j < 9; j ++){
            fscanf(puzzle, "%d", &sol[i][j]);
        }
    }
}

// A helper function to craft a text file containing the inputs to fill in the puzzle according to the solution.
// Execute it to generate a text file that prints the inputs leading to a finished puzzle
// To Debug:
//  In Powershell, run: Get-Content .\textInput.txt | & .\main.exe
//  or simply run the program, copy and paste contents of the text file to console.
// You may modify the function as you wish
void printSolution(int puzzle[][9],int solution[][9]){
    FILE *fp;
    fp = fopen("textInput.txt", "w");
    if (fp == NULL) {printf("Error in writing file."); return;}

    fprintf(fp,"0\n"); // Change to 1 if runns in Hard mode
    for(int i=0; i<9; i++)
    for (int j=0; j<9; j++){
        if (puzzle[i][j]==0){
            fprintf(fp, "%d %d\n", i, j);
            fprintf(fp, "%d\n", solution[i][j]); // You may print a character to test Hint/Save-load function.
        }
    }
    fclose(fp);
}

/* The main function */
int main()
{
    /* Local variables */
    //FILE* test = fopen("testInput_LockBoard2.txt","r");
    FILE *puzzle, *saveGame;
    int myPuzzle[9][9], mySolution[9][9], isLocked = 0;
    char Load_Saved_Game;
    // Assume both mode uses same set of puzzle
    // In Part 2, read the puzzle and solution from puzzle.txt
    // You may input your puzzle to debug, e.g., replace some entries of the solution by 0 
    
    /*
    int myPuzzle[9][9]={
        {5,0,0,0,6,3,4,0,0},
        {0,0,0,7,0,0,0,0,0},
        {1,0,0,0,5,0,8,3,0},
        {0,0,0,0,1,8,0,0,7},
        {0,0,6,9,0,0,0,0,0},
        {0,4,3,0,0,0,9,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,7,0,0,2,0},
        {3,2,0,6,4,0,5,0,0}
    };
    // The solution
    int mySolution[9][9] = {
        {5,9,8,1,6,3,4,7,2},
        {6,3,2,7,8,4,1,5,9},
        {1,7,4,2,5,9,8,3,6},
        {2,5,9,4,1,8,3,6,7},
        {8,1,6,9,3,7,2,4,5},
        {7,4,3,5,2,6,9,8,1},
        {4,6,5,8,9,2,7,1,3},
        {9,8,1,3,7,5,6,2,4},
        {3,2,7,6,4,1,5,9,8}
    };
    */
    // Game Board
    int gameBoard[9][9];

    // gameMode: {0: Easy  1: Hard}
    // chances is the no. of chances in hard mode
    // hintCount stores the no. of hint used.
    int gameMode, chances = 3, hintCount = 0;

    // store x, y coordinate of a cell
    int x, y;

    // number will store the puzzle ID (player's puzzle selection)
    int number;

    // Create YOUR local variables
    /* Initialize the local variables */
    int win = 0, validIn = 0, inputValid = 0;
    int check = 0;

    // Read the Game mode to gameMode
    // Repeats the input process for an invalid input
    // Set the Game mode and display the message

    // TODO: Read Game Mode and output selected mode
    printf("Load the saved game (y/n)?");
    scanf("%c", &Load_Saved_Game);
    //fscanf(test, "%c", &Load_Saved_Game);

    printf("Enter the game mode [0: Easy. 1: Hard]: ");
    scanf("%d", &gameMode);
    //fscanf(test, "%d", &gameMode);

    while (gameMode != 0 && gameMode != 1){
        printf("Invalid Input.\n");
        printf("Enter the game mode [0: Easy. 1: Hard]: ");
        scanf("%d", &gameMode);
        //fscanf(test, "%d", &gameMode);
    }
    if (gameMode) printf("You have selected Hard mode.\n");
    else printf("You have selected Easy mode.\n");

    if (Load_Saved_Game == 'n'){
        puzzle = fopen("puzzle.txt", "r");
    } else {
        puzzle = fopen("saveGame.txt", "r");
    }
    loadPuzzle(myPuzzle, mySolution, puzzle);

    // Call initGameBoard to read the puzzle to gameBoard
    // and call printGameBoard to print it
    /* Uncomment the following statements to test if they are implemented correctly.
       You can add more if you wish. But remember to delete them before submission*/

    initGameBoard(gameBoard, myPuzzle);
    printGameBoard(gameBoard);

    // The following line calls the helper function, which print the user inputs leading to a finished puzzle
    // printSolution(gameBoard, mySolution);

    // TODO: Your Easy/Hard mode Game starts
    // The following is the suggested workflow
    
    // While the game is not finished:
        while (checkFinish(gameBoard, mySolution) == 0){
            // Let the player select a cell
            printf("Select a row and column: ");
            scanf("%d %d", &x, &y);
            //fscanf(test, "%d %d", &x, &y);
           
            //    Repeat the cell selection process if it is invalid
            while ((x < 0) || (x > 8) || (y < 0 || y > 8) || gameBoard[x][y] != 0){
                if ((x < 0 || x > 8) || (y < 0 || y > 8)) 
                    printf("Out of bound. Input Again.\n");
                else 
                    printf("Occupied.\n");

                printf("Select a row and column: ");
                scanf("%d %d", &x, &y);
                //fscanf(test, "%d %d", &x, &y);
            }      
            gameBoard[x][y] = 'X';  
            // Print Game Board After player chose a valid cell (displayed as 'X')
            printGameBoard(gameBoard);
            // Receive input from the player by calling inputBoard().
            // Use the return value from inputBoard() for program control flow.
            //int returnValue_inputBoard = inputBoard(gameBoard, x, y, mySolution, gameMode, test);
            int returnValue_inputBoard = inputBoard(gameBoard, x, y, mySolution, gameMode);
            
            // If inputBoard indicates invalid input, go back to cell selection
            if (returnValue_inputBoard == 'S'){
                gameBoard[x][y] = 0;
                saveGame = fopen("saveGame.txt", "w");
                savePuzzle(gameBoard, mySolution, saveGame);
                fclose(saveGame);
                chances = 0;
                break;
            }
            else if (returnValue_inputBoard == -1){
                gameBoard[x][y] = 0;
            } 
            // check the answer for different game mode
            // e.g., call checkSolutionDetail() for Hard mode
            else if (returnValue_inputBoard == 0){
                // input is '1' - '9'
                if (gameMode == 0){
                    if (gameBoard[x][y] != mySolution[x][y]){
                    printf("Sorry, %d should not be placed at (%d,%d).\n", gameBoard[x][y], x, y);
                    gameBoard[x][y] = 0;
                    }
                } else {
                    int returnValue_checkSolutionDetail = checkSolutionDetail(gameBoard, x, y);
                    if (returnValue_checkSolutionDetail) {
                        // collision exists
                        chances--;
                        if (!chances){
                            printf("You lose.\n");
                            break;} 
                        else {
                            printf("You have %d chances left. \n", chances);
                            gameBoard[x][y] = 0;
                        }
                    } 
                }
            }
            else {
                hintCount++;
                gameBoard[x][y] = mySolution[x][y];
            }
            // print the game board
            printGameBoard(gameBoard);
            if (isLockBoard(gameBoard)){
                printf("You lose.\n");
                chances = 0;
                break;
            }
            // If the player wins, exit the while loop, else continue the game.
        
    } 

    // Output the winning or losing message
    if (chances) {
        if (gameMode){
            printf("Congratulations! You have finished a puzzle in hard mode with %d chances left.\n", chances);
        } else {
            printf("Congratulations! You have finished a puzzle in easy mode and used %d hints.\n", hintCount);
        }
    } 
    fclose(puzzle);
    return 0;
}
