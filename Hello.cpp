/*==============================================================
character movement testing using Fly2

Load a scene
Generate a terrain object
Load a character
Control a character to move
Change poses
(C)2012-2015 Chuan-Chang Wang, All Rights Reserved
Created : 0802, 2012

Last Updated : 1004, 2015, Kevin C. Wang
===============================================================*/
#include "FlyWin32.h"

#define speed 10
#define pi 3.14159265
#define rad pi/180.0f
#define LENGTH 1000.0f
#define COS 0.8f
#define SIN sqrt(double(1.0f-COS*COS))
#define DIST LENGTH*COS
#define HEIGHT LENGTH*SIN
#define attacktime 24
#define damagetime1 25
#define damagetime2 15
#define dietime1 170
#define dietime2 31

VIEWPORTid vID; // the major viewport
SCENEid sID; // the 3D scene
OBJECTid cID, tID; // the main camera and the terrain for terrain following
CHARACTERid actorID, npc1ID, npc2ID; // the major character
ACTIONid idleID, runID, attackID, curPoseID, idle1ID, damage1ID, idle2ID, damage2ID, die1ID, die2ID; // two actions
ROOMid terrainRoomID = FAILED_ID;
TEXTid textID = FAILED_ID;

// some globals
int frame = 0, frameattack = -2000, framedamage1 = -2000, framedamage2 = -2000, HP1 = 10, HP2 = 5;
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

float dot2(float*, float*);
float dot3(float*, float*);
float norm2(float*);
float norm3(float*);

/* ------------------
the main program
C.Wang 1010, 2014
-------------------*/
void FyMain(int argc, char **argv)
{
	// create a new world
	BOOL4 beOK = FyStartFlyWin32("NTU@2014 Homework #02 - Use Fly2", 0, 0, 1024, 768, FALSE);

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
	npc1ID = scene.LoadCharacter("Donzo2");
	npc2ID = scene.LoadCharacter("Robber02");

	// put the character on terrain
	float apos[3], cpos[3], fDir[3], uDir[3];
	FnCharacter actor, npc1, npc2;
	actor.ID(actorID);
	npc1.ID(npc1ID);
	npc2.ID(npc2ID);
	apos[0] = 3569.0f; apos[1] = -3208.0f; apos[2] = 1000.0f;
	fDir[0] = 1.0f; fDir[1] = 0.0f; fDir[2] = 0.0f;
	uDir[0] = 0.0f; uDir[1] = 0.0f; uDir[2] = 1.0f;
	actor.SetDirection(fDir, uDir);
	fDir[0] = -1.0f; fDir[1] = -1.0f;
	npc1.SetDirection(fDir, uDir);
	fDir[0] = 1.0f;
	npc2.SetDirection(fDir, uDir);

	actor.SetTerrainRoom(terrainRoomID, 10.0f);
	npc1.SetTerrainRoom(terrainRoomID, 10.0f);
	npc2.SetTerrainRoom(terrainRoomID, 10.0f);
	beOK = actor.PutOnTerrain(apos);
	apos[1] -= 150.0f;
	beOK = npc1.PutOnTerrain(apos);
	apos[1] -= 50.0f;
	beOK = npc2.PutOnTerrain(apos);

	// Get two character actions pre-defined at Lyubu2
	idleID = actor.GetBodyAction(NULL, "Idle");
	runID = actor.GetBodyAction(NULL, "Run");
	attackID = actor.GetBodyAction(NULL, "NormalAttack1");

	idle1ID = npc1.GetBodyAction(NULL, "Idle");
	damage1ID = npc1.GetBodyAction(NULL, "DamageL");
	die1ID = npc1.GetBodyAction(NULL, "Die");
	idle2ID = npc2.GetBodyAction(NULL, "CombatIdle");
	damage2ID = npc2.GetBodyAction(NULL, "Damage1");
	die2ID = npc2.GetBodyAction(NULL, "DEAD");

	// set the character to idle action
	curPoseID = idleID;
	actor.SetCurrentAction(NULL, 0, curPoseID);
	actor.Play(START, 0.0f, FALSE, TRUE);
	actor.TurnRight(90.0f);

	npc1.SetCurrentAction(NULL, 0, idle1ID);
	npc1.Play(START, 0.0f, FALSE, TRUE);
	npc2.SetCurrentAction(NULL, 0, idle2ID);
	npc2.Play(START, 0.0f, FALSE, TRUE);

	// translate the camera
	cID = scene.CreateObject(CAMERA);
	FnCamera camera;
	camera.ID(cID);
	camera.SetNearPlane(5.0f);
	camera.SetFarPlane(100000.0f);

	// set camera initial position and orientation
	actor.GetPosition(apos);
	//cpos[0] = 4315.783f; cpos[1] = -3199.686f; cpos[2] = 93.046f;
	fDir[0] = DIST; fDir[1] = 0.0f; fDir[2] = -HEIGHT;
	cpos[0] = apos[0] - fDir[0]; cpos[1] = apos[1] - fDir[1]; cpos[2] = apos[2] - fDir[2];
	float distance = sqrt(double((fDir[0])*(fDir[0]) + (fDir[1])*(fDir[1])));
	uDir[0] = -fDir[2] * fDir[0] / distance; uDir[1] = -fDir[2] * fDir[1] / distance; uDir[2] = distance;
	//fDir[0] = -0.983f; fDir[1] = -0.143f; fDir[2] = -0.119f;
	//uDir[0] = -0.116f; uDir[1] = -0.031f; uDir[2] = 0.993f;
	camera.SetPosition(cpos);
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
	FyDefineHotKey(FY_DOWN, Movement, FALSE);    // Down for turning right
	FyDefineHotKey(FY_RIGHT, Movement, FALSE);   // Right for turning right
	FyDefineHotKey(FY_LEFT, Movement, FALSE);    // Left for turning left
	FyDefineHotKey('W', Movement, FALSE);        // Up for moving forward
	FyDefineHotKey('S', Movement, FALSE);        // Down for turning right
	FyDefineHotKey('D', Movement, FALSE);        // Right for turning right
	FyDefineHotKey('A', Movement, FALSE);        // Left for turning left
	FyDefineHotKey('J', Movement, FALSE);

	// define some mouse functions
	FyBindMouseFunction(LEFT_MOUSE, InitPivot, PivotCam, NULL, NULL);
	FyBindMouseFunction(MIDDLE_MOUSE, InitZoom, ZoomCam, NULL, NULL);
	FyBindMouseFunction(RIGHT_MOUSE, InitMove, MoveCam, NULL, NULL);

	// bind timers, frame rate = 30 fps
	FyBindTimer(0, 30.0f, GameAI, TRUE);
	FyBindTimer(1, 30.0f, RenderIt, TRUE);

	// invoke the system
	FyInvokeFly(TRUE);
}

/* ------------------------------------------------------------ -
30fps timer callback in fixed frame rate for major game loop
-------------------------------------------------------------- */
void GameAI(int skip)
{
	FnCharacter actor, npc1, npc2;

	// play character pose
	actor.ID(actorID);
	actor.Play(LOOP, (float)skip, FALSE, TRUE);

	npc1.ID(npc1ID);
	if (HP1>0 || (frame - framedamage1 + 1000) % 1000 < dietime1)
		npc1.Play(LOOP, (float)skip, FALSE, TRUE);
	npc2.ID(npc2ID);
	if (HP2>0 || (frame - framedamage2 + 1000) % 1000 < dietime2)
		npc2.Play(LOOP, (float)skip, FALSE, TRUE);
	if ((frame - frameattack + 1000) % 1000 == attacktime)
		actor.SetCurrentAction(NULL, 0, curPoseID, 5.0f);
	if (HP1 > 0)
	{
		if ((frame - framedamage1 + 1000) % 1000 == damagetime1)
			npc1.SetCurrentAction(NULL, 0, idle1ID, 0.0f);
		else if (frame == framedamage1)
			npc1.SetCurrentAction(NULL, 0, damage1ID, 0.0f);
	}
	else if (frame == framedamage1)
	{
		npc1.SetCurrentAction(NULL, 0, die1ID, 0.0f);
	}
	if (HP2 > 0)
	{
		if ((frame - framedamage2 + 1000) % 1000 == damagetime2)
			npc2.SetCurrentAction(NULL, 0, idle2ID, 0.0f);
		else if (frame == framedamage2)
			npc2.SetCurrentAction(NULL, 0, damage2ID, 0.0f);
	}
	else if (frame == framedamage2)
	{
		npc2.SetCurrentAction(NULL, 0, die2ID, 0.0f);
	}

	FnCamera camera;
	camera.ID(cID);

	FnObject terrain;
	terrain.ID(tID);

	float fDir[3], uDir[3] = { 0, 0, 1 }, cpos[3], apos[3], distance, height, length;
	camera.GetPosition(cpos);
	actor.GetPosition(apos);
	fDir[0] = apos[0] - cpos[0]; fDir[1] = apos[1] - cpos[1]; fDir[2] = apos[2] - cpos[2];
	distance = sqrt(double((fDir[0])*(fDir[0]) + (fDir[1])*(fDir[1])));
	height = -fDir[2];
	length = sqrt(double(distance*distance + height*height));
	uDir[0] = -fDir[2] * fDir[0] / distance; uDir[1] = -fDir[2] * fDir[1] / distance; uDir[2] = distance;
	camera.SetDirection(fDir, uDir);
	uDir[0] = 0; uDir[1] = 0; uDir[2] = 1;
	bool up = FyCheckHotKeyStatus(FY_UP) || FyCheckHotKeyStatus('W'),
		down = FyCheckHotKeyStatus(FY_DOWN) || FyCheckHotKeyStatus('S'),
		left = FyCheckHotKeyStatus(FY_LEFT) || FyCheckHotKeyStatus('A'),
		right = FyCheckHotKeyStatus(FY_RIGHT) || FyCheckHotKeyStatus('D'),
		act = (frame - frameattack + 1000) % 1000 >= attacktime;
	if (act)
	{
		if (up&&!down)
		{
			actor.SetDirection(fDir, uDir);
			float norm = sqrt(double((fDir[0])*(fDir[0]) + (fDir[1])*(fDir[1])));

			actor.MoveForward(speed, TRUE);
			actor.GetPosition(apos);
			cpos[0] = apos[0] - LENGTH*fDir[0] / norm;
			cpos[1] = apos[1] - LENGTH*fDir[1] / norm;
			cpos[2] = apos[2] + HEIGHT;
			float dir[3] = { cpos[0] - apos[0], cpos[1] - apos[1], 0 }, result[3];
			if (terrain.HitTest(apos, dir, result) > 0)
			{
				float line[3] = { result[0] - apos[0], result[1] - apos[1], result[2] - apos[2] };
				if (line[0] * line[0] + line[1] * line[1]<LENGTH*LENGTH)
				{
					cpos[0] = result[0];
					cpos[1] = result[1];
					cpos[2] = apos[2] + sqrt(double(LENGTH*LENGTH + HEIGHT*HEIGHT - (line[0] * line[0] + line[1] * line[1])));
				}
			}
			camera.SetPosition(cpos);
		}
		if (down&&!up)
		{
			float bDir[3] = { -fDir[0], -fDir[1], -fDir[2] };
			actor.SetDirection(bDir, uDir);
			float norm = sqrt(double((bDir[0])*(bDir[0]) + (bDir[1])*(bDir[1])));

			actor.MoveForward(speed, TRUE);
			actor.GetPosition(apos);
			cpos[0] = apos[0] - LENGTH*fDir[0] / norm;
			cpos[1] = apos[1] - LENGTH*fDir[1] / norm;
			cpos[2] = apos[2] + HEIGHT;
			float dir[3] = { cpos[0] - apos[0], cpos[1] - apos[1], 0 }, result[3];
			if (terrain.HitTest(apos, dir, result) > 0)
			{
				float line[3] = { result[0] - apos[0], result[1] - apos[1], result[2] - apos[2] };
				if (line[0] * line[0] + line[1] * line[1]<LENGTH*LENGTH)
				{
					cpos[0] = result[0];
					cpos[1] = result[1];
					cpos[2] = apos[2] + sqrt(double(LENGTH*LENGTH + HEIGHT*HEIGHT - (line[0] * line[0] + line[1] * line[1])));
				}
			}
			camera.SetPosition(cpos);
		}
		if (left&&!right)
		{
			float lDir[3] = { -fDir[1], fDir[0], fDir[2] }, apos2[3];
			actor.SetDirection(lDir, uDir);
			actor.TurnRight(-asin(speed / 2 / distance) * 180 / pi);
			actor.MoveForward(speed, TRUE);

			actor.GetPosition(apos2);
			if ((apos[0] - apos2[0])*(apos[0] - apos2[0]) + (apos[1] - apos2[1])*(apos[1] - apos2[1]) == 0)
			{
				camera.TurnRight(-asin(2 * speed / 2 / distance) * 180 / pi);
				camera.MoveRight(2 * speed);
			}
		}
		if (right&&!left)
		{
			float rDir[3] = { fDir[1], -fDir[0], fDir[2] }, apos2[3];
			actor.SetDirection(rDir, uDir);
			actor.TurnRight(asin(speed / 2 / distance) * 180 / pi);
			actor.MoveForward(speed, TRUE);

			actor.GetPosition(apos2);
			if ((apos[0] - apos2[0])*(apos[0] - apos2[0]) + (apos[1] - apos2[1])*(apos[1] - apos2[1]) == 0)
			{
				camera.TurnRight(asin(2 * speed / 2 / distance) * 180 / pi);
				camera.MoveRight(-2 * speed);
			}
		}
	}
}

/* ----------------------
perform the rendering
C.Wang 0720, 2006
---------------------- - /
/ ----------------------
perform the rendering
C.Wang 0720, 2006
---------------------- - */
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
	float cpos[3], apos[3], distance, height, length;//
	FnCharacter actor;
	actor.ID(actorID);

	FnObject terrain;
	terrain.ID(tID);

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

/* ------------------
movement control
------------------ - */
void Movement(BYTE code, BOOL4 value)
{
	FnCharacter actor;
	actor.ID(actorID);

	bool up = FyCheckHotKeyStatus(FY_UP) || FyCheckHotKeyStatus('W'),
		down = FyCheckHotKeyStatus(FY_DOWN) || FyCheckHotKeyStatus('S'),
		left = FyCheckHotKeyStatus(FY_LEFT) || FyCheckHotKeyStatus('A'),
		right = FyCheckHotKeyStatus(FY_RIGHT) || FyCheckHotKeyStatus('D'),
		act = (frame - frameattack + 1000) % 1000 >= attacktime;
	if (code == 'J'&&value == TRUE)
	{
		if ((frame - frameattack + 1000) % 1000> attacktime)
		{
			actor.SetCurrentAction(NULL, 0, attackID, 5.0f);
			actor.Play(ONCE, 0.0f, FALSE, TRUE);
			frameattack = frame;
			FnCharacter npc1, npc2;
			npc1.ID(npc1ID);
			npc2.ID(npc2ID);
			float apos[3], npos[3], vector[2], fDir[3], rDir[3];
			actor.GetDirection(fDir, NULL);
			actor.GetPosition(apos);
			npc1.GetPosition(npos);
			vector[0] = npos[0] - apos[0];
			vector[1] = npos[1] - apos[1];
			rDir[0] = fDir[1]; rDir[1] = -fDir[0];
			if ((HP1>0) && (dot2(vector, fDir) / norm2(fDir)>0.0f) && (dot2(vector, fDir) / norm2(fDir) < 150.0f) && (abs(dot2(vector, rDir)) / norm2(rDir) < 20.0f))
			{
				framedamage1 = frame + 10;
				HP1--;
			}
			npc2.GetPosition(npos);
			vector[0] = npos[0] - apos[0];
			vector[1] = npos[1] - apos[1];
			rDir[0] = fDir[1]; rDir[1] = -fDir[0];
			if ((HP2>0) && (dot2(vector, fDir) / norm2(fDir)>0.0f) && (dot2(vector, fDir) / norm2(fDir) < 150.0f) && (abs(dot2(vector, rDir)) / norm2(rDir) < 20.0f))
			{
				framedamage2 = frame + 10;
				HP2--;
			}
		}
	}
	else if (((up || down) && !(up&&down)) || ((left || right) && !(left&&right)))
	{
		curPoseID = runID;
		if (act)
			actor.SetCurrentAction(NULL, 0, curPoseID, 5.0f);
	}
	else
	{
		curPoseID = idleID;
		if (act)
			actor.SetCurrentAction(NULL, 0, curPoseID, 5.0f);
	}
}

/* ------------------
quit the demo
C.Wang 0327, 2005
------------------ - */
void QuitGame(BYTE code, BOOL4 value)
{
	if (code == FY_ESCAPE) {
		if (value) {
			FyQuitFlyWin32();
		}
	}
}

/* ---------------------------------- -
initialize the pivot of the camera
C.Wang 0329, 2005
------------------------------------ */
void InitPivot(int x, int y)
{
	oldX = x;
	oldY = y;
	frame = 0;
}

/* ------------------
pivot the camera
C.Wang 0329, 2005
------------------ - */
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

/* ----------------------------------
initialize the move of the camera
C.Wang 0329, 2005
---------------------------------- - */
void InitMove(int x, int y)
{
	oldXM = x;
	oldYM = y;
	frame = 0;
}

/* ------------------
move the camera
C.Wang 0329, 2005
------------------ - */
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

/* ----------------------------------
initialize the zoom of the camera
C.Wang 0329, 2005
---------------------------------- - */
void InitZoom(int x, int y)
{
	oldXMM = x;
	oldYMM = y;
	frame = 0;
}

/* ------------------
zoom the camera
C.Wang 0329, 2005
------------------ - */
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

float dot2(float *v1, float *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1];
}

float dot3(float *v1, float *v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

float norm2(float *v)
{
	return sqrt(dot2(v, v));
}

float norm3(float *v)
{
	return sqrt(dot3(v, v));
}