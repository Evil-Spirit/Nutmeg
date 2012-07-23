//------------------------------------------------------------------------------
//
// ambient vertex shader
//
//------------------------------------------------------------------------------

varying vec2 v_texcoord;

void main(void) {

	v_texcoord = (gl_TextureMatrix[0] * gl_MultiTexCoord0).xy;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

//------------------------------------------------------------------------------
