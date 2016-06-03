#include "TaskSystemEx.h"

// 處理鍵盤事件
void TaskEx::KeyMain(void* arg){//KEYEVENT* kevent){

}

// 處理serial port事件
void TaskEx::SerialMain(void* arg){//SERIALEVENT* sevent){

}

// 處理Network事件
void TaskEx::NetworkMain(void* arg){//NETWORKEVENT* nevent){

}

// 初始化TASK LIST後執行指定的函式
void TaskEx::InitTaskList(void)//TASKINITFUNCTION taskInitFunction)
{
	Task::InitTaskList();

	//taskInitFunction();

}

// 刪除特定的TASK(自己除外),以id指定
void TaskEx::Delete(int id)
{
	TaskEx *task, *next;
	for (task = (TaskEx*)this->m_next; task != this; task = next)
	{
		if (task->m_id == id)
		{
			delete task;
		}
		next = (TaskEx*)task->m_next;
	}
}

// 執行所有TASK的SerialMain函式
void TaskEx::SerialEventTask(void* arg){//SERIALEVENT* sevent){
	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		task->SerialMain(arg);//sevent);
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}
}

// 執行所有TASK的NetworkMain函式
void TaskEx::NetWorkEventTask(void* arg){//NETWORKEVENT* nevent){
	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		task->NetworkMain(arg);//nevent);
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}
}

// 執行所有TASK的KeyMain函式
void TaskEx::KeyEventTask(void* arg){//KEYEVENT* kevent){
	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		task->KeyMain(arg);//kevent);
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}
	//kevent->_reset();
}

// 執行所有TASK的Draw函式
void TaskEx::DrawTask()
{
	//if(driver==NULL) return;

	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		task->Draw();
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}
}

// 執行特定TASK的Draw函式,以id指定
void TaskEx::DrawTask(int id)
{
	//if(driver==NULL) return;

	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		if (task->m_id == id) task->Draw();
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}
}

// 取得特定TASK的總數,以id指定
DWORD TaskEx::GetCount(int id)
{
	DWORD count = 0;

	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		if (task->m_id == id) count++;
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}

	return count;
}

// 取得特定TASK的位址,以id指定
// 如果記憶體中存在2個以上,number指定為0代表第一個,1代表第二個,以此類推
void* TaskEx::GetTask(int id, DWORD number)
{
	DWORD count = 0;

	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		if (task->m_id == id && count++ == number) return task;
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}

	return NULL;
}

// 取得自己的Data
void TaskEx::GetData(DATA *pData)
{
	if (pData == NULL) return;

	pData->id = m_id;
	pData->cx = m_cx;
	pData->cy = m_cy;
	pData->hit_cw = m_hit_cw;
	pData->hit_ch = m_hit_ch;
	pData->speed = m_speed;
	pData->life = m_life;
	pData->max_life = m_max_life;
	pData->rot = m_rot;
	pData->alpha = m_alpha;
}

// 建構子
TaskEx::TaskEx(void)
{
	m_id = 0;
	m_cx = 0; m_cy = 0;
	m_hit_cw = 0; m_hit_ch = 0;
	m_speed = 0;
	m_life = 0; m_max_life = 0;
	//m_pTexture=NULL;
	m_rot = 0;
	m_alpha = 0xff;
}
