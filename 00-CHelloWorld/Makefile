CC=gcc
GREEN=\033[0;32m
NC=\033[0m # No Color

run: hello.c
	@echo "${GREEN}Compiling and linking...${NC}"
	$(CC) hello.c -o hello -Wall
	@echo "${GREEN}Creating output.txt...\033[0;32m${NC}"
	touch output.txt
	@echo "${GREEN}Capturing the output of the executable and writing it in output.txt\033[0;32m${NC}"
	./hello > output.txt

clean:
	@echo "${GREEN}Cleaning...${NC}"
	rm hello output.txt
