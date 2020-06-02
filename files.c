#include <stdio.h>

int main(int argc, char* argv[])
{
    FILE* first = fopen("first.txt", "r");
    FILE* second = fopen("second.txt", "r");
    if (first == NULL || second == NULL)
    {
        return 1;
    }

    fseek(first, 0L, SEEK_END);
    fseek(second, 0L, SEEK_END);

    size_t first_len = ftell(first);
    size_t second_len = ftell(second);
    size_t result_len = ((first_len > second_len) ? first_len : second_len) + 1;

    int first_digit = 0;
    int second_digit = 0;
    int result_digit = 0;
    int carry = 0;

    FILE* result = fopen("result.txt", "w");
    if (result == NULL)
    {
        return 1;
    }
    
    for (size_t digit = 1; digit < result_len; digit++)
    {
        if (digit <= first_len)
        {
            fseek(first, -digit, SEEK_END);
            first_digit = fgetc(first);
            first_digit -= '0';
        }
        if (digit <= second_len)
        {
            fseek(second, -digit, SEEK_END);
            second_digit = fgetc(second);
            second_digit -= '0';
        }
        result_digit = (first_digit + second_digit + carry) % 10;

        fseek(result, result_len - digit, SEEK_SET);
        fprintf(result, "%d", result_digit);

        carry = (first_digit + second_digit + carry) / 10;
        first_digit = second_digit = 0;
    }
    
    fseek(result, 0L, SEEK_SET);
    if (carry != 0) 
    {
        fprintf(result, "%d", carry);
    }
    
    fclose(first);
    fclose(second);
    fclose(result);
    return 0;
}