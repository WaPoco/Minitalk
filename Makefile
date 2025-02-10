CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L. -lft -lftprintf
SERVER = server 
CLIENT = client

SRC_SERVER = server.c
SRC_CLIENT = client.c
HEADER = ft_printf.h libft.h

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

all: $(SERVER) $(CLIENT)

$(SERVER): $(OBJ_SERVER)
	$(CC) $(OBJ_SERVER) $(LFLAGS) -o $(SERVER)

$(CLIENT): $(OBJ_CLIENT)
	$(CC) $(OBJ_CLIENT) $(LFLAGS) -o $(CLIENT)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	rm $(SERVER) $(CLIENT)

re: fclean all
.PHONY: all clean fclean re