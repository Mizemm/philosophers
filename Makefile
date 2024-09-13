PHILO = philo
CC = cc 
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

PHILO_C = philo.c
UTILS_C = routine.c utils1.c utils2.c utils3.c utils/ft_atoi.c utils/ft_strlen.c

PHILO_O = $(PHILO_C:.c=.o)
UTILS_O = $(UTILS_C:.c=.o)

all: $(PHILO)

$(PHILO): $(PHILO_O) $(UTILS_O) philo.h
	$(CC) $(CFLAGS) $(PHILO_O) $(UTILS_O) -o philo

clean:
	rm -rf $(PHILO_O) $(UTILS_O)

fclean: clean
	rm -rf $(PHILO)

re: fclean all