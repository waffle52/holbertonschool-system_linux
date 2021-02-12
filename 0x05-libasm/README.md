# 0x05-libasm

## 0-strlen.asm
Write a copycat of the function strlen(3), in x86-64 Assembly

    Prototype when used in C: size_t asm_strlen(const char *str);

## 1-strcmp.asm
Write a copycat of the function strcmp(3), in x86-64 Assembly

    Prototype when used in C: int asm_strcmp(const char *s1, const char *s2);

## 2-strncmp.asm
Write a copycat of the function strncmp(3), in x86-64 Assembly

    Prototype when used in C: int asm_strncmp(const char *s1, const char *s2, size_t n);

## 3-strchr.asm
Write a copycat of the function strchr(3), in x86-64 Assembly

    Prototype when used in C: char *asm_strchr(const char *s, int c);

## 4-strstr.asm
Write a copycat of the function strstr(3), in x86-64 Assembly

    Prototype when used in C: char *asm_strstr(const char *haystack, const char *needle);

## 5-memcpy.asm
Write a copycat of the function memcpy(3), in x86-64 Assembly

    Prototype when used in C: void *asm_memcpy(void *dest, const void *src, size_t n);

## 6-putc.asm
Write a function that prints a single character on the standard output, in x86-64 Assembly

    Prototype when used in C: size_t asm_putc(int c);
    Where c holds the character to be printed
    Your function must return the total number of bytes written on the standard output
    For this task, you are allowed to use the syscall instruction only once in your file

## 7-puts.asm
Write a function that prints a string of characters on the standard output, in x86-64 Assembly

    Prototype when used in C: size_t asm_puts(const char *str);
    Where str holds the string to be printed
    Your function must return the total number of bytes written on the standard output
    You are not allowed to use any sort of jump
    Your file 0-strlen.asm will be compiled as well, you are allowed to call it once in your file
    For this task, you are allowed to use the syscall instruction only once in your file

## 8-strcasecmp.asm
Write a copycat of the function strcasecmp(3), in x86-64 Assembly

    Prototype when used in C: int asm_strcasecmp(const char *s1, const char *s2);

## 9-strncasecmp.asm
Write a copycat of the function strncasecmp(3), in x86-64 Assembly

    Prototype when used in C: int asm_strncasecmp(const char *s1, const char *s2, size_t n);

## 10-strspn.asm
Write a copycat of the function strspn(3), in x86-64 Assembly

    Prototype when used in C: size_t asm_strspn(const char *s, const char *accept);

## 11-strcspn.asm
Write a copycat of the function strcspn(3), in x86-64 Assembly

    Prototype when used in C: size_t asm_strcspn(const char *s, const char *reject);

## 12-strpbrk.asm
Write a copycat of the function strpbrk(3), in x86-64 Assembly

    Prototype when used in C: char *asm_strpbrk(const char *s, const char *accept);
