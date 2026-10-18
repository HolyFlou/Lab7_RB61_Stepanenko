#include "funcs.h"

char* make_table(double x1, double x2, unsigned int N, double delta)
{
    // Перевірка на мінімально необхідну кількість точок для побудови таблиці
    if (N < 2)
    {
        printf("Кількість точок повинна бути не менше 2!\n");
        return NULL;
    }

    // Виділення достатнього обсягу пам'яті для збереження текстової таблиці
    char *result = malloc(4000);

    // Копіювання початкового заголовка таблиці у виділену пам'ять
    strcpy(result, "*********************************\n*      N   *     X   *   F(X)   *\n*********************************");

    // Цикл для проходу по всіх N точках
    for (unsigned int i = 1; i <= N; i++)
    {
        char temp[100]; // Тимчасовий буфер для форматування одного рядка
        double func = pow(x1, 2); // Обчислення значення функції (у даному випадку x^2)
        
        // Зупинка обчислень, якщо поточний x вийшов за межі кінцевого значення інтервалу
        if (x1 > x2) break;

        strcat(result, "\n+----------+----------+----------+");
        // Форматування значень поточного кроку у рядок
        sprintf(temp, "\n|%10u|%10.2lf|%10.2lf|", i, x1, func);
        // Додавання сформованого рядка до загальної таблиці
        strcat(result, temp);

        // Збільшення поточного значення x на заданий крок
        x1 += delta;
    }

    strcat(result, "\n+----------+----------+----------+\n");
    return result; // Повернення вказівника на готову таблицю
}

void print_output_data(double x1, double x2, unsigned int N, double delta, char* group, char* name) {
    FILE* output_file;

    // Спроба відкрити або створити текстовий файл для запису
    if((output_file = fopen("Texts/output_data.txt", "w+")) != 0) {
        // Запис згенерованої таблиці у файл
        fprintf(output_file, "%s", make_table(x1, x2, N, delta));
        // Запис додаткової інформації (група та ім'я)
        fprintf(output_file, "Group: %s\n", group); 
        fprintf(output_file, "Name: %s\n", name);
        
        fclose(output_file); // Закриття файлу після успішного запису
    } else {
        // Виведення повідомлення про помилку, якщо файл не вдалося відкрити
        printf("Error! File cannot be opened 2");
    }
}

void write_bin_file(double x1, double x2, unsigned int N, double delta) {
    FILE* bin_file;

    // Спроба відкрити бінарний файл для запису
    if((bin_file = fopen("Texts/bin_file.bin", "wb")) != 0) {
        // Спочатку записуємо загальну кількість розрахункових точок
        fwrite(&N, sizeof(unsigned int), 1, bin_file);

        // Цикл для обчислення та збереження кожної пари значень
        for (unsigned int j = 0; j < N; j++) {
            double func = pow(x1, 2);
            
            // Якщо поточне значення перевищило кінцеву межу, припиняємо запис
            if (x1 > x2) break;
            
            // Послідовний запис аргументу (x) та значення функції (f(x))
            fwrite(&x1, sizeof(double), 1, bin_file);
            fwrite(&func, sizeof(double), 1, bin_file);
            
            x1 += delta; // Перехід до наступної точки
        }
        fclose(bin_file); // Закриття бінарного файлу
    } else {
        printf("Error! File cannot be opened 3");
    }
}

void print_bin_data(double x1, double x2, unsigned int N, double delta) {
    FILE* bin_file;

    // Відкриття бінарного файлу для читання
    if ((bin_file = fopen("Texts/bin_file.bin", "rb")) != NULL) {
        unsigned int check_N;
        
        // Зчитування кількості точок, яка була збережена на початку файлу
        fread(&check_N, sizeof(unsigned int), 1, bin_file);

        // Виділення динамічної пам'яті для масиву. 
        // Множимо на 2, оскільки кожна точка має 2 значення: x та f(x).
        double* dynamic_array = (double*)malloc(2 * check_N * sizeof(double));
        
        // Перевірка на успішне виділення пам'яті
        if (dynamic_array != NULL) {
            
            // Зчитування всіх значень з файлу одним блоком безпосередньо у масив
            fread(dynamic_array, sizeof(double), 2 * check_N, bin_file);
            
            printf("\nДані з бінарного файлу (динамічний масив)\n");
            printf("%12s | %20s | %20s\n", "Номер точки", "Значення аргументу", "Значення функції");
            
            // Прохід по масиву та виведення зчитаних пар
            for (unsigned int j = 0; j < check_N; j++) {
                // Витягування x та f(x) з відповідних індексів одновимірного масиву
                double x = dynamic_array[2 * j];
                double fx = dynamic_array[2 * j + 1];

                printf("%12u | %20.4f | %20.4f\n", j + 1, x, fx);
            }
            
            free(dynamic_array);
            
        } else {
            printf("Помилка! Не вдалося виділити пам'ять для масиву.\n");
        }
        
        fclose(bin_file); // Закриття файлу після читання
    } else {
        printf("Error! File cannot be opened 4\n");
    }
}