# Makefile.in generated by automake 1.15 from Makefile.am.
# plugins/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994-2014 Free Software Foundation, Inc.

# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



#
#  tslib/plugins/Makefile.am
#
#  Copyright (C) 2001 Russell King.
#
# This file is placed under the LGPL.  Please see the file
# COPYING for more details.
#
# $Id: Makefile.am,v 1.7 2005/02/28 23:44:12 kergoth Exp $
#


am__is_gnu_make = { \
  if test -z '$(MAKELEVEL)'; then \
    false; \
  elif test -n '$(MAKE_HOST)'; then \
    true; \
  elif test -n '$(MAKE_VERSION)' && test -n '$(CURDIR)'; then \
    true; \
  else \
    false; \
  fi; \
}
am__make_running_with_option = \
  case $${target_option-} in \
      ?) ;; \
      *) echo "am__make_running_with_option: internal error: invalid" \
              "target option '$${target_option-}' specified" >&2; \
         exit 1;; \
  esac; \
  has_opt=no; \
  sane_makeflags=$$MAKEFLAGS; \
  if $(am__is_gnu_make); then \
    sane_makeflags=$$MFLAGS; \
  else \
    case $$MAKEFLAGS in \
      *\\[\ \	]*) \
        bs=\\; \
        sane_makeflags=`printf '%s\n' "$$MAKEFLAGS" \
          | sed "s/$$bs$$bs[$$bs $$bs	]*//g"`;; \
    esac; \
  fi; \
  skip_next=no; \
  strip_trailopt () \
  { \
    flg=`printf '%s\n' "$$flg" | sed "s/$$1.*$$//"`; \
  }; \
  for flg in $$sane_makeflags; do \
    test $$skip_next = yes && { skip_next=no; continue; }; \
    case $$flg in \
      *=*|--*) continue;; \
        -*I) strip_trailopt 'I'; skip_next=yes;; \
      -*I?*) strip_trailopt 'I';; \
        -*O) strip_trailopt 'O'; skip_next=yes;; \
      -*O?*) strip_trailopt 'O';; \
        -*l) strip_trailopt 'l'; skip_next=yes;; \
      -*l?*) strip_trailopt 'l';; \
      -[dEDm]) skip_next=yes;; \
      -[JT]) skip_next=yes;; \
    esac; \
    case $$flg in \
      *$$target_option*) has_opt=yes; break;; \
    esac; \
  done; \
  test $$has_opt = yes
am__make_dryrun = (target_option=n; $(am__make_running_with_option))
am__make_keepgoing = (target_option=k; $(am__make_running_with_option))
pkgdatadir = $(datadir)/tslib
pkgincludedir = $(includedir)/tslib
pkglibdir = $(libdir)/tslib
pkglibexecdir = $(libexecdir)/tslib
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_triplet = x86_64-pc-linux-gnu
host_triplet = arm-unknown-linux-gnu
subdir = plugins
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/m4/internal/libtool.m4 \
	$(top_srcdir)/m4/internal/ltoptions.m4 \
	$(top_srcdir)/m4/internal/ltsugar.m4 \
	$(top_srcdir)/m4/internal/ltversion.m4 \
	$(top_srcdir)/m4/internal/lt~obsolete.m4 \
	$(top_srcdir)/m4/internal/visibility.m4 \
	$(top_srcdir)/acinclude.m4 $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
DIST_COMMON = $(srcdir)/Makefile.am $(am__DIST_COMMON)
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
am__vpath_adj_setup = srcdirstrip=`echo "$(srcdir)" | sed 's|.|.|g'`;
am__vpath_adj = case $$p in \
    $(srcdir)/*) f=`echo "$$p" | sed "s|^$$srcdirstrip/||"`;; \
    *) f=$$p;; \
  esac;
am__strip_dir = f=`echo $$p | sed -e 's|^.*/||'`;
am__install_max = 40
am__nobase_strip_setup = \
  srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*|]/\\\\&/g'`
am__nobase_strip = \
  for p in $$list; do echo "$$p"; done | sed -e "s|$$srcdirstrip/||"
am__nobase_list = $(am__nobase_strip_setup); \
  for p in $$list; do echo "$$p $$p"; done | \
  sed "s| $$srcdirstrip/| |;"' / .*\//!s/ .*/ ./; s,\( .*\)/[^/]*$$,\1,' | \
  $(AWK) 'BEGIN { files["."] = "" } { files[$$2] = files[$$2] " " $$1; \
    if (++n[$$2] == $(am__install_max)) \
      { print $$2, files[$$2]; n[$$2] = 0; files[$$2] = "" } } \
    END { for (dir in files) print dir, files[dir] }'
am__base_list = \
  sed '$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;$$!N;s/\n/ /g' | \
  sed '$$!N;$$!N;$$!N;$$!N;s/\n/ /g'
am__uninstall_files_from_dir = { \
  test -z "$$files" \
    || { test ! -d "$$dir" && test ! -f "$$dir" && test ! -r "$$dir"; } \
    || { echo " ( cd '$$dir' && rm -f" $$files ")"; \
         $(am__cd) "$$dir" && rm -f $$files; }; \
  }
am__installdirs = "$(DESTDIR)$(pluginexecdir)"
LTLIBRARIES = $(pluginexec_LTLIBRARIES)
arctic2_la_LIBADD =
am_arctic2_la_OBJECTS = arctic2-raw.lo
arctic2_la_OBJECTS = $(am_arctic2_la_OBJECTS)
AM_V_lt = $(am__v_lt_$(V))
am__v_lt_ = $(am__v_lt_$(AM_DEFAULT_VERBOSITY))
am__v_lt_0 = --silent
am__v_lt_1 = 
arctic2_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(arctic2_la_LDFLAGS) $(LDFLAGS) -o $@
am_arctic2_la_rpath = -rpath \
	$(pluginexecdir)
collie_la_LIBADD =
am_collie_la_OBJECTS = collie-raw.lo
collie_la_OBJECTS = $(am_collie_la_OBJECTS)
collie_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(collie_la_LDFLAGS) $(LDFLAGS) -o $@
am_collie_la_rpath = -rpath \
	$(pluginexecdir)
corgi_la_LIBADD =
am_corgi_la_OBJECTS = corgi-raw.lo
corgi_la_OBJECTS = $(am_corgi_la_OBJECTS)
corgi_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(corgi_la_LDFLAGS) $(LDFLAGS) -o $@
am_corgi_la_rpath = -rpath $(pluginexecdir)
dejitter_la_LIBADD =
am_dejitter_la_OBJECTS = dejitter.lo
dejitter_la_OBJECTS = $(am_dejitter_la_OBJECTS)
dejitter_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(dejitter_la_LDFLAGS) $(LDFLAGS) -o $@
am_dejitter_la_rpath = -rpath \
	$(pluginexecdir)
h3600_la_LIBADD =
am_h3600_la_OBJECTS = h3600-raw.lo
h3600_la_OBJECTS = $(am_h3600_la_OBJECTS)
h3600_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(h3600_la_LDFLAGS) $(LDFLAGS) -o $@
am_h3600_la_rpath = -rpath $(pluginexecdir)
input_la_LIBADD =
am_input_la_OBJECTS = input-raw.lo
input_la_OBJECTS = $(am_input_la_OBJECTS)
input_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(input_la_LDFLAGS) $(LDFLAGS) -o $@
am_input_la_rpath = -rpath $(pluginexecdir)
linear_la_LIBADD =
am_linear_la_OBJECTS = linear.lo
linear_la_OBJECTS = $(am_linear_la_OBJECTS)
linear_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(linear_la_LDFLAGS) $(LDFLAGS) -o $@
am_linear_la_rpath = -rpath \
	$(pluginexecdir)
linear_h2200_la_LIBADD =
am_linear_h2200_la_OBJECTS = linear-h2200.lo
linear_h2200_la_OBJECTS = $(am_linear_h2200_la_OBJECTS)
linear_h2200_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC \
	$(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=link $(CCLD) \
	$(AM_CFLAGS) $(CFLAGS) $(linear_h2200_la_LDFLAGS) $(LDFLAGS) \
	-o $@
am_linear_h2200_la_rpath = -rpath \
	$(pluginexecdir)
mk712_la_LIBADD =
am_mk712_la_OBJECTS = mk712-raw.lo
mk712_la_OBJECTS = $(am_mk712_la_OBJECTS)
mk712_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(mk712_la_LDFLAGS) $(LDFLAGS) -o $@
am_mk712_la_rpath = -rpath $(pluginexecdir)
pthres_la_LIBADD =
am_pthres_la_OBJECTS = pthres.lo
pthres_la_OBJECTS = $(am_pthres_la_OBJECTS)
pthres_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(pthres_la_LDFLAGS) $(LDFLAGS) -o $@
am_pthres_la_rpath = -rpath \
	$(pluginexecdir)
ucb1x00_la_LIBADD =
am_ucb1x00_la_OBJECTS = ucb1x00-raw.lo
ucb1x00_la_OBJECTS = $(am_ucb1x00_la_OBJECTS)
ucb1x00_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(ucb1x00_la_LDFLAGS) $(LDFLAGS) -o $@
am_ucb1x00_la_rpath = -rpath \
	$(pluginexecdir)
variance_la_LIBADD =
am_variance_la_OBJECTS = variance.lo
variance_la_OBJECTS = $(am_variance_la_OBJECTS)
variance_la_LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(variance_la_LDFLAGS) $(LDFLAGS) -o $@
am_variance_la_rpath = -rpath \
	$(pluginexecdir)
AM_V_P = $(am__v_P_$(V))
am__v_P_ = $(am__v_P_$(AM_DEFAULT_VERBOSITY))
am__v_P_0 = false
am__v_P_1 = :
AM_V_GEN = $(am__v_GEN_$(V))
am__v_GEN_ = $(am__v_GEN_$(AM_DEFAULT_VERBOSITY))
am__v_GEN_0 = @echo "  GEN     " $@;
am__v_GEN_1 = 
AM_V_at = $(am__v_at_$(V))
am__v_at_ = $(am__v_at_$(AM_DEFAULT_VERBOSITY))
am__v_at_0 = @
am__v_at_1 = 
DEFAULT_INCLUDES = -I. -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__depfiles_maybe = depfiles
am__mv = mv -f
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
LTCOMPILE = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=compile $(CC) $(DEFS) \
	$(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) \
	$(AM_CFLAGS) $(CFLAGS)
AM_V_CC = $(am__v_CC_$(V))
am__v_CC_ = $(am__v_CC_$(AM_DEFAULT_VERBOSITY))
am__v_CC_0 = @echo "  CC      " $@;
am__v_CC_1 = 
CCLD = $(CC)
LINK = $(LIBTOOL) $(AM_V_lt) --tag=CC $(AM_LIBTOOLFLAGS) \
	$(LIBTOOLFLAGS) --mode=link $(CCLD) $(AM_CFLAGS) $(CFLAGS) \
	$(AM_LDFLAGS) $(LDFLAGS) -o $@
AM_V_CCLD = $(am__v_CCLD_$(V))
am__v_CCLD_ = $(am__v_CCLD_$(AM_DEFAULT_VERBOSITY))
am__v_CCLD_0 = @echo "  CCLD    " $@;
am__v_CCLD_1 = 
SOURCES = $(arctic2_la_SOURCES) $(collie_la_SOURCES) \
	$(corgi_la_SOURCES) $(dejitter_la_SOURCES) $(h3600_la_SOURCES) \
	$(input_la_SOURCES) $(linear_la_SOURCES) \
	$(linear_h2200_la_SOURCES) $(mk712_la_SOURCES) \
	$(pthres_la_SOURCES) $(ucb1x00_la_SOURCES) \
	$(variance_la_SOURCES)
DIST_SOURCES = $(arctic2_la_SOURCES) $(collie_la_SOURCES) \
	$(corgi_la_SOURCES) $(dejitter_la_SOURCES) $(h3600_la_SOURCES) \
	$(input_la_SOURCES) $(linear_la_SOURCES) \
	$(linear_h2200_la_SOURCES) $(mk712_la_SOURCES) \
	$(pthres_la_SOURCES) $(ucb1x00_la_SOURCES) \
	$(variance_la_SOURCES)
am__can_run_installinfo = \
  case $$AM_UPDATE_INFO_DIR in \
    n|no|NO) false;; \
    *) (install-info --version) >/dev/null 2>&1;; \
  esac
am__tagged_files = $(HEADERS) $(SOURCES) $(TAGS_FILES) $(LISP)
# Read a list of newline-separated strings from the standard input,
# and print each of them once, without duplicates.  Input order is
# *not* preserved.
am__uniquify_input = $(AWK) '\
  BEGIN { nonempty = 0; } \
  { items[$$0] = 1; nonempty = 1; } \
  END { if (nonempty) { for (i in items) print i; }; } \
'
# Make sure the list of sources is unique.  This is necessary because,
# e.g., the same source file might be shared among _SOURCES variables
# for different programs/libraries.
am__define_uniq_tagged_files = \
  list='$(am__tagged_files)'; \
  unique=`for i in $$list; do \
    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
  done | $(am__uniquify_input)`
ETAGS = etags
CTAGS = ctags
am__DIST_COMMON = $(srcdir)/Makefile.in $(top_srcdir)/depcomp
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
ACLOCAL = ${SHELL} /work/driver/11th_drv/tslib/tslib/missing aclocal-1.15
ALLOCA = 
AMTAR = $${TAR-tar}
AM_DEFAULT_VERBOSITY = 1
AR = arm-linux-ar
AUTOCONF = ${SHELL} /work/driver/11th_drv/tslib/tslib/missing autoconf
AUTOHEADER = ${SHELL} /work/driver/11th_drv/tslib/tslib/missing autoheader
AUTOMAKE = ${SHELL} /work/driver/11th_drv/tslib/tslib/missing automake-1.15
AWK = mawk
CC = arm-linux-gcc
CCDEPMODE = depmode=gcc3
CFLAGS = -O2 -Wall -W
CPP = arm-linux-gcc -E
CPPFLAGS = 
CXX = arm-linux-g++
CXXCPP = arm-linux-g++ -E
CXXDEPMODE = depmode=gcc3
CXXFLAGS = -g -O2
CYGPATH_W = echo
DEBUGFLAGS = 
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
DLLTOOL = false
DSYMUTIL = 
DUMPBIN = 
ECHO_C = 
ECHO_N = -n
ECHO_T = 
EGREP = /bin/grep -E
EXEEXT = 
FGREP = /bin/grep -F
GREP = /bin/grep
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
LD = /usr/local/arm/arm-linux/bin/ld
LDFLAGS = 
LIBFLAGS = -DTSLIB_INTERNAL
LIBOBJS =  ${LIBOBJDIR}lstat$U.o ${LIBOBJDIR}stat$U.o
LIBS = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIPO = 
LN_S = ln -s
LTLIBOBJS =  ${LIBOBJDIR}lstat$U.lo ${LIBOBJDIR}stat$U.lo
LT_AGE = 1
LT_CURRENT = 1
LT_RELEASE = 0.0
LT_REVISION = 1
LT_SYS_LIBRARY_PATH = 
MAKEINFO = ${SHELL} /work/driver/11th_drv/tslib/tslib/missing makeinfo
MANIFEST_TOOL = :
MKDIR_P = /bin/mkdir -p
NM = /usr/local/arm/bin/arm-linux-nm -B
NMEDIT = 
OBJDUMP = arm-linux-objdump
OBJEXT = o
OTOOL = 
OTOOL64 = 
PACKAGE = tslib
PACKAGE_BUGREPORT = kergoth@handhelds.org
PACKAGE_DESCRIPTION = Touchscreen Access Library
PACKAGE_NAME = tslib
PACKAGE_STRING = tslib 0.0.2
PACKAGE_TARNAME = tslib
PACKAGE_URL = 
PACKAGE_VERSION = 0.0.2
PATH_SEPARATOR = :
PLUGIN_DIR = ${libdir}/ts/
RANLIB = arm-linux-ranlib
SED = /bin/sed
SET_MAKE = 
SHELL = /bin/bash
STRIP = arm-linux-strip
TS_CONF = ${sysconfdir}/ts.conf
VERSION = 0.0.2
VIS_CFLAGS = 
abs_builddir = /work/driver/11th_drv/tslib/tslib/plugins
abs_srcdir = /work/driver/11th_drv/tslib/tslib/plugins
abs_top_builddir = /work/driver/11th_drv/tslib/tslib
abs_top_srcdir = /work/driver/11th_drv/tslib/tslib
ac_ct_AR = 
ac_ct_CC = 
ac_ct_CXX = 
ac_ct_DUMPBIN = 
am__include = include
am__leading_dot = .
am__quote = 
am__tar = $${TAR-tar} chof - "$$tardir"
am__untar = $${TAR-tar} xf -
bindir = ${exec_prefix}/bin
build = x86_64-pc-linux-gnu
build_alias = 
build_cpu = x86_64
build_os = linux-gnu
build_vendor = pc
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = ${prefix}
host = arm-unknown-linux-gnu
host_alias = arm-linux
host_cpu = arm
host_os = linux-gnu
host_vendor = unknown
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /work/driver/11th_drv/tslib/tslib/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = $(MKDIR_P)
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /work/driver/11th_drv/tslib/tslib/tmp
program_transform_name = s,x,x,
psdir = ${docdir}
runstatedir = ${localstatedir}/run
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target_alias = 
top_build_prefix = ../
top_builddir = ..
top_srcdir = ..
AM_CFLAGS = $(DEBUGFLAGS) $(LIBFLAGS) $(VIS_CFLAGS)
LDADD = -rpath $(PLUGIN_DIR)
INCLUDES = -I$(top_srcdir)/src

#LTVSN			= -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) \
#			   -release $(LT_RELEASE)
LTVSN = -avoid-version
pluginexecdir = $(PLUGIN_DIR)
#LINEAR_MODULE = 
LINEAR_MODULE = linear.la
#DEJITTER_MODULE = 
DEJITTER_MODULE = dejitter.la
#VARIANCE_MODULE = 
VARIANCE_MODULE = variance.la
#PTHRES_MODULE = 
PTHRES_MODULE = pthres.la
#UCB1X00_MODULE = 
UCB1X00_MODULE = ucb1x00.la
#CORGI_MODULE = 
CORGI_MODULE = corgi.la
#COLLIE_MODULE = 
COLLIE_MODULE = collie.la
#H3600_MODULE = 
H3600_MODULE = h3600.la
#MK712_MODULE = 
MK712_MODULE = mk712.la
#ARCTIC2_MODULE = 
ARCTIC2_MODULE = arctic2.la
#INPUT_MODULE = 
INPUT_MODULE = input.la
#H2200_LINEAR_MODULE = 
H2200_LINEAR_MODULE = linear_h2200.la
pluginexec_LTLIBRARIES = \
	$(LINEAR_MODULE) \
	$(DEJITTER_MODULE) \
	$(VARIANCE_MODULE) \
	$(PTHRES_MODULE) \
	$(UCB1X00_MODULE) \
	$(CORGI_MODULE) \
	$(COLLIE_MODULE) \
	$(H3600_MODULE) \
	$(MK712_MODULE) \
	$(ARCTIC2_MODULE) \
	$(H2200_LINEAR_MODULE) \
	$(INPUT_MODULE)

variance_la_SOURCES = variance.c
variance_la_LDFLAGS = -module $(LTVSN)
dejitter_la_SOURCES = dejitter.c
dejitter_la_LDFLAGS = -module $(LTVSN)
linear_la_SOURCES = linear.c
linear_la_LDFLAGS = -module $(LTVSN)
pthres_la_SOURCES = pthres.c
pthres_la_LDFLAGS = -module $(LTVSN)

# hw access
corgi_la_SOURCES = corgi-raw.c
corgi_la_LDFLAGS = -module $(LTVSN)
collie_la_SOURCES = collie-raw.c
collie_la_LDFLAGS = -module $(LTVSN)
ucb1x00_la_SOURCES = ucb1x00-raw.c
ucb1x00_la_LDFLAGS = -module $(LTVSN)
h3600_la_SOURCES = h3600-raw.c
h3600_la_LDFLAGS = -module $(LTVSN)
mk712_la_SOURCES = mk712-raw.c
mk712_la_LDFLAGS = -module $(LTVSN)
arctic2_la_SOURCES = arctic2-raw.c
arctic2_la_LDFLAGS = -module $(LTVSN)
input_la_SOURCES = input-raw.c
input_la_LDFLAGS = -module $(LTVSN)
linear_h2200_la_SOURCES = linear-h2200.c
linear_h2200_la_LDFLAGS = -module $(LTVSN)
all: all-am

.SUFFIXES:
.SUFFIXES: .c .lo .o .obj
$(srcdir)/Makefile.in:  $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --gnu plugins/Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --gnu plugins/Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__depfiles_maybe);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure:  $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4):  $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(am__aclocal_m4_deps):

install-pluginexecLTLIBRARIES: $(pluginexec_LTLIBRARIES)
	@$(NORMAL_INSTALL)
	@list='$(pluginexec_LTLIBRARIES)'; test -n "$(pluginexecdir)" || list=; \
	list2=; for p in $$list; do \
	  if test -f $$p; then \
	    list2="$$list2 $$p"; \
	  else :; fi; \
	done; \
	test -z "$$list2" || { \
	  echo " $(MKDIR_P) '$(DESTDIR)$(pluginexecdir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(pluginexecdir)" || exit 1; \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) $$list2 '$(DESTDIR)$(pluginexecdir)'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=install $(INSTALL) $(INSTALL_STRIP_FLAG) $$list2 "$(DESTDIR)$(pluginexecdir)"; \
	}

uninstall-pluginexecLTLIBRARIES:
	@$(NORMAL_UNINSTALL)
	@list='$(pluginexec_LTLIBRARIES)'; test -n "$(pluginexecdir)" || list=; \
	for p in $$list; do \
	  $(am__strip_dir) \
	  echo " $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=uninstall rm -f '$(DESTDIR)$(pluginexecdir)/$$f'"; \
	  $(LIBTOOL) $(AM_LIBTOOLFLAGS) $(LIBTOOLFLAGS) --mode=uninstall rm -f "$(DESTDIR)$(pluginexecdir)/$$f"; \
	done

clean-pluginexecLTLIBRARIES:
	-test -z "$(pluginexec_LTLIBRARIES)" || rm -f $(pluginexec_LTLIBRARIES)
	@list='$(pluginexec_LTLIBRARIES)'; \
	locs=`for p in $$list; do echo $$p; done | \
	      sed 's|^[^/]*$$|.|; s|/[^/]*$$||; s|$$|/so_locations|' | \
	      sort -u`; \
	test -z "$$locs" || { \
	  echo rm -f $${locs}; \
	  rm -f $${locs}; \
	}

arctic2.la: $(arctic2_la_OBJECTS) $(arctic2_la_DEPENDENCIES) $(EXTRA_arctic2_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(arctic2_la_LINK) $(am_arctic2_la_rpath) $(arctic2_la_OBJECTS) $(arctic2_la_LIBADD) $(LIBS)

collie.la: $(collie_la_OBJECTS) $(collie_la_DEPENDENCIES) $(EXTRA_collie_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(collie_la_LINK) $(am_collie_la_rpath) $(collie_la_OBJECTS) $(collie_la_LIBADD) $(LIBS)

corgi.la: $(corgi_la_OBJECTS) $(corgi_la_DEPENDENCIES) $(EXTRA_corgi_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(corgi_la_LINK) $(am_corgi_la_rpath) $(corgi_la_OBJECTS) $(corgi_la_LIBADD) $(LIBS)

dejitter.la: $(dejitter_la_OBJECTS) $(dejitter_la_DEPENDENCIES) $(EXTRA_dejitter_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(dejitter_la_LINK) $(am_dejitter_la_rpath) $(dejitter_la_OBJECTS) $(dejitter_la_LIBADD) $(LIBS)

h3600.la: $(h3600_la_OBJECTS) $(h3600_la_DEPENDENCIES) $(EXTRA_h3600_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(h3600_la_LINK) $(am_h3600_la_rpath) $(h3600_la_OBJECTS) $(h3600_la_LIBADD) $(LIBS)

input.la: $(input_la_OBJECTS) $(input_la_DEPENDENCIES) $(EXTRA_input_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(input_la_LINK) $(am_input_la_rpath) $(input_la_OBJECTS) $(input_la_LIBADD) $(LIBS)

linear.la: $(linear_la_OBJECTS) $(linear_la_DEPENDENCIES) $(EXTRA_linear_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(linear_la_LINK) $(am_linear_la_rpath) $(linear_la_OBJECTS) $(linear_la_LIBADD) $(LIBS)

linear_h2200.la: $(linear_h2200_la_OBJECTS) $(linear_h2200_la_DEPENDENCIES) $(EXTRA_linear_h2200_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(linear_h2200_la_LINK) $(am_linear_h2200_la_rpath) $(linear_h2200_la_OBJECTS) $(linear_h2200_la_LIBADD) $(LIBS)

mk712.la: $(mk712_la_OBJECTS) $(mk712_la_DEPENDENCIES) $(EXTRA_mk712_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(mk712_la_LINK) $(am_mk712_la_rpath) $(mk712_la_OBJECTS) $(mk712_la_LIBADD) $(LIBS)

pthres.la: $(pthres_la_OBJECTS) $(pthres_la_DEPENDENCIES) $(EXTRA_pthres_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(pthres_la_LINK) $(am_pthres_la_rpath) $(pthres_la_OBJECTS) $(pthres_la_LIBADD) $(LIBS)

ucb1x00.la: $(ucb1x00_la_OBJECTS) $(ucb1x00_la_DEPENDENCIES) $(EXTRA_ucb1x00_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(ucb1x00_la_LINK) $(am_ucb1x00_la_rpath) $(ucb1x00_la_OBJECTS) $(ucb1x00_la_LIBADD) $(LIBS)

variance.la: $(variance_la_OBJECTS) $(variance_la_DEPENDENCIES) $(EXTRA_variance_la_DEPENDENCIES) 
	$(AM_V_CCLD)$(variance_la_LINK) $(am_variance_la_rpath) $(variance_la_OBJECTS) $(variance_la_LIBADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/arctic2-raw.Plo
include ./$(DEPDIR)/collie-raw.Plo
include ./$(DEPDIR)/corgi-raw.Plo
include ./$(DEPDIR)/dejitter.Plo
include ./$(DEPDIR)/h3600-raw.Plo
include ./$(DEPDIR)/input-raw.Plo
include ./$(DEPDIR)/linear-h2200.Plo
include ./$(DEPDIR)/linear.Plo
include ./$(DEPDIR)/mk712-raw.Plo
include ./$(DEPDIR)/pthres.Plo
include ./$(DEPDIR)/ucb1x00-raw.Plo
include ./$(DEPDIR)/variance.Plo

.c.o:
	$(AM_V_CC)$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	$(AM_V_CC)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(COMPILE) -c -o $@ $<

.c.obj:
	$(AM_V_CC)$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	$(AM_V_CC)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(COMPILE) -c -o $@ `$(CYGPATH_W) '$<'`

.c.lo:
	$(AM_V_CC)$(LTCOMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Plo
#	$(AM_V_CC)source='$<' object='$@' libtool=yes \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(LTCOMPILE) -c -o $@ $<

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

ID: $(am__tagged_files)
	$(am__define_uniq_tagged_files); mkid -fID $$unique
tags: tags-am
TAGS: tags

tags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	set x; \
	here=`pwd`; \
	$(am__define_uniq_tagged_files); \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: ctags-am

CTAGS: ctags
ctags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	$(am__define_uniq_tagged_files); \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"
cscopelist: cscopelist-am

cscopelist-am: $(am__tagged_files)
	list='$(am__tagged_files)'; \
	case "$(srcdir)" in \
	  [\\/]* | ?:[\\/]*) sdir="$(srcdir)" ;; \
	  *) sdir=$(subdir)/$(srcdir) ;; \
	esac; \
	for i in $$list; do \
	  if test -f "$$i"; then \
	    echo "$(subdir)/$$i"; \
	  else \
	    echo "$$sdir/$$i"; \
	  fi; \
	done >> $(top_builddir)/cscope.files

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags

distdir: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: check-am
all-am: Makefile $(LTLIBRARIES)
installdirs:
	for dir in "$(DESTDIR)$(pluginexecdir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	if test -z '$(STRIP)'; then \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	      install; \
	else \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	    "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'" install; \
	fi
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic clean-libtool clean-pluginexecLTLIBRARIES \
	mostlyclean-am

distclean: distclean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags

dvi: dvi-am

dvi-am:

html: html-am

html-am:

info: info-am

info-am:

install-data-am:

install-dvi: install-dvi-am

install-dvi-am:

install-exec-am: install-pluginexecLTLIBRARIES

install-html: install-html-am

install-html-am:

install-info: install-info-am

install-info-am:

install-man:

install-pdf: install-pdf-am

install-pdf-am:

install-ps: install-ps-am

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-am
	-rm -rf ./$(DEPDIR)
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic \
	mostlyclean-libtool

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-pluginexecLTLIBRARIES

.MAKE: install-am install-strip

.PHONY: CTAGS GTAGS TAGS all all-am check check-am clean clean-generic \
	clean-libtool clean-pluginexecLTLIBRARIES cscopelist-am ctags \
	ctags-am distclean distclean-compile distclean-generic \
	distclean-libtool distclean-tags distdir dvi dvi-am html \
	html-am info info-am install install-am install-data \
	install-data-am install-dvi install-dvi-am install-exec \
	install-exec-am install-html install-html-am install-info \
	install-info-am install-man install-pdf install-pdf-am \
	install-pluginexecLTLIBRARIES install-ps install-ps-am \
	install-strip installcheck installcheck-am installdirs \
	maintainer-clean maintainer-clean-generic mostlyclean \
	mostlyclean-compile mostlyclean-generic mostlyclean-libtool \
	pdf pdf-am ps ps-am tags tags-am uninstall uninstall-am \
	uninstall-pluginexecLTLIBRARIES

.PRECIOUS: Makefile


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
