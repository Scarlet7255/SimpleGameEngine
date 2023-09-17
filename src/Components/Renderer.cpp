#include "Renderer.h"
#include "../Game.h"
#include "../Shader.h"
Renderer::Renderer(GameObject* owner, int updateOrder):Component(owner)
{
}

void Renderer::Draw(Shader* shader)
{
	glDrawElements(
		GL_TRIANGLES,
		6,
		GL_UNSIGNED_INT,
		nullptr
	);
}

void Renderer::OnEnable()
{
	Game::AddRenderer(this);
}

void Renderer::OnDisable()
{
	Game::RemoveRenderer(this);
}
