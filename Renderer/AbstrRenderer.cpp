#include "AbstrRenderer.h"
#include "../Controller/MasterController.h"

using namespace std;

bool AbstrRenderer::LoadDataset(const string& strFilename) {
	if (m_pMasterController == NULL) return false;
	if (m_pMasterController->MemMan() == NULL) {
		m_pMasterController->DebugOut()->Error("AbstrRenderer::LoadDataset","Cannont load dataset because m_pMasterController->MemMan() == NULL");
		return false;
	}

	m_pDataset = m_pMasterController->MemMan()->LoadDataset(strFilename,this);

	m_pMasterController->MemMan()->GetEmpty1DTrans(1<<m_pDataset->GetInfo()->GetBitwith(), this, &m_p1DTrans, &m_p1DTransTex);
	m_pMasterController->MemMan()->GetEmpty2DTrans(VECTOR2<size_t>(1<<m_pDataset->GetInfo()->GetBitwith(), 256), this, &m_p2DTrans, &m_p2DTransTex);  // TODO: decide: always 8bit gradient ?

	if (m_pDataset == NULL) {
		m_pMasterController->DebugOut()->Error("AbstrRenderer::LoadDataset","MemMan call to load dataset failed");
		return false;
	}

	return true;
}

AbstrRenderer::~AbstrRenderer() {
	m_pMasterController->MemMan()->FreeDataset(m_pDataset, this);
}
