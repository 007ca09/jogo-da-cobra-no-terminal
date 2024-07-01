#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

enum KEYBOARD {
    W_KEY = 119,
    S_KEY = 115,
    D_KEY = 100,
    A_KEY = 97
};

typedef struct {
    int x;
    int y;
} Snake;
typedef struct {
    int x;
    int y;
} Apple;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void collision(Snake* snake, int* snakelen, int* score) {
    for (int i = 1; i < *snakelen; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            *score = 0;
            *snakelen = 1;
            snake[0].x = 10;
            snake[0].y = 15;
        }
    }
}

void new_apple_pos(Apple* apple) {
    apple->x = rand() % (35 - 2) + 1;
    apple->y = rand() % (22 - 7) + 6;  
}

int main() {
    char k;
    int snakelen = 1, score = 0;
    Apple apple;
    Snake snake[200];
    //Definindo toda cobra com suas respectivas posições.
    for (int i = 0; i < 200; i++) {
        snake[i].x = 10;
        snake[i].y = 15;
    }
    //Inicializando a posição aleatória da maçã antes do jogo começar
    srand(time(NULL));
    new_apple_pos(&apple);
    gotoxy(apple.x, apple.y);
    while (1) {
        Sleep(200);
        system("cls");
        //Condições de verificações das teclas abaixo. A função 'collision()' está presente para ser detectado apenas quando tiver uma tecla pressionada
        if (kbhit()) {
            k = getch();
        }

        if (k ==  W_KEY) {
            snake[0].y--;
            collision(snake, &snakelen, &score);
        }
        else if (k ==  S_KEY) {
            snake[0].y++;
            collision(snake, &snakelen, &score);
        }
        else if (k ==  D_KEY) {
            snake[0].x++;
            collision(snake, &snakelen, &score);
        }
        else if (k ==  A_KEY) {
            snake[0].x--;
            collision(snake, &snakelen, &score);
        }
        //Renderizando toda a arena do jogo
        printf("SCORE: %d", score);
        gotoxy(0, 2);
        printf("X: %d\nY: %d", snake[0].x, snake[0].y);
        gotoxy(0, 6);
        for (int i = 0; i <= 15; i++) {
            printf("                                   #\n");
        }
        gotoxy(0, 6);
        for (int i = 0; i <= 15; i++) {
            printf("#\n");
        }
            
        for (int i = 0; i <= 35; i++) {
            printf("#");
        }
        gotoxy(0, 5);
        for (int i = 0; i <= 35; i++) {
            printf("#");
        }
        //Atualizando a posição atual da cobra
        for (int i = 0; i < snakelen; i++) {
            gotoxy(snake[i].x, snake[i].y);
            printf("O");
        }
        //Calculando o deslocamento da cobra(Sistema do rabo perseguir a cabeça da cobra)
        for (int i = snakelen - 1; i > 0; i--) { 
            snake[i].x = snake[i-1].x;
            snake[i].y = snake[i-1].y;
        }
    
        if (apple.x == snake[0].x && apple.y == snake[0].y) { // Verificação se a cobra comeu a maçã
            new_apple_pos(&apple);
            snakelen++;
            score++;
            gotoxy(apple.x, apple.y);
        }
        if (snakelen == 199) { //Caso a cobra chegar no tamanho 199(Tamanho máximo que a cobra pode chegar) O jogo finaliza.
            gotoxy(10, 0);
            printf("GAME WIN !");
            break;
        }
        if (snake[0].x <= 0 || snake[0].x >= 35 || snake[0].y <= 5 || snake[0].y >= 22) { //Verificação se caso a cobra colidiu com a parede
            snake[0].x = 10; 
            snake[0].y = 15;
            snakelen = 1;
            score = 0;    
        }
        printf("X"); // Renderizando a maçã
    }
    
    return 0;
}