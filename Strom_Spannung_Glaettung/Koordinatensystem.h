#pragma once
/**
 * KLASSEN: CData & CKoordinatensystem
 * ----------------------------------------------------------------
 * Dieses Modul bildet die grafische Engine zur Visualisierung von
 * Simulationsdaten in einem 2D-Koordinatensystem.
 *
 * Hauptaufgaben CData:
 * - Datenkapselung: Speicherung von XY-Wertepaaren, Farben und Namen für
 * einzelne Funktionsgraphen.
 * - Speichermanagement: Dynamische Verwaltung von Daten-Arrays mit
 * implementiertem Kopierkonstruktor und Destruktor zur Vermeidung von Memory Leaks.
 *
 * Hauptaufgaben CKoordinatensystem:
 * - Skalierung & Transformation: Umrechnung physikalischer Größen in
 * Bildschirmkoordinaten (Linear und Logarithmisch).
 * - Automatisierung: Optionale AutoScale-Funktion zur optimalen Einpassung
 * der Kurven in den verfügbaren Zeichnungsbereich.
 * - Rendering: Zeichnen von Achsen, Gitternetzen (Grids), Labels und den
 * eigentlichen Funktionsverläufen mittels GDI.
 */
#include "afx.h"
#include "atltypes.h"
#include "pch.h"

class CColor						//RGB
{
private:
	int red;						//Rot
	int green;						//Grün
	int blue;						//Blau
public:
	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);
	int getRed(void);
	int getGreen(void);
	int getBlue(void);
	CColor(void);					//Standard-Konstruktor
	CColor(const CColor& color);	//Kopier-Konstruktor
};

class CData
{
private:
	double* Xarry;			//Daten Arry für X-Koordinaten
	double* Yarry;			//Daten Arry für Y-Koordinaten
	int lengthArry;			//Länge des Feldes
	char Name[10];			//Name der Funktion;
	bool PointView;			//Punktdarstellung ON/OFF
	CColor	Color;			//Farbe der Funktion
public:
	void setRed(void);
	void setGreen(void);
	void setBlue(void);
	void setYellow(void);
	void setOrgange(void);
	void setPurple(void);
	void setBlack(void);
	void setGrau(void);
	void setXYdata(double arryX[], double arryY[], int length);	//zum einlesen der X-Y Funktionswerte und Größe des Feldes
	int getLengthArry(void);
	void setPointView(void);
	bool getPointView(void);
	void setName(char name[10]);
	char* getName(void);
	CColor getColor(void);
	double* getXarry(void);
	double* getYarry(void);
	CData(void);				//Standard-Konstruktor
	CData(const CData& CD);		//Kopier-Konstruktor
	~CData(void); // Destruktor
	CData& operator=(const CData& other);
};

class CKoordinatensystem
{
private:
	CData* FunctionVar;	//Funktionswerte
	int CDataCount;			//Anzahl der Funktionen
	double minValueY;		//kleinster Y-Wert
	double maxValueY;		//größter Y-Wert
	double minValueX;		//kleinster X-Wert
	double maxValueX;		//größter X-Wert
	int nettoWidth;			//Breite in Pixel
	int nettoHeight;		//Höhe in Pixel
	int x2y;				//verhältnis zwischen X und Y Achse
	int y2x;				//verhältnis zwischen Y und X Achse
	bool grid;				//Gitter ON/OFF (1,0)
	bool LinLin;			//Darstellung Linear(X-Achse) zu Linear(Y-SAchse)
	bool LinLog;			//Darstellung Linear(X-Achse) zu Logarithmisch(Y-Achse)
	bool LogLin;			//Darstellung Logarithmisch(X-Achse) zu Linear(Y-Achse)		
	bool LogLog;			//Darstellung Logarithmisch(X-Achse) zu Logarithmisch(Y-Achse)
	CPoint CoorZero;		//Koordinatensystem Nullpunkt (x/y) in Pixel in Windows Koordinaten
	bool NrLabel;			//Achsenbeschriftung ON/OFF (1,0)
	bool AutoScale;			//automatische-Skalierung(1) manuelle-Skalierung(0)
	double StepX;			// Schrittweite X-Achse Einheit[Wert]
	double StepY;			// Schrittweite Y-Achse Einheit[Wert]
	char LabelFormatX[10];	//Ausgabeformat der X-Achsen Beschriftung
	char LabelFormatY[10];	//Ausgabeformat der Y-Achsen Beschriftung
	char AxesLabelX[10];	//Name der X-Achse
	char AxesLabelY[10];	//Name der Y-Achse
	bool NameFunc;			//Funktionsname ON/OFF (1,0)

public:
	void addData(CData CDObject);
	void Draw(CDC* pDC);								//Zeichenfunktion, Aufrufen zum Koordinatensystem darstellen
	void setManuScale(double stepX, double stepY, double MaxValueX, double MaxValueY, double MinValueX, double MinValueY);
	void setAutoScale(void);
	void setGridOFF(void);								//Hilfsgitter ON
	void setGridON(void);								//Hilfsgitter OFF
	void setLinLinON(void);								//standardmäßig aktiv
	void setLinLinOFF(void);
	void setLinLogON(void);
	void setLinLogOFF(void);
	void setLogLinON(void);
	void setLogLinOFF(void);
	void setLogLogON(void);
	void setLogLogOFF(void);
	void setNameFunc(void);
	void setNettoWidth(int width);						//Höhe des Koordinatensystem in Pixel
	void setNettoHeight(int height);					//Breite des Koordinatensystem in Pixel
	void setCoorZero(int xCoor, int yCoor);				//setzt Koordinaten-Nullpunkt(Anfangspunkt)
	void setNrLabelOFF(void);							//Achsen Nummerierung OFF
	void setNrLabelON(void);							//Achsen Nummerierung ON
	void setAxesLabelX(char name[10]);
	void setAxesLabelY(char name[10]);
	void setLabelFormatX(char Format[10]);
	void setLabelFormatY(char Format[10]);
	void setx2y(double xOffset);
	void sety2x(double yOffset);
	CData* getCData(void);
	double getMinValueY(void);
	double getMaxValueY(void);
	double getMinValueX(void);
	double getMaxValueX(void);
	double getStepX(void);
	double getStepY(void);
	int getNettoWidth(void);
	int getNettoHeight(void);
	int getX2Y(void);
	int getY2X(void);
	int getCDataCount(void);
	bool getGrid(void);
	bool getLinLin(void);
	bool getLogLin(void);
	bool getLinLog(void);
	bool getLogLog(void);
	bool getNrLabel(void);
	bool getAutoScale(void);
	bool getNameFunc(void);
	char* getLabelFormatX(void);
	char* getLabelFormatY(void);
	char* getAxesLabelX(void);
	char* getAxesLabelY(void);
	CPoint getCoorZero(void);
	CKoordinatensystem(void);		//Standard-Konstruktor
	~CKoordinatensystem(void);		//Default-Konstruktor
	// NEU HINZUFÜGEN:
	void ClearData();
};




