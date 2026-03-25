#include "pch.h"
#include "Legende.h"

CLegende::CLegende() {};

CLegende::~CLegende() {};

void CLegende::draw(CDC* pDC) {

    // Für die Legende der Graphen
    CPen PenBlack(PS_SOLID, 1, RGB(0, 0, 0));
    pDC->SelectObject(PenBlack);
    pDC->SetBkMode(TRANSPARENT);
    // Ustr
    CString leg;
    CBrush blue(RGB(0, 0, 255));
    pDC->SelectObject(blue);
    pDC->Ellipse(575, 60, 590, 75);
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkMode(TRANSPARENT);
    leg.Format(_T("Ustr"));
    pDC->TextOut(595, 60, leg);
    // fsz
    CBrush grau(RGB(192, 192, 192));
    pDC->SelectObject(grau);
    pDC->Ellipse(575, 80, 590, 95);
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkMode(TRANSPARENT);
    leg.Format(_T("Usz"));
    pDC->TextOut(595, 80, leg);

    CBrush black_U(RGB(0, 0, 0));
    pDC->SelectObject(black_U);
    pDC->Ellipse(575, 210, 590, 225);
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkMode(TRANSPARENT);
    leg.Format(_T("Upulse"));
    pDC->TextOut(595, 210, leg);
    // fsz
    CBrush red_U(RGB(255, 0, 0));
    pDC->SelectObject(red_U);
    pDC->Ellipse(575, 230, 590, 245);
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkMode(TRANSPARENT);
    leg.Format(_T("Uout"));
    pDC->TextOut(595, 230, leg);

    CBrush black_I(RGB(0, 0, 0));
    pDC->SelectObject(black_I);
    pDC->Ellipse(575, 360, 590, 375);
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkMode(TRANSPARENT);
    leg.Format(_T("Ipulse"));
    pDC->TextOut(595, 360, leg);
    // fsz
    CBrush red_I(RGB(255, 0, 0));
    pDC->SelectObject(red_I);
    pDC->Ellipse(575, 380, 590, 395);
    pDC->SetTextColor(RGB(0, 0, 0));
    pDC->SetBkMode(TRANSPARENT);
    leg.Format(_T("Iout"));
    pDC->TextOut(595, 380, leg);


};