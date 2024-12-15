#ifndef _MeshFactory_
#define _MeshFactory_

#include "Body.h"

namespace MeshFactory
{
    void create_tetrahedron(double dSize, Mesh& m);
    void create_box(double xSize, double ySize, double zSize, Mesh& m);

    ///////////////////////////////////////////////////////////////////////////
    class Box : public Body
    {
    public:
        explicit Box(double xSize, double ySize, double zSize);

        virtual void compute_mesh() override;

    private:
        double _xSize, _ySize, _zSize;
    };
    ///////////////////////////////////////////////////////////////////////////
    class Octahedron : public Body
    {
    public:
        explicit Octahedron(double dSize);

        virtual void compute_mesh() override;

    private:
        double _size;
    };
    ///////////////////////////////////////////////////////////////////////////
    class Dodecahedron : public Body
    {
    public:
        explicit Dodecahedron(double dSize);

        virtual void compute_mesh() override;

    private:
        double _size;
    };    
	///////////////////////////////////////////////////////////////////////////
    class Icosahedron : public Body
    {
    public:
        explicit Icosahedron(double dSize);

        virtual void compute_mesh() override;

    private:
        double _size;
    };
    ///////////////////////////////////////////////////////////////////////////
    class Cylinder : public Body
    {
    public:
        explicit Cylinder(double height, double radius);

        virtual void compute_mesh() override;

    private:
        double _height, _radius;
    };
    ///////////////////////////////////////////////////////////////////////////
    class SphereGeodesic : public Body
    {
    public:
        explicit SphereGeodesic(double radius);

        virtual void compute_mesh() override;

    private:
        double _radius;
    };
    ///////////////////////////////////////////////////////////////////////////
    class SphereUV : public Body
    {
    public:
        explicit SphereUV(double radius);

        virtual void compute_mesh() override;

    private:
        double _radius;
    };
    ///////////////////////////////////////////////////////////////////////////
    class Torus : public Body
    {
    public:
        Torus(double dMajorRadius, double dMinorRadius);

        virtual void compute_mesh() override;

    private:
        double _dMajorRadius,_dMinorRadius;
    };
    ///////////////////////////////////////////////////////////////////////////

}
#endif