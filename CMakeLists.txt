cmake_minimum_required(VERSION 2.8)
project(cpp-markdown)

add_library(cppmarkdown
	src/markdown.h
	src/markdown.cpp
	src/markdown-tokens.h
	src/markdown-tokens.cpp
)
target_include_directories(cppmarkdown PUBLIC src)
target_link_libraries(cppmarkdown PUBLIC boost_regex)

add_executable(cpp-markdown src/main.cpp)
target_link_libraries(cpp-markdown PUBLIC cppmarkdown)

