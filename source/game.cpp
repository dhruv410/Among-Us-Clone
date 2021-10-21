#include <algorithm>
#include <sstream>
#include <iostream>

#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include<bits/stdc++.h>
#include "maze.h"
#include "text_renderer.h"
// #include "game_level.h"

// Game-related State data
typedef long long ll;
bool vis[3*MAZE_SIZE][3*MAZE_SIZE];
int fl = 0;
vector <pair<int, int> > inipos;
void dfs(ll x, ll y, ll sz)
{

	vis[x][y] = true;
	if(x==sz-1&&y==sz-1)
	{
		fl = 1;
		return ;
	}
	int f1,f2,f3,f4;
	f1 = f2 = f3 = f4 = 0;
	while(true)
	{
		int r = (rand())%4;
		if(x==0||vis[x-2][y]==true)
			f1 = 1;
		if(y==0||vis[x][y-2]==true)
			f2 = 1;
		if(x==sz-1||vis[x+2][y]==true)
			f3 = 1;
		if(y==sz-1||vis[x][y+2]==true)
			f4 = 1;
		if(fl)
			return ;
		if(x!=0&&r==0&&vis[x-2][y]==false)
		{
			vis[x-1][y] = true;
			dfs(x-2, y, sz);
			f1 = 1;
		}
		if(y!=0&&r==1&&vis[x][y-2]==false)
		{
			vis[x][y-1] = true;
			dfs(x, y-2, sz);
			f2 = 1;
		}
		if(x!=sz-1&&r==2&&vis[x+2][y]==false)
		{
			vis[x+1][y] = true;
			dfs(x+2, y, sz);
			f3 = 1;
		}
		if(y!=sz-1&&r==3&&vis[x][y+2]==false)
		{
			vis[x][y+1] = true;
			dfs(x, y+2, sz);
			f4 = 1;
		}
		if(f1+f2+f3+f4==4)
			break;
	}
}
void maze()
{
	srand(time(0));
	ll n;
	// cin>>n;
	n = MAZE_SIZE;
	ll sz = 2*n-1;
	// ll ar[sz+2][sz+2];
	for(int i=0;i<sz;i++)
	{
		for(int j=0;j<sz;j++)
		{
			vis[i][j] = false;
		}
	}
	fl = 0;
	dfs(0, 0, sz);
	ofstream Myfile;
	Myfile.open("../source/levels/one.lvl");
	for(int i=0;i<sz;i++)
	{
		string s;
		for(int j=0;j<sz;j++)
		{
			if(vis[i][j]){
				inipos.push_back({i, j});
				s += "0 ";
			}
			else
				s += "1	";
		}
		// line += "\n";
		Myfile << s << endl; 
	}
	Myfile.close();
}


SpriteRenderer  *Renderer;
GameObject      *Player;
GameObject 		*Enemy;
GameObject      *BlueButton;
GameObject 		*RedButton;
GameObject 		*Obstacle[3];
GameObject 		*Coins[5];
GameObject  	*ExitDoor;
TextRenderer      *Text;

int levelWidth, levelHeight;
std::vector<std::vector<unsigned int>> mat;
Game::Game(unsigned int width, unsigned int height) 
    : State(GAME_ACTIVE), Keys(), Width(width), Height(height), Level(0), Lives(3)
{ 

}

Game::~Game()
{
    delete Renderer;
    delete Player;
    delete Enemy;
    delete RedButton;
    delete BlueButton;
    delete ExitDoor;
    delete Text;
}

void Game::Init()
{
    maze();
    ResourceManager::LoadShader("../source/shaders/sprite.vs", "../source/shaders/sprite.frag", nullptr, "sprite");
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), 
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // load textures
    ResourceManager::LoadTexture("../source/textures/au_6.jpg", false, "background");
    ResourceManager::LoadTexture("../source/textures/au_1.png", true, "face");
    ResourceManager::LoadTexture("../source/textures/au_5.png", false, "block");
    ResourceManager::LoadTexture("../source/textures/au_4.png", true, "enemy");
    ResourceManager::LoadTexture("../source/textures/au_7.png", true, "blue");
    ResourceManager::LoadTexture("../source/textures/au_8.png", true, "red");
    ResourceManager::LoadTexture("../source/textures/au_9.png", true, "obstacle");
    ResourceManager::LoadTexture("../source/textures/au_10.png", true, "coin");
    ResourceManager::LoadTexture("../source/textures/au_12.png", true, "door");
    ResourceManager::LoadTexture("../source/textures/au_13.png", true, "leftface");
    ResourceManager::LoadTexture("../source/textures/au_14.png", true, "leftenemy");
    ResourceManager::LoadTexture("../source/textures/player_left_1.png", true, "player_left_1");
    ResourceManager::LoadTexture("../source/textures/player_left_2.png", true, "player_left_2");
    ResourceManager::LoadTexture("../source/textures/player_left_3.png", true, "player_left_3");
    ResourceManager::LoadTexture("../source/textures/player_left_4.png", true, "player_left_4");
    ResourceManager::LoadTexture("../source/textures/player_left_5.png", true, "player_left_5");
    ResourceManager::LoadTexture("../source/textures/player_right_1.png", true, "player_right_1");
    ResourceManager::LoadTexture("../source/textures/player_right_2.png", true, "player_right_2");
    ResourceManager::LoadTexture("../source/textures/player_right_3.png", true, "player_right_3");
    ResourceManager::LoadTexture("../source/textures/player_right_4.png", true, "player_right_4");
    ResourceManager::LoadTexture("../source/textures/player_right_5.png", true, "player_right_5");
    
    Text = new TextRenderer(this->Width, this->Height);
    // cout<<1<<endl;
    Text->Load("../source/fonts/Oswald-Medium.ttf", 24);
    // this->translate = glm::vec3(-0.75f, -0.55f, 0.0f);
    GameLevel one; 
    mat = one.Load("../source/levels/one.lvl", this->Width, this->Height);
    // mat = glm::translate(mat, this->translate);
    this->Levels.push_back(one);
    // cout<<"done"<<endl;
    this->Level = 0;
    unsigned int height = mat.size();
    unsigned int width = mat[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = this->Width / static_cast<float>(width), unit_height = this->Height /static_cast<float> (height); 
    int insize = (inipos.size()-1)/4;
    // cout<<insize<<" ";
    set <int> st;
    int insize1 = rand()%insize ;
    st.insert(insize1);
    float posx = inipos[insize1].second*unit_width;
    float posy = inipos[insize1].first*unit_height ;
    glm::vec2 playerPos = glm::vec2(posx, posy);
    
    levelWidth = this->Width;
    levelHeight = this->Height;

    insize1 = rand()%insize + 2*insize ;
    st.insert(insize1);
    posx = inipos[insize1].second*unit_width + PLAYER_SIZE.x/2;
    posy = inipos[insize1].first*unit_height +PLAYER_SIZE.y/2;
    glm::vec2 BluePos = glm::vec2(posx, posy);


    insize1 = rand()%insize + 1*insize ;
    st.insert(insize1);
    posx = inipos[insize1].second*unit_width + PLAYER_SIZE.x/2;
    posy = inipos[insize1].first*unit_height +PLAYER_SIZE.y/2;
    glm::vec2 RedPos = glm::vec2(posx, posy);
    
    insize1 = rand()%insize + 3*insize ;
    st.insert(insize1);
    posx = inipos[insize1].second*unit_width + PLAYER_SIZE.x/2;
    posy = inipos[insize1].first*unit_height + PLAYER_SIZE.y/2;
    glm::vec2 enemyPos = glm::vec2(posx, posy);


     // + PLAYER_SIZE.x/2;

    // glm::vec2 enemyPos = glm::vec2(PLAYER_SIZE.x/2,PLAYER_SIZE.y/2);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player_right_1"));
    Player->Health = 10;
    Player->TimeLeft = 100;
    Player->Score = 0;
    Player->Task = 0;
    Enemy = new GameObject(enemyPos, PLAYER_SIZE, ResourceManager::GetTexture("enemy"));
    Enemy->Destroyed = false;
    BlueButton = new GameObject(BluePos, PLAYER_SIZE, ResourceManager::GetTexture("blue"));
    BlueButton->Destroyed = false;
    RedButton = new GameObject(RedPos, PLAYER_SIZE, ResourceManager::GetTexture("red"));

    	insize *= 4;
    for(int i=0;i<3;i++)
    {
    	insize1 = rand()%insize;
    	if(st.find(insize1)!=st.end())
    	{
    		i--;
    		continue;
    	}
	    posx = inipos[insize1].second*unit_width + PLAYER_SIZE.x/2;
	    posy = inipos[insize1].first*unit_height + PLAYER_SIZE.y/2;
	    glm::vec2 ObstaclePos = glm::vec2(posx, posy);
    	Obstacle[i] = new GameObject(ObstaclePos, PLAYER_SIZE, ResourceManager::GetTexture("obstacle"));
    	Obstacle[i]->Destroyed = false;
    }
    for(int i=0;i<5;i++)
    {
    	// insize *= 4;
    	insize1 = rand()%insize;
    	if(st.find(insize1)!=st.end())
    	{
    		i--;
    		continue;
    	}
	    posx = inipos[insize1].second*unit_width + PLAYER_SIZE.x/2;
	    posy = inipos[insize1].first*unit_height + PLAYER_SIZE.y/2;
	    glm::vec2 CoinPos = glm::vec2(posx, posy);
    	Coins[i] = new GameObject(CoinPos, PLAYER_SIZE, ResourceManager::GetTexture("coin"));
    	Coins[i]->Destroyed = false;
    }
    insize1 = inipos.size();
    posx = inipos[insize1-1].second*unit_width + PLAYER_SIZE.x/2;
    posy = inipos[insize1-1].first*unit_height + PLAYER_SIZE.y/2;
    glm::vec2 ExitPos = glm::vec2(posx, posy);
    ExitDoor = new GameObject(ExitPos, PLAYER_SIZE, ResourceManager::GetTexture("door"));
    ExitDoor->Destroyed = false;
    lightPos = glm::vec3(Player->Position.x, Player->Position.y, 0.0f);
    lightCutOff = 5000.0f;
    // ResourceManager::GetShader("sprite").SetVector3f("lightColor", lightColor);
    ResourceManager::GetShader("sprite").SetVector3f("lightPos", lightPos);
    ResourceManager::GetShader("sprite").SetFloat("lightCutOff", lightCutOff);
    ResourceManager::GetShader("sprite").SetFloat("ambient", 0.0);

}
int dy1, dx1;
int bfs()
{
	unsigned int height = mat.size();
    unsigned int width = mat[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight /static_cast<float> (height); 

	int sy1 = (Player->Position.x)/unit_width;
	int sx1 = (Player->Position.y)/unit_height;
	dy1 = (Enemy->Position.x)/unit_width;
	dx1 = (Enemy->Position.y)/unit_height;
	// cout<<sx1<<" "<<sy1<<endl;
	int dis[height][width];
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			dis[i][j] = -1;
		}
	}
	dis[sx1][sy1] = 0;
	queue <pair<int, int> > q;
	q.push({sx1, sy1});
	while(!q.empty())
	{
		auto j = q.front();
		q.pop();
		if(j.first!=0&&dis[j.first-1][j.second]==-1&&mat[j.first-1][j.second]==0)
		{
			dis[j.first-1][j.second] = dis[j.first][j.second]+1;
			q.push({j.first-1, j.second});
		}
		if(j.second!=0&&dis[j.first][j.second-1]==-1&&mat[j.first][j.second-1]==0)
		{
			dis[j.first][j.second-1] = dis[j.first][j.second]+1;
			q.push({j.first, j.second-1});
		}
		if(j.first!=height-1&&dis[j.first+1][j.second]==-1&&mat[j.first+1][j.second]==0)
		{
			dis[j.first+1][j.second] = dis[j.first][j.second]+1;
			q.push({j.first+1, j.second});
		}
		if(j.second!=width-1&&dis[j.first][j.second+1]==-1&&mat[j.first][j.second+1]==0)
		{
			dis[j.first][j.second+1] = dis[j.first][j.second]+1;
			q.push({j.first, j.second+1});
		}
	}
	int ans = 0, mn = 100000;
	int v1 = dx1 - 1;
	if(dx1!=0&&dis[dx1-1][dy1]<mn&&mat[dx1-1][dy1]!=1&&dis[dx1-1][dy1]!=-1){		
		mn = dis[dx1-1][dy1];
		ans = 1;
	}
	if(dy1!=0&&dis[dx1][dy1-1]<mn&&mat[dx1][dy1-1]!=1&&dis[dx1][dy1-1]!=-1){
		mn = dis[dx1][dy1-1];
		ans = 2;
	}
	if(dx1!=height-1&&dis[dx1+1][dy1]<mn&&mat[dx1+1][dy1]!=1&&dis[dx1+1][dy1]!=-1){
		mn = dis[dx1+1][dy1];
		ans = 3;
	}
	if(dy1!=width-1&&dis[dx1][dy1+1]<mn&&mat[dx1][dy1+1]!=1&&dis[dx1][dy1+1]!=-1){
		mn = dis[dx1][dy1+1];
		ans = 4;
	}
	if(ans==1)
		dx1--;
	if(ans==2)
		dy1--;
	if(ans==3)
		dx1++;
	if(ans==4)
		dy1++;
	return ans;
}
	int dir=6;
bool CheckCollision(GameObject &one, GameObject &two);	
void Game::Update(float dt)
{
    float velocity = PLAYER_VELOCITY * dt;
	unsigned int height = mat.size();
    unsigned int width = mat[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight /static_cast<float> (height); 
	// light_pressed = false;
	if(!light)
    {
        // lightCutOff = y_offset*1.25;
        lightCutOff = unit_height*1.25;
        // this->score += 0.1;
    }
    else
        lightCutOff = 5000.0f;

    ResourceManager::GetShader("sprite").SetFloat("lightCutOff", lightCutOff);
    lightPos = glm::vec3(Player->Position.x, Player->Position.y, 0.0f);
    ResourceManager::GetShader("sprite").SetVector3f("lightPos", lightPos);

	if(dir==6&&Enemy->Destroyed==false&&this->State==GAME_ACTIVE)
	dir = bfs();
	int position1 = 0;
    position1 = (int)Enemy->Position.x;
    position1 %= 5;

    if(dir==1)
    {
		// Enemy->Position.y -= velocity;
		if (Enemy->Position.y >= 0.0f){
	        Enemy->Position.y -= velocity;
	        for (GameObject &box : this->Levels[this->Level].Bricks)
		    {
	            if(CheckCollision(*Enemy, box))
	                Enemy->Position.y += velocity; 
		    }
	    }
	    if(Enemy->Position.y-PLAYER_SIZE.y/2<=(dx1-3/4)*unit_height)
	    	dir = 6;
	    // cout<<"1"<<endl;;
	}
	if(dir==2)
	{
		if (Enemy->Position.x >= 0.0f){
			Enemy->Position.x -= velocity;
	        // Enemy->Position.x -= velocity;
	        for (GameObject &box : this->Levels[this->Level].Bricks)
		    {
	            if(CheckCollision(*Enemy, box))
	                Enemy->Position.x += velocity; 
		    }
	    }
	    if(Enemy->Position.x-PLAYER_SIZE.x/2<=(dy1-1/2)*unit_width)
	    	dir = 6;
	    // cout<<"2"<<endl;;
        // Enemy->Sprite = ResourceManager::GetTexture("enemy_left_"+std::to_string(position1));
        Enemy->Sprite = ResourceManager::GetTexture("leftenemy");
	}
	if(dir==3)
	{
		// Enemy->Position.y += velocity;
		if (Enemy->Position.y <= this->Height - Player->Size.y){
	        Enemy->Position.y += velocity;
	        for (GameObject &box : this->Levels[this->Level].Bricks)
		    {
	            if(CheckCollision(*Enemy, box))
	                Enemy->Position.y -= velocity; 
		    }
	    }
	    if(Enemy->Position.y+PLAYER_SIZE.y>=(dx1)*unit_height)
	    	dir = 6;
	    // cout<<"3"<<endl;

	}
	if(dir==4)
	{
		// Enemy->Position.x += velocity;
		if (Enemy->Position.x <= this->Width - Player->Size.x){
	        Enemy->Position.x += velocity;
	        for (GameObject &box : this->Levels[this->Level].Bricks)
		    {
	            if(CheckCollision(*Enemy, box))
	                Enemy->Position.x -= velocity; 
		    }
	    }
	    // Enemy->Sprite = ResourceManager::GetTexture("enemy_right_"+std::to_string(position1));
	    // cout<<"4"<<endl;
	    Enemy->Sprite = ResourceManager::GetTexture("enemy");
	    if(Enemy->Position.x>=dy1*unit_width)
	    	dir = 6;
	}
	if(dir==5)
	{
		if (Enemy->Position.y >= 0.0f){
	        Enemy->Position.y -= velocity;
	        for (GameObject &box : this->Levels[this->Level].Bricks)
		    {
	            if(CheckCollision(*Enemy, box))
	                Enemy->Position.y += velocity; 
		    }
	    }
	    if (Enemy->Position.x >= 0.0f){
			Enemy->Position.x -= velocity;
	        // Enemy->Position.x -= velocity;
	        for (GameObject &box : this->Levels[this->Level].Bricks)
		    {
	            if(CheckCollision(*Enemy, box))
	                Enemy->Position.x += velocity; 
		    }
	    }
     // check for collisions
	}
	if(this->State == GAME_ACTIVE)
	{
		if(!light)
        Player->Score += 0.008;
    	Player->TimeLeft -= 0.02;
		if(Player->TimeLeft<=0.5)
		{
			this->State = GAME_LOST;
		}

		if(abs(Enemy->Position.x - Player->Position.x) < unit_width && abs(Enemy->Position.y- Player->Position.y)<unit_height&&Enemy->Destroyed==false)
		{
			Player->Health-=0.02;
			if(Player->Health <= 0.5)
			{
				this->State = GAME_LOST;
			}
			// cout<<Player->Health<<endl;;
		}
		if(Enemy->Destroyed==false&&CheckCollision(*Player, *RedButton))
		{
			Player->Task++;
			Enemy->Destroyed = true;
			// cout<<Player->Task<<endl;
		}
		if(BlueButton->Destroyed==false&&CheckCollision(*Player, *BlueButton))
		{	
			Player->Task++;
			BlueButton->Destroyed = true;
			// cout<<Player->Task<<endl;
		}
		if(Player->Task==2)
		{
			// cout<<Player->Task<<endl;

			ExitDoor->Destroyed = true;
		}
		if(BlueButton->Destroyed==true)
		{
			for(int i=0;i<3;i++)
			{
				if(Obstacle[i]->Destroyed==false)
				{
					if(CheckCollision(*Player, *Obstacle[i]))
					{
						Player->Score-=1;
						// cout<<Player->Score<<endl;;
						Obstacle[i]->Destroyed = true;
					}
				}
			}
			for(int i=0;i<5;i++)
			{
				if(Coins[i]->Destroyed==false)
				{
					if(CheckCollision(*Player, *Coins[i]))
					{
						Player->Score+=1;
						// cout<<Player->Score<<endl;;
						Coins[i]->Destroyed = true;
					}
				}
			}
		}
		if(ExitDoor->Destroyed==true&&CheckCollision(*Player, *ExitDoor))
		{
			this->State = GAME_WIN;
			// cout<<"Win!!"<<endl;
			// exit(0);
		}
	}
}

void Game::ProcessInput(float dt)
{
	if (this->State == GAME_MENU)
    {
        if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
        {
            this->State = GAME_ACTIVE;
            this->KeysProcessed[GLFW_KEY_ENTER] = true;
        }
        if (this->Keys[GLFW_KEY_W] && !this->KeysProcessed[GLFW_KEY_W])
        {
            this->Level = (this->Level + 1) % 4;
            this->KeysProcessed[GLFW_KEY_W] = true;
        }
        if (this->Keys[GLFW_KEY_S] && !this->KeysProcessed[GLFW_KEY_S])
        {
            if (this->Level > 0)
                --this->Level;
            else
                this->Level = 3;
            //this->Level = (this->Level - 1) % 4;
            this->KeysProcessed[GLFW_KEY_S] = true;
        }
    }
    if (this->State == GAME_WIN)
    {
        if (this->Keys[GLFW_KEY_ENTER])
        {
            this->KeysProcessed[GLFW_KEY_ENTER] = true;
            // Effects->Chaos = false;
            this->State = GAME_MENU;
        }
    }
    int position = 0;
    position = (int)Player->Position.x;
    position %= 5;
    position++;
    if (this->State == GAME_ACTIVE)
    {
        float velocity = PLAYER_VELOCITY * dt;
        // move playerboard
        if (this->Keys[GLFW_KEY_A])
        {
            if (Player->Position.x >= 0.0f){
                Player->Position.x -= velocity;
                for (GameObject &box : this->Levels[this->Level].Bricks)
			    {
	                if(CheckCollision(*Player, box))
	                    Player->Position.x += velocity; 
			    }
            }
            Player->Sprite = ResourceManager::GetTexture("player_left_"+std::to_string(position));
        }
        if (this->Keys[GLFW_KEY_D])
        {
            if (Player->Position.x <= this->Width - Player->Size.x){
                Player->Position.x += velocity;
                for (GameObject &box : this->Levels[this->Level].Bricks)
			    {
		            if(CheckCollision(*Player, box))
		                Player->Position.x -= velocity; 
			    }
            }

            Player->Sprite = ResourceManager::GetTexture("player_right_"+std::to_string(position));
        }
        if (this->Keys[GLFW_KEY_S])
        {
            if (Player->Position.y <= this->Height - Player->Size.y){
                Player->Position.y += velocity;
                for (GameObject &box : this->Levels[this->Level].Bricks)
			    {
			        // if (!box.Destroyed)
			        // {
		                if(CheckCollision(*Player, box))

		                // if (Player->Stuck)
		                    Player->Position.y -= velocity; 
			    }
            }

        }
        if (this->Keys[GLFW_KEY_W])
        {
            if (Player->Position.y >= 0.0f){
                Player->Position.y -= velocity;
                for (GameObject &box : this->Levels[this->Level].Bricks)
			    {
		            if(CheckCollision(*Player, box))
		                Player->Position.y += velocity; 
			    }
            }
        }
        if (this->Keys[GLFW_KEY_L]&&light_pressed==false)
        {
            light = 1-light;
            light_pressed = true;
        }
    }
}

void Game::Render()
{
        std::stringstream shealth, sscore, stime, stask;
        string slight; 
        shealth << std::fixed << std::setprecision(0) << Player->Health;
        sscore << std::fixed << std::setprecision(0) << Player->Score;
        stime << std::fixed << std::setprecision(0) << Player->TimeLeft;
        stask << Player->Task;
        if(light)
        	slight = "ON";
    	else
    		slight = "OFF";
    if(this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN || this->State == GAME_LOST)
    {
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
        // draw player
        Player->Draw(*Renderer);
        // Text->RenderText("Health", 5.0f, 5.0f, 2.0f, glm::vec3(1.0f, 0.5f, 0.0f));
        Text->RenderText("Health: " + shealth.str() + "         Score: " + sscore.str() + "         Tasks Completed: " + stask.str() + "         Light: " + slight + "         TimeLeft: " + stime.str(), 5.0f, 5.0f, 2.0f, glm::vec3(1.0f, 0.5f, 0.0f));
        if(Enemy->Destroyed==false)
        Enemy->Draw(*Renderer);
        BlueButton->Draw(*Renderer);
        RedButton->Draw(*Renderer);
        if(BlueButton->Destroyed==true)
        {
        	for(int i=0;i<3;i++)
        		if(Obstacle[i]->Destroyed==false)
        			Obstacle[i]->Draw(*Renderer);
        	for(int i=0;i<5;i++)
        		if(Coins[i]->Destroyed==false)
        			Coins[i]->Draw(*Renderer);
        }
        if(ExitDoor->Destroyed==true)
        {
        	ExitDoor->Draw(*Renderer);
        }
    }
    if (this->State == GAME_WIN)
    {
        Text->RenderText("You WON!!!", this->Width/ 2.0f - 420.0f, this->Height / 2.0f - 100.0f, 3.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        Text->RenderText("Press ESC to quit", this->Width/ 2.0f - 320.0f, this->Height / 2.0f + 0.0f, 3.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
    if(this->State == GAME_LOST)
    {
    	Text->RenderText("You LOST!!!", this->Width/ 2.0f - 220.0f, this->Height / 2.0f - 60.0f, 3.0f, glm::vec3(1.0f, 0.0f, 0.0f));
    	Text->RenderText("Press ESC to quit", this->Width/ 2.0f - 320.0f, this->Height / 2.0f + 40.0f, 3.0f, glm::vec3(1.0f, 1.0f, 0.0f));
    }
}

void Game::ResetLevel()
{
    if (this->Level == 0)
        this->Levels[0].Load("levels/one.lvl", this->Width, this->Height / 2);
    this->Lives = 3;
}

void Game::ResetPlayer()
{
    // reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    
}

Direction VectorDirection(glm::vec2 closest);


bool CheckCollision(GameObject &one, GameObject &two) // AABB - AABB collision
{
    // collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}
Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}