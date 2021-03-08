#include "helf.h"

/**
 * get_segment_type - get string represenation of segment type
 * @p_type: the p_type of this segment
 * Return: string representation of p_type
 */
char *get_segment_type(unsigned long p_type)
{
	switch (p_type)
	{
	case PT_NULL:	return ("NULL");
	case PT_LOAD:	return ("LOAD");
	case PT_DYNAMIC:	return ("DYNAMIC");
	case PT_INTERP:	return ("INTERP");
	case PT_NOTE:	return ("NOTE");
	case PT_SHLIB:	return ("SHLIB");
	case PT_PHDR:	return ("PHDR");
	case PT_TLS:	return ("TLS");
	case PT_GNU_EH_FRAME:	return ("GNU_EH_FRAME");
	case PT_GNU_STACK:	return ("GNU_STACK");
	case PT_GNU_RELRO:  return ("GNU_RELRO");
	case 0x6464E550:	return ("LOOS+464e550");
	default:	return ("UNKNOWN");
	}
}

void switch_all_endian_ver(elf_t *h, uint16_t *versym, size_t versym_size,
	Elf64_Verneed *verneed, size_t verneed_size)
{
	size_t i = 0;

	if (!IS_BE(h->e64))
		return;

	for (i = 0; i < versym_size; i++)
		versym[i] = switch_endian2(versym[i]);
	for (i = 0; i < verneed_size; i++)
	{
		verneed[i].vn_version = switch_endian2(verneed[i].vn_version);
		verneed[i].vn_cnt = switch_endian2(verneed[i].vn_cnt);
		verneed[i].vn_file = switch_endian4(verneed[i].vn_file);
		verneed[i].vn_aux = switch_endian4(verneed[i].vn_aux);
		verneed[i].vn_next = switch_endian4(verneed[i].vn_next);
	}
	(void)versym;
}

/**
 * print_symbol_table32 - prints 32 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @sym_string_table: the symbol string table
 * @versym: the Elf64_Versym section array
 * @verneed: the Elf64_Verneed section array
 * @verneed_size: the size of the verneed array
 * @section: the symbol section to print
 */
void print_symbol_table32(elf_t *elf_header, char *string_table,
	char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed,
	size_t verneed_size, int section)
{
	size_t i = 0;
	size_t size = SGET(section, sh_size) / SGET(section, sh_entsize);

	printf(TITLE_SYMBOL_32, string_table + SGET(section, sh_name), size);
	for (i = 0; i < size; i++)
	{
		char str[16] = {0};

		sprintf(str, "%3d", YGET(i, st_shndx));
		printf(FORMAT_SYMBOL_32, i,
			YGET(i, st_value),
			YGET(i, st_size),
			get_sym_type(elf_header, i),
			get_sym_bind(elf_header, i),
			get_sym_visibility(elf_header, i),
			YGET(i, st_shndx) == SHN_ABS ? "ABS"
				: YGET(i, st_shndx) == SHN_COMMON ? "COM"
				: YGET(i, st_shndx) == 0 ? "UND" : str,
			sym_string_table + YGET(i, st_name));
		if (i && verneed && versym[i] >= 2)
		{
			size_t index = find_verneed_index(verneed, verneed_size, (size_t)versym[i]);

			if (!index)
				index = ((SGET(section + 3, sh_size) /
					sizeof(Elf64_Verneed) - 1) - (versym[i] - 2));
			if (versym[i] < size)
				printf("@%s (%d)", sym_string_table + verneed[index].vn_aux, versym[i]);
		}
		printf("\n");
	}
}

/**
 * print_program_headers64 - prints 64 bit program headers
 * @elf_header: address of elf header struct
 * @string_table: the string table program
 * @sym_string_table: the symbol string table
 * @versym: the Elf64_Versym section array
 * @verneed: the Elf64_Verneed section array
 * @verneed_size: the size of the verneed array
 * @section: the symbol section to print
 */
void print_symbol_table64(elf_t *elf_header, char *string_table,
	char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed,
	size_t verneed_size, int section)
{
	size_t i = 0;
	size_t size = SGET(section, sh_size) / SGET(section, sh_entsize);

	printf(TITLE_SYMBOL_64, string_table + SGET(section, sh_name), size);
	for (i = 0; i < size; i++)
	{
		char str[16] = {0};

		sprintf(str, "%3d", YGET(i, st_shndx));
		printf(FORMAT_SYMBOL_64, i,
			YGET(i, st_value),
			YGET(i, st_size),
			get_sym_type(elf_header, i),
			get_sym_bind(elf_header, i),
			get_sym_visibility(elf_header, i),
			YGET(i, st_shndx) == SHN_ABS ? "ABS"
				: YGET(i, st_shndx) == SHN_COMMON ? "COM"
				: YGET(i, st_shndx) == 0 ? "UND" : str,
			sym_string_table + YGET(i, st_name));
		print_verneed_info(elf_header, sym_string_table, versym, verneed,
			verneed_size, i, size, section);
		printf("\n");
	}
}
