#pragma once

#include "raylib.h"
#include "rlgl.h"

#ifndef RAYLIB_FONTSTASH_H
#define RAYLIB_FONTSTASH_H

FONScontext* rlfonsCreate(int width, int height, int flags);
void rlfonsDelete(FONScontext* ctx);

unsigned int rlfonsRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

unsigned int rlfonsColor(Color color);

#endif

#ifdef RAYLIB_FONTSTASH_IMPLEMENTATION

struct RaylibFONScontext {
	Texture2D tex;
	unsigned char *buff;
	int width, height;
};
typedef struct RaylibFONScontext RaylibFONScontext;

static int rlfons__renderCreate(void* userPtr, int width, int height)
{
	RaylibFONScontext* rl = (RaylibFONScontext*)userPtr;
	// Create may be called multiple times, delete existing texture.
	if (rl->tex.id != 0) {
		UnloadTexture(rl->tex);
		rl->tex = {0};
	}
	if (rl->buff) {
		free(rl->buff);
	}

	rl->buff = (unsigned char*)malloc(width * height * 4);
	rl->tex.id = rlLoadTexture(rl->buff, width, height, RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, 1);
	rl->tex.width = width;
	rl->tex.height = height;
	rl->tex.mipmaps = 1;
	rl->tex.format = RL_PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;
	return 1;
}

static int rlfons__renderResize(void* userPtr, int width, int height)
{
	// Reuse create to resize too.
	return rlfons__renderCreate(userPtr, width, height);
}

static void rlfons__renderUpdate(void* userPtr, int* rect, const unsigned char* data)
{
	RaylibFONScontext* rl = (RaylibFONScontext*)userPtr;
	int x = rect[0];
	int y = rect[1];
	int w = rect[2] - rect[0];
	int h = rect[3] - rect[1];

	if (rl->tex.id == 0) return;

	if (!rl->buff) return;

	// for (int i = rect[0]; i < rect[2]; i++) {
	// 	for (int j = rect[1]; j < rect[3]; j++) {
	// 		int index = j * w + i;
	// 		rl->buff[index * 4 + 0] = rl->buff[index * 4 + 1] = rl->buff[index * 4 + 2] = 0; 
	// 		rl->buff[index * 4 + 3] = data[index];
	// 		if (data[index]) printf("Update %d %d\n", index, data[index]);
	// 	}
	// }

	for (int i = 0; i < rl->tex.height; i++) {
		for (int j = 0; j < rl->tex.width; j++) {
			int index = i * rl->tex.width + j;
			rl->buff[index * 4 + 0] = rl->buff[index * 4 + 1] = rl->buff[index * 4 + 2] = 255; 
			rl->buff[index * 4 + 3] = data[index];
		}
	}
	
    rlUpdateTexture(rl->tex.id, 0, 0, rl->tex.width, rl->tex.height, rl->tex.format, rl->buff);
}

static void rlfons__renderDraw(void* userPtr, const float* verts, const float* tcoords, const unsigned int* colors, int nverts)
{
	RaylibFONScontext* rl = (RaylibFONScontext*)userPtr;
	if (rl->tex.id == 0) return;

	unsigned char *colorsb = (unsigned char*)colors;

	rlBegin(RL_TRIANGLES);
	rlSetTexture(rl->tex.id);
	for (int i = 0; i < nverts; i++) {
		rlColor4ub(colorsb[i * 4 + 0], colorsb[i * 4 + 1], colorsb[i * 4 + 2], colorsb[i * 4 + 3]);
		rlTexCoord2f(tcoords[i * 2 + 0], tcoords[i * 2 + 1]);
		rlVertex2f(verts[i * 2 + 0], verts[i * 2 + 1]);
	}
	rlEnd();
	rlSetTexture(0);
}

static void rlfons__renderDelete(void* userPtr)
{
	RaylibFONScontext* rl = (RaylibFONScontext*)userPtr;
	UnloadTexture(rl->tex);
	free(rl->buff);
	free(rl);
}


FONScontext* rlfonsCreate(int width, int height, int flags)
{
	FONSparams params;
	RaylibFONScontext* rl;

	rl = (RaylibFONScontext*)malloc(sizeof(RaylibFONScontext));
	if (rl == NULL) goto error;
	memset(rl, 0, sizeof(RaylibFONScontext));

	memset(&params, 0, sizeof(params));
	params.width = width;
	params.height = height;
	params.flags = (unsigned char)flags;
	params.renderCreate = rlfons__renderCreate;
	params.renderResize = rlfons__renderResize;
	params.renderUpdate = rlfons__renderUpdate;
	params.renderDraw = rlfons__renderDraw; 
	params.renderDelete = rlfons__renderDelete;
	params.userPtr = rl;

	return fonsCreateInternal(&params);

error:
	if (rl != NULL) free(rl);
	return NULL;
}

void rlfonsDelete(FONScontext* ctx)
{
	fonsDeleteInternal(ctx);
}

unsigned int rlfonsRGBA(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return (r) | (g << 8) | (b << 16) | (a << 24);
}

unsigned int rlfonsColor(Color color)
{
	return rlfonsRGBA(color.r, color.g, color.b, color.a);
}

#endif