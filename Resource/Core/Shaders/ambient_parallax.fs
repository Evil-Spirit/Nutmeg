//------------------------------------------------------------------------------
//
// ambient parallax fragment shader
//
//------------------------------------------------------------------------------

varying vec2 v_texcoord;

uniform sampler2D s_material_texture_diffuse;
uniform vec4 s_material_color_diffuse;
uniform vec3 s_material_color_ambient;
uniform vec3 s_parallax_scale;
uniform sampler2D s_material_texture_normal;

varying vec3 v_camera_dir;
const int num_steps = 5;

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

	/*
	float height = texture2D(s_material_texture_normal, v_texcoord).w * s_parallax_scale.x - s_parallax_scale.y;
	
	vec3 eye = normalize(v_camera_dir);
	vec2 parallaxCoord = v_texcoord + eye.xy * height;

    */

	vec4 diffuse_texel = texture2D(s_material_texture_diffuse, parallax_coord);

	gl_FragColor = vec4(s_material_color_ambient, 1.0) * s_material_color_diffuse * diffuse_texel;

}

//------------------------------------------------------------------------------