#include "CPrimitives.h"
#include "Triangle.h"
#include "CBlending.h"
#include "CSmoother.h"
#include "CMove.h"
#include "CObjects.h"
#include "COrthoGraphic.h"
#include "CModelviewProjection.h"
#include "CSphereWorld.h"
#include "CPyramid.h"
#include "CTunnel.h"

int main(int argc, char* argv[])
{
//    CPrimitives p(argc, argv);
//    p.mainLoop();
//    Triangle t(argc, argv);
//    t.mainLoop();
//    CBlending b(argc, argv);
//    b.mainLoop();
//    CSmoother s(argc, argv);
//    s.mainLoop();
//    CMove m(argc, argv);
//    m.mainLoop();
//    CObjects o(argc, argv);
//    o.mainLoop();
//    COrthoGraphic og(argc, argv);
//    og.mainLoop();
//    CModelviewProjection mp(argc, argv);
//    mp.mainLoop();
//    CSphereWorld sw(argc, argv);
//    sw.mainLoop();
//    CPyramid pyramid(argc, argv);
//    pyramid.mainLoop();
    CTunnel tunnel(argc, argv);
    tunnel.mainLoop();
    
    return 0;
}
