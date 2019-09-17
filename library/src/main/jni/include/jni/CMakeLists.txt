file(GLOB JNI_SOURCE "*.cpp")
message("file ${JNI_SOURCE}")
add_library(libjni
           ${JNI_SOURCE}
)

target_link_libraries(libjni)

