project(src)

set(HEADER_FILES inkmark.cpp inkmark.h)

set(SOURCE_FILES inkmark.cpp inkmark.h)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})
