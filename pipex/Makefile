# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#==============================================================================#
#                                  MAKE CONFIG                                 #
#==============================================================================#

MAKE	= make -C
SHELL	:= bash

# Default test values
ARG			?=

#==============================================================================#
#                                     NAMES                                    #
#==============================================================================#

UNAME 			= $(shell whoami)
NAME 			= pipex 

### Message Vars
_SUCCESS 		= [$(GRN)SUCCESS$(D)]
_INFO 			= [$(BLU)INFO$(D)]
_NORM 			= [$(MAG)Norminette$(D)]
_NORM_SUCCESS 	= $(GRN)=== OK:$(D)
_NORM_INFO 		= $(BLU)File no:$(D)
_NORM_ERR 		= $(RED)=== KO:$(D)
_SEP 			= =====================

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH		= .
LIBS_PATH		= lib
BUILD_PATH		= .build
TEMP_PATH		= .temp
TESTS_PATH		= files

FILES	= main.c
FILES	+= manual_pipex.c

SRC		= $(addprefix $(SRC_PATH)/ $(FILES))

OBJS	= $(SRC:$(SRC_PATH)/%.c=$(BUILD_PATH)/%.o)

#==============================================================================#
#                              COMPILER & FLAGS                                #
#==============================================================================#

CC			= cc

CFLAGS		= -Wall -Wextra -Werror
DFLAGS		= -g

INC			= -I.

#==============================================================================#
#                                COMMANDS                                      #
#==============================================================================#

RM		= rm -rf
AR		= ar rcs
MKDIR_P	= mkdir -p

#==============================================================================#
#                                  RULES                                       #
#==============================================================================#

##@ pipex Compilation Rules 🏗

all: $(BUILD_PATH) $(NAME)	## Compile Mandatory version

$(NAME): $(BUILD_PATH) $(OBJS)			## Compile Mandatory version
	@echo "$(YEL)Compiling $(MAG)$(NAME)$(YEL) mandatory version$(D)"
	$(CC) $(CFLAGS) $(DFLAGS) $(OBJS) -o $(NAME)
	@echo "[$(_SUCCESS) compiling $(MAG)$(NAME)$(D) $(YEL)🖔$(D)]"
	make norm

deps:		## Download/Update deps
	@if test ! -d "$(LIBFT_PATH)"; then make get_libft; \
		else echo "$(YEL)[libft]$(D) folder found 🖔"; fi
	@echo " $(RED)$(D) [$(GRN)Nothing to be done!$(D)]"

-include $(BUILD_PATH)/%.d

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -n "$(MAG)█$(D)"
	$(CC) $(CFLAGS) $(DFLAGS) -MMD -MP -c $< -o $@

$(BUILD_PATH):
	$(MKDIR_P) $(BUILD_PATH)
	@echo "* $(YEL)Creating $(CYA)$(BUILD_PATH)$(YEL) folder:$(D) $(_SUCCESS)"

$(TEMP_PATH):
	$(MKDIR_P) $(TEMP_PATH)
	@echo "* $(YEL)Creating $(CYA)$(TEMP_PATH)$(YEL) folder:$(D) $(_SUCCESS)"

$(LIBFT_ARC):
	$(MAKE) $(LIBFT_PATH) extra

get_libft:
	@echo "* $(CYA)Getting Libft submodule$(D)]"
	@if test ! -d "$(LIBFT_PATH)"; then \
		git clone git@github.com:PedroZappa/42_libft.git $(LIBFT_PATH); \
		echo "* $(GRN)Libft submodule download$(D): $(_SUCCESS)"; \
	else \
		echo "* $(GRN)Libft submodule already exists 🖔"; \
	echo " $(RED)$(D) [$(GRN)Nothing to be done!$(D)]"; \
	fi

##@ Norm Rules

norm: $(TEMP_PATH)		## Run norminette test on source files
	@echo "$(CYA)$(_SEP)$(D)"
	@printf "${_NORM}: $(YEL)$(SRC_PATH)$(D)\n"
	@ls $(SRC_PATH) | wc -l > $(TEMP_PATH)/norm_ls.txt
	@printf "$(_NORM_INFO) $$(cat $(TEMP_PATH)/norm_ls.txt)\n"
	@printf "$(_NORM_SUCCESS) "
	@norminette $(SRC_PATH) | grep -wc "OK" > $(TEMP_PATH)/norm.txt; \
	if [ $$? -eq 1 ]; then \
		echo "0" > $(TEMP_PATH)/norm.txt; \
	fi
	@printf "$$(cat $(TEMP_PATH)/norm.txt)\n"
	@if ! diff -q $(TEMP_PATH)/norm_ls.txt $(TEMP_PATH)/norm.txt > /dev/null; then \
		printf "$(_NORM_ERR) "; \
		norminette $(SRC_PATH) | grep -v "OK"> $(TEMP_PATH)/norm_err.txt; \
		cat $(TEMP_PATH)/norm_err.txt | grep -wc "Error:" > $(TEMP_PATH)/norm_errn.txt; \
		printf "$$(cat $(TEMP_PATH)/norm_errn.txt)\n"; \
		printf "$$(cat $(TEMP_PATH)/norm_err.txt)\n"; \
	else \
		printf "[$(YEL)Everything is OK$(D)]\n"; \
	fi
	@echo "$(CYA)$(_SEP)$(D)"

check_ext_func: all		## Check for external functions
	@echo "[$(YEL)Checking for external functions$(D)]"
	@echo "$(YEL)$(_SEP)$(D)"
	@echo "$(CYA)Reading binary$(D): $(MAG)$(NAME)$(D)"
	nm ./$(NAME) | grep "U" | grep -v "__" | tee $(TEMP_PATH)/ext_func.txt
	@echo "$(YEL)$(_SEP)$(D)"

##@ Test Rules 🧪

test_input: all			## Run tests on input args
	@echo "$(CYA)Testing $(RED)invalid $(CYA)input$(D)"
	@echo "$(YEL)$(_SEP)$(D)"
	@echo "$(CYA)Test $(GRN)1$(CYA) : Less arguments than required$(D)"
	-./$(NAME)
	@echo "$(CYA)Test $(GRN)2$(CYA) : Less arguments than required$(D)"
	-./$(NAME) 2 200 200
	@echo "$(CYA)Test $(GRN)3$(CYA) : Negative argument$(D)"
	-./$(NAME) 2 200 -200 200 
	@echo "$(CYA)Test $(GRN)4$(CYA) : Argument larger than INT_MAX$(D)"
	-./$(NAME) 2 2147483648 200 200
	@echo "$(CYA)Test $(GRN)5$(CYA) : Invalid argument$(D)"
	-./$(NAME) "  a2" 200 200 200
	@echo "$(CYA)Test $(GRN)6$(CYA) : Argument value out of range (too many philos)$(D)"
	-./$(NAME) 201 800 200 200 2
	@echo "$(CYA)Test $(GRN)7$(CYA) : Argument value out of range (number of philos less oe equal to 0)$(D)"
	-./$(NAME) 0 120 60 60 
	@echo "$(CYA)Test $(GRN)8$(CYA) : Argument value out of range (time_to_die less than 60)$(D)"
	-./$(NAME) 5 59 30 30 
	@echo "$(CYA)Test $(GRN)9$(CYA) : Argument value out of range (time_to_eat less than 60)$(D)"
	-./$(NAME) 5 120 59 60 
	@echo "$(CYA)Test $(GRN)10$(CYA) : Argument value out of range (time_to_sleep less than 60)$(D)"
	-./$(NAME) 5 120 60 59 
	@echo "$(YEL)$(_SEP)$(D)"

test: all				## Run test with input args
	tmux set-option remain-on-exit on
	@echo "$(YEL)$(_SEP)$(D)"
	tmux split-window -h "./$(NAME) $(ARG)"
	@echo "$(YEL)$(_SEP)$(D)"

test_kill_one: all			## Run a kill test
	tmux set-option remain-on-exit on
	@echo "$(CYA)Testing $(GRN)kill $(D): A philo should not eat and should die"
	@echo "$(YEL)$(_SEP)$(D)"
	./$(NAME) 1 800 200 200
	@echo "$(YEL)$(_SEP)$(D)"

test_kill_four: all			## Run a kill test
	tmux set-option remain-on-exit on
	@echo "$(CYA)Testing $(GRN)kill $(D): A philo should not eat and should die"
	@echo "$(YEL)$(_SEP)$(D)"
	./$(NAME) 4 310 200 100
	@echo "$(YEL)$(_SEP)$(D)"

test_life_min: all			## Run a infinite test with shortest life possible
	tmux set-option remain-on-exit on
	@echo "$(CYA)Testing $(GRN)life $(D): 5 philos should eat and live forever"
	@echo "$(YEL)$(_SEP)$(D)"
	tmux split-window -h "./$(NAME) 200 180 60 60"
	@echo "$(YEL)$(_SEP)$(D)"

test_life_4: all			## Run a infinite meal test
	tmux set-option remain-on-exit on
	@echo "$(CYA)Testing $(GRN)life $(D): 4 philos should eat and live forever"
	@echo "$(YEL)$(_SEP)$(D)"
	tmux split-window -h "./$(NAME) 4 410 200 200"
	@echo "$(YEL)$(_SEP)$(D)"
	tmux resize-pane -R 54

test_life_5: all			## Run a infinite meal test
	tmux set-option remain-on-exit on
	@echo "$(CYA)Testing $(GRN)life $(D): 5 philos should eat and live forever"
	@echo "$(YEL)$(_SEP)$(D)"
	tmux split-window -h "./$(NAME) 5 800 200 200"
	@echo "$(YEL)$(_SEP)$(D)"
	tmux resize-pane -R 54

test_seven_meals: all			## Run a seven meals test
	tmux set-option remain-on-exit on
	-./$(NAME) 5 800 200 200 7 > $(TEMP_PATH)/out.txt
	@echo "$(CYA)Testing $(GRN)seven meals $(D): 5 philos should eat seven meals"
	@echo "$(YEL)$(_SEP)$(D)"
	make count_meals
	tmux resize-pane -R 54

test_all: all			## Run all tests
	make test_input
	make test_kill_one
	make test_kill_four
	make test_life_4
	tmux resize-pane -L 50
	make test_life_5
	tmux resize-pane -L 64
	make test_life_min
	make check_ext_func

test_count_panes:
	PANES_COUNT=$(shell tmux display-message -p '#{pane_count}'); \
	tmux list-panes -t $(shell tmux display -p '#W') | wc -l
	# Print the number of panes
	@echo "$(CYA)Number of panes: $(GRN)$$PANES_COUNT$(D)"
	@echo "$(YEL)$(_SEP)$(D)"

test_chaos: all			## Run a chaos test
	tmux set-option remain-on-exit on
	@TIMESTAMP=$(shell date +%Y%m%d%H%M%S); \
	if [ -f $(TEMP_PATH)/out.txt ]; then \
		mv -f $(TEMP_PATH)/out.txt $(TEMP_PATH)/out.$$TIMESTAMP.txt; \
	fi
	@echo "$(CYA)Testing $(RED)chaos$(D)"
	@echo "Iterations : $(GRN)$(ITER)$(D)"
	@echo "$(YEL)$(_SEP)$(D)"
	@for i in $(shell seq 1 $(ITER)); do \
		TEST_N=$$i; \
		echo "Test $(CYA)$$TEST_N$(D) of $(GRN)$(ITER)$(D)"; \
		echo "$(YEL)$(_SEP)$(D)"; \
		valgrind --leak-check=full --show-leak-kinds=all --log-file=$(TEMP_PATH)/temp.txt ./$(NAME) $(ARG7); \
		sed -n '10p' $(TEMP_PATH)/temp.txt | tee -a $(TEMP_PATH)/out.txt; \
		COUNTER=$$((COUNTER + 1)); \
		echo $$COUNTER > $(TEMP_PATH)/passed_count.txt; \
		echo "$(YEL)$(_SEP)$(D)"; \
	done
	@make --no-print-directory test_results
	@tmux select-pane -L

test_results: $(TEMP_PATH)
	@make --no-print-directory remove_ansi_noise
	@if pgrep -x "lnav" > /dev/null; then \
		echo "lnav is already running."; \
	else \
		if command -v lnav; then \
		tmux split-window -h "lnav $(TEMP_PATH)/out.txt"; \
		else \
			cat $(TEMP_PATH)/out.txt; \
		fi; \
	fi
	@echo "$(YEL)$(_SEP)$(D)"
	@echo "$(BCYA)Tests Summary$(D)"
	@TOTAL=$(shell cat $(TEMP_PATH)/passed_count.txt)
	@echo -ne "$(MAG)Total\t:  $(YEL)"
	@awk '{print $$1}' $(TEMP_PATH)/passed_count.txt
	@echo -ne "$(D)"
	@cat $(TEMP_PATH)/out.txt | grep heap | awk '{ print $$5, $$7 }' > $(TEMP_PATH)/count.txt
	@awk -v count=0 '{if ($$1 == $$2) count++} END \
		{ print "$(GRN)Passed$(D)\t: ", count}' $(TEMP_PATH)/count.txt
	@awk -v count=0 '{if ($$1 != $$2) \
		{ print $$1 > "$(TEMP_PATH)/failing_test_number.txt"; count++ }} END \
		{ print "$(RED)Failed$(D)\t: ", count}' $(TEMP_PATH)/count.txt
	@echo "$(YEL)$(_SEP)$(D)"

remove_ansi_noise:
	@sed -i 's/\␏//g' $(TEMP_PATH)/out.txt

count_meals:
	@echo "$(YEL)$(_SEP)$(D)"
	@echo "$(CYA)Simulation $(GRN)Stats$(D):"
	@echo "$(YEL)$(_SEP)$(D)"
	@awk '/is eating/ {; \
	    philo_id=$$2;; \
	    meals[philo_id]++;; \
	} END {; \
	    for(id in meals) {; \
	        printf("Philosopher %s has eaten %d meals\n", id, meals[id]);; \
	    }; \
	}' $(TEMP_PATH)/out.txt
	@if command -v lnav; then \
		tmux split-window -h "lnav $(TEMP_PATH)/out.txt"; \
	else \
		tail -f $(TEMP_PATH)/out.txt; \
	fi
	@echo "$(YEL)$(_SEP)$(D)"

visual: all 	## Run philosopher's Visualizer
	@if test ! -d "$(VISUALIZER_PATH)"; then make get_visual; \
	else echo "$(YEL)[$(NAME) Visualizer]$(D) folder found 🖔"; \
	echo " $(RED)$(D) [$(GRN)Getting $(NAME) output$(D)]"; \
	timeout $(TIMEOUT)s ./$(NAME) $(ARG) > $(TEMP_PATH)/out.txt;\
	./$(VISUALIZER_PATH)/visualizer $(TIMESTEP) < $(TEMP_PATH)/out.txt; fi

get_visual:
	@echo "* [$(CYA)Getting $(NAME) Visualizer$(D)]"
	git clone git@github.com:SimonCROS/philosophers-visualizer.git $(VISUALIZER_PATH)
	@echo "* $(GRN)Visualizer download$(D): $(_SUCCESS)"
	@echo "[$(YEL)Building $(NAME) Visualizer$(D)]"
	$(MAKE) $(VISUALIZER_PATH)
	@echo "[$(_SUCCESS) building $(MAG)$(NAME) Visualizer!$(D) $(YEL)🖔$(D)]"

##@ Debug Rules 

gdb: all $(NAME) $(TEMP_PATH)			## Debug w/ gdb
	tmux split-window -h "gdb --tui --args ./$(NAME)"
	tmux resize-pane -L 5
	make get_log

vgdb: all $(NAME) $(TEMP_PATH)			## Debug w/ valgrind (memcheck) & gdb
	tmux split-window -h "valgrind --vgdb-error=0 --log-file=gdb.txt ./$(NAME) $(ARG)"
	make vgdb_pid
	tmux split-window -v "gdb --tui -x $(TEMP_PATH)/gdb_commands.txt $(NAME)"
	tmux resize-pane -U 18
	make get_log

valgrind: all $(NAME) $(TEMP_PATH)			## Debug w/ valgrind (memcheck)
	tmux set-option remain-on-exit on
	tmux split-window -h "valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) $(ARG)"

helgrind: all $(NAME) $(TEMP_PATH)			## Debug threads w/ helgrind
	tmux set-option remain-on-exit on
	tmux split-window -h "valgrind --log-file=gdb.txt --tool=helgrind -s ./$(NAME) $(ARG7)"
	tmux resize-pane -R 55
	make get_log

vgdb_helgrind: all $(NAME) $(TEMP_PATH)			## Debug threads w/ helgrind & gdb
	tmux split-window -h "valgrind --vgdb-error=0 --log-file=gdb.txt --tool=helgrind ./$(NAME) $(ARG)"
	make vgdb_pid
	tmux split-window -v "gdb --tui -x $(TEMP_PATH)/gdb_commands.txt $(NAME)"
	tmux resize-pane -U 18
	make get_log

massif: all $(TEMP_PATH)		## Run Valgrind w/ Massif (gather profiling information)
	@TIMESTAMP=$(shell date +%Y%m%d%H%M%S); \
	if [ -f massif.out.* ]; then \
		mv -f massif.out.* $(TEMP_PATH)/massif.out.$$TIMESTAMP; \
	fi
	@echo " 🔎 [$(YEL)Massif Profiling$(D)]"
	valgrind --tool=massif --time-unit=B ./$(NAME) $(ARG)
	ms_print massif.out.*
# Learn more about massif and ms_print:
### https://valgrind.org/docs/manual/ms-manual.html

get_log:
	touch gdb.txt
	@if command -v lnav; then \
		lnav gdb.txt; \
	else \
		tail -f gdb.txt; \
	fi

vgdb_pid: $(NAME) $(TEMP_PATH)
	printf "target remote | vgdb --pid=" > $(TEMP_PATH)/gdb_commands.txt
	printf "$(shell pgrep -f valgrind)" >> $(TEMP_PATH)/gdb_commands.txt

##@ Clean-up Rules 󰃢

clean: 				## Remove object files
	@echo "*** $(YEL)Removing $(MAG)$(NAME)$(D) and deps $(YEL)object files$(D)"
	@if [ -d "$(BUILD_PATH)" ] || [ -d "$(TEMP_PATH)" ]; then \
		if [ -d "$(BUILD_PATH)" ]; then \
			$(RM) $(BUILD_PATH); \
			echo "* $(YEL)Removing $(CYA)$(BUILD_PATH)$(D) folder & files$(D): $(_SUCCESS)"; \
		fi; \
		if [ -d "$(TEMP_PATH)" ]; then \
			$(RM) $(TEMP_PATH); \
			echo "* $(YEL)Removing $(CYA)$(TEMP_PATH)$(D) folder & files:$(D) $(_SUCCESS)"; \
		fi; \
	else \
		echo " $(RED)$(D) [$(GRN)Nothing to clean!$(D)]"; \
	fi

fclean: clean			## Remove executable and .gdbinit
	@if [ -f "$(NAME)" ]; then \
		if [ -f "$(NAME)" ]; then \
			$(RM) $(NAME); \
			echo "* $(YEL)Removing $(CYA)$(NAME)$(D) file: $(_SUCCESS)"; \
		fi; \
	else \
		echo " $(RED)$(D) [$(GRN)Nothing to be fcleaned!$(D)]"; \
	fi

libclean: fclean	## Remove libs
	$(RM) $(LIBS_PATH)
	@echo "* $(YEL)Removing lib folder & files!$(D) : $(_SUCCESS)"

re: fclean all	## Purge & Recompile

##@ Help 󰛵

help: 			## Display this help page
	@awk 'BEGIN {FS = ":.*##"; \
			printf "\n=> Usage:\n\tmake $(GRN)<target>$(D)\n"} \
		/^[a-zA-Z_0-9-]+:.*?##/ { \
			printf "\t$(GRN)%-18s$(D) %s\n", $$1, $$2 } \
		/^##@/ { \
			printf "\n=> %s\n", substr($$0, 5) } ' Makefile
## Tweaked from source:
### https://www.padok.fr/en/blog/beautiful-makefile-awk

.PHONY: bonus extrall clean fclean re help

#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)

