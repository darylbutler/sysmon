PROJPATH=/share/projects/sysmon
EXECUTABLE=sysmon
CC=g++
CFLAGS=-W -Wall -Wextra -pedantic -std=c++0x `pkg-config --cflags --libs pangomm-1.4 cairomm-1.0`
LDFLAGS=-lcairo -lX11

MAINFILES=$(PROJPATH)/testmm.cpp
WIDGETFILES=$(PROJPATH)/src/widgets/widget.cpp \
			$(PROJPATH)/src/widgets/data/bar_widget.cpp \
			$(PROJPATH)/src/widgets/layout/horz_layout_widget.cpp \
			$(PROJPATH)/src/widgets/layout/vert_layout_widget.cpp \
			$(PROJPATH)/src/widgets/layout/layout_widget.cpp
UTILITYFILES=$(PROJPATH)/src/utilities/color.cpp \
			 $(PROJPATH)/src/utilities/file_utility.cpp \
			 $(PROJPATH)/src/utilities/param_list.cpp \
			 $(PROJPATH)/src/utilities/value_history_table.cpp
DATASOURCEFILES=$(PROJPATH)/src/data_sources/data_source.cpp \
				$(PROJPATH)/src/data_sources/cpu_source.cpp

all: sysmon

sysmon: $(MAINFILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(MAINFILES) -o $(EXECUTABLE)

main.o: $(MAINFILES)
	$(CC) -c $(CFLAGS) $(MAINFILES)

widgets.o: $(WIDGETFILES)
	$(CC) -c $(CFLAGS) $(WIDGETFILES)

utilities.o: $(UTILITYFILES)
	$(CC) -c $(CFLAGS) $(UTILITYFILES)

data_sources.o: $(DATASOURCEFILES)
	$(CC) -c $(CFLAGS) $(DATASOURCEFILES)

clean:
	rm -rf *o sysmon
