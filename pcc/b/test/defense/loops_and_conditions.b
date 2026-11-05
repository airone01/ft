main()
{
	auto i, c, c2;
	extrn syscall;

	i = 0;
	c = 'a';

	while (i < 10)
	{
		if (i % 2)
			syscall(4, 1, &c, 1);
		else
		{
			c2 = c - 32;
			syscall(4, 1, &c2, 1);
		}
		i++;
		++c;
	}
}
