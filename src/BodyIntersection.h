#ifndef BodyIntersection_
#define BodyIntersection_

#include "Body.h"

///////////////////////////////////////////////////////////////////////////
class BodyIntersection: public Body
{
public:
    BodyIntersection();
    virtual ~BodyIntersection() override;

    void set(Body& A,Body& B);

    virtual void compute_mesh() override;

private:
    Body* _A;
    Body* _B;
};
///////////////////////////////////////////////////////////////////////////

#endif