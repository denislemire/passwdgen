SUBDIRS = class src

# Get the current git commit hash
PASSWDGEN_BUILD != git rev-parse --short HEAD

# Export the variable so it's available to subdirectories
.export PASSWDGEN_BUILD

.PHONY: all clean

all:
.for dir in $(SUBDIRS)
	@cd ${dir} && ${MAKE}
.endfor

clean:
.for dir in $(SUBDIRS)
	@cd ${dir} && ${MAKE} clean
.endfor
