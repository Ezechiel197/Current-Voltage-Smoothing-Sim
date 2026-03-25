#include "pch.h"
#include "InduktorDesign.h"

CInduktorDesign::CInduktorDesign(CController* _pCtr)
	: CAbstractView()
{
	pCtr = _pCtr;
}

CInduktorDesign::~CInduktorDesign()
{
}

void CInduktorDesign::draw(CDC* _pDC) {
	CString text;
	CPen pen(PS_SOLID, 1, pCtr->getLineCol());
	_pDC->SelectObject(&pen);
	CPoint act = pCtr->getAct();
	int hotWidth = pCtr->getHotWidth();
	int hotHeight = pCtr->getHotHeight();
	CBrush black(RGB(0, 0, 0));
	_pDC->SelectObject(black);
	_pDC->Rectangle(pCtr->getOrg().x, pCtr->getOrg().y - hotHeight / 2, act.x, pCtr->getOrg().y + hotHeight / 2);
	CBrush red(RGB(255, 0, 0));
	_pDC->SelectObject(red);
	_pDC->Rectangle(act.x - hotWidth / 2, act.y - hotHeight / 2, act.x + hotWidth / 2, act.y + hotHeight / 2);

	text.Format(_T("L"));
	_pDC->TextOut(970, 120 + hotHeight / 2, text);
}
