
//#include "StdAfx.h"
#include "pch.h"
#include "Koordinatensystem.h"
#include "math.h"
#include <new> 

//Declaration der Funktions-Bibliothek________________________________________________________
void D2ArryToPixelX(CData* Func, int XCount, int nettoScale, double maxValue, double minValue);
void D2ArryToPixelY(CData* Func, int YCount, int nettoScale, double maxValue, double minValue);
void D2ArryToLogPixelX(CData* Func, int XCount, int DekadenPixel, int anzFailDekande);
void D2ArryToLogPixelY(CData* Func, int YCount, int DekadenPixel, int anzFailDekande);
double D2highestValueX(CData* Func, int XCount);
double D2leastValueX(CData* Func, int XCount);
double D2highestValueY(CData* Func, int YCount);
double D2leastValueY(CData* Func, int YCount);
double minDekade(double minValue);
double maxDekade(double maxValue);
double Round(double Zahl, int Stellen);
int NrLabelSearch(int nettoScale);
int anzDekaden(double maxDekade, double minDekade);
int DekadenPixel(int anzDekaden, int nettoScale);
int failNrDekaden(double minDekade);

//___________________________________________________________________________________________
// CColor Implementierung
//___________________________________________________________________________________________
void CColor::setRed(int r) { red = r; }
void CColor::setGreen(int g) { green = g; }
void CColor::setBlue(int b) { blue = b; }
int CColor::getRed(void) { return red; }
int CColor::getGreen(void) { return green; }
int CColor::getBlue(void) { return blue; }

CColor::CColor(void)
{
	red = 0; green = 0; blue = 0;
}
CColor::CColor(const CColor& color)
{
	red = color.red; green = color.green; blue = color.blue;
}

//___________________________________________________________________________________________
// CData Implementierung (WICHTIG: Speicherverwaltung korrigiert)
//___________________________________________________________________________________________
CData::CData(void)
{
	strcpy_s(Name, "Func");
	PointView = 0;
	Color.setRed(0); Color.setGreen(0); Color.setBlue(255);
	lengthArry = 0;
	Xarry = nullptr;
	Yarry = nullptr;
}

CData::CData(const CData& CD) // Kopier-Konstruktor
{
	lengthArry = CD.lengthArry;
	PointView = CD.PointView;
	Color = CD.Color;
	strcpy_s(Name, CD.Name);

	if (lengthArry > 0)
	{
		Xarry = new double[lengthArry];
		Yarry = new double[lengthArry];
		for (int i = 0; i < lengthArry; i++) {
			Xarry[i] = CD.Xarry[i];
			Yarry[i] = CD.Yarry[i];
		}
	}
	else {
		Xarry = nullptr;
		Yarry = nullptr;
	}
}

// WICHTIG: Destruktor hinzugefügt, um Speicherlecks zu verhindern
CData::~CData(void)
{
	if (Xarry != nullptr) { delete[] Xarry; Xarry = nullptr; }
	if (Yarry != nullptr) { delete[] Yarry; Yarry = nullptr; }
}

// WICHTIG: Zuweisungsoperator hinzugefügt (Rule of Three)
CData& CData::operator=(const CData& other)
{
	if (this != &other) // Selbstzuweisung verhindern
	{
		// Alten Speicher freigeben
		if (Xarry != nullptr) delete[] Xarry;
		if (Yarry != nullptr) delete[] Yarry;

		// Daten kopieren
		lengthArry = other.lengthArry;
		PointView = other.PointView;
		Color = other.Color;
		strcpy_s(Name, other.Name);

		if (lengthArry > 0) {
			Xarry = new double[lengthArry];
			Yarry = new double[lengthArry];
			for (int i = 0; i < lengthArry; i++) {
				Xarry[i] = other.Xarry[i];
				Yarry[i] = other.Yarry[i];
			}
		}
		else {
			Xarry = nullptr;
			Yarry = nullptr;
		}
	}
	return *this;
}

void CData::setXYdata(double arryX[], double arryY[], int length)
{
	// Alten Speicher zuerst löschen, falls vorhanden
	if (Xarry != nullptr) delete[] Xarry;
	if (Yarry != nullptr) delete[] Yarry;

	lengthArry = length;
	if (length > 0)
	{
		Xarry = new double[length];
		Yarry = new double[length];

		for (int i = 0; i < length; i++)
		{
			Yarry[i] = arryY[i];
			Xarry[i] = arryX[i];
		}
	}
	else {
		Xarry = nullptr;
		Yarry = nullptr;
	}
}

void CData::setPointView(void) { PointView = 1; }
void CData::setName(char name[10]) { strcpy_s(Name, name); }
void CData::setRed(void) { Color.setRed(255); Color.setGreen(0); Color.setBlue(0); }
void CData::setGreen(void) { Color.setRed(18); Color.setGreen(226); Color.setBlue(7); }
void CData::setBlue(void) { Color.setRed(0); Color.setGreen(0); Color.setBlue(255); }
void CData::setYellow(void) { Color.setRed(243); Color.setGreen(255); Color.setBlue(23); }
void CData::setOrgange(void) { Color.setRed(255); Color.setGreen(128); Color.setBlue(0); }
void CData::setPurple(void) { Color.setRed(251); Color.setGreen(19); Color.setBlue(227); }
void CData::setBlack(void) { Color.setRed(0); Color.setGreen(0); Color.setBlue(0); }
void CData::setGrau(void) { Color.setRed(192); Color.setGreen(192); Color.setBlue(192); }
CColor CData::getColor(void) { return Color; }
bool CData::getPointView(void) { return PointView; }
double* CData::getXarry(void) { return Xarry; }
double* CData::getYarry(void) { return Yarry; }
char* CData::getName(void) { return Name; }
int CData::getLengthArry(void) { return lengthArry; }

//______________________________________________________________________________________
// CKoordinatensystem Implementierung
//______________________________________________________________________________________

CKoordinatensystem::CKoordinatensystem(void)
{

	FunctionVar = nullptr;
	CDataCount = 0;

	grid = 1;
	CoorZero.x = 100;
	CoorZero.y = 300;
	nettoWidth = 500;
	nettoHeight = 250;
	NrLabel = 1;
	AutoScale = 1;
	LinLin = 1;
	LinLog = 0; LogLin = 0; LogLog = 0;
	x2y = 0; y2x = 0;
	strcpy_s(LabelFormatX, "%.1f");
	strcpy_s(LabelFormatY, "%.1f");
	strcpy_s(AxesLabelX, "orgX");
	strcpy_s(AxesLabelY, "orgY");
	NameFunc = 0;
}

CKoordinatensystem::~CKoordinatensystem(void)
{

	if (FunctionVar != nullptr) {
		delete[] FunctionVar;
		FunctionVar = nullptr;
	}
}


void CKoordinatensystem::ClearData()
{
	if (FunctionVar != nullptr) {
		delete[] FunctionVar;
		FunctionVar = nullptr;
	}
	CDataCount = 0;
}


void CKoordinatensystem::addData(CData CDObject)
{

	CData* newArray = new CData[CDataCount + 1];


	for (int i = 0; i < CDataCount; i++)
	{
		newArray[i] = FunctionVar[i];
	}

	// Das neue Element hinzufügen
	newArray[CDataCount] = CDObject;

	// Alten Speicher löschen und Zeiger aktualisieren
	if (FunctionVar != nullptr)
	{
		delete[] FunctionVar;
	}

	FunctionVar = newArray;
	CDataCount++;
}

void CKoordinatensystem::setLinLinOFF() { LinLin = 0; LogLog = 1; }
void CKoordinatensystem::setLinLinON() { LinLin = 1; LogLog = 0; LinLog = 0; LogLin = 0; }
void CKoordinatensystem::setLinLogOFF() { LinLog = 0; LinLin = 1; }
void CKoordinatensystem::setLinLogON() { LinLog = 1; LogLog = 0; LinLin = 0; LogLin = 0; }
void CKoordinatensystem::setLogLogOFF() { LogLog = 0; LinLin = 1; }
void CKoordinatensystem::setLogLogON() { LogLog = 1; LinLin = 0; LinLog = 0; LogLin = 0; }
void CKoordinatensystem::setLogLinOFF() { LinLin = 1; LogLin = 0; }
void CKoordinatensystem::setLogLinON() { LogLog = 0; LinLin = 0; LinLog = 0; LogLin = 1; }
void CKoordinatensystem::setGridOFF() { grid = 0; }
void CKoordinatensystem::setGridON() { grid = 1; }
void CKoordinatensystem::setNrLabelON() { NrLabel = 1; }
void CKoordinatensystem::setNrLabelOFF() { NrLabel = 0; }
void CKoordinatensystem::setAxesLabelX(char name[10]) { strcpy_s(AxesLabelX, name); }
void CKoordinatensystem::setAxesLabelY(char name[10]) { strcpy_s(AxesLabelY, name); }
void CKoordinatensystem::setLabelFormatX(char Format[10]) { strcpy_s(LabelFormatX, Format); }
void CKoordinatensystem::setLabelFormatY(char Format[10]) { strcpy_s(LabelFormatY, Format); }

void CKoordinatensystem::setx2y(double xOffset)
{
	if (xOffset < 0.0) xOffset = 0.0;
	if (xOffset > 100.0) xOffset = 100.0;
	x2y = (int)(xOffset);
}
void CKoordinatensystem::sety2x(double yOffset)
{
	if (yOffset < 0.0) yOffset = 0.0;
	if (yOffset > 100.0) yOffset = 100.0;
	y2x = (int)(yOffset);
}
void CKoordinatensystem::setNameFunc(void) { NameFunc = 1; }
void CKoordinatensystem::setNettoWidth(int width) { nettoWidth = width; }
void CKoordinatensystem::setNettoHeight(int height) { nettoHeight = height; }
void CKoordinatensystem::setCoorZero(int xCoor, int yCoor) { CoorZero.x = xCoor; CoorZero.y = yCoor; }
void CKoordinatensystem::setManuScale(double stepX, double stepY, double MaxValueX, double MaxValueY, double MinValueX, double MinValueY)
{
	AutoScale = 0; StepX = stepX; StepY = stepY; maxValueY = MaxValueY; maxValueX = MaxValueX; minValueY = MinValueY; minValueX = MinValueX;
}
void CKoordinatensystem::setAutoScale() { AutoScale = 1; }
CData* CKoordinatensystem::getCData(void) { return FunctionVar; }
int CKoordinatensystem::getNettoWidth(void) { return nettoWidth; }
int CKoordinatensystem::getNettoHeight(void) { return nettoHeight; }
int CKoordinatensystem::getX2Y(void) { return x2y; }
int CKoordinatensystem::getY2X(void) { return y2x; }
int CKoordinatensystem::getCDataCount(void) { return CDataCount; }
bool CKoordinatensystem::getGrid(void) { return grid; }
bool CKoordinatensystem::getLinLin(void) { return LinLin; }
bool CKoordinatensystem::getLogLin(void) { return LogLin; }
bool CKoordinatensystem::getLinLog(void) { return LinLog; }
bool CKoordinatensystem::getLogLog(void) { return LogLog; }
bool CKoordinatensystem::getNrLabel(void) { return NrLabel; }
bool CKoordinatensystem::getAutoScale(void) { return AutoScale; }
bool CKoordinatensystem::getNameFunc(void) { return NameFunc; }
double CKoordinatensystem::getMinValueY(void) { return minValueY; }
double CKoordinatensystem::getMaxValueY(void) { return maxValueY; }
double CKoordinatensystem::getMinValueX(void) { return minValueX; }
double CKoordinatensystem::getMaxValueX(void) { return maxValueX; }
double CKoordinatensystem::getStepX(void) { return StepX; }
double CKoordinatensystem::getStepY(void) { return StepY; }
char* CKoordinatensystem::getLabelFormatX(void) { return LabelFormatX; }
char* CKoordinatensystem::getLabelFormatY(void) { return LabelFormatY; }
char* CKoordinatensystem::getAxesLabelX(void) { return AxesLabelX; }
char* CKoordinatensystem::getAxesLabelY(void) { return AxesLabelY; }
CPoint CKoordinatensystem::getCoorZero(void) { return CoorZero; }

//_________________________________________________________________________________________________
// Draw Funktion (Korrigiertes Memory Management)
//_________________________________________________________________________________________________
void CKoordinatensystem::Draw(CDC* pDC)
{
	if (CDataCount == 0) return; // Nichts zu zeichnen

	//Hilfsvariablen
	int NrGridX, NrGridY, NrLabelX, NrLabelY;
	double minDekadeY, maxDekadeY, minDekadeX, maxDekadeX;
	int anzDekadenY, DekadenPixelY, anzDekadenX, DekadenPixelX;
	CPen Color;
	double incrementX, incrementY;

	//Datensicherung: Wir erstellen eine tiefe Kopie
	CData* FunctionVarSave = new CData[CDataCount];
	for (int i = 0; i < CDataCount; i++)
	{
		FunctionVarSave[i] = FunctionVar[i]; // Ruft jetzt den operator= auf
	}

	if (AutoScale)//AutoScale ON
	{
		maxValueX = D2highestValueX(FunctionVar, CDataCount);
		maxValueY = D2highestValueY(FunctionVar, CDataCount);
		minValueX = D2leastValueX(FunctionVar, CDataCount);
		minValueY = D2leastValueY(FunctionVar, CDataCount);

		NrGridX = NrLabelSearch(nettoWidth);
		incrementX = (nettoWidth * 1.0) / (NrGridX - 1);
		NrGridY = NrLabelSearch(nettoHeight);
		incrementY = (nettoHeight * 1.0) / (NrGridY - 1);

		NrLabelX = NrLabelSearch(nettoWidth);
		NrLabelY = NrLabelSearch(nettoHeight);

		// Schutz gegen Division durch Null
		if (NrLabelX > 1) StepX = (maxValueX - minValueX) / (NrLabelX - 1); else StepX = 1;
		if (NrLabelY > 1) StepY = (maxValueY - minValueY) / (NrLabelY - 1); else StepY = 1;
	}
	else//Manuscale ON(AutoScale OFF)
	{
		if (StepX != 0) NrGridX = (int)((maxValueX - minValueX) / StepX) + 1; else NrGridX = 1;
		if (StepY != 0) NrGridY = (int)((maxValueY - minValueY) / StepY) + 1; else NrGridY = 1;
		NrLabelX = NrGridX;
		NrLabelY = NrGridY;

		if (maxValueX - minValueX != 0)
			incrementX = StepX * (nettoWidth / (maxValueX - minValueX));
		else incrementX = 0;

		if (maxValueY - minValueY != 0)
			incrementY = StepY * (nettoHeight / (maxValueY - minValueY));
		else incrementY = 0;
	}

	//Hilfberechnungen f r logarithmische Darstellung
	if (LinLog || LogLog)
	{
		maxDekadeY = maxDekade(maxValueY);
		minDekadeY = minDekade(minValueY);
		if (minDekadeY == maxDekadeY) { maxDekadeY *= 10.0; minDekadeY /= 10.0; }
		anzDekadenY = anzDekaden(maxDekadeY, minDekadeY);
		if (anzDekadenY > 0) DekadenPixelY = DekadenPixel(anzDekadenY, nettoHeight); else DekadenPixelY = 1;
	}
	if (LogLog || LogLin)
	{
		maxDekadeX = maxDekade(maxValueX);
		minDekadeX = minDekade(minValueX);
		if (minDekadeX == maxDekadeX) { maxDekadeX *= 10.0; minDekadeX /= 10.0; }
		anzDekadenX = anzDekaden(maxDekadeX, minDekadeX);
		if (anzDekadenX > 0) DekadenPixelX = DekadenPixel(anzDekadenX, nettoWidth); else DekadenPixelX = 1;
	}

	if (grid)
	{
		int GridCoorX;
		if (LinLin || LinLog)
		{
			for (int i = 0; i < NrGridX; i++)
			{
				GridCoorX = Round(CoorZero.x + (incrementX * i), 0);
				CPen Farbe; Farbe.CreatePen(PS_SOLID, 1, RGB(185, 185, 185));
				pDC->SelectObject(&Farbe);
				pDC->MoveTo(GridCoorX, CoorZero.y);
				pDC->LineTo(GridCoorX, CoorZero.y - nettoHeight);
				pDC->SelectStockObject(BLACK_PEN);
			}
		}

		if (LogLog || LogLin)
		{
			double Z = 2.0;
			for (int j = 0; j < anzDekadenX; j++)
			{
				double OffsetLog = DekadenPixelX * j;
				for (int i = 2; i <= 10; i++)
				{
					GridCoorX = Round(CoorZero.x + ((log10(Z) * DekadenPixelX) + OffsetLog), 0);
					CPen Farbe; Farbe.CreatePen(PS_SOLID, 1, RGB(185, 185, 185));
					pDC->SelectObject(&Farbe);
					pDC->MoveTo(GridCoorX, CoorZero.y);
					pDC->LineTo(GridCoorX, CoorZero.y - nettoHeight);
					Z++;
				}
				Z = 2;
			}
			pDC->SelectStockObject(BLACK_PEN);
		}
		int GridCoorY;
		if (LinLin || LogLin)
		{
			for (int i = 0; i < NrGridY; i++)
			{
				GridCoorY = Round(CoorZero.y - (incrementY * i), 0);
				CPen Farbe; Farbe.CreatePen(PS_SOLID, 1, RGB(185, 185, 185));
				pDC->SelectObject(&Farbe);
				pDC->MoveTo(CoorZero.x, GridCoorY);
				pDC->LineTo(CoorZero.x + nettoWidth, GridCoorY);
				pDC->SelectStockObject(BLACK_PEN);
			}
		}
		if (LogLog || LinLog)
		{
			double Z = 2.0;
			for (int j = 0; j < anzDekadenY; j++)
			{
				double OffsetLog = DekadenPixelY * j;
				for (int i = 2; i <= 10; i++)
				{
					GridCoorY = Round(CoorZero.y - ((log10(Z) * DekadenPixelY) + OffsetLog), 0);
					CPen Farbe; Farbe.CreatePen(PS_SOLID, 1, RGB(185, 185, 185));
					pDC->SelectObject(&Farbe);
					pDC->MoveTo(CoorZero.x, GridCoorY);
					pDC->LineTo(CoorZero.x + nettoWidth, GridCoorY);
					Z++;
				}
				Z = 2;
			}
			pDC->SelectStockObject(BLACK_PEN);
		}
	}

	int yPixelOffset = Round((nettoWidth / 100.0) * y2x, 0);
	int xPixelOffset = Round((nettoHeight / 100.0) * x2y, 0);

	//Achsen zeichnen
	pDC->MoveTo(CoorZero.x, CoorZero.y - xPixelOffset);
	pDC->LineTo(CoorZero.x + nettoWidth, CoorZero.y - xPixelOffset);
	pDC->MoveTo(CoorZero.x + yPixelOffset, CoorZero.y);
	pDC->LineTo(CoorZero.x + yPixelOffset, CoorZero.y - (nettoHeight));

	//Label zeichnen
	pDC->TextOut(CoorZero.x - 20 + yPixelOffset, CoorZero.y - nettoHeight - 30, AxesLabelY);
	pDC->TextOut(CoorZero.x + nettoWidth + 20, CoorZero.y - 15 - xPixelOffset, AxesLabelX);

	if (NrLabel)
	{
		int LabelCoorX; char AusgabeStrX[20];
		if (LinLin || LinLog)
		{
			for (int i = 0; i < NrLabelX; i++)
			{
				LabelCoorX = Round(CoorZero.x + (incrementX * i), 0);
				double ausgabeZahlX = minValueX + (StepX * i);
				sprintf_s(AusgabeStrX, LabelFormatX, ausgabeZahlX);
				pDC->TextOut(LabelCoorX - 4, CoorZero.y + 2 - xPixelOffset, AusgabeStrX);
				pDC->MoveTo(LabelCoorX, CoorZero.y - xPixelOffset);
				pDC->LineTo(LabelCoorX, CoorZero.y - 5 - xPixelOffset);
			}
		}

		int LabelCoorY; char AusgabeStrY[20];
		if (LinLin || LogLin)
		{
			for (int i = 0; i < NrLabelY; i++)
			{
				LabelCoorY = Round(CoorZero.y - (incrementY * i), 0);
				double ausgabeZahlY = minValueY + (StepY * i);
				sprintf_s(AusgabeStrY, LabelFormatY, ausgabeZahlY);
				pDC->TextOut(CoorZero.x - 25 + yPixelOffset, LabelCoorY - 7, AusgabeStrY);
				pDC->MoveTo(CoorZero.x + yPixelOffset, LabelCoorY);
				pDC->LineTo(CoorZero.x + yPixelOffset + 5, LabelCoorY);
			}
		}
		if (LinLog || LogLog)
		{
			double DekadenZahlY = minDekadeY;
			for (int i = 0; i < (anzDekadenY + 1); i++)
			{
				LabelCoorY = Round(CoorZero.y - (DekadenPixelY * i), 0);
				sprintf_s(AusgabeStrY, LabelFormatY, DekadenZahlY);
				pDC->TextOut(CoorZero.x - 40 + yPixelOffset, LabelCoorY - 7, AusgabeStrY);
				pDC->MoveTo(CoorZero.x + yPixelOffset, LabelCoorY);
				pDC->LineTo(CoorZero.x + 5 + yPixelOffset, LabelCoorY);
				DekadenZahlY = DekadenZahlY * 10;
			}
		}
		if (LogLog || LogLin)
		{
			double DekadenZahlX = minDekadeX;
			for (int i = 0; i < (anzDekadenX + 1); i++)
			{
				LabelCoorX = Round(CoorZero.x + (DekadenPixelX * i), 0);
				sprintf_s(AusgabeStrX, LabelFormatX, DekadenZahlX);
				pDC->TextOut(LabelCoorX - 4, CoorZero.y + 2 - xPixelOffset, AusgabeStrX);
				pDC->MoveTo(LabelCoorX, CoorZero.y - xPixelOffset);
				pDC->LineTo(LabelCoorX, CoorZero.y - 5 - xPixelOffset);
				DekadenZahlX = DekadenZahlX * 10;
			}
		}
	}

	//Datenwert nach Pixel wandeln
	if (LinLin) {
		D2ArryToPixelX(FunctionVar, CDataCount, nettoWidth, maxValueX, minValueX);
		D2ArryToPixelY(FunctionVar, CDataCount, nettoHeight, maxValueY, minValueY);
	}
	if (LinLog) {
		D2ArryToPixelX(FunctionVar, CDataCount, nettoWidth, maxValueX, minValueX);
		D2ArryToLogPixelY(FunctionVar, CDataCount, DekadenPixelY, failNrDekaden(minDekadeY));
	}
	if (LogLog) {
		D2ArryToLogPixelX(FunctionVar, CDataCount, DekadenPixelX, failNrDekaden(minDekadeX));
		D2ArryToLogPixelY(FunctionVar, CDataCount, DekadenPixelY, failNrDekaden(minDekadeY));
	}
	if (LogLin) {
		D2ArryToLogPixelX(FunctionVar, CDataCount, DekadenPixelX, failNrDekaden(minDekadeX));
		D2ArryToPixelY(FunctionVar, CDataCount, nettoHeight, maxValueY, minValueY);
	}

	//Windows Koordinate berechnen f r Y-Werte
	for (int j = 0; j < CDataCount; j++)
	{
		for (int i = 0; i < FunctionVar[j].getLengthArry(); i++)
		{
			FunctionVar[j].getYarry()[i] = CoorZero.y - FunctionVar[j].getYarry()[i];
		}
	}

	//Zeichnen
	for (int j = 0; j < CDataCount; j++)
	{
		CPen penToUse;
		if (FunctionVar[j].getPointView() == 0)//Linien
		{
			penToUse.CreatePen(PS_SOLID, 2, RGB(FunctionVar[j].getColor().getRed(), FunctionVar[j].getColor().getGreen(), FunctionVar[j].getColor().getBlue()));
			pDC->SelectObject(&penToUse);

			// Startpunkt sicherstellen
			if (FunctionVar[j].getLengthArry() > 0) {
				pDC->MoveTo(Round(CoorZero.x + FunctionVar[j].getXarry()[0], 0), Round(FunctionVar[j].getYarry()[0], 0));

				for (int i = 0; i < FunctionVar[j].getLengthArry(); i++)
				{
					pDC->LineTo(Round(CoorZero.x + FunctionVar[j].getXarry()[i], 0), Round(FunctionVar[j].getYarry()[i], 0));
					if (NameFunc == 1 && i + 1 == FunctionVar[j].getLengthArry())
					{
						pDC->SetTextColor(RGB(FunctionVar[j].getColor().getRed(), FunctionVar[j].getColor().getGreen(), FunctionVar[j].getColor().getBlue()));
						pDC->TextOut(Round(CoorZero.x + FunctionVar[j].getXarry()[i], 0), Round(FunctionVar[j].getYarry()[i], 0), FunctionVar[j].getName());
						pDC->SetTextColor(RGB(0, 0, 0));
					}
				}
			}
		}
		else//Punkte
		{
			penToUse.CreatePen(PS_SOLID, 4, RGB(FunctionVar[j].getColor().getRed(), FunctionVar[j].getColor().getGreen(), FunctionVar[j].getColor().getBlue()));
			pDC->SelectObject(&penToUse);

			for (int i = 0; i < FunctionVar[j].getLengthArry(); i++)
			{
				pDC->MoveTo(Round(CoorZero.x + FunctionVar[j].getXarry()[i], 0), Round(FunctionVar[j].getYarry()[i], 0));
				pDC->LineTo(Round(CoorZero.x + FunctionVar[j].getXarry()[i], 0), Round(FunctionVar[j].getYarry()[i], 0));

				if (NameFunc == 1 && i + 1 == FunctionVar[j].getLengthArry())
				{
					pDC->SetTextColor(RGB(FunctionVar[j].getColor().getRed(), FunctionVar[j].getColor().getGreen(), FunctionVar[j].getColor().getBlue()));
					pDC->TextOut(Round(CoorZero.x + FunctionVar[j].getXarry()[i], 0), Round(FunctionVar[j].getYarry()[i], 0), FunctionVar[j].getName());
					pDC->SetTextColor(RGB(0, 0, 0));
				}
			}
		}
		penToUse.DeleteObject();
	}
	pDC->SelectStockObject(BLACK_PEN);

	//FunctinVar Daten wiederherstellen
	for (int i = 0; i < CDataCount; i++)
	{
		FunctionVar[i] = FunctionVarSave[i];
	}

	// WICHTIG: Temporären Speicher freigeben (Leak Fix)
	delete[] FunctionVarSave;
}


//Hilfsfuntionen (Unverändert, nur sichergestellt, dass sie kompiliert werden)
//======================================================================================================
void D2ArryToPixelX(CData* Func, int XCount, int nettoScale, double maxValue, double minValue)
{
	for (int j = 0; j < XCount; j++)
	{
		for (int i = 0; i < Func[j].getLengthArry(); i++)
		{
			if (maxValue - minValue != 0)
				Func[j].getXarry()[i] = (nettoScale / (maxValue - minValue)) * (Func[j].getXarry()[i] - minValue);
		}
	}
}

void D2ArryToPixelY(CData* Func, int YCount, int nettoScale, double maxValue, double minValue)
{
	for (int j = 0; j < YCount; j++)
	{
		for (int i = 0; i < Func[j].getLengthArry(); i++)
		{
			if (maxValue - minValue != 0)
				Func[j].getYarry()[i] = (nettoScale / (maxValue - minValue)) * (Func[j].getYarry()[i] - minValue);
		}
	}
}
double D2highestValueX(CData* Func, int XCount)
{
	if (XCount == 0 || Func[0].getLengthArry() == 0) return 1.0;
	double PosMaxValue = Func[0].getXarry()[0];
	for (int j = 0; j < XCount; j++)
	{
		for (int i = 0; i < Func[j].getLengthArry(); i++)
		{
			if (PosMaxValue < Func[j].getXarry()[i]) PosMaxValue = Func[j].getXarry()[i];
		}
	}
	return PosMaxValue;
}

double D2leastValueX(CData* Func, int XCount)
{
	if (XCount == 0 || Func[0].getLengthArry() == 0) return 0.0;
	double NegMaxValue = Func[0].getXarry()[0];
	for (int j = 0; j < XCount; j++)
	{
		for (int i = 0; i < Func[j].getLengthArry(); i++)
		{
			if (NegMaxValue > Func[j].getXarry()[i]) NegMaxValue = Func[j].getXarry()[i];
		}
	}
	return NegMaxValue;
}
double D2highestValueY(CData* Func, int YCount)
{
	if (YCount == 0 || Func[0].getLengthArry() == 0) return 1.0;
	double PosMaxValue = Func[0].getYarry()[0];
	for (int j = 0; j < YCount; j++)
	{
		for (int i = 0; i < Func[j].getLengthArry(); i++)
		{
			if (PosMaxValue < Func[j].getYarry()[i]) PosMaxValue = Func[j].getYarry()[i];
		}
	}
	return PosMaxValue;
}

double D2leastValueY(CData* Func, int YCount)
{
	if (YCount == 0 || Func[0].getLengthArry() == 0) return 0.0;
	double NegMaxValue = Func[0].getYarry()[0];
	for (int j = 0; j < YCount; j++)
	{
		for (int i = 0; i < Func[j].getLengthArry(); i++)
		{
			if (NegMaxValue > Func[j].getYarry()[i]) NegMaxValue = Func[j].getYarry()[i];
		}
	}
	return NegMaxValue;
}

int NrLabelSearch(int nettoScale)
{
	if (nettoScale < 200) return 3;
	if (nettoScale < 400) return 4;
	if (nettoScale < 600) return 6;
	if (nettoScale < 800) return 8;
	return 10;
}

double minDekade(double minValue)
{
	double minDekade = 100000000000.0;
	if (minValue <= 0) return 0.001; // Schutz gegen 0 oder negativ bei Log
	while (minDekade > minValue)
	{
		minDekade = minDekade / 10.0;
	}
	return minDekade;
}
double maxDekade(double maxValue)
{
	double maxDekade = 0.0000000001;
	if (maxValue <= 0) return 100.0;
	while (maxDekade < maxValue)
	{
		maxDekade = maxDekade * 10.0;
	}
	return maxDekade;
}
int anzDekaden(double maxDekade, double minDekade)
{
	if (minDekade <= 0) return 1;
	double Var = maxDekade;
	int count = 0;
	while (Var > minDekade)
	{
		Var = Var / 10.0;
		count++;
	}
	return count;
}
int DekadenPixel(int anzDekaden, int nettoScale)
{
	if (anzDekaden == 0) return nettoScale;
	return nettoScale / anzDekaden;
}

void D2ArryToLogPixelX(CData* Func, int XCount, int DekadenPixel, int anzFailDekande)
{
	for (int j = 0; j < XCount; j++)
	{
		for (int i = 0; i < Func[j].getLengthArry(); i++)
		{
			if (Func[j].getXarry()[i] > 0)
				Func[j].getXarry()[i] = (log10(Func[j].getXarry()[i]) * DekadenPixel) - (DekadenPixel * anzFailDekande);
		}
	}
}
void D2ArryToLogPixelY(CData* Func, int YCount, int DekadenPixel, int anzFailDekande)
{
	for (int j = 0; j < YCount; j++)
	{
		for (int i = 0; i < Func[j].getLengthArry(); i++)
		{
			if (Func[j].getYarry()[i] > 0)
				Func[j].getYarry()[i] = (log10(Func[j].getYarry()[i]) * DekadenPixel) - (DekadenPixel * anzFailDekande);
		}
	}
}

double Round(double Zahl, int Stellen)
{
	return floor(Zahl * pow(10.0, Stellen) + 0.5) * pow(10.0, -Stellen);
}
int failNrDekaden(double minDekade)
{
	double Zahl = minDekade;
	int count = 0;
	if (minDekade >= 1) {
		while (Zahl > 1) { Zahl /= 10.0; count++; }
	}
	else {
		while (Zahl < 1 && Zahl > 0) { Zahl *= 10.0; count++; }
		count = count * (-1);
	}
	return count;
}