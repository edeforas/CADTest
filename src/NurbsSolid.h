#ifndef NurbsSolid_
#define NurbsSolid_

#include "NurbsSurface.h"

#include <vector>
using namespace std;


///////////////////////////////////////////////////////////////////////////
class NurbsSolid
{
public:
    NurbsSolid();
    virtual ~NurbsSolid();
    void clear();

    void add_surface(const NurbsSurface& ns); 
    vector<NurbsSurface>& surfaces();

private:
	vector<NurbsSurface> _surfaces;
};
///////////////////////////////////////////////////////////////////////////

#endif