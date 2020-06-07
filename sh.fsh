#version 330 core

/*in vec4 vertexColor; // Входная переменная из вершинного шейдера (то же название и тот же тип)

out vec4 color;

void main()
{
    color = vertexColor;
}*/

in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(text,TexCoords).r);
    color = vec4(textColor, 1.0) * sampled;
}
