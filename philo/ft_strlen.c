int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	if (str == 0)
		return (-1);
	while (str[len])
		len++;
	return (len);
}
