#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform bool useTexture;

uniform int levels;
uniform bool toonEnabled;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;
	
	// diffuse
	vec3 norm 	  = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff 	  = max(dot(norm, lightDir), 0.0);
	
	// toon shading
	float level = floor(diff * levels);
	if (toonEnabled) {
		diff = level / levels;
	}
    vec3 diffuse = diff * lightColor;
	
	// specular
    float specularStrength = 0.5;
    vec3 viewDir 	= normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec 		= pow(max(dot(viewDir, reflectDir), 0.0), 32);
	
	// toon shading
	level = floor(spec * levels);
	if (toonEnabled) {
		spec  = level / (levels / 2); // makes specular lighting less intensive than diffuse
	}
    vec3 specular = specularStrength * spec * lightColor;
	
	// attenuation
    float distance    = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09 * distance + 
							   0.032 * (distance * distance));
	ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

	vec3 result = (ambient + diffuse + specular) * vec3(1.0, 1.0, 1.0); // last vector is color (for now just white)
	if(useTexture) {
		FragColor = vec4(result, 1.0) * texture(texture_diffuse1, TexCoords);
	} else {
		FragColor = vec4(result, 1.0);
	}
}