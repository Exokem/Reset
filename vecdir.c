
#include "vecdir.h"

Vecdir vecdirSum ( Vecdir vd1, Vecdir vd2 )
{
	Vecdir sum = { vd1.vx + vd2.vx, vd1.vy + vd2.vy, vd1.vz + vd2.vz };
	return sum;
}