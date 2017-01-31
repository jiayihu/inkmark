project(src)

set(HEADER_FILES models/bookmark-model.cpp models/bookmark-model.h models/application-model.cpp models/application-model.h views/application-view.cpp views/application-view.h)

set(SOURCE_FILES models/bookmark-model.cpp models/bookmark-model.h models/application-model.cpp models/application-model.h views/application-view.cpp views/application-view.h)

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(src Qt5::Widgets)
