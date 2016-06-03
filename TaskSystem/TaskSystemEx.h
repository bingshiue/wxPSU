/**
* @file     TaskSystemEx.h
* @brief    Sequence Control System.
*/
#ifndef _TASKSYSTEMEX_H_
#define _TASKSYSTEMEX_H_

#include <iostream>
using namespace std;
#include "TaskSystem.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * Type of TaskSystem initial function.
 */
typedef void(*TASKINITFUNCTION)(void);

/**
 * @brief Additional Task Data.
 *
 */
struct DATA
{
	int id;
	float cx, cy;
	float hit_cw, hit_ch;
	float speed;
	DWORD life, max_life;
	float rot;
	BYTE alpha;
};

/**
 * @brief TaskEx Object.
 *
 */
class TaskEx : public Task
{
protected:
	int m_id;/**< ID of Task */
	float m_cx, m_cy;/**< x,y position of Task */
	float m_hit_cw, m_hit_ch;/**< hit cw,ch of Task */
	float m_speed;/**< Speed of Task */
	DWORD m_life, m_max_life;/**< Life of Task */
	float m_rot;/**< Rot of Task */
	BYTE  m_alpha;/**< Alpha Value of Task */
public:
	/**
	 * @brief Constructor.
	 *
	 */
	TaskEx(void);

	/**
	 * @brief Initialize Task System.
	 *
	 * @taskInitFunction Function that run after TaskSystem initialization completed
	 */
	static void InitTaskList(void);//TASKINITFUNCTION taskInitFunction);

	/**
	 * @brief Delete Task(with specified id).
	 *
	 * @id Specified ID
	 */
	void Delete(int id);

	/**
	* @brief Process Key Board Event.
	*
	* @kevent Key Board Event
	* @author SHIE-BINGSHIUE
	* @date 2010-08-05
	*/
	static void KeyEventTask(void* arg);//KEYEVENT* kevent);

	/**
	 * @brief Process Serial Port Event.
	 *
	 * @sevent Serial Port Event
	 */
	static void SerialEventTask(void* arg);//SERIALEVENT* sevent);

	/**
	 * @brief Process Network Event.
	 *
	 * @param nevent Network Event
	 */
	static void NetWorkEventTask(void* arg);//NETWORKEVENT* nevent);

	/**
	 * @brief Draw all task in TaskSystem.
	 *
	 */
	static void DrawTask(void);

	/**
	 * @brief Draw task(with specified id) in TaskSystem .
	 *
	 * @param id Specified ID
	 */
	static void DrawTask(int id);

	/**
	 * @brief Get Task's(with specified id) count.
	 *
	 * @param id Specified ID
	 */
	static DWORD GetCount(int id);

	/**
	 * @brief Get Task's(with specified id) address.
	 *
	 * @param id Specified ID
	 * @param number Number of Task
	 * @retval Task's(with specified id) address
	 */
	static void* GetTask(int id, DWORD number);

	/**
	 * @brief Get Task's additional data.
	 *
	 * @param pData pointer of additional data
	 */
	void GetData(DATA *pData);

	/**
	 * @brief Task's Key Board event process function.
	 *
	 * @param kevent Key Board event
	 */
	virtual void KeyMain(void* arg);//KEYEVENT* kevent);

	/**
	 * @brief Task's Serial port event process function.
	 *
	 * @param sevent Serial port event
	 */
	virtual void SerialMain(void* arg);//SERIALEVENT* sevent);

	/**
	 * @brief Task's Network event process function.
	 *
	 * @param nevent Network event
	 */
	virtual void NetworkMain(void* arg);//NETWORKEVENT* nevent);

	/**
	 * @brief Task's draw function.
	 *
	 */
	virtual void Draw(void) = 0;
};

#endif
