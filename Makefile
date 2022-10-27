NAME 	:= minishell
LIB	:= ./lib/

LIBFTDIR	:= $(LIB)/libft
LIBFTNAME	:= libft.a
LIBFT		:= $(LIBFTDIR)/$(LIBFTNAME)

PIPEDIR		:= $(LIB)/pipex
PIPENAME	:= libpipex.a
PIPEX		:= $(PIPEDIR)/$(PIPENAME)

OBJDIR		:= ./obj

SRCDIR	:= ./srcs/
SRC	:= env.c \
	utils_array.c \
	signal.c \
	lexer.c \
	lexer_util.c \
	parser.c \
	parser_util.c \
	parser_init.c \
	parser_expand.c \
	parser_expand_doller.c \
	parser_expand_asterisk.c \
	parser_expand_asterisk_util.c \
	parser_expand_asterisk_saved_file.c \
	parser_expand_exit_status.c \
	parser_heredoc.c \
	parser_change_std.c \
	parser_find_cmds.c \
	exe_cmds.c \
	env_util.c \
	exit_status.c \
	dir.c
	
ENTRY	:= main.c
ENTRYBONUS	:= main_bonus.c
DELENTRY	:= $(OBJDIR)/main_bonus.o
ifdef WITH_BONUS
ENTRY	:= $(ENTRYBONUS)
DELENTRY	:= $(OBJDIR)/main.o
endif
SRC	+= $(ENTRY)

SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJS	:= $(SRCS:.c=.o)
OBJECTS	:= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
DEPS	:= $(OBJECTS:.o=.d)
INCS	:= ./include 

LIBDIRS	:= $(LIBFTDIR) $(PIPEDIR)
IFLAGS	:= $(addprefix -I,$(INCS)) -I$(shell brew --prefix readline)/include
LFLAGS	:= $(addprefix -L,$(LIBDIRS))
LIBS	:= $(LIBFT) $(PIPEX)

CC	:= cc
ifeq ($(shell uname),Darwin)
CFLAGS	:= -Wall -Wextra -Werror
#CFLAGS	:= -Wall -Wextra -Werror -fsanitize=address  -fsanitize=undefined
else
CFLAGS	:= -Wall -Wextra -Werror
#CFLAGS	:= -Wall -Wextra -Werror -fsanitize=address  -fsanitize=undefined -fsanitize=leak 
endif
LDFLAGS := $(IFLAGS) $(LFLAGS)  -lpipex -lft -lreadline  -L$(shell brew --prefix readline)/lib -lreadline

all:
	@make -C $(LIBFTDIR)
	@make -C $(PIPEDIR)
	@make $(NAME)	

$(NAME)	:	$(OBJECTS) $(LIBS) 
		$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@
		$(RM) $(DELENTRY)


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR) / $(*D)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -MMD -MP -MF $(OBJDIR)/$*.d  -o $@
	$(CC) $(CFLAGS) $(IFLAGS) -c -o $@ $<

clean	:
			$(RM) $(OBJECTS)
			$(RM) $(DEPS)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.o)
			$(RM) $(OBJDIR)/$(ENTRYBONUS:.c=.d)
			@make clean -C $(LIBFTDIR)
			@make clean -C $(PIPEDIR)

fclean	:	clean
			$(RM) $(NAME)
			$(RM) $(LIBS)

re	:		fclean all

bonus	:	
			@make WITH_BONUS=1

ifeq ($(findstring clean,$(MAKECMDGOALS)),)
-include $(DEPS)
endif

.PHONY: clean fclean bonus re
