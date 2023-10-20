#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TexCoord);

    //vec3 color = vec3(255.0, 0.0, 100.0);
    //FragColor = vec4(color, 1.0);
}
