#include "SmoothMeshFactory.h"

#include "MeshUtil.h"

#include <cmath>
using namespace std;

#include "Transform.h"

namespace SmoothMeshFactory
{

	void create_tetrahedron(double dSize, SmoothMesh& m)
	{
		m.clear();

		Point3 p0(dSize, dSize, dSize);
		Point3 p1(-dSize, -dSize, dSize);
		Point3 p2(dSize, -dSize, -dSize);
		Point3 p3(-dSize, dSize, -dSize);

		m.add_flat_triangle(p0, p1, p2);
		m.add_flat_triangle(p1, p3, p2);
		m.add_flat_triangle(p0, p3, p1);
		m.add_flat_triangle(p0, p2, p3);
	}

	void create_box(double xSize, double ySize, double zSize, SmoothMesh& m)
	{
		m.clear();

		double x = xSize / 2.;
		double y = ySize / 2.;
		double z = zSize / 2.;

		Point3 p0(x, y, z);
		Point3 p1(-x, y, z);
		Point3 p2(-x, -y, z);
		Point3 p3(x, -y, z);
		Point3 p4(x, y, -z);
		Point3 p5(-x, y, -z);
		Point3 p6(-x, -y, -z);
		Point3 p7(x, -y, -z);

		m.add_flat_quad(p0, p1, p2, p3);
		m.add_flat_quad(p7, p6, p5, p4);
		m.add_flat_quad(p4, p5, p1, p0);
		m.add_flat_quad(p3, p2, p6, p7);
		m.add_flat_quad(p5, p6, p2, p1);
		m.add_flat_quad(p0, p3, p7, p4);
	}
	///////////////////////////////////////////////////////////////////////////

	void create_octahedron(double dSize, SmoothMesh& m)
	{
		m.clear();

		Point3 p0(dSize, 0, 0);
		Point3 p1(0., dSize, 0);
		Point3 p2(0., 0., dSize);
		Point3 p3(-dSize, 0, 0);
		Point3 p4(0, -dSize, 0.);
		Point3 p5(0., 0, -dSize);

		m.add_flat_triangle(p0, p1, p2);
		m.add_flat_triangle(p1, p0, p5);
		m.add_flat_triangle(p2, p1, p3);
		m.add_flat_triangle(p0, p2, p4);
		m.add_flat_triangle(p4, p3, p5);
		m.add_flat_triangle(p3, p4, p2);
		m.add_flat_triangle(p5, p3, p1);
		m.add_flat_triangle(p4, p5, p0);
	}

	void create_dodecahedron(double dSize, SmoothMesh& m)
	{
		m.clear();
		// coordinate from: https://en.wikipedia.org/wiki/Regular_dodecahedron

		double u = dSize;
		double t1 = (std::sqrt(5.) + 1.) / 2.;
		double t2 = 1. / t1;
		t1 *= dSize;
		t2 *= dSize;

		Point3 p0(u, u, u);
		Point3 p1(u, u, -u);
		Point3 p2(u, -u, u);
		Point3 p3(u, -u, -u);
		Point3 p4(-u, u, u);
		Point3 p5(-u, u, -u);
		Point3 p6(-u, -u, u);
		Point3 p7(-u, -u, -u);

		Point3 p8(0, t1, t2);
		Point3 p9(0, t1, -t2);
		Point3 p10(0, -t1, t2);
		Point3 p11(0, -t1, -t2);

		Point3 p12(t2, 0, t1);
		Point3 p13(t2, 0, -t1);
		Point3 p14(-t2, 0, t1);
		Point3 p15(-t2, 0, -t1);

		Point3 p16(t1, t2, 0);
		Point3 p17(t1, -t2, 0);
		Point3 p18(-t1, t2, 0);
		Point3 p19(-t1, -t2, 0);

		m.add_flat_pentagon(p0, p12, p2, p17, p16);
		m.add_flat_pentagon(p19, p18, p5, p15, p7);

		m.add_flat_pentagon(p12, p0, p8, p4, p14);
		m.add_flat_pentagon(p13, p3, p11, p7, p15);

		m.add_flat_pentagon(p2, p12, p14, p6, p10);
		m.add_flat_pentagon(p9, p1, p13, p15, p5);

		m.add_flat_pentagon(p18, p19, p6, p14, p4);
		m.add_flat_pentagon(p3, p13, p1, p16, p17);

		m.add_flat_pentagon(p1, p9, p8, p0, p16);
		m.add_flat_pentagon(p19, p7, p11, p10, p6);

		m.add_flat_pentagon(p18, p4, p8, p9, p5);
		m.add_flat_pentagon(p2, p10, p11, p3, p17);
	}


	void create_icosahedron(double dSize, SmoothMesh& m)
	{
		m.clear();

		// from "Beyond the Third Dimension" by Banchoff, p.168.
		double u = dSize;
		double t = (std::sqrt(5.) - 1.) / 2. * dSize;

		Point3 p0(u, 0., t); //0
		Point3 p1(u, 0., -t);
		Point3 p2(-u, 0., t);
		Point3 p3(-u, 0., -t);

		Point3 p4(0., t, u); //4
		Point3 p5(0., -t, u);
		Point3 p6(0., t, -u);
		Point3 p7(0., -t, -u);

		Point3 p8(t, u, 0.); //8
		Point3 p9(-t, u, 0.);
		Point3 p10(t, -u, 0.);
		Point3 p11(-t, -u, 0.);

		m.add_flat_triangle(p0, p1, p8);
		m.add_flat_triangle(p0, p10, p1);
		m.add_flat_triangle(p2, p3, p11);
		m.add_flat_triangle(p2, p9, p3);

		m.add_flat_triangle(p4, p5, p0);
		m.add_flat_triangle(p4, p2, p5);
		m.add_flat_triangle(p6, p7, p3);
		m.add_flat_triangle(p6, p1, p7);

		m.add_flat_triangle(p8, p9, p4);
		m.add_flat_triangle(p8, p6, p9);
		m.add_flat_triangle(p10, p11, p7);
		m.add_flat_triangle(p10, p5, p11);

		m.add_flat_triangle(p0, p8, p4);
		m.add_flat_triangle(p3, p7, p11);

		m.add_flat_triangle(p10, p0, p5);
		m.add_flat_triangle(p9, p6, p3);

		m.add_flat_triangle(p1, p6, p8);
		m.add_flat_triangle(p2, p11, p5);

		m.add_flat_triangle(p2, p4, p9);
		m.add_flat_triangle(p1, p10, p7);
	}

	void create_sphere(double dRadius, SmoothMesh& m)
	{
		m.clear();
		double d = dRadius;

		{
			QuadBezierTriangle st;
			st.set_points(Point3(d, 0, 0), Point3(0, d, 0), Point3(0, 0, d));
			st.set_control_points(Point3(d, d, 0), Point3(d, 0, d), Point3(0, d, d));
			m.add_triangle(st);
		}

		{
			QuadBezierTriangle st;
			st.set_points(Point3(-d, 0, 0), Point3(0, d, 0), Point3(0, 0, d));
			st.set_control_points(Point3(-d, d, 0), Point3(-d, 0, d), Point3(0, d, d));
			m.add_triangle(st);
		}

		{
			QuadBezierTriangle st;
			st.set_points(Point3(d, 0, 0), Point3(0, -d, 0), Point3(0, 0, d));
			st.set_control_points(Point3(d, -d, 0), Point3(d, 0, d), Point3(0, -d, d));
			m.add_triangle(st);
		}

		{
			QuadBezierTriangle st;
			st.set_points(Point3(d, 0, 0), Point3(0, d, 0), Point3(0, 0, -d));
			st.set_control_points(Point3(d, d, 0), Point3(d, 0, -d), Point3(0, d, -d));
			m.add_triangle(st);
		}

		{
			QuadBezierTriangle st;
			st.set_points(Point3(-d, 0, 0), Point3(0, -d, 0), Point3(0, 0, d));
			st.set_control_points(Point3(-d, -d, 0), Point3(-d, 0, d), Point3(0, -d, d));
			m.add_triangle(st);
		}

		{
			QuadBezierTriangle st;
			st.set_points(Point3(-d, 0, 0), Point3(0, -d, 0), Point3(0, 0, -d));
			st.set_control_points(Point3(-d, -d, 0), Point3(-d, 0, -d), Point3(0, -d, -d));
			m.add_triangle(st);
		}

		{
			QuadBezierTriangle st;
			st.set_points(Point3(-d, 0, 0), Point3(0, d, 0), Point3(0, 0, -d));
			st.set_control_points(Point3(-d, d, 0), Point3(-d, 0, -d), Point3(0, d, -d));
			m.add_triangle(st);
		}

		{
			QuadBezierTriangle st;
			st.set_points(Point3(d, 0, 0), Point3(0, -d, 0), Point3(0, 0, -d));
			st.set_control_points(Point3(d, -d, 0), Point3(d, 0, -d), Point3(0, -d, -d));
			m.add_triangle(st);
		}
	}


	/*
	void create_cylinder(double dHeight, double dRadius, int iNbSegments, SmoothMesh& m)
	{
		m.clear();

		double PI = 3.14159265358979323846264338; // TODO
		double z = dHeight / 2.;

		int iNbSegmentLongitude = 2 + 4 * iNbSegments;
		// create vertices
		for (int i = 0; i < iNbSegmentLongitude; i++)
		{
			double x = std::cos((double)i / iNbSegmentLongitude * 2. * PI) * dRadius;
			double y = std::sin((double)i / iNbSegmentLongitude * 2. * PI) * dRadius;

			m.add_vertex(x, y, z);
			m.add_vertex(x, y, -z);
		}
		m.add_vertex(0, 0, z);
		m.add_vertex(0, 0, -z);

		// associates triangles, edge
		for (int i = 0; i < iNbSegmentLongitude - 1; i++)
		{
			m.add_quad(2 * i, 2 * i + 1, 2 * i + 3, 2 * i + 2);
		}
		m.add_quad(2 * iNbSegmentLongitude - 2, 2 * iNbSegmentLongitude - 1, 1, 0);

		// associates triangles, up face
		for (int i = 0; i < iNbSegmentLongitude; i++)
		{
			m.add_triangle(iNbSegmentLongitude * 2, 2 * i, 2 * i + 2);
		}
		m.add_triangle(iNbSegmentLongitude * 2, 2 * iNbSegmentLongitude - 2, 0);

		// associates triangles, down face
		for (int i = 0; i < iNbSegmentLongitude; i++)
		{
			m.add_triangle(iNbSegmentLongitude * 2 + 1, 2 * i + 3, 2 * i + 1);
		}
		m.add_triangle(iNbSegmentLongitude * 2 + 1, 1, 2 * iNbSegmentLongitude - 1);
	}


	void create_torus(double dMajorRadius, double dMinorRadius, int iNbSegments, SmoothMesh& m)
	{
		m.clear();

		if (!m.empty())
			return;

		double PI = 3.14159265358979323846264338; // TODO

		int iNbSegmentLongitude = 2 + 4 * iNbSegments;
		int iNbSegmentLatitude = 2 + 4 + 4 * iNbSegments / 2;

		// create vertices
		for (int longitude = 0; longitude < iNbSegmentLongitude; longitude++)
		{
			double upi = (double)longitude / iNbSegmentLongitude * 2. * PI;

			for (int latitude = 0; latitude < iNbSegmentLatitude; latitude++)
			{
				double vpi = (double)latitude / iNbSegmentLatitude * 2. * PI;

				// compute parametric point from: https://en.wikipedia.org/wiki/Torus
				Point3 p;
				p._x = (dMajorRadius + dMinorRadius * std::cos(vpi)) * std::cos(upi);
				p._y = (dMajorRadius + dMinorRadius * std::cos(vpi)) * std::sin(upi);
				p._z = dMinorRadius * std::sin(vpi);

				m.add_vertex(p);
			}
		}

		// associates quads
		for (int longitude = 0; longitude < iNbSegmentLongitude; longitude++)
		{
			for (int latitude = 0; latitude < iNbSegmentLatitude; latitude++)
			{
				int longitude2 = (longitude + 1) % iNbSegmentLongitude;
				int latitude2 = (latitude + 1) % iNbSegmentLatitude;
				m.add_quad(
					longitude2 * iNbSegmentLatitude + latitude,
					longitude2 * iNbSegmentLatitude + latitude2,
					longitude * iNbSegmentLatitude + latitude2,
					longitude * iNbSegmentLatitude + latitude);
			}
		}
	}
*/
}








