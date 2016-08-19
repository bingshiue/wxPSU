/**
 * @brief UserCancelISPPostDelay.cpp
 */

#include "Task.h"

UserCancelISPPostDelay::UserCancelISPPostDelay(){
	this->m_id = task_ID_UserCancelISPPostDelay;

	this->m_elapsedTimer = 0.0f;
}

UserCancelISPPostDelay::~UserCancelISPPostDelay(void){

}

void UserCancelISPPostDelay::Draw(void){
	// Do Nothing
}

int UserCancelISPPostDelay::Main(double elapsedTime){

	this->m_elapsedTimer += elapsedTime;

	//PSU_DEBUG_PRINT(MSG_DEBUG ,"m_elapsedTimer = %.0f", this->m_elapsedTimer);

	if (this->m_elapsedTimer >= UserCancelISP_POST_DELAY_TIME){
		// If Time up 
		delete this;
	}

	return 0;
}