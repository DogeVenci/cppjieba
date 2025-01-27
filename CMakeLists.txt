PROJECT(CPPJIEBA)

CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps
  ${PROJECT_SOURCE_DIR}/include)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "/usr/local/cppjieba" CACHE PATH "default install path" FORCE )
endif()

ADD_DEFINITIONS(-O3 -w)

IF(APPLE) # mac os
    ADD_DEFINITIONS(-std=c++0x)
endif()

# cmake .. -DENC=GBK
# IF (DEFINED ENC)
#     ADD_DEFINITIONS(-DCPPJIEBA_${ENC})
# ENDIF()

# ADD_SUBDIRECTORY(deps)
# ADD_SUBDIRECTORY(test)

ADD_EXECUTABLE(demo test/demo.cpp)
SET_TARGET_PROPERTIES(demo PROPERTIES LINK_FLAGS "-s ALLOW_MEMORY_GROWTH=1 --preload-file ${CMAKE_SOURCE_DIR}/dict@../dict")

ADD_EXECUTABLE(jieba wasm/jieba.cpp)
# SET_TARGET_PROPERTIES(jieba PROPERTIES LINK_FLAGS "--bind -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS=['_Extract'] -s EXPORTED_RUNTIME_METHODS=['cwrap','ccall'] --preload-file ${CMAKE_SOURCE_DIR}/dict@../dict")
SET_TARGET_PROPERTIES(jieba PROPERTIES LINK_FLAGS "--bind -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 --preload-file ${CMAKE_SOURCE_DIR}/dict@../dict")

# ENABLE_TESTING()
# ADD_TEST(NAME ./test/test.run COMMAND ./test/test.run)
# ADD_TEST(NAME ./load_test COMMAND ./load_test)
# ADD_TEST(NAME ./demo COMMAND ./demo)
