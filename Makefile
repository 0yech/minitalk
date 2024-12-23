NAME_SERVER = server
NAME_CLIENT = client
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
PRINTF_DIR = ./ft_printf
SRC_DIR = ./src
INC_DIR = ./include
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRCS_SERVER = $(SRC_DIR)/server.c

SRCS_CLIENT = $(SRC_DIR)/client.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

LIBS = -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

all: $(LIBFT) $(PRINTF) $(NAME_SERVER) $(NAME_CLIENT)

# Compile libft
$(LIBFT):
	@echo "Compiling libft"
	@$(MAKE) -C $(LIBFT_DIR)

# Compile printf with root libft
$(PRINTF): $(LIBFT)
	@echo "Compiling ft_printf"
	@$(MAKE) -C $(PRINTF_DIR)

# Compile server
$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT) $(PRINTF)
	@echo "Compiling $(NAME_SERVER)"
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBS) -o $(NAME_SERVER)
	@echo "$(NAME_SERVER) created successfully"

# Compile client
$(NAME_CLIENT): $(OBJS_CLIENT) $(LIBFT) $(PRINTF)
	@echo "Compiling $(NAME_CLIENT)"
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBS) -o $(NAME_CLIENT)
	@echo "$(NAME_CLIENT) created successfully"

# Compile object files to output
%.o: %.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(PRINTF_DIR)/include -c $< -o $@

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@echo "Clean completed."

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@echo "Full clean completed."

re: fclean all

.PHONY: all clean fclean re
