#version 330 core
in vec2 TexCoords;
out vec4 color;
in vec3 FragPos;  
uniform sampler2D image;
uniform vec3 spriteColor;
 uniform vec3 lightPos;
 uniform float ambient;
 uniform float lightCutOff;

void main()
{    
     float distance = length(FragPos - lightPos);
     if(distance<lightCutOff)
    	color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
     else
    	color = vec4(ambient*spriteColor, 1.0) * texture(image, TexCoords);
}  