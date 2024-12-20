#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// static size_t	ft_toklen(const char *s, char c)
// {
// 	size_t	ret;
// 	size_t	i;

// 	ret = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			++ret;
// 			while (s[i] && s[i] != c)
// 				++s;
// 		}
// 		else
// 			++s;
// 	}
// 	return (ret);
// }

// char	**split(const char *s, char c)
// {
// 	char	**ptr;
// 	size_t	i;
// 	size_t	len;

// 	if (s == 0)
// 		return (0);
// 	i = 0;
// 	ptr = malloc(sizeof(char *) * (ft_toklen(s, c) + 1));
// 	if (ptr == 0)
// 		return (0);
// 	while (*s)
// 	{
// 		if (*s != c)
// 		{
// 			len = 0;
// 			while (*s && *s != c && ++len)
// 				++s;
// 			ptr[i++] = ft_substr(s - len, 0, len);
// 		}
// 		else
// 			++s;
// 	}
// 	ptr[i] = 0;
// 	return (ptr);
// }

void echo_command(char **args) {
    bool suppress_newline = false;
    int start_index = 1;  // Start after the "echo" command

    if (args[start_index] && strcmp(args[start_index], "-n") == 0) {
        suppress_newline = true;
        start_index++;  // Skip "-n"
    }
    for (int i = start_index; args[i] != NULL; i++) {
        printf("%s", args[i]);
        if (args[i + 1] != NULL) {
            printf(" ");  // Add a space between arguments
        }
    }
    // if (!suppress_newline) {
    //     printf("\n");
    // }
}

// void execute_pwd(void)
// {
//     char *cwd;

//     cwd = getcwd(NULL, 0);
//     if (cwd == NULL)
//     {
//         perror("pwd");
//         return;
//     }
//     printf("%s\n", cwd);
//     free(cwd);
// }

// int main(int argc, char **argv)
// {
//     if(strcmp(argv[1], "echo"))
//         echo_command(argv);
//     if (argc == 2 && strcmp(argv[1], "pwd") == 0)
//         execute_pwd();
//     else
//         printf("Usage: %s pwd\n", argv[0]);
//     return 0;
// }

int main(int argc, char **argv) {
    
    //printf("%s\n",argv[2]);
    // Example 1: echo "Hello World"
    //char **example1;
    if (strcmp(argv[2], "-n") == 0)
    {
        //example1 = split(argv[3]);
        printf("Output of \"echo -n\": ");
    }
    else
    {
        //example1 = split(argv[2]);
        printf("Output of \"echo\": ");
    }
    echo_command(argv+1);

    return 0;
}

