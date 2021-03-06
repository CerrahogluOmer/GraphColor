typedef struct bucket {
	int *vertices;
	int size;
	int capacity;
} bucket;

bucket* init_bucket() {
	bucket *new_bucket = malloc(sizeof(bucket *));
	new_bucket->vertices = malloc(sizeof(int *));
	new_bucket->size = 0;
	new_bucket->capacity = 1;
}

static void free_bucket(bucket *bucket) {
	free(bucket->vertices);
}

void kill_bucket(bucket *bucket) {
	free_bucket(bucket);
	free(bucket);
}

static void resize(bucket *bucket, int new_capacity) {
	bucket->capacity = new_capacity;
	int *new_vertices = malloc(new_capacity * sizeof(int *));
	cilk_for (int i = 0; i < bucket->size; i++) {
		new_vertices[i] = vertices[i];
	}
	free(bucket->vertices);
	bucket->vertices = new_vertices;
}

void insert_bucket(bucket *bucket, int *vertices, int num) {
	if (bucket->size + num > capacity) {
		resize(bucket, 2 * (bucket->size + num));
	}
	cilk_for (int i = 0; i < num; i++) {
		bucket[bucket->size + i] = vertices[i];
	}
	bucket->size += num;
}

// Doesn't use resize in case of overflow
// void insert_optimized(bucket *bucket, int *vertices, int num);