PHP_ARG_WITH(libthrift, for libthrift support,
[  --with-libthrift[=DIR]        libthrift support])
  
if test "$PHP_LIBTHRIFT" != "no"; then
  if test -r $PHP_LIBTHRIFT/libthrift.so; then
    LIBTHRIFT_DIR=$PHP_LIBTHRIFT
  else
    AC_MSG_CHECKING(for libthrift in default path)
    for i in /usr/local /usr /usr/local/lib /usr/lib /usr/lib64; do
      if test -r $i/libthrift.so; then
        LIBTHRIFT_DIR=$i
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$LIBTHRIFT_DIR"; then
    AC_MSG_RESULT(not found lib thrift)
    AC_MSG_ERROR(Please review path of libthrift, or install thrift if not installed)
  fi
fi

PHP_ARG_WITH(includethrift, for includethrift support,
[  --with-includethrift[=DIR]        Include thrift support])
  
if test "$PHP_INCLUDETHRIFT" != "no"; then
  if test -r $PHP_INCLUDETHRIFT/thrift; then
    INCLUDETHRIFT="$PHP_INCLUDETHRIFT/thrift"
  else
    AC_MSG_CHECKING(for include thrift in default path)
    for i in /usr/local /usr /usr/local/include /usr/include; do
      if test -r $i/thrift; then
        INCLUDETHRIFT="$i/thrift"
        AC_MSG_RESULT(found in $i)
      fi
    done
  fi
  
  if test -z "$PHP_INCLUDETHRIFT"; then
    AC_MSG_RESULT(not found include thrift)
    AC_MSG_ERROR(Please review path of includethrift, or install thrift if not installed)
  fi
fi


PHP_ARG_ENABLE(logscribe, whether to enable logscribe support,
[ --enable-logscribe   Enable logscribe support])

if test "$PHP_LOGSCRIBE" = "yes"; then
  AC_DEFINE(HAVE_LOGSCRIBE, 1, [Whether you have logscribe])
  PHP_REQUIRE_CXX
  logscribe_sources="logscribe.c scribe-cpp/scribe_c.cpp \
  scribe-cpp/gen-cpp/scribe_types.cpp scribe-cpp/gen-cpp/scribe_constants.cpp \
  scribe-cpp/gen-cpp/FacebookService.cpp scribe-cpp/gen-cpp/fb303_types.cpp \
  scribe-cpp/gen-cpp/scribe.cpp scribe-cpp/gen-cpp/fb303_constants.cpp"  
  
  PHP_ADD_INCLUDE(scribe-cpp)  
  PHP_ADD_INCLUDE($INCLUDETHRIFT) 
  PHP_SUBST(LOGSCRIBE_SHARED_LIBADD)
  PHP_ADD_LIBRARY_WITH_PATH(thrift, $LIBTHRIFT_DIR, LOGSCRIBE_SHARED_LIBADD)  
  PHP_NEW_EXTENSION(logscribe, $logscribe_sources, $ext_shared)
fi