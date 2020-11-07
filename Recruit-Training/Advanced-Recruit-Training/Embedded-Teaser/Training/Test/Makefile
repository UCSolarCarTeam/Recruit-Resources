TARGET = TEST
EMBEDDED_REPO_ROOT = ../../

UNITY_DIR = $(EMBEDDED_REPO_ROOT)/UnityTestingTool/
UNITY_SRC_DIR = $(UNITY_DIR)/src/

TRAINING_DIR = $(EMBEDDED_REPO_ROOT)/Training/
TRAINING_TESTS_DIR = $(TRAINING_DIR)/Test/
TRAINING_SRC_DIR = $(TRAINING_DIR)/Core/Src/

TRAINING_INC_DIR = $(TRAINING_DIR)/Core/Inc/

ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -rf
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -rf
	MKDIR = mkdir -p
	TARGET_EXTENSION=out
endif

.PHONY: clean
.PHONY: test
.PHONY: all

PATHS = -I . \
-I $(TRAINING_TESTS_DIR) \
-I $(TRAINING_INC_DIR) \
-I $(UNITY_SRC_DIR) \

PATHT = ./
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/

COMPILE=gcc
CFLAGS=$(PATHS)

TRAINING_SOURCES = \
				$(TRAINING_SRC_DIR)/Training.c \

TEST_SOURCES = \
			main.c \
			TrainingTest.c \

UNITY_SOURCES = $(UNITY_SRC_DIR)unity.c

# Get object file name of each source
# Each object file will be compiled as a target
TEST_OBJ = $(patsubst %.c, $(PATHO)%.o, $(TEST_SOURCES))
TRAINING_OBJ = $(patsubst $(TRAINING_SRC_DIR)%.c, $(PATHO)%.o, $(TRAINING_SOURCES))
UNITY_OBJ = $(patsubst $(UNITY_SRC_DIR)%.c, $(PATHO)%.o, $(UNITY_SOURCES))

default: mkdirs $(TARGET)

# Parse files within this folder
$(PATHO)%.o: %.c
	$(COMPILE) -c -o $@ $< $(CFLAGS)

# Parse the unity sources
$(PATHO)%.o: $(UNITY_SRC_DIR)/%.c
	$(COMPILE) -c -o $@ $< $(CFLAGS)

# Parse files within the Training source
$(PATHO)%.o: $(TRAINING_SRC_DIR)/%.c
	echo "building $@"
	$(MKDIR) $(dir $@)
	$(COMPILE) -c -o $@ $< $(CFLAGS)

$(TARGET): $(TEST_OBJ) $(UNITY_OBJ) $(TRAINING_OBJ)
	$(COMPILE) -o $(PATHB)$@ $^ $(CFLAGS)

# Make build directories
mkdirs:
	$(MKDIR) $(PATHB)
		echo "$(TRAINING_OBJ)"
	$(MKDIR) $(PATHO)

clean:
	$(CLEANUP) $(PATHB)

test:
	$(PATHB)/$(TARGET)

.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt
.PRECIOUS: $(PATHB)$(TARGET)
