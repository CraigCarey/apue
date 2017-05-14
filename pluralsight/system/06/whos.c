/* Simple demonstration of password file lookup */

#include <pwd.h>

void main(int argc, char *argv[])
{
    struct passwd *user;

    user = getpwnam(argv[1]);

    if (user != NULL) {
	printf("uid=%d\n", user->pw_uid);
	printf("Home directory=%s\n", user->pw_dir);
	printf("Shell=%s\n", user->pw_shell);
    }
    else
	printf("no such user\n");
}
