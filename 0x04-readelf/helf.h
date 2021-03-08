#ifndef HELF_H
#define HELF_H

#include <elf.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define MAPPING_TITLE \
	"\n Section to Segment mapping:\n  Segment Sections...\n"

#define ELF_SECTION_SIZE(sec_hdr, segment)			\
	(((sec_hdr->sh_flags & SHF_TLS) == 0				\
	|| sec_hdr->sh_type != SHT_NOBITS				\
	|| segment->p_type == PT_TLS) ? sec_hdr->sh_size : 0)

#define ELF_IS_SECTION_IN_SEGMENT(sec_hdr, segment)			\
	(((((sec_hdr->sh_flags & SHF_TLS) != 0)				\
	&& (segment->p_type == PT_TLS					\
	 || segment->p_type == PT_LOAD))				\
	|| ((sec_hdr->sh_flags & SHF_TLS) == 0				\
	&& segment->p_type != PT_TLS))					\
	&& (sec_hdr->sh_type == SHT_NOBITS					\
	|| (sec_hdr->sh_offset >= segment->p_offset		\
	   && (sec_hdr->sh_offset + ELF_SECTION_SIZE(sec_hdr, segment)	\
	       <= segment->p_offset + segment->p_filesz)))		\
	&& ((sec_hdr->sh_flags & SHF_ALLOC) == 0				\
	|| (sec_hdr->sh_addr >= segment->p_vaddr				\
	   && (sec_hdr->sh_addr + ELF_SECTION_SIZE(sec_hdr, segment)	\
	       <= segment->p_vaddr + segment->p_memsz))))

#define ELF_IS_SECTION_IN_SEGMENT_FILE(sec_hdr, segment)	\
	(sec_hdr->sh_size > 0						\
	&& ELF_IS_SECTION_IN_SEGMENT(sec_hdr, segment))

#define ELF_IS_SECTION_IN_SEGMENT_MEMORY(sec_hdr, segment)	\
	(ELF_SECTION_SIZE(sec_hdr, segment) > 0			\
	&& ELF_IS_SECTION_IN_SEGMENT(sec_hdr, segment))

#define TITLE_PROGRAM_32 \
	"  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align\n"

#define FORMAT_PROGRAM_32 \
	"  %-14s 0x%6.6lx 0x%8.8lx 0x%8.8lx 0x%5.5lx 0x%5.5lx %c%c%c %#lx\n"

#define TITLE_PROGRAM_64 \
	"  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align\n"

#define FORMAT_PROGRAM_64 \
	"  %-14s 0x%6.6lx 0x%16.16lx 0x%16.16lx 0x%6.6lx 0x%6.6lx %c%c%c %#lx\n"
#define USAGE "0-hreadelf elf_filename\n"
#define ERR_NO_ENTRY "'%s': No such file\n"
#define ERR_NO_ACCESS "Input file '%s' is not readable.\n"
#define ERR_NOT_MAGIC "Not an ELF file - it has the wrong magic bytes at the start\n"

#define TITLE_SYMBOL_64 \
	"\nSymbol table '%s' contains %lu entries:\n" \
	"   Num:    Value          Size Type    Bind   Vis      Ndx Name\n"

#define TITLE_SYMBOL_32 \
	"\nSymbol table '%s' contains %lu entries:\n" \
	"   Num:    Value  Size Type    Bind   Vis      Ndx Name\n"

#define FORMAT_SYMBOL_64 \
	"  %4lu: %16.16lx %5lu %-7s %-6s %-7s %4s %s"

#define FORMAT_SYMBOL_32 \
	"  %4lu: %8.8lx %5lu %-7s %-6s %-7s %4s %s"

#define IS_32(x) ((x).e_ident[EI_CLASS] == ELFCLASS32)
#define IS_64 ((elf_header->e64).e_ident[EI_CLASS] == ELFCLASS64)
#define IS_BE(x) ((x).e_ident[EI_DATA] == ELFDATA2MSB)
#define EGET(x) \
	(IS_32(elf_header->e64) ? elf_header->e32.x : elf_header->e64.x)
#define SGET(i, x) \
	(IS_32(elf_header->e64) ? elf_header->s32[i].x : elf_header->s64[i].x)
#define PGET(i, x) \
	(IS_32(elf_header->e64) ? elf_header->p32[i].x : elf_header->p64[i].x)
#define YGET(i, x) \
	(IS_32(elf_header->e64) ? elf_header->y32[i].x : elf_header->y64[i].x)


/**
 * struct hdrs - struct containing 32 and 64 bit ELF header information
 * @Ehdr32: 32-bit ELF header
 * @Ehdr64: 64-bit ELF header
 * @Shdr32: 32-bit ELF section header
 * @Shdr64: 64-bit ELF section header
 */
typedef struct hdrs
{
	Elf32_Ehdr Ehdr32;
	Elf64_Ehdr Ehdr64;
	Elf32_Shdr Shdr32;
	Elf64_Shdr Shdr64;
} hdrs;

/**
 * struct Elf - stores 32/64 structs and other data
 * @e64: the 64 bit struct
 * @e32: the 32 bit struct
 * @s64: the 64 bit struct section array
 * @s32: the 32 bit struct section array
 * @p64: the 64 bit struct program array
 * @p32: the 32 bit struct program array
 * @y64: the 64 bit struct symbol array
 * @y32: the 32 bit struct symbol array
 */
typedef struct Elf
{
	Elf64_Ehdr e64;
	Elf32_Ehdr e32;
	Elf64_Shdr *s64;
	Elf32_Shdr *s32;
	Elf64_Phdr *p64;
	Elf32_Phdr *p32;
	Elf64_Sym *y64;
	Elf32_Sym *y32;

} elf_t;

/* shared.c */
FILE *parse(int argc, char **argv);
void convertmsb(char *type, size_t size);

/* 0-print_info1-4.c */
int printelfh(FILE *fp, char *arg);
int printversion(hdrs hdr, char *arg);
void printosabi(hdrs hdr);
void printtype(hdrs hdr, int is_msb);
void printmachine(hdrs hdr, int is_msb);
void printfileversion(hdrs hdr, int is_msb);
void printentry(hdrs hdr, int is_32, int is_msb);
void printpshoff(hdrs hdr, int is_32, int is_msb);
void printflags(hdrs hdr, int is_32, int is_msb);
void printhdrsize(hdrs hdr, int is_32, int is_msb);
void printphnum(hdrs hdr, int is_32, int is_msb);
void printshentsize(hdrs hdr, int is_32, int is_msb);
void printshnum(hdrs hdr, int is_32, int is_msb);
void printshstrndx(hdrs hdr, int is_32, int is_msb);
void printmachine2(Elf64_Half machine);

/* 1-print_header.c */
int print_section_headers_full(elf_t *elf_header, int fd);
void switch_all_endian(elf_t *h);
int open_file(char *name, int silent);
int check_elf(char *elf_header);
char *read_string_table(elf_t *elf_header, int fd);
void read_section_headers(elf_t *elf_header, int fd);
void switch_all_endian_section(elf_t *h, size_t i);
void print_section_headers32(elf_t *elf_header, char *string_table);
unsigned int switch_endian4(unsigned int n);
unsigned long switch_endian8(unsigned long n);
char *get_section_type(unsigned int sh_type);
char *get_section_flags(elf_t *elf_header, size_t i);
unsigned short switch_endian2(unsigned short n);
void print_section_headers64(elf_t *elf_header, char *string_table);
int print_all_symbol_tables(elf_t *elf_header, int fd);
void print_symbol_table(elf_t *elf_header, int fd, size_t i,
			char *string_table);
int print_program_headers_full(elf_t *elf_header, int fd);
void read_symbol_table(elf_t *elf_header, int fd, int i);
void switch_all_endian_program(elf_t *h, size_t i);
void switch_all_endian_symbol(elf_t *h, size_t i);
char *read_symbol_string_table(elf_t *elf_header, int fd, int i);
void *read_data(elf_t *elf_header, int fd, unsigned long offset, long size);
void read_program_headers(elf_t *elf_header, int fd);
void print_program_headers64(elf_t *elf_header, char *string_table, int fd);
void print_program_headers32(elf_t *elf_header, char *string_table, int fd);
char *get_segment_type(unsigned long p_type);
void switch_all_endian_ver(elf_t *h, uint16_t *versym, size_t versym_size,
			   Elf64_Verneed *verneed, size_t verneed_size);
void print_symbol_table32(elf_t *elf_header, char *string_table,
			  char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed,
			  size_t verneed_size, int section);
void print_symbol_table64(elf_t *elf_header, char *string_table,
			  char *sym_string_table, uint16_t *versym, Elf64_Verneed *verneed,
			  size_t verneed_size, int section);
char *get_sym_type(elf_t *elf_header, size_t i);
char *get_sym_bind(elf_t *elf_header, size_t i);
size_t find_verneed_index(Elf64_Verneed *verneed, size_t verneed_size,
			  size_t index);
void print_verneed_info(elf_t *elf_header, char *sym_string_table,
	uint16_t *versym, Elf64_Verneed *verneed, size_t verneed_size, size_t i,
			size_t size, int section);
char *get_sym_visibility(elf_t *elf_header, size_t i);
int print_section_to_segment_mapping(elf_t *elf_header, char *string_table);
char *get_type(elf_t *elf_header);

#endif
