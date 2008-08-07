#include "GPUMemMan.h"
#include "../IO/Images/BMPLoader.h"
#include "../Controller/MasterController.h"
#include "GLInclude.h"

using namespace std;

GPUMemMan::GPUMemMan(MasterController* masterController) :
	m_MasterController(masterController)
{

}

GPUMemMan::~GPUMemMan() {

}


VolumeDataset* GPUMemMan::LoadDataset(const std::string& strFilename, AbstrRenderer* requester) {
	for (VolDataListIter i = m_vpVolumeDatasets.begin();i<m_vpVolumeDatasets.end();i++) {
		if (i->pVolumeDataset->Filename() == strFilename) {
			m_MasterController->DebugOut()->Message("GPUMemMan::LoadDataset","Reusing %s", strFilename.c_str());
			i->qpUser.push_back(requester);
			return i->pVolumeDataset;
		}
	}

	m_MasterController->DebugOut()->Message("GPUMemMan::LoadDataset","Loading %s", strFilename.c_str());
	VolumeDataset* dataset = new VolumeDataset(strFilename);
	if (dataset->IsLoaded()) {
		m_vpVolumeDatasets.push_back(VolDataListElem(dataset, requester));
		return dataset;
	} else return NULL;
}


void GPUMemMan::FreeDataset(VolumeDataset* pVolumeDataset, AbstrRenderer* requester) {
	for (VolDataListIter i = m_vpVolumeDatasets.begin();i<m_vpVolumeDatasets.end();i++) {
		if (i->pVolumeDataset == pVolumeDataset) {
			for (AbstrRendererListIter j = i->qpUser.begin();j<i->qpUser.end();j++) {
				if (*j == requester) {
					i->qpUser.erase(j);
					if (i->qpUser.size() == 0) {
						m_MasterController->DebugOut()->Message("GPUMemMan::FreeDataset","Released Dataset %s", pVolumeDataset->Filename().c_str());
						delete pVolumeDataset;
						m_vpVolumeDatasets.erase(i);
					} else {
						m_MasterController->DebugOut()->Message("GPUMemMan::FreeDataset","Decreased access count but dataset %s is still in use by another subsystem", pVolumeDataset->Filename().c_str());
					}
					return;
				}
				break;
			}
		}
	}
	m_MasterController->DebugOut()->Warning("GPUMemMan::FreeDataset","Dataset %s not found or not being used by requester", pVolumeDataset->Filename().c_str());
}

GLTexture2D* GPUMemMan::Load2DTextureFromFile(const std::string& strFilename) {
	for (SimpleTextureListIter i = m_vpSimpleTextures.begin();i<m_vpSimpleTextures.end();i++) {
		if (i->strFilename == strFilename) {
			m_MasterController->DebugOut()->Message("GPUMemMan::Load2DTextureFromFile","Reusing %s", strFilename.c_str());
			i->iAccessCounter++;
			return i->pTexture;
		}
	}

	TextureImage image;
	if (!BMPLoader::Load(strFilename, &image)) {
		m_MasterController->DebugOut()->Error("GPUMemMan::Load2DTextureFromFile","Unable to load file %s", strFilename.c_str());
		return NULL;
	}
	m_MasterController->DebugOut()->Message("GPUMemMan::Load2DTextureFromFile","Loading %s", strFilename.c_str());

	GLTexture2D* tex = new GLTexture2D(image.width,image.height, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, image.data, GL_LINEAR, GL_LINEAR);
	delete [] image.data;

	m_vpSimpleTextures.push_back(SimpleTextureListElem(1,tex,strFilename));
	return tex;
}


void GPUMemMan::FreeTexture(GLTexture2D* pTexture) {
	for (SimpleTextureListIter i = m_vpSimpleTextures.begin();i<m_vpSimpleTextures.end();i++) {
		if (i->pTexture == pTexture) {
			i->iAccessCounter--;
			if (i->iAccessCounter == 0) {
				m_MasterController->DebugOut()->Message("GPUMemMan::FreeTexture","Deleted texture %s", i->strFilename.c_str());
				i->pTexture->Delete();
				m_vpSimpleTextures.erase(i);
			} else {
				m_MasterController->DebugOut()->Message("GPUMemMan::FreeTexture","Decreased access count but the texture %s is still in use by another subsystem",i->strFilename.c_str());
			}
			return;
		}
	}
	m_MasterController->DebugOut()->Warning("GPUMemMan::FreeTexture","Texture not found");
}


void GPUMemMan::GetEmpty1DTrans(size_t iSize, AbstrRenderer* requester, TransferFunction1D** transferFunc, GLTexture1D** tex) {
	m_MasterController->DebugOut()->Message("GPUMemMan::GetEmpty1DTrans","Creating new empty 1D transfer function");
	*transferFunc = new TransferFunction1D(iSize);
	*tex = new GLTexture1D(iSize, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);

	m_vpTrans1DList.push_back(Trans1DListElem(*transferFunc, *tex, requester));
}

void GPUMemMan::Get1DTransFromFile(const std::string& strFilename, AbstrRenderer* requester, TransferFunction1D** transferFunc, GLTexture1D** tex) {
	// TODO
}

GLTexture1D* GPUMemMan::Access1DTrans(TransferFunction1D* transferFunc, AbstrRenderer* requester) {
	// TODO
	return NULL;
}

void GPUMemMan::Free1DTrans(TransferFunction1D* transferFunc, AbstrRenderer* requester) {
	// TODO
}

void GPUMemMan::GetEmpty2DTrans(const VECTOR2<size_t>& iSize, AbstrRenderer* requester, TransferFunction2D** transferFunc, GLTexture2D** tex) {
	m_MasterController->DebugOut()->Message("GPUMemMan::GetEmpty2DTrans","Creating new empty 2D transfer function");
	*transferFunc = new TransferFunction2D(iSize);
	*tex = new GLTexture2D(GLuint(iSize.x), GLuint(iSize.y), GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE);

	m_vpTrans2DList.push_back(Trans2DListElem(*transferFunc, *tex, requester));
}

void GPUMemMan::Get2DTransFromFile(const std::string& strFilename, AbstrRenderer* requester, TransferFunction2D** transferFunc, GLTexture2D** tex) {
	// TODO
}

GLTexture2D* GPUMemMan::Access2DTrans(TransferFunction2D* transferFunc, AbstrRenderer* requester) {
	// TODO
	return NULL;
}

void GPUMemMan::Free2DTrans(TransferFunction2D* transferFunc, AbstrRenderer* requester) {
	// TODO
}
