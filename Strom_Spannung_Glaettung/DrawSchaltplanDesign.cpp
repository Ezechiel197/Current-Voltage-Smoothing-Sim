#include "pch.h"
#include "DrawSchaltplanDesign.h"
#include "Controller.h"



CDrawSchaltplanDesign::CDrawSchaltplanDesign() {

}

CDrawSchaltplanDesign::CDrawSchaltplanDesign(CPoint _org, CPoint _orgC, bool _m_bS1Closed, bool _m_bS2Closed, CController* _ctrC, CController* _ctrRL)

    : org(_org), orgC(_orgC), m_bS1Closed(_m_bS1Closed), m_bS2Closed(_m_bS2Closed), ctrC(_ctrC), ctrRL(_ctrRL) {

}

CDrawSchaltplanDesign::~CDrawSchaltplanDesign() {

}

void CDrawSchaltplanDesign::DrawSwitchV(CDC* pDC, int x, int y1, int y2, bool closed, int r)

{
    pDC->Ellipse(x - r, y1 - r, x + r, y1 + r);
    pDC->Ellipse(x - r, y2 - r, x + r, y2 + r);

    if (closed)
    {

        pDC->MoveTo(x, y1 + r);
        pDC->LineTo(x, y2 - r);
    }
    else
    {

        const int leverX = x + 8;
        const int leverEndY = y2 - r - 3;
        const int leverStartY = y1 + r + 8;

        pDC->MoveTo(x, y1 + r);
        pDC->LineTo(x, leverStartY);

        pDC->MoveTo(x, leverStartY);
        pDC->LineTo(leverX, leverEndY);
    }
}

void CDrawSchaltplanDesign::DrawSwitchH(CDC* pDC, int x1, int x2, int y, bool closed, int r)

{   // Kreise (Kontakte)
    pDC->Ellipse(x1 - r, y - r, x1 + r, y + r);
    pDC->Ellipse(x2 - r, y - r, x2 + r, y + r);

    if (closed)
    {
        // geschlossen: voller Kontakt
        pDC->MoveTo(x1 + r, y);
        pDC->LineTo(x2 - r, y);
    }
    else
    {
        // offen: kleines Segment auf der linken Seite + geneigter Hebel 
        const int leverY = y - 8;
        const int leverEndX = x2 - r - 3;
        const int leverStartX = x1 + r + 8;

        // kleines festes Segment links
        pDC->MoveTo(x1 + r, y);
        pDC->LineTo(leverStartX, y);

        // Schräghebel
        pDC->MoveTo(leverStartX, y);
        pDC->LineTo(leverEndX, leverY);
    }
}

void CDrawSchaltplanDesign::draw(CDC* pDC) {


    if (!pDC) return;

    CBrush white(RGB(255, 255, 255));
    CBrush black(RGB(0, 0, 0));
    CPen penWire(PS_SOLID, 2, RGB(0, 0, 0));
    CPen penFrame(PS_SOLID, 1, RGB(210, 210, 210));

    pDC->SetBkMode(TRANSPARENT);
    pDC->SetTextColor(RGB(0, 0, 0));

    const int yBus = org.y;
    const int yBottom = org.y + 120;

    const int nodeX = orgC.x;
    const int nodeY = yBus;

    const int xRight = orgC.x + 260;

    //  DC-DC
    const int srcL = org.x - 140;
    const int srcR = org.x - 20;
    const int srcT = yBus - 20;
    const int srcB = yBus + 140;

    // Rundzentrum auf Arm + Klemme
    const int r = 30;
    const int pad = 10;
    const double kTap = 0.50;

    int xTap = srcL + (int)((srcR - srcL) * kTap + 0.5);
    if (xTap < srcL + pad + r) xTap = srcL + pad + r;
    if (xTap > srcR - pad - r) xTap = srcR - pad - r;

    const int cx = xTap;

    int cy = srcT + (srcB - srcT) / 2;
    if (cy < srcT + pad + r) cy = srcT + pad + r;
    if (cy > srcB - pad - r) cy = srcB - pad - r;

    // Rahmen
    pDC->SelectObject(&white);
    pDC->SelectObject(&penFrame);
    pDC->Rectangle(org.x - 160, org.y - 90, orgC.x + 320, org.y + 170);

    //  DC-DC-Block (Zeichnung)
    {
        CPen dcPen(PS_SOLID, 2, RGB(180, 180, 180));
        CBrush dcBrush(RGB(245, 245, 245));
        pDC->SelectObject(&dcPen);
        pDC->SelectObject(&dcBrush);
        pDC->Rectangle(srcL, srcT, srcR, srcB);

        CPen blackPen(PS_SOLID, 2, RGB(0, 0, 0));
        CBrush whiteBrush(RGB(255, 255, 255));
        pDC->SelectObject(&blackPen);
        pDC->SelectObject(&whiteBrush);

        // Kreis PWM
        pDC->Ellipse(cx - r, cy - r, cx + r, cy + r);

        // internes Rechtecksignal
        pDC->MoveTo(cx - 20, cy + 12);
        pDC->LineTo(cx - 20, cy - 12);
        pDC->LineTo(cx - 7, cy - 12);
        pDC->LineTo(cx - 7, cy + 12);
        pDC->LineTo(cx + 7, cy + 12);
        pDC->LineTo(cx + 7, cy - 12);
        pDC->LineTo(cx + 20, cy - 12);

        // text DC-DC
        pDC->SetTextColor(RGB(170, 170, 170));
        pDC->TextOut(srcL + 12, srcB - 28, CString(_T("DC-DC")));
        pDC->SetTextColor(RGB(0, 0, 0));

        // Pfeil uPulse
        pDC->SelectObject(&penWire);
        const int xArrow = srcL + 22;
        const int yA1 = cy - 55;
        const int yA2 = cy + 55;

        pDC->MoveTo(xArrow, yA1);
        pDC->LineTo(xArrow, yA2);

        POINT tri[3] = { { xArrow - 6, yA2 - 8 }, { xArrow + 6, yA2 - 8 }, { xArrow, yA2 } };
        pDC->SelectObject(&black);
        pDC->Polygon(tri, 3);
        pDC->SelectObject(&white);

        // vertikaler Text "uPulse"
        {
            LOGFONT lf{};
            CFont* pOldFont = nullptr;

            CFont* pGuiFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
            if (pGuiFont) pGuiFont->GetLogFont(&lf);
            else ::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(lf), &lf);

            lf.lfEscapement = 900;
            lf.lfOrientation = 900;

            CFont rotFont;
            rotFont.CreateFontIndirect(&lf);
            pOldFont = pDC->SelectObject(&rotFont);

            pDC->TextOut(srcL + 5, cy + 25, CString(_T("uPulse")));
            pDC->SelectObject(pOldFont);
        }
    }

    // Hauptstromkreis
    pDC->SelectObject(&penWire);
    pDC->SelectObject(&white);

    // Oberer Faden + S2
    const int rr = 4;
    const int s2x1 = nodeX + 70;
    const int s2x2 = nodeX + 115;

    pDC->MoveTo(xTap, yBus);
    pDC->LineTo(s2x1 - rr, yBus);

    DrawSwitchH(pDC, s2x1, s2x2, yBus, get_m_bS2Closed(), rr);
    pDC->TextOut(nodeX + 85, yBus + 12, CString(_T("S2")));

    pDC->MoveTo(s2x2 + rr, yBus);
    pDC->LineTo(xRight, yBus);

    // Gerader Ast: um den Widerstand herum schneiden 
    if (ctrRL)
    {
        const int xR = ctrRL->getOrg().x;
        const int m = -1;

        const int y1 = min(ctrRL->getOrg().y, ctrRL->getAct().y);
        const int y2 = max(ctrRL->getOrg().y, ctrRL->getAct().y);

        int cutTop = y1 - m;
        int cutBot = y2 + m;

        if (cutTop < yBus)    cutTop = yBus;
        if (cutBot > yBottom) cutBot = yBottom;
        if (cutTop > cutBot) { int t = cutTop; cutTop = cutBot; cutBot = t; }

        pDC->MoveTo(xR, yBus);
        pDC->LineTo(xR, cutTop);

        pDC->MoveTo(xR, cutBot);
        pDC->LineTo(xR, yBottom);
    }
    else
    {
        pDC->MoveTo(xRight, yBus);
        pDC->LineTo(xRight, yBottom);
    }


    pDC->MoveTo(xRight, yBottom);
    pDC->LineTo(xTap, yBottom);

    // PWM-Zweig (vertikal) 
    pDC->MoveTo(xTap, yBus);
    pDC->LineTo(xTap, cy - r);

    pDC->MoveTo(xTap, cy + r);
    pDC->LineTo(xTap, yBottom);

    // Knoten 

    pDC->SelectObject(&black);
    pDC->Ellipse(nodeX - 5, nodeY - 5, nodeX + 5, nodeY + 5);
    pDC->Ellipse(nodeX - 5, yBottom - 5, nodeX + 5, yBottom + 5);
    pDC->SelectObject(&white);

    //  Kondensatorzweig + S1 
    if (ctrC)
    {
        const int capY = ctrC->getOrg().y;
        const int hotH = ctrC->getHotHeight();

        const int yUpperBottom = capY - hotH / 6;
        const int yLowerTop = capY + hotH / 6;
        const int gap = 2;


        const int yTarget = yUpperBottom - gap;
        int mid = (nodeY + yTarget) / 2;

        const int s1Half = 12;
        int s1y1 = mid - s1Half;
        int s1y2 = mid + s1Half;

        // Knotendraht S1
        pDC->MoveTo(nodeX, nodeY);
        pDC->LineTo(nodeX, s1y1 - rr);

        // switch S1
        DrawSwitchV(pDC, nodeX, s1y1, s1y2, get_m_bS1Closed(), rr);
        pDC->TextOut(nodeX - 35, mid - 5, CString(_T("S1")));

        // Faden nach S1 
        pDC->MoveTo(nodeX, s1y2 + rr);
        pDC->LineTo(nodeX, yUpperBottom - gap);

        // Flachdraht  
        pDC->MoveTo(nodeX, yLowerTop + gap);
        pDC->LineTo(nodeX, yBottom);
    }
    else
    {
        pDC->MoveTo(nodeX, nodeY);
        pDC->LineTo(nodeX, yBottom);
    }
}