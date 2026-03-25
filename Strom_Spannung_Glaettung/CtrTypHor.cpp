#include "pch.h"
#include "CtrTypHor.h"

CCtrTypHor::CCtrTypHor(CController* _pCtr)
	: CAbstractController(_pCtr)
{	// horizontaler Controller mit Bewegungsrichtung nach RECHTS
	pCtr->setMinPx(pCtr->getOrg().x + pCtr->getMinLen());
	pCtr->setMaxPx(pCtr->getOrg().x + pCtr->getMaxLen());

}

CCtrTypHor::~CCtrTypHor()
{
}

double CCtrTypHor::calcController(CPoint _pos, CDC* pDC, CController* ctrfs) {
	if (pCtr != ctrfs) {
		pCtr->setActPointX(_pos.x);
		if (pCtr->getActX() < pCtr->getMinPx())
			pCtr->setActPointX(pCtr->getMinPx());
		if (pCtr->getActX() > pCtr->getMaxPx())
			pCtr->setActPointX(pCtr->getMaxPx());
		double actValue = pCtr->getPCO()->getMinVal() + ((pCtr->getActX() - pCtr->getMinPx())) * (pCtr->getPCO()->getMaxVal() - pCtr->getPCO()->getMinVal()) / ((pCtr->getMaxPx() - pCtr->getMinPx()));

		pCtr->getPCO()->setActualValue(actValue);
		// Model neu berechnen
		pCtr->getPModel()->calcModel(pDC);
		return actValue;
	}
	else { // dür die Schaltfrequen´z 
		pCtr->setActPointX(_pos.x);


		if (pCtr->getActX() < pCtr->getMinPx())
			pCtr->setActPointX(pCtr->getMinPx());
		if (pCtr->getActX() > pCtr->getMaxPx())
			pCtr->setActPointX(pCtr->getMaxPx());
		double actValue = 500 / ((pCtr->getActX() - 60) * 0.01);
		pCtr->getPCO()->setActualValue(actValue);
		pCtr->getPModel()->calcModel(pDC);
		return actValue;
	}
}
