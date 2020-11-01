#include <stdio.h>
#include <locale.h>
#include <math.h>

void main() 
{
    double h, w, d, pDvp, pDsp, pWood, m, vZad, vBok, vKry, vDve, vPol;
    setlocale(LC_ALL, "Russian");
    printf("-------- ФИРМА \"УМЕЛЫЕ РУЧКИ\" --------\n");

    printf("Укажите высоту шкафа (в м): ");
    scanf("%lf", &h);
    if ((h < 1.8) || (h > 2.2)) 
    {
        printf("ОШИБКА: Высота шкафа должна быть в промежутке между 1.8 и 2.2 м.");
        return;
    }

    printf("Укажите ширину шкафа (в м): ");
    scanf("%lf", &w);
    if ((w < 0.8) || (w > 1.2)) 
    {
        printf("ОШИБКА: Ширина шкафа должна быть в промежутке между 0.8 и 1.2 м.");
        return;
    }

    printf("Укажите глубину шкафа (в м): ");
    scanf("%lf", &d);
    if ((d < 0.5) || (d > 0.9)) 
    {
        printf("ОШИБКА: Глубина шкафа должна быть в промежутке между 0.5 и 0.9 м.");
        return;
    }

    printf("\nВведите плотность ДВП (в кг/м3): ");
    scanf("%lf", &pDvp);
    if (pDvp <= 0) 
    {
        printf("ОШИБКА: Плотность должна быть больше 0");
        return;
    }

    printf("Введите плотность ДСП (в кг/м3): ");
    scanf("%lf", &pDsp);
    if (pDsp <= 0) 
    {
        printf("ОШИБКА: Плотность должна быть больше 0");
        return;
    }

    printf("Введите плотность дерева (в кг/м3): ");
    scanf("%lf", &pWood);
    if (pWood <= 0) 
    {
        printf("ОШИБКА: Плотность должна быть больше 0");
        return;
    }

    vZad = h * w * 0.005;
    vBok = 2 * h * d * 0.015;
    vKry = 2 * w * d * 0.015;
    vDve = h * w * 0.01;
    vPol = (h - 2 * 0.015) / (0.4 + 0.015) * (w - 2 * 0.015) * (d - 0.005) * 0.015;
    m = vZad * pDvp + vBok * pDsp + vKry * pDsp + vDve * pWood + vPol * pDsp;
    printf("\nМАССА ШКАФА: %.2lf кг\n", m);
}