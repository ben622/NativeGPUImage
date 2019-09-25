# API
file(GLOB API_SOURCE "*.cpp*")
message("file ${API_SOURCE}")
add_library(libapi
           ${API_SOURCE}
)

target_link_libraries(libapi
        android
)

