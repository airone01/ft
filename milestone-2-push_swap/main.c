/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:25:47 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/10 18:21:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

char **stdin_stack(int argc, char **argv);

/**
 * Main entrypoint for
 * @param   argv
 * @param   argc
 * @returns POSIX return code
 */
int main(int argc, char **argv)
{
    char    **stack;

    (void) argv;
    if (argc <= 1)
        return (1);
    stack = stdin_stack(argc, argv);
    free_stack(stack);
    return(0);
}

/**
 * Gets a stack from CLI arguments
 * @param   argc    arguments count
 * @param   argv    arguments
 * @returns         stack
 */
char **stdin_stack(int argc, char **argv)
{
    char    **out;
    char    **tmp;

    out = ft_calloc(1, sizeof (char **));
    if (!out)
        return (NULL);
    while (argc--)
    {
        tmp = ft_split(*argv++, ' ');
        if (!tmp)
            return (free_stack(stack), NULL);
        while (*tmp)
            *out++ = *tmp++;
    }
    *out = NULL;
    return (out);
}
