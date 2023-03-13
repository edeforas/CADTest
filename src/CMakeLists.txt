set(CADTEST_FILES
		
	Geometry.cpp Geometry.h
	GeometryUtil.cpp GeometryUtil.h
	Transform.cpp Transform.h
	Face.cpp Face.h
	Solid.cpp Solid.h
	
	Mesh.cpp Mesh.h
	MeshFactory.cpp MeshFactory.h
	MeshKernel.cpp MeshKernel.h
	MeshKernelTIN.cpp MeshKernelTIN.h
	MeshKernelHalfEdge.cpp MeshKernelHalfEdge.h
	MeshKernelLinkedTriangles.cpp MeshKernelLinkedTriangles.h
	MeshMeasurements.cpp MeshMeasurements.h
	MeshUtil.cpp MeshUtil.h
	
	BezierUtil.cpp BezierUtil.h
	QuadBezierTriangle.cpp QuadBezierTriangle.h
	CubicBezierTriangles.cpp CubicBezierTriangles.h
	SmoothMesh.cpp SmoothMesh.h
	SmoothMeshFactory.cpp SmoothMeshFactory.h
	
	MeshTessellate.cpp MeshTessellate.h
	MeshBoolean.cpp MeshBoolean.h
	STLFile.cpp STLFile.h
	OBJFile.cpp OBJFile.h
	
	NurbsCurve.cpp NurbsCurve.h
	NurbsSurface.cpp NurbsSurface.h
	NurbsExtrude.cpp NurbsExtrude.h
	NurbsRuled.cpp NurbsRuled.h
	NurbsRevolve.cpp NurbsRevolve.h
	NurbsUtil.cpp NurbsUtil.h
	NurbsFactory.cpp NurbsFactory.h
	NurbsSolid.cpp NurbsSolid.h
	StepFile.cpp StepFile.h
	
	Renderer.cpp Renderer.h
	RendererCamera.cpp RendererCamera.h
	RendererLight.cpp RendererLight.h
	Image.h
	ImageGenerator.cpp ImageGenerator.h
	ImageIoBmp.cpp ImageIoBmp.h
	ImageUtil.cpp ImageUtil.h
	Color.h	
)

include_directories(.)
add_library( libCADTest STATIC ${CADTEST_FILES})