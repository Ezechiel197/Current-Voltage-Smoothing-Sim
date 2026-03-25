#include "pch.h"
#include "CapacitorPilotDesign.h"
#include "Controller.h"

static inline int imin(int a, int b) { return (a < b) ? a : b; }
static inline int imax(int a, int b) { return (a > b) ? a : b; }

CCapacitorPilotDesign::CCapacitorPilotDesign(CController* _pCtr)
{
    pCtr = _pCtr;
}

CCapacitorPilotDesign::~CCapacitorPilotDesign() {}

void CCapacitorPilotDesign::draw(CDC* dc)
{
    if (!dc || !pCtr) return;

    const CPoint org = pCtr->getOrg();
    const CPoint act = pCtr->getAct();

    const int hotW = pCtr->getHotWidth();
    const int hotH = pCtr->getHotHeight();
    const int minPx = pCtr->getMinPx();
    const int maxPx = pCtr->getMaxPx();


    const int xFactor = (hotW >= 10) ? (hotW / 10) : 1;
    const int bias = 6 * xFactor;

    const int yUpperTop = org.y - hotH / 2;
    const int yUpperBottom = org.y - hotH / 6;
    const int yLowerTop = org.y + hotH / 6;
    const int yLowerBottom = org.y + hotH / 2;

    CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
    CPen* oldPen = dc->SelectObject(&pen);

    CBrush black(RGB(0, 0, 0));
    CBrush* oldBrush = dc->SelectObject(&black);

    // schwarze Platten 
    dc->Rectangle(org.x - bias, yUpperTop, act.x, yUpperBottom);
    dc->Rectangle(2 * org.x - act.x - hotW / 2, yUpperTop, org.x - bias, yUpperBottom);

    dc->Rectangle(org.x - bias, yLowerTop, act.x, yLowerBottom);
    dc->Rectangle(2 * org.x - act.x - hotW / 2, yLowerTop, org.x - bias, yLowerBottom);

    dc->SetBkMode(TRANSPARENT);
    dc->TextOut(org.x + 5, yUpperBottom + 20, CString(_T("C")));

    //roter Griff
    CBrush red(RGB(255, 0, 0));
    dc->SelectObject(&red);
    dc->Rectangle(act.x - hotW / 2, org.y - hotH / 2, act.x + hotW / 2, org.y - hotH / 6);
    dc->Rectangle(act.x - hotW / 2, org.y + hotH / 6, act.x + hotW / 2, org.y + hotH / 2);


    dc->SelectObject(oldBrush);
    dc->SelectObject(oldPen);
}