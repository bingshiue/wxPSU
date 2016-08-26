/**
* @brief UserCancelISPTask.cpp
*/

#include "Task.h"

UserCancelISPTask::UserCancelISPTask(unsigned char* ispStatus){
	this->m_id = task_ID_UserCancelISPTask;

	this->m_elapsedTimer = 0.0f;

	this->m_ispStatus = ispStatus;
}

UserCancelISPTask::~UserCancelISPTask(void){

}

void UserCancelISPTask::Draw(void){
	// Do Nothing
}

int UserCancelISPTask::Main(double elapsedTime){

	this->m_elapsedTimer += elapsedTime;

	PSU_DEBUG_PRINT(MSG_DEBUG ,"m_elapsedTimer = %.0f", this->m_elapsedTimer);

	*this->m_ispStatus = ISP_Status_UserRequestCancel;

	delete this;

	return 0;
}