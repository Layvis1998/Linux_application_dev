TESTS = test_init test_grow test_push test_pop
check_PROGRAMS = test_init test_grow test_push test_pop

AM_CFLAGS = -I$(top_builddir)/source @CHECK_CFLAGS@
LDADD = $(top_builddir)/source/libgrowbuf.la @CHECK_LIBS@
