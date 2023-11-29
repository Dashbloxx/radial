#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void done()
{
	printf("\e[?1049l");
}

int main()
{
	printf("\e[?1049h");
	printf("\e[1;1H\e[2J");
	atexit(done);

	/*
	 *	Print the logo, uses color, this color may not be supported on all UNIX-like
	 *	terminals.
	 */
	printf(	"\x1b[38;5;124m8888888b.                888 d8b          888 \r\n"
			"\x1b[38;5;125m888   Y88b               888 Y8P          888 \r\n"
			"\x1b[38;5;126m888    888               888              888 \r\n"
			"\x1b[38;5;127m888   d88P  8888b.   .d88888 888  8888b.  888 \r\n"
			"\x1b[38;5;128m8888888P\"      \"88b d88\" 888 888     \"88b 888 \r\n"
			"\x1b[38;5;129m888 T88b   .d888888 888  888 888 .d888888 888 \r\n"
			"\x1b[38;5;128m888  T88b  888  888 Y88b 888 888 888  888 888 \r\n"
			"\x1b[38;5;127m888   T88b \"Y888888  \"Y88888 888 \"Y888888 888 \r\n");

	printf("Copyright (C) 2023 Reapiu (Dashbloxx), All rights Reserved.\r\nRadial is a small Discord multitool written in C.");

	getchar();

	return 0;
}