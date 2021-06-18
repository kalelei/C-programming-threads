# C-programming-threads
Synchronize d ≤ m threads so they can shift an m x m matrix concurrently. You will repeat the following shifts s many times: first perform a circular shift from left to right,
then a circular shift from bottom to top. Here is an example with m = 4 and s = 1:

Each thread is responsible for m/d consecutive rows (last thread may take more if d ∤ m) during 
row shifting, and then m/d consecutive columns for the column shifting, e.g., with m = 4 and d
= 2, thread 0 shifts rows 0-1, and thread 1 shifts rows 2-3. No thread can start shifting columns 
until all threads have finished shifting rows. Also, if s > 1, no thread can start shifting rows for 
the current stage until all threads have finished shifting columns in the previous stage.
