#ifndef NurbsSolid_
#define NurbsSolid_

#include "NurbsSurface.h"

#include <vector>
using namespace std;
class Transform;

///////////////////////////////////////////////////////////////////////////
class NurbsSolid
{
public:
    NurbsSolid();
    virtual ~NurbsSolid();
    void clear();

    void add_surface(const NurbsSurface& ns);
    vector<NurbsSurface>& surfaces();
    const vector<NurbsSurface>& surfaces() const;

    void apply_transform(const Transform& t);

private:
	vector<NurbsSurface> _surfaces;
};
///////////////////////////////////////////////////////////////////////////

#endif