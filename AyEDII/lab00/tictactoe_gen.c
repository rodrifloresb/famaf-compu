#include <stdlib.h>  /* exit() y EXIT_FAILURE */
#include <stdio.h>   /* printf(), scanf()     */
#include <stdbool.h> /* Tipo bool             */

#include <assert.h>  /* assert() */

#define TAM 11
#define CELL_MAX (TAM * TAM - 1) //original (3*3 - 1)

void print_sep(int length) {
    printf("\t ");
    for (int i=0; i < length;i++) printf("................");
    printf("\n");

}

void print_board(char board[TAM][TAM])
{
    int cell = 0;

    print_sep(TAM);
    for (int row = 0; row < TAM; ++row) {
        for (int column = 0; column < TAM; ++column) {
            printf("\t | %d: %c ", cell, board[row][column]);
            ++cell;
        }
        printf("\t | \n");
        print_sep(TAM);
    }
}

char get_winner(char board[TAM][TAM])
{
    char winner = '-';
    bool res = true;
    
    for (unsigned int i = 0; i < TAM; i++)
    {
        //FILAS
        for (unsigned int j = 0; j < TAM; j++)
        {
            res = res && (board[i][0] == board[i][j]);
        }

        if (res)
        {
            winner = board[i][0];
            printf("a");
            break;
        }

        res = true; //si estoy aca es porque no hay fila ganadora

        //COLUMNAS
        for (unsigned int j = 0; j < TAM; j++)
        {
            res = res && (board[0][i] == board[j][i]);
        }

        if (res)
        {
            winner = board[0][i];
            printf("b");
            break;
        }
    }

    res = true; //reset

    for (unsigned int i = 0; i < TAM; i++)
    {
        res = res && (board[0][0] == board[i][i]);
    }
    if (res)
    {
        winner = board[0][0];
        printf("c");
    }
    
    res = true;

    for (int i = TAM-1, j = 0; i > -1, j < TAM; i--, j++)
    {
        res = res && (board[TAM][0] == board[i][j]);

        
    }

    if (res)
    {
        winner = board[TAM][0];
        printf("d");
    }

    
    return winner;
}

bool has_free_cell(char board[TAM][TAM])
{
    bool free_cell=false;

    for (unsigned int i = 0; i < TAM; i++)
    {
        for (unsigned int  j = 0; j < TAM; j++)
        {
            if (board[i][j] == '-')
            {
                free_cell = true;
            }

            if (free_cell)
            {
                break;
            }
        }

        if (free_cell)
        {
            break;
        }
        
    }
    return free_cell;
}

int main(void)
{
    printf("TicTacToe [InCoMpLeTo :'(]\n");

    char board[TAM][TAM];

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            board[i][j] = '-';
        }
    }
    

    char turn = 'X';
    char winner = '-';
    int cell = 0;
    while (winner == '-' && has_free_cell(board)) {
        print_board(board);
        printf("\nTurno %c - Elija posición (número del 0 al %d): ", turn,
               CELL_MAX);
        int scanf_result = scanf("%d", &cell);
        if (scanf_result <= 0) {
            printf("Error al leer un número desde teclado\n");
            exit(EXIT_FAILURE);
        }
        if (cell >= 0 && cell <= CELL_MAX) {
            int row = cell / TAM;
            int colum = cell % TAM;
            if (board[row][colum] == '-') {
                board[row][colum] = turn;
                turn = turn == 'X' ? 'O' : 'X';
                winner = get_winner(board);
            } else {
                printf("\nCelda ocupada!\n");
            }
        } else {
            printf("\nCelda inválida!\n");
        }
    }
    print_board(board);
    if (winner == '-') {
        printf("Empate!\n");
    } else {
        printf("Ganó %c\n", winner);
    }
    return 0;
}