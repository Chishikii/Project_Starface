uniform float hasTexture=0.0f;
uniform samplerCube textureMap;

in vec3 texCoords;
out vec4 fragColor;

void main()
{
    if(hasTexture > 0.5)
    {
        vec4 textureFrag = texture(textureMap, texCoords);
        fragColor = vec4(textureFrag.rgb, textureFrag.a);
    }
    else
        fragColor = vec4(texCoords.x,texCoords.y,0.,1.);
}
