/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice) {
  printf("Running task = name: [%s] priority: [%d] burst: [%d] tid: [%d] for slice: %d units.\n",task->name, task->priority, task->burst, task->tid, slice);
}
