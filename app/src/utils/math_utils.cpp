#include "math_utils.h"
#include "fpoint.h"
#include "fpointarray.h"

FPoint getMaxClipF(const FPointArray* clip)
{
    FPoint np;
    FPoint rp;
    double mx = 0;
    double my = 0;
    int clipSize = clip->size();
    for (int i = 0; i < clipSize; ++i)
    {
        np = clip->point(i);
        if (clip->isMarker(i))
            continue;
        if (np.x() > mx)
            mx = np.x();
        if (np.y() > my)
            my = np.y();
    }
    rp.setXY(mx, my);
    return rp;
}

FPoint getMinClipF(const FPointArray* clip)
{
    FPoint np;
    FPoint rp;
    double mx = std::numeric_limits<double>::max();
    double my = std::numeric_limits<double>::max();
    int clipSize = clip->size();
    for (int i = 0; i < clipSize; ++i)
    {
        np = clip->point(i);
        if (clip->isMarker(i))
            continue;
        if (np.x() < mx)
            mx = np.x();
        if (np.y() < my)
            my = np.y();
    }
    rp.setXY(mx, my);
    return rp;
}
