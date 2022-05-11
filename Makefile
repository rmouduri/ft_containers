CC			=	clang++
FLAGS		=	-Wall -Wextra -Werror -std=c++98
INCLUDES	=	-I/srcs/ -Itester/srcs -Itester/srcs

VECTOR_FT_SRCS	=	tester/srcs/main_vector_ft.cpp tester/srcs/utils.cpp
VECTOR_STD_SRCS	=	tester/srcs/main_vector_std.cpp tester/srcs/utils.cpp

MAP_FT_SRCS		=	tester/srcs/main_map_ft.cpp tester/srcs/utils.cpp
MAP_STD_SRCS	=	tester/srcs/main_map_std.cpp tester/srcs/utils.cpp

STACK_FT_SRCS	=	tester/srcs/main_stack_ft.cpp tester/srcs/utils.cpp
STACK_STD_SRCS	=	tester/srcs/main_stack_std.cpp tester/srcs/utils.cpp

OBJS_VECTOR_FT	=	$(VECTOR_FT_SRCS:.cpp=.o)
OBJS_VECTOR_STD	=	$(VECTOR_STD_SRCS:.cpp=.o)

OBJS_MAP_FT		=	$(MAP_FT_SRCS:.cpp=.o)
OBJS_MAP_STD	=	$(MAP_STD_SRCS:.cpp=.o)

OBJS_STACK_FT	=	$(STACK_FT_SRCS:.cpp=.o)
OBJS_STACK_STD	=	$(STACK_STD_SRCS:.cpp=.o)

tester/srcs/%.o		:	tester/srcs/%.cpp $(INCLUDES)
						$(CC) $(FLAGS) $(INCLUDES) -o $@ -c $<

all		:	vector map stack

vector	:	$(OBJS_VECTOR_FT) $(OBJS_VECTOR_STD)
			$(CC) $(FLAGS) $(INCLUDES) -o vector_ft $(OBJS_VECTOR_FT)
			$(CC) $(FLAGS) $(INCLUDES) -o vector_std $(OBJS_VECTOR_STD)

map		:	$(OBJS_MAP_FT) $(OBJS_MAP_STD)
			$(CC) $(FLAGS) $(INCLUDES) -o map_ft  $(OBJS_MAP_FT)
			$(CC) $(FLAGS) $(INCLUDES) -o map_std $(OBJS_MAP_STD)

stack	:	$(OBJS_STACK_FT) $(OBJS_STACK_STD)
			$(CC) $(FLAGS) $(INCLUDES) -o stack_ft $(OBJS_STACK_FT)
			$(CC) $(FLAGS) $(INCLUDES) -o stack_std $(OBJS_STACK_STD)

clean	:
			@rm -rf $(OBJS_MAP_FT) $(OBJS_MAP_STD) $(OBJS_VECTOR_FT) $(OBJS_VECTOR_STD) $(OBJS_STACK_FT) $(OBJS_STACK_STD) 

fclean	:	clean
			@rm -rf map_ft map_std vector_ft vector_std stack_ft stack_std

re		:	fclean all

.PHONY	:	all clean fclean re