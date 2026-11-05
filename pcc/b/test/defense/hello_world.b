main()
{
	extrn syscall;
	syscall(4, 1, "hello, world\n", 13);
}
