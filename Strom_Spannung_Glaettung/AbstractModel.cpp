#include "pch.h"
#include "AbstractModel.h"
//#include "AbstractView.h"
#include "Controller.h"

CAbstractModel::CAbstractModel()
{
}


CAbstractModel::~CAbstractModel()
{
}

void CAbstractModel::addView(CAbstractView* _pV) {
	viewListe.push_back(_pV);
}

void CAbstractModel::notifyViews(CDC* pDC) {
	for (vector<CController*>::iterator it = controllerListe.begin(); it != controllerListe.end(); it++) {
		(*it)->update(pDC);
	}
}

void CAbstractModel::addCtr(CController* _pC) {
	auto it = find(controllerListe.begin(), controllerListe.end(), _pC);
	if (it == controllerListe.end()) controllerListe.push_back(_pC);
	
}
void CAbstractModel::removeCtr(CController* _pC) {
	auto it = find(controllerListe.begin(), controllerListe.end(), _pC);
	if (it != controllerListe.end()) {
		controllerListe.erase(it);
		
	}
	
}

void CAbstractModel::calcModel(CDC* pDC) {
	// Informieren aller beobachtenden Views über Änderungen am Model: notifyViews()

	this->notifyViews(pDC);
}


bool CAbstractModel::controllerCheck(CPoint _pos) {
	for (auto it = controllerListe.begin(); it != controllerListe.end(); ++it) {
		if ((*it)->isCtrActive(_pos)) return true;
	}
	return false;
}


CController* CAbstractModel::getCtrPtr(CPoint _pos) {
	for (vector<CController*>::iterator it = controllerListe.begin(); it != controllerListe.end(); it++) {
		if ((*it)->isCtrActive(_pos))
			return *it;
	}
	return NULL;
}
