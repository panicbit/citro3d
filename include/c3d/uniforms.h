#pragma once
#include "types.h"
#define C3D_FVUNIF_COUNT 96
#define C3D_IVUNIF_COUNT 4

extern C3D_FVec C3D_FVUnif[2][C3D_FVUNIF_COUNT];
extern C3D_IVec C3D_IVUnif[2][C3D_IVUNIF_COUNT];
extern u16      C3D_BoolUnifs[2];

extern bool C3D_FVUnifDirty[2][C3D_FVUNIF_COUNT];
extern bool C3D_IVUnifDirty[2][C3D_IVUNIF_COUNT];
extern bool C3D_BoolUnifsDirty[2];

static inline C3D_FVec* C3D_FVUnifWritePtr(GPU_SHADER_TYPE type, int id, int size)
{
	int i;
	for (i = 0; i < size; i ++)
		C3D_FVUnifDirty[type][id+i] = true;
	return &C3D_FVUnif[type][id];
}

static inline C3D_IVec* C3D_IVUnifWritePtr(GPU_SHADER_TYPE type, int id)
{
	C3D_IVUnifDirty[type][id] = true;
	return &C3D_IVUnif[type][id];
}

static inline void C3D_FVUnifSet(GPU_SHADER_TYPE type, int id, float x, float y, float z, float w)
{
	C3D_FVec* ptr = C3D_FVUnifWritePtr(type, id, 1);
	ptr->x = x;
	ptr->y = y;
	ptr->z = z;
	ptr->w = w;
}

static inline void C3D_IVUnifSet(GPU_SHADER_TYPE type, int id, int x, int y, int z, int w)
{
	C3D_IVec* ptr = C3D_IVUnifWritePtr(type, id);
	*ptr = IVec_Pack(x, y, z, w);
}

void C3D_UpdateUniforms(GPU_SHADER_TYPE type);
