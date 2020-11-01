#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <string.h>
#define BUFFER_SIZE 2048

void print_menu();
void user_input(wchar_t **wa);
int dir_contents(const wchar_t *sDir, wchar_t ***fileNames,
    ULONGLONG **fileSizes);
void output_by_idxes(int *filesIdxes, wchar_t **fileNames,
     ULONGLONG *fileSizes, int filesCount, int is_format);
void output_formatted_size(ULONGLONG size);
int  find_by_size(ULONGLONG size, int k, ULONGLONG *sizes, int n);
void swap_int(int *var1, int *var2);
void swap_ULL(ULONGLONG *var1, ULONGLONG *var2);

void choosing_sort(ULONGLONG *sizes, int *idxes, int n);
void insert_sort(ULONGLONG *sizes, int *idxes, int n);
void bubble_sort(ULONGLONG *sizes, int *idxes, int n);
int  counting_sort(ULONGLONG *sizes, int *idxes, int n);
void start_quick_sort(ULONGLONG *sizes, int *idxes, int n1, int n2);
void quick_sort(ULONGLONG *a, int *idxes, int n1, int n2);
void start_merge_sort(ULONGLONG *sizes, int *idxes, int l, int r);
void merge_sort(ULONGLONG *sizes, int *idxes, int l, int r);
void merge_sorted(ULONGLONG *sizes, int *idxes, int l, int m, int r);

void main() 
{
    int algo, i, filesCount, error, is_format = 0;
    int *filesIdxes;
    wchar_t *path;
    wchar_t **fileNames;
    ULONGLONG *fileSizes;
    clock_t start, end;
    float total_time = 0.0f;
    setlocale(LC_ALL, "Russian");
    
    printf("====================== ФАЙЛОВЫЙ МЕНЕДЖЕР ======================");
    do {
        error = 0;
        printf("\nДля завершения работы программы нажмите Ctrl+C или закройте окно.");
        printf("\nВведите путь к папке: ");
        user_input(&path);
        filesCount = dir_contents(path, &fileNames, &fileSizes);
        if (filesCount == -1)
        {
            printf("Указанный путь не найден. Проверьте правильность ввода.\n");
            continue;
        }
        if (filesCount == 0)
        {
            printf("Папка не содержит элементов. Укажите другой путь.\n");
            continue;
        }
        filesIdxes = (int*)malloc((filesCount + 1) * sizeof(int));
        for (i = 0; i < filesCount; i++)
            filesIdxes[i] = i;
        printf("%d файлов найдено.\n", filesCount);
        print_menu();
        printf("Выберите алгоритм сортировки: ");
        scanf("%d%*c", &algo);
        switch (algo)
        {
            case 1:
                start = clock();
                choosing_sort(fileSizes, filesIdxes, filesCount);
                end = clock();
                break;
            case 2:
                start = clock();
                insert_sort(fileSizes, filesIdxes, filesCount);
                end = clock();
                break;
            case 3:
                start = clock();
                bubble_sort(fileSizes, filesIdxes, filesCount);
                end = clock();
                break;
            case 4:
                start = clock();
                error = counting_sort(fileSizes, filesIdxes, filesCount);
                end = clock();
                break;
            case 5:
                start = clock();
                start_quick_sort(fileSizes, filesIdxes, filesIdxes[0],
                    filesIdxes[filesCount - 1]);
                end = clock();
                break;
            case 6:
                start = clock();
                start_merge_sort(fileSizes, filesIdxes, filesIdxes[0],
                    filesIdxes[filesCount - 1]);
                end = clock();
                break;
            default:
                printf("Неверный номер.\n");
                continue;
        }
        total_time = (float)(end - start) / CLOCKS_PER_SEC;
        if (error == 0)
        {
            printf("Отобразить размеры в удобном формате? (0 - нет, 1 - да) ");
            scanf("%d", &is_format);
            printf("Список файлов в папке:\n");
            output_by_idxes(filesIdxes, fileNames, fileSizes, filesCount, is_format);
            printf("ВРЕМЯ, ЗАТРАЧЕННОЕ НА СОРТИРОВКУ: %.3f с\n", total_time);
        }
        else
        {
            printf("Похоже, что диапазон размеров файлов в папке слишком велик");
            printf(" для сортировки подсчетом.\nПовторите попытку, выбрав");
            printf(" другой метод сортировки. Нажмите Enter, чтобы продолжить.\n");
        }
        getchar();
        for (i = 0; i < filesCount; i++)
            free(fileNames[i]);
        free(fileNames);
        free(fileSizes);
        free(filesIdxes);
        free(path);
    } while (1);
}

// Вывод меню в консоль
void print_menu()
{
    printf("1 сортировка выбором      | 2 сортировка простыми вставками\n");
    printf("3 пузырьковая сортировка  | 4 сортировка подсчетом\n");
    printf("5 быстрая сортировка      | 6 сортировка слиянием\n");
}

// Ввод пути с клавиатуры
void user_input(wchar_t **str_convert_to)
{
    char *input;
    *str_convert_to = (wchar_t*)malloc(BUFFER_SIZE * sizeof(wchar_t));
    input = (char*)malloc(BUFFER_SIZE * sizeof(char));
    fgets(input, BUFFER_SIZE, stdin);
    input[strlen(input) - 1] = '\0';
    swprintf(*str_convert_to, BUFFER_SIZE, L"%hs", input);
    free(input);
}

// Получение списка файлов и размеров из директории
int dir_contents(const wchar_t *sDir, wchar_t ***fileNames, 
                 ULONGLONG **fileSizes)
{
    int i = 0;
    WIN32_FIND_DATA fdFile;
    HANDLE hFind = NULL;
    wchar_t *sPath;
    sPath = (wchar_t*)malloc(BUFFER_SIZE * sizeof(wchar_t));
    
    wsprintf(sPath, L"%s\\*.*", sDir);
    if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
        return -1;

    //wprintf(L"Path: [%s]\n", sDir);
    do
    {
        if (wcscmp(fdFile.cFileName, L".") != 0 && wcscmp(fdFile.cFileName, L"..") != 0)
            i++;
    } while (FindNextFile(hFind, &fdFile));

    hFind = FindFirstFile(sPath, &fdFile);
    *fileNames = (wchar_t**)malloc(i * sizeof(wchar_t*));
    *fileSizes = (ULONGLONG*)malloc(i * sizeof(ULONGLONG));
    i = 0;
    do
    {
        if (wcscmp(fdFile.cFileName, L".") != 0 && wcscmp(fdFile.cFileName, L"..") != 0)
        {
            ULONGLONG fileSize = fdFile.nFileSizeHigh;
            fileSize <<= sizeof(fdFile.nFileSizeHigh) * 8;
            fileSize |= fdFile.nFileSizeLow;

            (*fileNames)[i] = (wchar_t*)malloc(BUFFER_SIZE * sizeof(wchar_t));
            (*fileSizes)[i] = fileSize;
            wsprintf(sPath, L"%s\\%s", sDir, fdFile.cFileName);
            wsprintf((*fileNames)[i], L"%s", sPath);
            i++;
        }
    } while (FindNextFile(hFind, &fdFile));
    FindClose(hFind);

    free(sPath);
    return i;
}

// Вывод списка файлов по последовательности индексов
void output_by_idxes(int *filesIdxes, wchar_t **fileNames, 
                     ULONGLONG *fileSizes, int filesCount, int is_format)
{
    int i;
    for (i = 0; i < filesCount; i++)
    {
        wprintf(L"Файл: %s Размер: ", fileNames[filesIdxes[i]]);
        if (is_format)
            output_formatted_size(fileSizes[filesIdxes[i]]);
        else
            printf("%lld байт", fileSizes[filesIdxes[i]]);
        printf("\n");
    }
}

// Вывод форматированного размера
void output_formatted_size(ULONGLONG size)
{
    if (size < 1024)
        printf("%d байт", (int)size);
    else if (size < 1024 * 1024)
        printf("%.2f Кб", size / (float)1024);
    else if (size < (ULONGLONG)1073741824)
        printf("%.2lf Мб", size / (double)(1024 * 1024));
    else
        printf("%.2lf Гб", size / (long double)1073741824);
}

// Поиск k-го файла с заданным размером
int find_by_size(ULONGLONG size, int k, ULONGLONG *sizes, int n)
{
    int i = 0, fnd = 0, idx = -1;
    if (k > n)
        return -2;
    while ((i < n) && (fnd < k))
    {
        if (sizes[i] == size)
        {
            idx = i;
            fnd++;
        }
        i++;
    }
    if ((i == n) && (idx == -1))
        return -1;
    return idx;
}

// Обмен значений целочисленных переменных
void swap_int(int *var1, int *var2)
{
    int tmp = *var1;
    *var2 = (*var1 = *var2, tmp);
}

// Обмен значений 64-битных переменных
void swap_ULL(ULONGLONG *var1, ULONGLONG *var2)
{
    ULONGLONG tmp = *var1;
    *var2 = (*var1 = *var2, tmp);
}

// Сортировка выбором
void choosing_sort(ULONGLONG *sizes, int *idxes, int n)
{
    int i, j, minidx;
    ULONGLONG min;
    for (i = 0; i < n; i++) 
    {
        min = sizes[idxes[i]];
        minidx = i;
        for (j = i + 1; j < n; j++) 
            if (sizes[idxes[j]] < min)
            {
                min = sizes[idxes[j]];
                minidx = j;
            }
        swap_int(idxes + minidx, idxes + i);
    }
}

// Сортировка простыми вставками
void insert_sort(ULONGLONG *sizes, int *idxes, int n)
{
    int i, j;
    ULONGLONG temp;
    for (i = 1; i < n; i++) 
    {
        temp = sizes[idxes[i]];
        j = i - 1;
        while ((j >= 0) && (sizes[idxes[j]]>temp))
        {
            idxes[j + 1] = idxes[j];
            idxes[j] = i;
            j--;
        }
    }
}

// Пузырьковая сортировка
void bubble_sort(ULONGLONG *sizes, int *idxes, int n)
{
    int i, j;
    for (i = 0; i < n; i++) 
        for (j = 1; j < n - i; j++) 
            if (sizes[idxes[j - 1]] > sizes[idxes[j]])
                swap_int(idxes + j, idxes + j - 1);
}

// Адаптированная сортировка подсчетом
int counting_sort(ULONGLONG *sizes, int *idxes, int n)
{
    ULONGLONG delta = 0, min = sizes[0], max = sizes[0];
    int *count;
    int i, j, _i_delta = 0, idx = 0;
    for (i = 1; i < n; i++)
    {
        if (sizes[i] < min)
            min = sizes[i];
        if (sizes[i] > max)
            max = sizes[i];
    }
    delta = max - min + 1;
    if (delta * (ULONGLONG)sizeof(int) > (ULONGLONG)UINT_MAX)
        return 1;
    /*    если будет выполнено условие выше, то delta не выйдет за границы    *
    * диапазона значений int, поэтому потеря данных при приведении исключена */
    _i_delta = (int)delta;
    count = (int*)malloc(_i_delta * sizeof(int));
    for (i = 0; i < _i_delta; i++)
        count[i] = 0;
    for (i = 0; i < n; i++)
        count[sizes[i] - min]++;
    for (i = 0; i < _i_delta; i++)
        for (j = 0; j < count[i]; j++, idx++)
            idxes[idx] = find_by_size(i + min, j + 1, sizes, n);
    free(count);
    return 0;
}

// Запуск быстрой сортировки
void start_quick_sort(ULONGLONG *sizes, int *idxes, int n1, int n2)
{
    int i, total_length = n2 - n1 + 1;
    ULONGLONG *newSizes;
    newSizes = (ULONGLONG*)malloc(total_length * sizeof(ULONGLONG));
    for (i = 0; i < total_length; i++)
        newSizes[i] = sizes[i + n1];
    quick_sort(newSizes, idxes, n1, n2);
    free(newSizes);
}

// Быстрая сортировка
void quick_sort(ULONGLONG *sizes, int *idxes, int n1, int n2)
{
    ULONGLONG comp = sizes[(n1 + n2) / 2];
    int i = n1, j = n2;
    do {
        while (sizes[i] < comp)
            i++;
        while (sizes[j] > comp)
            j--;
        if (i <= j) {
            if (sizes[i] > sizes[j])
            {
                swap_int(idxes + i, idxes + j);
                swap_ULL(sizes + i, sizes + j);
            }
            i++;
            j--;
        }
    } while (i <= j);
    if (i < n2)
        quick_sort(sizes, idxes, i, n2);
    if (j > n1)
        quick_sort(sizes, idxes, n1, j);
}

// Запуск сортировки слиянием
void start_merge_sort(ULONGLONG *sizes, int *idxes, int l, int r)
{
    int i, total_length = r - l + 1;
    ULONGLONG *newSizes;
    newSizes = (ULONGLONG*)malloc(total_length * sizeof(ULONGLONG));
    for (i = 0; i < total_length; i++)
        newSizes[i] = sizes[i];
    merge_sort(newSizes, idxes, l, r);
    free(newSizes);
}

// Сортировка слиянием
void merge_sort(ULONGLONG *sizes, int *idxes, int l, int r)
{
    int m;
    if (l >= r) 
        return;
    m = (l + r) / 2;
    merge_sort(sizes, idxes, l, m);
    merge_sort(sizes, idxes, m + 1, r);
    merge_sorted(sizes, idxes, l, m, r);
}

// Слияние отсортированных частей массива
void merge_sorted(ULONGLONG *sizes, int *idxes, int l, int m, int r)
{
    int i, j, s = 0, total_length = r - l + 1;
    int *tmpIdxes;
    ULONGLONG *merged;
    merged = (ULONGLONG*)malloc(total_length * sizeof(ULONGLONG));
    tmpIdxes = (int*)malloc(total_length * sizeof(int));
    for (i = 0; i < total_length; i++)
        tmpIdxes[i] = idxes[i + l];
    i = l;
    j = m + 1;
    while ((i <= m) && (j <= r)) {
        if (sizes[i] <= sizes[j])
        {
            merged[s] = sizes[i];
            tmpIdxes[s] = idxes[i];
            s++; i++;
        }
        else
        {
            merged[s] = sizes[j];
            tmpIdxes[s] = idxes[j];
            s++; j++;
        }
    }
    while (i <= m)
    {
        merged[s] = sizes[i];
        tmpIdxes[s] = idxes[i];
        s++; i++;
    }
    while (j <= r)
    {
        merged[s] = sizes[j];
        tmpIdxes[s] = idxes[j];
        s++; j++;
    }
    for (i = l; i <= r; i++)
    {
        sizes[i] = merged[i - l];
        idxes[i] = tmpIdxes[i - l];
    }
    free(merged);
    free(tmpIdxes);
}