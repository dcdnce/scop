#version 330 core

in vec2 fragTexCoord;
flat in vec3 fragColor;

uniform int uColorRendering;
uniform sampler2D texture1;

void main()
{
    // texture rendering
    gl_FragColor = texture(texture1, fragTexCoord);

    if (uColorRendering == 1) { // color rendering
        gl_FragColor = vec4(fragColor, 1.0);
    }

    if (uColorRendering == 2) { // grey rendering
        float grey = (0.2125 * fragColor.x + 0.1154 * fragColor.y + 0.021 * fragColor.z);    
        gl_FragColor = vec4(grey, grey, grey, 1.0);
    }

}
