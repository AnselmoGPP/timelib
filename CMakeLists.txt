CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(timelib)

ADD_EXECUTABLE( ${PROJECT_NAME}
	src/main.cpp
	src/timelib.cpp

	headers/timelib.hpp
)

TARGET_INCLUDE_DIRECTORIES( ${PROJECT_NAME} PUBLIC
        headers
)
