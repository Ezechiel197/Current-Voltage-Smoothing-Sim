#include "pch.h"
#include "Last_WiderstandDesign.h"

CLast_WiderstandDesign::CLast_WiderstandDesign(CController* _pCtr)
    : CAbstractView()
{
    pCtr = _pCtr;
    pCtr->setOffsetY(0);
  
}

CLast_WiderstandDesign::~CLast_WiderstandDesign()
{
}

void CLast_WiderstandDesign::draw(CDC* dc)
{
    CString text;


    if (!dc || !pCtr) return;
    

    const CPoint org = pCtr->getOrg();
    const CPoint act = pCtr->getAct();

    CPen penBlack(PS_SOLID, 1, RGB(0, 0, 0));
    dc->SelectObject(&penBlack);
    dc->SetBkMode(TRANSPARENT);

    const int bodyW = 40; // Feste Körperbreite
    const int xC = org.x;

    CBrush white(RGB(255, 255, 255));
    dc->SelectObject(&white);


    dc->Rectangle(xC - bodyW / 2, org.y, xC + bodyW / 2, act.y);

    int bandH = pCtr->getHotHeight();

    CBrush red(RGB(255, 0, 0));
    dc->SelectObject(&red);

    dc->Rectangle(xC - bodyW / 2, act.y - bandH / 2, xC + bodyW / 2, act.y + bandH / 2);

    text.Format(_T("RL"));
    dc->TextOut(xC - bodyW / 2 - 5, 215, text); // bezogen auf CPoint org

}