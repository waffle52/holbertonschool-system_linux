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

#define USAGE "0-hreadelf elf_filename\n"
#define ERR_NO_ENTRY "'%s': No such file\n"
#define ERR_NO_ACCESS "Input file '%s' is not readable.\n"
#define ERR_NOT_MAGIC "Not an ELF file - it has the wrong magic bytes at the start\n"
#define IS_32(x) ((x).e_ident[EI_CLASS] == ELFCLASS32)
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


#endif
