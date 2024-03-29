# HW4-Operating-Systems
## Задание выполнено на 10 баллов. В работе представлена 1 программа, в которой покрываются все условия для получения высокой оценки.
### `Условие на оценку 10` : читать и переписывать не только текстовые, но и исполняемые файлы (текстовые и бинарные, содержащие признак исполнимости), включая скрипты, которые сохраняют режим доступа исходных файлов, обеспечивающий их запуск. При этом обычные текстовые файлы запускаться не должны. Для них режим доступа должен оставаться прежним.

```c++
// Открываем или создаем файл для записи с правами, аналогичными исходному файлу
struct stat source_stat;
if (fstat(source_fd, &source_stat) == -1) {
    perror("Ошибка при получении информации о файле");
    close(source_fd);
    exit(EXIT_FAILURE);
}

dest_fd = open(destination_filename, O_WRONLY | O_CREAT | O_TRUNC, source_stat.st_mode);
if (dest_fd == -1) {
    perror("Ошибка при открытии/создании файла для записи");
    close(source_fd);
    exit(EXIT_FAILURE);
}
```
`fstat` используется для получения информации о файле (в данном случае, о исходном файле), включая режим доступа. Затем, при открытии целевого файла (destination_filename), используется `source_stat.st_mode` для установки прав доступа такими же, как у исходного файла.</br>
Это обеспечивает сохранение режима доступа для целевого файла, который становится копией исходного файла
### `Условие на оценку 9` : вместо большого буфера использовать для работы с файлами буфер ограниченного размера, требующий циклического использования как для чтения, так и для записи.
При выполнении задания в программе было соблюдено данное условие:
```c++
char buffer[BUFFER_SIZE];       // Буфер для чтения и записи данных, где BUFFER_SIZE = 4096
// Циклическое чтение и запись с использованием буфера
while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
    bytesWritten = write(dest_fd, buffer, bytesRead);
    if (bytesWritten != bytesRead) {
        perror("Ошибка при записи данных в файл");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }
}
```
### `Условие на оценку 8` : разработать программу использующую для работы с текстовыми файлами только системные вызовы. Программа на языке C (или C++ в стиле C) должна прочитать, используя буфер, размер которого превышает читаемые файлы и записать прочитанный файл в файл с другим именем. Имена файлов для чтения и записи задавать с использованием аргументов командной строки.
#### Решение (с подробными комментариями) предоставлено в файле [main.cpp](https://github.com/AMGureev/HW4-Operating-Systems/blob/main/main.cpp). </br>
#### Инструкция по запуску:
+ Ввести в консоль команду `g++ file_name`, где далее `file_name` - расположение файла.
+ Ввести в консоль команду `./a.out first_argument second_argument`, где `first_argument` - исходный файл, а `second_argument` - целевой файл.   
## Работу выполнил студент 2 курса БПИ227 Гуреев Александр Михайлович
