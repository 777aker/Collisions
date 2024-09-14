#pragma once
#ifndef common // man, getting double defined variables to not happen is so hard
#define common

// do I even need all these libraries?
// barrier doesn't even work lol
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstring>
#include <barrier>
#include <thread>
#include <mutex>
#include <atomic>
#include <pthread.h>
#include <random>
#include <memory>
#include <shared_mutex>

// different headers depending on what machine you're on
#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#include <OpenGL/gl.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#define PI 3.14159265

#define SEQ_CST memory_order_seq_cst
using namespace std;

extern double dim; // size of the world
extern double asp; // aspect ratio
extern bool wasResized; // called resize function

#define TESTINGRW false
// atomics for testing retry amounts
extern atomic<int> readretries;
extern atomic<int> writeretries;

extern int fps; // fps

// colors for drawing
struct color {
	int r;
	int g;
	int b;
};

const struct color asphalt = { 52, 73, 94 };
const struct color concrete = { 127, 140, 141 };
const struct color nephritis = { 39, 174, 96 };
const struct color midnight = { 44, 62, 80 };
const struct color emerald = { 46, 204, 113 };
const struct color sunflower = { 241, 196, 15 };
const struct color alizarin = { 231, 76, 60 };

void debugline(); // nice print

// had to build a barrier because barrier not working and idk if mingw supports it
class sensebar {
public:
	sensebar(int numthreads) {
		cnt.store(1, SEQ_CST);
		sense.store(false, SEQ_CST);
		N = numthreads;
	}
	void wait() {
		thread_local bool my_sense = false;
		my_sense = !my_sense;

		if (cnt.fetch_add(1, SEQ_CST) == N) {
			cnt.store(1, SEQ_CST);
			sense.store(my_sense, SEQ_CST);
		}
		else {
			while (sense.load() != my_sense) {}
		}
	}
	atomic<bool> sense;
	int N;
private:
	atomic<int> cnt;
};

#endif // !common
