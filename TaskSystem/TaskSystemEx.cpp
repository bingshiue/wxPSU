#include "TaskSystemEx.h"

// �B�z��L�ƥ�
void TaskEx::KeyMain(void* arg){//KEYEVENT* kevent){

}

// �B�zserial port�ƥ�
void TaskEx::SerialMain(void* arg){//SERIALEVENT* sevent){

}

// �B�zNetwork�ƥ�
void TaskEx::NetworkMain(void* arg){//NETWORKEVENT* nevent){

}

// ��l��TASK LIST�������w���禡
void TaskEx::InitTaskList(void)//TASKINITFUNCTION taskInitFunction)
{
	Task::InitTaskList();

	//taskInitFunction();

}

// �R���S�w��TASK(�ۤv���~),�Hid���w
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

// ����Ҧ�TASK��SerialMain�禡
void TaskEx::SerialEventTask(void* arg){//SERIALEVENT* sevent){
	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		task->SerialMain(arg);//sevent);
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}
}

// ����Ҧ�TASK��NetworkMain�禡
void TaskEx::NetWorkEventTask(void* arg){//NETWORKEVENT* nevent){
	TaskEx *task, *next;
	for (task = (TaskEx*)m_active; m_active; task = next)
	{
		task->NetworkMain(arg);//nevent);
		next = (TaskEx*)task->m_next;
		if (next == (TaskEx*)m_active) break;
	}
}

// ����Ҧ�TASK��KeyMain�禡
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

// ����Ҧ�TASK��Draw�禡
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

// ����S�wTASK��Draw�禡,�Hid���w
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

// ���o�S�wTASK���`��,�Hid���w
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

// ���o�S�wTASK����},�Hid���w
// �p�G�O���餤�s�b2�ӥH�W,number���w��0�N��Ĥ@��,1�N��ĤG��,�H������
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

// ���o�ۤv��Data
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

// �غc�l
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
