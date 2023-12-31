#include "lib.h"

void	ft_putnbr_aux(int n)
{
	int		r;
	int		q;
	char	c;

	q = n / 10;
	r = n % 10;
	if (q > 0)
		ft_putnbr_aux(q);
	c = (char)(r + 48);
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (-2147483648 == nb)
		write(1, "-2147483648", 11);
	else
	{
		if (nb < 0)
		{
			write(1, "-", 1);
			nb *= -1;
		}
		ft_putnbr_aux(nb);
	}
}

size_t	ft_strlen(char *str)
{
	char	*save;

	save = str;
	while (str != NULL && *str != '\0')
		str++;
	return (str - save);
}

// ft_power takes:
// a signed integer base - [b]
// an unsigned exponent - [e]
//
// returns the result of exponentiation of b to the e as a signed integer
//
// doesn't handle overflow
int	ft_power(int b, unsigned int e)
{
	if (e == 0)
		return (1);
	else
		return (b * (ft_power(b, e - 1)));
}

unsigned int	factorial(unsigned int n)
{
	if (n == 1)
		return (n);
	else
		return (n * factorial(n - 1));
}

void	swap_int(int *ptr1, int *ptr2)
{
	int	temp;

	temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

int	*rev_int_arr(int *arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		swap_int(arr + i, arr + size - 1);
		size--;
		i++;
	}
	return (arr);
}

// permute takes:
// a pointer to the previous permutation - [prev]
// a pointer to store of the next permutation - [next]
// the size of the sequence to of permutation - [size]
//
// returns a pointer to the start of [next]
//
// assumes proper malloc of prev and next
int	*permute(int *prev, int *next, size_t size)
{
	int		*save_lower;
	int		*save_upper;
	size_t	k;

	save_lower = NULL;
	save_upper = NULL;
	k = 0;
	if (size == 0)
		return (NULL);
	while (size - k)
	{
		if (((size - 1) - k) && *(prev + k) < *(prev + k + 1))
		{
			save_lower = prev + k;
			save_upper = prev + k + 1;
		}
		else if (save_lower != NULL && *save_lower < *(prev + k))
			save_upper = prev + k;
		*(next + k) = *(prev + k);
		k++;
	}
	if (save_lower != NULL)
	{
		*(next + (save_lower - prev)) = *save_upper;
		*(next + (save_upper - prev)) = *save_lower;
		rev_int_arr(next + (save_lower - prev) + 1, size - (save_lower - prev)
			- 1);
	}
	return (next);
}

// print numbers (char) from int
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

// takes an 1 dimensional array of int as input
// calculates visible boxes for view
//
// return - 1 == error
// return 1, 2, 3,4 == number of visible boxes
int	count_view(const int *ch)
{
	int	i;

	i = 0;
	if (ch[i] == 4)
		return (1);
	if ((ch[i] > ch[i + 1]) && (ch[i] < ch[i + 2]) && ch[i + 2] > ch[i + 3]
		|| ((ch[i] > ch[i + 1]) && (ch[i] > ch[i + 2]) && (ch[i] < ch[i + 3]))
		|| ((ch[i] < ch[i + 1]) && (ch[i + 1] > ch[i + 2]) && (ch[i + 1] > ch[i
				+ 3])))
		return (2);
	if ((ch[i] > ch[i + 1] && ch[i] > ch[i + 2] && ch[i + 2] < ch[i + 3])
		|| (ch[i] < ch[i + 1] && ch[i + 1] > ch[i + 2] && ch[i + 1] < ch[i + 3])
		|| (ch[i] > ch[i + 1] && ch[i + 1] < ch[i + 2] && ch[i + 1] < ch[i + 3])
		|| (ch[i] < ch[i + 1] && ch[i + 1] < ch[i + 2] && ch[i + 2] > ch[i
			+ 3]))
		return (3);
	if (ch[i] < ch[i + 1] && ch[i + 1] < ch[i + 2] && ch[i + 2] < ch[i + 3])
		return (4);
	return (-1);
}

// takes 2d array as input, and output array to transpose to
//
// yield a tranposed array
int	**transpose_matrix(int **matrix, int **matrix_transpose, size_t rows,
		size_t cols)
{
	size_t	j;
	size_t	i;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			matrix_transpose[i][j] = matrix[j][i];
			j++;
		}
		i++;
	}
	return (matrix_transpose);
}

void	print_matrix(int **arr, size_t rows, size_t cols)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < rows)
	{
		i = 0;
		while (i < cols)
		{
			ft_putnbr(arr[j][i]);
			if (i < cols - 1)
				ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
		j++;
	}
}

int	**malloc_matrix_rows(size_t rows)
{
	int	**matrix;

	matrix = (int **)malloc(rows * sizeof(int *));
	if (matrix == NULL)
		return (NULL);
	return (matrix);
}

int	**malloc_matrix(size_t cols, size_t rows)
{
	int		**matrix;
	size_t	i;

	matrix = malloc_matrix_rows(rows);
	if (matrix == NULL)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		matrix[i] = (int *)malloc(cols * sizeof(int));
		if (matrix[i] == NULL)
			return (NULL);
		i++;
	}
	return (matrix);
}

int	**gen_permutations(size_t size)
{
	size_t	cols;
	size_t	rows;
	size_t	i;
	size_t	j;
	int		**matrix;

	cols = size;
	rows = factorial(size);
	matrix = malloc_matrix(cols, rows);
	if (matrix == NULL)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		j = 0;
		if (i == 0)
		{
			while (j < cols)
			{
				matrix[i][j] = j + 1;
				j++;
			}
		}
		else
			permute(matrix[i - 1], matrix[i], cols);
		i++;
	}
	return (matrix);
}

int	**gen_solution(size_t size, int *input)
{
	size_t	permutations;
	int		**solution_matrix;
	int		**permutation_matrix;
	int		**solution_matrix_transpose;
	int		*views;
	int		i;
	int		j;
	int		k;
	int		l;

	views = malloc(ft_power((int)size, 2) * sizeof(int));
	permutation_matrix = gen_permutations(size);
	solution_matrix = malloc_matrix_rows(size);
	solution_matrix_transpose = malloc_matrix(size, size);
	permutations = factorial(size);
	i = 0;
	while (i < permutations)
	{
		solution_matrix[0] = permutation_matrix[i];
		j = 0;
		while (j < permutations)
		{
			solution_matrix[1] = permutation_matrix[j];
			k = 0;
			while (k < permutations)
			{
				solution_matrix[2] = permutation_matrix[k];
				l = 0;
				while (l < permutations)
				{
					solution_matrix[3] = permutation_matrix[l];
					transpose_matrix(solution_matrix, solution_matrix_transpose,
						size, size);
					if ((sudoku(solution_matrix, size)
							&& (sudoku(solution_matrix_transpose, size))))
					{
						count_rows(solution_matrix, views, size);
						if (checker(input, views, ft_power((int)size, 2)) == 0)
							return (solution_matrix);
					}
					l++;
				}
				k++;
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	puterr(char *error_detail)
{
	char	*errormsg;

	if (error_detail != NULL)
	{
		errormsg = "error:\n";
		write(2, errormsg, ft_strlen(errormsg));
		write(2, error_detail, ft_strlen(error_detail));
	}
	else
	{
		errormsg = "error\n";
		write(2, errormsg, ft_strlen(errormsg));
	}
}

int	*parse_uinput(char *str, unsigned int n)
{
	size_t	format_length;
	size_t	i;
	int		*uinput;

	uinput = malloc(ft_power(n, 2) * sizeof(int));
	format_length = ft_power(n, 2) + (ft_power(n, 2) - 1);
	i = 0;
	if (ft_strlen(str) != format_length)
	{
		free(uinput);
		return (NULL);
	}
	while (i < format_length)
	{
		if ((i % 2 == 0) && ('0' < str[i]) && (str[i] <= n + 48))
		{
			uinput[i / 2] = str[i] - 48;
		}
		else if (!((i % 2 == 1) && (str[i] == ' ')))
		{
			free(uinput);
			return (NULL);
		}
		i++;
	}
	return (uinput);
}

// compare results and user-input
// returns 0 if perfect match
// return != 0 when no match
int	checker(const int *input, const int *result, size_t size)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (count == 0 && i < size)
	{
		count += input[i] - result[i];
		i++;
	}
	return (count);
}

// count nbr of boxes seen from all POV (CU CD RR RL)
// writes results to "results" array in main
void	count_rows(int **matrix, int *dest_arr, size_t size)
{
	int	j;
	int	k;
	int	**matrix_transpose;
	int	**matrix_copy;

	matrix_transpose = malloc_matrix(size, size);
	matrix_copy = malloc_matrix(size, size);
	transpose_matrix(matrix, matrix_transpose, 4, 4);
	transpose_matrix(matrix_transpose, matrix_copy, 4, 4);
	j = 0;
	k = 0;
	while (j < 4)
	{
		dest_arr[k] = count_view(matrix_transpose[j]);
		j++;
		k++;
	}
	j = 0;
	while (j < 4)
	{
		rev_int_arr(matrix_transpose[j], 4);
		dest_arr[k] = count_view(matrix_transpose[j]);
		j++;
		k++;
	}
	j = 0;
	while (j < 4)
	{
		dest_arr[k] = count_view(matrix[j]);
		j++;
		k++;
	}
	j = 0;
	while (j < 4)
	{
		rev_int_arr(matrix_copy[j], 4);
		dest_arr[k] = count_view(matrix_copy[j]);
		j++;
		k++;
	}
}

bool	sudoku(int **matrix, size_t n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < n - 1)
		{
			k = j + 1;
			while (k < n)
			{
				if (matrix[i][j] == matrix[i][k])
					return (false);
				k++;
			}
			j++;
		}
		i++;
	}
	return (true);
}
