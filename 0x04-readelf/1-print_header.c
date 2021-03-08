#include "helf.h"

#define FORMAT_LEGEND \
	"Key to Flags:\n" \
	"  W (write), A (alloc), X (execute), M (merge), S (strings)%s\n" \
	"  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n" \
	"  O (extra OS processing required) o (OS specific), p (processor specific)\n"

/**
 * print_section_headers_full - prints all the ELF section headers
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * Return: 0 on success else exit_status
 */
int print_section_headers_full(elf_t *elf_header, int fd)
{
	char *string_table;
	size_t i;

	if (!EGET(e_shnum))
	{
		printf("\nThere are no sections in this file.\n");
		return (1);
	}
	printf("There are %d section headers, starting at offset 0x%lx:\n",
		EGET(e_shnum), EGET(e_shoff));
	read_section_headers(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
		switch_all_endian_section(elf_header, i);
	string_table = read_string_table(elf_header, fd);
	printf("\nSection Headers:\n");
	if (IS_32(elf_header->e64))
		print_section_headers32(elf_header, string_table);
	else
		print_section_headers64(elf_header, string_table);
	printf(FORMAT_LEGEND, IS_32(elf_header->e64) ? "" : ", l (large)");
	free(string_table);
	return (0);
}

/**
 * switch_all_endian - switches all endians if need be
 * @h: address of our internal struct
 */
void switch_all_endian(elf_t *h)
{
	if (IS_BE(h->e64))
	{
		h->e64.e_machine = switch_endian2(h->e64.e_machine);
		h->e64.e_version = switch_endian4(h->e64.e_version);
		h->e64.e_type = switch_endian2(h->e64.e_type);
		h->e64.e_flags = switch_endian4(h->e64.e_flags);
		h->e64.e_ehsize = switch_endian2(h->e64.e_ehsize);
		h->e64.e_phentsize = switch_endian2(h->e64.e_phentsize);
		h->e64.e_phnum = switch_endian2(h->e64.e_phnum);
		h->e64.e_shentsize = switch_endian2(h->e64.e_shentsize);
		h->e64.e_shnum = switch_endian2(h->e64.e_shnum);
		h->e64.e_shoff = switch_endian8(h->e64.e_shoff);
		h->e64.e_phoff = switch_endian8(h->e64.e_phoff);
		h->e64.e_entry = switch_endian8(h->e64.e_entry);
		h->e64.e_shstrndx = switch_endian2(h->e64.e_shstrndx);
	}
	if (IS_BE(h->e64) && IS_32(h->e64))
	{
		h->e32.e_machine = switch_endian2(h->e32.e_machine);
		h->e32.e_version = switch_endian4(h->e32.e_version);
		h->e32.e_type = switch_endian2(h->e32.e_type);
		h->e32.e_flags = switch_endian4(h->e32.e_flags);
		h->e32.e_ehsize = switch_endian2(h->e32.e_ehsize);
		h->e32.e_phentsize = switch_endian2(h->e32.e_phentsize);
		h->e32.e_phnum = switch_endian2(h->e32.e_phnum);
		h->e32.e_shentsize = switch_endian2(h->e32.e_shentsize);
		h->e32.e_shnum = switch_endian2(h->e32.e_shnum);
		h->e32.e_shoff = switch_endian4(h->e32.e_shoff);
		h->e32.e_phoff = switch_endian4(h->e32.e_phoff);
		h->e32.e_entry = switch_endian4(h->e32.e_entry);
		h->e32.e_shstrndx = switch_endian2(h->e32.e_shstrndx);
	}
}

/**
 * open_file - opens a file descriptor, exits on failure
 * @name: name of file to open
 * @silent: if true don't print errors
 * Return: fd of file
 */
int open_file(char *name, int silent)
{
	int fd;

	fd = open(name, O_RDONLY);
	if (fd == -1 && !silent)
	{
		if (errno == EACCES)
			fprintf(stderr, ERR_NO_ACCESS, name);
		else if (errno == ENOENT)
			fprintf(stderr, ERR_NO_ENTRY, name);
	}
	return (fd);
}


/**
 * check_elf - checks if header matches magic bytes
 * @elf_header: 16 byte buffer holding elf header
 * Return: 0 if ELF else 1
 */
int check_elf(char *elf_header)
{
	if (elf_header[0] == 0x7f && elf_header[1] == 0x45 &&
		elf_header[2] == 0x4c && elf_header[3] == 0x46)
		return (0);
	return (1);
}

/**
 * read_string_table - reads the string table
 * @elf_header: the internal header
 * @fd: file descriptor to read
 * Return: pointer to beginning of table
 */
char *read_string_table(elf_t *elf_header, int fd)
{
	char *str;

	str = calloc(1, SGET(EGET(e_shstrndx), sh_size));
	if (!str)
		exit(1);

	lseek(fd, SGET(EGET(e_shstrndx), sh_offset), SEEK_SET);
	read(fd, str, SGET(EGET(e_shstrndx), sh_size));
	return (str);
}
