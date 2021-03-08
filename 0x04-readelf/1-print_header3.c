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
 * get_section_type - return string type of section
 * @sh_type: the section type
 * Return: string name of type
*/
char *get_section_type(unsigned int sh_type)
{
	static char buf[32];

	switch (sh_type)
	{
	case SHT_NULL:		return ("NULL");
	case SHT_PROGBITS:		return ("PROGBITS");
	case SHT_SYMTAB:		return ("SYMTAB");
	case SHT_STRTAB:		return ("STRTAB");
	case SHT_RELA:		return ("RELA");
	case SHT_HASH:		return ("HASH");
	case SHT_DYNAMIC:		return ("DYNAMIC");
	case SHT_NOTE:		return ("NOTE");
	case SHT_NOBITS:		return ("NOBITS");
	case SHT_REL:		return ("REL");
	case SHT_SHLIB:		return ("SHLIB");
	case SHT_DYNSYM:		return ("DYNSYM");
	case SHT_INIT_ARRAY:	return ("INIT_ARRAY");
	case SHT_FINI_ARRAY:	return ("FINI_ARRAY");
	case SHT_PREINIT_ARRAY:	return ("PREINIT_ARRAY");
	case SHT_GNU_HASH:		return ("GNU_HASH");
	case SHT_GROUP:		return ("GROUP");
	case SHT_SYMTAB_SHNDX:	return ("SYMTAB SECTION INDICIES");
	case SHT_GNU_verdef:	return ("VERDEF");
	case SHT_GNU_verneed:	return ("VERNEED");
	case SHT_GNU_versym:	return ("VERSYM");
	case 0x6ffffff0:		return ("VERSYM");
	case 0x6ffffffc:		return ("VERDEF");
	case 0x7ffffffd:		return ("AUXILIARY");
	case 0x7fffffff:		return ("FILTER");
	case 0x6ffffff1:		return ("LOOS+ffffff1");
	case 0x6ffffff3:		return ("LOOS+ffffff3");
	case SHT_GNU_LIBLIST:	return ("GNU_LIBLIST");
	default:
		sprintf(buf, "%08x: <unknown>", sh_type);
		return (buf);
	}
}

/**
 * get_section_flags - translates section flags to string
 * @elf_header: address of elf header struct
 * @i: the section index
 * Return: legend-based string rep of flag
 */
char *get_section_flags(elf_t *elf_header, size_t i)
{
	static char buf[32];
	unsigned long flags = SGET(i, sh_flags);
	char *p = buf;

	if (flags & SHF_WRITE)
		*p++ = 'W';
	if (flags & SHF_ALLOC)
		*p++ = 'A';
	if (flags & SHF_EXECINSTR)
		*p++ = 'X';
	if (flags & SHF_MERGE)
		*p++ = 'M';
	if (flags & SHF_STRINGS)
		*p++ = 'S';
	if (flags & SHF_INFO_LINK)
		*p++ = 'I';
	if (flags & SHF_LINK_ORDER)
		*p++ = 'L';
	if (flags & SHF_OS_NONCONFORMING)
		*p++ = 'O';
	if (flags & SHF_GROUP)
		*p++ = 'G';
	if (flags & SHF_TLS)
		*p++ = 'T';
	if (flags & SHF_EXCLUDE)
		*p++ = 'E';
	*p = 0;
	return (buf);
}

/**
 * switch_endian2 - switches endianness on 2 byte unsigned int
 * @n: the unsigned int whose bytes to switch
 * Return: unsigned int with switched bytes
 */
unsigned short switch_endian2(unsigned short n)
{
	return (((n >> 8)  & 0x00ff) |
			((n << 8)  & 0xff00));
}

/**
 * print_section_headers64 - prints 64 bit section headers
 * @elf_header: address of elf header struct
 * @string_table: the string table section
 */
void print_section_headers64(elf_t *elf_header, char *string_table)
{
	size_t i = 0;

	printf(TITLE_SECTION_64);
	for (i = 0; i < EGET(e_shnum); i++)
		printf(FORMAT_SECTION_64,
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
 * print_all_symbol_tables - prints all the symbol table stuff
 * @elf_header: address of elf header struct
 * @fd: the file descriptor of our ELF file
 * Return: 0 on success else exit_status
 */
int print_all_symbol_tables(elf_t *elf_header, int fd)
{
	char *string_table = NULL;
	size_t i;

	if (!EGET(e_shnum))
	{
		printf("\nThere are no section headers in this file.\n");
		return (0);
	}
	read_section_headers(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
		switch_all_endian_section(elf_header, i);
	string_table = read_string_table(elf_header, fd);
	for (i = 0; i < EGET(e_shnum); i++)
	{
		if (SGET(i, sh_type) == SHT_DYNSYM ||
			SGET(i, sh_type) == SHT_SYMTAB)
		{
			print_symbol_table(elf_header, fd, i, string_table);
		}
	}
	free(string_table);
	return (0);
}
