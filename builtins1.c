#include "minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int	is_builtin_command2(char **args)
{
	if (strcmp(args[0], "export") == 0)
		return (1);
	else if (strcmp(args[0], "unset") == 0)
		return (1);
	else if (strcmp(args[0], "env") == 0)
		return (1);
	else if (strcmp(args[0], "exit") == 0)
		return (1);
	return (0);
}

int	is_builtin_command(char **args)
{
	if (!args || !args[0])
		return (0);
	if (strcmp(args[0], "echo") == 0)
		return (1);
	else if (strcmp(args[0], "cd") == 0)
		return (1);
	else if (strcmp(args[0], "pwd") == 0)
		return (1);
	else
		return (is_builtin_command2(args));
	return (0);
}

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

static int	is_only_n(char *word)
{
	int	i;

	i = 0;
	if (!word || *word == '\0')
		return (0);
	if (word[i++] != '-')
		return (0);
	while (word[i])
	{
		if (word[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// static void	many_n(char *word)
// {
//     int i;

//     i = 0;
//     while (word[i])
//     {
        
//     }
// }

void	ft_echo(char **args)
{
	bool	suppress_newline;
	int		start_index;

	suppress_newline = false;
	start_index = 1;
	if (args[start_index] && (strcmp(args[start_index], "-n") == 0
			|| is_only_n(args[start_index]) == 1))
	{
		suppress_newline = true;
		start_index++;
	}
	for (int i = start_index; args[i] != NULL; i++)
	{
		printf("%s", args[i]);
		if (args[i + 1] != NULL)
		{
			printf(" ");
		}
	}
	if (!suppress_newline)
	{
		printf("\n");
	}
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
		return(1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return(0);
}

#include <errno.h>

// Função para mudar de diretório
void my_cd(const char *path) {
    char *home_dir;

    // Caso o caminho seja NULL ou "~", muda para o diretório inicial
    if (path == NULL || strcmp(path, "~") == 0) {
        home_dir = getenv("HOME");
        if (!home_dir) {
            printf("Erro: Variável HOME não está definida.\n");
            return;
        }
        path = home_dir;
    }

    // Tenta mudar para o diretório especificado
    if (chdir(path) != 0) {
        // Exibe uma mensagem de erro detalhada
        fprintf(stderr, "Erro ao mudar para o diretório '%s': %s\n", path, strerror(errno));
        return;
    }
}
 
int ft_cd(char **input_path, t_env *envs) {
    char *path = NULL;

	if (input_path[1] == NULL || (input_path[1][0] == '~' && input_path[1][1] == '\0')) 
	{
        path = ft_getenv("HOME", envs);
        if (path == NULL) {
            printf("Error: path HOME not specified.\n");
            return (1);
        }
    }
	else
        path = input_path[1];
	if (chdir(path) != 0) {
        perror("cd");
        return (1);
    }
    char *current_dir = getcwd(NULL, 0);
    if (current_dir)
        free(current_dir);
	else
        perror("getcwd");
	return (0);
}

// int main(int argc, char **argv)
// {
//     if(strcmp(argv[1], "echo"))
//         echo_command(argv);
//     if (argc == 2 && strcmp(argv[1], "pwd") == 0)
//         execute_pwd();
//     else
//         printf("Usage: %s pwd\n", argv[0]);
//     return (0);
// }

/* int main(int argc, char **argv) {

	//printf("%s\n",argv[2]);
	// Example 1: echo "Hello World"
	//char **example1;
	if (!(argc > 2))
		return (0);
	if (strcmp(argv[2], "-n") == 0)
	{
		//example1 = split(argv[3]);
		printf("Output of \"echo -n\": ");
		echo_command(argv+1);
	}
	else
	{
		//example1 = split(argv[2]);
		printf("Output of \"echo\": ");
		echo_command(argv+1);
		printf("\n");
	}

	return (0);
} */

// void    ft_unset(t_env **envs, char *key_name)
// {
//     while()
//     ;
// }
