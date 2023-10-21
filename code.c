#include <stdio.h>
#include <stdlib.h>
#include <string.h>             // for string manipulation functions
#include <unistd.h>             // for usleep function
#include <readline/readline.h>  // for command line input with line editing features
#include <readline/history.h>   // for maintaining a history of commands entered by the user

// define a constant for maximum input length
#define MAX_INPUT_LENGTH 100

// global variables to store user input and its length
char input[MAX_INPUT_LENGTH];
int inputLength;

// defining a structure to store project information
struct Project {
    char name[50];          // name of the project, can store up to 49 characters + 1 null terminator
    char nameObject[50];    // name of the object associated with the project
};

// initializing a list of projects
struct Project projects[] = {
    {"Simple Calculator Application", "./projects/simple-calculator-application"},
    {"Student Grade Application", "./projects/student-grade-application"},
    {"Mini Quiz Game", "./projects/mini-quiz-game"}
};

// function to display header
void displayHeader(){
    // ASCII art
    printf("\n███████\x1b[38;5;165m╗\x1b[0m██\x1b[38;5;165m╗\x1b[0m  ██\x1b[38;5;165m╗\x1b[0m██████\x1b[38;5;165m╗\x1b[0m ██████\x1b[38;5;165m╗\x1b[0m ██\x1b[38;5;165m╗\x1b[0m  ██\x1b[38;5;165m╗\x1b[0m █████\x1b[38;5;165m╗\x1b[0m ███\x1b[38;5;165m╗\x1b[0m  ██\x1b[38;5;165m╗\x1b[0m\n");
    printf("██\x1b[38;5;165m╔════╝\x1b[0m\x1b[38;5;165m╚\x1b[0m██\x1b[38;5;165m╗\x1b[0m██\x1b[38;5;165m╔╝\x1b[0m██\x1b[38;5;165m╔══\x1b[0m██\x1b[38;5;165m╗\x1b[0m██\x1b[38;5;165m╔══\x1b[0m██\x1b[38;5;165m╗\x1b[0m██\x1b[38;5;165m║\x1b[0m  ██\x1b[38;5;165m║\x1b[0m██\x1b[38;5;165m╔══\x1b[0m██\x1b[38;5;165m╗\x1b[0m████\x1b[38;5;165m╗\x1b[0m ██\x1b[38;5;165m║\x1b[0m\n");
    printf("█████\x1b[38;5;165m╗\x1b[0m   \x1b[38;5;165m╚\x1b[0m███\x1b[38;5;165m╔╝\x1b[0m ██████\x1b[38;5;165m╔╝\x1b[0m██\x1b[38;5;165m║\x1b[0m  ██\x1b[38;5;165m║\x1b[0m███████\x1b[38;5;165m║\x1b[0m███████\x1b[38;5;165m║\x1b[0m██\x1b[38;5;165m╔\x1b[0m██\x1b[38;5;165m╗\x1b[0m██\x1b[38;5;165m║\x1b[0m\n");
    printf("██\x1b[38;5;165m╔══╝\x1b[0m   ██\x1b[38;5;165m╔\x1b[0m██\x1b[38;5;165m╗\x1b[0m ██\x1b[38;5;165m╔══\x1b[0m██\x1b[38;5;165m╗\x1b[0m██\x1b[38;5;165m║\x1b[0m  ██\x1b[38;5;165m║\x1b[0m██\x1b[38;5;165m╔══\x1b[0m██\x1b[38;5;165m║\x1b[0m██\x1b[38;5;165m╔══\x1b[0m██\x1b[38;5;165m║\x1b[0m██\x1b[38;5;165m║\x1b[0m\x1b[38;5;165m╚\x1b[0m████\x1b[38;5;165m║\x1b[0m\n");
    printf("██\x1b[38;5;165m║\x1b[0m     ██\x1b[38;5;165m╔╝\x1b[0m\x1b[38;5;165m╚\x1b[0m██\x1b[38;5;165m╗\x1b[0m██\x1b[38;5;165m║\x1b[0m  ██\x1b[38;5;165m║\x1b[0m██████\x1b[38;5;165m╔╝\x1b[0m██\x1b[38;5;165m║\x1b[0m  ██\x1b[38;5;165m║\x1b[0m██\x1b[38;5;165m║\x1b[0m  ██\x1b[38;5;165m║\x1b[0m██\x1b[38;5;165m║\x1b[0m \x1b[38;5;165m╚\x1b[0m███\x1b[38;5;165m║\x1b[0m   █▀█ █▀█ █▀█   █ █▀▀ █▀▀ ▀█▀ █▀\n");
    printf("\x1b[38;5;165m╚═╝\x1b[0m     \x1b[38;5;165m╚═╝\x1b[0m  \x1b[38;5;165m╚═╝╚═╝\x1b[0m  \x1b[38;5;165m╚═╝╚═════╝\x1b[0m \x1b[38;5;165m╚═╝\x1b[0m  \x1b[38;5;165m╚═╝╚═╝\x1b[0m  \x1b[38;5;165m╚═╝╚═╝\x1b[0m  \x1b[38;5;165m╚══╝\x1b[0m \x1b[38;5;165m▄\x1b[0m \x1b[38;5;165m█▀▀ █▀▄ █▄█ █▄█ ██▄ █▄▄  █  ▄█\n\x1b[0m");
    printf("\x1b[38;5;165m══════════════════════════════════════════════════════════════════════════════════════════\x1b[0m\n");
    printf("\033[1mRepository: \033[34;4mhttps://github.com/fxrdhan/\033[0m  \033[1m\x1b[38;5;165m||\x1b[0m  \033[1mInstagram: \033[34;4mhttps://www.instagram.com/fxrdhan/\033[0m\n");
    printf("\x1b[38;5;165m══════════════════════════════════════════════════════════════════════════════════════════\x1b[0m\n");
    // guided first command
    printf("\n\033[3m// Try \"help\" to show available commands\033[0m\n");
}

// function to display an animation while running the application
void runningAppAnimation(){
    // runnning app animation
    printf("\n\x1b[1;33mRunning the application\x1b[0m");
    // wait for a second
    sleep(1);
    // loop to create the animation
    for (int i = 0; i < 1; i++) {
        // inner loop to display three dots, one at a time
        for (int j = 0; j < 3; j++) {
            // print a yellow dot
            printf("\x1b[1;33m.\x1b[0m");
            // flush the output buffer to make the dot appear immediately
            fflush(stdout);
            // wait for half a second
            usleep(500000);
        }
        // overwrite the line with the complete message and three dots
        printf("\r\x1b[1;33mRunning the application...\x1b[0m\n");
    }
    // wait for a quarter of a second before returning
    usleep(500000);
}

// function to display an animation while exiting the application
void exitTheApplication() {
    printf("\033[3m// Press Enter to exit the application...\033[0m");
    getchar();
    printf("\033[A\033[2K\n"); // move one line up and clear that line
    // return to the original directory (two levels up)
    chdir("../..");
}

// function to execute user command input
void executeCommand(const char* command) {
    // help info
    if (strcmp(command, "help") == 0) {
        printf("- list/ls\tlist the projects I've made\n- clear/cls\tclear the CLI screen\n- rm -rf *\tclear the CLI temporary files\n- exit\t\texit the CLI\n");
    // clear the CLI screen except ASCII art header
    } else if (strcmp(command, "clear") == 0 || (strcmp(command, "cls") == 0)) {
        #ifdef _WIN32   // windows terminal command
            system("cls");
        #else           // linux terminal command
            system("clear");
        #endif
            displayHeader();
    // exit the CLI screen
    } else if (strcmp(command, "exit") == 0) {
        printf("\033[3m// Press Enter to exit the CLI...\033[0m");
        getchar();
        printf("\033[A\033[2K"); // move one line up and clear that line
        exit(0);
    // validate exit-related commands and provide feedback
    } else if (strcmp(command, "quit") == 0 || strcmp(command, "close") == 0 || strcmp(command, "end") == 0) {
        printf("Command '%s' not found, did you mean:\n command 'exit' to %s this CLI\n", command, command);
    // validate clear-related commands and provide feedback
    } else if (strcmp(command, "cleat") == 0 || strcmp(command, "clr") == 0) {
        printf("Command '%s' not found, did you mean:\n command 'clear' to clear this CLI\n", command);
    // display a list of available projects
    } else if (strcmp(command, "list") == 0 || strcmp(command, "ls") == 0) {
        for (int i = 0; i < sizeof(projects) / sizeof(projects[0]); i++) {
            printf("%d. %s\n", i + 1, projects[i].name);
        }
        printf("Enter the project number to select (e.g., '1' for Simple Calculator Application): \n");
    // clear the CLI temp files
    } else if (strcmp(command, "rm -rf *") == 0) {
        #ifdef _WIN32
            printf("This command is not supported on Windows.\n");
        #else
            system("rm -rf ./projects/temp/*");
            printf("All files in ./projects/temp have been deleted\n");
        #endif
    // execute the specified project based on numeric input
    } else if (strlen(command) > 0) {
        int projectNumber = atoi(command); // ascii to integer
        if (projectNumber >= 1 && projectNumber <= sizeof(projects) / sizeof(projects[0])) {
            printf("\x1b[1;33mCompiling the program:\x1b[0m \x1b[34;1m%s\x1b[0m", projects[projectNumber - 1].nameObject);
            runningAppAnimation();
            // project #1
            if (projectNumber == 1) {
                // navigate to the directory
                chdir("./projects");
                // compile project, place the output in temp directory
                system("gcc -o temp/simple-calculator-application simple-calculator-application.c");
                // navigate to the temp directory
                chdir("temp");
                // run the console app
                system("./simple-calculator-application");
                //delay
                usleep(500000);
                exitTheApplication();
            // project #2
            } else if (projectNumber == 2){
                chdir("./projects");
                system("gcc -o temp/student-grade-application student-grade-application.c");
                chdir("temp");
                system("./student-grade-application");
                usleep(500000);
                exitTheApplication();
            // project #3
            } else if (projectNumber == 3){
                chdir("./projects");
                system("gcc -o temp/mini-quiz-game mini-quiz-game.c");
                chdir("temp");
                system("./mini-quiz-game");
                usleep(500000);
                exitTheApplication();
            }
        } else {
            // if command not listed, display an warning massage
            printf("Command '%s' not found\n", command);
        }
    }
}

int main() {
    // display the ASCII art header
    displayHeader();

    char *input = NULL;     // initialize user input pointer to NULL

    // infinite loop to keep prompting the user for commands
    while (1) {
        char *prompt = "\x1b[38;5;165muser@host\x1b[0m:\x1b[34;1m~\x1b[0m$ ";
        // use readline to read input and provide an editable prompt
        input = readline(prompt);

        rl_on_new_line();

        // if Ctrl-D is pressed, input will be NULL, and we break
        if (!input) {
            break;
        }

        // only save non-empty input to history
        if (*input) {
            add_history(input);
        }

        // process and execute the user's command
        executeCommand(input);
        // free the input memory
        free(input);
    }

    return 0;
}
