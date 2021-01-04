#include "hls.h"

/**
 * _str_error - print err msg
 * @errnum: errno number
 *
 * Description: Returns message defined by errno)?
 * Return: msg corresponding to errno code
 */

char *_str_error(int errnum)
{
	switch (errnum)
	{
	case 1:
		return ("Operation not permitted");
	case 2:
		return ("No such file or directory");
	case 3:
		return ("No such process");
	case 4:
		return ("Interrupted system call");
	case 5:
		return ("I/O error");
	case 6:
		return ("No such device or address");
	case 7:
		return ("Argument list too long");
	case 8:
		return ("Exec format error");
	case 9:
		return ("No child processes");
	case 10:
		return ("Try again");
	case 11:
		return ("Out of memory");
	case 12:
		return ("Out of memory");
	case 13:
		return ("Permission denied");
	default:
		return ("");
	}
}
