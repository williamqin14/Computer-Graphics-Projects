
cmake_minimum_required ( VERSION 3.1.0 )

project ( RTWeekend
  VERSION 3.0.0
  LANGUAGES CXX
)

# Set to c++11
set ( CMAKE_CXX_STANDARD 11 )


set ( SOURCE_ONE_WEEKEND
  # ${COMMON_ALL}
  src/InOneWeekend/rtweekend.h
  src/InOneWeekend/camera.h
  src/InOneWeekend/ray.h
  src/InOneWeekend/vec3.h
  src/InOneWeekend/hittable.h
  src/InOneWeekend/hittable_list.h
  src/InOneWeekend/material.h
  src/InOneWeekend/sphere.h
  src/InOneWeekend/main.cc
)


# Executables
add_executable(inOneWeekend      ${SOURCE_ONE_WEEKEND})
