#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
all:
	@$(MAKE) -C libmove --no-print-directory
	@$(MAKE) -C sample/libmove-NoRSX pkg --no-print-directory

clean:
	@$(MAKE) -C libmove clean --no-print-directory
	@$(MAKE) -C sample/libmove-NoRSX clean --no-print-directory
