#include <errno.h>
#include <signal.h>

/**
 * pid_exist - entry
 * @pid: pid of process
 *
 * Return: 1 (SUCCESS)
 */
int pid_exist(pid_t pid)
{
	return (kill(pid, 0) == 0 ? 1 : (errno == ESRCH ? 0 : 1));
}
