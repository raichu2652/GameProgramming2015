/*==============================================================
character movement testing using Fly2

- Load a scene
- Generate a terrain object
- Load a character
- Control a character to move
- Change poses

(C)2012-2015 Chuan-Chang Wang, All Rights Reserved
Created : 0802, 2012

Last Updated : 1004, 2015, Kevin C. Wang
===============================================================*/
#include "FlyWin32.h"
#include <math.h>

VIEWPORTid vID;                 // the major viewport
SCENEid sID;                    // the 3D scene
OBJECTid cID, tID, dummyObjID;              // the main camera and the terrain for terrain following
CHARACTERid actorID;            // the major character
ACTIONid idleID, runID, curPoseID; // two actions
ROOMid terrainRoomID = FAILED_ID;
TEXTid textID = FAILED_ID;

// some globals
int frame = 0;
int oldX, oldY, oldXM, oldYM, oldXMM, oldYMM;

// hotkey callbacks
void QuitGame(BYTE, BOOL4);
void Movement(BYTE, BOOL4);

// timer callbacks
void GameAI(int);
void RenderIt(int);

// mouse callbacks
void InitPivot(int, int);
void PivotCam(int, int);
void InitMove(int, int);
void MoveCam(int, int);
void InitZoom(int, int);
void ZoomCam(int, int);

void RotateCam(int x, int y);
void InitZoom2(int, int);
void ZoomCam2(int, int);

//camera control parameters
float distance = 700;
float xSpeed = 10;
float ySpeed = 10;

const float CameraBaseHeight = 300;

float rot_x = 0;
float rot_y = -30;

float playerRot_x = 0;

bool IsCameraFollow = false;

bool left_firstPressed = false;
bool right_firstPressed = false;

bool up_firstPressed = false;
bool down_firstPressed = false;

float radius = 0;
float dist = 0;

float cameraHeight = CameraBaseHeight;

//camera
void CameraControl(CHARACTERid targetid);
void CameraFocus(CHARACTERid targetid, float scaler);
void InitCamera();

// math helper functions
void EulerToQuarternion(float x, float y, float z, float* result);
void QuaternionMultiVector(float* quat, float* vec, float* result);
float degToRad(float d);
void VectorCross(float* vec1, float* vec2, float* result);
float VectorDot(float* vec1, float* vec2, float* result);
void VectorNormalize(float* vec1, float* result);
float VectorMagnitude(float* vec1);
void VectorScalerMultiply(float s, float* vec1, float* result);

/*------------------
the main program
C.Wang 1010, 2014
-------------------*/
//test
void FyMain(int argc, char **argv)
{
	// create a new world
	BOOL4 beOK = FyStartFlyWin32("NTU@2014 Homework #01 - Use Fly2", 0, 0, 1024, 768, FALSE);

	// setup the data searching paths
	FySetShaderPath("Data\\NTU6\\Shaders");
	FySetModelPath("Data\\NTU6\\Scenes");
	FySetTexturePath("Data\\NTU6\\Scenes\\Textures");
	FySetScenePath("Data\\NTU6\\Scenes");

	// create a viewport
	vID = FyCreateViewport(0, 0, 1024, 768);
	FnViewport vp;
	vp.ID(vID);

	// create a 3D scene
	sID = FyCreateScene(10);
	FnScene scene;
	scene.ID(sID);

	// load the scene
	scene.Load("gameScene02");
	scene.SetAmbientLights(1.0f, 1.0f, 1.0f, 0.6f, 0.6f, 0.6f);

	// load the terrain
	tID = scene.CreateObject(OBJECT);
	FnObject terrain;
	terrain.ID(tID);
	BOOL beOK1 = terrain.Load("terrain");
	terrain.Show(FALSE);

	// set terrain environment
	terrainRoomID = scene.CreateRoom(SIMPLE_ROOM, 10);
	FnRoom room;
	room.ID(terrainRoomID);
	room.AddObject(tID);

	// load the character
	FySetModelPath("Data\\NTU6\\Characters");
	FySetTexturePath("Data\\NTU6\\Characters");
	FySetCharacterPath("Data\\NTU6\\Characters");
	actorID = scene.LoadCharacter("Lyubu2");

	// put the character on terrain
	float pos[3], fDir[3], uDir[3];
	FnCharacter actor;
	actor.ID(actorID);
	pos[0] = 3569.0f; pos[1] = -3208.0f; pos[2] = 1000.0f;
	fDir[0] = 1.0f; fDir[1] = -1.0f; fDir[2] = 0.0f;
	uDir[0] = 0.0f; uDir[1] = 0.0f; uDir[2] = 1.0f;
	actor.SetDirection(fDir, uDir);

	actor.SetTerrainRoom(terrainRoomID, 10.0f);
	beOK = actor.PutOnTerrain(pos);

	// Get two character actions pre-defined at Lyubu2
	idleID = actor.GetBodyAction(NULL, "Idle");
	runID = actor.GetBodyAction(NULL, "Run");

	// set the character to idle action
	curPoseID = idleID;
	actor.SetCurrentAction(NULL, 0, curPoseID);
	actor.Play(START, 0.0f, FALSE, TRUE);
	actor.TurnRight(90.0f);

	// translate the camera
	cID = scene.CreateObject(CAMERA);
	FnCamera camera;
	camera.ID(cID);
	camera.SetNearPlane(5.0f);
	camera.SetFarPlane(100000.0f);

	dummyObjID = scene.CreateObject(OBJECT);


	// set camera initial position and orientation
	pos[0] = 4069.0f; pos[1] = -3208.0f; pos[2] = 93.046f;
	fDir[0] = -500.0f; fDir[1] = -0.0f; fDir[2] = -0.0f;
	uDir[0] = -0.116f; uDir[1] = -0.031f; uDir[2] = 0.993f;
	camera.SetPosition(pos);
	camera.SetDirection(fDir, uDir);

	float mainLightPos[3] = { -4579.0, -714.0, 15530.0 };
	float mainLightFDir[3] = { 0.276, 0.0, -0.961 };
	float mainLightUDir[3] = { 0.961, 0.026, 0.276 };

	FnLight lgt;
	lgt.ID(scene.CreateObject(LIGHT));
	lgt.Translate(mainLightPos[0], mainLightPos[1], mainLightPos[2], REPLACE);
	lgt.SetDirection(mainLightFDir, mainLightUDir);
	lgt.SetLightType(PARALLEL_LIGHT);
	lgt.SetColor(1.0f, 1.0f, 1.0f);
	lgt.SetName("MainLight");
	lgt.SetIntensity(0.4f);

	// create a text object for displaying messages on screen
	textID = FyCreateText("Trebuchet MS", 18, FALSE, FALSE);

	// set Hotkeys
	FyDefineHotKey(FY_ESCAPE, QuitGame, FALSE);  // escape for quiting the game
	FyDefineHotKey(FY_UP, Movement, FALSE);      // Up for moving forward
	FyDefineHotKey(FY_DOWN, Movement, FALSE);      // Down for moving backward
	FyDefineHotKey(FY_RIGHT, Movement, FALSE);   // Right for turning right
	FyDefineHotKey(FY_LEFT, Movement, FALSE);    // Left for turning left

	// define some mouse functions
	if (!IsCameraFollow)
	{
		FyBindMouseFunction(LEFT_MOUSE, InitPivot, PivotCam, NULL, NULL);
		FyBindMouseFunction(MIDDLE_MOUSE, InitZoom, ZoomCam, NULL, NULL);
		FyBindMouseFunction(RIGHT_MOUSE, InitMove, MoveCam, NULL, NULL);
	}
	else
	{
		FyBindMouseFunction(LEFT_MOUSE, InitZoom2, ZoomCam2, NULL, NULL);
		FyBindMouseFunction(RIGHT_MOUSE, NULL, RotateCam, NULL, NULL);
	}

	CameraFocus(actorID, 1);

	// bind timers, frame rate = 30 fps
	FyBindTimer(0, 30.0f, GameAI, TRUE);
	FyBindTimer(1, 30.0f, RenderIt, TRUE);

	// invoke the system
	FyInvokeFly(TRUE);

	
}

//not used for now
void InitCamera()
{
	FnCamera camera;
	camera.ID(cID);

	FnCharacter actor;
	actor.ID(actorID);

	float playerFDir[3], targetPos[3], playerUDir[3];
	actor.GetPosition(targetPos);
	actor.GetDirection(playerFDir, playerUDir);

	float camLocalPos[3], cameraPos[3], cameraForward[3];
	camLocalPos[0] = -1*distance*playerFDir[0];
	camLocalPos[1] = -1*distance*playerFDir[1];
	camLocalPos[2] = cameraHeight;

	FnObject controlObj;
	controlObj.ID(dummyObjID);
	controlObj.SetPosition(targetPos);
	controlObj.SetDirection(playerFDir, playerUDir);

	camera.SetParent(dummyObjID);
	camera.SetPosition(camLocalPos, false);

	camera.GetPosition(cameraPos);
	cameraForward[0] = targetPos[0] - cameraPos[0];
	cameraForward[1] = targetPos[1] - cameraPos[1];
	cameraForward[2] = targetPos[2] - cameraPos[2];

	float playerRight[3];
	VectorCross(cameraForward, playerUDir, playerRight);
	float camUpDir[3];
	VectorCross(playerRight, cameraForward, camUpDir);

	camera.SetDirection(cameraForward, camUpDir);
}

//camera orbit control
void CameraControl(CHARACTERid targetid)
{
	FnCamera camera;
	camera.ID(cID);

	FnCharacter actor;
	actor.ID(targetid);

	float targetPos[3];
	actor.GetPosition(targetPos);

	float negativeDistance[3];
	negativeDistance[0] = -distance;
	negativeDistance[1] = 0;
	negativeDistance[2] = 0;

	float rotation[3];
	EulerToQuarternion(0, degToRad(rot_y), degToRad(rot_x), rotation);

	float forwardDir[3];
	QuaternionMultiVector(rotation, negativeDistance, forwardDir);

	float camPos[3], GlobalRight[3];
	GlobalRight[0] = 0;
	GlobalRight[1] = 1;
	GlobalRight[2] = 0;


	camPos[0] = targetPos[0] - forwardDir[0];
	camPos[1] = targetPos[1] - forwardDir[1];
	camPos[2] = targetPos[2] - forwardDir[2];

	float upDir[3];
	VectorCross(GlobalRight, forwardDir, upDir);

	//camera.Quaternion(rotation[0], rotation[1], rotation[2], rotation[3], GLOBAL);
	camera.SetPosition(camPos);
	camera.SetDirection(forwardDir, upDir);
}

void CameraFocus(CHARACTERid targetid, float scaler)
{
	FnCamera camera;
	camera.ID(cID);

	FnCharacter actor;
	actor.ID(targetid);

	float targetPos[3];
	actor.GetPosition(targetPos);

	float fDir[3], upDir[3],camPos[3],cameraPos[3],cameraForward[3];
	actor.GetDirection(fDir, upDir);
	camera.GetPosition(cameraPos);

	cameraForward[0] = distance*scaler*fDir[0];
	cameraForward[1] = distance*scaler*fDir[1];
	cameraForward[2] = -cameraHeight;

	float rightDir[3];
	VectorCross(cameraForward, upDir, rightDir);

	float camUpDir[3];
	VectorCross(rightDir, cameraForward, camUpDir);

	camPos[0] = targetPos[0] - cameraForward[0];
	camPos[1] = targetPos[1] - cameraForward[1];
	camPos[2] = targetPos[2] - cameraForward[2];

	camera.SetDirection(cameraForward, camUpDir);
	camera.SetPosition(camPos);
}

float lastPlayerPos[3];

/*-------------------------------------------------------------
30fps timer callback in fixed frame rate for major game loop
--------------------------------------------------------------*/
void GameAI(int skip)
{
	FnCharacter actor;

	// play character pose
	actor.ID(actorID);
	actor.Play(LOOP, (float)skip, FALSE, TRUE);

	FnObject controlObj;
	controlObj.ID(dummyObjID);

	FnCamera camera;
	camera.ID(cID);

	float fDir[3], uDir[3];
	float playerPos[3],dummyPos[3];
	actor.GetPosition(playerPos);
	actor.GetDirection(fDir, uDir);

	float cameraPos[3];
	camera.GetPosition(cameraPos);

	float forwardDir[3], backwardDir[3], camForwardDir[3];

	camForwardDir[0] = playerPos[0] - cameraPos[0];
	camForwardDir[1] = playerPos[1] - cameraPos[1];
	camForwardDir[2] = playerPos[2] - cameraPos[2];

	forwardDir[0] = camForwardDir[0];
	forwardDir[1] = camForwardDir[1];
	forwardDir[2] = 0;

	backwardDir[0] = -forwardDir[0];
	backwardDir[1] = -forwardDir[1];
	backwardDir[2] = 0;

	FnObject terrain;
	terrain.ID(tID);

	float hitPos[3], hitDir[3], GlobalDownDir[3];

	GlobalDownDir[0] = 0;
	GlobalDownDir[1] = 0;
	GlobalDownDir[2] = -1;

	float hit = terrain.HitTest(cameraPos, GlobalDownDir, hitPos);
	if (hit > 0)
	{
		distance += 10;
		cameraHeight -= 10;

		if (distance > 700)
			distance = 700;

		if (cameraHeight < CameraBaseHeight)
		     cameraHeight = CameraBaseHeight;
	}
	else
	{
		distance -= 10;
		if (distance < 10)
			distance = 10;
		cameraHeight += 10;

		if (cameraHeight > 1000)
			cameraHeight = 1000;
	}

	if (FyCheckHotKeyStatus(FY_UP))
	{
		if (!up_firstPressed)
		{
			float playerForward[3];
			playerForward[0] = forwardDir[0];
			playerForward[1] = forwardDir[1];
			playerForward[2] = forwardDir[2];

			actor.SetDirection(playerForward, uDir);
			up_firstPressed = true;
		}

		actor.MoveForward(20,true,true,0,true);

		//controlObj.SetPosition(playerPos);
		CameraFocus(actorID,1);

	}
	else if (FyCheckHotKeyStatus(FY_DOWN))
	{
		if (!down_firstPressed)
		{
			float playerForward[3];
			playerForward[0] = backwardDir[0];
			playerForward[1] = backwardDir[1];
			playerForward[2] = backwardDir[2];

			actor.SetDirection(playerForward, uDir);
			down_firstPressed = true;
		}

		actor.MoveForward(20, true, true, 0, true);

		//controlObj.SetPosition(playerPos);
		CameraFocus(actorID,-1);
	}
	else if (FyCheckHotKeyStatus(FY_LEFT))
	{
		IsCameraFollow = false;

		if (!left_firstPressed)
		{
			float playerForward[3];
			VectorCross(backwardDir, uDir, playerForward);
			actor.SetDirection(playerForward, uDir);

			radius = sqrt(forwardDir[0] * forwardDir[0] + forwardDir[1] * forwardDir[1]);
			dist = radius*degToRad(2);

			left_firstPressed = true;
		}

		
		actor.MoveForward(dist, true, true, 0, true);
		
		float playerF[3], playerU[3];
		actor.GetDirection(playerF, playerU);

		float radiusDir[3];
		VectorCross(playerU, playerF, radiusDir);

		float camPos[3];
		camPos[0] = playerPos[0] + distance*radiusDir[0];
		camPos[1] = playerPos[1] + distance*radiusDir[1];
		camPos[2] = playerPos[2] + cameraHeight;
		camera.SetPosition(camPos);

		float camUpDir[3];
		VectorCross(camForwardDir, playerF, camUpDir);

		float deltaPos[3];
		deltaPos[0] = playerPos[0] - lastPlayerPos[0];
		deltaPos[1] = playerPos[1] - lastPlayerPos[1];
		deltaPos[2] = playerPos[2] - lastPlayerPos[2];

		float mag = VectorMagnitude(deltaPos);

		//if (mag > 0.1)
		//{
			actor.TurnRight(-2);
			camera.SetDirection(camForwardDir, camUpDir);
		//}

		lastPlayerPos[0] = playerPos[0];
		lastPlayerPos[1] = playerPos[1];
		lastPlayerPos[2] = playerPos[2];

	}
	
	else if (FyCheckHotKeyStatus(FY_RIGHT))
	{
		IsCameraFollow = false;
		if (!right_firstPressed)
		{
			float playerForward[3];
			VectorCross(forwardDir, uDir, playerForward);
			actor.SetDirection(playerForward, uDir);

			radius = sqrt(forwardDir[0] * forwardDir[0] + forwardDir[1] * forwardDir[1]);
			dist = radius*degToRad(2);

			right_firstPressed = true;
		}

		actor.MoveForward(dist, true, true, 0, true);

		float playerF[3], playerU[3];
		actor.GetDirection(playerF, playerU);

		float radiusDir[3];
		VectorCross(playerF, playerU, radiusDir);

		float camPos[3];
		camPos[0] = playerPos[0] + distance*radiusDir[0];
		camPos[1] = playerPos[1] + distance*radiusDir[1];
		camPos[2] = playerPos[2] + cameraHeight;
		camera.SetPosition(camPos);


		float camUpDir[3];
		VectorCross(playerF, camForwardDir, camUpDir);

		float deltaPos[3];
		deltaPos[0] = playerPos[0] - lastPlayerPos[0];
		deltaPos[1] = playerPos[1] - lastPlayerPos[1];
		deltaPos[2] = playerPos[2] - lastPlayerPos[2];

		float mag = VectorMagnitude(deltaPos);

		//if (mag > 0.1)
		//{
			actor.TurnRight(2);
			camera.SetDirection(camForwardDir, camUpDir);
		//}

		lastPlayerPos[0] = playerPos[0];
		lastPlayerPos[1] = playerPos[1];
		lastPlayerPos[2] = playerPos[2];

	}
	//else {}
	// ....
	if (IsCameraFollow)
	{
		CameraControl(actorID);
	}
}


/*----------------------
perform the rendering
C.Wang 0720, 2006
-----------------------*/
void RenderIt(int skip)
{
	FnViewport vp;

	// render the whole scene
	vp.ID(vID);
	vp.Render3D(cID, TRUE, TRUE);

	// get camera's data
	FnCamera camera;
	camera.ID(cID);

	float pos[3], fDir[3], uDir[3];
	camera.GetPosition(pos);
	camera.GetDirection(fDir, uDir);

	// show frame rate
	static char string[128];
	if (frame == 0) {
		FyTimerReset(0);
	}

	if (frame / 10 * 10 == frame) {
		float curTime;

		curTime = FyTimerCheckTime(0);
		sprintf(string, "Fps: %6.2f", frame / curTime);
	}

	frame += skip;
	if (frame >= 1000) {
		frame = 0;
	}

	FnText text;
	text.ID(textID);

	text.Begin(vID);
	text.Write(string, 20, 20, 255, 0, 0);

	char posS[256], fDirS[256], uDirS[256];
	sprintf(posS, "pos: %8.3f %8.3f %8.3f", pos[0], pos[1], pos[2]);
	sprintf(fDirS, "facing: %8.3f %8.3f %8.3f", fDir[0], fDir[1], fDir[2]);
	sprintf(uDirS, "up: %8.3f %8.3f %8.3f", uDir[0], uDir[1], uDir[2]);

	text.Write(posS, 20, 35, 255, 255, 0);
	text.Write(fDirS, 20, 50, 255, 255, 0);
	text.Write(uDirS, 20, 65, 255, 255, 0);

	text.End();

	// swap buffer
	FySwapBuffers();
}

float degToRad(float d)
{
	return d*3.14159f / 180;
}

void EulerToQuarternion(float x, float y, float z, float* quarternion) {
	// Assuming the angles are in radians.
	double c1 = cos(y / 2);
	double s1 = sin(y / 2);
	double c2 = cos(z / 2);
	double s2 = sin(z / 2);
	double c3 = cos(x / 2);
	double s3 = sin(x / 2);
	double c1c2 = c1*c2;
	double s1s2 = s1*s2;
	float qw = c1c2*c3 - s1s2*s3;
	float qx = c1c2*s3 + s1s2*c3;
	float qy = s1*c2*c3 + c1*s2*s3;
	float qz = c1*s2*c3 - s1*c2*s3;

	quarternion[0] = qw;
	quarternion[1] = qx;
	quarternion[2] = qy;
	quarternion[3] = qz;
}

void QuaternionMultiVector(float* quat, float* vec, float* result){
	float num = quat[1] * 2;
	float num2 = quat[2] * 2;
	float num3 = quat[3] * 2;
	float num4 = quat[1] * num;
	float num5 = quat[2] * num2;
	float num6 = quat[3] * num3;
	float num7 = quat[1] * num2;
	float num8 = quat[1] * num3;
	float num9 = quat[2] * num3;
	float num10 = quat[0] * num;
	float num11 = quat[0] * num2;
	float num12 = quat[0] * num3;
	
	result[0] = (1 - (num5 + num6)) * vec[0] + (num7 - num12) * vec[1] + (num8 + num11) * vec[2];
	result[1] = (num7 + num12) * vec[0] + (1 - (num4 + num6)) * vec[1] + (num9 - num10) * vec[2];
	result[2] = (num8 - num11) * vec[0] + (num9 + num10) * vec[1] + (1 - (num4 + num5)) * vec[2];
}

float VectorDot(float* vec1, float* vec2)
{
	float result;

	result = vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];

	return result;
}

void VectorCross(float* vec1, float* vec2, float* result)
{
	result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

void VectorNormalize(float* vec1, float* result)
{
	float magnitude = VectorMagnitude(vec1);

	result[0] = vec1[0] / magnitude;
	result[1] = vec1[1] / magnitude;
	result[2] = vec1[2] / magnitude;
}

float VectorMagnitude(float* vec1)
{
	float magnitude = sqrt(vec1[0] * vec1[0] + vec1[1] * vec1[1] + vec1[2] * vec1[2]);
	return magnitude;
}

void VectorScalerMultiply(float s, float* vec1, float* result)
{
	result[0] = s*vec1[0];
	result[1] = s*vec1[1];
	result[2] = s*vec1[2];
}

float ClampAngle(float angle, float min, float max)
{
	if (angle < -360.0F)
		angle += 360.0F;
	if (angle > 360.0F)
		angle -= 360.0F;

	float result = angle;

	if (angle > max)
		result = max;
	if (angle < min)
		result = min;
	return result;
}

/*------------------
movement control
-------------------*/
void Movement(BYTE code, BOOL4 value)
{
	// Homework #01 part 2
	FnCharacter actor;
	actor.ID(actorID);
	if (code == FY_UP || code == FY_DOWN || code == FY_LEFT || code == FY_RIGHT)
	{
		if (value)
			actor.SetCurrentAction(NULL, 0, runID, 5.0f);
		else if (!(FyCheckHotKeyStatus(FY_UP) || FyCheckHotKeyStatus(FY_DOWN) || FyCheckHotKeyStatus(FY_LEFT) || FyCheckHotKeyStatus(FY_RIGHT)))
			actor.SetCurrentAction(NULL, 0, idleID, 5.0f);
	}

	if (code == FY_UP)
	{
		if (value == false)
		{
			up_firstPressed = false;
		}
	}

	if (code == FY_DOWN)
	{
		if (value == false)
		{
			down_firstPressed = false;
		}
	}

	if (code == FY_LEFT)
	{
		if (value == false)
		{
			left_firstPressed = false;
		}
	}

	if (code == FY_RIGHT)
	{
		if (value == false)
		{
			right_firstPressed = false;
		}
	}
	// ....
}


/*------------------
quit the demo
C.Wang 0327, 2005
-------------------*/
void QuitGame(BYTE code, BOOL4 value)
{
	if (code == FY_ESCAPE) {
		if (value) {
			FyQuitFlyWin32();
		}
	}
}



/*-----------------------------------
initialize the pivot of the camera
C.Wang 0329, 2005
------------------------------------*/
void InitPivot(int x, int y)
{
	oldX = x;
	oldY = y;
	frame = 0;
}


/*------------------
pivot the camera
C.Wang 0329, 2005
-------------------*/
void PivotCam(int x, int y)
{
	FnObject model;

	if (x != oldX) {
		model.ID(cID);
		model.Rotate(Z_AXIS, (float)(x - oldX), GLOBAL);
		oldX = x;
	}

	if (y != oldY) {
		model.ID(cID);
		model.Rotate(X_AXIS, (float)(y - oldY), GLOBAL);
		oldY = y;
	}
}


/*----------------------------------
initialize the move of the camera
C.Wang 0329, 2005
-----------------------------------*/
void InitMove(int x, int y)
{
	oldXM = x;
	oldYM = y;
	frame = 0;
}


/*------------------
move the camera
C.Wang 0329, 2005
-------------------*/
void MoveCam(int x, int y)
{
	if (x != oldXM) {
		FnObject model;

		model.ID(cID);
		model.Translate((float)(x - oldXM)*2.0f, 0.0f, 0.0f, LOCAL);
		oldXM = x;
	}
	if (y != oldYM) {
		FnObject model;

		model.ID(cID);
		model.Translate(0.0f, (float)(oldYM - y)*2.0f, 0.0f, LOCAL);
		oldYM = y;
	}
}


/*----------------------------------
initialize the zoom of the camera
C.Wang 0329, 2005
-----------------------------------*/
void InitZoom(int x, int y)
{
	oldXMM = x;
	oldYMM = y;
	frame = 0;
}


/*------------------
zoom the camera
C.Wang 0329, 2005
-------------------*/
void ZoomCam(int x, int y)
{
	if (x != oldXMM || y != oldYMM) {
		FnObject model;

		model.ID(cID);
		model.Translate(0.0f, 0.0f, (float)(x - oldXMM)*10.0f, LOCAL);
		oldXMM = x;
		oldYMM = y;
	}
}


void RotateCam(int x, int y)
{
	float axis_x = 0;
	float axis_y = 0;
	if (x != oldXM) {
		if ((float)(x - oldXM) > 0)
			axis_x = 1;
		else
			axis_x = -1;

		oldXM = x;
	}
	if (y != oldYM) {
		if ((float)(y - oldYM) > 0)
			axis_y = 1;
		else
			axis_y = -1;

		oldYM = y;
	}


	rot_x += axis_x*xSpeed*0.02;
	rot_y += axis_y*ySpeed*0.02;

	rot_x = ClampAngle(rot_x, -80, 80);
	rot_y = ClampAngle(rot_y, -80, 20);
}

void InitZoom2(int x, int y)
{
	oldXMM = x;
	oldYMM = y;
	frame = 0;
}

void ZoomCam2(int x, int y)
{
	if (x != oldXMM || y != oldYMM) {

		distance += (float)(x - oldXMM)*10.0f;

		oldXMM = x;
		oldYMM = y;
	}
}