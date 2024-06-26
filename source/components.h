/*******************************************************************************************
*	Various component structures to be used by various systems throughout the program.
*	Entities are defined by ID, and thus need no actual structure, only a logical reference
*
*   Created by Davis Teigeler
********************************************************************************************/
#ifndef componentsh
#define componentsh
#include "cglm/call.h"
#include "common.h"

//#region Models
typedef struct 
{
	uint32_t VAO;  //Vertex Array Object, which stores our VBO and EBO
	uint32_t VBO;  //Vertex Buffer Object, which stores our vertex/texture/misc. data for the shader to use
	uint32_t EBO;  //Element Buffer Object (Index Order for Tris)
} Mesh;

typedef struct __attribute__((__packed__)) // 96 Bytes (it doesn't properly pack mesh otherwise)
{
	mat4 	  transform;	// Deprecated - might change this to offset
	Mesh 	  mesh;
	uint64_t  ID;		 	// Entity ID
	uint32_t  mat;			// Material ID
	uint64_t  vertexCount;
} Model;

// #endregion

//#region Materials

typedef enum UniformType
{
	ut_Integer 		= 0x00000001,
	ut_Float   		= 0x00000002,
	ut_Vector4 		= 0x00000004,
	ut_Sampler2D	= 0x00000008
} UniformType;

typedef struct MatAtt
{
	char uniformName[128];
	UniformType type;
	uint32_t size;			//  How large is this attribute in bytes?  Includes the string and the type, and this variable itself (which are 128, 8, and 4 bytes repspectively)
	char data[];
} MatAtt;

typedef struct Material
{
	uint64_t  ID;				// Material ID, distinct from entity ID
	uint32_t  size;				// Since materials can have dynamic size, we keep track of it here and then we can make enough room for it in the Arena
	uint32_t  count;			// How many material attributes are there?
	uint64_t  isUnique;			// A Unique material will be disposed of when the model using it is disposed (technically a bool, but the size keeps us byte aligned, most of the time)
	MatAtt   *matAttributes;	// Do *not* access like an array, use the provided material iterator to access material attributes
} Material;


//#endregion

//#region Entity

// An entity is the base for any 3D object in the scene.  Using the identifier, we can transpose various components onto the Entity.
// Parent entities offset the transform of child entities

// TODO: Scale, Rotation and Translation vectors (so as to normalize transformations)?  Think it over
typedef struct Entity
{
	uint64_t ID;		// might not need ID
	mat4 transform;
	vec3 position;
	vec3 scale;
	vec3 rotation;
	uint64_t parent;
} Entity;









//#endregion

//#region Collider

typedef enum ColliderType
{
	cl_NONE 		= 0x00000000,
	cl_AABB 		= 0x00000001,
	cl_TRIGGER		= 0X00000002
} ColliderType;

typedef struct ColliderContainer
{
	uint32_t colliderType;
	vec3 	 offset;
	void* 	 mem; 				// Contains the collider data - if a trigger, the collider definition comes before the trigger memory section
} ColliderContainer;

typedef struct Rect3D
{
	float x;    // Origin vectors
	float y;
	float z;
	float w;	// Dimension vectors
	float d;
	float h;
} Rect3D;

typedef struct ColliderTrigger
{
	void (*event)();
} ColliderTrigger;

//#endregion

//#region Physics
typedef struct PhysicBody
{
	uint64_t 		  entity;
	bool 	 		  stat;				// A static physic body is not updated by physics calculations, and is not moved by other physics forces (such as collisions), but
										// still interacts with other physics bodys e.g. a static landmass
	ColliderContainer col;
	float 	 		  mass;
	float			  friction;
	float 			  bounce;
	vec3 	 		  offset;			// This dictates the center of mass, away from entity origin - it does not change the position of the collider.
	vec3 	 		  velocity;
	vec3 	 		  accel;			// Typically, this should only be modified for constant acceleration, such as gravity.  More dynamic forms (such as air resistance)
										// should be custom coded To modify velocity instead
	vec3			  prevPos;			// Used to ensure we don't end up inside colliders.
	uint64_t 		  mask;				// Two physic bodies need to have a bit in common between masks in order to interact.  Default mask is 0x1.
} PhysicBody;


//#endregion











#endif