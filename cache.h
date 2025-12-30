// #ifndef __CACHE_H__
// #define __CACHE_H__

// #define QUEUE_SIZE 10
// #define LINE_LENGTH 64

// struct Queue {
//   char lines[QUEUE_SIZE][LINE_LENGTH];
//   int cut_index;
// };

// // Initialize the queue
// void queue_init(Queue* q);

// // Enqueue a string (removes oldest if queue is full)
// void queue_enqueue(Queue* q, const char* line);

// // Get element at index x (0-based, returns nullptr if invalid index)
// const char* queue_get(Queue* q, int x);

// #endif