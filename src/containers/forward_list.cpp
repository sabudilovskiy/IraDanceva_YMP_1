#include "forward_list.hpp"
#include <stdexcept>

namespace LMP
{
    forward_list::node::~node() {
        //Освобождаем память, занятую звеном: удаляем все последующие звенья
        if (next){
            delete next;
        }
    }
    forward_list::node::node(TInfo info, forward_list::node *next) : info(info), next(next) {}

    forward_list::iterator::iterator(forward_list::node *ptr) : ptr(ptr) {}

    //реализация префиксного инкремента
    forward_list::iterator &forward_list::iterator::operator++() {
        //если есть возможность двигаться дальше, то двигаемся
        if (this->ptr->next != nullptr)this->ptr = this->ptr->next;
        //если нет возможности двинуться дальше, то кидаем эксепшен
        else {
            throw std::out_of_range("The iterator cannot be moved to the next link because there is none.");
        }
        return *this;
    }

    forward_list::iterator forward_list::iterator::operator++(int) {
        //создаём копию старого итератора
        auto copy = *this;
        //идём дальше по возможности
        if (this->ptr->next != nullptr)this->ptr = this->ptr->next;
        else {
            throw std::out_of_range("The iterator cannot be moved to the next link because there is none.");
        }
        //возвращаем старый итератор
        return copy;
    }

    forward_list::iterator forward_list::begin() {
        //возвращаем итератор, указывающий на первой ноду(следующая после головы)
        return {head_ptr->next};
    }
    forward_list::iterator forward_list::end() {
        //возвращаем итератор, указывающий на последнюю ноду
        return {end_ptr};
    }

    void forward_list::clear() {
        //получаем первую ноду
        auto& begin_ptr = head_ptr->next;
        if (begin_ptr != end_ptr){
            //удаляем все ноды кроме первой
            delete begin_ptr->next;
            //переставляем последнюю ноду и помечаем, что у неё нет потомка
            end_ptr = begin_ptr;
            end_ptr->next = nullptr;
        }
    }

    forward_list::~forward_list() {
        //если есть что удалять - удаляем
        if (head_ptr) delete head_ptr;
    }

    forward_list::iterator forward_list::insert_after(forward_list::iterator pos, TInfo info) {
        //если вставляем в корректных диапазонах
        if (pos.ptr != end_ptr){
            //получаем ссылку на поле, хранящее следующее звено
            auto& after = pos.ptr->next;
            //в это поле кладём указатель на новое звено,
            // хранящее вставляему информацию и указывающее на то звено,
            // которое раньше следовало после того, в которое вставляем
            after = new node(info, after);
            //возвращаем итератор, указывающий на новое звено
            return iterator(after->next);
        }
        //если нет, то кидаем ошибку
        else{
            throw std::out_of_range("Can't insert after end");
        }
    }

    forward_list::iterator forward_list::erase_after(forward_list::iterator pos) {
        //получаем ссылку на поле, хранящее следующее звено
        auto& after = pos.ptr->next;
        //проверяем, что есть что стирать
        if (!after){
            throw std::out_of_range("The iterator cannot be moved to the next node because there is none.");
        }
        //проверяем, что стираем не последний узел
        if (after == end_ptr){
            throw std::out_of_range("forward_list cannot erase next node because it is the end node");
        }
        //запоминаем указатель на звено, идущий после следующего звена
        auto next_after = after->next;
        //стираем зависимость между удаляемым звеном и остальным списком
        after->next = nullptr;
        //удаляем удаляемое звено
        delete after;
        //записываем в поле у изначального итератора указатель на то звено, которое было за следующим
        after = next_after;
        //уменьшаем размер
        --_size;
        //возвращаем итератор на элемент, находящийся после удаляемого
        return iterator(after);
    }

    forward_list::forward_list(forward_list &&another){
        //конструируем валидный список. Без конструирования деструктор не отработает корректно
        construct();
        //меняем местами все поля
        std::swap(this->_size, another._size);
        std::swap(this->head_ptr, another.head_ptr);
        std::swap(this->end_ptr, another.end_ptr);
    }

    forward_list::forward_list() {
        construct();
    }

    void forward_list::push_front(TInfo info) {
        //создаём новое звено после головы, в нём будет вставляемая информация, а следующее звено то, которые было до этого следующим после головы
        head_ptr->next = new node(info, head_ptr->next);
        _size++;
    }

    size_t forward_list::size() const {
        return _size;
    }

    void forward_list::insert_before(forward_list::iterator pos, TInfo info) {
        //если вставка идёт не перед головой и не перед последним звеном
        if (pos.ptr != head_ptr && pos.ptr && pos.ptr != end_ptr){
            //создаём звено, которое будет идентично тому, перед которым вставляем и записываем его как следующее
            pos.ptr->next = new node(pos.ptr->info, pos.ptr->next);
            //в старом звене записываем новую информацию
            pos.ptr->info = info;
            //увеличиваем размер
            ++_size;
        }
        //если вставка идёт перед последним звеном, то потребуется заменить последнее звено
        else if (pos.ptr == end_ptr){
            end_ptr->info = info;
            end_ptr->next = new node(0);
            end_ptr = end_ptr->next;
            ++_size;
        }
        //вставка перед головой невозможна
        else throw std::out_of_range("can't insert before head");
    }

    void forward_list::construct() {

        end_ptr = new node{};
        //голова будет указывать на конечное звено
        head_ptr = new node(0, end_ptr);
        _size = 0;
    }

    bool forward_list::empty() {
        return _size == 0;
    }

    TInfo &forward_list::iterator::operator*() {
        //при разыменовывании итератора возвращаем ссылку на информацию внутри него
        return ptr->info;
    }

    bool forward_list::iterator::operator==(forward_list::iterator right) {
        return right.ptr == this->ptr;
    }

    bool forward_list::iterator::operator!=(forward_list::iterator right) {
        return !(*this == right);
    }
    forward_list::iterator next(forward_list::iterator iter, size_t pos) {
        for (size_t index = 0; index < pos; ++index){
            ++iter;
        }
        return iter;
    }
}

