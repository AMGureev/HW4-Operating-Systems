#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

// Функция для копирования содержимого одного файла в другой
void copy_file(const char *source_filename, const char *destination_filename) {
    int source_fd, dest_fd;         // Файловые дескрипторы для исходного и целевого файлов
    char buffer[BUFFER_SIZE];       // Буфер для чтения и записи данных
    ssize_t bytesRead, bytesWritten; // Количество байт, прочитанных и записанных
    // Открываем файл для чтения
    source_fd = open(source_filename, O_RDONLY);
    if (source_fd == -1) {
        perror("Ошибка при открытии файла для чтения");
        exit(EXIT_FAILURE);
    }
    // Открываем или создаем файл для записи с правами, аналогичными исходному файлу
    struct stat source_stat;
    if (fstat(source_fd, &source_stat) == -1) {
        perror("Ошибка при получении информации о файле");
        close(source_fd);
        exit(EXIT_FAILURE);
    }
    dest_fd = open(destination_filename, O_WRONLY | O_CREAT | O_TRUNC, source_stat.st_mode);
    if (dest_fd == -1) {
        perror("Ошибка при открытии или создании файла для записи");
        close(source_fd);
        exit(EXIT_FAILURE);
    }
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
    // Проверяем ошибку чтения
    if (bytesRead == -1) {
        perror("Ошибка при чтении данных из файла");
        close(source_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }
    // Закрываем файлы
    close(source_fd);
    close(dest_fd);
}

int main(int argc, char *argv[]) {
    // Проверяем, что передано два аргумента командной строки
    if (argc != 3) {
        fprintf(stderr, "Использование: %s <исходный файл> <целевой файл>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // Копируем файл
    copy_file(argv[1], argv[2]);
    printf("Файл успешно скопирован: %s -> %s\n", argv[1], argv[2]);
    return 0;
}
