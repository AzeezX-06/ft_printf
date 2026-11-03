#include "libft/libft.h"
#include <stdarg.h>
#include <unistd.h>

static int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

static size_t	ft_putstr(char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		write(1, "(null)", 6);
	while(str && str[count])
		count += ft_putchar(str[count]);
	return (count);
}

static size_t	ft_put_unbr(unsigned nb)
{
	size_t	count;
	char	num;

	count = 0;
	if(nb > 9)
		count += ft_put_unbr(nb/10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}

static size_t	ft_putnbr(int nb)
{
	size_t	count;

	count = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb *= -1;
	}
	if (nb > 9)
		count += ft_putnbr(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return(count);
}

int	ft_printf(const char *str, ...)
{
	size_t	count;
	va_list	ap;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			str += 1;
			if ((*str == 'd') || (*str == 'i'))
				count += ft_putnbr(va_arg(ap, int));
			else if (*str == 'c')
				count += ft_putchar((char)va_arg(ap, int));
			else if (*str == 's')
				count += ft_putstr(va_arg(ap, char *));
			else if (*str == '%')
				count += ft_putchar('%');
			else if (*str == 'u')
				count += ft_put_unbr(va_arg(ap, unsigned int));
	//		else if (*str == 'p')
	//			count += 
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(ap);
	return (count);
}

#include <stdio.h>
int	main(void)
{
	char	str[] = "printed";
	char	c = 'l';
	printf("%d\n", ft_printf("Was %c %s? %d or %u\n", 'I', str, 1234, -4321));
	printf("%d\n", printf("Was %c %s? %d or %u\n", 'I', str, 1234, -4321));
}
