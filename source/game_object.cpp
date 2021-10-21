#include "game_object.h"


GameObject::GameObject() 
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f), Color(1.0f), Rotation(0.0f), Sprite(), IsSolid(false), Destroyed(false), Radius(25.0f) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color, glm::vec2 velocity, float radius) 
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false), Radius(radius) { }

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}

glm::vec2 GameObject::Move(float dt, unsigned int window_width, unsigned int window_height, int dir)
{
    // if not stuck to player board
    // if (!this->Stuck)
    // {
        // move the ball
        // this->Position += this->Velocity * dt;
	// cout<<dir<<endl;
		// if(dir==1)
		// 	this->Position.y -= dt;
		// if(dir==2)
		// 	this->Position.x -= dt;
		// if(dir==3)
		// 	this->Position.y += dt;
		// if(dir==4)
		// 	this->Position.x += dt;
        // then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f)
        {
            this->Velocity.x = -this->Velocity.x;
            // this->Velocity.x = 0;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            // this->Velocity.x = 0;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            // this->Velocity.y = 0;
            this->Position.y = 0.0f;
        }
        else if(this->Position.y + this->Size.y >= window_height)
        {
        	this->Velocity.y = -this->Velocity.y;	
        	// this->Velocity.y = 0;
        	this->Position.y = window_height - this->Size.y;	
        }
    // }
    return this->Position;
}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void GameObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    // this->Stuck = true;
}