/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abasarud <abasarud@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 13:29:45 by abasarud          #+#    #+#             */
/*   Updated: 2022/04/24 15:28:06 by abasarud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

typedef struct s_sc
{
	int	len;
	int	width;
}	t_sc;

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	if (nb == INT_MIN)
	{
		write(1, "-2147486348", 11);
		return ;
	}
	if (nb >= '0' && nb <= '9')
		ft_putchar(nb + 48);
	else if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(-nb);
	}
	else
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
}

int	ft_intlen(int nb, char c)
{
	int	i;
	int	number;
	int	neg;

	i = 0;
	if (!nb)
		return (1);
	if (nb < 0)
	{
		neg = 1;
		number = -nb;
	}
	else
	{
		neg = 0;
		number = nb;
	}
	if (c == 'd')
	{
		while (number)
		{
			number /= 10;
			i++;
		}
		return (i + neg);
	}
	if (c == 'x')
	{
		while (number)
		{
			number /= 16;
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

void	ft_printhexa(unsigned int x)
{
	char	*hexa;
	int		i;
	int		res[100];

	hexa = "0123456789abcdef";
	i = 0;
	while (x >= 16)
	{
		res[i] = hexa[x % 16];
		x = x / 16;
		i++;
	}
	res[i] = hexa[x];
	while (i >= 0)
	{
		ft_putchar(res[i]);
		i--;
	}
}

char	*ft_strchr(const char *s)
{
	while (*s)
	{
		if (*s == '%')
			return ((char *)s);
		s++;
	}
	if (!s)
		return ((char *)s);
	return (0);
}

int	check_size(int number)
{
	unsigned int	num;
	int				count;

	count = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		count++;
		num = number * (-1);
	}
	else
		num = number;
	while (num > 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

int	print_width(int size, char c)
{
	int	count;

	count = 0;
	while (count < size)
	{
		write(1, &c, 1);
		count++;
	}
	return (count);
}

const char	*ft_search_arg(va_list arg, const char *format, t_sc *sc)
{
	int				d;
	char			*s;
	unsigned int	x;
	
	d = va_arg(arg, int);
	s = va_arg(arg, char *);
	if (*format == 'd')
	{
		ft_putnbr(d);
		sc->len += ft_intlen(d, *format);
	}
	else if (*format == 's')
	{
		if (!s)
		{
			write(1, "(null)", 6);
			sc->len += 6;
		}
		else
		{
			ft_putstr(s);
			sc->len += ft_strlen(s);
		}
	}
	else if (*format == 'x')
	{
		x = va_arg(arg, unsigned int);
		ft_printhexa((unsigned long)x);
		sc->len += ft_intlen((unsigned long)x, *format);
	}
	else
		return (NULL);
	format++;
	return (format);
}

const char	*ft_read_text(t_sc *sc, const char *format)
{
	char	*next;

	next = ft_strchr(format);
	if (next)
		sc->width = next - format;
	else
		sc->width = ft_strlen(format);
	write(1, format, sc->width);
	sc->len += sc->width;
	while (*format && *format != '%')
		++format;
	return (format);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	t_sc	sc;

	va_start(arg, format);
	sc.len = 0;
	sc.width = 0;
	while (*format)
	{
		if (*format == '%')
			format = ft_search_arg(arg, format + 1, &sc);
		else
			format = ft_read_text(&sc, format);
		if (!format)
		{
			write(1, "(null)", 6);
			va_end(arg);
			return (sc.len);
		}
	}
	va_end(arg);
	return (sc.len);
}

#include <stdio.h>

int main()
{
	printf("booba\n");
	ft_printf("booba");
}


