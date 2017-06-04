#include <pwd.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <shadow.h>

struct passwd * getpwnam(const char *name)
{
	struct passwd *ptr;

	/* ensure that the files are rewound */
	setpwent();

	/* return the next entry in the password file */
	while ((ptr = getpwent()) != NULL)
		if (strcmp(name, ptr->pw_name) == 0)
			break;
	
	/* neither getpwnam nor getpwuid should leave any of the files open */
	endpwent();
	
	return(ptr);
}

struct spwd * getspwnam(const char *name)
{
    struct spwd *ptr;

    /* ensure that the files are rewound */
    setspent();

    /* return the next entry in the password file */
    while ((ptr = getspent()) != NULL)
        if (strcmp(name, ptr->sp_namp) == 0)
            break;
    
    /* neither getpwnam nor getpwuid should leave any of the files open */
    endspent();
    
    return(ptr);
}


int main(void)
{
	struct passwd *pw = getpwnam("craig");

	printf("pw_name:  %s\n", pw->pw_name);
	printf("pw_uid:   %u\n", pw->pw_uid);
	printf("pw_gid:   %u\n", pw->pw_gid);
	printf("pw_dir:   %s\n", pw->pw_dir);
	printf("pw_shell: %s\n\n", pw->pw_shell);

	struct spwd *spw = getspwnam("craig");

	/* Must be root for this */
	printf("sp_namp:  %s\n", spw->sp_namp);
	printf("sp_pwdp:   %s\n", spw->sp_pwdp);

	return 0;
}