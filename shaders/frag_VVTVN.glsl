#version 330 core

in vec2 fragTexCoord;
in vec3 fragColor;

uniform float uAlpha;
uniform sampler2D texture1;

void main()
{
    gl_FragColor = mix(texture(texture1, fragTexCoord), vec4(fragColor, 1.0), uAlpha);
}
