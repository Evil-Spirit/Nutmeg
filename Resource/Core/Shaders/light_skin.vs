//------------------------------------------------------------------------------
//
// omni skin vertex shader
//
//------------------------------------------------------------------------------

attribute vec3 s_vertex_tangent;
attribute vec3 s_vertex_binormal;
attribute vec4 s_vertex_weight;
attribute vec4 s_vertex_bone;

uniform vec4 s_pose[225];

varying vec2 v_texcoord;
varying vec3 v_light_dir;
varying vec3 v_camera_dir;
varying vec3 v_vertex_pos;

uniform vec3 s_light_camera_pos;
uniform vec3 s_light_pos;

void main(void) {
	
	// transform matrix
	vec4 bones = s_vertex_bone;
	vec4 weights = s_vertex_weight;
	ivec3 bone;


/*	vec4 row_0 = vec4(1, 0, 0, 0);
	vec4 row_1 = vec4(0, 1, 0, 0);
	vec4 row_2 = vec4(0, 0, 1, 0);
*/
	vec4 row_0 = vec4(0);
	vec4 row_1 = vec4(0);
	vec4 row_2 = vec4(0);

	for (int i=0; i<4; i++) {
		bone = ivec3(int(bones.x) * 3) + ivec3(0, 1, 2);
		row_0 += s_pose[bone.x] * weights.x;
		row_1 += s_pose[bone.y] * weights.x;
		row_2 += s_pose[bone.z] * weights.x;
		bones = bones.yzwx;
		weights = weights.yzwx;
	}
/*
	bone = ivec3(int(bones.x) * 3) + ivec3(0, 1, 2);
	vec4 row_0 = s_pose[bone.x];
	vec4 row_1 = s_pose[bone.y];
	vec4 row_2 = s_pose[bone.z];
*/	
	
	

	// vertex
	vec4 vertex;
	vertex.x = dot(row_0, gl_Vertex);
	vertex.y = dot(row_1, gl_Vertex);
	vertex.z = dot(row_2, gl_Vertex);
	vertex.w = 1.0;
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
	
	// normal
	vec3 normal;
	normal.x = dot(row_0.xyz, gl_Normal);
	normal.y = dot(row_1.xyz, gl_Normal);
	normal.z = dot(row_2.xyz, gl_Normal);
	normal = gl_NormalMatrix * normal;

	// tangent
	vec3 tangent;
	tangent.x = dot(row_0.xyz, s_vertex_tangent);
	tangent.y = dot(row_1.xyz, s_vertex_tangent);
	tangent.z = dot(row_2.xyz, s_vertex_tangent);
	tangent = gl_NormalMatrix * tangent;

	// binormal
	vec3 binormal;
	binormal.x = dot(row_0.xyz, s_vertex_binormal);
	binormal.y = dot(row_1.xyz, s_vertex_binormal);
	binormal.z = dot(row_2.xyz, s_vertex_binormal);
	binormal = gl_NormalMatrix * binormal;

	// light_pos
	vertex = gl_ModelViewMatrix * vertex;
	v_vertex_pos = vertex.xyz;
    
	// light_dir
	vec3 dir = s_light_pos - vertex.xyz;
    v_light_dir.x = dot(dir, tangent);
    v_light_dir.y = dot(dir, binormal);
    v_light_dir.z = dot(dir, normal);

    // camera_dir
	dir = s_light_camera_pos - vertex.xyz;
    v_camera_dir.x = dot(dir, tangent);
    v_camera_dir.y = dot(dir, binormal);
    v_camera_dir.z = dot(dir, normal);

    // texcoord
	v_texcoord = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);

}

//------------------------------------------------------------------------------
