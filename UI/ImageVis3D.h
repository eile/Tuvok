#pragma once

#ifndef IMAGEVIS3D_H
#define IMAGEVIS3D_H

#include "AutoGen/ui_ImageVis3D.h"
#include "RenderWindow.h"
#include "Q1DTransferFunction.h"
#include "Q2DTransferFunction.h"
#include "Controller/MasterController.h"
#include "DebugOut/QTOut.h"

class MainWindow : public QMainWindow, protected Ui_MainWindow
{
	Q_OBJECT
	public:
		MainWindow(MasterController& masterController, QWidget* parent = 0, Qt::WindowFlags flags = 0);
		virtual ~MainWindow();
	
		QTOut* GetDebugOut() {return m_DebugOut;}

	protected slots:
		void LoadDataset();
		void LoadDirectory();
		void CloneCurrentView();

		void ToggleRenderWindowView1x3();
		void ToggleRenderWindowView2x2();
		void ToggleRenderWindowViewSingle();

		void Transfer1DCBClicked();
		void Transfer1DRadioClicked();

		void Use1DTrans();
		void Use2DTrans();
		void UseIso();

		bool LoadWorkspace();
		bool SaveWorkspace();
		bool ApplyWorkspace();

		bool LoadGeometry();
		bool SaveGeometry();

		void OpenRecentFile();
		void ClearMRUList();

		void UpdateMenus();

		void SaveDataset();
		void Load1DTrans();
		void Save1DTrans();
		void Load2DTrans();
		void Save2DTrans();

		void EditViewLocks();
		void EditRenderLocks();
		void EditToolsLocks();
		void EditFiltersLocks();

		void RenderWindowActive(RenderWindow* sender);
		void RenderWindowClosing(RenderWindow* sender);


	private :
		MasterController&		m_MasterController;
		QString					m_strCurrentWorkspaceFilename;
		Q1DTransferFunction*	m_1DTransferFunction;
		Q2DTransferFunction*	m_2DTransferFunction;
		QGLWidget*				m_glShareWidget;
		QTOut*					m_DebugOut;
		RenderWindow*			m_ActiveRenderWin;

		RenderWindow* CreateNewRenderWindow(QString dataset);
		RenderWindow* GetActiveRenderWindow();

		void SetupWorkspaceMenu();
		bool LoadWorkspace(QString strFilename, bool bSilentFail = false, bool bRetryResource = true);
		bool SaveWorkspace(QString strFilename);

		bool LoadGeometry(QString strFilename, bool bSilentFail = false, bool bRetryResource = true);
		bool SaveGeometry(QString strFilename);

		QString strippedName(const QString &fullFileName);
		static const unsigned int ms_iMaxRecentFiles = 5;
		QAction *m_recentFileActs[ms_iMaxRecentFiles];
		void UpdateMRUActions();
		void AddFileToMRUList(const QString &fileName);

		void setupUi(QMainWindow *MainWindow);
		
		void LoadDataset(QString fileName);
		
};

#endif // IMAGEVIS3D_H
