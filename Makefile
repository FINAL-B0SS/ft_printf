NAME = libftprintf.a

SRC = ft_printf.c

OBJECTS = *.o

all: $(NAME) 

$(NAME): 
		gcc -c $(SRC)
		ar rcs $(NAME) $(OBJECTS)
		ranlib $(NAME)

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
