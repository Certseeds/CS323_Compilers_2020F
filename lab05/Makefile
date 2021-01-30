CC=gcc
GPP=g++
LINK_FLAGS= -I. --shared -fPIC -o libsymtab.so

C_WARM= -Wall -Wextra
C_STD= -std=c11
C_FLAGS= $(C_WARM) $(C_STD) $(LINK_FLAGS)

CXX_STD= -std=c++17
CXX_DEBUG = -g
CXX_WARN = -Wall -Wextra
CXX_FLAGS = -O3 $(CXX_DEBUG) $(CXX_STD) $(CXX_WARN) $(LINK_FLAGS)
CPP = $(GPP) $(CXX_FLAGS)


lltest: clean
	$(CC) symtab_ll.c $(C_FLAGS)
	@echo "\e[92mRunning test for \e[4mlinked list\e[24m implementation...\e[0m"
	@python3 test.py ||:
httest: clean
	$(CC) symtab_ht.c $(C_FLAGS)
	@echo "\e[92mRunning test for \e[4mhash table\e[24m implementation...\e[0m"
	@python3 test.py ||:
bttest: clean
	$(GPP) symtab_bt.c $(CXX_FLAGS)
	@echo "\e[92mRunning test for \e[4mbinary tree\e[24m implementation...\e[0m"
	@python3 test.py ||:
clean:
	@rm -f *.o *.out *.so
.PHONY: lltest httest bttest clean
