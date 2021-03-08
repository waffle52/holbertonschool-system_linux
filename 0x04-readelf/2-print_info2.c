#include "helf.h"

/**
 * read_symbol_string_table - reads the string table
 * @elf_header: the internal header
 * @fd: file descriptor to read
 * @i: the current symbol section to print
 * Return: pointer to beginning of table
 */
char *read_symbol_string_table(elf_t *elf_header, int fd, int i)
{
	char *str;

	str = calloc(1, SGET(i, sh_size));
	if (!str)
		exit(1);

	lseek(fd, SGET(i, sh_offset), SEEK_SET);
	read(fd, str, SGET(i, sh_size));
	return (str);
}

/**
 * read_data - reads a block of data from descriptor
 * @elf_header: the internal header
 * @fd: the descriptor to read
 * @offset: offset to start at
 * @size: number of bytes to read
 * Return: pointer to the data
 */
void *read_data(elf_t *elf_header, int fd, unsigned long offset, long size)
{
	void *str = NULL;

	str = calloc(1, size);
	if (!str)
		exit(1);
	/* printf("Reading [%lu] bytes at offset [%lu]\n", size, offset); */
	lseek(fd, offset, SEEK_SET);
	if (read(fd, str, size) < size)
	{
		fprintf(stderr, "Read error.\n");
		exit(1);
	}
	return (str);
	(void)elf_header;
}

/**
 * read_program_headers - reads the program headers into data
 * @elf_header: the internal header
 * @fd: file descriptor to read
 */
void read_program_headers(elf_t *elf_header, int fd)
{
	size_t i = EGET(e_phnum), r;
	char *headers;
	size_t read_size = EGET(e_phentsize) * EGET(e_phnum);

	if (!i)
		return;
	headers = calloc(i, read_size * i);
	if (!headers)
		exit(1);
	lseek(fd, EGET(e_phoff), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
		exit(1); /* TODO */
	if (IS_32(elf_header->e64))
		elf_header->p32 = (void *)headers;
	else
		elf_header->p64 = (void *)headers;
}


/**
 * print_program_headers64 - prints 64 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @fd: file descriptor of ELF file
 */
void print_program_headers64(elf_t *elf_header, char *string_table, int fd)
{
	size_t i = 0;

	printf(TITLE_PROGRAM_64);
	for (i = 0; i < EGET(e_phnum); i++)
	{
		printf(FORMAT_PROGRAM_64,
			get_segment_type(PGET(i, p_type)),
			PGET(i, p_offset),
			PGET(i, p_vaddr),
			PGET(i, p_paddr),
			PGET(i, p_filesz),
			PGET(i, p_memsz),
			PGET(i, p_flags) & PF_R ? 'R' : ' ',
			PGET(i, p_flags) & PF_W ? 'W' : ' ',
			PGET(i, p_flags) & PF_X ? 'E' : ' ',
			PGET(i, p_align));
		switch (PGET(i, p_type))
		{
			case PT_INTERP:
			{
				char fmt[32], prog[PATH_MAX];
				FILE *file = fdopen(fd, "r");

				snprintf(fmt, sizeof(fmt), "%%%ds", PATH_MAX);
				lseek(fd, PGET(i, p_offset), SEEK_SET);
				if (fscanf(file, fmt, prog) > 0)
					printf("      [Requesting program interpreter: %s]\n", prog);
				fclose(file);
			}
		}
	}
	(void)string_table;
}


/**
 * print_program_headers32 - prints 32 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @fd: file descriptor of ELF file
 */
void print_program_headers32(elf_t *elf_header, char *string_table, int fd)
{
	size_t i = 0;

	printf(TITLE_PROGRAM_32);
	for (i = 0; i < EGET(e_phnum); i++)
	{
		printf(FORMAT_PROGRAM_32,
			get_segment_type(PGET(i, p_type)),
			PGET(i, p_offset),
			PGET(i, p_vaddr),
			PGET(i, p_paddr),
			PGET(i, p_filesz),
			PGET(i, p_memsz),
			PGET(i, p_flags) & PF_R ? 'R' : ' ',
			PGET(i, p_flags) & PF_W ? 'W' : ' ',
			PGET(i, p_flags) & PF_X ? 'E' : ' ',
			PGET(i, p_align));
		switch (PGET(i, p_type))
		{
			case PT_INTERP:
			{
				char fmt[32], prog[PATH_MAX];
				FILE *file = fdopen(fd, "r");

				snprintf(fmt, sizeof(fmt), "%%%ds", PATH_MAX);
				lseek(fd, PGET(i, p_offset), SEEK_SET);
				if (fscanf(file, fmt, prog) > 0)
					printf("      [Requesting program interpreter: %s]\n", prog);
				fclose(file);
			}
		}
	}
	(void)string_table;
}
