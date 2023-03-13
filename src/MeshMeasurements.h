#ifndef MeshMeasurements_
#define MeshMeasurements_

class Mesh;

///////////////////////////////////////////////////////////////////////////
class MeshMeasurements
{
public:
    static bool has_no_self_intersections(const Mesh& m); //todo
    static bool has_no_degenerated_triangles(const Mesh& m); //degenerated= zero surface triangles
    static bool is_closed(const Mesh& m); //not closed == triangles missing
    static bool is_oriented_outside(const Mesh& m); //volume is positive
    static bool has_no_isolated_vertices(const Mesh& m); // all vertices are associated with triangles
    static bool has_no_duplicated_vertices(const Mesh& m); //in the 10e-10 distance
    static bool has_no_short_edges(const Mesh& m); //shorte edges lower than 10e-10

    static bool is_clean(const Mesh& m); // all of the above

    static double volume(const Mesh& m);
    static double surface(const Mesh& m);

};
///////////////////////////////////////////////////////////////////////////

#endif