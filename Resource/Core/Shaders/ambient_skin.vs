//------------------------------------------------------------------------------
//
// ambient skin vertex shader
//
//------------------------------------------------------------------------------

attribute vec4 s_vertex_weight;
attribute vec4 s_vertex_bone;

varying vec2 v_texcoord;
uniform vec4 s_pose[225];


void main(void) {

	v_texcoord = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);

	vec4 bones = s_vertex_bone;
	vec4 weights = s_vertex_weight;

	ivec3 bone;

/*	vec4 row_0 = vec4(1, 0, 0, 0);
	vec4 row_1 = vec4(0, 1, 0, 0);
	vec4 row_2 = vec4(0, 0, 1, 0);
*/
	vec4 row_0 = vec4(0.0);
	vec4 row_1 = vec4(0.0);
	vec4 row_2 = vec4(0.0);

	for (int i=0; i<4; i++) {
		bone = ivec3(int(bones.x) * 3) + ivec3(0, 1, 2);
		row_0 += s_pose[bone.x] * weights.x;
		row_1 += s_pose[bone.y] * weights.x;
		row_2 += s_pose[bone.z] * weights.x;
		bones = bones.yzwx;
		weights = weights.yzwx;
	}

/*	bone = ivec3(int(bones.x) * 3) + ivec3(0, 1, 2);
	vec4 row_0 = s_pose[bone.x];
	vec4 row_1 = s_pose[bone.y];
	vec4 row_2 = s_pose[bone.z];
*/
	vec4 vertex = vec4(0.0, 0.0, 0.0, 1.0);

	vertex.x = dot(row_0, gl_Vertex);
	vertex.y = dot(row_1, gl_Vertex);
	vertex.z = dot(row_2, gl_Vertex);

	gl_Position = gl_ModelViewProjectionMatrix * vertex;

}

//------------------------------------------------------------------------------
