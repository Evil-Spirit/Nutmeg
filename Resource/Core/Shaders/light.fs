//------------------------------------------------------------------------------
//
// omni fragment shader
//
//------------------------------------------------------------------------------

varying vec2 v_texcoord;

varying vec3 v_light_dir;
varying vec3 v_camera_dir;
varying vec3 v_vertex_pos;

uniform sampler2D s_material_texture_diffuse;
uniform sampler2D s_material_texture_normal;
uniform sampler2D s_material_texture_specular;

uniform vec4 s_material_color_diffuse;
uniform vec3 s_material_color_specular;
uniform float s_material_specular_power;

uniform vec3 s_light_pos;
uniform float s_light_radius;
uniform vec3 s_light_color;

void main(void) {

	vec4 diffuse_texel = texture2D(s_material_texture_diffuse, v_texcoord);
	vec3 result = vec3(0.0, 0.0, 0.0);

	vec3 light_dir = normalize(v_light_dir);
	vec3 normal = normalize(texture2D(s_material_texture_normal, v_texcoord).xyz * 2.0 - 1.0);
	
	// diffuse lighting
	vec3 diffuse = vec3(s_material_color_diffuse) * diffuse_texel.xyz;
	float diffuse_light  = clamp(dot(light_dir, normal), 0.0, 1.0);
	result += diffuse * diffuse_light;
	
	// specular lighting	
	vec3 specular = s_material_color_specular * texture2D(s_material_texture_specular, v_texcoord).xyz;
	vec3 camera_dir = normalize(v_camera_dir);
	float specular_light = pow(clamp(dot(reflect(-light_dir, normal), camera_dir), 0.0, 1.0), s_material_specular_power);
	result += specular * specular_light;

	// attenuation
	float attenuation = clamp(1.0 - length(v_vertex_pos - s_light_pos) * 1.0 / s_light_radius, 0.0, 1.0);
	result *= attenuation * attenuation * s_light_color;

	gl_FragColor = vec4(result, diffuse_texel.w * s_material_color_diffuse.w);
}

//------------------------------------------------------------------------------