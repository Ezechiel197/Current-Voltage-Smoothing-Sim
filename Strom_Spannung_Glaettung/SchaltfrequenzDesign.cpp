#include "pch.h"
#include "SchaltfrequenzDesign.h"

CSchaltfrequenzDesign::CSchaltfrequenzDesign(CController* _pCtr)
    : CAbstractView()
{
    pCtr = _pCtr;
    //pCtr->setOffsetY(0);
}

CSchaltfrequenzDesign::~CSchaltfrequenzDesign()
{
}

void CSchaltfrequenzDesign::draw(CDC* dc)
{

    if (!dc || !pCtr) return;

    const CPoint org = pCtr->getOrg();
    const CPoint act = pCtr->getAct();

    dc->SetBkMode(TRANSPARENT);


    const int bodyW = 12; // Feste Körperbreite

    CPen penRed(PS_SOLID, 2, (RGB(255, 0, 0)));
    dc->SelectObject(&penRed);
    CBrush red(RGB(0, 0, 0));
    dc->SelectObject(&red);
    dc->BeginPath();
    dc->MoveTo(act);
    dc->LineTo(dc->GetCurrentPosition().x + bodyW/2, dc->GetCurrentPosition().y);
    dc->LineTo(dc->GetCurrentPosition().x , dc->GetCurrentPosition().y-3);
    dc->LineTo(dc->GetCurrentPosition().x + bodyW / 2, dc->GetCurrentPosition().y + bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x - bodyW / 2, dc->GetCurrentPosition().y + bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x, dc->GetCurrentPosition().y - 3);
    dc->LineTo(dc->GetCurrentPosition().x - bodyW, dc->GetCurrentPosition().y);
    dc->LineTo(dc->GetCurrentPosition().x , dc->GetCurrentPosition().y+3);
    dc->LineTo(dc->GetCurrentPosition().x - bodyW / 2, dc->GetCurrentPosition().y - bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x + bodyW / 2, dc->GetCurrentPosition().y - bodyW / 2);
    dc->LineTo(dc->GetCurrentPosition().x, dc->GetCurrentPosition().y +3 );
    dc->LineTo(dc->GetCurrentPosition().x + bodyW / 2, dc->GetCurrentPosition().y );
    dc->EndPath();
    dc->FillPath();
    
}