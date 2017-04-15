DIRS = lib 01_intro sockets advio daemons 06_datafiles db environ \
	03_fileio 04_filedir ipc1 ipc2 proc pty relation signals standards \
	05_stdio termios threadctl threads printer exercises

all:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
