#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "StepFile.h"
#include "NurbsSurface.h"
#include "NurbsSolid.h"

namespace StepFile
{

}

StepWriter::StepWriter() :
	_iItemIndent(10)
{
}

void StepWriter::write_header()
{
	_f << "ISO-10303-21;" << endl;
	_f << "HEADER;" << endl;
	_f << "FILE_SCHEMA(('AUTOMOTIVE_DESIGN { 1 0 10303 214 3 1 1 }'));" << endl;
	_f << "ENDSEC;" << endl << endl;

	_f << "DATA;" << endl;

	_f << "#10 = SHAPE_DEFINITION_REPRESENTATION(#11, #12);" << endl;
	_f << "#11 = PRODUCT_DEFINITION_SHAPE('', $, #14);" << endl;
	_f << "#12 = SHAPE_REPRESENTATION('', (), '');" << endl;
	_f << "#13 = PRODUCT_DEFINITION_CONTEXT('part definition', '', 'design');" << endl;
	_f << "#14 = PRODUCT_DEFINITION('(Unsaved)', '(Unsaved)', '', #13);" << endl << endl;

	_iItemIndent = 20;
}

void StepWriter::write_footer()
{
	_f << "ENDSEC;" << endl;
	_f << "END-ISO-10303-21;";
}

StepWriter::~StepWriter()
{
	if (_f.is_open())
		close();
}

void StepWriter::open(const string& filename)
{
	_iItemIndent = 10;
	_sNameFile = filename;
	_f.open(filename);
	write_header();
}

bool StepWriter::is_open()
{
	return _f.is_open();
}

void StepWriter::close()
{
	if (!_f.is_open())
		return;

	write_footer();
	_f.close();
}

void StepWriter::write_cartesian_point(const Point3& p)
{
	_f << "#" << _iItemIndent << "=CARTESIAN_POINT('',(" << p.x() << "," << p.y() << "," << p.z() << "));" << endl;
	_iItemIndent++;
}

void StepWriter::write(const NurbsSurface& n)
{
	int iPointIndex = _iItemIndent;
	const auto& vp = n.points();
	for (const auto& p : vp)
		write_cartesian_point(p);

	int itemFace = _iItemIndent;
	_f << endl << "#" << _iItemIndent << "=(" << endl << "BOUNDED_SURFACE()" << endl;
	_iItemIndent++;

	//write control points
	_f << "B_SPLINE_SURFACE(" << n.degree_u() << "," << n.degree_v() << ",(" << endl;
	for (int j = 0; j < n.nb_points_v(); j++)
	{
		_f << "(";
		for (int i = 0; i < n.nb_points_u(); i++)
		{
			_f << "#" << iPointIndex;
			iPointIndex++;
			if (i + 1 != n.nb_points_u())
				_f << ",";
		}
		_f << ")";
		if (j + 1 != n.nb_points_v())
			_f << "," << endl;
	}

	string sClosedU = n.is_closed_u() ? ".T." : ".F.";
	string sClosedV = n.is_closed_v() ? ".T." : ".F.";
	_f << endl << "),.UNSPECIFIED.," << sClosedU << "," << sClosedV << ",.F.";
	_f << ")" << endl;

	//write knots
	const auto& ku = n.knots_u();
	const auto& kv = n.knots_v();
	_f << "B_SPLINE_SURFACE_WITH_KNOTS(" << endl;

	//write knot multiplicity
	_f << "(" << n.degree_u() + 1 << ",";
	for (int i = 0; i < ku.size() - n.degree_u() * 2 - 2; i++)
		_f << "1,";
	_f << n.degree_u() + 1 << ")," << endl;

	_f << "(" << n.degree_v() + 1 << ",";
	for (int i = 0; i < kv.size() - n.degree_v() * 2 - 2; i++)
		_f << "1,";
	_f << n.degree_v() + 1 << ")," << endl;
	_f << "(";

	//write knot values
	for (int i = n.degree_u(); i < ku.size() - n.degree_u(); i++)
	{
		_f << ku[i];
		if (i != ku.size() - n.degree_u() - 1)
			_f << ",";
	}
	_f << ")," << endl << "(";

	for (int i = n.degree_v(); i < kv.size() - n.degree_v(); i++)
	{
		_f << kv[i];
		if (i != kv.size() - n.degree_v() - 1)
			_f << ",";
	}
	_f << ")," << endl;

	_f << ".UNSPECIFIED.)";

	_f << endl << "GEOMETRIC_REPRESENTATION_ITEM()";

	//write weights
	_f << endl << "RATIONAL_B_SPLINE_SURFACE((" << endl;
	for (int j = 0; j < n.nb_points_v(); j++)
	{
		_f << "(";
		for (int i = 0; i < n.nb_points_u(); i++)
		{
			_f << n.weights()[n.nb_points_u() * j + i];
			if (i + 1 != n.nb_points_u())
				_f << ",";
		}
		_f << ")";
		if (j + 1 != n.nb_points_v())
			_f << "," << endl;
	}
	_f << endl << "))";

	_f << endl << "REPRESENTATION_ITEM('')" << endl;
	_f << "SURFACE()" << endl << ");" << endl << endl;

	_f << "#" << _iItemIndent << "=ADVANCED_FACE('', (), #" << itemFace << ", .T.);" << endl;
	_iItemIndent++;
	_f << "#" << _iItemIndent << "=CLOSED_SHELL('',(#" << _iItemIndent - 1 << "));" << endl;
	_iItemIndent++;
	_f << "#" << _iItemIndent << "=MANIFOLD_SOLID_BREP('',#" << _iItemIndent - 1 << ");" << endl;
	_iItemIndent++;
	_f << "#" << _iItemIndent << "=ADVANCED_BREP_SHAPE_REPRESENTATION('',(#" << _iItemIndent - 1 << "),'');" << endl;
	_iItemIndent++;
	_f << "#" << _iItemIndent << "=SHAPE_REPRESENTATION_RELATIONSHIP('','None',#12,#" << _iItemIndent - 1 << ");" << endl << endl;
	_iItemIndent++;
}

void StepWriter::write(const NurbsSolid& n)
{
	for (const auto& f : n.surfaces())
		write(f);
}
///////////////////////////////////////////////////////////////////////////