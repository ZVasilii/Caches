Это инструкция по использованию двусвязного списка.

Внутренние файлы списка: dl_list.c

Заголовочный файл: dl_list.h, pages.h



Список состоит из ячеек: 
Объявление ячейки: struct cell <name>
Внутреннее строение (работа напрямую не предусмотрена):
struct cell {
    struct cell* prev;
    struct cell* next;
    long long int data;
    struct page_t* page_ptr;
};


Сам список может быть представлен структурой (возможна работа напрямую) 
struct list_t {
    struct cell* head;
    unsigned long long length;
};

Доступные функции:

Создание одной ячейки:
struct cell* make_cell()
Создает ячейку, возвращает указатель на нее. Имя по умолчанию 0, указатель на страницу отсутствует.
Не забудьте почистить память после использования. 
struct cell* make_cell_n(long long int name)
Создает ячейку с заданным именем
struct cell* make_cell_p(long long int name, struct page_t* page_ptr)
Создает ячейку с заданным указателем.
struct cell* make_cell_np(long long int name, struct page_t* page_ptr)
Создает ячейку с заданным именем и указателем.
struct list_t* make_list(unsigned long long length)
Создает список с пустыми ячейками длины length. При length = 0 создает список без ячеек. 

Уничтожение ячейки: 
void destroy_cell(struct cell* c) 
Уничтожает одну ячейку по введенному указателю, очищая память.
Затягивает "дыры", которые могли остаться на ее месте.
void destroy_all_cells(struct cell* c) 
Уничтожает указанную ячейку и все, которые с ней связаны. 
Предусмотрена работа на зацикленных списках.

Уничтожение списка: 
void destroy_list(struct list_t* l)
Уничтожает список и все его ячейки.

Перемещение ячейки: 
struct cell* place_cell_before(struct cell* c, struct cell* place)
struct cell* place_cell_after(struct cell* c, struct cell* place)
Перемещает ячеку *с на позицию до или после *place. Затягивает "дыры", которые могли остаться на старом месте.
Вставление между двумя подряд идущими ячейками предусмотрено.

Получение имени ячейки: 
long long int cell_name(struct cell* c)
Возвращает имя ячейки по указателю.

Переход к предыдущей/следующей ячейке:
struct cell* next_cell(struct cell* c)
struct cell* prev_cell(struct cell* c)
Получает указатель на текущую ячейку, возвращает указатель на следующую/предыдущую.

Работа с указателем ячейки:
struct cell* set_page(struct cell* c, struct page_t* page_ptr)
Записывает в ячейку значение введенного указателя, старый при наличии безвозвратно затирается.
Возращает указатель на ячейку.
struct page_t* cell_page(struct cell* c)
Возвращает записанный в ячейку указатель. При отстутствии возращает NULL.

Поиск ячейки:
struct cell* find_cell(struct list_t* l, long long int name)
Ищет ячейку с заданным именем, возвращает указатель на нее. l - указатель на список.
При наличии нескольких ячеек с одинаковым именем возвращает любую.

Нахождение длины списка:
unsigned long long list_len(struct cell* c)
Возвращает длину списка по любой его ячейке. Предусмотрена работа с зацикленными списками.

Тестирование работоспособности списка:
void list_test()
Сделано при помощи реализации сортировки вставками.
