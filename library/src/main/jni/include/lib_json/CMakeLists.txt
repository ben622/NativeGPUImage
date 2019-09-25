set( JSONCPP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/main/jni/include)

set( PUBLIC_HEADERS
    ${JSONCPP_INCLUDE_DIR}/json/config.h
    ${JSONCPP_INCLUDE_DIR}/json/forwards.h
    ${JSONCPP_INCLUDE_DIR}/json/features.h
    ${JSONCPP_INCLUDE_DIR}/json/value.h
    ${JSONCPP_INCLUDE_DIR}/json/reader.h
    ${JSONCPP_INCLUDE_DIR}/json/version.h
    ${JSONCPP_INCLUDE_DIR}/json/writer.h
    ${JSONCPP_INCLUDE_DIR}/json/assertions.h
    )


set(jsoncpp_sources
                json_tool.h
                json_reader.cpp
                json_valueiterator.inl
                json_value.cpp
                json_writer.cpp)



add_library(libjsoncpp ${PUBLIC_HEADERS} ${jsoncpp_sources})

target_link_libraries(libjsoncpp)
