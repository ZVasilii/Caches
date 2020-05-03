Ёто инструкци€ по использованию двусв€зного списка.

¬нутренние файлы списка: dl_list.c

«аголовочный файл: dl_list.h



—писок состоит из €чеек: 
ќбъ€вление €чейки: struct cell <name>
¬нутреннее строение (работа напр€мую не предусмотрена):
struct cell {
    struct cell* prev;
    struct cell* next;
    long long int data;
    void* pointer;
};



ƒоступные функции:

—оздание одной €чейки: struct cell* make_cell(long long int name)
ѕринимает "им€" €чейки, возвращает указатель на нее. Ќе забудьте почистить пам€ть после использовани€.

”ничтожение €чейки: void destroy_cell(struct cell* c) 
”ничтожает одну €чейку по введенному указателю, очища€ пам€ть.

ѕеремещение €чейки: 
struct cell* place_cell_before(struct cell* c, struct cell* place)
struct cell* place_cell_after(struct cell* c, struct cell* place)
ѕеремещает €чеку *с на позицию до или после *place. «ат€гивает "дыры", которые могли остатьс€ на старом месте.
¬ставление между двум€ подр€д идущими €чейками предусмотрено.

ѕолучение имени €чейки: int cell_name(struct cell* c)
¬озвращает им€ €чейки по указателю. long long int дописать € забыл, потом поправлю.

ѕереход к предыдущей/следующей €чейке:
struct cell* next_cell(struct cell* c)
struct cell* prev_cell(struct cell* c)
ѕолучает указатель на текущую €чейку, возвращает указатель на следующую/предыдущую.