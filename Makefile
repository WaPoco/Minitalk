CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L./Libft -lft -L./ft_printf -lftprintf
SERVER = server
CLIENT = client

SRC_SERVER = ./src/server.c
SRC_CLIENT = ./src/client.c
HEADER = ./ft_printf/ft_printf.h ./Libft/libft.h

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)


all: Libft ft_printf $(SERVER) $(CLIENT)

Libft:
	make -C ./Libft
	
ft_printf:
	make -C ./ft_printf
	
$(SERVER): $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) $(LFLAGS) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) $(LFLAGS) -o $(CLIENT)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@
	
bonus: all

clean:
	rm $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	rm $(SERVER) $(CLIENT)
	make -C ./Libft fclean
	make -C ./ft_printf fclean

re: fclean all Libft ft_printf

.PHONY: all clean fclean re Libft ft_printf
