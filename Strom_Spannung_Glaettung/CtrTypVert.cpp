#include "pch.h"
#include "CtrTypVert.h"
#include "Controller.h"
class CController;

CCtrTypVert::CCtrTypVert(CController* _pCtr)
	: CAbstractController(_pCtr)
{	// vertikaler Controller mit Bewegungsrichtung nach OBEN
	pCtr->setMinPx(pCtr->getOrg().y - pCtr->getMinLen());
	pCtr->setMaxPx(pCtr->getOrg().y - pCtr->getMaxLen());
}

CCtrTypVert::~CCtrTypVert()
{
}

double CCtrTypVert::calcController(CPoint _pos, CDC* pDC, CController* ctrfs) {
	pCtr->setActPointY(_pos.y);
	if (pCtr->getActY() > pCtr->getMinPx())
		pCtr->setActPointY(pCtr->getMinPx());
	if (pCtr->getActY() < pCtr->getMaxPx())
		pCtr->setActPointY(pCtr->getMaxPx());
	double actValue = pCtr->getPCO()->getMinVal() + ((double)(pCtr->getActY() - (pCtr->getMinPx()))) * (pCtr->getPCO()->getMaxVal() - pCtr->getPCO()->getMinVal()) / ((double)(pCtr->getMaxPx() - pCtr->getMinPx()));

	pCtr->getPCO()->setActualValue(actValue);
	// Model neu berechnen
	pCtr->getPModel()->calcModel(pDC);
	return actValue;
}