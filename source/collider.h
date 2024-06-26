#ifndef colliderh
#define collderh
#include "components.h"
#include "structs.h"
#include "camera.h"

CollisionData* c_CheckCollisions(uint64_t ID1, PhysicBody* p1, uint64_t ID2, PhysicBody* p2, double deltaTime);
void c_SetDefaultAABB(PhysicBody* body);

float c_RayAABBIntersection(Ray r, Rect3D a, uint64_t entID);
Ray c_GetMouseRay(Camera c);
Ray c_GetCameraRay(Camera c, int X, int Y);





















#endif