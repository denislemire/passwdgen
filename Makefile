PREFIX ?= /usr/local
SUBDIRS = class src

# Get the current git commit hash
PASSWDGEN_BUILD != git rev-parse --short HEAD

# Export the variable so it's available to subdirectories
.export PASSWDGEN_BUILD

.PHONY: all clean install uninstall

all:
.for dir in $(SUBDIRS)
	@cd ${dir} && ${MAKE}
.endfor

clean:
.for dir in $(SUBDIRS)
	@cd ${dir} && ${MAKE} clean
.endfor

test:
	$(MAKE) -C tests test

install: all
	@echo "Installing src/passwdgen to ${PREFIX}/bin"
	install -d ${PREFIX}/bin
	install -m 755 src/passwdgen ${PREFIX}/bin
	@echo "Installing src/man/passwdgen.1 to ${PREFIX}/man/man1"
	install -d ${PREFIX}/man/man1
	install -m 644 src/man/passwdgen.1 ${PREFIX}/man/man1

uninstall:
	@echo "Removing ${PREFIX}/bin/passwdgen"
	-rm -f ${PREFIX}/bin/passwdgen
	@echo "Removing ${PREFIX}/man/man1/passwdgen.1"
	-rm -f ${PREFIX}/man/man1/passwdgen.1
