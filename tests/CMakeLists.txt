include_directories(../src)

add_executable(test_geometry test_geometry.cpp  )
target_link_libraries(test_geometry libCADTest)

add_executable(test_geometryutil test_geometryutil.cpp  )
target_link_libraries(test_geometryutil libCADTest)

add_executable(test_transform test_transform.cpp  )
target_link_libraries(test_transform libCADTest)

add_executable(test_meshfactory "test_meshfactory.cpp"  )
target_link_libraries(test_meshfactory libCADTest)

add_executable(test_smoothmeshfactory "test_smoothmeshfactory.cpp"  )
target_link_libraries(test_smoothmeshfactory libCADTest)

add_executable(test_fileformat test_fileformat.cpp  )
target_link_libraries(test_fileformat libCADTest)

add_executable(test_mesh_level_of_details test_mesh_level_of_details.cpp  )
target_link_libraries(test_mesh_level_of_details libCADTest)

add_executable(test_mesh_geosphere "test_mesh_geosphere.cpp"  )
target_link_libraries(test_mesh_geosphere libCADTest)

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

add_executable(test_mesh_mandelbrot test_mesh_mandelbrot.cpp  )
target_link_libraries(test_mesh_mandelbrot libCADTest)

add_executable(test_stepfile test_stepfile.cpp  )
target_link_libraries(test_stepfile libCADTest)

add_executable(test_quadbeziertriangle test_quadbeziertriangle.cpp  )
target_link_libraries(test_quadbeziertriangle libCADTest)

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

add_executable(test_nurbs_mandelbrot test_nurbs_mandelbrot.cpp  )
target_link_libraries(test_nurbs_mandelbrot libCADTest)


add_test(test_geometry test_geometry)
add_test(test_geometryutil test_geometryutil)
add_test(test_transform test_transform)
add_test(test_bmpfile test_bmpfile)
add_test(test_measurements test_measurements)
add_test(test_meshfactory test_meshfactory)
add_test(test_mesh_level_of_details test_mesh_level_of_details)
add_test(test_mesh_geosphere test_mesh_geosphere)
add_test(test_fractal_tetrahedron test_fractal_tetrahedron)
add_test(test_mesh_mandelbrot test_mesh_mandelbrot)

add_test(test_smoothmeshfactory test_smoothmeshfactory)
add_test(test_quadbeziertriangle test_quadbeziertriangle)

add_test(test_nurbscurve test_nurbscurve)
add_test(test_nurbsutil test_nurbsutil)
add_test(test_nurbfactory test_nurbsfactory)
add_test(test_nurbssurface test_nurbssurface)
add_test(test_nurbsextrude test_nurbsextrude)
add_test(test_nurbsruled test_nurbsruled)
add_test(test_nurbsrevolve test_nurbsrevolve)
add_test(test_nurbs_mandelbrot test_nurbs_mandelbrot)

add_test(test_renderer test_renderer)