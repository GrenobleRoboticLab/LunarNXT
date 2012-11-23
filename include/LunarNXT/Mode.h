//=============================================================================
//
// This file is part of LunarNXT.
//
// LunarNXT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// LunarNXT is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with LunarNXT. If not, see <http://www.gnu.org/licenses/>.
//
//=============================================================================

#ifndef MODE_H
#define MODE_H

#include "LunarNXT/Receptor.h"
#include "LunarNXT/MoveMgr.h"

namespace Lunar_lib {

class Mode : public Receptor {
public:
	Mode();
	virtual ~Mode() { ; }
	
	virtual bool	SetMoveManager(MoveMgr** ppMoveManager);

	void			Launch();
	void			Unlaunch();
	bool			IsLaunched();
    bool			IsInitialized();

protected:
	bool			m_bLaunched;
	bool			m_bInitialized;
	MoveMgr**		m_ppMoveManager;

	void			SetInitialized(bool init);
	virtual void	Treat() =0;

	bool			CheckMoveManager();
};

};

#endif
