#include "lunarNXT/Tools.h"

bool Tools::compare_color(const nxt_msgs::Color* c1, const nxt_msgs::Color* c2) {
	return (c1->r == c2->r && c1->g == c2->g && c1->b == c2->b);
}
