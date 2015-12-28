#include "stdafx.h"
#include "ZeroIScene.h"
#include "ZeroCameraManager.h"
#include "ZeroEffectManager.h"
#include "ZeroMathManager.h"
#include "ZeroApplication.h"

#pragma warning(disable: 4996)

#define GETA(c) (((c)&0xff000000)>>24)
#define GETR(c) (((c)&0x00ff0000)>>16)
#define GETG(c) (((c)&0x0000ff00)>>8)
#define GETB(c) ((c)&0x000000ff)

ZeroIScene::ZeroIScene()
	: m_vPos(0.0f, 0.0f), m_vScale(1.0f, 1.0f), m_vScalingCenter(0.0f, 0.0f), m_vRotCenter(0.0f, 0.0f), m_fRot(0.0f),
	m_Color(D3DCOLOR_ARGB(255, 255, 255, 255)), m_bCamera(true), m_ColorTemp(D3DCOLOR_ARGB(255, 255, 255, 255)), m_fStartToCurrentTime(0.0f), m_bUpdate(true) {

	SetRect(0, 0, 0, 0);
	SetErase(false);
	SetParent(NULL);
	D3DXMatrixIdentity(&m_Mat);
	SetWorldPos(0, 0);

	SetWidth(0);
	SetHeight(0);

	SetHwnd(GetForegroundWindow());
}

ZeroIScene::~ZeroIScene() {
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		SAFE_DELETE(*iter);
	}
	m_Node.clear();
}

void ZeroIScene::Update(float _eTime) {
	m_fStartToCurrentTime += _eTime;

	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter)->m_bUpdate == true)
			(*iter)->Update(_eTime);

		if ((*iter)->IsErase()) {
			SAFE_DELETE(*iter);
			iter = m_Node.erase(iter);
			if (iter == m_Node.end()) break;
		}
	}

	UpdateWorldPos();
}

void ZeroIScene::UpdateWorldPos() {
	if (ZeroCameraMgr->IsCamera()) {
		//부모 객체를 모두 돌려 m_bCamera 가 false인 객체가 있는지 없는지 확인한다.
		bool isCamera = true;
		ZeroIScene* parent = m_pParent;
		while (parent) {
			if (!parent->m_bCamera) {
				isCamera = false;
				break;
			}
			parent = parent->m_pParent;
		}


		if (m_pParent == NULL) {
			//만약 최상위 객체가 카메라 설정이 안되있으면 카메라 매니저의 카메라기능을 해제
			if (!m_bCamera) {
				ZeroCameraMgr->SetCameraOff();
			}
			SetWorldPos(Pos() - ZeroCameraMgr->Pos());
		}
		else {		//최상위 객체가 아니라면?
			//카메라 기능이 설정되어 있으면 그냥 Pos를 넣어준다.
			if (m_bCamera) {
				SetWorldPos(Pos());
			}
			else {
				//객체의 카메라기능이 꺼져있고 부모객체가 모두 켜져있을때
				if (isCamera) {
					//카메라매니저가 돌려놨던 Pos만큼 되돌려서 빌보드 출력을 한다.
					SetWorldPos(Pos() + ZeroCameraMgr->Pos());
				}
				else {
					//부모객체중 하나라도 꺼져 있을 때 그냥 Pos를 넣어준다.
					SetWorldPos(Pos());
				}
			}
		}
	}
	else {
		//카메라매니저의 카메라기능이 꺼져있으므로 정상 빌보드 출력.
		SetWorldPos(Pos());
	}
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter)->m_bUpdate == true)
			(*iter)->UpdateWorldPos();
	}
}

void ZeroIScene::Render() {
	UpdateWorldPos();
	D3DXMatrixTransformation2D(&m_Mat, &m_vScalingCenter, 0.0f, &m_vScale, &m_vRotCenter, m_fRot * 3.141592f / 180.0f, &m_vWorldPos);
	if (m_pParent != NULL)
		m_Mat *= m_pParent->m_Mat;

	//컬러 상속
	if (m_pParent != NULL) {
		m_Color = D3DCOLOR_ARGB(
			(int) (GETA(m_ColorTemp) * GETA(m_pParent->m_Color) / 255.0f),
			(int) (GETR(m_ColorTemp) * GETR(m_pParent->m_Color) / 255.0f),
			(int) (GETG(m_ColorTemp) * GETG(m_pParent->m_Color) / 255.0f),
			(int) (GETB(m_ColorTemp) * GETB(m_pParent->m_Color) / 255.0f)
			);
	}
	else {
		m_Color = m_ColorTemp;
	}
}

void ZeroIScene::PushScene(ZeroIScene* _scene, bool update/*=true*/) {
	if (_scene == this) {
		assert(!"자기 자신을 Push할 수 없습니다");
		return;
	}
	_scene->m_bUpdate = update;
	_scene->m_pParent = this;
	m_Node.push_back(_scene);
}

void ZeroIScene::PopScene(ZeroIScene* _scene, bool isErase) {
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter) == _scene) {
			if (isErase) {
				SAFE_DELETE(*iter);
			}
			else {
				(*iter)->m_pParent = NULL;
			}
			m_Node.erase(iter);
			break;
		}
	}
}

bool ZeroIScene::IsExistScene(ZeroIScene* _scene) {
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter) == _scene) {
			return true;
		}
	}
	return false;
}

bool ZeroIScene::IsOverlapped(ZeroIScene* _scene) {
	D3DXMATRIX mat1 = m_Mat;
	D3DXMATRIX mat2 = _scene->Mat();
	D3DXMATRIX mat1Inv;	D3DXMatrixInverse(&mat1Inv, NULL, &mat1);
	D3DXMATRIX mat2Inv;	D3DXMatrixInverse(&mat2Inv, NULL, &mat2);

	ZeroVec topLeft2 = ZeroVec(0.0f, 0.0f);
	ZeroVec topRight2 = ZeroVec(0.0f + _scene->Width(), 0.0f);
	ZeroVec bottomLeft2 = ZeroVec(0.0f, 0.0f + _scene->Height());
	ZeroVec bottomRight2 = ZeroVec(0.0f + _scene->Width(), 0.0f + _scene->Height());

	D3DXVec2TransformCoord(&topLeft2, &topLeft2, &mat2);
	D3DXVec2TransformCoord(&topRight2, &topRight2, &mat2);
	D3DXVec2TransformCoord(&bottomLeft2, &bottomLeft2, &mat2);
	D3DXVec2TransformCoord(&bottomRight2, &bottomRight2, &mat2);

	D3DXVec2TransformCoord(&topLeft2, &topLeft2, &mat1Inv);
	D3DXVec2TransformCoord(&topRight2, &topRight2, &mat1Inv);
	D3DXVec2TransformCoord(&bottomLeft2, &bottomLeft2, &mat1Inv);
	D3DXVec2TransformCoord(&bottomRight2, &bottomRight2, &mat1Inv);

	if (IsPosInRect(m_Rect, topLeft2) || IsPosInRect(m_Rect, topRight2) || IsPosInRect(m_Rect, bottomLeft2) || IsPosInRect(m_Rect, bottomRight2)) {
		return true;
	}
	else {
		ZeroVec topLeft1 = ZeroVec(0.0f, 0.0f);
		ZeroVec topRight1 = ZeroVec(0.0f + Width(), 0.0f);
		ZeroVec bottomLeft1 = ZeroVec(0.0f, 0.0f + Height());
		ZeroVec bottomRight1 = ZeroVec(0.0f + Width(), 0.0f + Height());

		D3DXVec2TransformCoord(&topLeft1, &topLeft1, &mat1);
		D3DXVec2TransformCoord(&topRight1, &topRight1, &mat1);
		D3DXVec2TransformCoord(&bottomLeft1, &bottomLeft1, &mat1);
		D3DXVec2TransformCoord(&bottomRight1, &bottomRight1, &mat1);

		D3DXVec2TransformCoord(&topLeft1, &topLeft1, &mat2Inv);
		D3DXVec2TransformCoord(&topRight1, &topRight1, &mat2Inv);
		D3DXVec2TransformCoord(&bottomLeft1, &bottomLeft1, &mat2Inv);
		D3DXVec2TransformCoord(&bottomRight1, &bottomRight1, &mat2Inv);

		if (IsPosInRect(_scene->Rect(), topLeft1) || IsPosInRect(_scene->Rect(), topRight1) || IsPosInRect(_scene->Rect(), bottomLeft1) || IsPosInRect(_scene->Rect(), bottomRight1)) {
			return true;
		}
	}
	return false;
}

bool ZeroIScene::IsOverlapped(ZeroVec pos) {
	D3DXMATRIX mat1 = m_Mat;
	D3DXMATRIX mat1Inv;	D3DXMatrixInverse(&mat1Inv, NULL, &mat1);

	D3DXVec2TransformCoord(&pos, &pos, &mat1Inv);

	if (IsPosInRect(m_Rect, pos))
		return true;
	return false;
}

bool ZeroIScene::IsPosInRect(ZeroRect rect, ZeroVec pos) {
	if (rect.left < pos.x && rect.right > pos.x && rect.top < pos.y && rect.bottom > pos.y)
		return true;
	return false;
}

void ZeroIScene::SetColorA(int color) {
	ZeroMathMgr->Clamp(color, 0, 255);
	m_ColorTemp = D3DCOLOR_ARGB(color, GETR(m_ColorTemp), GETG(m_ColorTemp), GETB(m_ColorTemp));
}

void ZeroIScene::SetColorR(int color) {
	ZeroMathMgr->Clamp(color, 0, 255);
	m_ColorTemp = D3DCOLOR_ARGB(GETA(m_ColorTemp), color, GETG(m_ColorTemp), GETB(m_ColorTemp));
}

void ZeroIScene::SetColorG(int color) {
	ZeroMathMgr->Clamp(color, 0, 255);
	m_ColorTemp = D3DCOLOR_ARGB(GETA(m_ColorTemp), GETR(m_ColorTemp), color, GETB(m_ColorTemp));
}

void ZeroIScene::SetColorB(int color) {
	ZeroMathMgr->Clamp(color, 0, 255);
	m_ColorTemp = D3DCOLOR_ARGB(GETA(m_ColorTemp), GETR(m_ColorTemp), GETG(m_ColorTemp), color);
}

#undef GETA
#undef GETR
#undef GETG
#undef GETB
