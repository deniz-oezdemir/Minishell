/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:54:02 by ecarlier          #+#    #+#             */
/*   Updated: 2024/03/20 20:11:24 by ecarlier         ###   ########.fr       */
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

void print_command_list(t_node *head) {
    t_node *current = head;

    while (current != NULL) {
        t_cmddat *data = current->data;

        if (data != NULL && data->full_command != NULL) {
            printf("Command sequence:\n");
            for (int i = 0; data->full_command[i] != NULL; i++) {
                printf("  %s\n", data->full_command[i]);
            }
        } else {
            printf("Empty command sequence\n");
        }

        current = current->next;
    }
}
