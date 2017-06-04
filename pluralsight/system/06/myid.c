// Approximation to the standard "id" program
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	uid_t uid = getuid();
	printf("uid=%d", uid);

	struct passwd *u = getpwuid(uid);
	printf("(%s) ", u->pw_name);

	gid_t gid = getgid();
	printf("gid=%d", gid);

	struct group *g = getgrgid(gid);
	printf("(%s) ", g->gr_name);

	printf("groups=");
	
	char *member;

	// check each group to see if current user is a member
	while ((g = getgrent()) != NULL)
	{
		// printf("%s\n", g->gr_name);
		while((member = *(g->gr_mem)++) != NULL)
			if (strcmp(member, u->pw_name) == 0)
				printf("%d(%s),", g->gr_gid, g->gr_name);
	}

	printf("\n");
}
