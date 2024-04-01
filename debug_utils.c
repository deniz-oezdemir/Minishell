/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecarlier <ecarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:54:02 by ecarlier          #+#    #+#             */
/*   Updated: 2024/04/01 13:46:07 by ecarlier         ###   ########.fr       */
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
        printf("%s, ", arr[i]);
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
void print_cmddat(const t_cmddat *cmd) {
    printf("full_command:\n");
    if (cmd->full_command != NULL) {
        for (int i = 0; cmd->full_command[i] != NULL; i++) {
            printf("  \"%s\"\n", cmd->full_command[i]);
        }
    } else {
        printf("  (empty)\n");
    }

    if (cmd->full_path != NULL) {
        printf("full_path: \"%s\"\n", cmd->full_path);
    } else {
        printf("full_path: (empty)\n");
    }

    printf("infile: %d\n", cmd->infile);
    printf("outfile: %d\n", cmd->outfile);
    // Additional fields can be printed similarly
}

void print_cmd_list(const t_node *head) {
    const t_node *current = head;
    while (current != NULL) {
        printf("Node: %p\n", (void *)current);
        printf("Data: ");
        if (current->data != NULL) {
            print_cmddat(current->data);
        } else {
            printf("NULL\n");
        }
        printf("Next: %p\n", (void *)current->next);
        printf("\n");
        current = current->next;
    }
}
