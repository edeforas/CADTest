#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "StepFile.h"
#include "NurbsSurface.h"

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

StepWriter::StepWriter()
{

}

void StepWriter::write_header()
{
    _f << "ISO - 10303 - 21;" << endl;
    _f << "HEADER;" << endl;
    _f << "FILE_DESCRIPTION((''),'2;1');" << endl;
    _f << "FILE_NAME('" << _sNameFile << "','',(''),(''), '', 'CADTest', '');" << endl;
    _f << "FILE_SCHEMA(('AUTOMOTIVE_DESIGN { 1 0 10303 214 3 1 1 }'));" << endl;
    _f << "ENDSEC;" << endl;
}

void StepWriter::write_footer()
{
    _f << "END - ISO - 10303 - 21;" << endl;
}

StepWriter::~StepWriter()
{
    if (_f.is_open())
        close();
}

void StepWriter::open(const string& filename)
{
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
    write_footer();
    _f.close();
}

void StepWriter::write(const NurbsSurface& n)
{

}
///////////////////////////////////////////////////////////////////////////