
#ifndef _VECDIR_H
#define _VECDIR_H

typedef struct vecdir_s
{
	int vx;
	int vy;
	int vz;
} Vecdir;

static const Vecdir AX = {  1,  0,  0  };
static const Vecdir DX = { -1,  0,  0  };

static const Vecdir AY = {  0,  1,  0  };
static const Vecdir DY = {  0, -1,  0  };

static const Vecdir AZ = {  0,  0, -1  };
static const Vecdir DZ = {  0,  0,  1  };

static const Vecdir OO = {  0,  0,  0  };

Vecdir vecdirSum ( Vecdir, Vecdir );

#endif