
file(GLOB SOURCE "*.c*")
message("file ${SOURCE}")
add_library(libpng
           ${SOURCE}
)

target_link_libraries(libpng
                    z
)

