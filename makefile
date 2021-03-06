#

ifndef CC
	CC := gcc
endif

CFLAGS := $(PLAT_CFLAGS)

RM := rm -rf
CP := cp
MD := mkdir -p
DIR_SRC := ./src
DIR_OBJ := ./obj
DIR_DEP := ./obj
DIR_BIN := ./bin
DIR_CONFIG := ./config

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifeq ($(DEBUG), 1)
	CFLAGS := $(CFLAGS) -DNVIPFIX_DEF_DEBUG
endif

ifeq ($(USE_NVC), 1)
	CFLAGS := $(CFLAGS) -DNVIPFIX_DEF_ENABLE_NVC
	LIBS := $(LIBS) -lssl -lcrypto -lnvOS
endif

ifeq ($(UNICODE), 1)
	CFLAGS := $(CFLAGS) -DNVIPFIX_DEF_UNICODE
endif

ifeq ($(TEST), 1)
	CFLAGS := $(CFLAGS) -DNVIPFIX_DEF_TEST
endif

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# All Target
all: dirs $(DIR_BIN)/nvIPFIX

dirs:
	$(MD) $(DIR_BIN)
	$(MD) $(DIR_OBJ)
	$(MD) $(DIR_DEP)

# Tool invocations
$(DIR_BIN)/nvIPFIX: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	$(CC) -fopenmp -o $@ $(OBJS) $(USER_OBJS) -L/usr/local/lib $(PLAT_LDFLAGS) $(LIBS)
	$(CP) $(DIR_CONFIG)/log4crc $(DIR_BIN)/
	$(CP) $(DIR_CONFIG)/nvipfix.config $(DIR_BIN)/
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) $(DIR_BIN)/nvIPFIX
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
