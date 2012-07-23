//------------------------------------------------------------------------------
//
// omni vertex shader
//
//------------------------------------------------------------------------------

attribute vec3 s_vertex_tangent;
attribute vec3 s_vertex_binormal;

varying vec2 v_texcoord;
varying vec3 v_light_dir;
varying vec3 v_camera_dir;
varying vec3 v_vertex_pos;

uniform vec3 s_light_camera_pos;
uniform vec3 s_light_pos;

void main(void) {
	
/*	mat3 tbn = mat3(gl_Normal, s_vertex_binormal, s_vertex_tangent) * gl_NormalMatrix;
	tbn[0] = normalize(tbn[0]);
	tbn[1] = normalize(tbn[1]);
	tbn[2] = normalize(tbn[2]);
	vec3 vertex = (gl_ModelViewMatrix * gl_Vertex).xyz;

    v_light_dir = tbn * (s_light_pos - v_vertex_pos);
    v_camera_dir = tbn * (s_light_camera_pos - v_vertex_pos);
	v_vertex_pos = vertex;

	v_texcoord = (gl_TextureMatrix[0] * gl_MultiTexCoord0).xy;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
*/
	vec4 vertex = gl_ModelViewMatrix * gl_Vertex;
	vec3 normal = normalize(gl_NormalMatrix * gl_Normal);
	vec3 tangent = normalize(gl_NormalMatrix * s_vertex_tangent);
	vec3 binormal = normalize(gl_NormalMatrix * s_vertex_binormal);

	v_texcoord = vec2(gl_TextureMatrix[0] * gl_MultiTexCoord0);
	v_vertex_pos = vertex.xyz;
    
	vec3 dir = s_light_pos - vertex.xyz;

    v_light_dir.x = dot(dir, tangent);
    v_light_dir.y = dot(dir, binormal);
    v_light_dir.z = dot(dir, normal);

	dir = s_light_camera_pos - vertex.xyz;

    v_camera_dir.x = dot(dir, tangent);
    v_camera_dir.y = dot(dir, binormal);
    v_camera_dir.z = dot(dir, normal);

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//	gl_ClipVertex = gl_ModelViewMatrix * gl_Vertex;

}

//------------------------------------------------------------------------------
