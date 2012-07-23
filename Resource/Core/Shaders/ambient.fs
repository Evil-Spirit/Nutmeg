//------------------------------------------------------------------------------
//
// ambient fragment shader
//
//------------------------------------------------------------------------------

varying vec2 v_texcoord;

uniform sampler2D s_material_texture_diffuse;
uniform vec4 s_material_color_diffuse;
uniform vec3 s_material_color_ambient;

void main(void) {

	vec4 diffuse_texel = texture2D(s_material_texture_diffuse, v_texcoord);

	gl_FragColor = vec4(s_material_color_ambient, 1.0) * s_material_color_diffuse * diffuse_texel;

}

//------------------------------------------------------------------------------