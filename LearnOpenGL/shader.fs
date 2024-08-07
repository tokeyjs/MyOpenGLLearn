#version 330 core

// 物体
struct Material {
	sampler2D diffuse;
    //vec3 specular;  // 镜面光照
	sampler2D specular;
    float shininess;  // 反光度
}; 


// 光
struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	
	// 漫反射光照
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	//vec3 diffuse = diff * material.diffuse * light.diffuse;
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	// 环境光照
	//vec3 ambient = material.ambient * light.ambient;\
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	
	// 镜面反射光照
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = vec3(texture(material.specular, TexCoords))* spec * light.specular;


	vec3 result = ambient +  diffuse + specular;
	FragColor = vec4( result,1.0);

}