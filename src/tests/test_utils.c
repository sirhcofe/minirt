#include "minirt.h"

void	test_atod(void)
{
	char	*arr[] = {"1205.", ".203", "12.45098", "0.0000006", "100000.00007", "-0.005", "-123.45", "-400.00005"};
	double	x;
	double	y;

	// printf("Here : %f\n", ft_atod(arr[0]));
	for (int i = 0 ; i < 8; i++)
	{
		x = ft_atod(arr[i]);
		y = atof(arr[i]);
		if (x != y)
		{
			printf("Problem at number %s\n", arr[i]);
			printf("Your ft_atod  : %f\n", x);
			printf("System's atof : %f\n", y);
		}
		else
			printf("Good for number %s\n", arr[i]);
	}
	return ;
}

void	test_arrlen(void)
{
	char	**arr = ft_split("A pirates life until we're done", ' ');

	if (ft_arrlen(arr) != 6)
		printf("Error!\n");
	else
		printf("Okay!\n");
	free_split(arr);
	system("leaks test");
}

void	test_isdouble(void)
{
	char	*correct[] = {"1205.3", "12.45098", "0.0000006", "100000.00007", "-0.005", "-123.45", "-400.00005"};
	char	*errors[] = {"12.", ".345", "--205.6", "20.0.0", ". 234", "123..6", "qwe123.5qwe"};

	for (int i = 0 ; i < 7; i++)
	{
		if (ft_isdouble(correct[i]) == 1)
			printf("Okay for %s\n", correct[i]);
		else
			printf("Problem for %s\n", correct[i]);
	}
	for (int i = 0 ; i < 7; i++)
	{
		if (ft_isdouble(errors[i]) == 0)
			printf("Okay for %s\n", errors[i]);
		else
			printf("Problem for %s\n", errors[i]);
	}
	return ;
}

void	test_isrgb(void)
{
	char	*correct[] = {"0,0,0", "20,20,20", "255,255,255", "10,1,200", "0,0,90", "1,20,109", "100,30,1"};
	char	*errors[] = {"0", "0,0", "1.0.0", "we,t,w", ", , ,", "-8,9,0", "100,100,200w"};

	for (int i = 0 ; i < 7; i++)
	{
		if (ft_isrgb(correct[i]) == 1)
			printf("Okay for %s\n", correct[i]);
		else
			printf("Problem for %s\n", errors[i]);
	}
	for (int i = 0 ; i < 7; i++)
	{
		if (ft_isrgb(errors[i]) == 0)
			printf("Okay for %s\n", errors[i]);
		else
			printf("Problem for %s\n", errors[i]);
	}
	return ;
}