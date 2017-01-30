project(src)

set(HEADER_FILES model/bookmark-model.cpp model/bookmark-model.h model/model.cpp model/model.h)

set(SOURCE_FILES model/bookmark-model.cpp model/bookmark-model.h model/model.cpp model/model.h)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(src Qt5::Widgets)
