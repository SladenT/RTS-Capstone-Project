#ifndef entityh
#define entityh
#include "components.h"

void e_InitEntities();
uint64_t e_CreateEntity();
mat4* e_GetEntityTransform(uint64_t id);

void e_SetEnitityPosition(uint64_t id, vec3 pos);
void e_SetEnitityRotation(uint64_t id, vec3 pos);
void e_SetEnitityScale(uint64_t id, vec3 pos);
void e_OrbitAroundEntity(uint64_t id1, uint64_t id2, float angle, float radius);
void e_RotateBy(uint64_t id, float angle, vec3 axis);

Entity* e_GetEntity(uint64_t id);



















#endif