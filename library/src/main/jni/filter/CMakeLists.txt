# filter
file(GLOB FILTER_SOURCE "*.cpp*")
message("file ${FILTER_SOURCE}")
add_library(libfilter
           ${FILTER_SOURCE}
)

target_link_libraries(libfilter
        z
        GLESv2
        EGL
        android
)

