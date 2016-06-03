/**
 * @file     TaskSystem.h
 * @brief    Manage Memory System.
 */
#ifndef _TASKSYSTEM_H_
#define _TASKSYSTEM_H_

#include<stdio.h>
#include<malloc.h>		        // for malloc, free
#include<string.h>		        // for memset, memmove

typedef unsigned char BYTE;
typedef unsigned long DWORD;

#define TRUE  1
#define FALSE 0

/**
 * @brief Base Task Object.
 */
class Task
{
	BYTE m_use;/**< TRUE using / FALSE not use */
	DWORD m_size;/**< count of byte */
	float m_priority;/**< priority */

	/**
	 * @brief Defrag TaskSystem's memory.
	 */
	static void Defrag(void);

protected:
	static BYTE* m_active;/**< Pointer to first task in TaskSystem */
	static BYTE* m_free;/**< Pointer to begin address of free memory */
	Task* m_pre;/**< Pointer to previous task */
	Task* m_next;/**< Pointer to next task */

public:
	/**
	 * @brief virtual deconstructor.
	 */
	virtual ~Task(void){}

	/**
	 * @brief Initial TaskSystem's task list.
	 */
	static void InitTaskList(void);

	/**
	 * @brief Release TaskSystem's task list.
	 */
	static void ReleaseTaskList(void);

	/**
	 * @brief Delete all other task in task list.
	 */
	void Delete(void);

	/**
	 * @brief Run TaskSystem.
	 *
	 * @param elapsedTime Elapsed Time of each frame
	 */
	static void RunTask(double elapsedTime);

	/**
	 * @brief Overload 'new' operator.
	 *
	 * @param priority Default Priority
	 */
	void* operator new(size_t size, float priority = 0.5f);

	/**
	 * @brief Overload 'delete' operator.
	 *
	 * @param pTask Task's address
	 */
	void operator delete(void *pTask);

	/**
	 * @brief Set Task's Priority.
	 *
	 * @param priority New Priority
	 */

	void SetPriority(float priority);

	/**
	 * @brief Get TaskSystem's size.
	 *
	 */
	static DWORD GetSize(void);

	/**
	 * @brief Get count of tasks in TaskSystem.
	 *
	 */
	static DWORD GetCount(void);

	/**
	 * @brief Dump TaskSystem's content.
	 *
	 * @filename File Name
	 */
	static void Dump(const char *filename);

	/**
	 * @brief Main Process Function.
	 *
	 * @elapsedTime Elapsed Time of each frame
	 */
	virtual int Main(double elapsedTime) = 0;
};


#endif
