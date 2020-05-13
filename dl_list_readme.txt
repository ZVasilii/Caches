��� ���������� �� ������������� ����������� ������.

���������� ����� ������: dl_list.c

������������ ����: dl_list.h, pages.h



������ ������� �� �����: 
���������� ������: struct cell <name>
���������� �������� (������ �������� �� �������������):
struct cell {
    struct cell* prev;
    struct cell* next;
    long long int data;
    struct page_t* page_ptr;
};


��� ������ ����� ���� ����������� ���������� (�������� ������ ��������) 
struct list_t {
    struct cell* head;
    unsigned long long length;
};

��������� �������:

�������� ����� ������:
struct cell* make_cell()
������� ������, ���������� ��������� �� ���. ��� �� ��������� 0, ��������� �� �������� �����������.
�� �������� ��������� ������ ����� �������������. 
struct cell* make_cell_n(long long int name)
������� ������ � �������� ������
struct cell* make_cell_p(long long int name, struct page_t* page_ptr)
������� ������ � �������� ����������.
struct cell* make_cell_np(long long int name, struct page_t* page_ptr)
������� ������ � �������� ������ � ����������.
struct list_t* make_list(unsigned long long length)
������� ������ � ������� �������� ����� length. ��� length = 0 ������� ������ ��� �����. 

����������� ������: 
void destroy_cell(struct cell* c) 
���������� ���� ������ �� ���������� ���������, ������ ������.
���������� "����", ������� ����� �������� �� �� �����.
void destroy_all_cells(struct cell* c) 
���������� ��������� ������ � ���, ������� � ��� �������. 
������������� ������ �� ����������� �������.

����������� ������: 
void destroy_list(struct list_t* l)
���������� ������ � ��� ��� ������.

����������� ������: 
struct cell* place_cell_before(struct cell* c, struct cell* place)
struct cell* place_cell_after(struct cell* c, struct cell* place)
���������� ����� *� �� ������� �� ��� ����� *place. ���������� "����", ������� ����� �������� �� ������ �����.
���������� ����� ����� ������ ������� �������� �������������.

��������� ����� ������: 
long long int cell_name(struct cell* c)
���������� ��� ������ �� ���������.

������� � ����������/��������� ������:
struct cell* next_cell(struct cell* c)
struct cell* prev_cell(struct cell* c)
�������� ��������� �� ������� ������, ���������� ��������� �� ���������/����������.

������ � ���������� ������:
struct cell* set_page(struct cell* c, struct page_t* page_ptr)
���������� � ������ �������� ���������� ���������, ������ ��� ������� ������������ ����������.
��������� ��������� �� ������.
struct page_t* cell_page(struct cell* c)
���������� ���������� � ������ ���������. ��� ����������� ��������� NULL.

����� ������:
struct cell* find_cell(struct list_t* l, long long int name)
���� ������ � �������� ������, ���������� ��������� �� ���. l - ��������� �� ������.
��� ������� ���������� ����� � ���������� ������ ���������� �����.

���������� ����� ������:
unsigned long long list_len(struct cell* c)
���������� ����� ������ �� ����� ��� ������. ������������� ������ � ������������ ��������.

������������ ����������������� ������:
void list_test()
������� ��� ������ ���������� ���������� ���������.
