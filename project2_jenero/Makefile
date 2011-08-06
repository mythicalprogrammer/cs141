#
#  Usage: 
#
#   make 
#
#  Compiles format_text.cc
#

CXXFLAGS = -g -Iinclude -I../include

INCLUDES=$(wildcard include/*.h)

all: format_text format_text_greedily show_cost format_text_soln

%: %.cc ${INCLUDES}
	g++ ${CXXFLAGS} -o $@ $<

compare: format_text_greedily format_text show_cost
	format_text_greedily 60 < sample_text_short | show_cost 60
	@echo 
	format_text 60 < sample_text_short | show_cost 60

compare_long: format_text_greedily format_text show_cost
	format_text_greedily 60 < sample_text_long | show_cost 60 | grep 'TOTAL'
	format_text 60 < sample_text_long | show_cost 60 | grep 'TOTAL'
