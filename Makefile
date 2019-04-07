.PHONY: all install uninstall clean

CC = cc
CFLAGS = -c -Wall
TARGET = btree
SRCS = main.c $(TARGET).c 
OBJS = main.o $(TARGET).o 
INSTALL_PATH = ~/bin

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) -o $(TARGET) $(OBJS)
	
$(OBJS): $(SRCS) $(TARGET).h
	@$(CC) $(CFLAGS) $(SRCS)
	
install: $(TARGET)
	@install -D -m 744 $(TARGET) $(INSTALL_PATH)/$(TARGET)
	
uninstall: $(TARGET)
	@rm -rf $(INSTALL_PATH)/$(TARGET)
	
clean:
	@rm -rf $(TARGET) *.o 
