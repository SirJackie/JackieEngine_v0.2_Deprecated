#ifndef __JKEG_CameraSupport
#define __JKEG_CameraSupport

#include <stdio.h>
#include <math.h>
#include "LinearAlgebra.h"


/*
** Camera4D Definition
*/

struct Camera4D {


	/*
	** Position Setting
	*/

	Vector4D position;
	Vector4D rotation;


	/*
	** Frustum Setting
	*/

	double n;
	double f;
	double t;
	double b;
	double l;
	double r;
	double fovY;
	int ScreenWidth;
	int ScreenHeight;


	/*
	** Matrices
	*/

	Matrix4D Mtranslation;
	Matrix4D Mrotation;
	Matrix4D Mortho;
	Matrix4D Mpersp;
	Matrix4D Mviewport;
	Matrix4D MprojAndviewport;
	Matrix4D Mtransform;
};

Camera4D CreateCamera4D(
	double x, double y, double z, double rotx, double roty, double rotz,
	double n, double f, double fovY, int ScreenWidth, int ScreenHeight
)
{
	Camera4D cam;

	cam.position = CreateVector4D(x, y, z, 1);
	cam.rotation = CreateVector4D(rotx, roty, rotz, 1);

	cam.n = n;
	cam.f = f;
	cam.fovY = fovY;
	cam.ScreenWidth = ScreenWidth;
	cam.ScreenHeight = ScreenHeight;

	cam.t = fabs(cam.n) * tand(cam.fovY / 2.0);
	cam.b = -1.0 * cam.t;

	cam.r = cam.ScreenWidth * cam.t / cam.ScreenHeight;
	cam.l = -1.0 * cam.r;

	return cam;
}


/*
** View Transform Supporting Functions
*/

void CalcCamera4DMtranslation(Camera4D* cam) {
	cam->Mtranslation = CreateMatrix4D(
		1.0, 0.0, 0.0, -1.0 * (cam->position.x),
		0.0, 1.0, 0.0, -1.0 * (cam->position.y),
		0.0, 0.0, 1.0, -1.0 * (cam->position.z),
		0.0, 0.0, 0.0,  1.0
	);
}

void CalcCamera4DMrotation(Camera4D* cam) {
	Matrix4D MrotationX = CreateMatrix4D(
		1.0, 0.0, 0.0, 0.0,
		0.0, cosd(cam->rotation.x), -1.0 * sind(cam->rotation.x), 0.0,
		0.0, sind(cam->rotation.x), cosd(cam->rotation.x), 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	Matrix4D MrotationY = CreateMatrix4D(
		cosd(cam->rotation.y), 0.0, sind(cam->rotation.y), 0.0,
		0.0, 1.0, 0.0, 0.0,
		-1.0 * sind(cam->rotation.y), 0.0, cosd(cam->rotation.y), 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	Matrix4D MrotationZ = CreateMatrix4D(
		cosd(cam->rotation.z), -1.0 * sind(cam->rotation.z), 0.0, 0.0,
		sind(cam->rotation.z), cosd(cam->rotation.z), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	cam->Mrotation = Matrix4DTimesMatrix4D(
		&MrotationZ,
		&MrotationY
	);

	cam->Mrotation = Matrix4DTimesMatrix4D(
		&(cam->Mrotation),
		&MrotationX
	);
}


/*
** Projection Transform Supporting Functions
*/

void CalcCamera4DMortho(Camera4D* cam) {
	Matrix4D Morthoa = CreateMatrix4D(
		1.0, 0.0, 0.0, -1 * (cam->r + cam->l) / 2.0,
		0.0, 1.0, 0.0, -1 * (cam->t + cam->b) / 2.0,
		0.0, 0.0, 1.0, -1 * (cam->n + cam->f) / 2.0,
		0.0, 0.0, 0.0, 1.0
	);

	Matrix4D Morthob = CreateMatrix4D(
		2.0 / (cam->r - cam->l), 0.0, 0.0, 0.0,
		0.0, 2.0 / (cam->t - cam->b), 0.0, 0.0,
		0.0, 0.0, 2.0 / (cam->n - cam->f), 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	cam->Mortho = Matrix4DTimesMatrix4D(
		&Morthoa,
		&Morthob
	);
}

void CalcCamera4DMpersp(Camera4D* cam) {
	CalcCamera4DMortho(cam);
	Matrix4D Mpersp2ortho = CreateMatrix4D(
		cam->n, 0.0, 0.0, 0.0,
		0.0, cam->n, 0.0, 0.0,
		0.0, 0.0, cam->f + cam->n, -1 * cam->f * cam->n,
		0.0, 0.0, 1.0, 0.0
	);

	cam->Mpersp = Matrix4DTimesMatrix4D(
		&Mpersp2ortho,
		&(cam->Mortho)
	);
}

void CalcCamera4DMviewport(Camera4D* cam) {
	Matrix4D MviewportPre = CreateMatrix4D(
		cam->ScreenWidth / 2.0, 0.0, 0.0, cam->ScreenWidth / 2.0,
		0.0, cam->ScreenHeight / 2.0, 0.0, cam->ScreenHeight / 2.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	Matrix4D MYReverse = CreateMatrix4D(
		1.0, 0.0, 0.0, 0.0,
		0.0, -1.0, 0.0, cam->ScreenHeight,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	cam->Mviewport = Matrix4DTimesMatrix4D(&MviewportPre, &MYReverse);
}


/*
** Functions that Merge Matrices Together In Order To Speed Up
*/

void CalcCamera4DMprojAndviewport(Camera4D* cam) {
	CalcCamera4DMpersp(cam);
	CalcCamera4DMviewport(cam);
	cam->MprojAndviewport = Matrix4DTimesMatrix4D(
		&(cam->Mpersp),
		&(cam->Mviewport)
	);
}

void CalcCamera4DMatrices(Camera4D* cam) {
	CalcCamera4DMtranslation(cam);
	CalcCamera4DMrotation(cam);
	CalcCamera4DMprojAndviewport(cam);
	cam->Mtransform = Matrix4DTimesMatrix4D(
		&(cam->Mtranslation),
		&(cam->Mrotation)
	);
	cam->Mtransform = Matrix4DTimesMatrix4D(
		&(cam->Mtransform),
		&(cam->MprojAndviewport)
	);
}

void RefreshCamera4DMatrices(Camera4D* cam) {
	CalcCamera4DMtranslation(cam);
	CalcCamera4DMrotation(cam);
	// cam->MprojAndviewport is not changed
	cam->Mtransform = Matrix4DTimesMatrix4D(
		&(cam->Mtranslation),
		&(cam->Mrotation)
	);
	cam->Mtransform = Matrix4DTimesMatrix4D(
		&(cam->Mtransform),
		&(cam->MprojAndviewport)
	);
}

#endif
