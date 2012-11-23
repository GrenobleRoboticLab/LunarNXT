#include "LunarNXT/Mode.h"

using namespace Lunar_lib;

// Constructeur
Mode::Mode() : Receptor() { 
	m_bLaunched		= false;
	m_bInitialized	= false;
}

bool Mode::SetMoveManager(MoveMgr** ppMoveManager) {
	bool bRet = false;

	if (ppMoveManager && *ppMoveManager) {
		m_ppMoveManager = ppMoveManager;
		SetMotorsName(((MoveMgr*)*m_ppMoveManager)->GetNameLeftMotor(), ((MoveMgr*)*m_ppMoveManager)->GetNameRightMotor());
		bRet = true;
	}

	return bRet;
}

void Mode::Launch() {
	m_bLaunched		= true;
	m_bInitialized	= false;
}

void Mode::Unlaunch() {
	m_bLaunched		= false;
	m_bInitialized	= false;
	if (CheckMoveManager())
		((MoveMgr*)*m_ppMoveManager)->Stop();
}

bool Mode::IsLaunched()    { return m_bLaunched;	}
bool Mode::IsInitialized() { return m_bInitialized;	}

void Mode::SetInitialized(bool init) { m_bInitialized = init; }

bool Mode::CheckMoveManager() {
	bool bRet = true;

	if (!m_ppMoveManager || !*m_ppMoveManager) {
		ROS_ERROR("MoveManager is NULL.");
		bRet = false;
	}

	return bRet;
}
