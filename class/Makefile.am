CFLAGS = -O2 $(X_CFLAGS)
lib_LTLIBRARIES		= libpasswdgen.la
libpasswdgen_la_SOURCES	= password.cpp pwdgenerr.cpp

libpasswdgen_la_LDFLAGS = \
        -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)    \
        -release $(LT_RELEASE)					\
        -export-dynamic \
        $(X_LIBS)

libpasswdgenincludedir = $(prefix)/include/passwdgen
passwdgen_public_h_sources = password.h pwdgenerr.h

libpasswdgeninclude_HEADERS = $(passwdgen_public_h_sources)

EXTRA_DIST = $(passwdgen_public_h_sources)

CLEANFILES		= *~
DISTCLEANFILES		= .deps/*.P
