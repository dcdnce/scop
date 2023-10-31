#version 330 core

in vec2 fragTexCoord;
flat in vec3 fragColor;

void main()
{
    gl_FragColor = vec4(fragColor, 1.0);
}
