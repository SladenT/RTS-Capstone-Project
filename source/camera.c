/*******************************************************************************************
*	Basic camera functionality.
*
*   Created by Davis Teigeler
********************************************************************************************/
#include "camera.h"

static bool init = false;
Camera* mainCam;
float defaultAspectRatio = 1920.0f/1080.0f;

static void InitializeMainCamera(float aspectRatio);

Camera* cam_GetMainCamera(void)
{
    if (!init)
    {
        init = true;
        InitializeMainCamera(defaultAspectRatio);
    }
    return mainCam;
}

void cam_GetCamPosition(Camera cam, vec3 outPos)
{
    vec4 pos;
    mat4 r;
    vec3 s;
    glmc_decompose(cam.transform, pos, r, s);
    outPos = (vec3){pos[0],pos[1],pos[2]};
}

static void InitializeMainCamera(float aspectRatio)
{
    mainCam = malloc(sizeof(Camera));
    // Initial View
    mat4 view;
	glmc_mat4_identity(view);
    vec3 cameraPos   = {0.0f, 2.0f,  3.0f};
	vec3 cameraFront = {0.0f, -0.5f,  -1.0f};
	vec3 cameraUp    = {0.0f, 1.0f,  0.0f};
    vec3 c;
	glmc_vec3_add(cameraPos, cameraFront, c);
	glmc_lookat(cameraPos, c, cameraUp, view);
	
    // Default to 45 degree downward view
	mat4 projection;
	glmc_mat4_identity(projection);
	glmc_perspective(glm_rad(45.0f), aspectRatio, 0.1f, 10000.0f, projection);

    
    glmc_mat4_copy(view, *mainCam->transform);
    glmc_mat4_copy(projection, mainCam->projection);
    mainCam->aspectRatio = aspectRatio;
}

