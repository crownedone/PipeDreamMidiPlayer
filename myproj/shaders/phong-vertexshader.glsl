#version 440 core

layout(location = 0) in vec4 vertex_modelspace;
layout(location = 1) in vec3 normal_modelspace;

uniform mat4 myprojection_matrix;
uniform mat4 myview_matrix;
uniform mat4 mymodel_matrix;

out vec4 myvertex;
out vec3 mynormal;

void main() {
    gl_Position = myprojection_matrix * myview_matrix * mymodel_matrix * vertex_modelspace; 
	myvertex = vertex_modelspace;
	mynormal = normal_modelspace;
}
