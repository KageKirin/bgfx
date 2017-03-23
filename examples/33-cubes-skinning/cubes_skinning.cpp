/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"

struct PosColorVertex
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

bgfx::VertexDecl PosColorVertex::ms_decl;

static PosColorVertex s_cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000, {1, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff, {1, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00, {1, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff, {1, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{-1.0f,  1.0f, -1.0f, 0xffff0000, {1, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff, {1, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{-1.0f, -1.0f, -1.0f, 0xffffff00, {1, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff, {1, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },

	{-1.0f,  1.0f,  1.0f, 0xff000000, {0, 2, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff, {0, 2, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00, {0, 2, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff, {0, 2, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{-1.0f,  1.0f, -1.0f, 0xffff0000, {0, 2, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff, {0, 2, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{-1.0f, -1.0f, -1.0f, 0xffffff00, {0, 2, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff, {0, 2, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },

	{-1.0f,  1.0f,  1.0f, 0xff000000, {0, 0, 3, 0}, {0.0f, 0.0f, 1.0f, 0.0f} },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff, {0, 0, 3, 0}, {0.0f, 0.0f, 1.0f, 0.0f} },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00, {0, 0, 3, 0}, {0.0f, 0.0f, 1.0f, 0.0f} },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff, {0, 0, 3, 0}, {0.0f, 0.0f, 1.0f, 0.0f} },
	{-1.0f,  1.0f, -1.0f, 0xffff0000, {0, 0, 3, 0}, {0.0f, 0.0f, 1.0f, 0.0f} },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff, {0, 0, 3, 0}, {0.0f, 0.0f, 1.0f, 0.0f} },
	{-1.0f, -1.0f, -1.0f, 0xffffff00, {0, 0, 3, 0}, {0.0f, 0.0f, 1.0f, 0.0f} },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff, {0, 0, 3, 0}, {0.0f, 0.0f, 1.0f, 0.0f} },

	{-1.0f,  1.0f,  1.0f, 0xff000000, {0, 0, 0, 4}, {0.0f, 0.0f, 0.0f, 1.0f} },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff, {0, 0, 0, 4}, {0.0f, 0.0f, 0.0f, 1.0f} },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00, {0, 0, 0, 4}, {0.0f, 0.0f, 0.0f, 1.0f} },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff, {0, 0, 0, 4}, {0.0f, 0.0f, 0.0f, 1.0f} },
	{-1.0f,  1.0f, -1.0f, 0xffff0000, {0, 0, 0, 4}, {0.0f, 0.0f, 0.0f, 1.0f} },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff, {0, 0, 0, 4}, {0.0f, 0.0f, 0.0f, 1.0f} },
	{-1.0f, -1.0f, -1.0f, 0xffffff00, {0, 0, 0, 4}, {0.0f, 0.0f, 0.0f, 1.0f} },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff, {0, 0, 0, 4}, {0.0f, 0.0f, 0.0f, 1.0f} },

	{-1.0f,  1.0f,  1.0f, 0xff000000, {5, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff, {5, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00, {5, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff, {5, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{-1.0f,  1.0f, -1.0f, 0xffff0000, {5, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff, {5, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{-1.0f, -1.0f, -1.0f, 0xffffff00, {5, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff, {5, 0, 0, 0}, {1.0f, 0.0f, 0.0f, 0.0f} },

	{-1.0f,  1.0f,  1.0f, 0xff000000, {0, 6, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff, {0, 6, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00, {0, 6, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff, {0, 6, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{-1.0f,  1.0f, -1.0f, 0xffff0000, {0, 6, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff, {0, 6, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{-1.0f, -1.0f, -1.0f, 0xffffff00, {0, 6, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff, {0, 6, 0, 0}, {0.0f, 1.0f, 0.0f, 0.0f} },
};

static const uint16_t s_cubeTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,


	8+0, 8+1, 8+2, // 0
	8+1, 8+3, 8+2,
	8+4, 8+6, 8+5, // 2
	8+5, 8+6, 8+7,
	8+0, 8+2, 8+4, // 4
	8+4, 8+2, 8+6,
	8+1, 8+5, 8+3, // 6
	8+5, 8+7, 8+3,
	8+0, 8+4, 8+1, // 8
	8+4, 8+5, 8+1,
	8+2, 8+3, 8+6, // 10
	8+6, 8+3, 8+7,


	16+0, 16+1, 16+2, // 0
	16+1, 16+3, 16+2,
	16+4, 16+6, 16+5, // 2
	16+5, 16+6, 16+7,
	16+0, 16+2, 16+4, // 4
	16+4, 16+2, 16+6,
	16+1, 16+5, 16+3, // 6
	16+5, 16+7, 16+3,
	16+0, 16+4, 16+1, // 8
	16+4, 16+5, 16+1,
	16+2, 16+3, 16+6, // 10
	16+6, 16+3, 16+7,


	24+0, 24+1, 24+2, // 0
	24+1, 24+3, 24+2,
	24+4, 24+6, 24+5, // 2
	24+5, 24+6, 24+7,
	24+0, 24+2, 24+4, // 4
	24+4, 24+2, 24+6,
	24+1, 24+5, 24+3, // 6
	24+5, 24+7, 24+3,
	24+0, 24+4, 24+1, // 8
	24+4, 24+5, 24+1,
	24+2, 24+3, 24+6, // 10
	24+6, 24+3, 24+7,


	32+0, 32+1, 32+2, // 0
	32+1, 32+3, 32+2,
	32+4, 32+6, 32+5, // 2
	32+5, 32+6, 32+7,
	32+0, 32+2, 32+4, // 4
	32+4, 32+2, 32+6,
	32+1, 32+5, 32+3, // 6
	32+5, 32+7, 32+3,
	32+0, 32+4, 32+1, // 8
	32+4, 32+5, 32+1,
	32+2, 32+3, 32+6, // 10
	32+6, 32+3, 32+7,
};

static const uint16_t s_cubeTriStrip[] =
{
	0, 1, 2,
	3,
	7,
	1,
	5,
	0,
	4,
	2,
	6,
	7,
	4,
	5,

	8+0, 8+1, 8+2,
	8+3,
	8+7,
	8+1,
	8+5,
	8+0,
	8+4,
	8+2,
	8+6,
	8+7,
	8+4,
	8+5,

	16+0, 16+1, 16+2,
	16+3,
	16+7,
	16+1,
	16+5,
	16+0,
	16+4,
	16+2,
	16+6,
	16+7,
	16+4,
	16+5,

	24+0, 24+1, 24+2,
	24+3,
	24+7,
	24+1,
	24+5,
	24+0,
	24+4,
	24+2,
	24+6,
	24+7,
	24+4,
	24+5,

	32+0, 32+1, 32+2,
	32+3,
	32+7,
	32+1,
	32+5,
	32+0,
	32+4,
	32+2,
	32+6,
	32+7,
	32+4,
	32+5,
};

class ExampleCubes : public entry::AppI
{
	void init(int _argc, char** _argv) BX_OVERRIDE
	{
		BX_UNUSED(s_cubeTriList, s_cubeTriStrip);

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
		PosColorVertex::init();

		// Create static vertex buffer.
		m_vbh = bgfx::createVertexBuffer(
				// Static data can be passed with bgfx::makeRef
				bgfx::makeRef(s_cubeVertices, sizeof(s_cubeVertices) )
				, PosColorVertex::ms_decl
				);

		// Create static index buffer.
		m_ibh = bgfx::createIndexBuffer(
				// Static data can be passed with bgfx::makeRef
				//bgfx::makeRef(s_cubeTriStrip, sizeof(s_cubeTriStrip) )
				bgfx::makeRef(s_cubeTriList, sizeof(s_cubeTriList) )
				);

		u_matrices = bgfx::createUniform("u_matrices", bgfx::UniformType::Mat4);//, 11*11);

		// Create program from shaders.
		m_program = loadProgram("vs_cubes_skinning", "fs_cubes_skinning");

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

			float time = (float)( (now-m_timeOffset)/double(bx::getHPFrequency() ) );

			// Use debug font to print information about this example.
			bgfx::dbgTextClear();
			bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/03-cubes-skinning");
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



			// Submit 11x11 cubes.
			float basemtx[16];
			bx::mtxRotateXY(basemtx, 0.2, 0.4);

			float matrices[16];// * 11 * 11];
			for (uint32_t yy = 0; yy < 11; ++yy)
			{
				for (uint32_t xx = 0; xx < 11; ++xx)
				{
					float* mtx = matrices; //&matrices[(yy * 11 + xx) * 16];
					bx::mtxRotateXY(mtx, time + xx*0.21f, time + yy*0.37f);
					mtx[12] = -15.0f + float(xx)*3.0f;
					mtx[13] = -15.0f + float(yy)*3.0f;
					mtx[14] = 0.0f;
				}
			}

			{
				// Set model matrix for rendering.
				bgfx::setTransform(basemtx);
				bgfx::setUniform(u_matrices, matrices); //, 11*11);

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
