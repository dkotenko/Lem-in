/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_compat.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 16:31:42 by ksticks           #+#    #+#             */
/*   Updated: 2020/02/13 20:51:56 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COMPAT_H
# define LIBFT_COMPAT_H

# include "limits.h"
# ifdef _WIN32
#  include <io.h>
#  define READ _read
# else
#  include <unistd.h>
# endif

# ifndef ULONG

typedef unsigned long		t_ULONG;
#  define ULONG t_ULONG

# endif

# ifndef ULLONG

typedef unsigned long long	t_ULLONG;
#  define ULLONG t_ULLONG

# endif

# ifndef UINT

typedef unsigned int		t_UINT;
#  define UINT t_UINT

# endif

# ifndef BYTE

typedef unsigned char		t_byte;
#  define BYTE t_byte

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
#  define STDIN_FILENO	0
#  define STDOUT_FILENO	1
#  define STDERR_FILENO	2
# endif

# ifndef LITTLE_ENDIAN
#  define LITTLE_ENDIAN 1234
#  define BIG_ENDIAN 4321
# endif

#endif
