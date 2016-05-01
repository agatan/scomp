file(GLOB_RECURSE FILES *.cpp)

add_executable(scomp
  ${FILES})

target_link_libraries(scomp
  coco)
