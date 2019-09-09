/* 
 * This is a very minimal shell.  It is only required to find an executable
 * in the PATH, then load it and execute it (using execv).  Since it uses
 * "." (dot) as a separator, it cannot handle file names like "minishell.h"
 * The focus on this exercise is to use fork, PATH variables, and exec.
 * This code can be extended by doing the exercise at the end of Chapter 9.
 *
 * Provided as a solution to Kernel Projects by Gary Nutt with contributions
 * by Sam Siewert and Panos Tsirigotis
 *
 * Modified by Sam Siewert (2013) to remove gets() call considered dangerous and
 * replaced with recommended fgets with line-feed stripping.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
#include <crypt.h>
#include <dirent.h>
#include <signal.h>
#include "minishell.h"

void sigHandler(int);

char *lookupPath(char **, char **);

int parseCommand(char *, struct command_t *);

int parsePath(char **);

void printPrompt();

void readCommand(char *);

char *createPassword(int);

int checkPasswd();

void addUser(USER **, FILE *);

int getUsers(USER **, FILE *);

void putUsers(USER **, FILE *);

int promptUsername();

int unameExists(char **, char *);

void securityQuestion(USER **, int, int);

char promptString[] = "Ferrin shell >";
extern FILE *stdin;
volatile sig_atomic_t sigintRecieved = 0;

int main() {
    signal(SIGINT, sigHandler);
    char commandLine[LINE_LEN];
    char *pathv[MAX_PATHS];
    int numPaths;
    int i, j, len;
    int chPID;        // Child PID
    int stat;        // Used by parent wait
    pid_t thisChPID;
    int status;
    struct command_t command;

    USER *users[10] = {NULL};
    char *home = (char *) getenv("HOME");
    int isLoggedIn = 0;

    // Shell initialization
    for (i = 0; i < MAX_ARGS; i++)
        command.argv[i] = (char *) malloc(MAX_ARG_LEN);

    parsePath(pathv);

    char filepath[128];
    strcpy(filepath, home);
    strcat(filepath, "/.minishell/");

    DIR* dir = opendir(filepath);
    if (dir) {
        closedir(dir);
    } else if (ENOENT == errno) {
        mkdir(filepath, DEFFILEMODE | S_IXUSR);
    } else {
        printf("THere was a problem opining the shell directory.");
        return 1;
    }

    FILE *fptr = NULL;
    char usersFile[128];
    strcpy(usersFile, filepath);
    strcat(usersFile, ".users");
    // if file of users exists read filed load users and check if more users can be added.
    if (access(usersFile, R_OK | W_OK) != -1) {
        FILE *fptrRead = fopen(usersFile, "r");
        int userNum = getUsers(users, fptrRead);
        fclose(fptrRead);
        if (userNum < 10) {
            fptr = fopen(usersFile, "w");
        }
    } else {        //else create the users file and load for reading
        fptr = fopen(usersFile, "w");
        addUser(users, fptr);
    }


    do {
        int userNum = promptUsername();

        if (userNum == -1) {
            printf("Username is not valid \n\n\tEXITING...\n");
            continue;
        }

        // Login Loop
        int loginAttempts;
        for (loginAttempts = 0; loginAttempts < 3 && !isLoggedIn; ++loginAttempts) {
            isLoggedIn = checkPasswd();
        }

        if (!isLoggedIn) {
            printf("Attempts exceeded \n\n");
        }
    } while (!isLoggedIn);

    // Main loop
    while (isLoggedIn || !sigintRecieved) {
        printPrompt();

        // Read the command line and parse it
        readCommand(commandLine);
        printf("commandLine=%s\n", commandLine);

        if ((strcmp(commandLine, "exit") == 0) ||
            (strcmp(commandLine, "quit") == 0)) {
            isLoggedIn = 0;
            break;    // Quit the shell
        }

        parseCommand(commandLine, &command);

#ifdef DEBUG
        printf("... returned from parseCommmand ...\n");

        for(i=0; i<command.argc; i++)
            printf("	argv[%d] = %s\n", i,  command.argv[i]);
#endif

        // Get the full pathname for the file
        command.name = lookupPath(command.argv, pathv);

#ifdef DEBUG
        printf("... returned from lookupPath ...\n");
        printf("	command path = %s\n", command.name);
        for(i=0; i<command.argc; i++)
        printf("	argv[%d] = %s\n", i,  command.argv[i]);
#endif

        if (command.name == NULL) {
            fprintf(stderr, "Command %s not found\n", command.argv[0]);
            continue;
        }

        // Create a process to execute the command
        if ((chPID = fork()) == 0) {
            //  This is the child, that will execute the command requested

#ifdef DEBUG
            printf("child executing: %s\n", command.name);
            for(i=1; i<command.argc; i++)
                printf("	argv[%d] = %s\n", i,  command.argv[i]);
#endif

            execv(command.name, command.argv);
        }

        // Wait for the child to terminate

#ifdef DEBUG
        printf("Parent waiting\n");
#endif

        thisChPID = wait(&stat);
    }

    putUsers(users, fptr);

    fclose(fptr);
// Shell termination

}


char *lookupPath(char **argv, char **dir) {

    // This function inspired by one written by Sam Siewert in Spring 1996
    int i;
    char *result;
    char pName[MAX_PATH_LEN];

    // Check to see if file name is already an absolute path name
    if (*argv[0] == '/') {
        result = (char *) malloc(strlen(argv[0]) + 1);
        strcpy(result, argv[0]);
        return result;
    }

    // Look in PATH directories
    // This code does not handle the case of a relative pathname
    for (i = 0; i < MAX_PATHS; i++) {
        if (dir[i] == NULL) break;
        strcpy(pName, dir[i]);
        strcat(pName, "/");
        strcat(pName, argv[0]);

#ifdef DEBUG
        printf("lookupPath: Checking for %s\n", pName);
#endif

        if (access(pName, X_OK | F_OK) != -1) {

            // File found
#ifdef DEBUG
            printf("lookupPath: Found %s in %s (full path is %s)\n",
            argv[0], dir[i], pName);
#endif
            result = (char *) malloc(strlen(pName) + 1);
            strcpy(result, pName);
            return result;        // Return with success
        }
    }

    // File name not found in any path variable
    fprintf(stderr, "%s: command not found\n", argv[0]);
    return NULL;

}


void sigHandler(int s){
    sigintRecieved = 1;
}


int parseCommand(char *cLine, struct command_t *cmd) {
    // Determine command name and construct the parameter list
    int argc;
    int i, j;
    char **clPtr;

    // Initialization
    clPtr = &cLine;
    argc = 0;

    // Get the command name and parameters
    // This code does not handle multiple WHITESPACE characters
    while ((cmd->argv[argc++] = strsep(clPtr, WHITESPACE)) != NULL);

    cmd->argv[argc--] = '\0';    // Null terminated list of strings
    cmd->argc = argc;

    return 1;
}


int parsePath(char *dirs[]) {
    // This routine based on one written by Panos Tsirigotis, Spring 1989
    int i;
    char *pathEnvVar;
    register char *thePath, *oldp;

    for (i = 0; i < MAX_ARGS; i++)
        dirs[i] = NULL;

    pathEnvVar = (char *) getenv("PATH");
    thePath = (char *) malloc(strlen(pathEnvVar) + 1);
    strcpy(thePath, pathEnvVar);

    i = 0;
    oldp = thePath;

    for (;; thePath++) {
        if ((*thePath == ':') || (*thePath == '\0')) {
            dirs[i] = oldp;
            i++;

            if (*thePath == '\0') break;

            *thePath = '\0';
            oldp = thePath + 1;
        }
    }

#ifdef DEBUG
    printf("Directories in PATH variable\n");
        for(i=0; i<MAX_PATHS; i++)
            if(dirs[i] != '\0')
        printf("	Directory[%d]: %s\n", i, dirs[i]);
#endif

}


void printPrompt() {
    printf("%s ", promptString);
}

void readCommand(char *buffer) {
    // original dangerous stdio call - can over-run buffer, see man gets
    // gets(buffer); 


    // suggested safer replacement call - can't go beyond length provided,
    // but we must strip off the line feed included in the buffer unlike gets
    // 
    fgets(buffer, LINE_LEN, stdin);

    buffer[strlen(buffer) - 1] = '\0';  // overwrite the line feed with null term

    printf("readCommand buffer=%s\n", buffer);
}


char *createPassword(int allowRetry) {
    char salt[] = "$6$................";
    const char *const saltChars =
            "./0123456789ABCDEFGHIJKLMNOPQRST"
            "UVWXYZabcdefghijklmnopqrstuvwxyz";

    char *password;
    char *attemptStatus;

    srandom(time(NULL));

    for (int i = 0; i < 16; ++i) {
        salt[i + 3] = saltChars[random() % 64];
    }

    int passwordsMatch = 0;
    do {
        int goodAttempt = 0;
        do {
            char *passAttempt = getpass("New password: ");

            if (strlen(passAttempt) < 8) {
                attemptStatus = "BAD PASSWORD: Must be at least 8";
            } else if (strlen(passAttempt) > MAX_PASSWD) {
                attemptStatus = "BAD PASSWORD: Must be at most 20";
            } else {
                password = crypt(passAttempt, salt);
                goodAttempt = 1;
            }

            if(!goodAttempt){
                printf("%s\n", attemptStatus);
            }
        } while (!goodAttempt);

        char *passMatch = crypt(getpass("Retype new password: "), salt);

        if (strcmp(password, passMatch) == 0){
            passwordsMatch = 1;
        }

        if(!passwordsMatch && !allowRetry){
            printf("Passwords do not match\n");
            return NULL;
        }
    } while (!passwordsMatch && allowRetry);

    return password;
}


int checkPasswd(){
    return 1;
}


void addUser(USER **users, FILE *fptrAppend) {
    USER *newUser = malloc(sizeof(USER));

    int userPos = -1;

    char buffer[32];
    char *usernames[MAX_USERS] = {NULL};
    char *username;
    char *password;

    for(int i =0;i < MAX_USERS && userPos == -1; ++i){
        if (users[i] == NULL){
            userPos = i;
        } else {
            usernames[i] = users[i]->uname;
        }
    }

    int nameGood = 0;
    char *attemptStatus;
    do{
        printf("New Username: ");
        username = fgets(buffer, LINE_LEN, stdin);

        if(strlen(username) < 1){
            attemptStatus = "BAD USERNAME: Username can not be empty";
        } else if(strlen(username) > MAX_UNAME){
            attemptStatus = "BAD USERNAME: Username to long";
        } else if(unameExists(usernames, username)){
            attemptStatus = "BAD USERNAME: Username already exists";
        } else {
            nameGood = 1;
        }

        if(!nameGood){
            printf("%s\n", attemptStatus);
        }
    } while (!nameGood);
    password = createPassword(1);

    for(int i = 0; i < 3; ++i){
        securityQuestion(&newUser, i, userPos);
    }

    username = strtok(username, "\n");
    password = strtok(password, "\n");

    newUser->uname = strdup(username);
    newUser->passwd = strdup(password);
    users[userPos] = newUser;
}


int getUsers(USER **users, FILE *userPtr){
    return 1;
}


void putUsers(USER **users, FILE *userPtr){
    for(int i = 0; i < MAX_USERS; ++i){
        if(users[i] != NULL){
            fprintf(userPtr, "%s#%s#%s#%s#%s#%s#%s#%s\n", users[i]->uname, users[i]->passwd, users[i]->securityQuestion[0]->question,
                    users[i]->securityQuestion[0]->answer, users[i]->securityQuestion[1]->question, users[i]->securityQuestion[1]->answer,
                    users[i]->securityQuestion[2]->question, users[i]->securityQuestion[2]->answer);
        }
    }
}


int promptUsername() {
    return 1;
}

int unameExists(char **users, char* newName) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if(users[i] != NULL && strcmp(users[i], newName) == 0){
            return 1;
        }
    }
    return 0;
}

void securityQuestion(USER **pUser, int questionNum, int userNum) {
    char *question;
    char *answer = "";
    char buffer[128];

    int questionGood = 0;
    char *attemptStatus = "";
    do{
        printf("Security Question #%d: ", questionNum);
        question = fgets(buffer, LINE_LEN, stdin);

        if(strlen(question) < 1){
            attemptStatus = "BAD QUESTION: question can not be empty";
        } else {
            questionGood = 1;
        }

        if(!questionGood){
            printf("%s\n", attemptStatus);
        }
    } while (!questionGood);

    question = strtok(question, "\n");

    int answerGood = 0;
    do{
        printf("%s? ", question);
        answer = fgets(buffer, LINE_LEN, stdin);

        if(strlen(answer) < 1){
            attemptStatus = "BAD QUESTION: answer can not be empty";
        } else {
            answerGood = 1;
        }

        if(!answerGood){
            printf("%s\n", attemptStatus);
        }
    } while (!answerGood);

    answer = strtok(answer, "\n");

    SECURITY_QUESTION *inputQuestion = malloc(sizeof(SECURITY_QUESTION));
    inputQuestion->question = strdup(question);
    inputQuestion->answer = strdup(answer);

    pUser[userNum]->securityQuestion[questionNum] = inputQuestion;
}
