#include <stdio.h>
#include <stdlib.h>
#include <string.h>     // for string manipulation functions
#include <ctype.h>      // for character manipulation functions

// define a structure for Student with fields for name and scores
struct Student {
    char name[50];      // array to store the student's name (max length 49 + null terminator)
    float *scores;      // pointer to an array of scores
};

// function to determine the grade based on the average score
char* getGrade(float avg) {
    // the ANSI escape sequences are used to color the output.
    if(avg >= 80.01)
        return "\033[1;32mA\033[0m";        // green for 'A'
    else if(avg >= 72.01 && avg <= 80)
        return "\033[1;92mAB\033[0m";       // light green for 'AB'
    else if(avg >= 64.01 && avg <= 72)
        return "\033[1;34mB\033[0m";        // blue for 'B'
    else if(avg >= 56.01 && avg <= 64)
        return "\033[1;36mBC\033[0m";       // cyan for 'BC'
    else if(avg >= 48.01 && avg <= 56)
        return "\033[1;33mC\033[0m";        // yellow for 'C'
    else if(avg >= 40.01 && avg <= 48)
        return "\033[1;91mD\033[0m";        // light red for 'D'
    else
        return "\033[1;31mE\033[0m";        // red for 'E'
}

// get integer input from the user
int getIntegerInput() {
    char buffer[50];    // array to store user input
    int number;
    char *endptr;       // pointer to store the position of the invalid character

    // loop until a valid integer is received
    while (1) {
        fgets(buffer, sizeof(buffer), stdin);

        // check if the user gives empty input
        if (buffer[0] == '\n') {
            printf("\x1b[1;37;41m[ERROR]\x1b[0m: \033[31mNo entries can be processed\033[0m\n\x1b[1;48;5;208m\x1b[38;5;15m[NOTE]\x1b[0m: \x1b[38;5;208mInput must not be empty\x1b[0m\n\x1b[38;5;165m> \x1b[0m");
            continue;
        }

        // check for end command
        if (strcmp(buffer, "end\n") == 0) {
            exit(0);
        }

        number = strtol(buffer, &endptr, 10);

        // check if the end pointer points to a newline or null character
        if (*endptr == '\n' || *endptr == '\0') {
            // if the input is valid, break out of the loop
            break;
        } else {
            // if invalid, print an error message
            printf("\x1b[1;37;41m[ERROR]\x1b[0m: \033[31mInvalid input\033[0m\n\x1b[1;48;5;208m\x1b[38;5;15m[NOTE]\x1b[0m: \x1b[38;5;208mPlease enter only numbers without any characters or spaces\x1b[0m\n\x1b[38;5;165m> \x1b[0m");
        }
    }

    // return the valid integer input by user
    return number;
}

// get string input from the user
void getStringInput(char *input, int size) {
    // loop until a valid string is received
    while (1) {
        // fetch a line of input up to the specified size
        fgets(input, size, stdin);
        // replace the newline character with null terminator to process the string properly
        input[strcspn(input, "\n")] = '\0';

        // check if the user gives empty input
        if (input[0] == '\n') {
            printf("\x1b[1;37;41m[ERROR]\x1b[0m: \033[31mNo entries can be processed\033[0m\n\x1b[1;48;5;208m\x1b[38;5;15m[NOTE]\x1b[0m: \x1b[38;5;208mInput must not be empty\x1b[0m\n\x1b[38;5;165m> \x1b[0m");
            continue;
        }

        // check for end command
        if (strcmp(input, "end") == 0) {
            exit(0);
        }

        int isValid = 1;

        // iterate through the characters of the input string
        for (int i = 0; i < strlen(input); i++) {
            // if a character is neither alphabetic nor a space
            if (!isalpha(input[i]) && input[i] != ' ') {
                isValid = 0;    // mark the input as invalid
                break;
            }
        }

        // if the input string is valid (contains only alphabets and spaces)
        if (isValid) {
            break;      // pass the loop
        } else {
            // if not, display an error message
            printf("\x1b[1;37;41m[ERROR]\x1b[0m: \033[31mInvalid input\033[0m\n\x1b[1;48;5;208m\x1b[38;5;15m[NOTE]\x1b[0m: \x1b[38;5;208mPlease provide a valid string that contains only alphabetic characters and spaces\x1b[0m\n\x1b[38;5;165m> \x1b[0m ");
        }
    }
}

// read multiple space-separated floats from input
void getMultipleFloatInput(float* arr, int numScores) {
    char buffer[100];   // Buffer to store the raw user input.

    // continuously attempt to get user input until valid floats are received.
    while(1) {
        fgets(buffer, sizeof(buffer), stdin);

        // check if the buffer only contains a newline character.
        if (buffer[0] == '\n') {
            printf("\x1b[1;37;41m[ERROR]\x1b[0m: \033[31mNo entries can be processed\033[0m\n\x1b[1;48;5;208m\x1b[38;5;15m[NOTE]\x1b[0m: \x1b[38;5;208mInput must not be empty\x1b[0m\n\x1b[38;5;165m> \x1b[0m");
            continue;
        }
        // check if user input is "end" to exit the program.
        if (strcmp(buffer, "end\n") == 0) {
            free(arr);
            exit(0);
        }
        // remove newline character from the end of the buffer.
        buffer[strcspn(buffer, "\n")] = 0;

        // split the buffer string into tokens based on spaces.
        char *token = strtok(buffer, " ");

        int isValid = 1; // flag to check if the entered floats are valid.
        int count = 0;   // count the number of floats read from input.
        
        // process each token until either all required floats are read or a token is invalid.
        while(token && count < numScores) {
            char *endptr;

            // convert token to float.
            arr[count] = strtof(token, &endptr);

            // check if token is a valid float.
            if(*endptr != '\0') {
                isValid = 0;
                break;
            }

            count++;
            token = strtok(NULL, " ");
        }

        // if the input contains exactly 'numScores' valid floats and there are no extra tokens, break out of the loop.
        if(isValid && count == numScores && token == NULL) {
            break;
        } else {
            printf("\x1b[1;37;41m[ERROR]\x1b[0m: \033[31mInvalid input\033[0m\n\x1b[1;48;5;208m\x1b[38;5;15m[NOTE]\x1b[0m: \x1b[38;5;208mPlease provide %d grades separated by spaces\x1b[0m\n\x1b[38;5;165m> \x1b[0m ", numScores);
        }
    }
}

int main() {
    // define variables
    int n, i, j, numScores;

    // guided end command
    printf("\033[3m// Enter \"end\" command if you want to end this session\033[0m\n\n");
    // prompt the user for the number of students
    printf("\x1b[38;5;165m┌─(\x1b[0mBanyak siswa\x1b[38;5;165m)\x1b[0m\n\x1b[38;5;165m└─> \x1b[0m");
    n = getIntegerInput();

    // create an array of Student structures based on user input
    struct Student students[n];

    // prompt the user for the number of scores to be input for each student
    printf("\x1b[38;5;165m┌─(\x1b[0mBanyak nilai yang akan diinput\x1b[38;5;165m)\x1b[0m\n\x1b[38;5;165m└─> \x1b[0m");
    numScores = getIntegerInput();

    // loop to get the name and scores for each student
    for(i = 0; i < n; i++) {
        // get the name of the student
        // display student numbers starting from 1 (not 0)
        printf("\n\x1b[38;5;165m┌─([\x1b[0m%d\x1b[38;5;165m]\x1b[0m Masukkan nama\x1b[38;5;165m)\x1b[0m\n\x1b[38;5;165m└─> \x1b[0m", i+1);
        getStringInput(students[i].name, sizeof(students[i].name));

        // allocate memory for scores based on the number of scores specified
        students[i].scores = (float*)malloc(numScores * sizeof(float));

        // get the scores for the student
        printf("\x1b[38;5;165m┌─(\x1b[0mMasukkan %d nilai untuk %s\x1b[38;5;165m)\x1b[0m\n\x1b[38;5;165m└─> \x1b[0m", numScores, students[i].name);
        getMultipleFloatInput(students[i].scores, numScores);
    }

    // display the output header
    printf("\n\x1b[38;5;165mOutput\x1b[0m: \n");
    printf("\x1b[38;5;165mNama\t\tRerata\t\tSkor\x1b[0m\n");

    // loop to display the average and grade for each student
    for(i = 0; i < n; i++) {
        float avg = 0.0;
        // calculate the average score for the student
        for(j = 0; j < numScores; j++) {
            avg += students[i].scores[j];
        }
        avg /= numScores;

        // print the student's name, average score, and grade
        printf("%s\t\t%.2f\t\t%s\n", students[i].name, avg, getGrade(avg));

        // free the dynamically allocated memory for scores
        free(students[i].scores);
    }

    return 0;
}
