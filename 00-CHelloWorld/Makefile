CC=gcc
GREEN=\033[0;32m
NC=\033[0m # No Color

run: hello.c
	@echo "${GREEN}Compiling and linking...${NC}"
	$(CC) hello.c -o hello -Wall
	@echo "${GREEN}Executing program and capturing output to output.txt${NC}"
	./hello > output.txt

clean:
	@echo "${GREEN}Cleaning...${NC}"
	rm hello
