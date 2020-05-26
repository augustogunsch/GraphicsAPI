#include <cube.hpp>
#include <debug.hpp>

cube::cube(program *program, camera *camera, glm::vec3 worldPosition, glm::vec3 rotation,
glm::vec3 scale) : 
model(program, camera, worldPosition, rotation, scale) {
  float vertexData[] = {
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

    0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f, 0.0f, 1.0f
  };
  
  //VBO
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  
  //VAO
  glGenVertexArrays(1, &ID);
  glBindVertexArray(ID);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  
  // Unbinding all
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
 
void cube::use() {
  glBindVertexArray(ID);
}

void cube::render() {
  myProgram->use();
  debug::queryErrors("After prog use:");

  glm::mat4 modelM = getModelMatrix();
  glm::mat4 viewM = myCamera->getViewMatrix();
  glm::mat4 projectionM = myCamera->getProjectionMatrix();
  debug::queryErrors("After matrices query:");

  myProgram->setMat4("modelM", modelM);
  myProgram->setMat4("viewM", viewM);
  myProgram->setMat4("projectionM", projectionM);
  debug::queryErrors("After matrices assignment:");
  
  use();
  debug::queryErrors("After cube use:");
  glDrawArrays(GL_TRIANGLES, 0, 36);
  debug::queryErrors("After draw:");
}