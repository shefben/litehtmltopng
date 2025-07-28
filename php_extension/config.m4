PHP_ARG_ENABLE(litehtmltopng, whether to enable litehtmltopng support, [ --enable-litehtmltopng   Enable litehtmltopng support])

if test "$PHP_LITEHTMLTOPNG" != "no"; then
  PHP_REQUIRE_CXX()
  PHP_ADD_INCLUDE(../libs/litehtmlcpp98/include)
  PHP_ADD_INCLUDE(../libs/litehtmlcpp98/src)
  PHP_ADD_INCLUDE(../libs/litehtmlcpp98/src/litehtml_boost)
  PHP_ADD_LIBRARY_WITH_PATH(cairo, /usr/lib)
  PHP_ADD_LIBRARY_WITH_PATH(freetype, /usr/lib)
  LITEHTML_SRCS="`cd $abs_srcdir/../libs/litehtmlcpp98/src && echo *.cpp`"
  PHP_NEW_EXTENSION(litehtmltopng, litehtmltopng.cpp render.cpp $LITEHTML_SRCS, $ext_shared,,-std=c++11)
fi
