#include "helf.h"


/**
 * get_type - gets the ELF file type
 * @elf_header: the internal header
 * Return: string file type
 */
char *get_type(elf_t *elf_header)
{
	static char buf[32];

	switch (EGET(e_type))
	{
		case ET_NONE:
			return ("NONE (None)");
		case ET_REL:
			return ("REL (Relocatable file)");
		case ET_EXEC:
			return ("EXEC (Executable file)");
		case ET_DYN:
			return ("DYN (Shared object file)");
		case ET_CORE:
			return ("CORE (Core file)");
		default:
			sprintf(buf, "<unknown>: %x", EGET(e_type));
	}
	return (buf);
}

/**
 * get_sym_visibility - gets the STV type
 * @elf_header: the internal header
 * @i: index of the current symbol struct
 * Return: string visibility type
 */
char *get_sym_visibility(elf_t *elf_header, size_t i)
{
	switch (YGET(i, st_other) & 0x3)
	{
		case STV_DEFAULT: return ("DEFAULT");
		case STV_INTERNAL: return ("INTERNAL");
		case STV_HIDDEN: return ("HIDDEN");
		case STV_PROTECTED: return ("PROTECTED");
		default: return ("UNKNOWN");
	}
}
