PHILO = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

PHILO_C = philo.c
UTILS_C = utils/ft_atoi.c

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