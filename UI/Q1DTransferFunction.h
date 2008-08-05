#pragma once

#ifndef Q1DTRANSFERFUNCTION
#define Q1DTRANSFERFUNCTION

#include <QtGui/QWidget>
#include <IO/TransferFunction1D.h>

#define Q1DT_PAINT_NONE  0
#define Q1DT_PAINT_RED   1
#define Q1DT_PAINT_GREEN 2
#define Q1DT_PAINT_BLUE  4
#define Q1DT_PAINT_ALPHA 8
#define Q1DT_PAINT_UNDEF 16

class Q1DTransferFunction : public QWidget
{
	Q_OBJECT

	public:
		Q1DTransferFunction(QWidget *parent=0);
		virtual ~Q1DTransferFunction(void);
		void SetData(const Histogram1D& vHistrogram, TransferFunction1D* Trans);
		void SetPaintmode(unsigned int iPaintmode) {if (iPaintmode < Q1DT_PAINT_UNDEF) m_iPaintmode = iPaintmode;};

	public slots:
		bool LoadFromFile(const QString& strFilename);
		bool SaveToFile(const QString& strFilename);
	
	protected:
		virtual void paintEvent(QPaintEvent *event);
		virtual void mouseMoveEvent(QMouseEvent *event);
		virtual void mousePressEvent(QMouseEvent *event);
		virtual void mouseReleaseEvent(QMouseEvent *event);
		virtual void changeEvent(QEvent * event);

	private:
		// states
		NormalizedHistogram1D m_vHistrogram;
		TransferFunction1D* m_pTrans;
		unsigned int m_iPaintmode;

		// cached image of the backdrop
		bool		 m_bBackdropCacheUptodate;
		unsigned int m_iCachedHeight;
		unsigned int m_iCachedWidth;
		QPixmap*	 m_pBackdropCache;

		// borders, may be changed in the constructor 
		unsigned int m_iLeftBorder;
		unsigned int m_iBottomBorder;

		// automatically computed borders (computed by DrawCoordinateSystem)
		unsigned int m_iRightBorder;
		unsigned int m_iTopBorder;

		// colors, may be changed in the setcolor 
		QColor m_colorHistogram;
		QColor m_colorBack;
		QColor m_colorBorder;
		QColor m_colorScale;
		QColor m_colorLargeScale;
		QColor m_colorRedLine;
		QColor m_colorGreenLine;
		QColor m_colorBlueLine;
		QColor m_colorAlphaLine;

		void SetColor(bool bIsEnabled);

		// scale apearance, may be changed in the constructor 
		unsigned int m_iMarkersX;
		unsigned int m_iMarkersY;
		unsigned int m_iBigMarkerSpacingX;
		unsigned int m_iBigMarkerSpacingY;
		unsigned int m_iMarkerLength;
		unsigned int m_iBigMarkerLength;

		// mouse motion handling
		int m_iLastIndex;
		float m_fLastValue;

		// drawing routines
		void DrawCoordinateSystem(QPainter& painter);
		void DrawHistogram(QPainter& painter);
		void DrawFunctionPlots(QPainter& painter);
};


#endif // Q1DTRANSFERFUNCTION
