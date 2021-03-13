#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 in_TexCoord;

uniform mat4 u_MVP;

out vec2 TexCoord;

void main()
{
    gl_Position = u_MVP * vec4(position, 1.0f);
    TexCoord = in_TexCoord;
};

#shader fragment
#version 330 core

out vec4 color;
in vec2 TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, TexCoord);
};