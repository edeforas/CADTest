#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "StepFile.h"
#include "NurbsSurface.h"
#include "NurbsSolid.h"

namespace StepFile
{   /*
    class StepLine
    {
    public:
        StepLine(const string& s)
        {
            from_string(s);
        }

        void from_string(const string& s)
        {
            if (s[0] != '#')
                return;
            int iPosEqual = s.find('=');
            _id = atoi(s.substr(1, iPosEqual).c_str());

        }

        int _id;
        //string _type;
    };
    
    bool save(const string& filename, const Body& body)
    {
        ofstream f(filename);
        if (!f)
            return false;

        return false;
    }
    ///////////////////////////////////////////////////////////////////////////
	bool load(const string& filename, Body& body)
    {
        body.clear();
        ifstream f(filename);
        if (!f)
            return false;

        vector<StepLine> vs;

        bool bDataReady = false;

        // read all lines
        while (!f.eof())
        {
            string sLine; //,sType;
            getline(f, sLine);

            if (sLine.size() == 0)
                continue;

            //skip header
            if (sLine == "DATA;")
                bDataReady = true;
            if (bDataReady == false)
                continue;

            //read full line
            while (sLine[sLine.size() - 1] != ';')
            {
                string s;
                if (f.eof())
                    return false;
                getline(f, s);
                sLine += s;
            }

            vs.push_back(StepLine(sLine));
        }

        return true;
    }
    ///////////////////////////////////////////////////////////////////////////
    */
}

StepWriter::StepWriter():
    _iItemIndex(0)
{
}

void StepWriter::write_header()
{
    _f << "ISO-10303-21;" << endl;
    _f << "HEADER;" << endl;
    _f << "FILE_DESCRIPTION((''),'2;1');" << endl;
    _f << "FILE_NAME('" << _sNameFile << "','',(''),(''), '', 'CADTest', '');" << endl;
    _f << "FILE_SCHEMA(('AUTOMOTIVE_DESIGN { 1 0 10303 214 3 1 1 }'));" << endl;
    _f << "ENDSEC;" << endl;

    _f << "DATA;" << endl;
}

void StepWriter::write_footer()
{
    _f << "ENDSEC;" << endl;
    _f << "END-ISO-10303-21;" << endl;
}

StepWriter::~StepWriter()
{
    if (_f.is_open())
        close();
}

void StepWriter::open(const string& filename)
{
    _iItemIndex = 0;
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

int StepWriter::write_cartesian_point(const Point3& p)
{
    _iItemIndex++;
    _f << "#" << _iItemIndex << "=CARTESIAN_POINT('',(" << p.x() << "," << p.y() << "," << p.z() << "));" << endl;
    return _iItemIndex;
}

void StepWriter::write(const NurbsSurface& n)
{
    int iPointIndex = _iItemIndex;
    const auto& vp = n.points();
    for (const auto& p : vp)
        write_cartesian_point(p);

    _iItemIndex++;
    _f << "#" << _iItemIndex << "=UNIFORM_SURFACE('','',3,3,(";
//    _f << "#" << _iItemIndex << " = B_SPLINE_SURFACE_WITH_KNOTS('','',3,3,(";
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
            _f << ",";
    }

    _f << ".UNSPECIFIED.,.T.,.T.,.F.";
    _f << "); " << endl;

    _f << "#" << _iItemIndex+1 << "=ADVANCED_FACE('', '', #" << _iItemIndex << ", .T.)"<< endl;
    _iItemIndex++;
    _f << "#" << _iItemIndex+1 << "=CLOSED_SHELL('',(#" << _iItemIndex << "));" << endl;
    _iItemIndex++;

    _f << "#302 = (GEOMETRIC_REPRESENTATION_CONTEXT(3), GLOBAL_UNCERTAINTY_ASSIGNED_CONTEXT((#300)), GLOBAL_UNIT_ASSIGNED_CONTEXT((#304, #306, #307)), REPRESENTATION_CONTEXT('', '3D'));" << endl;
    _f << "#304 = (LENGTH_UNIT(), NAMED_UNIT(*), SI_UNIT(.MILLI., .METRE.));" << endl;
    _f << "#308 = SHAPE_DEFINITION_REPRESENTATION(#309, #310);" << endl;
    _f << "#309 = PRODUCT_DEFINITION_SHAPE('', $, #312);" << endl;
    _f << "#310 = SHAPE_REPRESENTATION('', (#41), #302);" << endl;
    _f << "#311 = PRODUCT_DEFINITION_CONTEXT('part definition', #316, 'design');" << endl;
    _f << "#312 = PRODUCT_DEFINITION('(Unsaved)', '(Unsaved)', #313, #311);" << endl;
    _f << "#313 = PRODUCT_DEFINITION_FORMATION('', $, #318);" << endl;

}

void StepWriter::write(const NurbsSolid& n)
{
    for (const auto& f : n.surfaces())
        write(f);
}
///////////////////////////////////////////////////////////////////////////