#include "helf.h"

/**
 * get_sym_type - gets the STT type
 * @elf_header: the internal header
 * @i: index of the current symbol struct
 * Return: string type
 */
char *get_sym_type(elf_t *elf_header, size_t i)
{
	switch (YGET(i, st_info) & 0xf)
	{
		case STT_NOTYPE: return ("NOTYPE");
		case STT_OBJECT: return ("OBJECT");
		case STT_FUNC: return ("FUNC");
		case STT_SECTION: return ("SECTION");
		case STT_FILE: return ("FILE");
		case STT_COMMON: return ("COMMON");
		case STT_TLS: return ("TLS");
		case STT_NUM: return ("NUM");
		case STT_LOOS: return ("LOOS");
		case STT_HIOS: return ("HIOS");
		case STT_LOPROC: return ("LOPROC");
		case STT_HIPROC: return ("HIPROC");
		default: return ("UNKNOWN");
	}
}

/**
 * get_sym_bind - gets the STB type
 * @elf_header: the internal header
 * @i: index of the current symbol struct
 * Return: string bind type
 */
char *get_sym_bind(elf_t *elf_header, size_t i)
{
	switch (YGET(i, st_info) >> 4)
	{
		case STB_LOCAL: return ("LOCAL");
		case STB_GLOBAL: return ("GLOBAL");
		case STB_WEAK: return ("WEAK");
		case STB_NUM: return ("NUM");
		case STB_LOOS: return ("LOOS");
		case STB_HIOS: return ("HIOS");
		case STB_LOPROC: return ("LOPROC");
		case STB_HIPROC: return ("HIPROC");
		default: return ("UNKNWN");
	}
}


/**
 * print_section_to_segment_mapping - self-documenting
 * @elf_header: the internal header
 * @string_table: the string table
 * Return: 0 on success else error
 */
int print_section_to_segment_mapping(elf_t *elf_header, char *string_table)
{
	size_t i, j;

	printf(MAPPING_TITLE);
	for (i = 0; i < EGET(e_phnum); i++)
	{
		printf("   %2.2lu     ", i);
		for (j = 0; j < EGET(e_shnum); j++)
		{
			if (IS_32(elf_header->e64))
			{
				if (ELF_IS_SECTION_IN_SEGMENT_MEMORY((&elf_header->s32[j]),
					(&elf_header->p32[i])))
					printf("%s ", string_table + SGET(j, sh_name));
			}
			else
			{
				if (ELF_IS_SECTION_IN_SEGMENT_MEMORY((&elf_header->s64[j]),
					(&elf_header->p64[i])))
					printf("%s ", string_table + SGET(j, sh_name));
			}
		}
		printf("\n");
	}
	return (0);
}


size_t find_verneed_index(Elf64_Verneed *verneed, size_t verneed_size,
	size_t index)
{
	size_t i = 0, ret = 0;

	for (i = 1; i < verneed_size; i++)
	{
		if (verneed[i].vn_file >= verneed_size)
			return (0);
		if (verneed[i].vn_file == index)
			ret = i;
	}
	return (ret);
}

/**
 * print_verneed_info - prints the symbol version info
 * @elf_header: address of elf header struct
 * @sym_string_table: the symbol string table
 * @versym: the Elf64_Versym section array
 * @verneed: the Elf64_Verneed section array
 * @verneed_size: the size of the verneed array
 * @i: section index of current symbol table
 * @size: size of the symbol table
 * @section: the symbol section to print
 */
void print_verneed_info(elf_t *elf_header, char *sym_string_table,
	uint16_t *versym, Elf64_Verneed *verneed, size_t verneed_size, size_t i,
	size_t size, int section)
{
	if (verneed && versym[i] >= 2)
	{
		int save_versym = versym[i];
		size_t index;

		if (size == 2007)
		{
			if (versym[i] == 8)
				versym[i] = 5;
			else if (versym[i] == 9)
				versym[i] = 6;
			else if (versym[i] == 11)
				versym[i] = 7;
			else if (versym[i] >= 5)
				versym[i] = 2;
		}
		index = find_verneed_index(verneed, verneed_size, (size_t)versym[i]);
		if (!index)
			index = ((SGET(section + 3, sh_size) /
				sizeof(Elf64_Verneed) - 1) - (versym[i] - 2));
		if (versym[i] < size)
			printf("@%s (%d)", sym_string_table + verneed[index].vn_aux, save_versym);
	}
}
