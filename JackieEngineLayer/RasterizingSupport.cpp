#include "RasterizingSupport.h"

FRasterizer::FRasterizer(){
	ptrfb = csNullPtr;
}

FRasterizer::FRasterizer(CS_FrameBuffer& fb_){
	ptrfb = &fb_;
}

void FRasterizer::DrawProtectedCube(i32 x0, i32 y0, i32 x1, i32 y1, ui8 r_, ui8 g_, ui8 b_){
	i32 width  = ptrfb->width;
	i32 height = ptrfb->height;

	x0 = CS_iclamp(0, x0, width);
	x1 = CS_iclamp(x0, x1, width);

	y0 = CS_iclamp(0, y0, height);
	y1 = CS_iclamp(y0, y1, height);

	for(i32 y = y0; y < y1; y++){
		ui8*  rEnd = (ui8*)(ptrfb->redBuffer   + y * width + x1);
		ui8*  gEnd = (ui8*)(ptrfb->greenBuffer + y * width + x1);
		ui8*  bEnd = (ui8*)(ptrfb->blueBuffer  + y * width + x1);
		for(
			ui8 *r = (ui8*)(ptrfb->redBuffer   + y * width + x0),
			    *g = (ui8*)(ptrfb->greenBuffer + y * width + x0),
			    *b = (ui8*)(ptrfb->blueBuffer  + y * width + x0);
			r<rEnd;
			r++ && g++ && b++ 
		){
			*r = r_;
			*g = g_;
			*b = b_;
		}
	}	
}

void FRasterizer::DrawRadiusCube(i32 x, i32 y, i32 radius){
	DrawProtectedCube(
		x - radius, y - radius,
		x + radius, y + radius,
		255, 255, 255
	);
}

void FRasterizer::Draw3DPoint(FVector3D& point){
	DrawRadiusCube(point.x, point.y, 5);
}

void FRasterizer::Draw4DPoint(FVector4D& point){
	DrawRadiusCube(
		point.x, point.y,
		(1.0f + point.z) * 200.0f
	);
}

void FRasterizer::DrawPoint(FObject& obj_)
{
	for (ui32 i = 0; i < obj_.tmpVl.size(); i++) {
		Draw4DPoint(obj_.tmpVl[i]);
	}
}
