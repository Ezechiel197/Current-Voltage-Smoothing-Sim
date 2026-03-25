#pragma once
/**
 * KLASSE: CController
 * ----------------------------------------------------------------
 * Diese Klasse fungiert als zentrale Vermittlungsinstanz im MVC-Pattern.
 * Sie verbindet die physikalischen Daten (CControllableObject) mit ihrer
 * grafischen Darstellung (CAbstractView) und der Logik der Benutzereingabe.
 *
 * Hauptaufgaben:
 * - Ereignisverarbeitung: Überprüfung, ob ein Mausklick ein interaktives
 * Bauteil getroffen hat (isCtrActive).
 * - Koordinatensynchronisation: Speicherung von Ankerpunkten (org) und
 * aktuellen Griffpositionen (act) für die grafische Darstellung.
 * - Brückenfunktion: Kommunikation zwischen der mathematischen Simulation
 * (CAbstractModel) und den veränderbaren Objekten.
 * - Ressourcenverwaltung: Dynamische Verwaltung und Bereinigung der
 * zugehörigen Design- und Logik-Komponenten.
 */
#include "atltypes.h"
#include "AbstractModel.h"
#include "ControllableObject.h"
class CCtrTyp;
class CAbstractView;
class CAbstractController;

class CController {
protected:
	CPoint org;
	CPoint act;
	int hotWidth;
	int hotHeight;
	int minPx;
	int maxPx;
	int minLen;
	int maxLen;
	COLORREF lineColor;
	COLORREF areaColor;
	CAbstractModel* pModel;
	CAbstractController* pTypeOfCtr;
	CControllableObject* pCO;
	CAbstractView* pDesignOfCtr;
	int offsetY = 0;
public:
	virtual ~CController();
	CController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO, CAbstractController* _pCtrTyp, CAbstractView* _pDesign, COLORREF _lineCol, COLORREF _areaCol);
	CController(CPoint _org, CPoint _act, CAbstractModel* _pModel, CControllableObject* _pCO, COLORREF _lineCol, COLORREF _areaCol);
	virtual bool isCtrActive(CPoint _mousePos);
	virtual double calcActualValue(CPoint _pos, CDC* pDC, CController* ctrfs);
	virtual void update(CDC* pDC);

	void setControllableObject(CControllableObject* _pCO);
	CControllableObject* getControllableObject()const;
	void setOrgX(int _x);
	void setOrgY(int _y);
	void setActPointX(int _x);
	void setActPointY(int _y);
	void setMinPx(int _px);
	void setMaxPx(int _px);
	int getActY(void)const;
	int getActX(void)const;
	int getMinPx(void)const;
	int getMaxPx(void)const;
	CControllableObject* getPCO(void)const;
	CAbstractModel* getPModel(void)const;
	COLORREF getLineCol();
	COLORREF getAreaCol();
	CPoint getAct();
	CPoint getOrg();
	int getHotWidth();
	int getHotHeight();
	void setHeigth(int _hotHeight);
	void setWidth(int _width);
	void setMinLen(int _minLen);
	void setMaxLen(int _maxLen);
	int getMinLen(void)const;
	int getMaxLen(void)const;
	void setCtrTyp(CAbstractController* _pCtrTyp);
	void setCtrDesign(CAbstractView* _pCtrDes);
	void setOffsetY(int _y) { offsetY = _y; }
	int getOffsetY() const { return offsetY; }
};

