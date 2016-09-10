#include "TaskSystem.h"

#define MEM_SIZE  1024*1024	/**< 所要申請的記憶體BYTE數 */
#define DFRG_SIZE  1024*100	/**< 未使用記憶體若小於這個這個數就執行記憶體重組 */

static BYTE *g_buf = NULL;	/**< 指向所申請記憶體開頭的指標 */

BYTE* Task::m_active = NULL;	/**< 指向第一個被執行的TASK的指標 */
BYTE* Task::m_free = NULL;	/**< 指向未使用記憶體開頭的指標(從這裡開始追加新的TASK) */

static DWORD g_size = 0;		/**< 表示目前所有TASK所使用的記憶體總數 */
static DWORD g_count = 0;		/**< 表示目前所有執行中的TASK數目 */

//wxCriticalSection Task::m_critsect;
static wxCriticalSection g_critsect;

// 初始化TASK LIST(雙向LIST,LIST中的每一個元素為一個TASK)
void Task::InitTaskList(void)
{	
	ReleaseTaskList();// 先做釋放的動作以防LIST已經初始化過

	g_buf = (BYTE*)malloc(MEM_SIZE);// 申請記憶體空間
	memset(g_buf, 0, MEM_SIZE);// 重置記憶體空間,將每一個BYTE設為零

	m_active = NULL;// 讓m_active指向NULL
	m_free = g_buf;// 讓m_free指向所申請記憶體開頭位址

	g_size = 0;// TASK所使用的記憶體總數設為零
	g_count = 0;// 所有執行中的TASK數目設為零
}

// 釋放TASK LIST空間
void Task::ReleaseTaskList(void)
{
	if (g_buf == NULL) return;// 尚未執行初始化,別做以下的動作
	//依序將LIST中所有的TASK刪除
	for (Task *task = (Task*)m_active; m_active; task = (Task*)m_active)
	{
		delete task;
	}

	m_free = NULL;// 將m_free重設為NULL

	free(g_buf);// 釋放所申請記憶體空間
	g_buf = NULL;// 將g_buf重設為NULL
}

// 刪除自己以外的所有其他TASK
void Task::Delete(void)
{
	for (Task *task = this->m_next; task != this; task = task->m_next)
	{
		delete task;
	}
}

// 執行所有的TASK中的Main函式,傳入每一畫格的時間差
void Task::RunTask(double elapsedTime)
{
	//wxCriticalSectionLocker locker(g_critsect);

	if (g_buf == NULL) return;	// 若還未執行過初始化動作,別做以下的動作

	Task *task, *next;
	//執行所有的TASK中的Main函式

	for (task = (Task*)m_active; m_active; task = next)
	{
		task->Main(elapsedTime);// 呼叫每一個TASK的Main函式
		next = task->m_next;// 指向下一個TASK
		if (next == (Task*)m_active) break;//表示已經找了一輪,中斷for迴圈
	}


	if (g_buf + MEM_SIZE - m_free < DFRG_SIZE) Defrag();// 重新整理記憶體空間

}

// 重新整理記憶體空間
void Task::Defrag(void)
{
	if (m_active == NULL)// 沒有任何執行中的TASK
	{
		m_free = g_buf;// 將m_free重新指向所申請記憶體空間的開頭
		memset(g_buf, 0, MEM_SIZE);// 重置記憶體空間
		return;
	}

	BYTE *dest = g_buf;// 等一下要開始清除的開頭位址

	Task *task;// 儲存第一個使用中的TASK位址
	DWORD size;// 所移動的BYTE數

	task = (Task*)m_active;
	if (task->m_next == task)// LIST中目前只有一個TASK的情形下
	{
		size = task->m_size;// 所要移動的BYTE數

		memmove(g_buf, m_active, size);// 移動TASK至記憶體開頭處

		task = (Task*)g_buf;// 將目前這一個TASK的開頭指標設為所申請記憶體開頭
		task->m_pre = task;// 將前一個TASK設為自己
		task->m_next = task;// 將下一個TASK設為自己

		m_active = g_buf;// 將目前第一個執行中的TASK開頭位址設為所申請記憶體開頭
		dest += size;// 設定等一下要執行清除動作的開頭位址
	}
	else// LIST中目前有多個TASK的情形下
	{
		//從所申請的記憶體空間開頭開始依序移動每一個TASK
		for (BYTE *source = g_buf; source<m_free; source += size)// g_buf必為第一個TASK的位址,所以開始時可以直接設給source
		{
			task = (Task*)source;// 取得TASK位址
			size = task->m_size;// 取得TASK的大小
			if (task->m_use == FALSE) continue;// 若此TASK已經標記為未使用,continue

			memmove(dest, source, size);// 移動TASK

			task = (Task*)dest;// 從dest取得目前這個TASK的位址
			// 更新相鄰TASK的m_next,m_pre的值
			task->m_pre->m_next = task;
			task->m_next->m_pre = task;
			// 是LIST中的第一個TASK嗎(必定是for迴圈執行第一次時)?如果是的話要重新指定m_active的值,這時dest = g_buf = 所申請的記憶體空間開頭位址
			if (source == m_active) m_active = dest;

			dest += size;// 移動dest的位址
		}
	}

	memset(dest, 0, m_free - dest);// 重置記憶體為零

	m_free = dest;// 執行結束時dest就是指向free記憶體空間的開頭位址,所以將m_free設為dest
}

// TASK生成,超載 delete 運算子
void Task::operator delete(void *pTask)
{	
	wxCriticalSectionLocker locker(g_critsect);
	
	if (pTask == NULL) return; // 檢查是否為空指標
	Task *task = (Task*)pTask;// 取得位址

	if (task->m_use == FALSE) return; // 防止重複刪除
	task->m_use = FALSE;// 設定為非使用

	g_size -= task->m_size;// 計算 g_size
	g_count--;// 計算 g_count

	if (task == (Task*)m_active)// 是第一個被執行的TASK嗎?
	{
		if (task->m_next == (Task*)m_active)// 是最後一個被執行的TASK嗎?是的話代表TASK中只有一個TASK
		{
			m_active = NULL;// 因為刪除之後就沒有任何的TASK,所以要將m_active設為NULL
			return;
		}
		else m_active = (BYTE*)task->m_next;//將第一個被執行的TASK設定為被刪除的下一個
	}

	// 更新相鄰TASK的m_next,m_pre的值
	task->m_pre->m_next = task->m_next;
	task->m_next->m_pre = task->m_pre;

}

// TASK生成,超載 new 運算子
// 優先權越小會放在越前面,會先被執行
void* Task::operator new(size_t size, float priority)
{
	wxCriticalSectionLocker locker(g_critsect);
	
	if (g_buf == NULL) return NULL;// 若還未執行過初始化動作,別做以下的動作
	if (m_free + size >= g_buf + MEM_SIZE) return NULL;// 記憶體容量不足

	g_size += (DWORD)size;// 累加g_size
	g_count++;// 累加g_count

	Task *new_task = (Task*)m_free;// 取得未使用記憶體空間的開頭位址
	m_free += size;// 重設未使用記憶體空間的開頭位址

	if (m_active == NULL)// 如果現在LIST中沒有任何TASK
	{
		m_active = (BYTE*)new_task; // 那欲生成的TASK,就會成為第一個被執行的TASK

		new_task->m_use = TRUE;// 設定為使用中
		new_task->m_size = (DWORD)size;// 設定TASK佔用BYTE數的大小
		// 更新相鄰TASK的m_next,m_pre的值
		new_task->m_pre = new_task;
		new_task->m_next = new_task;
		new_task->m_priority = priority;// 設定優先權

		return new_task;// 返回生成TASK的開頭位址,除非有必要得知這個位址,不然可以不理會這一個回傳值
	}

	// LIST中存在其他TASK

	Task *task, *next;// 暫存用
	//從LIST的開始比較優先權
	for (task = (Task*)m_active;; task = next)
	{
		next = task->m_next;// 取得下一個TASK的位址

		if (priority < task->m_priority)		// 設定的優先權小於目前TASK的優先權
		{                                   // 將欲生成的TASK插入在目前TASK的前面,注意這僅僅更新TASK的 m_pre,m_next的值,並不實際移動TASK
			if (task == (Task*)m_active)// 如果目前這一個TASK剛剛好是第一個被執行的TASK,因為插在前面的關係所以要更新一下m_active
			{
				m_active = (BYTE*)new_task;
			}
			// 更新相鄰TASK的m_next,m_pre的值
			new_task->m_pre = task->m_pre;
			new_task->m_next = task;
			break;
		}
		else if (next == (Task*)m_active)// 設定的優先權大於或等於目前TASK的優先權
		{                             // 將欲生成的TASK插入在目前TASK的後面,注意這僅僅更新TASK的 m_pre,m_next的值,並不實際移動TASK
			// 更新相鄰TASK的m_next,m_pre的值
			new_task->m_pre = task;
			new_task->m_next = next;
			break;
		}
	}

	new_task->m_use = TRUE;// 設定為使用中
	new_task->m_size = (DWORD)size;// 設定TASK佔用BYTE數的大小
	new_task->m_priority = priority;// 設定優先權
	// 更新相鄰TASK的m_next,m_pre的值
	new_task->m_pre->m_next = new_task;
	new_task->m_next->m_pre = new_task;

	return new_task;// 返回生成TASK的開頭位址,除非有必要得知這個位址,不然可以不理會這一個回傳值
}

// 對已存在的TASK更改優先權
void Task::SetPriority(float priority)
{
	m_priority = priority;// 設定新的優先權

	// 將這一個TASK的相鄰TASK給重新對接好
	if (this == (Task*)m_active)// 是第一個被執行的TASK嗎?
	{
		if (m_next == (Task*)m_active) return;	// 是LIST中唯一的TASK嗎?
		m_active = (BYTE*)m_next;// 重設m_active
	}
	// 更新相鄰TASK的 m_pre,m_next
	m_pre->m_next = m_next;
	m_next->m_pre = m_pre;

	// 開始尋找要插入的位址
	Task *active = (Task*)m_active;// 取得第一個被執行中的值

	Task *task, *next;// 暫存用
	//從第一個找起
	for (task = active;; task = next)
	{
		next = task->m_next;// 取得下一個TASK的位址

		if (priority < task->m_priority)		// 設定的優先權小於目前TASK的優先權
		{                                   // 將欲生成的TASK插入在目前TASK的前面,注意這僅僅更新TASK的 m_pre,m_next的值,並不實際移動TASK
			if (task == (Task*)m_active)		// 如果目前這一個TASK剛剛好是第一個被執行的TASK,因為插在前面的關係所以要更新一下m_active
			{
				m_active = (BYTE*)this;// 更新m_active
			}
			// 更新TASK的 m_pre,m_next
			m_pre = task->m_pre;
			m_next = task;
			break;
		}
		else if (next == active)// 設定的優先權大於或等於目前TASK的優先權
		{                    // 將欲生成的TASK插入在目前TASK的後面,注意這僅僅更新TASK的 m_pre,m_next的值,並不實際移動TASK
			// 更新TASK的 m_pre,m_next
			m_pre = task;
			m_next = next;
			break;
		}
	}

	// 更新相鄰TASK的 m_pre,m_next
	m_pre->m_next = this;
	m_next->m_pre = this;

	// 在設定一次m_active的值,以防萬一
	if (priority < active->m_priority) m_active = (BYTE*)this;
}

// 取得目前所有TASK所使用的記憶體BYTE總數
DWORD Task::GetSize(void)
{
	return g_size;
}

// 取得目前所有執行中的TASK數目
DWORD Task::GetCount(void)
{
	return g_count;
}

// 將所申請的記憶體空間的內容以16進制dump到指定的檔案,DEBUG用
void Task::Dump(const char *filename)
{
	if (g_buf == NULL) return;		// 若還未執行過初始化動作,別做以下的動作

	FILE *fp = fopen(filename, "w");

	int i;

	fprintf(fp, "          ");
	for (i = 0; i<16; i++)
	{
		if (i % 16 == 8) fprintf(fp, " ");
		fprintf(fp, " %02x", i);
	}
	fprintf(fp, "\n");

	fprintf(fp, "          ");
	for (i = 0; i<16; i++)
	{
		if (i % 16 == 8) fprintf(fp, "-");
		fprintf(fp, "---");
	}
	fprintf(fp, "\n");

	for (i = 0; i<MEM_SIZE; i++)
	{
		if (i % 16 == 0) fprintf(fp, "%p |", g_buf + i);
		else if (i % 16 == 8) fprintf(fp, " ");
		fprintf(fp, " %02x", *(g_buf + i));
		if (i % 16 == 15) fprintf(fp, "\n");
	}

	fclose(fp);
}

wxCriticalSection& Task::GetCriticalSectionObject(void){
	return g_critsect;
}

