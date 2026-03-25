#include "pch.h"
#include "SteuerspannungDesign.h"

CSteuerspannungDesign::CSteuerspannungDesign(CController* _pCtr)
    : CAbstractView()
{
    pCtr = _pCtr;
    //pCtr->setOffsetY(0);
}

CSteuerspannungDesign::~CSteuerspannungDesign()
{
}

void CSteuerspannungDesign::draw(CDC* dc)
{

    if (!dc || !pCtr) return;

    const CPoint org = pCtr->getOrg();
    const CPoint act = pCtr->getAct();
    const int bodyW = 12; // Feste Körperbreite
    const int xC = org.x;

    //const bool isVertical = (abs(act.y - org.y) > abs(act.x - org.x));

    CPen penBleu(PS_SOLID, 2, RGB(0, 0, 255));
    dc->SelectObject(&penBleu);
    dc->SetBkMode(TRANSPARENT);
    dc->MoveTo(60, act.y);
    dc->LineTo(560, act.y);


    CPen penRed(PS_SOLID, 2, (RGB(255, 0, 0)));
    dc->SelectObject(&penRed);
    CBrush red(RGB(255, 0, 0));
    dc->SelectObject(&red);
    dc->BeginPath();
    dc->MoveTo(act);
    dc->LineTo(dc->GetCurrentPosition().x , dc->GetCurrentPosition().y + bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x - 3, dc->GetCurrentPosition().y );
    dc->LineTo(dc->GetCurrentPosition().x + bodyW / 2, dc->GetCurrentPosition().y + bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x + bodyW / 2, dc->GetCurrentPosition().y - bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x-3, dc->GetCurrentPosition().y);
    dc->LineTo(dc->GetCurrentPosition().x , dc->GetCurrentPosition().y - bodyW);
    dc->LineTo(dc->GetCurrentPosition().x + 3, dc->GetCurrentPosition().y);
    dc->LineTo(dc->GetCurrentPosition().x - bodyW / 2, dc->GetCurrentPosition().y - bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x - bodyW / 2, dc->GetCurrentPosition().y + bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x + 3, dc->GetCurrentPosition().y );
    dc->LineTo(dc->GetCurrentPosition().x , dc->GetCurrentPosition().y + bodyW / 2);
    dc->EndPath();
    dc->FillPath();

}