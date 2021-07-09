#ifndef __JKEG_RasterizingSupport__
#define __JKEG_RasterizingSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"
#include "../CrossBufferLayer/CrossBuffer.h"
#include "MathSupport.h"
#include "ObjectSupport.h"

class FRasterizer {
public:
	CS_FrameBuffer* ptrfb;

	FRasterizer();
	FRasterizer(CS_FrameBuffer& fb_);

	void DrawProtectedCube(i32 x0, i32 y0, i32 x1, i32 y1, ui8 r_, ui8 g_, ui8 b_);
	void DrawPoint(FVector3D& point);
	void DrawPoint(FObject& obj_);
};

#endif
