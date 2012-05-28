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

#ifndef LUNARTOOLS_H
#define LUNARTOOLS_H

#include "nxt_msgs/Color.h"

/// Tools contient les methodes et classes utilisees dans de nombreuses classes.
namespace Tools {
	/**
	 * Compare deux couleurs
	 * @param c1 couleur a comparer
	 * @param c2 couleur a comparer
	 */
	bool compare_color(const nxt_msgs::Color* c1, const nxt_msgs::Color* c2);

	/**
	 * MVector represente un vecteur et par extension un point ou une taille
	 */
	class MVector {
	private:
		float x, y;
	
	public:
		/**
		 * Constructeur.
		 */
		MVector();
		/**
		 * Constructeur.
		 */
		MVector(float x, float y);
	
		float getX();
		float getY();
	
		void setX(float x);
		void setY(float y);
		void setVector(float x, float y);
	};
};

#endif
