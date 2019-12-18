layout (location = 0) in vec4 vertexPosition;

out vec4 outputColor;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec4 color;


vec4 vertexPosNew = vertexPosition;

#define COLOR_STEP 18

void main()
{
    //calculate vertex color
    //this should be definable via uniforms
    if(vertexPosition.y < 50){
        outputColor = vec4(0.0, 0.0, 120.0, 1.0);
        vertexPosNew.y = 50.0;
    }
    else if(vertexPosition.y < 80){
        outputColor = vec4(0.0, 120.0, 0.0, 1.0);
    }
    else {
        outputColor = vec4(120.0, 120.0, 120.0, 1.0);
    }

    // Calculate the vertex position
    gl_Position = projectionMatrix * modelViewMatrix * vertexPosNew;
}
