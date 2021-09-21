CPPFLAGS = -std=c++17 -Wall -Wno-unused-variable
TARGET = ngram
.PHONY: clean test run

define dir_touch_win
	pwsh -noprofile -command "[Void](New-Item -ItemType Directory -Force -Path $(1))"
endef

define dir_touch_linux
	mkdir -p $(1)
endef

# On Windows
ifeq ($(OS),Windows_NT)
src_dir := .\src
obj_dir := .\obj
out_dir := .\output
srcs := $(shell forfiles /p src /s /m *.cpp /c "cmd /c echo @relpath")
srcs := $(patsubst "%",%,$(srcs))
srcs := $(patsubst .\\%,$(src_dir)\\%,$(srcs))
objs := $(patsubst $(src_dir)\\%.cpp,$(obj_dir)\\%.o,$(srcs))

all: $(TARGET)

$(TARGET): $(objs)
	g++ $(CPPFLAGS) -o $@ $^

$(obj_dir)\\%.o: $(src_dir)\%.cpp
	@$(call dir_touch_win, $(@D))
	g++ $(CPPFLAGS) -c -o $@ $<

run:
	@$(call dir_touch_win, $(out_dir))
	@.\$(TARGET).exe

clean:
	@$(shell rmdir /s/q "$(obj_dir)" 2>nul)
	@$(shell del "$(TARGET).exe" 2>nul)

# On Linux
else
src_dir := ./src
obj_dir := ./obj
out_dir := ./output
srcs := $(shell find $(src_dir) -name "*.cpp")
objs := $(patsubst $(src_dir)%.cpp,$(obj_dir)%.o,$(srcs))

all: $(TARGET)

$(TARGET): $(objs)
	g++ $(CPPFLAGS) -o $@ $^

$(obj_dir)/%.o: $(src_dir)/%.cpp
	@$(call dir_touch_linux, $(@D))
	g++ $(CPPFLAGS) -c -o $@ $<

run:
	@$(call dir_touch_linux, $(out_dir))
	@./$(TARGET)

clean:
	@$(shell rm -rf $(obj_dir) $(TARGET))

endif

# GNU Make macros memo:
# $@ = the name of the file to be made
# $< = the name of the related file that caused the action
# $^ = The names of all the prerequisites, with spaces between them.
# $(@D) = directory part of $@
# \% in $(patsubst ...) is neccesary on windows, or it will be translated as a literal %
# ref: https://www.tutorialspoint.com/makefile/makefile_macros.htm
# ref: https://www.gnu.org/software/make/manual/make.html#Automatic-Variables
# ref: https://stackoverflow.com/questions/15704662/patsubst-not-working-in-gnu-make
