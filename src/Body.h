#ifndef _Body_
#define _Body_

#include "Mesh.h"
#include "Transform.h"
#include "Face.h"

#include <vector>
using namespace std;

// todo: clean up
#define RGB(a,b,c) ((a<<16)+(b<<8)+c)

///////////////////////////////////////////////////////////////////////////
class Body
{
public:
    Body();
    virtual ~Body();
    void clear();

    Transform& transform();
    virtual void set_mesh_precision(int iNbSegments);
    void set_color(int iColor);
    
    virtual void compute_mesh();

    void add_face(const Face& f); 
    vector<Face>& faces();

    const Mesh& mesh();

protected:
    Mesh _mesh;
    int _iNbSegments;
    Transform _transform;
    int _iColor; // -1 for no custom color
	
	vector<Face> _faces;
};
///////////////////////////////////////////////////////////////////////////

#endif