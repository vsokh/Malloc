/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokh <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 15:03:26 by vsokh             #+#    #+#             */
/*   Updated: 2021/03/15 18:43:35 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <stddef.h>
# include <string.h>

typedef struct				s_meta_block
{
	size_t					size;
	struct s_meta_block		*next;
	int						free;
	char					data[1];
}							t_meta_block;

void						print_meta_block(t_meta_block *b);
void						print_constants(void);
size_t						align4(size_t x);

#endif
