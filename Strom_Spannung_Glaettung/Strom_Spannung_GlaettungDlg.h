#pragma once
/**
 * KLASSE: CStromSpannungGlaettungDlg
 * ----------------------------------------------------------------
 * Diese Klasse ist der Haupt-Dialog der Anwendung. Sie fungiert als Mediator
 * zwischen dem physikalischen Modell, den grafischen Views und dem Benutzer.
 *
 * Hauptaufgaben:
 * - Instanziierung & Initialisierung: Erzeugung des Modells (CModel), der
 * Controller für alle Parameter (L, R, C, fs, etc.) und der Design-Views.
 * - Event-Handling: Verarbeitung von Windows-Botschaften wie Mausbewegungen
 * (OnMouseMove) und Button-Klicks zur dynamischen Parameteränderung.
 * - Zustandsverwaltung: Steuerung der verschiedenen Filter-Modi (L, RC, LC)
 * durch Aktivierung/Deaktivierung spezifischer Schaltungskomponenten.
 * - UI-Synchronisation: Echtzeit-Aktualisierung der Textfelder (Static Controls)
 * für physikalische Werte wie Tastgrad, Frequenz oder Resonanzfrequenz.
 */

#include "afxdialogex.h"
#include <vector>   
#include <string>   
#include "Controller.h"
#include "ControllableObject.h"
#include "CtrTypHor.h"
#include "CtrTypVert.h"
#include "InduktorDesign.h"
#include "Last_WiderstandDesign.h"
#include "resource.h"
#include "CapacitorPilotDesign.h"
#include "CtrTypCapacitorPilotHor.h"
#include "AbstractModel.h"   
#include "DrawSchaltplanDesign.h"   
#include "Legende.h" 
#include "SchaltfrequenzDesign.h" 
#include "SteuerspannungDesign.h"
#include "WiderstandDesign.h" 
#include "CModel.h"
class CControllableObject;
class CController;
class CDC;
class CWiderstandDesign;

class CStromSpannungGlaettungDlg : public CDialogEx
{
	// Konstruktion
public:
	CStromSpannungGlaettungDlg(CWnd* pParent = nullptr);	// Standardkonstruktor
	~CStromSpannungGlaettungDlg();

	// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STROM_SPANNUNG_GLAETTUNG_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


	// Implementierung
protected:
	HICON m_hIcon;

	CPoint org;
	CPoint orgC;

	bool m_bS1Closed = false;
	bool m_bS2Closed = false;



	CModel* p_model;



	CController* ctrL = nullptr;
	CController* ctrRL = nullptr;
	CController* ctrC = nullptr;
	CController* ctrR = nullptr;
	CController* ctrUstr = nullptr;
	CController* ctrfs = nullptr;

	CController* cPtr = nullptr;
	CLegende* legende = nullptr;

	CSchaltfrequenzDesign* viewfs = nullptr;
	CSteuerspannungDesign* viewUstr = nullptr;
	CInduktorDesign* viewL = nullptr;
	CWiderstandDesign* viewR = nullptr;
	CLast_WiderstandDesign* viewRL = nullptr;
	CCapacitorPilotDesign* viewC = nullptr;

	CDrawSchaltplanDesign* schaltplan = nullptr;



	void initControllers();



	// Generierte Funktionen für die Meldungstabellen
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNo_Filter();
	afx_msg void OnBnClickedL_Filter();
	afx_msg void OnBnClickedRC_filter();
	afx_msg void OnBnClickedRC_und_Load_filter();
	afx_msg void OnBnClickedLC();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CStatic L;
	CStatic C;

	//CStatic R;
	CStatic RL;
	CStatic R;
	CStatic f0;
	CStatic Ustr;
	CStatic fs;
	CStatic Ts;
	CStatic Tastgrad;
};
