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
uniform vec3 s_parallax_scale;

void main(void) {

	
	//--------------------------------------------------------------------------
	// parallax
	//--------------------------------------------------------------------------

	const int num_steps = 1;

	vec3 camera_dir = normalize(v_camera_dir);
	vec2 parallax_coord = v_texcoord;
	float bias = -s_parallax_scale.y / float(num_steps);
	float scale = s_parallax_scale.x / float(num_steps);

	for (int i=0; i<num_steps; i++) {
		float height = texture2D(s_material_texture_normal, parallax_coord).w * scale + bias;
		parallax_coord += height * camera_dir.xy;
	}

	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------
	
	vec3 light_dir = normalize(v_light_dir);
//	if (dot(vec3(0.0, 0.0, 1.0), light_dir) < 0.0) discard;

	vec4 diffuse_texel = texture2D(s_material_texture_diffuse, parallax_coord);

	vec3 diffuse = vec3(s_material_color_diffuse) * diffuse_texel.xyz;
	vec3 specular = s_material_color_specular * texture2D(s_material_texture_specular, parallax_coord).xyz;

	vec3 normal = normalize(texture2D(s_material_texture_normal, parallax_coord).xyz * 2.0 - 1.0);

	float specular_light = pow(clamp(dot(reflect(-light_dir, normal), camera_dir), 0.0, 1.0), s_material_specular_power);
	float diffuse_light  = clamp(dot(light_dir, normal), 0.0, 1.0);

	vec3 result = vec3(0.0, 0.0, 0.0);

	result += diffuse * diffuse_light;
	result += specular * specular_light;

//	float attenuation = 1.0f;
	float attenuation = clamp(1.0 - length(v_vertex_pos - s_light_pos) * 1.0 / s_light_radius, 0.0, 1.0);

	result *= attenuation * s_light_color;

	gl_FragColor = vec4(result, diffuse_texel.w * s_material_color_diffuse.w);

}

//------------------------------------------------------------------------------