#pragma once

#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QtGui/QListWidget>
#include <QtOpenGL/QGLWidget>

#include "Controller/MasterController.h"

class RenderWindow : public QGLWidget
{
	Q_OBJECT
	public:
		RenderWindow(MasterController& masterController, QString dataset, QListWidget *listWidget_Lock, unsigned int iCounter, QGLWidget* glWidget, QWidget* parent = 0, Qt::WindowFlags flags = 0);
		virtual ~RenderWindow();

		QString GetDataset() {return m_strDataset;}
		QSize minimumSizeHint() const;
		QSize sizeHint() const;

	public slots:
		void ToggleRenderWindowView1x3();
		void ToggleRenderWindowView2x2();
		void ToggleRenderWindowViewSingle();

	signals:
		void RenderWindowViewChanged(int iViewID);

	protected:
		void initializeGL();
		void paintGL();
		void resizeGL(int width, int height);
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
		void closeEvent(QCloseEvent *event);

	private:
		MasterController&		m_MasterController;
		GPUSBVR*				m_Renderer;
		
		void normalizeAngle(int *angle);
		int xRot;
		QPoint lastPos;
		
		QString m_strDataset;
		QString m_strID;
		QListWidget *m_listWidget_Lock;

};

#endif // RENDERWINDOW_H
