cmake_minimum_required(VERSION 3.10)
project(ece_city_1_i)

set(CMAKE_C_STANDARD 99)

add_executable(ece_city_1_i
        main.c Structure.h menu.c menu.h)

IF(WIN32)
    target_link_libraries(ece_city_1_i -lmingw32 -lallegro-5.0.10-monolith-md-debug)
ELSE()
    INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.7.0/include)
    LINK_DIRECTORIES(/opt/homebrew/Cellar/allegro/5.2.7.0/lib)
    file(GLOB LIBRARIES "/opt/homebrew/Cellar/allegro/5.2.7.0/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
    TARGET_LINK_LIBRARIES(ece_city_1_i ${LIBRARIES})
ENDIF(WIN32)


