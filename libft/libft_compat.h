/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_compat.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksticks <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:31:42 by ksticks           #+#    #+#             */
/*   Updated: 2019/10/17 16:31:43 by ksticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COMPAT_H
# define LIBFT_COMPAT_H

# include "limits.h"
# ifdef _WIN32
#  include <io.h>
#  define read _read
#  define sleep(x) _sleep(x)
# else
#  include <unistd.h>
# endif

# ifndef ulong

typedef unsigned long		t_ulong;
#  define ulong t_ulong

# endif

# ifndef ullong

typedef unsigned long long	t_ullong;
#  define ullong t_ullong

# endif

# ifndef uint

typedef unsigned int		t_uint;
#  define uint t_uint

# endif

# ifndef byte

typedef unsigned char		t_byte;
#  define byte t_byte

# endif

# ifndef ULLONG_MAX
#  define ULLONG_MAX ULONG_LONG_MAX
# endif

# ifdef __APPLE__
#  define MACOS 1
# else
#  define MACOS 0
# endif

# ifndef STDOUT_FILENO
#  define	STDIN_FILENO	0
#  define	STDOUT_FILENO	1
#  define	STDERR_FILENO	2
# endif

# ifndef LITTLE_ENDIAN
#  define LITTLE_ENDIAN 1234
#  define BIG_ENDIAN 4321
# endif

#endif
