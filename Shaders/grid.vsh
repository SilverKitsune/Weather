#version 330 core

in vec2 vertex; // Устанавливаем позицию атрибута в 0

out vec4 vertexColor; // Передаем цвет во фрагментный шейдер

void main()
{
    gl_Position = vec4(vertex, 0.0, 1.0); // Напрямую передаем vec3 в vec4
    vertexColor = vec4(1.0, 1.0, 1.0, 0.5); // Устанавливаем значение выходной переменной в темно-красный цвет.
}
