#ifndef _BodyUnion_
#define _BodyUnion_

#include "Body.h"

///////////////////////////////////////////////////////////////////////////
class BodyUnion: public Body
{
public:
    BodyUnion();
    virtual ~BodyUnion() override;

    void set(Body& A,Body& B);

    virtual void compute_mesh() override;

private:
    Body* _A;
    Body* _B;
};
///////////////////////////////////////////////////////////////////////////

#endif