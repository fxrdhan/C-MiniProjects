#include <stdio.h>
#include <string.h>     // for string manipulation functions

#define TOTAL_NUMBER_OF_QUESTIONS 5
#define FILE_PATH "/home/fxrdhan/Dev/myCLI/projects/temp/highest_score_quiz.txt"

typedef struct {
    char questions[255];
    char options[5][100];
    char correct_answer;
} Quiz;

Quiz quizList[TOTAL_NUMBER_OF_QUESTIONS] = {
    {"Program ini dibuat menggunakan bahasa pemrograman apa?", {"Python", "Java", "C", "C++", "Assembly"}, 'c'},
    {"Siapa pengembang bahasa C?", {"Dennis Ritchie", "Bjarne Stroustrup", "Microsoft", "Guido van Rossum", "Brendan Eich"}, 'a'},
    {"Directive preprocessor apa yang digunakan untuk menyertakan file header?", {"#define", "#include", "#ifdef", "#endif", "#undef"}, 'b'},
    {"Tipe data apa yang digunakan untuk menyimpan nilai ASCII karakter?", {"float", "string", "int", "double", "char"}, 'e'},
    {"Bagaimana cara mendeklarasikan array 2D dengan 3 baris dan 4 kolom?", {"int array[4][3];", "int array[][] = {3, 4};", "int array[3, 4];", "int array[3][4];", "int 3x4 array;"}, 'd'},
};

void headerArt(){
    printf("\x1b[1;38;5;165m  ___    __  __  ____  _  _  ____    _____  __  __  ____  ____ \n / __)  (  \\/  )(_  _)( \\( )(_  _)  (  _  )(  )(  )(_  _)(_   )\n( (__    )    (  _)(_  )  (  _)(_    )(_)(  )(__)(  _)(_  / /_\n \\___)  (_/\\/\\_)(____)(_)\\_)(____)  (___/\\\\(______)(____)(____)\x1b[0m\n\n");
}

void printQuestionWithBorder(int num, Quiz q) {
    int width = 80; // border width

    // print the top border
    printf("\x1b[1;38;5;165m+\x1b[0m");
    for (int i = 0; i < width - 2; i++) printf("\x1b[1;38;5;165m─\x1b[0m");
    printf("\x1b[1;38;5;165m+\x1b[0m\n");

    // print the questions with number of list
    printf("\x1b[1;38;5;165m|\x1b[0m %d. %-73s \x1b[1;38;5;165m|\x1b[0m\n", num, q.questions);
    /**
    %   - Start of the format specifier
    -   - Indicates left alignment of the string
    75  - Specifies the width of the field; the string will occupy 75 characters in total
    s   - The corresponding argument is a string
    */

    // print the opstions
    for (int i = 0; i < 5; i++) {
        printf("\x1b[1;38;5;165m|\x1b[0m    %c) %-70s \x1b[1;38;5;165m|\x1b[0m\n", 'a' + i, q.options[i]);
    }

    // print the bottom border
    printf("\x1b[1;38;5;165m+\x1b[0m");
    for (int i = 0; i < width - 2; i++) printf("\x1b[1;38;5;165m─\x1b[0m");
    printf("\x1b[1;38;5;165m+\x1b[0m\n");
}

int main() {
    int score = 0;
    char answer;

    headerArt();

    for (int i = 0; i < TOTAL_NUMBER_OF_QUESTIONS; i++) {
        printQuestionWithBorder(i + 1, quizList[i]);
        printf("\x1b[38;5;165m┌─(\x1b[0mJawaban Anda\x1b[38;5;165m)\x1b[0m\n\x1b[38;5;165m└─> \x1b[0m");
        scanf(" %c", &answer);
        getchar(); // consume the leftover newline character

        if (answer == quizList[i].correct_answer) {
            score+=20;
        }

        if (i != TOTAL_NUMBER_OF_QUESTIONS - 1) { // (don't prompt for the last question)
            printf("\033[3m// Press Enter to the next question...\033[0m");
            getchar(); // wait for the user to press Enter
            printf("\033[A\033[2K"); // move one line up and clear that line
        }
    }

    int highestScore = 0;
    FILE *file = fopen(FILE_PATH, "r");
    if (file) {
        if (fscanf(file, "%d", &highestScore) != 1) {
            highestScore = 0; // set to default if reading failed
        }
        fclose(file);
    } else {
        highestScore = 0;
    }

    if (score > highestScore) {
        highestScore = score;
        file = fopen(FILE_PATH, "w");
        if (file) {
            fprintf(file, "%d", highestScore);
            fclose(file);
            printf("\nSelamat! Anda mencetak skor tertinggi baru dengan skor: %d\n", score);
        } else {
            perror("Gagal membuka file untuk penulisan\n");
        }
    } else {
        printf("\nSkor Anda: %d\nSkor Tertinggi Anda: %d\n", score, highestScore);
    }

    return 0;
}
