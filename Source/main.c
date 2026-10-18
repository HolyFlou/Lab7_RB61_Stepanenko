#ifdef _WIN32
#include <windows.h>
#endif
#include "funcs.h"

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    
    // Оголошення змінних
    double x1, x2, delta;
    unsigned int N;
    char group[20] = "";
    char name[100] = "";

    FILE* input_data_file;

    // Спроба відкрити текстовий файл із вхідними даними для читання
    if((input_data_file = fopen("Texts/input_data.txt", "r")) != 0) {
        // Зчитування числових параметрів: початок, кінець, кількість точок, крок
        fscanf(input_data_file, "%lf", &x1);
        fscanf(input_data_file, "%lf", &x2);
        fscanf(input_data_file, "%u", &N);
        fscanf(input_data_file, "%lf", &delta);
        
        // Зчитування рядкових даних: групи та імені
        fscanf(input_data_file, "%s", group); 
        // Зчитування імені до кінця рядка (ігноруючи символи перенесення \r\n)
        fscanf(input_data_file, " %[^\r\n]", name);

        // Закриваємо файл після успішного зчитування всіх даних
        fclose(input_data_file);
    } else {
        // Якщо файлу не існує або шлях невірний, виводимо помилку і завершуємо програму
        printf("Error! File cannot be opened 1");
        return 0;
    }

    // Контрольний вивід зчитаних даних у консоль для перевірки
    printf("x1: %lf\n", x1);
    printf("x2: %lf\n", x2);
    printf("N: %d\n", N);
    printf("delta: %lf\n", delta);
    printf("Group: %s\n", group);
    printf("Name: %s\n", name);

    // Виклик функції для створення текстової таблиці та збереження її у файл
    print_output_data(x1, x2, N, delta, group, name);

    // Виклик функції для запису результатів обчислень у бінарний файл
    write_bin_file(x1, x2, N, delta);
    
    // Виклик функції для зчитування та виводу даних з бінарного файлу на екран
    print_bin_data(x1, x2, N, delta);
    
    return 0;
}