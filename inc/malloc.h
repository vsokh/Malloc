/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsokolog <vsokolog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:55:41 by vsokolog          #+#    #+#             */
/*   Updated: 2021/04/07 16:06:55 by vsokolog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdio.h>

# include <unistd.h>

# include <sys/mman.h>

# include <sys/resource.h>

# include <string.h>

# include <errno.h>

/* For size_t */
# include <stddef.h>

/* For uintptr_t.  */
# include <stdint.h>

# include <stdlib.h>

# define align(x, alignment)	\
	((x) + (alignment) - 1) & ~((alignment) - 1)

