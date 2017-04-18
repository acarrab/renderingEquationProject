#include "../include/teapot.h"

void Teapot::draw() {
  glUseProgram(programId);
  glUniformMatrix4fv(mvpMtxId, 1, GL_FALSE, &mvp[0][0]);
  glUniformMatrix4fv(rtnMtxId, 1, GL_FALSE, &rtn[0][0]);
  glm::vec3 lightPos = lh.getPosition();
  glUniform3f(lightId, lightPos.x, lightPos.y, lightPos.z);

  for (const VBO_Data & va : data.getAttribs()) {
    glEnableVertexAttribArray(va.attribNum);
    glVertexAttribPointer(va.attribNum, va.vecSize, va.dataType,
			  va.normalized, va.stride, va.address);
    glBindBuffer(GL_ARRAY_BUFFER, va.id);
  }
  glDrawArrays(data.getVertexType(), 0, data.getVertexCount());

  for (const VBO_Data & va : data.getAttribs()) {
    glDisableVertexAttribArray(va.attribNum);
  }
}
