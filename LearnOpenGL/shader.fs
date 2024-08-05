#version 330 core
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 FragPos;
in vec3 Normal;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	
	// 漫反射光照
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	// 环境光照
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	
	// 镜面反射光照
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;


	vec3 result = (ambient +  diffuse + specular)* objectColor;
	
	FragColor = vec4( result,1.0);
	//FragColor = vec4( objectColor,1.0);
}