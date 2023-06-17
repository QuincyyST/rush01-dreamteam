#include "includes.h"

size_t	ft_strlen(char *str)
{
	char	*save;

	save = str;
	while(str != NULL && *str != '\0')
		str++;
	return (str - save); 
}

void	ft_putstr(char *str)
{
	while(str && *str)
		write(1, (str++), 1);
}

//pow takes:
//a signed integer base - [b]
//an unsigned exponent - [e]
//
//returns the result of exponentiation of b to the e as a signed integer
//
//doesn't handle overflow
int ft_power(int b, unsigned int e)
{
	if (e == 0)
		return 1;
	else
		return b * (ft_power(b, e - 1));
}


//permute takes:
//a pointer to the previous permutation - [prev]
//a pointer to store of the next permutation - [next]
//the size of the sequence to of permutation - [size]
//
//returns a pointer to the start of [next]
//
//assumes proper malloc of prev and next
int	*permute(int *prev, int *next, size_t size)
{
	int* save_lower = NULL;
	int* save_upper = NULL;
	size_t k = 0;

	if (size == 0)
		return NULL;

	while((size - 1) - k)
	{
		if (*(prev + k) < *(prev + k + 1))
		{
			save_lower = prev + k;
			save_upper = prev + k + 1;
		}
		else if (save_lower != NULL && save_lower < prev + k)
			save_upper = prev + k;
		else
			*(next + k) = *(prev + k);
		k++;
	}
	if (save_lower != NULL)
			
	return next;
}
