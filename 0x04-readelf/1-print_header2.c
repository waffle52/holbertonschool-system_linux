#include "helf.h"


#define TITLE_SECTION_32 \
	"  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n"
#define FORMAT_SECTION_32 \
	"  [%2u] %-17s %-15.15s %8.8lx %6.6lx %6.6lx %2.2lx %3s %2u %3u %2lu\n"
#define TITLE_SECTION_64 \
	"  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n"
#define FORMAT_SECTION_64 \
	"  [%2u] %-17s %-15.15s %16.16lx %6.6lx %6.6lx %2.2lx %3s %2u %3u %2lu\n"

/**
 * read_section_headers - reads the section headers into data
 * @elf_header: the internal header
 * @fd: file descriptor to read
 */
void read_section_headers(elf_t *elf_header, int fd)
{
	size_t i = EGET(e_shnum), r;
	char *headers;
	size_t read_size = EGET(e_shentsize) * EGET(e_shnum);

	if (!i)
		return;
	headers = calloc(i, read_size * i);
	if (!headers)
		exit(1);
	lseek(fd, EGET(e_shoff), SEEK_SET);
	r = read(fd, headers, read_size);
	if (r < read_size)
		exit(1); /* TODO */
	if (IS_32(elf_header->e64))
		elf_header->s32 = (void *)headers;
	else
		elf_header->s64 = (void *)headers;
}

/**
 * switch_all_endian_section - switches all endians if need be
 * @h: address of our internal struct
 * @i: index of this section
 */
void switch_all_endian_section(elf_t *h, size_t i)
{
	if (IS_BE(h->e64) && !IS_32(h->e64))
	{
		h->s64[i].sh_name = switch_endian4(h->s64[i].sh_name);
		h->s64[i].sh_type = switch_endian4(h->s64[i].sh_type);
		h->s64[i].sh_flags = switch_endian8(h->s64[i].sh_flags);
		h->s64[i].sh_addr = switch_endian8(h->s64[i].sh_addr);
		h->s64[i].sh_offset = switch_endian8(h->s64[i].sh_offset);
		h->s64[i].sh_size = switch_endian8(h->s64[i].sh_size);
		h->s64[i].sh_link = switch_endian4(h->s64[i].sh_link);
		h->s64[i].sh_info = switch_endian4(h->s64[i].sh_info);
		h->s64[i].sh_addralign = switch_endian8(h->s64[i].sh_addralign);
		h->s64[i].sh_entsize = switch_endian8(h->s64[i].sh_entsize);
	}
	if (IS_BE(h->e64) && IS_32(h->e64))
	{
		h->s32[i].sh_name = switch_endian4(h->s32[i].sh_name);
		h->s32[i].sh_type = switch_endian4(h->s32[i].sh_type);
		h->s32[i].sh_flags = switch_endian4(h->s32[i].sh_flags);
		h->s32[i].sh_addr = switch_endian4(h->s32[i].sh_addr);
		h->s32[i].sh_offset = switch_endian4(h->s32[i].sh_offset);
		h->s32[i].sh_size = switch_endian4(h->s32[i].sh_size);
		h->s32[i].sh_link = switch_endian4(h->s32[i].sh_link);
		h->s32[i].sh_info = switch_endian4(h->s32[i].sh_info);
		h->s32[i].sh_addralign = switch_endian4(h->s32[i].sh_addralign);
		h->s32[i].sh_entsize = switch_endian4(h->s32[i].sh_entsize);
	}
}

/**
 * print_section_headers32 - prints 32 bit section headers
 * @elf_header: address of elf header struct
 * @string_table: the string table section
 */
void print_section_headers32(elf_t *elf_header, char *string_table)
{
	size_t i = 0;

	printf(TITLE_SECTION_32);
	for (i = 0; i < EGET(e_shnum); i++)
		printf(FORMAT_SECTION_32,
			(unsigned int)i,
			string_table + SGET(i, sh_name),
			get_section_type(SGET(i, sh_type)),
			SGET(i, sh_addr),
			SGET(i, sh_offset),
			SGET(i, sh_size),
			SGET(i, sh_entsize),
			get_section_flags(elf_header, i),
		    SGET(i, sh_link),
		    SGET(i, sh_info),
		    SGET(i, sh_addralign));
}

/**
 * switch_endian4 - switches endianness on 4 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned int switch_endian4(unsigned int n)
{
	return (((n >> 24) & 0x000000ff) |
			((n >> 8)  & 0x0000ff00) |
			((n << 8)  & 0x00ff0000) |
			((n << 24) & 0xff000000));
}

/**
 * switch_endian8 - switches endianness on 8 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned long switch_endian8(unsigned long n)
{
	return (((n >> 56) & 0x00000000000000ff) |
			((n >> 40) & 0x000000000000ff00) |
			((n >> 24) & 0x0000000000ff0000) |
			((n >> 8)  & 0x00000000ff000000) |
			((n << 8)  & 0x000000ff00000000) |
			((n << 24) & 0x0000ff0000000000) |
			((n << 40) & 0x00ff000000000000) |
			((n << 56) & 0xff00000000000000));
}
