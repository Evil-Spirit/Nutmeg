//------------------------------------------------------------------------------
//
// ambient parallax vertex shader
//
//------------------------------------------------------------------------------

attribute vec3 s_vertex_tangent;
attribute vec3 s_vertex_binormal;

varying vec2 v_texcoord;
varying vec3 v_camera_dir;
uniform vec3 s_light_camera_pos;

void main(void) {

	vec3 vertex = (gl_ModelViewMatrix * gl_Vertex).xyz;
	vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
	vec3 tangent = normalize(gl_NormalMatrix * s_vertex_tangent);
	vec3 binormal = normalize(gl_NormalMatrix * s_vertex_binormal);

	v_texcoord = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
    
	vec3 dir = s_light_camera_pos - vertex;

    v_camera_dir.x = dot(dir, tangent);
    v_camera_dir.y = dot(dir, binormal);
    v_camera_dir.z = dot(dir, normal);

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

//------------------------------------------------------------------------------
