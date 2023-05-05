#pragma once

#include "snakeObject.h"

namespace Snake
{
	class SnakeTail : SnakeObject
	{
	public:
		SnakeTail();
		~SnakeTail();

		virtual void Init() override;

		virtual bool Move(float deltaTime) override;
		virtual void Draw() override;

		SnakeObject *Parent() { return m_parent; }
		SnakeObject *Child() { return m_child; }

		void SetParent(SnakeObject *parent) { m_parent = parent; }
		void AddChild(SnakeObject *child) { m_child = child; }

	private:
		SnakeObject *m_parent;
		SnakeObject *m_child;

	};

}
