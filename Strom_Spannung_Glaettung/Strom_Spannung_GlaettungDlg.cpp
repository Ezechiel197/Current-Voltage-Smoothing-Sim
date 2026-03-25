
// Strom_Spannung_GlaettungDlg.cpp: Implementierungsdatei

#include "pch.h"
#include "framework.h"
#include "Strom_Spannung_Glaettung.h"
#include "Strom_Spannung_GlaettungDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "AbstractController.h"

class CAbstractController;
class CModel;
class CAboutDlg;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // Dialogfelddaten
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

    // Implementierung
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CStromSpannungGlaettungDlg::CStromSpannungGlaettungDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_STROM_SPANNUNG_GLAETTUNG_DIALOG, pParent), org(850, 120)
    , orgC(org.x + 260, org.y + 40)


{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    p_model = new CModel();
    p_model->pL = new CControllableObject(0.0001, p_model->get_induktivitaet(), 0.001, "L");     // min, act, max, name
    p_model->pRL = new CControllableObject(0.5, p_model->get_Lastwiderstand(), 1, "RL");
    p_model->pC = new CControllableObject(0.00025, p_model->get_Kapazitaet(), 0.001, "C");
    p_model->pR = new CControllableObject(0.5, p_model->get_widerstand(), 1, "R");
    p_model->pUstr = new CControllableObject(0, p_model->get_steuers_spannung(), 5, "Ustr");
    p_model->pfs = new CControllableObject(2000, p_model->get_dreieck_frequenz(), 100, "fs");



    // Kontroller fs
    ctrfs = new CController( // Diese Punkte wurde aus der Graph mithilfe von setNettoWidth(500) und setNettoHeight(100) ermitteln
        CPoint(60, 60),
        CPoint(160, 60),
        p_model, p_model->pfs,
        RGB(255, 0, 0), RGB(255, 0, 0)
    );
    // Kontroller Ustr
    ctrUstr = new CController( // Diese Punkte wurde aus der Graph mithilfe von setNettoWidth(500) und setNettoHeight(100) ermitteln
        CPoint(310, 160),
        CPoint(310, 100),
        p_model, p_model->pUstr,
        RGB(255, 0, 0), RGB(255, 0, 0)
    );
    // Induktivitaet L
    ctrL = new CController(
        CPoint(org.x + 60, org.y),
        CPoint(org.x + 120, org.y),
        p_model, p_model->pL,
        RGB(0, 0, 0), RGB(255, 0, 0)
    );
    //  Widerstand R
    ctrR = new CController(
        CPoint(org.x + 60, org.y),
        CPoint(org.x + 120, org.y),
        p_model, p_model->pR,
        RGB(0, 0, 0), RGB(255, 255, 255)
    );
    // Lastwiderstand RL
    const int xRight = orgC.x + 260;
    const int yBus = org.y;
    const int yBottom = org.y + 120;


    ctrRL = new CController(
        CPoint(xRight, yBottom - 25),
        CPoint(xRight, yBottom - 10),
        p_model, p_model->pRL,
        RGB(0, 0, 0), RGB(0, 0, 0)
    );

    // --- Kondensatorsteuerung (C) ---
    const int capCenterY = orgC.y + 40;
    ctrC = new CController(
        CPoint(orgC.x, capCenterY),
        CPoint(orgC.x + 20, capCenterY),
        p_model, p_model->pC,
        RGB(0, 0, 0), RGB(0, 0, 0)
    );


    // views erstellen
    schaltplan = new CDrawSchaltplanDesign(org, orgC, m_bS1Closed, m_bS2Closed, ctrC, ctrRL);
    legende = new CLegende();
    viewfs = new CSchaltfrequenzDesign(ctrfs);
    viewUstr = new CSteuerspannungDesign(ctrUstr);
    viewL = new CInduktorDesign(ctrL);
    viewR = new CWiderstandDesign(ctrR);
    viewRL = new CLast_WiderstandDesign(ctrRL);
    viewC = new CCapacitorPilotDesign(ctrC);

    // Die Controller beim Modell anmelden!
   // p_modell->addCtr(ctrL);
    p_model->addCtr(ctrR);
    p_model->addCtr(ctrRL);
    p_model->addCtr(ctrC);
    p_model->addCtr(ctrUstr);
    p_model->addCtr(ctrfs);
    initControllers();

    // Views anmelden 
    p_model->addView(viewfs);
    p_model->addView(viewUstr);
    p_model->addView(viewL);
    p_model->addView(viewR);
    p_model->addView(viewRL);
    p_model->addView(viewC);

}
CStromSpannungGlaettungDlg::~CStromSpannungGlaettungDlg()
{
    delete p_model->pL; p_model->pL = nullptr;
    delete p_model->pRL; p_model->pRL = nullptr;
    delete p_model->pR; p_model->pR = nullptr;
    delete p_model->pC; p_model->pC = nullptr;
    delete p_model->pUstr; p_model->pUstr = nullptr;
    delete p_model->pfs; p_model->pfs = nullptr;
    delete p_model; p_model = nullptr;
    delete ctrL; ctrL = nullptr;
    delete ctrR; ctrR = nullptr;
    delete ctrRL; ctrRL = nullptr;
    delete ctrC; ctrC = nullptr;
    delete ctrUstr; ctrUstr = nullptr;
    delete ctrfs; ctrfs = nullptr;
    delete schaltplan; schaltplan = nullptr;
    delete legende; legende = nullptr;
    cPtr = nullptr;
}

void CStromSpannungGlaettungDlg::initControllers()
{
    // ----- fs  -----

    ctrfs->setHeigth(12);
    ctrfs->setWidth(24);
    ctrfs->setMaxLen(480);  // MaxLen in pixel
    ctrfs->setCtrDesign(viewfs);
    ctrfs->setMinLen(25);
    ctrfs->setMaxLen(500);
    ctrfs->setCtrTyp(new CCtrTypHor(ctrfs));
    // ----- Ustr  -----
    ctrUstr->setHeigth(24);
    ctrUstr->setWidth(12);
    ctrUstr->setMaxLen(110);  // MaxLen in pixel
    ctrUstr->setCtrDesign(viewUstr);
    ctrUstr->setCtrTyp(new CCtrTypVert(ctrUstr));

    // ----- L (Induktivität) -----
    ctrL->setHeigth(40);
    ctrL->setWidth(10);
    ctrL->setMaxLen(80);
    ctrL->setCtrDesign(viewL);
    ctrL->setCtrTyp(new CCtrTypHor(ctrL));

    // ----- R (Widerstand) -----
    ctrR->setHeigth(40);
    ctrR->setWidth(10);
    ctrR->setMaxLen(80);
    ctrR->setMinLen(40);
    ctrR->setCtrDesign(viewR);
    ctrR->setCtrTyp(new CCtrTypHor(ctrR));

    // ----- RL  -----
    ctrRL->setWidth(30);
    ctrRL->setHeigth(10);
    ctrRL->setMinLen(30);
    ctrRL->setMaxLen(60);
    ctrRL->setCtrDesign(viewRL);
    ctrRL->setCtrTyp(new CCtrTypVert(ctrRL));
    ctrRL->setActPointX(ctrRL->getOrg().x);
    ctrRL->setActPointX(ctrRL->getOrg().x);

    //  CCtrTypVert : act.y ∈ [org.y - maxLen ; org.y - minLen]
    int yMin = ctrRL->getOrg().y - ctrRL->getMaxLen();
    int yMax = ctrRL->getOrg().y - ctrRL->getMinLen();
    int yInit = ctrRL->getOrg().y - (ctrRL->getMaxLen() / 2);
    if (yInit < yMin) yInit = yMin;
    if (yInit > yMax) yInit = yMax;
    ctrRL->setActPointY(yInit);


    // ----- C -----
    ctrC->setHeigth(30);
    ctrC->setWidth(15);
    ctrC->setMinLen(5);
    ctrC->setMaxLen(60);

    ctrC->setCtrDesign(new CCapacitorPilotDesign(ctrC));
    ctrC->setCtrTyp(new CCtrTypCapacitorPilotHor(ctrC));
    ctrC->setActPointY(ctrC->getOrg().y);
}


void CStromSpannungGlaettungDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_L, L);
    DDX_Control(pDX, IDC_STATIC_C, C);
    DDX_Control(pDX, IDC_STATIC_RL, RL);
    DDX_Control(pDX, IDC_STATIC_R, R);
    DDX_Control(pDX, IDC_STATIC_f0, f0);
    DDX_Control(pDX, IDC_STATIC_str, Ustr);
    DDX_Control(pDX, IDC_STATIC_fs, fs);
    DDX_Control(pDX, IDC_STATIC_Ts, Ts);
    DDX_Control(pDX, IDC_STATIC_D, Tastgrad);
}

BEGIN_MESSAGE_MAP(CStromSpannungGlaettungDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_RADIO1, &CStromSpannungGlaettungDlg::OnBnClickedNo_Filter)
    ON_BN_CLICKED(IDC_RADIO2, &CStromSpannungGlaettungDlg::OnBnClickedL_Filter)
    ON_BN_CLICKED(IDC_RADIO3, &CStromSpannungGlaettungDlg::OnBnClickedRC_filter)
    ON_BN_CLICKED(IDC_RADIO4, &CStromSpannungGlaettungDlg::OnBnClickedRC_und_Load_filter)
    ON_BN_CLICKED(IDC_RADIO5, &CStromSpannungGlaettungDlg::OnBnClickedLC)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CStromSpannungGlaettungDlg-Meldungshandler
// gehört zum Modell
BOOL CStromSpannungGlaettungDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Hinzufügen des Menübefehls "Info..." zum Systemmenü.

    // IDM_ABOUTBOX muss sich im Bereich der Systembefehle befinden.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Symbol für dieses Dialogfeld festlegen.  Wird automatisch erledigt
    //  wenn das Hauptfenster der Anwendung kein Dialogfeld ist
    SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
    SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden


    // TODO: Hier zusätzliche Initialisierung einfügen
    // 1. Zeichnung
    CClientDC dc(this);
    schaltplan->draw(&dc);

    p_model->calcModel(&dc);




    CString strL, strRL, strC, strR, strf0, strUstr, strfs, strTs, strDuty;
    strL.Format(_T("%.2f "), p_model->get_induktivitaet() * 1000);
    L.SetWindowText(strL);
    strC.Format(_T("%.2f "), p_model->get_Kapazitaet() * 1000);
    C.SetWindowText(strC);
    strRL.Format(_T("%.2f "), p_model->get_Lastwiderstand());
    RL.SetWindowText(strRL);
    strR.Format(_T("%.2f "), p_model->get_widerstand());
    R.SetWindowText(strR);
    strf0.Format(_T("%.2f "), 1 / (2 * PI * sqrt(p_model->get_Kapazitaet() * p_model->get_induktivitaet())));
    f0.SetWindowText(strf0);
    strUstr.Format(_T("%.2f "), p_model->get_steuers_spannung());
    Ustr.SetWindowText(strUstr);
    strfs.Format(_T("%.2f "), p_model->get_dreieck_frequenz());
    fs.SetWindowText(strfs);
    strTs.Format(_T("%.2f "), 1000 / p_model->get_dreieck_frequenz());
    Ts.SetWindowText(strTs);
    strDuty.Format(_T("%.2f "), p_model->get_Tastgrad());
    Tastgrad.SetWindowText(strDuty);




    //Koordinatensystem für die Steurung
    p_model->koord_str->setCoorZero(60, 150);
    p_model->koord_str->setNettoWidth(500);
    p_model->koord_str->setNettoHeight(100);
    p_model->koord_str->setAxesLabelX("Zeit [s]");
    p_model->koord_str->setAxesLabelY("U [V]");
    p_model->koord_str->setGridON();
    p_model->koord_str->setLabelFormatX("%.3f");
    p_model->koord_str->setManuScale(0.001, 1, 0.01, 5, 0, 0);
    //Koordinatensystem für Spannungen 
    p_model->koord_U->setCoorZero(60, 300);
    p_model->koord_U->setNettoWidth(500);
    p_model->koord_U->setNettoHeight(100);
    p_model->koord_U->setAxesLabelX("Zeit [s]");
    p_model->koord_U->setAxesLabelY("U [V]");
    p_model->koord_U->setGridON();
    p_model->koord_U->setLabelFormatX("%.3f");
    p_model->koord_U->setManuScale(0.001, 2.5, 0.01, 5, 0, -5);
    //Koordinatensystem für  die Strömen
    p_model->koord_I->setCoorZero(60, 450);
    p_model->koord_I->setNettoWidth(500);
    p_model->koord_I->setNettoHeight(100);
    p_model->koord_I->setAxesLabelX("Zeit [s]");
    p_model->koord_I->setAxesLabelY("I [A]");
    p_model->koord_I->setGridON();
    p_model->koord_I->setLabelFormatX("%.3f");
    p_model->koord_I->setManuScale(0.001, 5, 0.01, 15, 0, -15);
    OnBnClickedNo_Filter();
    CheckDlgButton(IDC_RADIO1, BST_CHECKED);


    return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

void CStromSpannungGlaettungDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// Wenn Sie dem Dialogfeld eine Schaltfläche "Minimieren" hinzufügen, benötigen Sie
//  den nachstehenden Code, um das Symbol zu zeichnen.  Für MFC-Anwendungen, die das 
//  Dokument/Ansicht-Modell verwenden, wird dies automatisch ausgeführt.
// Gehört zu View
void CStromSpannungGlaettungDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // Gerätekontext zum Zeichnen

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // Symbol in Clientrechteck zentrieren
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // Symbol zeichnen
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CPaintDC dc(this);



        p_model->GetDataKoord_str()->Draw(&dc);
        p_model->GetDataKoord_U()->Draw(&dc);
        p_model->GetDataKoord_I()->Draw(&dc);
        // Dynamische Werte (Kontroller)

        schaltplan->draw(&dc);
        p_model->calcModel(&dc);
        legende->draw(&dc);
        //legende(&dc);

        CDialogEx::OnPaint();
    }
}

// Die System ruft diese Funktion auf, um den Cursor abzufragen, der angezeigt wird, während der Benutzer
//  das minimierte Fenster mit der Maus zieht.
HCURSOR CStromSpannungGlaettungDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// Methoden der Kontrolller 
void CStromSpannungGlaettungDlg::OnBnClickedNo_Filter()
{
    p_model->Kein_filter();
    p_model->removeCtr(ctrL);
    p_model->addCtr(ctrR);
    schaltplan->set_m_bS1Closed(false);
    schaltplan->set_m_bS2Closed(true);
    Invalidate();
}

void CStromSpannungGlaettungDlg::OnBnClickedL_Filter()
{
    p_model->L_filter();
    p_model->addCtr(ctrL);
    p_model->removeCtr(ctrR);
    schaltplan->set_m_bS1Closed(false);
    schaltplan->set_m_bS2Closed(true);
    Invalidate();
}

void CStromSpannungGlaettungDlg::OnBnClickedRC_filter()
{
    p_model->RC_filter();
    p_model->removeCtr(ctrL);
    p_model->addCtr(ctrR);
    schaltplan->set_m_bS1Closed(true);
    schaltplan->set_m_bS2Closed(false);
    Invalidate();
}

void CStromSpannungGlaettungDlg::OnBnClickedRC_und_Load_filter()
{
    p_model->RC_und_Load_filter();
    p_model->removeCtr(ctrL);
    p_model->addCtr(ctrR);
    schaltplan->set_m_bS1Closed(true);
    schaltplan->set_m_bS2Closed(true);
    Invalidate();
}


void CStromSpannungGlaettungDlg::OnBnClickedLC()
{
    p_model->LC_filter();
    p_model->addCtr(ctrL);
    p_model->removeCtr(ctrR);
    schaltplan->set_m_bS1Closed(true);
    schaltplan->set_m_bS2Closed(true);
    Invalidate();
}



void CStromSpannungGlaettungDlg::OnMouseMove(UINT nFlags, CPoint point)
{
    
    if ((nFlags & MK_LBUTTON) && cPtr)
    {
        CClientDC dc(this);

        // 1) update controller 
        double act;
        CString str, strf0, strUstr, strfs, strTs, strDuty;
        act = cPtr->calcActualValue(point, &dc, ctrfs);

        if (cPtr == ctrL && ctrL) {
            p_model->set_induktivitaet(act);
            str.Format(_T("%.2f "), act * 1000);
            L.SetWindowText(str);
            p_model->set_widerstand(ctrR->calcActualValue(point, &dc, ctrfs));

            if (IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED) { p_model->L_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO5) == BST_CHECKED) { p_model->LC_filter(); Invalidate(); }

        }
        else if (cPtr == ctrUstr && ctrUstr) {
            Invalidate();
            p_model->set_steuers_spannung(act);
            strUstr.Format(_T("%.2f "), act);
            Ustr.SetWindowText(strUstr);

            if (IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED) { p_model->Kein_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO3) == BST_CHECKED) { p_model->RC_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED) { p_model->L_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO4) == BST_CHECKED) { p_model->RC_und_Load_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO5) == BST_CHECKED) { p_model->LC_filter(); Invalidate(); }

        }
        else if (cPtr == ctrfs && ctrfs) {
            Invalidate();
            p_model->set_dreieck_frequenz(act);
            strfs.Format(_T("%.2f "), act);
            fs.SetWindowText(strfs);

            if (IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED) { p_model->Kein_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO3) == BST_CHECKED) { p_model->RC_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED) { p_model->L_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO4) == BST_CHECKED) { p_model->RC_und_Load_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO5) == BST_CHECKED) { p_model->LC_filter(); Invalidate(); }

        }
        else if (cPtr == ctrC && ctrC) {
            p_model->set_Kapazitaet(act);
            str.Format(_T("%.2f "), act * 1000);
            C.SetWindowText(str);


            if (IsDlgButtonChecked(IDC_RADIO3) == BST_CHECKED) { p_model->RC_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO4) == BST_CHECKED) { p_model->RC_und_Load_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO5) == BST_CHECKED) { p_model->LC_filter(); Invalidate(); }


        }
        else if (cPtr == ctrRL && ctrRL) {
            p_model->set_Lastwiderstand(act);
            str.Format(_T("%.2f "), act);
            RL.SetWindowText(str);
            if (IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED) { p_model->Kein_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED) { p_model->L_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO4) == BST_CHECKED) { p_model->RC_und_Load_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO5) == BST_CHECKED) { p_model->LC_filter(); Invalidate(); }

        }
        else if (cPtr == ctrR && ctrR) {
            p_model->set_widerstand(act);
            p_model->removeCtr(ctrL);
            str.Format(_T("%.2f "), act);
            R.SetWindowText(str);
            p_model->set_induktivitaet(ctrL->calcActualValue(point, &dc, ctrfs));

            if (IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED) { p_model->Kein_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO3) == BST_CHECKED) { p_model->RC_filter(); Invalidate(); }
            else if (IsDlgButtonChecked(IDC_RADIO4) == BST_CHECKED) { p_model->RC_und_Load_filter(); Invalidate(); }

        }


        // 2) redraw + Model
        schaltplan->draw(&dc);
        p_model->calcModel(&dc);

        strf0.Format(_T("%.2f "), 1 / (2 * PI * sqrt(p_model->get_Kapazitaet() * p_model->get_induktivitaet())));
        f0.SetWindowText(strf0);
        strUstr.Format(_T("%.2f "), p_model->get_steuers_spannung());
        Ustr.SetWindowText(strUstr);
        strfs.Format(_T("%.2f "), p_model->get_dreieck_frequenz());
        fs.SetWindowText(strfs);
        strTs.Format(_T("%.2f "), 1000 / p_model->get_dreieck_frequenz());
        Ts.SetWindowText(strTs);
        strDuty.Format(_T("%.2f "), p_model->get_Tastgrad());
        Tastgrad.SetWindowText(strDuty);

        return;
    }
    CDialogEx::OnMouseMove(nFlags, point);
}

void CStromSpannungGlaettungDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    cPtr = p_model->getCtrPtr(point);
    CDialogEx::OnLButtonDown(nFlags, point);
}

void CStromSpannungGlaettungDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
    cPtr = nullptr;
    CDialogEx::OnLButtonUp(nFlags, point);
}


