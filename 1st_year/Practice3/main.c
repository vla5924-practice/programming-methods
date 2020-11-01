#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define START_MIN 1
#define END_MAX 1000

void main() 
{
    int num, sug, count = 0, mode, start = START_MIN, end = END_MAX;
    char act = '<';
    setlocale(LC_ALL, "Russian");
    
    printf("================ Игра \"УГАДАЙ ЧИСЛО\" ========= 0+ ===\nВыберите режим игры\n");
    printf(" * 1 - компьютер загадывает, пользователь отгадывает\n");
    printf(" * 2 - пользователь загадывает, компьютер отгадывает\n");
    printf("Введите цифру (1 или 2): ");
    scanf("%d", &mode);
    srand((unsigned int)time(0));

    if (mode == 1) 
    {
        printf("\nВыбран режим 1 (компьютер загадывает число).\n\n");
        num = rand() % (end - start + 1) + start;
        printf("Компьютер загадал число от 1 до 1000. Попробуйте отгадать его!\n");
        printf("Введите число от 1 до 1000: ");

        do 
        {
            scanf("%d", &sug);
            if (num > sug) 
                printf("Загаданное число больше, чем %d. Попробуйте еще раз: ", sug);
            else if (num < sug) 
                printf("Загаданное число меньше, чем %d. Попробуйте еще раз: ", sug);
            count++;
        } while (num != sug);

        printf("Ура, вы отгадали число %d за %d попыток!\n", num, count);
        return;
    }
    else 
    {
        printf("\nВыбран режим 2 (пользователь загадывает число).\n\n");
        printf("Введите число от 1 до 1000: ");
        scanf("%d", &num);
        while ((num < 1) || (num > 1000)) 
        {
            printf("Ошибка ввода: нужно ввести число от 1 до 1000. Попробуйте еще раз: ");
            scanf("%d", &num);
        }
        while (act != '=') 
        {
            count++;
            sug = rand() % (end - start + 1) + start;
            printf("Я думаю, что вы загадали %d (введите > , < или = ): ", sug);
            scanf(" %c", &act);

            if (act == '>')
                start = sug + 1;
            else if (act == '<')
                end = sug - 1;
            else if (act != '=') 
                printf("Ошибка ввода. Нужно вводить > , < или =.\n");
        }

        printf("Ура, компьютер отгадал число %d за %d попыток!\n", num, count);
        return;
    }
}