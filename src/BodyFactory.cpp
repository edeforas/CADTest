#include "BodyFactory.h"

#include "MeshTessellate.h"

#include <cmath>
using namespace std;

namespace BodyFactory
{
	///////////////////////////////////////////////////////////////////////////
	Tetrahedron::Tetrahedron(double dSize)
	{
		_size = dSize;
	}
	void Tetrahedron::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		_mesh.add_vertex(_size, _size, _size);
		_mesh.add_vertex(-_size, -_size, _size);
		_mesh.add_vertex(_size, -_size, -_size);
		_mesh.add_vertex(-_size, _size, -_size);

		_mesh.add_triangle(0, 1, 2);
		_mesh.add_triangle(1, 3, 2);
		_mesh.add_triangle(0, 3, 1);
		_mesh.add_triangle(0, 2, 3);

		_transform.apply(_mesh);
	}
	///////////////////////////////////////////////////////////////////////////
	Box::Box(double xSize, double ySize, double zSize)
	{
		_xSize = xSize; _ySize = ySize; _zSize = zSize;
	}
	void Box::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		double x = _xSize * 0.5;
		double y = _ySize * 0.5;
		double z = _zSize * 0.5;

		_mesh.add_vertex(x, y, z);
		_mesh.add_vertex(-x, y, z);
		_mesh.add_vertex(-x, -y, z);
		_mesh.add_vertex(x, -y, z);
		_mesh.add_vertex(x, y, -z);
		_mesh.add_vertex(-x, y, -z);
		_mesh.add_vertex(-x, -x, -z);
		_mesh.add_vertex(x, -x, -z);

		_mesh.add_quad(0, 1, 2, 3);
		_mesh.add_quad(7, 6, 5, 4);
		_mesh.add_quad(4, 5, 1, 0);
		_mesh.add_quad(3, 2, 6, 7);
		_mesh.add_quad(5, 6, 2, 1);
		_mesh.add_quad(0, 3, 7, 4);

		_transform.apply(_mesh);
	}
	///////////////////////////////////////////////////////////////////////////
	Octahedron::Octahedron(double dSize)
	{
		_size = dSize;
	}
	void Octahedron::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		_mesh.add_vertex(_size, 0, 0);
		_mesh.add_vertex(0., _size, 0);
		_mesh.add_vertex(0., 0., _size);
		_mesh.add_vertex(-_size, 0, 0);
		_mesh.add_vertex(0, -_size, 0.);
		_mesh.add_vertex(0., 0, -_size);

		_mesh.add_triangle(0, 1, 2);
		_mesh.add_triangle(1, 0, 5);
		_mesh.add_triangle(2, 1, 3);
		_mesh.add_triangle(0, 2, 4);
		_mesh.add_triangle(4, 3, 5);
		_mesh.add_triangle(3, 4, 2);
		_mesh.add_triangle(5, 3, 1);
		_mesh.add_triangle(4, 5, 0);

		_transform.apply(_mesh);
	}
	///////////////////////////////////////////////////////////////////////////
	Dodecahedron::Dodecahedron(double dSize)
	{
		_size = dSize;
	}
	void Dodecahedron::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		// coordinate from: https://en.wikipedia.org/wiki/Regular_dodecahedron

		double u = _size;
		double t1 = (std::sqrt(5.) + 1.) / 2.;
		double t2 = 1./t1;
		t1*=_size;
		t2*=_size;

		_mesh.add_vertex(u, u, u);
		_mesh.add_vertex(u, u, -u);
		_mesh.add_vertex(u, -u, u);
		_mesh.add_vertex(u, -u, -u);
		_mesh.add_vertex(-u, u, u);
		_mesh.add_vertex(-u, u, -u);
		_mesh.add_vertex(-u, -u, u);
		_mesh.add_vertex(-u, -u, -u);

		_mesh.add_vertex(0, t1, t2);
		_mesh.add_vertex(0, t1, -t2);
		_mesh.add_vertex(0, -t1, t2);
		_mesh.add_vertex(0, -t1, -t2);

		_mesh.add_vertex(t2, 0, t1);
		_mesh.add_vertex(t2, 0, -t1);
		_mesh.add_vertex(-t2, 0, t1);
		_mesh.add_vertex(-t2, 0, -t1);

		_mesh.add_vertex(t1, t2, 0); 
		_mesh.add_vertex(t1, -t2, 0);
		_mesh.add_vertex(-t1, t2, 0);
		_mesh.add_vertex(-t1, -t2, 0);

		_mesh.add_pentagon(0, 12, 2, 17, 16);
		_mesh.add_pentagon(19, 18, 5, 15, 7);

		_mesh.add_pentagon(12, 0, 8, 4, 14);
		_mesh.add_pentagon(13, 3, 11, 7, 15);

		_mesh.add_pentagon(2, 12, 14, 6, 10);
		_mesh.add_pentagon(9, 1, 13, 15, 5);

		_mesh.add_pentagon(18, 19, 6, 14, 4);
		_mesh.add_pentagon(3, 13, 1, 16, 17);
	
		_mesh.add_pentagon(1, 9, 8, 0, 16);
		_mesh.add_pentagon(19, 7, 11, 10, 6);
		
		_mesh.add_pentagon(18, 4, 8, 9, 5);
		_mesh.add_pentagon(2, 10, 11, 3, 17);

		_transform.apply(_mesh);
	}
	///////////////////////////////////////////////////////////////////////////
	Icosahedron::Icosahedron(double dSize)
	{
		_size = dSize;
	}
	void Icosahedron::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		// from "Beyond the Third Dimension" by Banchoff, p.168.
		double u = _size;
		double t = (std::sqrt(5.) - 1.) / 2.*_size;

		_mesh.add_vertex(u, 0., t); //0
		_mesh.add_vertex(u, 0., -t);
		_mesh.add_vertex(-u, 0., t);
		_mesh.add_vertex(-u, 0., -t);

		_mesh.add_vertex(0., t, u); //4
		_mesh.add_vertex(0., -t, u);
		_mesh.add_vertex(0., t, -u);
		_mesh.add_vertex(0., -t, -u);

		_mesh.add_vertex(t, u, 0.); //8
		_mesh.add_vertex(-t, u, 0.);
		_mesh.add_vertex(t, -u, 0.);
		_mesh.add_vertex(-t, -u, 0.);

		_mesh.add_triangle(0, 1, 8);
		_mesh.add_triangle(0, 10, 1);
		_mesh.add_triangle(2, 3, 11);
		_mesh.add_triangle(2, 9, 3);

		_mesh.add_triangle(4, 5, 0);
		_mesh.add_triangle(4, 2, 5);
		_mesh.add_triangle(6, 7, 3);
		_mesh.add_triangle(6, 1, 7);

		_mesh.add_triangle(8, 9, 4);
		_mesh.add_triangle(8, 6, 9);
		_mesh.add_triangle(10, 11, 7);
		_mesh.add_triangle(10, 5, 11);

		_mesh.add_triangle(0, 8, 4);
		_mesh.add_triangle(3, 7, 11);

		_mesh.add_triangle(10, 0, 5);
		_mesh.add_triangle(9, 6, 3);

		_mesh.add_triangle(1, 6, 8);
		_mesh.add_triangle(2, 11, 5);

		_mesh.add_triangle(2, 4, 9);
		_mesh.add_triangle(1, 10, 7);

		_transform.apply(_mesh);
	}
	///////////////////////////////////////////////////////////////////////////
	Cylinder::Cylinder(double height, double diameter)
	{
		_height = height; _diameter = diameter;
	}
	void Cylinder::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		double PI = 3.14159265358979323846264338; // TODO
		double z = _height / 2.;

		int iNbSegmentLongitude = _iNbSegments / 2;
		// create vertices
		for (int i = 0; i < iNbSegmentLongitude; i++)
		{
			double x = std::cos((double)i / iNbSegmentLongitude * 2. * PI) * _diameter / 2.;
			double y = std::sin((double)i / iNbSegmentLongitude * 2. * PI) * _diameter / 2.;

			_mesh.add_vertex(x, y, z);
			_mesh.add_vertex(x, y, -z);
		}
		_mesh.add_vertex(0, 0, z);
		_mesh.add_vertex(0, 0, -z);

		// associates triangles, edge 
		for (int i = 0; i < iNbSegmentLongitude - 1; i++)
		{
			_mesh.add_quad(2 * i, 2 * i + 1, 2 * i + 3, 2 * i + 2);
		}
		_mesh.add_quad(2 * iNbSegmentLongitude - 2, 2 * iNbSegmentLongitude - 1, 1, 0);

		// associates triangles, up face 
		for (int i = 0; i < iNbSegmentLongitude; i++)
		{
			_mesh.add_triangle(iNbSegmentLongitude * 2, 2 * i, 2 * i + 2);
		}
		_mesh.add_triangle(iNbSegmentLongitude * 2, 2 * iNbSegmentLongitude - 2, 0);

		// associates triangles, down face 
		for (int i = 0; i < iNbSegmentLongitude; i++)
		{
			_mesh.add_triangle(iNbSegmentLongitude * 2 + 1, 2 * i + 3, 2 * i + 1);
		}
		_mesh.add_triangle(iNbSegmentLongitude * 2 + 1, 1, 2 * iNbSegmentLongitude - 1);

		_transform.apply(_mesh);
	}
	///////////////////////////////////////////////////////////////////////////
	SphereGeodesic::SphereGeodesic(double radius)
	{
		_radius = radius;
	}
	void SphereGeodesic::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		Icosahedron ico(1.);

		MeshTessellate mt;
		mt.compute(ico.mesh(), _iNbSegments, _mesh);

		for (int i = 0; i < _mesh.nb_vertices(); i++)
		{
			Point3 v;
			_mesh.get_vertex(i, v);
			_mesh.set_vertex(i,v.normalized()* _radius);
		}

		_transform.apply(_mesh);
	}
	///////////////////////////////////////////////////////////////////////////
	SphereUV::SphereUV(double radius):Body()
	{
		_radius = radius;
	}
	void SphereUV::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		double PI = 3.14159265358979323846264338; // TODO

		int iNbSegmentLongitude = _iNbSegments;
		int iNbSegmentLatitude = _iNbSegments/2;

		// create vertices
		for (int longitude = 0; longitude < iNbSegmentLongitude; longitude++)
		{
			double upi = (double)longitude / iNbSegmentLongitude * 2. * PI;

			for (int latitude = 1; latitude < iNbSegmentLatitude; latitude++)
			{
				double vpi = (double)latitude / iNbSegmentLatitude * PI;

				// compute parametric point from: https://en.wikipedia.org/wiki/Sphere
				Point3 p;
				p._x = _radius * std::sin(vpi) * std::cos(upi);
				p._y = _radius * std::sin(vpi) * std::sin(upi);
				p._z = _radius * std::cos(vpi);

				_mesh.add_vertex(p);
			}
		}
		_mesh.add_vertex(0, 0, _radius); // pole north
		_mesh.add_vertex(0, 0, -_radius); //pole south

		// associates quads to vertices
		int iNbVertexLatitude = iNbSegmentLatitude - 1; //poles removed
		//int iNbVertex = _mesh.nb_vertices()-2; // poles removed
		int iPoleNorth = _mesh.nb_vertices() - 2;
		int iPoleSouth= _mesh.nb_vertices() - 1;

		for (int longitude = 0; longitude < iNbSegmentLongitude; longitude++)
		{
			// add first trig
			int iLongitude1 = longitude;
			int iLongitude2 = (longitude+1)% iNbSegmentLongitude;

			// make north pole
			_mesh.add_triangle(iPoleNorth, iLongitude1 * iNbVertexLatitude, iLongitude2 * iNbVertexLatitude);
			
			for (int latitude = 1; latitude < iNbVertexLatitude ; latitude++)
			{
				_mesh.add_quad(
					iLongitude1 * iNbVertexLatitude + latitude-1,
					iLongitude1 * iNbVertexLatitude + latitude,
					iLongitude2 * iNbVertexLatitude + latitude,
					iLongitude2 * iNbVertexLatitude + latitude - 1
					);
			}
			
			// make south pole
			_mesh.add_triangle( iLongitude1 * iNbVertexLatitude+ iNbVertexLatitude-1, iPoleSouth, iLongitude2 * iNbVertexLatitude+ iNbVertexLatitude-1);
		}

		_transform.apply(_mesh);
		add_face(Face(_mesh));
	}
	///////////////////////////////////////////////////////////////////////////
	Torus::Torus(double dMajorRadius, double dMinorRadius)
	{
		_dMajorRadius = dMajorRadius;	_dMinorRadius = dMinorRadius;
	}
	void Torus::compute_mesh()
	{
		if (!_mesh.empty())
			return;

		double PI = 3.14159265358979323846264338; // TODO

		int iNbSegmentLongitude = _iNbSegments;
		int iNbSegmentLatitude = _iNbSegments / 2;

		// create vertices
		for (int longitude = 0; longitude < iNbSegmentLongitude; longitude++) 
		{
			double upi = (double)longitude / iNbSegmentLongitude * 2. * PI;

			for (int latitude = 0; latitude < iNbSegmentLatitude; latitude++)
			{
				double vpi = (double)latitude / iNbSegmentLatitude * 2. * PI;

				// compute parametric point from: https://en.wikipedia.org/wiki/Torus
				Point3 p;
				p._x = (_dMajorRadius + _dMinorRadius * std::cos(vpi)) * std::cos(upi);
				p._y = (_dMajorRadius + _dMinorRadius * std::cos(vpi)) * std::sin(upi);
				p._z = _dMinorRadius * std::sin(vpi);

				_mesh.add_vertex(p);
			}
		}

		// associates quads
		for (int longitude = 0; longitude < iNbSegmentLongitude; longitude++)
		{
			for (int latitude = 0; latitude < iNbSegmentLatitude; latitude++)
			{
				int longitude2 = (longitude + 1) % iNbSegmentLongitude;
				int latitude2 = (latitude + 1) % iNbSegmentLatitude;
				_mesh.add_quad(
					longitude2 * iNbSegmentLatitude + latitude,
					longitude2 * iNbSegmentLatitude + latitude2,
					longitude * iNbSegmentLatitude + latitude2,
					longitude * iNbSegmentLatitude + latitude);
			}
		}

		_transform.apply(_mesh);
	}
	///////////////////////////////////////////////////////////////////////////
}
