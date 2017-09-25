#include "shared.h"
#include "crendertarget.h"

#define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

CRenderTarget::CRenderTarget(gfxScreen_t screen, gfx3dSide_t side, int width, int height)
{
	this->target = C3D_RenderTargetCreate(height, width, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
	C3D_RenderTargetSetOutput(this->target, screen, side, DISPLAY_TRANSFER_FLAGS);

	Mtx_OrthoTilt(&projection, 0.0, width, height, 0.0, 0.0, 1.0, true);
	C3D_RenderTargetSetClear(this->target, C3D_CLEAR_ALL, 0x000000FF, 0);
}

C3D_Mtx * CRenderTarget::GetProjection()
{
	return &this->projection;
}

C3D_RenderTarget * CRenderTarget::GetTarget()
{
	return this->target;
}

void CRenderTarget::Clear(u32 color)
{
	C3D_FrameBufClear(&this->target->frameBuf, C3D_CLEAR_ALL, color, 0);
}