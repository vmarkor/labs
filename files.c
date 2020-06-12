#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

// Читает символ из файла по заданой позиции.
// Аргумент seek принимает константы SEEK_SET / SEEK_END / SEEK_CUR из stdio.h
// Если был некорректно прочитан символ, возвращает EOF.
int read_from_pos(FILE* file, size_t pos, int seek)
{
    fseek(file, pos, seek);
    return fgetc(file);
}

// Читает цифру из файла по заданой позиции.
// Если прочтена не цифра, фукнция возвращает значение -1.
// При успешном чтении возвращает число (int).
int read_digit(FILE* file, size_t pos, int seek)
{
    int digit = read_from_pos(file, pos, seek);
    if (!isdigit(digit))
    {
        return -1;
    }
    return digit - '0';
}

int main(int argc, char* argv[])
{
    // Проверить, что было переданно 3 аргумента, иначе вывести ошибку.
    if (argc != 4)
    {
        printf("Pass path to 2 text files with numbers to sum\n");
        printf("and path to text file for result\n");
        printf("Example: %s first.txt second.txt result.txt\n", argv[0]);
        return 1;
    }

    const char* first_dir = argv[1];
    const char* second_dir = argv[2];
    const char* result_dir = argv[3];

    // Открыть первый файл
    FILE* first = fopen(first_dir, "r");
    // Если выставлен код ошибки
    if (errno != 0)
    {
        // Вывести ошибку
        printf("%s -- %s\n", first_dir, strerror(errno));
        return 1;
    }

    // Открыть второй файл
    FILE* second = fopen(second_dir, "r");
    if (errno != 0)
    {
        printf("%s -- %s\n", second_dir, strerror(errno));
        return 1;
    }

    // Вычислить длинны чисел и числа-результата.
    fseek(first, 0L, SEEK_END);
    fseek(second, 0L, SEEK_END);

    size_t first_len = ftell(first);
    size_t second_len = ftell(second);
    size_t result_len = ((first_len > second_len) ? first_len : second_len) + 1; // Наиб. длинна + 1

    // Открыть файл для результата
    FILE* result = fopen(result_dir, "w");
    if (errno != 0)
    {
        printf("%s -- %s\n", result_dir, strerror(errno));
        return 1;
    }

    // Считывать каждую цифру, суммировать и записывать в файл.
    int carry = 0;
    for (size_t digit = 1; digit < result_len; digit++)
    {
        int first_digit = 0;
        int second_digit = 0;

        if (digit <= first_len)
        {
            first_digit = read_digit(first, -digit, SEEK_END);
            if (first_digit == -1)
            {
                printf("Not a number in file %s!\n", first_dir);
                return 2;
            }
        }
        if (digit <= second_len)
        {
            second_digit = read_digit(second, -digit, SEEK_END);
            if (second_digit == -1)
            {
                printf("Not a number in file %s!\n", second_dir);
                return 2;
            }
        }

        // Вычислить сумму цифр и перенос
        int result_digit = (first_digit + second_digit + carry) % 10;
        carry = (first_digit + second_digit + carry) / 10;

        // Записать полученную цифру в файл с результатом
        fseek(result, result_len - digit, SEEK_SET);
        int symbols_written = fprintf(result, "%d", result_digit);
        // fprintf возвращает число записанных символов при успехе или число <= 0 при ошибке.
        if (symbols_written <= 0)
        {
            printf("Encounter error while writing into file!\n");
            return 3;
        }
    }

    // Записать в начало файла последнюю цифрую.
    // Если переноса не было, запишет ноль. Иначе будет мусор на первой позиции в файле.
    fseek(result, 0L, SEEK_SET);
    int symbols_written = fprintf(result, "%d", carry);
    if (symbols_written <= 0)
    {
        printf("Encounter error while writing into file!\n");
        return 3;
    }

    // Закрыть файлы.
    fclose(first);
    fclose(second);
    fclose(result);
    return 0;
}
