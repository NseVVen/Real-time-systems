#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

#define SEM_NAME "/mysemaphore"

int main() {
    int pipefd[2];
    pid_t pid;
    sem_t *sem;

    // Создаем pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Создаем именованный семафор (начальное значение 0)
    sem = sem_open(SEM_NAME, O_CREAT | O_EXCL, 0600, 0);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // === Дочерний процесс ===
        close(pipefd[1]); // Закрываем запись

        sem_wait(sem); // Ждем сигнала от родителя

        char buffer[128];
        read(pipefd[0], buffer, sizeof(buffer));
        printf("👶 Дочерний процесс получил сообщение: %s\n", buffer);

        close(pipefd[0]);
        sem_close(sem);
        exit(0);

    } else {
        // === Родительский процесс ===
        close(pipefd[0]); // Закрываем чтение

        char msg[] = "Привет от родителя!";
        write(pipefd[1], msg, strlen(msg) + 1);
        printf("👨 Родитель отправил сообщение\n");

        sem_post(sem); // Сигналим дочернему процессу

        wait(NULL); // Ждем завершения дочернего процесса

        sem_close(sem);
        sem_unlink(SEM_NAME); // Удаляем семафор
        close(pipefd[1]);
    }

    return 0;
}
