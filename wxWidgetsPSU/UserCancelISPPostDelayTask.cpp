/**
 * @brief UserCancelISPPostDelayTask.cpp
 */

#include "Task.h"

UserCancelISPPostDelayTask::UserCancelISPPostDelayTask(){
	this->m_id = task_ID_UserCancelISPPostDelayTask;

	this->m_elapsedTimer = 0.0f;
}

UserCancelISPPostDelayTask::~UserCancelISPPostDelayTask(void){

}

void UserCancelISPPostDelayTask::Draw(void){
	// Do Nothing
}

int UserCancelISPPostDelayTask::Main(double elapsedTime){

	this->m_elapsedTimer += elapsedTime;

	//PSU_DEBUG_PRINT(MSG_DEBUG ,"m_elapsedTimer = %.0f", this->m_elapsedTimer);

	if (this->m_elapsedTimer >= UserCancelISP_POST_DELAY_TIME){
		// If Time up 
		delete this;
	}

	return 0;
}