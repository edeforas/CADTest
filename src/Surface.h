#ifndef Surface_
#define Surface_

#include "Mesh.h"

///////////////////////////////////////////////////////////////////////////
class Surface
{
public:
    Surface();
    virtual ~Surface();

    void set_color(int iColor);

    virtual void add_to_mesh(Mesh& m,int iNbSegments)=0;

private:
    int _iColor;
};
///////////////////////////////////////////////////////////////////////////

#endif