/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include <bx/float4x4_t.h>

struct PosColorVertexBlending
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr;
	uint8_t m_indices[4];
	float m_weight[4];

	static void init()
	{
		ms_decl
			.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Color0,   4, bgfx::AttribType::Uint8, true)
			.add(bgfx::Attrib::Indices,  4, bgfx::AttribType::Uint8)
			.add(bgfx::Attrib::Weight,   4, bgfx::AttribType::Float) //, true)
			.end();
	};

	static bgfx::VertexDecl ms_decl;
};

bgfx::VertexDecl PosColorVertexBlending::ms_decl;

#define GEN_CUBE_VERTICES(blendindices_x, blendindices_y, blendindices_z, blendindices_w, blendweights_x, blendweights_y, blendweights_z, blendweights_w) \
	{-1.0f,  1.0f,  1.0f, 0xff000000, {blendindices_x, blendindices_y, blendindices_z, blendindices_w}, {blendweights_x, blendweights_y, blendweights_z, blendweights_w} }, \
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff, {blendindices_x, blendindices_y, blendindices_z, blendindices_w}, {blendweights_x, blendweights_y, blendweights_z, blendweights_w} }, \
	{-1.0f, -1.0f,  1.0f, 0xff00ff00, {blendindices_x, blendindices_y, blendindices_z, blendindices_w}, {blendweights_x, blendweights_y, blendweights_z, blendweights_w} }, \
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff, {blendindices_x, blendindices_y, blendindices_z, blendindices_w}, {blendweights_x, blendweights_y, blendweights_z, blendweights_w} }, \
	{-1.0f,  1.0f, -1.0f, 0xffff0000, {blendindices_x, blendindices_y, blendindices_z, blendindices_w}, {blendweights_x, blendweights_y, blendweights_z, blendweights_w} }, \
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff, {blendindices_x, blendindices_y, blendindices_z, blendindices_w}, {blendweights_x, blendweights_y, blendweights_z, blendweights_w} }, \
	{-1.0f, -1.0f, -1.0f, 0xffffff00, {blendindices_x, blendindices_y, blendindices_z, blendindices_w}, {blendweights_x, blendweights_y, blendweights_z, blendweights_w} }, \
	{ 1.0f, -1.0f, -1.0f, 0xffffffff, {blendindices_x, blendindices_y, blendindices_z, blendindices_w}, {blendweights_x, blendweights_y, blendweights_z, blendweights_w} }


static PosColorVertexBlending s_cubeVertices[] =
{
	GEN_CUBE_VERTICES(0, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(10,0, 0, 0, 1.0f, 0.0f, 0.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(10,11, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(10,0, 12, 0, 1.0f, 0.0f, 1.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(1, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(2, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(3, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(4, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(5, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(6, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(7, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(8, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(9, 0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(10,0, 0, 13, 1.0f, 0.0f, 0.0f, 1.0f),

	GEN_CUBE_VERTICES(0, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(10,14, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(10,0, 15, 0, 1.0f, 0.0f, 1.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(1, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(2, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(3, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(4, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(5, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(6, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(7, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(8, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(9, 0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(10,0, 0, 16, 1.0f, 0.0f, 0.0f, 1.0f),

	GEN_CUBE_VERTICES(0, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(10,17, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(10,0, 18, 0, 1.0f, 0.0f, 1.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(1, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(2, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(3, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(4, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(5, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(6, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(7, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(8, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(9, 0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(10,0, 0, 19, 1.0f, 0.0f, 0.0f, 1.0f),

	GEN_CUBE_VERTICES(0, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),
	GEN_CUBE_VERTICES(10,20, 0, 0, 1.0f, 1.0f, 0.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(1, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(2, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(3, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(4, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(5, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(6, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(7, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(8, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(9, 0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),
	GEN_CUBE_VERTICES(10,0, 21, 0, 1.0f, 0.0f, 1.0f, 0.0f),

	GEN_CUBE_VERTICES(0, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(1, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(2, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(3, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(4, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(5, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(6, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(7, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(8, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(9, 0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
	GEN_CUBE_VERTICES(10,0, 0, 22, 1.0f, 0.0f, 0.0f, 1.0f),
};


#define GEN_CUBE_INDICES(offset) \
	offset + 0, offset + 1, offset + 2, \
	offset + 1, offset + 3, offset + 2, \
	offset + 4, offset + 6, offset + 5, \
	offset + 5, offset + 6, offset + 7, \
	offset + 0, offset + 2, offset + 4, \
	offset + 4, offset + 2, offset + 6, \
	offset + 1, offset + 5, offset + 3, \
	offset + 5, offset + 7, offset + 3, \
	offset + 0, offset + 4, offset + 1, \
	offset + 4, offset + 5, offset + 1, \
	offset + 2, offset + 3, offset + 6, \
	offset + 6, offset + 3, offset + 7

static const uint16_t s_cubeTriList[] =
{
	GEN_CUBE_INDICES(0),
	GEN_CUBE_INDICES(1),
	GEN_CUBE_INDICES(2),
	GEN_CUBE_INDICES(3),
	GEN_CUBE_INDICES(4),
	GEN_CUBE_INDICES(5),
	GEN_CUBE_INDICES(6),
	GEN_CUBE_INDICES(7),
	GEN_CUBE_INDICES(8),
	GEN_CUBE_INDICES(9),
	GEN_CUBE_INDICES(10),

	GEN_CUBE_INDICES(11 + 0),
	GEN_CUBE_INDICES(11 + 1),
	GEN_CUBE_INDICES(11 + 2),
	GEN_CUBE_INDICES(11 + 3),
	GEN_CUBE_INDICES(11 + 4),
	GEN_CUBE_INDICES(11 + 5),
	GEN_CUBE_INDICES(11 + 6),
	GEN_CUBE_INDICES(11 + 7),
	GEN_CUBE_INDICES(11 + 8),
	GEN_CUBE_INDICES(11 + 9),
	GEN_CUBE_INDICES(11 + 10),

	GEN_CUBE_INDICES(22 + 0),
	GEN_CUBE_INDICES(22 + 1),
	GEN_CUBE_INDICES(22 + 2),
	GEN_CUBE_INDICES(22 + 3),
	GEN_CUBE_INDICES(22 + 4),
	GEN_CUBE_INDICES(22 + 5),
	GEN_CUBE_INDICES(22 + 6),
	GEN_CUBE_INDICES(22 + 7),
	GEN_CUBE_INDICES(22 + 8),
	GEN_CUBE_INDICES(22 + 9),
	GEN_CUBE_INDICES(22 + 10),	

	GEN_CUBE_INDICES(33 + 0),
	GEN_CUBE_INDICES(33 + 1),
	GEN_CUBE_INDICES(33 + 2),
	GEN_CUBE_INDICES(33 + 3),
	GEN_CUBE_INDICES(33 + 4),
	GEN_CUBE_INDICES(33 + 5),
	GEN_CUBE_INDICES(33 + 6),
	GEN_CUBE_INDICES(33 + 7),
	GEN_CUBE_INDICES(33 + 8),
	GEN_CUBE_INDICES(33 + 9),
	GEN_CUBE_INDICES(33 + 10),	

	GEN_CUBE_INDICES(44 + 0),
	GEN_CUBE_INDICES(44 + 1),
	GEN_CUBE_INDICES(44 + 2),
	GEN_CUBE_INDICES(44 + 3),
	GEN_CUBE_INDICES(44 + 4),
	GEN_CUBE_INDICES(44 + 5),
	GEN_CUBE_INDICES(44 + 6),
	GEN_CUBE_INDICES(44 + 7),
	GEN_CUBE_INDICES(44 + 8),
	GEN_CUBE_INDICES(44 + 9),
	GEN_CUBE_INDICES(44 + 10),	

	GEN_CUBE_INDICES(55 + 0),
	GEN_CUBE_INDICES(55 + 1),
	GEN_CUBE_INDICES(55 + 2),
	GEN_CUBE_INDICES(55 + 3),
	GEN_CUBE_INDICES(55 + 4),
	GEN_CUBE_INDICES(55 + 5),
	GEN_CUBE_INDICES(55 + 6),
	GEN_CUBE_INDICES(55 + 7),
	GEN_CUBE_INDICES(55 + 8),
	GEN_CUBE_INDICES(55 + 9),
	GEN_CUBE_INDICES(55 + 10),	

	GEN_CUBE_INDICES(66 + 0),
	GEN_CUBE_INDICES(66 + 1),
	GEN_CUBE_INDICES(66 + 2),
	GEN_CUBE_INDICES(66 + 3),
	GEN_CUBE_INDICES(66 + 4),
	GEN_CUBE_INDICES(66 + 5),
	GEN_CUBE_INDICES(66 + 6),
	GEN_CUBE_INDICES(66 + 7),
	GEN_CUBE_INDICES(66 + 8),
	GEN_CUBE_INDICES(66 + 9),
	GEN_CUBE_INDICES(66 + 10),	

	GEN_CUBE_INDICES(77 + 0),
	GEN_CUBE_INDICES(77 + 1),
	GEN_CUBE_INDICES(77 + 2),
	GEN_CUBE_INDICES(77 + 3),
	GEN_CUBE_INDICES(77 + 4),
	GEN_CUBE_INDICES(77 + 5),
	GEN_CUBE_INDICES(77 + 6),
	GEN_CUBE_INDICES(77 + 7),
	GEN_CUBE_INDICES(77 + 8),
	GEN_CUBE_INDICES(77 + 9),
	GEN_CUBE_INDICES(77 + 10),	

	GEN_CUBE_INDICES(88 + 0),
	GEN_CUBE_INDICES(88 + 1),
	GEN_CUBE_INDICES(88 + 2),
	GEN_CUBE_INDICES(88 + 3),
	GEN_CUBE_INDICES(88 + 4),
	GEN_CUBE_INDICES(88 + 5),
	GEN_CUBE_INDICES(88 + 6),
	GEN_CUBE_INDICES(88 + 7),
	GEN_CUBE_INDICES(88 + 8),
	GEN_CUBE_INDICES(88 + 9),
	GEN_CUBE_INDICES(88 + 10),	

	GEN_CUBE_INDICES(99 + 0),
	GEN_CUBE_INDICES(99 + 1),
	GEN_CUBE_INDICES(99 + 2),
	GEN_CUBE_INDICES(99 + 3),
	GEN_CUBE_INDICES(99 + 4),
	GEN_CUBE_INDICES(99 + 5),
	GEN_CUBE_INDICES(99 + 6),
	GEN_CUBE_INDICES(99 + 7),
	GEN_CUBE_INDICES(99 + 8),
	GEN_CUBE_INDICES(99 + 9),
	GEN_CUBE_INDICES(99 + 10),	

	GEN_CUBE_INDICES(110 + 0),
	GEN_CUBE_INDICES(110 + 1),
	GEN_CUBE_INDICES(110 + 2),
	GEN_CUBE_INDICES(110 + 3),
	GEN_CUBE_INDICES(110 + 4),
	GEN_CUBE_INDICES(110 + 5),
	GEN_CUBE_INDICES(110 + 6),
	GEN_CUBE_INDICES(110 + 7),
	GEN_CUBE_INDICES(110 + 8),
	GEN_CUBE_INDICES(110 + 9),
	GEN_CUBE_INDICES(110 + 10),	
};



class ExampleCubes : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		BX_UNUSED(s_cubeTriList);

		Args args(_argc, _argv);

		m_width  = 1280;
		m_height = 720;
		m_debug  = BGFX_DEBUG_TEXT;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::init(args.m_type, args.m_pciId);
		bgfx::reset(m_width, m_height, m_reset);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
				);

		// Create vertex stream declaration.
		PosColorVertexBlending::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
				, PosColorVertexBlending::ms_decl
				);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(
				// Static data can be passed with bgfx::makeRef
				//bgfx::makeRef(s_cubeTriStrip, sizeof(s_cubeTriStrip) )
				bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList) )
				);

		// Create program from shaders.
		m_program = loadProgram("vs_cubes_skinning", "fs_cubes_skinning");
		u_matrices = bgfx::createUniform("u_matrices", bgfx::UniformType::Mat4, 22);

		m_timeOffset = bx::getHPCounter();
	}

	virtual int shutdown() BX_OVERRIDE
	{
		// Cleanup.
		bgfx::destroyUniform(u_matrices);
		bgfx::destroyIndexBuffer(m_ibh);
		bgfx::destroyVertexBuffer(m_vbh);
		bgfx::destroyProgram(m_program);

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}

	bool update() BX_OVERRIDE
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset) )
		{
			int64_t now = bx::getHPCounter();
			static int64_t last = now;
			const int64_t frameTime = now - last;
			last = now;
			const double freq = double(bx::getHPFrequency() );
			const double toMs = 1000.0/freq;

		//	float time = (float)( (now-m_timeOffset)/double(bx::getHPFrequency() ) );

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/33-cubes-skinning");
			bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Rendering static mesh with skinning information.");
			bgfx::dbgTextPrintf(0, 3, 0x0f, "Frame: % 7.3f[ms]", double(frameTime)*toMs);

			float at[3]  = { 0.0f, 0.0f,   0.0f };
			float eye[3] = { 0.0f, 0.0f, -35.0f };

			// Set view and projection matrix for view 0.
			const bgfx::HMD* hmd = bgfx::getHMD();
			if (NULL != hmd && 0 != (hmd->flags & BGFX_HMD_RENDERING) )
			{
				float view[16];
				bx::mtxQuatTranslationHMD(view, hmd->eye[0].rotation, eye);
				bgfx::setViewTransform(0, view, hmd->eye[0].projection, BGFX_VIEW_STEREO, hmd->eye[1].projection);

				// Set view 0 default viewport.
				//
				// Use HMD's width/height since HMD's internal frame buffer size
				// might be much larger than window size.
				bgfx::setViewRect(0, 0, 0, hmd->width, hmd->height);
			}
			else
			{
				float view[16];
				bx::mtxLookAt(view, eye, at);

				float proj[16];
				bx::mtxProj(proj, 60.0f, float(m_width)/float(m_height), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);



			// Submit cubes
			// create 23 matrices:
			// 0 is the base
			// 1-23 are row
			bx::float4x4_t matrices[23];
			for(auto& m : matrices)
			{
				bx::mtxIdentity((float*)&m);
			};
			
			for (uint32_t xx = 0; xx < 11; ++xx)
			{
				bx::float4x4_t& mtx = matrices[1 + xx];
				bx::mtxTranslate((float*)&mtx, -15.0f + float(xx) * 3.0f, 0, 0);
			}
			
			for (uint32_t yy = 0; yy < 11; ++yy)
			{
				bx::float4x4_t& mtx = matrices[12 + yy];
				bx::mtxTranslate((float*)&mtx, 0, -15.0f + float(yy) * 3.0f, 0);
			}
			

			// Submit 11x11 cubes.
			{
				// Set model matrix for rendering.
				bgfx::setTransform(matrices, 23);
				bgfx::setUniform(u_matrices, &matrices[1], 22);

				// Set vertex and index buffer.
				bgfx::setVertexBuffer(m_vbh);
				bgfx::setIndexBuffer(m_ibh);

				// Set render states.
				bgfx::setState(0
					| BGFX_STATE_DEFAULT
					//| BGFX_STATE_PT_TRISTRIP
					);

				// Submit primitive for rendering to view 0.
				bgfx::submit(0, m_program);
			}

			// Advance to next frame. Rendering thread will be kicked to
			// process submitted rendering primitives.
			bgfx::frame();

			return true;
		}

		return false;
	}

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle m_ibh;
	bgfx::ProgramHandle m_program;
	bgfx::UniformHandle u_matrices;
	int64_t m_timeOffset;
};

ENTRY_IMPLEMENT_MAIN(ExampleCubes);
