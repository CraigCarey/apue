DIRS = lib 01_intro 16_sockets advio daemons 06_datafiles db 07_environ \
	03_fileio 04_filedir ipc1 ipc2 08_proc pty 09_relation 10_signals standards \
	05_stdio termios threadctl threads printer exercises

all:
	for i in $(DIRS); do \
		(cd $$i && echo "making $$i" && $(MAKE) ) || exit 1; \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && echo "cleaning $$i" && $(MAKE) clean) || exit 1; \
	done
