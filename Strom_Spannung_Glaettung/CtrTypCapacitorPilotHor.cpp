#include "pch.h"
#include "CtrTypCapacitorPilotHor.h"
#include "Controller.h"

CCtrTypCapacitorPilotHor::CCtrTypCapacitorPilotHor(CController* _pCtr)
    : CAbstractController(_pCtr)
{

    pCtr->setMinPx(pCtr->getOrg().x + pCtr->getMinLen());
    pCtr->setMaxPx(pCtr->getOrg().x + pCtr->getMaxLen());
}

CCtrTypCapacitorPilotHor::~CCtrTypCapacitorPilotHor() {}

double CCtrTypCapacitorPilotHor::calcController(CPoint _pos, CDC* pDC, CController* ctrfs)
{
    // pilot
    pCtr->setActPointX(_pos.x);

    pCtr->setActPointY(pCtr->getOrg().y);

    // clamp min
    if (pCtr->getActX() < pCtr->getMinPx())
        pCtr->setActPointX(pCtr->getMinPx());

    // clamp max : maxPx - 5*xFactor 
    const int xFactor = (pCtr->getHotWidth() >= 10) ? (pCtr->getHotWidth() / 10) : 1;
    const int maxAllowed = pCtr->getMaxPx() - 5 * xFactor;

    if (pCtr->getActX() > maxAllowed)
        pCtr->setActPointX(maxAllowed);

    // mapping  
    double actValue =
        pCtr->getPCO()->getMinVal()
        + ((double)pCtr->getActX() - (double)pCtr->getMinPx())
        * (pCtr->getPCO()->getMaxVal() - pCtr->getPCO()->getMinVal())
        / ((double)pCtr->getMaxPx() - (double)pCtr->getMinPx());

    pCtr->getPCO()->setActualValue(actValue);

    if (pDC) pCtr->getPModel()->calcModel(pDC);
    return actValue;
}