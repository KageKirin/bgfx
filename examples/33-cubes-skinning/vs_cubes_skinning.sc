$input a_position, a_color0, a_indices, a_weight
$output v_color0

/*
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "../common/common.sh"

uniform mat4 u_matrices; //[11*11];

void main()
{
	//	mat4 m_base = mul(u_model[0],
	//	a_weight.x * u_matrices[int(a_indices.x)] + 
	//	a_weight.y * u_matrices[int(a_indices.y)] +
	//	a_weight.z * u_matrices[int(a_indices.z)] +
	//	a_weight.w * u_matrices[int(a_indices.w)]);

	gl_Position = mul(u_model[0] //* u_matrices
	 * u_viewProj, vec4(a_position, 1.0) );
	v_color0 = a_indices;
}
