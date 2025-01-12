SUBDIRS = class src

.PHONY: all clean

all:
.for dir in $(SUBDIRS)
	@cd ${dir} && ${MAKE}
.endfor

clean:
.for dir in $(SUBDIRS)
	@cd ${dir} && ${MAKE} clean
.endfor
