#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>

int32_t CALLBACK_FAILED = 0x01;
int32_t BAD_INPUT = 0xDEFEC8ED;
int32_t BAD_ARGS  = 0xDEADBABE;

const char* usage = "Usage ex.: ./fact 505\n" \
                    "Takes up to 64 bit number, but modulo 32 bit.";

typedef int (*callback)(int32_t);
extern int fact(int32_t num_to_factor, callback cb);

int process_results(int32_t x) 
{
    int32_t printed_chars = printf("%d ", x);
    if (printed_chars == 0)
    {
        return CALLBACK_FAILED;
    }
    return 0;
}

int main(int argc, char* argv[]) 
{
    if (argc != 2)
    {
        puts(usage);
        return BAD_ARGS;
    }

    // Make number from string 
    // (why convert 64 to 32? to handle maximal negative number case)
    int64_t number = (int32_t) strtoll(argv[1], NULL, 10);
    if (errno != 0)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return BAD_INPUT;
    }

    int32_t ret_code;
    if (number < 0)
    {
        ret_code = process_results(-1);
        if (ret_code != 0)
            return CALLBACK_FAILED;

        // No need to factor
        if (number == -1)
        {
            puts("");
            return ret_code;
        }

        number = (int32_t) (-1 * number);
    }

    // Call factor function
    ret_code = fact(number, process_results);
    puts("");

    // Handle errors
    if (ret_code == CALLBACK_FAILED)
    {
        fprintf(stderr, "Failed to process results!\n");
    }

    return ret_code;
}