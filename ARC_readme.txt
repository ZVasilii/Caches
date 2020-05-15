int imax(int a, int b) 
обычная функция max, возвращающая наибольшее

int imin(int a, int b) 
обычная функция imin, возвращающая наименьшее

void replace(int *p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem)
p - параметр кеша
page_name - название страницы
T1, B1, B2, T2 - части кеша
mem - указать на память
cache_mem - указатель на память кеша
Функция переноса из T в B кеш, для подробного изучения см. алгоритм

struct cell* insert_in_head(struct list_t* part, long long int page_name, struct page_t* cache_ptr)
part - указать на часть кеша
page_name - название(индекс) страницы
cache_ptr - указатель на страницу в памяти кеша
Вставляет в part новую голову списка с помощью insert_to_head с заданными значениями page_name и cache_ptr

struct cache_t* from_mem_to_cache_mem(long long int page_name, struct page_t* mem, struct cache_t* cache_mem)
page_name - название страницы
mem - указатель на память
cache_mem - указатель на память кеша
Копирует страницу из памяти в память кеша по заданному названию

struct cell* fast_get_page(int* p, long long int page_name, struct list_t* T1, struct list_t* T2, struct list_t* B1, struct list_t* B2, struct page_t* mem, struct cache_t* cache_mem, int* T_hits)
Функция кеширования
p - вспомогательный параметр кеширования
page_name - название или индекс страницы
T1, T2, B1, B2 - инициализированные части кеша
mem - указатель на память
cache_mem - указатель на память кеша
T_hits - количество попаданий в кеш
Выдает указатель на элемент кеша с данным названием(индексом)
Описание:
1)Поиск среди закешированных страниц
2)При попадании в T1 и T2 происходит лишь перестановка ячеек, увеличение числа попаданий T_hits
3)При попадании в B1, B2 или промахе происходит перестановка(возможно, удаление элементов), добавление в память кеша и адаптация

