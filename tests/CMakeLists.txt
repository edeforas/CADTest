include_directories(../src)

add_executable(test_geometry test_geometry.cpp  )
target_link_libraries(test_geometry libCADTest)

add_executable(test_bodyfactory test_bodyfactory.cpp  )
target_link_libraries(test_bodyfactory libCADTest)

add_executable(test_bodyboolean test_bodyboolean.cpp  )
target_link_libraries(test_bodyboolean libCADTest)

add_executable(test_fileformat test_fileformat.cpp  )
target_link_libraries(test_fileformat libCADTest)

add_executable(test_level_of_details test_level_of_details.cpp  )
target_link_libraries(test_level_of_details libCADTest)

add_executable(test_meshoperations test_meshoperations.cpp  )
target_link_libraries(test_meshoperations libCADTest)

add_executable(test_fractal_tetrahedron test_fractal_tetrahedron.cpp  )
target_link_libraries(test_fractal_tetrahedron libCADTest)

add_executable(test_measurements test_measurements.cpp  )
target_link_libraries(test_measurements libCADTest)

add_executable(test_renderer test_renderer.cpp )
target_link_libraries(test_renderer libCADTest)

add_executable(test_bmpfile test_bmpfile.cpp  )
target_link_libraries(test_bmpfile libCADTest)

add_executable(test_stepfile test_stepfile.cpp  )
target_link_libraries(test_stepfile libCADTest)