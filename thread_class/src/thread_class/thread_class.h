#include <sched.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <system_error>

#define CHECK(fun)                                                             \
  if ((fun) == -1) {                                                           \
    throw std::system_error(errno, std::generic_category());                   \
  }

class thread_class {
  pid_t pid;
  size_t stack_size;
  char *child_stack;
  void *child_stack_end;
  int status; // 0 - is running, 1 - otherwise
public:
  // конструктор
  thread_class(int (*fun)(void *args)) {
    stack_size = 1024 * 10;
    child_stack = new char[stack_size];
    child_stack_end = child_stack + stack_size;
    CHECK(pid = clone(
              fun, child_stack_end,
              CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | SIGCHLD, 0));
    status = 0;
  };

  // метод join
  void join() { CHECK(waitpid(pid, &status, 0)); };

  // метод joinable
  bool joinable() {
    if (pid > 0 && status == 0 && kill(pid, 0)) {
      return true;
    };
    return false;
  };

  // метод get_id
  pid_t get_id() { return pid; };

  // метод swap
  void swap(thread_class &rightThread) {
    pid_t tmpPid = rightThread.pid;
    size_t tmpstack_size = rightThread.stack_size;
    char *tmpchild_stack = rightThread.child_stack;
    void *tmpchild_stack_end = rightThread.child_stack_end;
    int tmpStatus = rightThread.status;

    rightThread.pid = this->pid;
    rightThread.stack_size = this->stack_size;
    rightThread.child_stack = this->child_stack;
    rightThread.child_stack_end = this->child_stack_end;
    rightThread.status = this->status;

    this->pid = tmpPid;
    this->stack_size = tmpstack_size;
    this->child_stack = tmpchild_stack;
    this->child_stack_end = tmpchild_stack_end;
    this->status = tmpStatus;
  };

  // оператор присваивания с перемещением
  thread_class &operator=(thread_class &&rightThread) {
    this->swap(rightThread);
    return *this;
  }
  /*  thread_class &operator=(const thread_class &rightThread) {
      if (this != &rightThread) {
        thread_class tmp(rightThread);
        this->swap(tmp);
      };
      return *this;
    }*/

  // деструктор
  ~thread_class() {
    if (kill(pid, 0)) {
      kill(pid, SIGTERM);
    };
    if (child_stack) {
      delete[] child_stack;
    };
  };
};
