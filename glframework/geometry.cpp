#include"geometry.h"

Geometry::Geometry() {}

Geometry::~Geometry() {
	if (0 != mVao) {
		glDeleteVertexArrays(1, &mVao);
	}
	if (0 != mPosVbo) {
		glDeleteBuffers(1, &mPosVbo);
	}
	if (0 != mUvVbo) {
		glDeleteBuffers(1, &mUvVbo);
	}
	if (0 != mEbo) {
		glDeleteBuffers(1, &mEbo);
	}
}

Geometry* Geometry::createBox(float size) {
	Geometry* geometry = new Geometry();

	geometry->mIndicesCount = 36;

	float halfSize = size / 2.0f;

	float positions[] = {
		-halfSize, -halfSize,  halfSize,  // v0
		 halfSize, -halfSize,  halfSize,  // v1
		 halfSize,  halfSize,  halfSize,  // v2
		-halfSize,  halfSize,  halfSize,  // v3

		// 背面 (z = -halfSize) - 4个顶点
		 halfSize, -halfSize, -halfSize,  // v4
		-halfSize, -halfSize, -halfSize,  // v5
		-halfSize,  halfSize, -halfSize,  // v6
		 halfSize,  halfSize, -halfSize,  // v7

		 // 左面 (x = -halfSize) - 4个顶点
		 -halfSize, -halfSize, -halfSize,  // v8 (重复v5)
		 -halfSize, -halfSize,  halfSize,  // v9 (重复v0)
		 -halfSize,  halfSize,  halfSize,  // v10 (重复v3)
		 -halfSize,  halfSize, -halfSize,  // v11 (重复v6)

		 // 右面 (x = halfSize) - 4个顶点
		  halfSize, -halfSize,  halfSize,  // v12 (重复v1)
		  halfSize, -halfSize, -halfSize,  // v13 (重复v4)
		  halfSize,  halfSize, -halfSize,  // v14 (重复v7)
		  halfSize,  halfSize,  halfSize,  // v15 (重复v2)

		  // 上面 (y = halfSize) - 4个顶点
		  -halfSize,  halfSize,  halfSize,  // v16 (重复v3)
		   halfSize,  halfSize,  halfSize,  // v17 (重复v2)
		   halfSize,  halfSize, -halfSize,  // v18 (重复v7)
		  -halfSize,  halfSize, -halfSize,  // v19 (重复v6)

		  // 下面 (y = -halfSize) - 4个顶点
		  -halfSize, -halfSize, -halfSize,  // v20 (重复v5)
		   halfSize, -halfSize, -halfSize,  // v21 (重复v4)
		   halfSize, -halfSize,  halfSize,  // v22 (重复v1)
		  -halfSize, -halfSize,  halfSize   // v23 (重复v0)
	};

	float uvs[] = {
		// 正面
		0, 0,  // v0
		1, 0,  // v1
		1, 1,  // v2
		0, 1,  // v3

		// 背面 (注意方向保持一致，使纹理可见)
		1, 0,  // v4
		0, 0,  // v5
		0, 1,  // v6
		1, 1,  // v7

		// 左面
		0, 0,  // v8
		1, 0,  // v9
		1, 1,  // v10
		0, 1,  // v11

		// 右面
		1, 0,  // v12
		0, 0,  // v13
		0, 1,  // v14
		1, 1,  // v15

		// 上面
		0, 1,  // v16 (注意上面从y轴俯视，u对应x，v对应z，方向调整使纹理正)
		1, 1,  // v17
		1, 0,  // v18
		0, 0,  // v19

		// 下面
		0, 0,  // v20
		1, 0,  // v21
		1, 1,  // v22
		0, 1   // v23
	};

	unsigned int indices[] = {
		// 正面
	   0, 1, 2,  0, 2, 3,
	   // 背面
	   4, 5, 6,  4, 6, 7,
	   // 左面
	   8, 9, 10,  8, 10, 11,
	   // 右面
	   12, 13, 14,  12, 14, 15,
	   // 上面
	   16, 17, 18,  16, 18, 19,
	   // 下面
	   20, 21, 22,  20, 22, 23
	};
	//geometry->mIndicesCount = sizeof(indices)/sizeof(indices[0]);

	GLuint& posVbo = geometry->mPosVbo;
	GLuint& uvVbo = geometry->mUvVbo;
	GLuint& ebo = geometry->mEbo;

	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// 绑定 EBO 到 VAO，确保 VAO 持有索引缓冲
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);

	return geometry;
}

Geometry* Geometry::createSphere(float radius) {
	Geometry* geometry = new Geometry();

	std::vector<GLfloat> positions{};
	std::vector<GLfloat> uvs{};
	std::vector<GLfloat> normals{};
	std::vector<GLint> indices{};

	int numLatLines = 60;
	int numLongLines = 60;

	for (int i = 0; i <= numLatLines; i++) {
		for (int j = 0; j <= numLongLines; j++) {
			float phi = i * glm::pi<float>() / numLatLines;
			float theta = j * 2 * glm::pi<float>() / numLongLines;

			float y = radius * cos(phi);
			float x = radius * sin(phi) * cos(theta);
			float z = radius * sin(phi) * sin(theta);

			positions.push_back(x);
			positions.push_back(y);
			positions.push_back(z);

			float u = 1.0 - (float)j / (float)numLongLines;
			float v = 1.0 - (float)i / (float)numLatLines;

			uvs.push_back(u);
			uvs.push_back(v);

			//法线没有归一化
			normals.push_back(x);
			normals.push_back(y);
			normals.push_back(z);
		}
	}

	for (int i = 0; i < numLatLines; i++) {
		for (int j = 0; j < numLongLines; j++) {
			int p1 = i * (numLongLines + 1) + j;
			int p2 = p1 + numLongLines + 1;
			int p3 = p1 + 1;
			int p4 = p2 + 1;

			indices.push_back(p1);
			indices.push_back(p2);
			indices.push_back(p3);

			indices.push_back(p3);
			indices.push_back(p2);
			indices.push_back(p4);
		}
	}

	GLuint& posVbo = geometry->mPosVbo,
		uvVbo = geometry->mUvVbo,
		normalVbo = geometry->mNormalVbo,
		ebo = geometry->mEbo;

	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(int), indices.data(), GL_STATIC_DRAW);


	//生成vao，并将vbo注入vao
	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// 绑定 EBO 到 VAO，确保 VAO 持有索引缓冲
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);

	geometry->mIndicesCount = indices.size();

	return geometry;
}

Geometry* Geometry::createPlane(float width, float height) {
	Geometry* geometry = new Geometry();
	geometry->mIndicesCount = 6;
	float halfW = width / 2.0f;
	float halfH = height / 2.0f;

	float positions[] = {
		-halfW, -halfH, 0.0f,  // 顶点0: 左下
		halfW, -halfH, 0.0f,  // 顶点1: 右下
		-halfW,  halfH, 0.0f,  // 顶点2: 左上
		halfW,  halfH, 0.0f   // 顶点3: 右上
	};

	float uvs[] = {
		0.0f, 0.0f,  // 左下
		1.0f, 0.0f,  // 右下
		0.0f, 1.0f,  // 左上
		1.0f, 1.0f   // 右上
	};

	float normals[] = {
		0.0f, 0.0f, 1.0f,  // 顶点0
		0.0f, 0.0f, 1.0f,  // 顶点1
		0.0f, 0.0f, 1.0f,  // 顶点2
		0.0f, 0.0f, 1.0f   // 顶点3
	};

	unsigned int indices[] = {
		0, 1, 2,  // 第一个三角形
		3, 2, 1   // 第二个三角形
	};

	GLuint& posVbo = geometry->mPosVbo;
	GLuint& uvVbo = geometry->mUvVbo;
	GLuint& normalVbo = geometry->mNormalVbo;
	GLuint& ebo = geometry->mEbo;

	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	glGenBuffers(1, &normalVbo);
	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//generate vao and insert vbo into it
	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, normalVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// 绑定 EBO 到 VAO，确保 VAO 持有索引缓冲
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBindVertexArray(0);

	return geometry;
}