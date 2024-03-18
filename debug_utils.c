/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:54:02 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/18 17:57:35 by ecarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_char_array(const char arr[]) {
    printf("[");
    for (int i = 0; arr[i] != '\0'; i++) {
        printf("%c", arr[i]);
    }
    printf("]\n");
}

void print_str_array(char **arr) {
    printf("[");
    for (int i = 0; arr[i] != NULL; i++) {
        printf("\"%s\", ", arr[i]);
    }
    printf("]\n");
}
