

#include "Level.h"
#include "Ground.h"
#include "Brick.h"
#include "GameObject.h"
#include "Pipe.h"

CLevel:: CLevel(int level_id, int time_limit)
{
	this->level_id = level_id;
	this->time_limit = time_limit;
	this->isCompleted = false; 

	this->Map_Height = 0;
	this->Map_Width = 0;
}

CLevel:: ~CLevel()
{
	UnLoadLevel();
}

void CLevel::Update(DWORD dt)
{     // Tải đối tượng lên 
	for (size_t i = 0; i < Objects.size(); i++)
	{
		//Này để kiểm xem đối tượng đã bị tiêu diệt chưa
		// Nếu đã bị tiêu diệt aka isDeleted = true, không update
		if (Objects[i]->IsDeleted == false)
		{
			Objects[i]->Update(dt, &Objects); 
		}

	}
}

void CLevel::Render()
{
	// Đưa đối tượng lên màn hình 
	for (size_t i = 0; i < Objects.size(); i++)
	{  //Này để kiểm xem đối tượng đã bị tiêu diệt chưa
		// Nếu đã bị tiêu diệt aka isDeleted = true, không render
		if (Objects[i]->IsDeleted == false)
		{
			Objects[i]->Render();
		}
		
	}
}

void CLevel::UnLoadLevel()
// trả tài nguyên 
{
	for (size_t i = 0; i < Objects.size(); i++)
	{
		delete Objects[i];

	}
	Objects.clear(); 
}

void CLevel::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); )
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;               // Xóa khỏi RAM
			it = objects.erase(it); // Xóa khỏi danh sách vector
		}
		else
		{
			it++;
		}
	}
}

