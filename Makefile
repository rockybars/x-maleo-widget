CC=g++
CFLAGS=-Wall -DXP_UNIX=1 -DMOZ_X11=1 -fPIC -O2 -I ./npapi `pkg-config --cflags gtk+-3.0`
LDFLAGS=-shared `pkg-config --libs gtk+-3.0`
SOURCES=maleo-npapi.cpp MaleoWidgetPlugin.cpp
OBJECTS=$(SOURCES:.cpp=.o)
LIBRARY=maleo-npapi.so

all: $(SOURCES) $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *.so
