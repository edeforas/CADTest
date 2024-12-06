#ifndef Solid_
#define Solid_

#include "NurbsSurface.h"

#include <vector>
using namespace std;


///////////////////////////////////////////////////////////////////////////
class Solid
{
public:
    Solid();
    virtual ~Solid();
    void clear();

    void add_surface(const NurbsSurface& ns); 
    vector<NurbsSurface>& surfaces();

private:
	vector<NurbsSurface> _surfaces;
};
///////////////////////////////////////////////////////////////////////////

#endif