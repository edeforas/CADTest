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

add_executable(test_simple_sphere test_simple_sphere.cpp  )
target_link_libraries(test_simple_sphere libCADTest)

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

add_executable(test_mandelbrot_mesh test_mandelbrot_mesh.cpp  )
target_link_libraries(test_mandelbrot_mesh libCADTest)

add_executable(test_stepfile test_stepfile.cpp  )
target_link_libraries(test_stepfile libCADTest)

add_executable(test_nurbscurve test_nurbscurve.cpp  )
target_link_libraries(test_nurbscurve libCADTest)

add_executable(test_nurbsutil test_nurbsutil.cpp  )
target_link_libraries(test_nurbsutil libCADTest)

add_executable(test_nurbsfactory test_nurbsfactory.cpp  )
target_link_libraries(test_nurbsfactory libCADTest)

add_executable(test_nurbssurface test_nurbssurface.cpp  )
target_link_libraries(test_nurbssurface libCADTest)

add_executable(test_nurbsextrude test_nurbsextrude.cpp  )
target_link_libraries(test_nurbsextrude libCADTest)

add_executable(test_nurbsruled test_nurbsruled.cpp  )
target_link_libraries(test_nurbsruled libCADTest)

add_executable(test_nurbsrevolve test_nurbsrevolve.cpp  )
target_link_libraries(test_nurbsrevolve libCADTest)

add_executable(test_solid test_solid.cpp  )
target_link_libraries(test_solid libCADTest)

add_test(test_geometry test_geometry)
add_test(test_bmpfile test_bmpfile)
add_test(test_mandelbrot_mesh test_mandelbrot_mesh)
add_test(test_measurements test_measurements)
add_test(test_bodyfactory test_bodyfactory)
add_test(test_level_of_details test_level_of_details)
add_test(test_simple_sphere test_simple_sphere)
add_test(test_fractal_tetrahedron test_fractal_tetrahedron)

add_test(test_nurbscurve test_nurbscurve)
add_test(test_nurbsutil test_nurbsutil)
add_test(test_nurbfactory test_nurbsfactory)
add_test(test_nurbssurface test_nurbssurface)
add_test(test_nurbsextrude test_nurbsextrude)
add_test(test_nurbsruled test_nurbsruled)
add_test(test_nurbsrevolve test_nurbsrevolve)
add_test(test_solid test_solid)

add_test(test_renderer test_renderer)