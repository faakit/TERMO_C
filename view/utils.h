#ifndef UTILS_H
#define UTILS_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#define UP_ARROW    65
#define LEFT_ARROW  68
#define DOWN_ARROW  66
#define RIGHT_ARROW 67
#define KB_A 97
#define KB_B 98
#define KB_C 99
#define KB_D 100
#define KB_E 101
#define KB_F 102
#define KB_G 103
#define KB_H 104
#define KB_I 105
#define KB_J 106
#define KB_K 107
#define KB_L 108
#define KB_M 109
#define KB_N 110
#define KB_O 111
#define KB_P 112
#define KB_Q 113
#define KB_R 114
#define KB_S 115
#define KB_T 116
#define KB_U 117
#define KB_V 118
#define KB_X 120
#define KB_W 119
#define KB_Y 121
#define KB_Z 122
#define KB_ENTER 10
#define KB_ESC 27

#define RED   "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW   "\x1B[33m"
#define BLUE   "\x1B[34m"
#define RESET "\x1B[0m"

//Lê o input do teclado sem retornar ao console.
int getch(void);

//Limpa a tela.
void clearScreen();

/* 
Credits: 
https://stackoverflow.com/questions/3276546/how-to-implement-getch-function-of-c-in-linux
*/

#endif