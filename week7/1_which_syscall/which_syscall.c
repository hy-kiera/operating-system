#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  long orig_rax;
  pid_t child;
  int status;
  int input;
  child = fork();
  if (child == 0) {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL); // pause execution (child)
    raise(SIGSTOP); // signal to parent
    scanf("%d", &input);
    printf("INPUT: %d\n", input);
  } else {
    while (1) {
      wait(&status);
      if (WIFEXITED(status))
        break;
      orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
      printf("SYSCALL NO: %ld\n", orig_rax); // orig_rax : system call number
      ptrace(PTRACE_SYSCALL, child, NULL, NULL); // restart execution (child)
    }
  }
  return 0;
}
