#include "helf.h"

#define PROGRAM_TITLE \
	"\nElf file type is %s\nEntry point 0x%lx\nThere are %d program headers," \
	" starting at offset %lu\n"

/**
 * print_all_table - prints just one symbol table
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * @i: section index of current symbol table
 * @string_table: the section header string_table
 */
void print_symbol_table(elf_t *elf_header, int fd, size_t i,
	char *string_table)
{
	char *sym_string_table = NULL;
	uint16_t *versym = NULL;
	Elf64_Verneed *verneed = NULL;
	size_t versym_size, verneed_size, size, j;

	size = SGET(i, sh_size) / SGET(i, sh_entsize);
	read_symbol_table(elf_header, fd, i);
	for (j = 0; j < size; j++)
		switch_all_endian_symbol(elf_header, j);
	sym_string_table = read_symbol_string_table(elf_header, fd, i + 1);

	if (SGET(i, sh_type) == SHT_DYNSYM)
	{
		versym = read_data(elf_header, fd, SGET(i + 2, sh_offset),
			SGET(i + 2, sh_size));
		verneed = read_data(elf_header, fd, SGET(i + 3, sh_offset),
			SGET(i + 3, sh_size));
		versym_size = SGET(i + 2, sh_size) / 2;
		verneed_size = SGET(i + 3, sh_size) / sizeof(Elf64_Verneed);
		if (strcmp(string_table + SGET(i + 3, sh_name), ".gnu.version_r"))
			verneed = NULL;
		switch_all_endian_ver(elf_header, versym, versym_size, verneed,
			verneed_size);
	}
	if (IS_64)
	{
		print_symbol_table64(elf_header, string_table, sym_string_table,
			versym, verneed, verneed_size, i);
		elf_header->y64 = (free(elf_header->y64), NULL);
	}
	else
	{
		print_symbol_table32(elf_header, string_table, sym_string_table,
			versym, verneed, verneed_size, i);
		elf_header->y32 = (free(elf_header->y32), NULL);
	}
	sym_string_table = (free(sym_string_table), NULL);
	verneed = (free(verneed), NULL);
	versym = (free(versym), NULL);
}

/**
 * print_program_headers_full - prints all the ELF PROGRAM headers
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * Return: 0 on success else exit_status
 */
int print_program_headers_full(elf_t *elf_header, int fd)
{
	char *string_table;
	size_t i;

	if (!EGET(e_phnum))
	{
		printf("\nThere are no program headers in this file.\n");
		return (0);
	}
	printf(PROGRAM_TITLE, get_type(elf_header), EGET(e_entry),
		EGET(e_phnum), EGET(e_phoff));

	read_section_headers(elf_header, fd);
	read_program_headers(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
		switch_all_endian_section(elf_header, i);
	for (i = 0; i < EGET(e_phnum); i++)
		switch_all_endian_program(elf_header, i);
	string_table = read_string_table(elf_header, fd);
	printf("\nProgram Headers:\n");
	if (IS_32(elf_header->e64))
		print_program_headers32(elf_header, string_table, fd);
	else
		print_program_headers64(elf_header, string_table, fd);
	print_section_to_segment_mapping(elf_header, string_table);
	free(string_table);
	return (0);
}

/**
 * read_symbol_table - reads the symbol headers into data
 * @elf_header: the internal header
 * @fd: file descriptor to read
 * @i: the current symbol section to print
 */
void read_symbol_table(elf_t *elf_header, int fd, int i)
{
	size_t r;
	char *headers;
	size_t read_size = SGET(i, sh_size);

	headers = calloc(1, read_size);
	if (!headers)
		exit(1);
	lseek(fd, SGET(i, sh_offset), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
	{
		fprintf(stderr, "Symbol read failed.\n");
		exit(1); /* TODO */
	}
	if (IS_32(elf_header->e64))
		elf_header->y32 = (void *)headers;
	else
		elf_header->y64 = (void *)headers;
}

/**
 * switch_all_endian_program - switches all endians if need be
 * @h: address of our internal struct
 * @i: index of this section
 */
void switch_all_endian_program(elf_t *h, size_t i)
{
	if (IS_BE(h->e64) && !IS_32(h->e64))
	{
		h->p64[i].p_type = switch_endian4(h->p64[i].p_type);
		h->p64[i].p_offset = switch_endian8(h->p64[i].p_offset);
		h->p64[i].p_vaddr = switch_endian8(h->p64[i].p_vaddr);
		h->p64[i].p_paddr = switch_endian8(h->p64[i].p_paddr);
		h->p64[i].p_filesz = switch_endian8(h->p64[i].p_filesz);
		h->p64[i].p_memsz = switch_endian8(h->p64[i].p_memsz);
		h->p64[i].p_align = switch_endian8(h->p64[i].p_align);
		h->p64[i].p_flags = switch_endian4(h->p64[i].p_flags);
	}
	if (IS_BE(h->e64) && IS_32(h->e64))
	{
		h->p32[i].p_type = switch_endian4(h->p32[i].p_type);
		h->p32[i].p_offset = switch_endian4(h->p32[i].p_offset);
		h->p32[i].p_vaddr = switch_endian4(h->p32[i].p_vaddr);
		h->p32[i].p_paddr = switch_endian4(h->p32[i].p_paddr);
		h->p32[i].p_filesz = switch_endian4(h->p32[i].p_filesz);
		h->p32[i].p_memsz = switch_endian4(h->p32[i].p_memsz);
		h->p32[i].p_align = switch_endian4(h->p32[i].p_align);
		h->p32[i].p_flags = switch_endian4(h->p32[i].p_flags);
	}
}

/**
 * switch_all_endian_symbol - switches all endians if need be
 * @h: address of our internal struct
 * @i: index of this section
 */
void switch_all_endian_symbol(elf_t *h, size_t i)
{
	if (IS_BE(h->e64) && !IS_32(h->e64))
	{
		h->y64[i].st_name = switch_endian4(h->y64[i].st_name);
		h->y64[i].st_shndx = switch_endian2(h->y64[i].st_shndx);
		h->y64[i].st_value = switch_endian8(h->y64[i].st_value);
		h->y64[i].st_size = switch_endian8(h->y64[i].st_size);
	}
	if (IS_BE(h->e64) && IS_32(h->e64))
	{
		h->y32[i].st_name = switch_endian4(h->y32[i].st_name);
		h->y32[i].st_shndx = switch_endian2(h->y32[i].st_shndx);
		h->y32[i].st_value = switch_endian4(h->y32[i].st_value);
		h->y32[i].st_size = switch_endian4(h->y32[i].st_size);
	}
	(void)i;
}
