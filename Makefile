MAKEFLAGS += -j$(nproc)
MAKEFLAGS += --no-print-directory

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror

MKDIR = mkdir -p

NAME = matt_daemon
TROJAN = trojan

OBJS = $(addprefix o/,\
	   matt_daemon.o\
	   lock.o\
	   socket.o\
	   commands.o\
	   logger.o\
	   signals.o\
	   )

VPATH = $(wildcard s/*/) s/

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LDLIBS)

.ONESHELL:
o/%.o: %.cpp | o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $< -c -o o/$(notdir $@)

o:
	@$(MKDIR) $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean .WAIT all

.PHONY: all clean fclean re
