//
// Created by ferri on 8/27/2019.
//

#ifndef TEST_MINISHELL_H
#define TEST_MINISHELL_H

#define	FALSE	0
#define TRUE	1
#define	LINE_LEN	512
#define MAX_ARGS	64
#define MAX_ARG_LEN	16
#define	MAX_PATHS	64
#define MAX_PATH_LEN	512
#define WHITESPACE	" .,\t"
#define MAX_PASSWD  20
#define MAX_UNAME   16
#define MAX_USERS 10

#ifndef NULL
#define	NULL	0
#endif

struct command_t
{
    char *name;
    int argc;
    char *argv[MAX_ARGS];
};

typedef struct
{
    char* question, answer;
} SECURITY_QUESTION;

typedef struct {
    char *uname;
    char *passwd;
    SECURITY_QUESTION *securityQuestion[3];
}USER;

#endif //TEST_MINISHELL_H
