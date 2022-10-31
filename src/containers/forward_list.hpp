#pragma once

#include <cstddef>

using TInfo = int;
namespace LMP{
    class forward_list {
    protected:
        /*
         звено односвязного списка:
         хранит информацию и следующее звено
         */
        struct node{
            TInfo info;
            forward_list::node* next;
            explicit node(TInfo info = 0, forward_list::node *next = nullptr);
            ~node();
        };
        //Указатель на голову односвязного списка. Необходим для более простой вставки.
        forward_list::node* head_ptr;
        //Указатель на последний элемент. Необходим для более просто итерирования
        forward_list::node* end_ptr;
        // размер списка
        size_t _size;
        //метод для конструирования валидного объекта списка
        void construct();
    public:
        //итератор для обхода списка.
        class iterator{
        protected:
            //делаем список дружественным итератору, чтобы тот имел прямой доступ
            friend class forward_list;
            //храним внутри себя указатель на звено списка
            forward_list::node* ptr;
            //конструктор сделаем защищённым, чтобы его не было видно снаружи
            iterator(node *ptr);
        public:
            //префиксный инкремент
            iterator& operator++();
            //постфиксный инкремент
            iterator operator++(int);
            //оператор разыменовывания для доступа к элементу списка
            TInfo& operator*();
            //оператор равенства итераторов. Возвращает истину, если итераторы указывают на одинаковый узел
            bool operator==(iterator right);
            //оператор неравенства итераторов. Возвращает истину, если итераторы указывают на разные узлы
            bool operator!=(iterator right);
            //функция для увеличения итератора на отличное от единицы
            friend iterator next(iterator iter, size_t pos);
        };
        //возвращает размер списка
        size_t size() const;
        //очищает список
        void clear();
        //возвращает итератор, указывающий на начало
        iterator begin();
        //возвращает итератор, указываюший на конец
        iterator end();
        //вставка после узла внутри переданного итератора. Возвращает итератор, указывающий на созданный узел.
        iterator insert_after(iterator pos, TInfo info);
        //вставка перед узлом внутри переданного итератора. Возвращает итератор, указывающий на созданный узел.
        void insert_before(iterator pos, TInfo info);
        //удалить следующий после итератора узел
        iterator erase_after(iterator pos);
        //возвращает истину, если лист пуст
        bool empty();
        //добавить в начало элемент
        void push_front(TInfo info);
        //запрещаем копировать список(ибо мне лень писать корректный конструктор копирования)
        forward_list(const forward_list& another) = delete;
        //конструктор по умолчанию
        forward_list();
        //конструктор перемещения(вызывается, например, при возврате из функции, если не применено NRVO)
        forward_list(forward_list&& another) ;
        //деструктор, для корректного высвобождения занимаемой памяти
        ~forward_list();
    };

}


