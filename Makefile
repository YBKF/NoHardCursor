# This Makefile only use for Windows

SRC_DIR = ./src
BUILD_DIR = ./build
TARGET = $(BUILD_DIR)/NohardCursor.exe

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.d,$(SRCS))

LDFLAGS = -Wl,--gc-sections
CFLAGS = -Wall -Os -ffunction-sections -fdata-sections

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@
	strip $@

$(BUILD_DIR)/%.d: $(SRC_DIR)/%.c
	rm -f %@; \
	$(CC) -MM $< > $@.tmp; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.tmp > $@; \
	rm -f $@.tmp

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "clean..."
	$(shell pwsh -c "Get-ChildItem $(BUILD_DIR) -Recurse | Remove-Item")

-include $(DEPS)
