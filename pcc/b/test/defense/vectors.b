putchar(c)
{
	extrn syscall;
	syscall(4, 1, &c, 1);
}

char(s, n)
{
	return ((s[n / 4] >> (((n - 4) % 4) * 8)) & 255);
}

mmaparg [6] 0, 0, 3, 34, 4294967295, 0;
alloc(n)
{
	extrn syscall, printn;
	auto ret;
	ret = 0;
	mmaparg[1] = (n + 1) * 4;
	ret = syscall(90, mmaparg);
	ret[0] = n;
	ret =+ 4;
	return (ret);
}

free(p)
{
	extrn syscall;
	syscall(91, p - 4, p[-1]);
}

putstr(s)
{
	auto i;
	i = 0;
	while (char(s, i))
	{
		putchar(char(s, i));
		i++;
	}
}

printn(n,b)
{
	extrn putchar;
	auto a;
	a = n / b;
	if(a)
		printn(a,b);
	putchar(n % b + '0');
}

printArray(Array)
{
	extrn print;
	auto i, size, data;

	i = 0;
	size = Array[0];
	data = Array[1];

	putstr("[ ");
	while (i < size)
	{
		if (i != 0)
			putstr(", ");
		print(data[i]);
		i++;
	}
	putstr(" ]");
}

INT 0;
ARRAY 1;
STRING 2;
FUNCTION 3;

print(thing)
{
	auto type, data;

	type = thing[0];
	data = thing[1];
	if (type == INT)
		printn(data, 10);
	else if (type == ARRAY)
		printArray(data);
	else if (type == STRING)
		putstr(data);
	else if (type == FUNCTION)
		print(data());
	else
		putstr("unknown object\n");
}

makething(type, value)
{
	extrn alloc;
	auto p;

	p = alloc(4);
	p[0] = type;
	p[1] = value;
	return (p);
}

Array(size, data /*...*/)
{
	auto i, ret;
	i = 0;

	ret = alloc(20);
	ret[0] = size;
	ret[1] = alloc(size);
	while (i < size)
	{
		(ret[1])[i] = (&data)[i];
		i++;
	}
	return (makething(ARRAY, ret));
}

Int(val)
{
	return (makething(INT, val));
}

Str(s)
{
	return (makething(STRING, s));
}

Fun(f)
{
	return (makething(FUNCTION, f));
}

currentval 0;

getsomething()
{
	return (Int(currentval++));
}

main()
{
	auto v;
	print(Int(42));
	putchar('\n');
	print(Array(4, Int(1), Int(2), Int(3), Int(4)));
	putchar('\n');
	print(Str("bonjour"));
	putchar('\n');
	print(Fun(getsomething));
	putchar('\n');
	print(Fun(getsomething));
	putchar('\n');
	print(Fun(getsomething));
	putchar('\n');

	putchar('\n');
	currentval = 0;

	print(Array(6,
	Int(42),
	Array(4, Int(1), Int(2), Int(3), Int(4)),
	Str("bonjour"),
	Fun(getsomething),
	Fun(getsomething),
	Fun(getsomething)
	));
}

/* expected output:

42
[ 1, 2, 3, 4 ]
bonjour
0
1
2

[ 42, [ 1, 2, 3, 4 ], bonjour, 0, 1, 2 ]

*/