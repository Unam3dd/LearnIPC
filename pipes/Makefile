###################################
#
#		PROJECT NAME
#
###################################

NAME = ipc_pipes
CC = gcc

##################################
#
#		CLEAN COMPILATION
#
##################################

OBJDIR = obj
vpath %.c src
vpath %.h inc

###################################
#
#		C SOURCES
#
###################################

SRC_MAIN = main.c

SRC_COMMAND = command/command.c
SRC_PARSING = parsing/parse_command.c
SRC_PIPES   = pipes/pipes_create.c
SRC_EXECUTE = execute/execute.c

SRCS = $(SRC_MAIN) $(SRC_COMMAND) $(SRC_PARSING) $(SRC_PIPES) $(SRC_EXECUTE)
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

###################################
#
#		CFLAGS
#
###################################

ifdef DEBUG
	CFLAGS = -Wall -Wextra -Werror -Iinc -g
else
	CFLAGS = -Wall -Wextra -Werror -Iinc -O2
endif

ifdef ASAN
	CFLAGS += -fsanitize=leak,address
endif

###################################
#
#		RULES
#
###################################

all: $(NAME)

obj/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o  $@

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(MSH_FLAGS) -o $(NAME)

$(OBJDIR):
	mkdir -p $(sort $(addprefix $(OBJDIR)/, $(dir $(SRCS))))

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) $(OBJDIR)

re: fclean all

run_dbg: $(NAME)
	@echo valgrind --leak-check=full --track-fds=yes --show-leak-kinds=all

###################################
#
#		PHONY
#
###################################

.PHONY: all clean fclean re run_dbg
