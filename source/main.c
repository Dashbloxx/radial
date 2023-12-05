#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#include "string.h"
#include "discord.h"

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

	printf("Copyright (C) 2023 Reapiu (Dashbloxx), All rights Reserved.\r\nRadial is a small Discord multitool written in C, for UNIX-like systems.\r\n");

	while(true)
	{
		char command[1024];
		printf("\x1b[31;1m>>> \x1b[0m");
		fgets(command, sizeof(command), stdin);

		size_t length = strlen(command);
		if(length > 0 && command[length - 1] == '\n')
		{
			command[length - 1] = '\0';
		}

		if(strcmp(command, "exit") == 0)
		{
			return 0;
		}
		else if(strlen(command) < 1) { }
		else if(strcmp(command, "generate-fingerprint") == 0)
		{
			string_t fingerprint;
			fingerprint.size = 1024;
			fingerprint.memory = malloc(fingerprint.size);
			int return_value = experiments(&fingerprint);
			if(return_value != 0)
			{
				fprintf(stderr, "\x1b[31;4mFailed to obtain a fingerprint!\x1b[0m\r\n");
				continue;
			}

			printf("Here's a generated fingerprint from Discord's backend: `%s`!\r\n", fingerprint.memory);
			free(fingerprint.memory);
		}
		else
		{
			fprintf(stderr, "\x1b[31;4mUnknown command!\x1b[0m\r\n");
		}
	}

	getchar();

	return 0;
}