#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // for boolean data type support (bool, true, false)
#include <unistd.h>     // for usleep function
#include <ctype.h>      // for character manipulation functions
#include <string.h>     // for string manipulation functions

#define bool _Bool
#define true 1
#define false 0
#define BUFFER_SIZE 100  // a sufficiently large buffer size

int main() {
    char input[BUFFER_SIZE];
    float A, B, result;
    char op;            // operation symbols
    _Bool isError;
    int ret;            // variable to store scanf return value

    // guided end command
    printf("\033[3m// Enter \"end\" command if you want to end this session\033[0m\n\n");

    do {
        isError = false;

        // user input
        printf("\x1b[38;5;165m┌─(\x1b[0mEnter two numbers and an operator (+, -, *, /)\x1b[38;5;165m)\x1b[0m\n\x1b[38;5;165m└─> \x1b[0m");

        fgets(input, BUFFER_SIZE, stdin);  // get the entire line

        // check if user wants to end
        if (strncmp(input, "end", 3) == 0) {
            return 0;  // exit the program
        }

        ret = sscanf(input, "%f %c %f", &A, &op, &B);  // parse the numbers and the operator

        // input validation
        if (ret != 3) {
            // handle input error
            usleep(500000);
            printf("\x1b[1;37;41m[ERROR]\x1b[0m: \033[31mInvalid input\033[0m\n");
            isError = true;
        } else {
            // OPERATION
            switch (op) {
                case '+':
                    result = A + B;
                    break;
                case '-':
                    result = A - B;
                    break;
                case '*':
                    result = A * B;
                    break;
                case '/':
                    // error handle (division by zero)
                    if (B == 0) {
                        usleep(500000);
                        printf("\x1b[1;37;41m[ERROR]\x1b[0m: \033[31mDivision by 0\033[0m\n");
                        isError = true;
                    } else {
                        result = A / B;
                    }
                    break;
                default:
                    // HANDLE INVALID OPERATOR
                    usleep(500000);
                    printf("\x1b[0;37;41mERROR\x1b[0m: \033[31mInvalid operator\033[0m\n");
                    isError = true;
            }
        }

        // ERROR MESSAGE
        if (isError) {
            usleep(500000);
            printf("\x1b[1;48;5;208m\x1b[38;5;15m[NOTE]\x1b[0m: \x1b[38;5;208mPlease input a valid operation\x1b[0m\n");
            usleep(500000);
        }

    // loop until valid input
    } while (isError);

    // output result
    usleep(500000);
    printf("The result is: \x1b[32m%g\x1b[0m\n", result);

    return 0;
}
