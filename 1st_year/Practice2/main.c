#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

// функция проверки на повторение цифр в числе
int checkReps(long long number) 
{
    long long cached_number;
    char current_number, comparing_number, flag = 0;
    while (number > 0) 
    {
        flag = 0;
        current_number = number % 10;
        number /= 10;
        cached_number = number;
        while (cached_number > 0) 
        {
            comparing_number = cached_number % 10;
            cached_number /= 10;
            if (comparing_number == current_number) 
            {
                flag++;
                break;
            }
        }
        if (flag) 
            break;
    }
    if (flag > 0) 
        return 0;
    else 
        return 1;
}

void main() 
{
    long long Num1 = 0, Num2 = 0, cached_Num, ord10 = 1;
    int bufs = 0, cows = 0, cNum2;
    char flag = 0, aNum1[MAX], aNum2[MAX], n, i, j, k = 0, temp_num;
    setlocale(LC_ALL, "Russian");

    // приветственный экран
    printf("Игра \"БЫКИ И КОРОВЫ\"\n");
    do 
    {
        printf("Введите длину загадываемого числа (от 1 до %d): ", MAX);
        scanf("%hhd", &n);
    } while ((n < 1) || (n > MAX));

    // вычисление числа без повторяющихся цифр
    srand((unsigned)time(NULL));
    for (i = 1; i < n; i++) 
        ord10 *= 10;
    aNum1[0] = rand() % (9 - 1 + 1) + 1;
    for (i = 1; i < n; i++) 
    {
        temp_num = rand() % (9 - 0 + 1) + 0;
        k = 0;
        for (j = 0; j < i; j++) 
        {
            if (aNum1[j] == temp_num) 
                k++;
        }
        if (k > 0) 
            i--;
        else 
            aNum1[i] = temp_num;
    }
    for (i = 0; ord10 > 0; i++) 
    {
        Num1 += aNum1[i] * ord10;
        ord10 /= 10;
    }
    printf("Отлично, я загадал %d-значное число с неповторяющимися цифрами. Теперь попробуйте угадать его.\n", n);
    printf("Введите %d-значное число: ", n);
    
    while (Num1 != Num2) 
    {
        // запрашиваем число у пользователя
        scanf("%lld", &Num2);
        if (Num1 == Num2) 
            break;
        // подсчет цифр во введенном числе
        cNum2 = 0;
        cached_Num = Num2;
        while (cached_Num > 0) 
        {
            cNum2++;
            cached_Num /= 10;
        }
        // проверка повторений, если кол-во цифр верно, иначе ошибка
        if (cNum2 == n) 
        {
            if (checkReps(Num2) == 0) 
            {
                printf("Цифры в вашем числе повторяются. Повторите попытку ввода: ");
                continue;
            }
        }
        else 
        {
            printf("Вы ввели не %d-значное число. Попробуйте еще раз: ", n);
            continue;
        }
        // засунем число в массив
        cached_Num = Num2;
        i = 0;
        while (cached_Num > 0) 
        {
            aNum2[n - i - 1] = cached_Num % 10;
            cached_Num /= 10;
            i++;
        }
        // посчитаем коров и быков
        cows = bufs = 0;
        for (i = 0; i < n; i++) 
        {
            for (j = 0; j < n; j++) 
            {
                if (aNum1[j] == aNum2[i]) 
                {
                    if (i == j) 
                        bufs++;
                    else 
                        cows++;
                    break;
                }
            }
        }
        // отобразим
        printf("[%lld]: %d коров, %d быков. Попробуйте еще раз: ", Num2, cows, bufs);
    }

    // если вдруг число угадано
    printf("Бинго! Действительно, было загадано число %lld.\n", Num1);
    return;
}