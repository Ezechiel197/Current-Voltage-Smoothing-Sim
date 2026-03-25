#include "pch.h"
#include "AbstractController.h"

class Controller;


CAbstractController::CAbstractController(CController* _pCtr)
	: pCtr(_pCtr)
{
}

CAbstractController::~CAbstractController()
{
}


void CAbstractController::init(void) {
	pCtr->setActPointX((int)((pCtr->getPCO()->getActualVal() - pCtr->getPCO()->getMinVal()) * (pCtr->getMaxPx() - pCtr->getMinPx()) / (pCtr->getPCO()->getMaxVal() - pCtr->getPCO()->getMinVal())) + (pCtr->getOrg().x + pCtr->getMinPx()));
}