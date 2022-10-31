#include "first.hpp"

LMP::forward_list read_and_sort(std::stringstream &ss) {
    LMP::forward_list forward_list;
    //пока есть что считывать
    while (!ss.eof()){
        //считываем число
        int read;
        ss >> read;
        //если считали
        if (!ss.fail()){
            //ищем место для вставки
            auto it = forward_list.begin(), end = forward_list.end();
            //пока не дошли до конца и не нашли звено, число в котором больше или равно вставляемому
            while (it!=end && *it < read){
                ++it;
            }
            //вставляем перед найденным местом
            forward_list.insert_before(it, read);
        }
    }
    return forward_list;
}

void task_1(LMP::forward_list &forward_list, std::stringstream &out) {
    //будем запоминать, стёрли ли что-то
    bool found = false;
    //если список не пуст, то можно его обойти
    if (!forward_list.empty()) {
        auto it_prev = forward_list.begin();
        auto it = next(forward_list.begin(), 1);
        auto end = forward_list.end();
        //так как мы будем удалять только тот элемент, который стоит после,
        // то можем сразу записывать в файл тот,
        // который уже пройден(первый элемент сразу считаем пройденным)
        //идём, пока не упрёмся в конец списка или не найдём нужное место
        while (it != end && !(*it_prev % 2 == 0 && *it % 2 != 0)) {
            //записываем предыдущий элемент
            out << *it_prev << ' ';
            //свдигаем итераторы
            ++it, ++it_prev;
        }
        //записываем элемент, который стоит перед местом остановки, так как цикл не запишет его
        out << *it_prev << ' ';
        //если мы остановились не в коцне
        if (it != forward_list.end()) {
            //мы нашли
            found = true;
            //удаляем элемент после предыдущего и сдвигаем итератор на следующий за ним элемент
            it = forward_list.erase_after(it_prev);
        }
        //проходим оставшийся список
        while (it != end){
            out << *it << ' ';
            ++it;
        }
    }
    //если мы ничего не нашли, то записываем, что мы ничего не нашли
    if (!found){
        out << '\n';
        out << "Numbers not found";
    }
}
