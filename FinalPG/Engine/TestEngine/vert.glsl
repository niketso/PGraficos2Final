#version 330 core

// Información de entrada de los vértices. Es diferente para cada una de las ejecuciones de este shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Valores de salida ; serán interpolados para cada fragmento.
out vec2 UV;

// Valores que permanecen constantes para toda la malla. .
uniform mat4 WVP;

void main(){

    // Posición de salida del vértice. En el espacio clip: WVP * position
    gl_Position =  WVP * vec4(vertexPosition_modelspace,1);

    // UV de los vértices. No se necesita un espacio especial para esta línea.
    UV = vertexUV;
}