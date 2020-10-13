/*
 * Copyright (c) 2020 RIPE NCC <atlas@ripe.net>
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */

#include "libbb.h"

void read_response(int fd, int type, size_t *sizep, void *data)
{
	int tmp_type;
	size_t tmp_size;

	if (read(fd, &tmp_type, sizeof(tmp_type)) != sizeof(tmp_type))
	{
		fprintf(stderr, "read_response: error reading\n");
		exit(1);
	}
	if (tmp_type != type)
	{
		fprintf(stderr,
			 "read_response: wrong type, expected %d, got %d\n",
			type, tmp_type);
		exit(1);
	}
	if (read(fd, &tmp_size, sizeof(tmp_size)) != sizeof(tmp_size))
	{
		fprintf(stderr, "read_response: error reading\n");
		exit(1);
	}
	if (tmp_size > *sizep)
	{
		fprintf(stderr, "read_response: data bigger than buffer\n");
		exit(1);
	}
	*sizep= tmp_size;
	if (read(fd, data, tmp_size) != tmp_size)
	{
		fprintf(stderr, "read_response: error reading\n");
		exit(1);
	}
}


void read_response_file(FILE *file, int type, size_t *sizep, void *data)
{
	int tmp_type;
	size_t tmp_size;

	if (fread(&tmp_type, sizeof(tmp_type), 1, file) != 1)
	{
		fprintf(stderr, "read_response_file: error reading\n");
		exit(1);
	}
	if (tmp_type != type)
	{
		fprintf(stderr,
		 "read_response_file: wrong type, expected %d, got %d\n",
			type, tmp_type);
		exit(1);
	}
	if (fread(&tmp_size, sizeof(tmp_size), 1, file) != 1)
	{
		fprintf(stderr, "read_response_file: error reading\n");
		exit(1);
	}
	if (tmp_size > *sizep)
	{
		fprintf(stderr,
			"read_response_file: data bigger than buffer\n");
		exit(1);
	}
	*sizep= tmp_size;
	if (fread(data, tmp_size, 1, file) != 1)
	{
		fprintf(stderr, "read_response_file: error reading\n");
		exit(1);
	}
}

