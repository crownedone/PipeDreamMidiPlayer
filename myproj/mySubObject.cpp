#include <math.h>
#include <iostream>

#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>    

#include "mySubObject.h"
#include "myShader.h"

using namespace std;

mySubObject::mySubObject(myMaterial *m, size_t s, size_t e, string n = "noname")
{
	start = s;
	end = e;
	name = n;

	if (m != nullptr) material = new myMaterial(m);
	else material = new myMaterial();
	
	textures.clear();
}

mySubObject::mySubObject(size_t s, size_t e, string n) : mySubObject(nullptr, s, e, n) { }

void mySubObject::setTexture(myTexture* t, TEXTURE_TYPE type)
{
	textures[type] = t;
}

mySubObject::~mySubObject()
{

}

void mySubObject::displaySubObject(myVAO *vao, myShader *shader)
{
	if (end <= start) return;

	if (material != nullptr) material->setUniform(shader, "material");

	if (textures.find(COLORMAP) != textures.end() && textures[COLORMAP] != nullptr)
	{
		shader->setUniform("totexture", 1);
		textures[COLORMAP]->bind(shader, "tex", 1);
	}
	else
	{
		shader->setUniform("tex", 11);
		shader->setUniform("totexture", 0);
	}

	if (textures.find(BUMPMAP) != textures.end() && textures[BUMPMAP] != nullptr )
		textures[BUMPMAP]->bind(shader, "bumptex", 2);
	else 
		shader->setUniform("bumptex", static_cast<int>(11));

	if (textures.find(CUBEMAP) != textures.end() && textures[CUBEMAP] != nullptr)
		textures[CUBEMAP]->bind(shader, "cubetex", 3);
	else
		shader->setUniform("cubetex", static_cast<int>(11));

	if (textures.find(CUBEMAP1) != textures.end() && textures[CUBEMAP1] != nullptr)
		textures[CUBEMAP1]->bind(shader, "cubetex1", 4);

	if (textures.find(REFLECTIONMAP) != textures.end() && textures[REFLECTIONMAP] != nullptr)
		textures[REFLECTIONMAP]->bind(shader, "reflectionTexture", 6);

	if (textures.find(REFRACTIONMAP) != textures.end() && textures[REFRACTIONMAP] != nullptr)
		textures[REFRACTIONMAP]->bind(shader, "refractionTexture", 7);

	if (textures.find(DUDVMAP) != textures.end() && textures[DUDVMAP] != nullptr)
		textures[DUDVMAP]->bind(shader, "dudvMap", 5);

	if (textures.find(DEPTHMAP) != textures.end() && textures[DEPTHMAP] != nullptr)
		textures[DEPTHMAP]->bind(shader, "depthMap", 6);



	
	if (vao != nullptr) vao->draw(start, end);
}

void mySubObject::displayNormals(myVAO* vao, myShader*)
{
}


