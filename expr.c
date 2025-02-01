/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jorcarva <jorcarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 11:48:22 by jorcarva          #+#    #+#             */
/*   Updated: 2025/02/01 11:49:49 by jorcarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_expr2(const char *input)
{
    
}

int ft_expr(const char *input) {
    char command[5];
    int num1, num2, result;
    char op[3];

    if (sscanf(input, "%4s", command) != 1 || strcmp(command, "expr") != 0) {
        printf("Error: Command not recognized.\n");
        return 1;
    }
    if (sscanf(input + 5, "%d %2s %d", &num1, op, &num2) != 3) {
        printf("Error: Invalid expression format.\n");
        return 1;
    }
    if (strcmp(op, "+") == 0) result = num1 + num2;
    else if (strcmp(op, "-") == 0) result = num1 - num2;
    else if (strcmp(op, "*") == 0) result = num1 * num2;
    else if (strcmp(op, "/") == 0) {
        if (num2 == 0) {
            printf("Error: Division by zero.\n");
            return 1;
        }
        result = num1 / num2;
    }
    else if (strcmp(op, "%") == 0) {
        if (num2 == 0) {
            printf("Error: Modulo by zero.\n");
            return 1;
        }
        result = num1 % num2;
    }
    else if (strcmp(op, "=") == 0) result = (num1 == num2);
    else if (strcmp(op, "!=") == 0) result = (num1 != num2);
    else if (strcmp(op, "<") == 0) result = (num1 < num2);
    else if (strcmp(op, "<=") == 0) result = (num1 <= num2);
    else if (strcmp(op, ">") == 0) result = (num1 > num2);
    else if (strcmp(op, ">=") == 0) result = (num1 >= num2);
    else {
        printf("Error: Unsupported operator '%s'.\n", op);
        return 1;
    }
    printf("%d\n", result);
    return 0;
}
