<h1 align="center">Version Log</h1>

This file contains the versions history of developing this project.

## Version 1.0.0

**Date:** 2022-03-22
**Description:** Initial version.

Added the following features:

1. Using Timer 2 to count the time with a fixed tick rate of 50ms.
2. Create a Task using (```cuteOS_TaskCreate```).
3. Remove a Task using (```cuteOS_TaskRemove```).
4. Ability to create upto 10 tasks.
5. Priority of the tasks is fixed. Tasks are given priority in the order of creation.
6. Minimum task tick rate is 1ms, maximum is 65 seconds.

## Version 1.0.1

**Date:** 2022-04-14
**Description:** Improvement in the code.

Added the following features:

1. The old fixed tick rate is replaced by the greatest common tick time using **Greatest Common Divisor Algorithm** to make the system faster and stable.
2. Naming Convention of variables updated. (```tickTime``` is now ```tick_time```)
3. Standard Types in STD_TYPES.h updated to:
   * Apply new naming convention. (```u8``` is now ```u8_t```)
   * Reduce the size of the code.
4. Max number of tasks is now 8 instead of 10 due to the limitation of the MCU memory.
