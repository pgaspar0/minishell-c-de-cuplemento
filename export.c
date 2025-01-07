#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Função que implementa o comportamento do comando export
void export(int argc, char *argv[], char *envp[]) {
    if (argc == 1) {
        // Quando não há argumentos, listamos as variáveis de ambiente exportadas
        for (int i = 0; envp[i] != NULL; i++) {
            // A saída do Bash é no formato "declare -x VARIAVEL=value"
            printf("declare -x %s\n", envp[i]);
        }
    } else {
        // Para cada variável passada como argumento, fazemos o "export"
        for (int i = 1; i < argc; i++) {
            char *var = argv[i];
            char *equals_sign = strchr(var, '=');
            
            if (equals_sign != NULL) {
                // Se houver um '=', isso significa que queremos definir/alterar a variável
                *equals_sign = '\0';  // Remove o '=' para obter o nome da variável
                char *value = equals_sign + 1;  // O valor está após o '='

                // Tenta exportar a variável com o novo valor
                if (setenv(var, value, 1) == -1) {
                    perror("Erro ao exportar a variável");
                    return;
                }
            } else {
                // Caso contrário, tenta exportar a variável
                if (getenv(var) != NULL) {
                    // A variável existe e não precisa ser alterada
                    if (setenv(var, getenv(var), 1) == -1) {
                        perror("Erro ao exportar a variável");
                        return;
                    }
                } else {
                    // A variável não existe
                    if (setenv(var, "", 1) == -1) {
                        perror("Erro ao adicionar a variável");
                        return;
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[], char *envp[]) {
    // Passando o ambiente (envp) explicitamente para a função my_export
    export(argc, argv, envp);
    return 0;
}
