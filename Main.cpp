#include "Main.h"

CS_FPSCalculator  fpsCalculator;
FCamera           camera;
FObject           object;
FRasterizer       rasterizer;
f32               walkSpeed = 0.01f;
f32               mouseSensitivity = 40.0f;
csbool            rotate = csFalse;

FVector4D v0, v1, v2;


void Setup (CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	// Initialize FrameBuffer-required Components
	camera = FCamera(
		0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f,
		-0.1f, -1000.0f, 60.0f, fb.width, fb.height
	);
	rasterizer = FRasterizer(fb);

	// Create Cube
	object.Add(FVector4D(-1.0, -1.0,  1.0, 1.0));
	object.Add(FVector4D( 1.0, -1.0,  1.0, 1.0));
	object.Add(FVector4D( 1.0,  1.0,  1.0, 1.0));
	object.Add(FVector4D(-1.0,  1.0,  1.0, 1.0));
	object.Add(FVector4D(-1.0, -1.0, -1.0, 1.0));
	object.Add(FVector4D( 1.0, -1.0, -1.0, 1.0));
	object.Add(FVector4D( 1.0,  1.0, -1.0, 1.0));
	object.Add(FVector4D(-1.0,  1.0, -1.0, 1.0));

	// Open Mouse Locking
	mouse.OpenInfinityMode();

	v0 = FVector4D(100.0f, 0.0f, 0.0f, 0.0f);
	v1 = FVector4D(0.0f, 400.0f, 0.0f, 0.0f);
	v2 = FVector4D(300.0f, 500.0f, 0.0f, 0.0f);
}

void Update(CS_FrameBuffer& fb, CS_Keyboard& kb, CS_Mouse& mouse, i32 deltaTime) {
	// // Rotation
	// if(rotate){
	// 	object.Rotate(0.05f * deltaTime, -0.05f * deltaTime, 0.0f);
	// }

	// if(kb.IsKeyPressed(CSK_W)){
	// 	camera.Walk(FVector4D( 0.0f, 0.0f, -1.0f, 1.0f) * walkSpeed * deltaTime);
	// }
	// if(kb.IsKeyPressed(CSK_S)){
	// 	camera.Walk(FVector4D( 0.0f, 0.0f,  1.0f, 1.0f) * walkSpeed * deltaTime);
	// }
	// if(kb.IsKeyPressed(CSK_A)){
	// 	camera.Walk(FVector4D(-1.0f, 0.0f,  0.0f, 1.0f) * walkSpeed * deltaTime);
	// }
	// if(kb.IsKeyPressed(CSK_D)){
	// 	camera.Walk(FVector4D( 1.0f, 0.0f,  0.0f, 1.0f) * walkSpeed * deltaTime);
	// }
	// if(kb.IsKeyPressed(CSK_Space)){
	// 	camera.Elevator( walkSpeed * deltaTime);
	// }
	// if(kb.IsKeyPressed(CSK_Shift)){
	// 	camera.Elevator(-walkSpeed * deltaTime);
	// }
	// if(kb.IsKeyFirstTimePressed(CSK_R)){
	// 	rotate = !rotate;
	// }
	// camera.Rotate(
	// 	(f32)mouse.deltaY / (f32)mouse.windowHeight * mouseSensitivity,
	// 	(f32)mouse.deltaX / (f32)mouse.windowWidth  * mouseSensitivity,
	// 	0.0f
	// );
	

	// // Projection and Rasterization
	// camera.ProjectObject(object);
	// rasterizer.DrawPoint(object);

	// // Count FPS and Print Things
	fpsCalculator.Count(deltaTime);
	// fb.Print(mouse.ToString());
	// fb.PrintLn(kb.ToString());

	fb.PrintLn(fpsCalculator.ToString());

	// fb.PrintLn("Press WASD to Move, Rotate the Mouse to Look.");
	// fb.PrintLn("Press R to Rotate the Cube, Space to Rise, Shift to Fall\n");
	
	// fb.PrintLn(camera.ToString());
	// fb.PrintLn(object.ToString());

	// // Interpolation test
	// FVector4D a(0.0f, 0.0f, 0.0f, 1.0f), b(1.0f, 1.0f, 1.0f, 1.0f);
	// fb.PrintLn(a.InterpolateTo(b, 0.3f).ToString());

	// Draw Triangle Test
	// // Flat Triangles Seperated
	// rasterizer.DrawFlatBottomTriangle(0.0f, 400.0f, 100.0f, 0.0f, 300.0f, 255, 255, 255);
	// rasterizer.DrawFlatTopTriangle(0.0f, 400.0f, 0.0f, 300.0f, 100.0f, 255, 255, 255);
	// // Flat Bottom Triangle
	// rasterizer.DrawTriangle(
	// 	FVector4D(100.0f, 0.0f, 0.0f, 0.0f),
	// 	FVector4D(0.0f, 400.0f, 0.0f, 0.0f),
	// 	FVector4D(300.0f, 400.0f, 0.0f, 0.0f),
	// 	255, 255, 255
	// );
	// // Flat Top Triangle
	// rasterizer.DrawTriangle(
	// 	FVector4D(0.0f, 0.0f, 0.0f, 0.0f),
	// 	FVector4D(300.0f, 0.0f, 0.0f, 0.0f),
	// 	FVector4D(100.0f, 400.0f, 0.0f, 0.0f),
	// 	255, 255, 255
	// );
	// // Longside Left
	// rasterizer.DrawTriangle(
	// 	FVector4D(100.0f, 0.0f, 0.0f, 0.0f),
	// 	FVector4D(0.0f, 500.0f, 0.0f, 0.0f),
	// 	FVector4D(300.0f, 400.0f, 0.0f, 0.0f),
	// 	255, 255, 255
	// );
	// // Longside Right
	// rasterizer.DrawTriangle(
	// 	FVector4D(100.0f, 0.0f, 0.0f, 0.0f),
	// 	FVector4D(0.0f, 400.0f, 0.0f, 0.0f),
	// 	FVector4D(300.0f, 500.0f, 0.0f, 0.0f),
	// 	255, 255, 255
	// );

	f32 triangleMovingSpeed = 0.5f;

	// WASD
	if(kb.IsKeyPressed(CSK_W)){
		v0.y -= triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_S)){
		v0.y += triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_A)){
		v0.x -= triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_D)){
		v0.x += triangleMovingSpeed * deltaTime;
	}

	// TFGH
	if(kb.IsKeyPressed(CSK_T)){
		v1.y -= triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_G)){
		v1.y += triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_F)){
		v1.x -= triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_H)){
		v1.x += triangleMovingSpeed * deltaTime;
	}

	// IJKL
	if(kb.IsKeyPressed(CSK_I)){
		v2.y -= triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_K)){
		v2.y += triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_J)){
		v2.x -= triangleMovingSpeed * deltaTime;
	}
	if(kb.IsKeyPressed(CSK_L)){
		v2.x += triangleMovingSpeed * deltaTime;
	}

	rasterizer.DrawTriangle(v0, v1, v2, 255, 255, 255);
}
