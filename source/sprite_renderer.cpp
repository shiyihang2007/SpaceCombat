
#include "sprite_renderer.h"


SpriteRenderer::SpriteRenderer(const Shader &shader) {
	this->shader = shader;
	this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() { glDeleteVertexArrays(1, &this->quadVAO); }

void SpriteRenderer::DrawSprite(const Texture2D &texture, glm::vec2 position,
								glm::vec2 size, float rotate,
								glm::vec3 color) {
	// prepare transformations
	this->shader.Use();
	glm::mat4 model = glm::mat4(1.0F);
	model = glm::translate(model, glm::vec3(position, 0.0F));
	// first translate (transformations are: scale happens first, then
	// rotation, and then final translation happens; reversed order)

	model =
		glm::translate(model, glm::vec3(0.5F * size.x, 0.5F * size.y, 0.0F));
	// move origin of rotation to center of quad
	model =
		glm::rotate(model, glm::radians(rotate), glm::vec3(0.0F, 0.0F, 1.0F));
	// then rotate
	model =
		glm::translate(model, glm::vec3(-0.5F * size.x, -0.5F * size.y, 0.0F));
	// move origin back

	model = glm::scale(model, glm::vec3(size, 1.0F)); // last scale

	this->shader.SetMatrix4("model", model);

	// render textured quad
	this->shader.SetVector3f("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
	texture.Bind();

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void SpriteRenderer::initRenderData() {
	// configure VAO/VBO
	unsigned int VBO;
	// clang-format off
	float vertices[] = {// pos	  // tex
						0.0F, 1.0F, 0.0F, 1.0F, 
						1.0F, 0.0F, 1.0F, 0.0F, 
						0.0F, 0.0F, 0.0F, 0.0F,
						0.0F, 1.0F, 0.0F, 1.0F, 
						1.0F, 1.0F, 1.0F, 1.0F, 
						1.0F, 0.0F, 1.0F, 0.0F};
	// clang-format on

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
						  static_cast<void *>(nullptr));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
