LDFLAGS = -L../class/.libs -lpasswdgen

bin_PROGRAMS		= passwdgen

if HAVE_SYSTEM_GETOPT_H
text_fe_sources = main.cpp cli.cpp
else
text_fe_sources = main.cpp cli.cpp getopt.cpp getopt1.cpp
endif
 
passwdgen_SOURCES	= $(text_fe_sources)

EXTRA_DIST = cli.h getopt.cpp getopt1.cpp mygetopt.h

SUBDIRS = man
