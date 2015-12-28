#include "stdafx.h"
#include "ZeroResource.h"
#include "ZeroResourceManager.h"

#pragma warning(disable: 4996)

ZeroResource::ZeroResource() {
	ZeroResourceMgr->RegisterResource(this);
}

ZeroResource::~ZeroResource() {
	ZeroResourceMgr->UnRegisterResource(this);
}

void ZeroResource::OnPrevDeviceReset() {

}

void ZeroResource::OnPostDeviceReset() {

}

void ZeroResource::ReloadResource() {

}
