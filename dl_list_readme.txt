��� ���������� �� ������������� ����������� ������.

���������� ����� ������: dl_list.c

������������ ����: dl_list.h



������ ������� �� �����: 
���������� ������: struct cell <name>
���������� �������� (������ �������� �� �������������):
struct cell {
    struct cell* prev;
    struct cell* next;
    long long int data;
    void* pointer;
};



��������� �������:

�������� ����� ������: struct cell* make_cell(long long int name)
��������� "���" ������, ���������� ��������� �� ���. �� �������� ��������� ������ ����� �������������.

����������� ������: void destroy_cell(struct cell* c) 
���������� ���� ������ �� ���������� ���������, ������ ������.

����������� ������: 
struct cell* place_cell_before(struct cell* c, struct cell* place)
struct cell* place_cell_after(struct cell* c, struct cell* place)
���������� ����� *� �� ������� �� ��� ����� *place. ���������� "����", ������� ����� �������� �� ������ �����.
���������� ����� ����� ������ ������� �������� �������������.

��������� ����� ������: int cell_name(struct cell* c)
���������� ��� ������ �� ���������. long long int �������� � �����, ����� ��������.

������� � ����������/��������� ������:
struct cell* next_cell(struct cell* c)
struct cell* prev_cell(struct cell* c)
�������� ��������� �� ������� ������, ���������� ��������� �� ���������/����������.