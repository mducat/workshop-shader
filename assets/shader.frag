#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_res;
uniform vec2 u_mouse;
uniform float u_time;
uniform sampler2D u_tex;

void main()
{
    gl_FragColor = vec4(1.);
}
